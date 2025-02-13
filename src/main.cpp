#include <lpp.h>
#include <modem.h>
#include <rtcm_generator.h>
#include <arpa/inet.h>
#include <fstream>
#include <getopt.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define UNUSED [[maybe_unused]]
#define SSR 0

struct Options {
    const char* host;
    int         port;
    bool        ssl;

    long mcc;
    long mnc;
    long tac;
    long cell_id;
    long msm_type;
};

int           connected = -1;
int           sockfd;
LPP_Client    client;
CellID        cell;
int           device;

bool provide_location_information_callback(LocationInformation* location, void* userdata);
bool provide_ecid_callback(ECIDInformation* ecid, void* userdata);
void assistance_data_callback(LPP_Client*, LPP_Transaction* transaction, LPP_Message* message,
                              void* userdata);
speed_t get_baud(long baud);

int get_agnss() {
    Options options = Options {
        // .host = "supl.qxwz.com",
        // .port = 7276,
        // .ssl = false,

        // .host = "supl.qxwz.com",
        // .port = 7275,
        // .ssl = true,

        // .host = "ppp.bd-caict.com",
        // .port = 7275,
        // .ssl = true,

        .host = "121.229.15.186",
        .port = 7275,
        .ssl = true,

        .mcc = 460,
        .mnc = 0,
        // .tac = 25509,
        // .cell_id = 336,

        .tac = 25509,
        .cell_id = 205772544,
    };

    cell         = CellID{
        .mcc  = options.mcc,
        .mnc  = options.mnc,
        .tac  = options.tac,
        .cell = options.cell_id,
    };

    // printf("Location Server: %s:%d %s\n", options.host, options.port, options.ssl ? "[ssl]" : "");
    // printf("Cell:            MCC=%ld, MNC=%ld, TAC=%ld, Id=%ld\n", cell.mcc, cell.mnc, cell.tac,
    //        cell.cell);

    // Flush pending printf output
    // fflush(stdout);

    // Initialize OpenSSL
    network_initialize();

    // Register callback for when the location server request location
    // information from the device.
    client.provide_location_information_callback(NULL, provide_location_information_callback);

    // Connect to location server
    if (!client.connect(options.host, options.port, options.ssl, cell, assistance_data_callback)) {
        printf("ERROR: Connection failed. (%s:%i%s)\n", options.host, options.port,
               options.ssl ? " [ssl]" : "");
        return 1;
    }


#if !SSR
    // Request assistance data (OSR) from server for the 'cell' and register a callback
    // when we receive assistance data.
    auto request = client.request_assistance_data(cell, NULL, assistance_data_callback);
    return 0;
#else
    // Request assistance data (SSR) from server for the 'cell' and register a callback
    // when we receive assistance data.
    auto request = client.request_assistance_data_ssr(cell, NULL, assistance_data_callback);
#endif
    if (request == AD_REQUEST_INVALID) {
        printf("ERROR: Requesting assistance data failed.\n");
        return 1;
    }

    // Run LPP client
    for (;;) {
        struct timespec timeout;
        timeout.tv_sec  = 0;
        timeout.tv_nsec = 1'000'000 * 100;  // 100 ms
        nanosleep(&timeout, NULL);

        // client.process() MUST be called at least once every second, otherwise
        // ProvideLocationInformation messages will send to the server.
        if (!client.process()) {
            printf("ERROR: Client has lost connection.\n");
            return 1;
        }
    }

    network_cleanup();
    return EXIT_SUCCESS;
}

bool provide_location_information_callback(LocationInformation* location, UNUSED void* userdata) {
    printf("provide_location_information_callback\n");
    location->time = time(NULL);
    location->lat  = 20;
    location->lon  = 20;
    return true;
}

#define c_2p55    36028797018963968
#define c_2p50    1125899906842624
#define c_2p43    8796093022208
#define c_2p38    274877906944  
#define c_2p33    8589934592  
#define c_2p31    2147483648  
#define c_2p30    1073741824  
#define c_2p29    536870912  
#define c_2p27    134217728  
#define c_2p24    16777216  
#define c_2p23    8388608  
#define c_2p21    2097152  
#define c_2p20    1048576  
#define c_2p19    524288  
#define c_2p16    65536.0
#define c_2p14    16384.0
#define c_2p12    4096.0
#define c_2p11    2048.0
#define c_2p5     32
#define c_2p4     16.0
#define c_2p3     8

