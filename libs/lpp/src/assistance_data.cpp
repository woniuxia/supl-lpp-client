#include "internal_lpp.h"
#include "lpp.h"


struct ttttttttt {
		A_SEQUENCE_OF(long) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	};

OCTET_STRING* lpp_request_assistance_data(LPP_Transaction* transaction, CellID cell, long interval) {
    auto message = lpp_create(transaction, LPP_MessageBody__c1_PR_requestAssistanceData);
    auto body    = message->lpp_MessageBody;

    auto cext     = &body->choice.c1.choice.requestAssistanceData.criticalExtensions;
    cext->present = RequestAssistanceData__criticalExtensions_PR_c1;
    cext->choice.c1.present =
        RequestAssistanceData__criticalExtensions__c1_PR_requestAssistanceData_r9;

    auto cad2 = ALLOC_ZERO(CommonIEsRequestAssistanceData::CommonIEsRequestAssistanceData__ext2);

    auto cad           = ALLOC_ZERO(CommonIEsRequestAssistanceData);
    cad->primaryCellID = ecgi_create(cell.mcc, cell.mnc, cell.cell);
    cad->ext2          = cad2;

    auto car_time = ALLOC_ZERO(GNSS_ReferenceTimeReq_t);
    asn_sequence_empty(&car_time->gnss_TimeReqPrefList.list);
    {
        auto id     = ALLOC_ZERO(GNSS_ID_t);
        id->gnss_id = GNSS_ID__gnss_id_gps;
        asn_sequence_add(&car_time->gnss_TimeReqPrefList.list, id);
    }
    {
        auto id     = ALLOC_ZERO(GNSS_ID_t);
        id->gnss_id = GNSS_ID__gnss_id_bds;
        asn_sequence_add(&car_time->gnss_TimeReqPrefList.list, id);
    }

    BOOLEAN_t *flag = (BOOLEAN_t *)malloc(sizeof(BOOLEAN_t));
    *flag = true;
    car_time->gps_TOW_assistReq = flag;

    flag = (BOOLEAN_t *)malloc(sizeof(BOOLEAN_t));
    *flag = true;
    car_time->notOfLeapSecReq = flag;
    auto car                   = ALLOC_ZERO(GNSS_CommonAssistDataReq_t);
    car->gnss_ReferenceTimeReq = car_time;
    // car->ext1                  = car1;
    car->gnss_ReferenceLocationReq = ALLOC_ZERO(GNSS_ReferenceLocationReq);

    // GENERIC
    auto gar = ALLOC_ZERO(GNSS_GenericAssistDataReq_t);
    asn_sequence_empty(&gar->list);

    // GPS
    {
    
        auto element                          = ALLOC_ZERO(GNSS_GenericAssistDataReqElement_t);
        element->gnss_ID.gnss_id              = GNSS_ID__gnss_id_gps;
        element->gnss_AuxiliaryInformationReq = ALLOC_ZERO(GNSS_AuxiliaryInformationReq);

        // TODO
        // gnss_TimeModelsReq
        auto timeModelListReq = ALLOC_ZERO(GNSS_TimeModelListReq);
        element->gnss_TimeModelsReq = timeModelListReq;
        asn_sequence_empty(&element->gnss_TimeModelsReq->list);
        auto timeModelElement = ALLOC_ZERO(GNSS_TimeModelElementReq);
        timeModelElement->gnss_TO_IDsReq = 1;
        timeModelElement->deltaTreq = true;
        asn_sequence_add(&element->gnss_TimeModelsReq->list, timeModelElement);

        // gnss_DifferentialCorrectionsReq
        auto differentialCorrections = ALLOC_ZERO(GNSS_DifferentialCorrectionsReq);
        element->gnss_DifferentialCorrectionsReq = differentialCorrections;
        auto signals = &element->gnss_DifferentialCorrectionsReq->dgnss_SignalsReq.gnss_SignalIDs;
        asn_bit_string_set_length(signals, 8);
        for(int i = 5; i < 8; ++i) {
            asn_bit_string_set(signals, i, 1);
        }
        element->gnss_DifferentialCorrectionsReq->dgnss_ValidityTimeReq = true;

        // gnss_NavigationModelReq
        auto navigationModelReq = ALLOC_ZERO(GNSS_NavigationModelReq);
        element->gnss_NavigationModelReq = navigationModelReq;
        auto navigationModel = element->gnss_NavigationModelReq;
        navigationModel->present = GNSS_NavigationModelReq_PR_reqNavList;
        signals = &navigationModel->choice.reqNavList.svReqList;
        asn_bit_string_set_length(signals, 64);  // 0xFF
        for(int i = 32; i < 64; ++i) {
            asn_bit_string_set(signals, i, 1);
        }
        
        auto clockModelID_PrefList = ALLOC_ZERO(ReqNavListInfo::ReqNavListInfo__clockModelID_PrefList);
        navigationModel->choice.reqNavList.clockModelID_PrefList = clockModelID_PrefList;
        asn_sequence_empty(navigationModel->choice.reqNavList.clockModelID_PrefList);
        asn_sequence_add(navigationModel->choice.reqNavList.clockModelID_PrefList, newLong(2));

        auto orbitModelID_PrefList = ALLOC_ZERO(ReqNavListInfo::ReqNavListInfo__orbitModelID_PrefList);
        navigationModel->choice.reqNavList.orbitModelID_PrefList = orbitModelID_PrefList;
        asn_sequence_empty(navigationModel->choice.reqNavList.orbitModelID_PrefList);
        asn_sequence_add(navigationModel->choice.reqNavList.orbitModelID_PrefList, newLong(2));


        flag = (BOOLEAN_t *)malloc(sizeof(BOOLEAN_t));
        *flag = true;
        navigationModel->choice.reqNavList.addNavparamReq = flag;

        // dataBitAssistance
        auto dataBitAssistanceReq = ALLOC_ZERO(GNSS_DataBitAssistanceReq);
        element->gnss_DataBitAssistanceReq = dataBitAssistanceReq;
        auto dataBitAssistance = element->gnss_DataBitAssistanceReq;
        dataBitAssistance->gnss_TOD_Req = 0;
        dataBitAssistance->gnss_TOD_FracReq = newLong(0);
        dataBitAssistance->dataBitInterval = 0;
        signals = &dataBitAssistance->gnss_SignalType.gnss_SignalIDs;
        asn_bit_string_set_length(signals, 8);  // 0xFF
        for(int i = 5; i < 8; ++i) {
            asn_bit_string_set(signals, i, 1);
        }

        // acquisitionAssistance
        auto acquisitionAssistanceReq = ALLOC_ZERO(GNSS_AcquisitionAssistanceReq);
        element->gnss_AcquisitionAssistanceReq = acquisitionAssistanceReq;
        element->gnss_AcquisitionAssistanceReq->gnss_SignalID_Req.gnss_SignalID = 1;

        // almanac
        auto almanacReq = ALLOC_ZERO(GNSS_AlmanacReq);
        element->gnss_AlmanacReq = almanacReq;
        element->gnss_AlmanacReq->modelID = newLong(2);

        // UTCModel
        auto UTC_ModelReq = ALLOC_ZERO(GNSS_UTC_ModelReq);
        element->gnss_UTCModelReq = UTC_ModelReq;
        element->gnss_UTCModelReq->modelID = newLong(1);

        asn_sequence_add(&gar->list, element);
    }

    // BEIDOU
    {

        auto element                          = ALLOC_ZERO(GNSS_GenericAssistDataReqElement_t);
        element->gnss_ID.gnss_id              = GNSS_ID__gnss_id_bds;
        element->gnss_AuxiliaryInformationReq = ALLOC_ZERO(GNSS_AuxiliaryInformationReq);

        // TODO
        // gnss_TimeModelsReq
        auto timeModelListReq = ALLOC_ZERO(GNSS_TimeModelListReq);
        element->gnss_TimeModelsReq = timeModelListReq;
        asn_sequence_empty(&element->gnss_TimeModelsReq->list);
        auto timeModelElement = ALLOC_ZERO(GNSS_TimeModelElementReq);
        timeModelElement->gnss_TO_IDsReq = 5;
        timeModelElement->deltaTreq = true;
        asn_sequence_add(&element->gnss_TimeModelsReq->list, timeModelElement);

        // gnss_DifferentialCorrectionsReq
        auto differentialCorrections = ALLOC_ZERO(GNSS_DifferentialCorrectionsReq_t);
        element->gnss_DifferentialCorrectionsReq = differentialCorrections;
        auto signals = &element->gnss_DifferentialCorrectionsReq->dgnss_SignalsReq.gnss_SignalIDs;
        asn_bit_string_set_length(signals, 8);
        asn_bit_string_set(signals, 7, 1);
        element->gnss_DifferentialCorrectionsReq->dgnss_ValidityTimeReq = true;

        // gnss_NavigationModelReq
        auto navigationModelReq = ALLOC_ZERO(GNSS_NavigationModelReq);
        element->gnss_NavigationModelReq = navigationModelReq;
        auto navigationModel = element->gnss_NavigationModelReq;
        navigationModel->present = GNSS_NavigationModelReq_PR_reqNavList;
        signals = &navigationModel->choice.reqNavList.svReqList;
        asn_bit_string_set_length(signals, 64);  // 0xFF
        for(int i = 32; i < 64; ++i) {
            asn_bit_string_set(signals, i, 1);
        }
        auto clockModelID_PrefList = ALLOC_ZERO(ReqNavListInfo::ReqNavListInfo__clockModelID_PrefList);
        navigationModel->choice.reqNavList.clockModelID_PrefList = clockModelID_PrefList;
        asn_sequence_empty(navigationModel->choice.reqNavList.clockModelID_PrefList);
        asn_sequence_add(navigationModel->choice.reqNavList.clockModelID_PrefList, newLong(6));

        auto orbitModelID_PrefList = ALLOC_ZERO(ReqNavListInfo::ReqNavListInfo__orbitModelID_PrefList);
        navigationModel->choice.reqNavList.orbitModelID_PrefList = orbitModelID_PrefList;
        asn_sequence_empty(navigationModel->choice.reqNavList.orbitModelID_PrefList);
        asn_sequence_add(navigationModel->choice.reqNavList.orbitModelID_PrefList, newLong(6));

        // dataBitAssistance
        auto dataBitAssistanceReq = ALLOC_ZERO(GNSS_DataBitAssistanceReq);
        element->gnss_DataBitAssistanceReq = dataBitAssistanceReq;
        auto dataBitAssistance = element->gnss_DataBitAssistanceReq;
        dataBitAssistance->gnss_TOD_Req = 0;
        dataBitAssistance->gnss_TOD_FracReq = newLong(0);
        dataBitAssistance->dataBitInterval = 0;
        signals = &dataBitAssistance->gnss_SignalType.gnss_SignalIDs;
        asn_bit_string_set_length(signals, 8);  // 0xFF
        for(int i = 5; i < 8; ++i) {
            asn_bit_string_set(signals, i, 1);
        }

        // acquisitionAssistance
        auto acquisitionAssistanceReq = ALLOC_ZERO(GNSS_AcquisitionAssistanceReq);
        element->gnss_AcquisitionAssistanceReq = acquisitionAssistanceReq;
        element->gnss_AcquisitionAssistanceReq->gnss_SignalID_Req.gnss_SignalID = 1;

        // almanac
        auto almanacReq = ALLOC_ZERO(GNSS_AlmanacReq);
        element->gnss_AlmanacReq = almanacReq;
        element->gnss_AlmanacReq->modelID = newLong(7);

        // UTCModel
        auto UTC_ModelReq = ALLOC_ZERO(GNSS_UTC_ModelReq);
        element->gnss_UTCModelReq = UTC_ModelReq;
        element->gnss_UTCModelReq->modelID = newLong(5);

        // element->ext2                         = element2;
        asn_sequence_add(&gar->list, element);
    }

    auto padq = ALLOC_ZERO(GNSS_PeriodicAssistDataReq_r15_t);

    padq->gnss_RTK_PeriodicResidualsReq_r15 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq->gnss_RTK_PeriodicResidualsReq_r15->deliveryAmount_r15   = 32;
    padq->gnss_RTK_PeriodicResidualsReq_r15->deliveryInterval_r15 = interval;

    padq->glo_RTK_PeriodicBiasInformationReq_r15 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq->glo_RTK_PeriodicBiasInformationReq_r15->deliveryAmount_r15   = 32;
    padq->glo_RTK_PeriodicBiasInformationReq_r15->deliveryInterval_r15 = interval;

    auto gad                       = ALLOC_ZERO(A_GNSS_RequestAssistanceData_t);
    // gad->ext1                      = gad1;
    gad->gnss_CommonAssistDataReq  = car;
    gad->gnss_GenericAssistDataReq = gar;

    auto rad9                            = &cext->choice.c1.choice.requestAssistanceData_r9;
    rad9->commonIEsRequestAssistanceData = cad;
    rad9->a_gnss_RequestAssistanceData   = gad;

    auto result = lpp_encode(message);
    lpp_destroy(message);

    return result;
}

