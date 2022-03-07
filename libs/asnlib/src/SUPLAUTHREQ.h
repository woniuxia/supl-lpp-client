/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "SUPL-AUTH-REQ"
 * 	found in "/home/martin/repos/LPP-Client/asn/SUPL.asn"
 * 	`asn1c -fcompound-names -no-gen-OER -pdu=all -no-gen-example -S /home/martin/repos/LPP-Client/ASN1C/skeletons`
 */

#ifndef	_SUPLAUTHREQ_H_
#define	_SUPLAUTHREQ_H_


#include <asn_application.h>

/* Including external dependencies */
#include "Ver.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct SETCapabilities;

/* SUPLAUTHREQ */
typedef struct SUPLAUTHREQ {
	Ver_t	*ver	/* OPTIONAL */;
	struct SETCapabilities	*sETCapabilities	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} SUPLAUTHREQ_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_SUPLAUTHREQ;
extern asn_SEQUENCE_specifics_t asn_SPC_SUPLAUTHREQ_specs_1;
extern asn_TYPE_member_t asn_MBR_SUPLAUTHREQ_1[2];

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "SETCapabilities.h"

#endif	/* _SUPLAUTHREQ_H_ */
#include <asn_internal.h>