#define c_2m4     0.0625
#define c_2m5     0.03125
#define c_2m6     0.015625
#define c_2m11    4.8828125e-4
#define c_2m12    0.000244140625
#define c_2m14    0.00006103515625
#define c_2m16    0.0000152587890625
#define c_2m19    1.9073486328125e-6
#define c_2m20    9.5367431640625e-7
#define c_2m21    4.76837158203125e-7
#define c_2m23    1.1920928955078125e-7
#define c_2m24    5.9604644775390625e-8
#define c_2m27    7.450580596923828125e-9
#define c_2m29    1.86264514923095703125e-9
#define c_2m30    9.31322574615478515625e-10
#define c_2m31    4.656612873077392578125e-10
#define c_2m32    2.32830644e-10
#define c_2m33    1.16415321826934814453125e-10
#define c_2m34    5.82076609e-11
#define c_2m38    3.63797880709171295166015625e-12
#define c_2m43    1.136868377216160297393798828125e-13
#define c_2m46    1.42108547e-14
#define c_2m50    8.8817841970012523233890533447266e-16
#define c_2m55    2.7755575615628913510590791702271e-17
#define c_2m59    1.73472348e-18
#define c_2m66    1.35525271560688e-20

#define CUBE(x)  ((x)*(x)*(x))	 

typedef struct ephemeris
{
  int    SatID,
         Valideph,    // 
         ExpiredSeceph,
         week,     // 10bit,week number
         tow,      // 0 - 604800 seconds
         iodc,     // 10bit,issue of date, clock       IODC=..IODE
         iode,     // 8bit, issue of date, ephemeris
         ura,      // 4bit, user range accuracy
         health;   // 6bit, satellite health

  float  af0,      // clock polynomial correction parameters
         af1,
         af2,
         tgd,      // satellite group delay differential correction term
         toc,      // clock data reference time
         toe,      // reference time ephemeris
         ety,      // eccentricity  
         sqra,     // square root of semi-major axis 
         ma,       // mean anomaly at reference time 
         wm,       // mean motion [rad/sec]          
         dn,       // mean motion correction term (delta n)
         inc0,     // inclination angle at reference time  
         idot,     // rate of inclination angle  
         omega0,   // (was w0) longitude of ascending node of orbit plane at weekly epoch 
         omegadot, // rate of right ascension    
         w,        // argument of perigee  
         cuc,      // amplitude of the cosine harmonic correction term to the argument of latitude
         cus,      // amplitude of the sine harmonic correction term to the argument of latitude
         crc,      // amplitude of the cosine harmonic correction term to the orbit radius
         crs,      // amplitude of the sine harmonic correction term to the orbit radius
         cic,      // amplitude of the cosine harmonic correction term to the angle of inclination
         cis;      // amplitude of the sine harmonic correction term to the angle of inclination
} EPHEMERIS;

void printf_ephemeris(EPHEMERIS ephemeris) {
    
        char * point = (char*)&ephemeris;
        int size = sizeof(ephemeris);
        write(device, point, size);
        
        // printf("satId:%d\n", ephemeris.SatID);
        // for(int i = 0; i < size; ++i) {
        //     printf("%.2x ", (unsigned char)point[i]);
        // }
        // printf("\n");

    return;

    printf("SatId:%d, validEph:%d, week:%d, tow:%d, iodc:%d, iode:%d, ura:%d, health:%d, ",
            ephemeris.SatID,
            ephemeris.Valideph,
            ephemeris.week,
            ephemeris.tow,
            ephemeris.iodc,
            ephemeris.iode,
            ephemeris.ura,
            ephemeris.health);
    
    printf("af0:%.8e, af1:%e, af2:%.8e, tgd:%.8e, toc:%.8e, toe:%.8e, ety:%.8e, sqra:%.8e, ma:%.8e, wm:%.8e, dn:%.8e, inc0:%.8e, idot:%.8e, omega0:%.8e, omegadot:%.8e, w:%.8e, ",
            ephemeris.af0,
            ephemeris.af1,
            ephemeris.af2,
            ephemeris.tgd,
            ephemeris.toc,
            ephemeris.toe,
            ephemeris.ety,
            ephemeris.sqra,
            ephemeris.ma,
            ephemeris.wm,
            ephemeris.dn,
            ephemeris.inc0,
            ephemeris.idot,
            ephemeris.omega0,
            ephemeris.omegadot,
            ephemeris.w);
    
    printf("cuc:%.8e, cus:%.8e, crc:%.8e, crs:%.8e, cic:%.8e, cis:%.8e\n",
            ephemeris.cuc,
            ephemeris.cus,
            ephemeris.crc,
            ephemeris.crs,
            ephemeris.cic,
            ephemeris.cis);
}