OCTET_STRING* lpp_request_assistance_data_ssr(LPP_Transaction* transaction, CellID cell,
                                              long periodic_id, long interval) {
    auto message = lpp_create(transaction, LPP_MessageBody__c1_PR_requestAssistanceData);
    auto body    = message->lpp_MessageBody;

    auto cext     = &body->choice.c1.choice.requestAssistanceData.criticalExtensions;
    cext->present = RequestAssistanceData__criticalExtensions_PR_c1;
    cext->choice.c1.present =
        RequestAssistanceData__criticalExtensions__c1_PR_requestAssistanceData_r9;

    auto pad1                     = ALLOC_ZERO(PeriodicAssistanceDataControlParameters_r15::
                               PeriodicAssistanceDataControlParameters_r15__ext1);
    auto pad1_update_capabilities = ALLOC_ZERO(UpdateCapabilities_r15_t);
    asn_bit_string_set(pad1_update_capabilities, UpdateCapabilities_r15_primaryCellID_r15, 1);
    pad1->updateCapabilities_r15 = pad1_update_capabilities;

    auto pad = ALLOC_ZERO(PeriodicAssistanceDataControlParameters_r15);
    pad->periodicSessionID_r15.periodicSessionInitiator_r15 =
        PeriodicSessionID_r15__periodicSessionInitiator_r15_targetDevice;
    pad->periodicSessionID_r15.periodicSessionNumber_r15 = periodic_id;
    pad->ext1                                            = pad1;

    auto cad2 = ALLOC_ZERO(CommonIEsRequestAssistanceData::CommonIEsRequestAssistanceData__ext2);
    cad2->periodicAssistanceDataReq_r15 = pad;

    auto cad           = ALLOC_ZERO(CommonIEsRequestAssistanceData);
    cad->primaryCellID = ecgi_create(cell.mcc, cell.mnc, cell.cell);
    cad->ext2          = cad2;

    auto car1_aux                  = ALLOC_ZERO(GNSS_RTK_AuxiliaryStationDataReq_r15);
    auto car1_ref                  = ALLOC_ZERO(GNSS_RTK_ReferenceStationInfoReq_r15);
    car1_ref->antennaHeightReq_r15 = true;

    auto car1 = ALLOC_ZERO(GNSS_CommonAssistDataReq::GNSS_CommonAssistDataReq__ext1);
    car1->gnss_RTK_AuxiliaryStationDataReq_r15 = car1_aux;
    car1->gnss_RTK_ReferenceStationInfoReq_r15 = car1_ref;

    auto car_time = ALLOC_ZERO(GNSS_ReferenceTimeReq_t);
    asn_sequence_empty(&car_time->gnss_TimeReqPrefList.list);
    {
        auto id     = ALLOC_ZERO(GNSS_ID_t);
        id->gnss_id = GNSS_ID__gnss_id_gps;
        asn_sequence_add(&car_time->gnss_TimeReqPrefList.list, id);
    }
    {
        auto id     = ALLOC_ZERO(GNSS_ID_t);
        id->gnss_id = GNSS_ID__gnss_id_glonass;
        asn_sequence_add(&car_time->gnss_TimeReqPrefList.list, id);
    }
    {
        auto id     = ALLOC_ZERO(GNSS_ID_t);
        id->gnss_id = GNSS_ID__gnss_id_galileo;
        asn_sequence_add(&car_time->gnss_TimeReqPrefList.list, id);
    }

    auto car                   = ALLOC_ZERO(GNSS_CommonAssistDataReq_t);
    car->gnss_ReferenceTimeReq = car_time;
    car->ext1                  = car1;

    // GENERIC
    auto gar = ALLOC_ZERO(GNSS_GenericAssistDataReq_t);
    asn_sequence_empty(&gar->list);

    // GPS
    {
        auto element2 =
            ALLOC_ZERO(GNSS_GenericAssistDataReqElement::GNSS_GenericAssistDataReqElement__ext2);
        element2->gnss_SSR_ClockCorrectionsReq_r15 = ALLOC_ZERO(GNSS_SSR_ClockCorrectionsReq_r15);
        element2->gnss_SSR_OrbitCorrectionsReq_r15 = ALLOC_ZERO(GNSS_SSR_OrbitCorrectionsReq_r15);
        element2->gnss_SSR_CodeBiasReq_r15         = ALLOC_ZERO(GNSS_SSR_CodeBiasReq_r15);
        auto codebias_signals =
            &element2->gnss_SSR_CodeBiasReq_r15->signal_and_tracking_mode_ID_Map_r15.gnss_SignalIDs;
        asn_bit_string_set_length(codebias_signals, 8);  // 0xFF
        asn_bit_string_set(codebias_signals, 0, 1);
        asn_bit_string_set(codebias_signals, 1, 1);
        asn_bit_string_set(codebias_signals, 2, 1);
        asn_bit_string_set(codebias_signals, 3, 1);
        asn_bit_string_set(codebias_signals, 4, 1);
        asn_bit_string_set(codebias_signals, 5, 1);
        asn_bit_string_set(codebias_signals, 6, 1);
        asn_bit_string_set(codebias_signals, 7, 1);

        auto element3 =
            ALLOC_ZERO(GNSS_GenericAssistDataReqElement::GNSS_GenericAssistDataReqElement__ext3);
        element3->gnss_SSR_PhaseBiasReq_r16 = ALLOC_ZERO(GNSS_SSR_PhaseBiasReq_r16);
        auto phasebias_signals              = &element3->gnss_SSR_PhaseBiasReq_r16
                                      ->signal_and_tracking_mode_ID_Map_r16.gnss_SignalIDs;
        asn_bit_string_set_length(phasebias_signals, 8);  // 0xFF
        asn_bit_string_set(phasebias_signals, 0, 1);
        asn_bit_string_set(phasebias_signals, 1, 1);
        asn_bit_string_set(phasebias_signals, 2, 1);
        asn_bit_string_set(phasebias_signals, 3, 1);
        asn_bit_string_set(phasebias_signals, 4, 1);
        asn_bit_string_set(phasebias_signals, 5, 1);
        asn_bit_string_set(phasebias_signals, 6, 1);
        asn_bit_string_set(phasebias_signals, 7, 1);

        element3->gnss_SSR_GriddedCorrectionReq_r16 = ALLOC_ZERO(GNSS_SSR_GriddedCorrectionReq_r16);
        element3->gnss_SSR_STEC_CorrectionReq_r16   = ALLOC_ZERO(GNSS_SSR_STEC_CorrectionReq_r16);
        element3->gnss_SSR_URA_Req_r16              = ALLOC_ZERO(GNSS_SSR_URA_Req_r16);

        auto element                          = ALLOC_ZERO(GNSS_GenericAssistDataReqElement_t);
        element->gnss_ID.gnss_id              = GNSS_ID__gnss_id_gps;
        element->gnss_AuxiliaryInformationReq = ALLOC_ZERO(GNSS_AuxiliaryInformationReq);
        element->ext2                         = element2;
        asn_sequence_add(&gar->list, element);
    }

    // GLONASS
    {
        auto element2 =
            ALLOC_ZERO(GNSS_GenericAssistDataReqElement::GNSS_GenericAssistDataReqElement__ext2);
        element2->gnss_SSR_ClockCorrectionsReq_r15 = ALLOC_ZERO(GNSS_SSR_ClockCorrectionsReq_r15);
        element2->gnss_SSR_OrbitCorrectionsReq_r15 = ALLOC_ZERO(GNSS_SSR_OrbitCorrectionsReq_r15);
        element2->gnss_SSR_CodeBiasReq_r15         = ALLOC_ZERO(GNSS_SSR_CodeBiasReq_r15);
        auto codebias_signals =
            &element2->gnss_SSR_CodeBiasReq_r15->signal_and_tracking_mode_ID_Map_r15.gnss_SignalIDs;
        asn_bit_string_set_length(codebias_signals, 8);  // 0xFF
        asn_bit_string_set(codebias_signals, 0, 1);
        asn_bit_string_set(codebias_signals, 1, 1);
        asn_bit_string_set(codebias_signals, 2, 1);
        asn_bit_string_set(codebias_signals, 3, 1);
        asn_bit_string_set(codebias_signals, 4, 1);
        asn_bit_string_set(codebias_signals, 5, 1);
        asn_bit_string_set(codebias_signals, 6, 1);
        asn_bit_string_set(codebias_signals, 7, 1);

        auto element3 =
            ALLOC_ZERO(GNSS_GenericAssistDataReqElement::GNSS_GenericAssistDataReqElement__ext3);
        element3->gnss_SSR_PhaseBiasReq_r16 = ALLOC_ZERO(GNSS_SSR_PhaseBiasReq_r16);
        auto phasebias_signals              = &element3->gnss_SSR_PhaseBiasReq_r16
                                      ->signal_and_tracking_mode_ID_Map_r16.gnss_SignalIDs;
        asn_bit_string_set_length(phasebias_signals, 8);  // 0xFF
        asn_bit_string_set(phasebias_signals, 0, 1);
        asn_bit_string_set(phasebias_signals, 1, 1);
        asn_bit_string_set(phasebias_signals, 2, 1);
        asn_bit_string_set(phasebias_signals, 3, 1);
        asn_bit_string_set(phasebias_signals, 4, 1);
        asn_bit_string_set(phasebias_signals, 5, 1);
        asn_bit_string_set(phasebias_signals, 6, 1);
        asn_bit_string_set(phasebias_signals, 7, 1);

        element3->gnss_SSR_GriddedCorrectionReq_r16 = ALLOC_ZERO(GNSS_SSR_GriddedCorrectionReq_r16);
        element3->gnss_SSR_STEC_CorrectionReq_r16   = ALLOC_ZERO(GNSS_SSR_STEC_CorrectionReq_r16);
        element3->gnss_SSR_URA_Req_r16              = ALLOC_ZERO(GNSS_SSR_URA_Req_r16);

        auto element                          = ALLOC_ZERO(GNSS_GenericAssistDataReqElement_t);
        element->gnss_ID.gnss_id              = GNSS_ID__gnss_id_glonass;
        element->gnss_AuxiliaryInformationReq = ALLOC_ZERO(GNSS_AuxiliaryInformationReq);
        element->ext2                         = element2;
        asn_sequence_add(&gar->list, element);
    }

    // GALILEO
    {
        auto element2 =
            ALLOC_ZERO(GNSS_GenericAssistDataReqElement::GNSS_GenericAssistDataReqElement__ext2);
        element2->gnss_SSR_ClockCorrectionsReq_r15 = ALLOC_ZERO(GNSS_SSR_ClockCorrectionsReq_r15);
        element2->gnss_SSR_OrbitCorrectionsReq_r15 = ALLOC_ZERO(GNSS_SSR_OrbitCorrectionsReq_r15);
        element2->gnss_SSR_CodeBiasReq_r15         = ALLOC_ZERO(GNSS_SSR_CodeBiasReq_r15);
        auto codebias_signals =
            &element2->gnss_SSR_CodeBiasReq_r15->signal_and_tracking_mode_ID_Map_r15.gnss_SignalIDs;
        asn_bit_string_set_length(codebias_signals, 8);  // 0xFF
        asn_bit_string_set(codebias_signals, 0, 1);
        asn_bit_string_set(codebias_signals, 1, 1);
        asn_bit_string_set(codebias_signals, 2, 1);
        asn_bit_string_set(codebias_signals, 3, 1);
        asn_bit_string_set(codebias_signals, 4, 1);
        asn_bit_string_set(codebias_signals, 5, 1);
        asn_bit_string_set(codebias_signals, 6, 1);
        asn_bit_string_set(codebias_signals, 7, 1);

        auto element3 =
            ALLOC_ZERO(GNSS_GenericAssistDataReqElement::GNSS_GenericAssistDataReqElement__ext3);
        element3->gnss_SSR_PhaseBiasReq_r16 = ALLOC_ZERO(GNSS_SSR_PhaseBiasReq_r16);
        auto phasebias_signals              = &element3->gnss_SSR_PhaseBiasReq_r16
                                      ->signal_and_tracking_mode_ID_Map_r16.gnss_SignalIDs;
        asn_bit_string_set_length(phasebias_signals, 8);  // 0xFF
        asn_bit_string_set(phasebias_signals, 0, 1);
        asn_bit_string_set(phasebias_signals, 1, 1);
        asn_bit_string_set(phasebias_signals, 2, 1);
        asn_bit_string_set(phasebias_signals, 3, 1);
        asn_bit_string_set(phasebias_signals, 4, 1);
        asn_bit_string_set(phasebias_signals, 5, 1);
        asn_bit_string_set(phasebias_signals, 6, 1);
        asn_bit_string_set(phasebias_signals, 7, 1);

        element3->gnss_SSR_GriddedCorrectionReq_r16 = ALLOC_ZERO(GNSS_SSR_GriddedCorrectionReq_r16);
        element3->gnss_SSR_STEC_CorrectionReq_r16   = ALLOC_ZERO(GNSS_SSR_STEC_CorrectionReq_r16);
        element3->gnss_SSR_URA_Req_r16              = ALLOC_ZERO(GNSS_SSR_URA_Req_r16);

        auto element                          = ALLOC_ZERO(GNSS_GenericAssistDataReqElement_t);
        element->gnss_ID.gnss_id              = GNSS_ID__gnss_id_galileo;
        element->gnss_AuxiliaryInformationReq = ALLOC_ZERO(GNSS_AuxiliaryInformationReq);
        element->ext2                         = element2;
        asn_sequence_add(&gar->list, element);
    }

    auto padq = ALLOC_ZERO(GNSS_PeriodicAssistDataReq_r15_t);
    auto padq1 = ALLOC_ZERO(GNSS_PeriodicAssistDataReq_r15::GNSS_PeriodicAssistDataReq_r15__ext1);
    padq->ext1 = padq1;

    padq->gnss_SSR_PeriodicClockCorrectionsReq_r15 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq->gnss_SSR_PeriodicClockCorrectionsReq_r15->deliveryAmount_r15   = 32;
    padq->gnss_SSR_PeriodicClockCorrectionsReq_r15->deliveryInterval_r15 = interval;

    padq->gnss_SSR_PeriodicOrbitCorrectionsReq_r15 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq->gnss_SSR_PeriodicOrbitCorrectionsReq_r15->deliveryAmount_r15   = 32;
    padq->gnss_SSR_PeriodicOrbitCorrectionsReq_r15->deliveryInterval_r15 = interval;

    padq->gnss_SSR_PeriodicCodeBiasReq_r15 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq->gnss_SSR_PeriodicCodeBiasReq_r15->deliveryAmount_r15   = 32;
    padq->gnss_SSR_PeriodicCodeBiasReq_r15->deliveryInterval_r15 = interval;

    padq1->gnss_SSR_PeriodicPhaseBiasReq_r16 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq1->gnss_SSR_PeriodicPhaseBiasReq_r16->deliveryAmount_r15   = 32;
    padq1->gnss_SSR_PeriodicPhaseBiasReq_r16->deliveryInterval_r15 = interval;

    padq1->gnss_SSR_PeriodicGriddedCorrectionReq_r16 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq1->gnss_SSR_PeriodicGriddedCorrectionReq_r16->deliveryAmount_r15   = 32;
    padq1->gnss_SSR_PeriodicGriddedCorrectionReq_r16->deliveryInterval_r15 = interval;

    padq1->gnss_SSR_PeriodicSTEC_CorrectionReq_r16 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq1->gnss_SSR_PeriodicSTEC_CorrectionReq_r16->deliveryAmount_r15   = 32;
    padq1->gnss_SSR_PeriodicSTEC_CorrectionReq_r16->deliveryInterval_r15 = interval;

    padq1->gnss_SSR_PeriodicURA_Req_r16 = ALLOC_ZERO(GNSS_PeriodicControlParam_r15);
    padq1->gnss_SSR_PeriodicURA_Req_r16->deliveryAmount_r15   = 32;
    padq1->gnss_SSR_PeriodicURA_Req_r16->deliveryInterval_r15 = interval;

    auto gad1 = ALLOC_ZERO(A_GNSS_RequestAssistanceData::A_GNSS_RequestAssistanceData__ext1);
    gad1->gnss_PeriodicAssistDataReq_r15 = padq;

    auto gad                       = ALLOC_ZERO(A_GNSS_RequestAssistanceData_t);
    gad->ext1                      = gad1;
    gad->gnss_CommonAssistDataReq  = car;
    gad->gnss_GenericAssistDataReq = gar;

    auto rad9                            = &cext->choice.c1.choice.requestAssistanceData_r9;
    rad9->commonIEsRequestAssistanceData = cad;
    rad9->a_gnss_RequestAssistanceData   = gad;

    auto result = lpp_encode(message);
    lpp_destroy(message);
    return result;
}
