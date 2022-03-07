/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "Ver2-ULP-Components"
 * 	found in "/home/martin/repos/LPP-Client/asn/ULP-Components.asn"
 * 	`asn1c -fcompound-names -no-gen-OER -pdu=all -no-gen-example -S /home/martin/repos/LPP-Client/ASN1C/skeletons`
 */

#ifndef	_HrpdCellInformation_H_
#define	_HrpdCellInformation_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* HrpdCellInformation */
typedef struct HrpdCellInformation {
	BIT_STRING_t	*refSECTORID	/* OPTIONAL */;
	long	 refBASELAT;
	long	 reBASELONG;
	long	 refWeekNumber;
	long	 refSeconds;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} HrpdCellInformation_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_HrpdCellInformation;
extern asn_SEQUENCE_specifics_t asn_SPC_HrpdCellInformation_specs_1;
extern asn_TYPE_member_t asn_MBR_HrpdCellInformation_1[5];

#ifdef __cplusplus
}
#endif

#endif	/* _HrpdCellInformation_H_ */
#include <asn_internal.h>