void assistance_data_callback(LPP_Client*, LPP_Transaction*, LPP_Message* message, void*) {
    // Convert LPP message to buffer of RTCM coded messages.

    auto provideAssistanceData = message->lpp_MessageBody->choice.c1.choice.provideAssistanceData.criticalExtensions.choice.c1.choice.provideAssistanceData_r9.a_gnss_ProvideAssistanceData;

    auto gnss_SystemTime = provideAssistanceData->gnss_CommonAssistData->gnss_ReferenceTime->gnss_SystemTime;
    int tow = gnss_SystemTime.gnss_DayNumber % 7 * 24 * 60 * 60 + gnss_SystemTime.gnss_TimeOfDay;
    int week = gnss_SystemTime.gnss_DayNumber/7;

    auto location_info = provideAssistanceData->gnss_CommonAssistData->gnss_ReferenceLocation->threeDlocation;
    float latitude = location_info.degreesLatitude * 1.0 / 8388607.0 * 90;
    float longitude = location_info.degreesLongitude * 1.0 / 8388608.0 * 180;
    printf("latitude:%f, longitude:%f, ", latitude, longitude);

    for(int i = 0; i < provideAssistanceData->gnss_GenericAssistData->list.count; ++i) {

        usleep(100*1000);
        
        char c = (char)0xff;
        write(device,&c,1);
        c = (char)0xfe;
        write(device,&c,1);
        c = (char)0xfd;
        write(device,&c,1);

        write(device, &latitude, 4);
        write(device, &longitude, 4);

        auto genericAssistDataElement = provideAssistanceData->gnss_GenericAssistData->list.array[i];
        c = (char)genericAssistDataElement->gnss_ID.gnss_id;
        write(device,&c,1);

        auto modelSatelliteElements = genericAssistDataElement->gnss_NavigationModel->gnss_SatelliteList.list;
        
        printf("gnss_id:%ld, count:%d, ", genericAssistDataElement->gnss_ID.gnss_id, modelSatelliteElements.count);
        
        c = (char)modelSatelliteElements.count;
        write(device,&c,1);

        for (int i = 0; i < modelSatelliteElements.count; i++)
        {
            usleep(100*1000);
            if(genericAssistDataElement->gnss_ID.gnss_id == GNSS_ID__gnss_id_gps) {
                
                auto modelSatelliteElement = modelSatelliteElements.array[i];
                auto keplerianSet = modelSatelliteElement->gnss_OrbitModel.choice.nav_KeplerianSet;
                auto clockModel = modelSatelliteElement->gnss_ClockModel.choice.nav_ClockModel;

                EPHEMERIS ephemeris;

                // asn_bit_string_int64
                ephemeris.SatID = modelSatelliteElement->svID.satellite_id;
                ephemeris.Valideph = 1;
                ephemeris.week = week;

                ephemeris.tow = tow;
                ephemeris.iodc = asn_bit_string_int64_left(&modelSatelliteElement->iod, 0, 11);
                ephemeris.iode = asn_bit_string_int64_left(&modelSatelliteElement->iod, 0, 11);
                ephemeris.ura = keplerianSet.navURA;
                ephemeris.health = asn_bit_string_int64(&modelSatelliteElement->svHealth, 0);

                ephemeris.af0 = clockModel.navaf0 * c_2m31;
                ephemeris.af1 = clockModel.navaf1 * c_2m43;
                ephemeris.af2 = clockModel.navaf2 * c_2m55;
                ephemeris.tgd = clockModel.navTgd * c_2m31;
                ephemeris.toc = clockModel.navToc * c_2p4;

                ephemeris.toe = keplerianSet.navToe * c_2p4;
                ephemeris.ety = keplerianSet.navE * c_2m33;
                ephemeris.sqra = keplerianSet.navAPowerHalf * c_2m19;
                ephemeris.ma = keplerianSet.navM0 * c_2m31;
                ephemeris.wm = (float)19964981.843217388 / CUBE(ephemeris.sqra); 
                ephemeris.dn = keplerianSet.navDeltaN * c_2m43;
                ephemeris.inc0 = keplerianSet.navI0 * c_2m31;
                ephemeris.idot = keplerianSet.navIDot * c_2m43;
                ephemeris.omega0 = keplerianSet.navOmegaA0 * c_2m31;
                ephemeris.omegadot = keplerianSet.navOmegaADot * c_2m43;
                ephemeris.w = keplerianSet.navOmega * c_2m31;

                ephemeris.cuc = keplerianSet.navCuc * c_2m29;
                ephemeris.cus = keplerianSet.navCus * c_2m29;
                ephemeris.crc = keplerianSet.navCrc * c_2m5;
                ephemeris.crs = keplerianSet.navCrs * c_2m5;
                ephemeris.cic = keplerianSet.navCic * c_2m29;
                ephemeris.cis = keplerianSet.navCis * c_2m29;


                printf_ephemeris(ephemeris);
            } else if(genericAssistDataElement->gnss_ID.gnss_id == GNSS_ID__gnss_id_bds) {

                auto modelSatelliteElement = modelSatelliteElements.array[i];
                auto keplerianSet = modelSatelliteElement->gnss_OrbitModel.choice.bds_KeplerianSet_r12;
                auto clockModel = modelSatelliteElement->gnss_ClockModel.choice.bds_ClockModel_r12;

                EPHEMERIS ephemeris;

                // asn_bit_string_int64
                ephemeris.SatID = modelSatelliteElement->svID.satellite_id;
                ephemeris.Valideph = 1;
                ephemeris.week = week;
                ephemeris.tow = tow;
                ephemeris.iodc = asn_bit_string_int64_left(&modelSatelliteElement->iod, 0, 11);
                ephemeris.iode = asn_bit_string_int64_left(&modelSatelliteElement->iod, 0, 11);
                ephemeris.ura = keplerianSet.bdsURAI_r12;
                ephemeris.health = asn_bit_string_int64(&modelSatelliteElement->svHealth, 0);
                
                ephemeris.af0 = clockModel.bdsA0_r12 * c_2m33;
                ephemeris.af1 = clockModel.bdsA1_r12 * c_2m50;
                ephemeris.af2 = clockModel.bdsA2_r12 * c_2m66;
                ephemeris.tgd = clockModel.bdsTgd1_r12 * 0.1;
                ephemeris.toc = clockModel.bdsToc_r12 * c_2p3;

                ephemeris.toe = keplerianSet.bdsToe_r12 * c_2p3;
                ephemeris.ety = keplerianSet.bdsE_r12 * c_2m33;
                ephemeris.sqra = keplerianSet.bdsAPowerHalf_r12 * c_2m19;
                ephemeris.ma = keplerianSet.bdsM0_r12 * c_2m31;
                ephemeris.wm = (float)19964981.843217388 / CUBE(ephemeris.sqra); 
                ephemeris.dn = keplerianSet.bdsDeltaN_r12 * c_2m43;
                ephemeris.inc0 = keplerianSet.bdsI0_r12 * c_2m31;
                ephemeris.idot = keplerianSet.bdsIDot_r12 * c_2m43;
                ephemeris.omega0 = keplerianSet.bdsOmega0_r12 * c_2m31;
                ephemeris.omegadot = keplerianSet.bdsOmegaDot_r12 * c_2m43;
                ephemeris.w = keplerianSet.bdsW_r12 * c_2m31;

                ephemeris.cuc = keplerianSet.bdsCuc_r12 * c_2m31;
                ephemeris.cus = keplerianSet.bdsCus_r12 * c_2m31;
                ephemeris.crc = keplerianSet.bdsCrc_r12 * c_2m6;
                ephemeris.crs = keplerianSet.bdsCrs_r12 * c_2m6;
                ephemeris.cic = keplerianSet.bdsCic_r12 * c_2m31;
                ephemeris.cis = keplerianSet.bdsCis_r12 * c_2m31;
                
                printf_ephemeris(ephemeris);
            } else {
                printf("gnss:%ld, not support!\n", genericAssistDataElement->gnss_ID.gnss_id);
            }

        }
    
    }
    printf("\n");
}

