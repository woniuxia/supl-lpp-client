/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LPP-PDU-Definitions"
 * 	found in "/home/martin/repos/LPP-Client/asn/LPP.asn"
 * 	`asn1c -fcompound-names -no-gen-OER -pdu=all -no-gen-example -S /home/martin/repos/LPP-Client/ASN1C/skeletons`
 */

#ifndef	_NeQuickModelParameter_H_
#define	_NeQuickModelParameter_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeInteger.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* NeQuickModelParameter */
typedef struct NeQuickModelParameter {
	long	 ai0;
	long	 ai1;
	long	 ai2;
	long	*ionoStormFlag1	/* OPTIONAL */;
	long	*ionoStormFlag2	/* OPTIONAL */;
	long	*ionoStormFlag3	/* OPTIONAL */;
	long	*ionoStormFlag4	/* OPTIONAL */;
	long	*ionoStormFlag5	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} NeQuickModelParameter_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_NeQuickModelParameter;
extern asn_SEQUENCE_specifics_t asn_SPC_NeQuickModelParameter_specs_1;
extern asn_TYPE_member_t asn_MBR_NeQuickModelParameter_1[8];

#ifdef __cplusplus
}
#endif

#endif	/* _NeQuickModelParameter_H_ */
#include <asn_internal.h>