speed_t get_baud(long baud) {
switch (baud) {
    case 50:
        return B50;
    case 75:
        return B75;
    case 110:
        return B110;
    case 134:
        return B134;
    case 150:
        return B150;
    case 200:
        return B200;
    case 300:
        return B300;
    case 600:
        return B600;
    case 1200:
        return B1200;
    case 1800:
        return B1800;
    case 2400:
        return B2400;
    case 4800:
        return B4800;
    case 9600:
        return B9600;
    case 19200:
        return B19200;
    case 38400:
        return B38400;
    case 57600:
        return B57600;
    case 115200:
        return B115200;
    case 230400:
        return B230400;
    default: 
        return B0;
    }
}


int main() {

    char path[50] = "/dev/ttyUSB0";

    device = open(path, O_RDWR);
    printf("OUTPUT Serial Port: %s\n", path);
    if (device < 0) {
        printf("ERROR: Opening serial port failed. %s.\n", strerror(errno));
        return 1;
    }
    struct termios tios;
    tcgetattr(device, &tios);

    // Disable flow control, and ignore break and parity errors
    tios.c_iflag = IGNBRK | IGNPAR;
    tios.c_oflag = 0;
    tios.c_lflag = 0;

    // Set baud rate
    cfsetspeed(&tios, get_baud(115200));
    tcsetattr(device, TCSAFLUSH, &tios);

    srand(time(NULL));
    while(1) {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t t_c = std::chrono::system_clock::to_time_t(now);
        printf("time:%s", std::ctime(&t_c));

        get_agnss();

        // int random_seconds = rand() % 10 + 1;
        int random_seconds = 1;
        sleep(random_seconds * 60);
    }

    // while(1) {

    // }

    close(device);

    // while(1) {
    //     char value[50];
    //     int nread = read(device, value, 50);
    //     value[nread] = '\0';
    //     printf("nread:%d, value:%s\n", nread, value);
    //     printf("%x\n", ((unsigned int)value[0]));
    // }

    return 0;
}