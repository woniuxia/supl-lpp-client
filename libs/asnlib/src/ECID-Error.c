/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LPP-PDU-Definitions"
 * 	found in "/home/martin/repos/LPP-Client/asn/LPP.asn"
 * 	`asn1c -fcompound-names -no-gen-OER -pdu=all -no-gen-example -S /home/martin/repos/LPP-Client/ASN1C/skeletons`
 */

#include "ECID-Error.h"

asn_per_constraints_t asn_PER_type_ECID_Error_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_ECID_Error_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct ECID_Error, choice.locationServerErrorCauses),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ECID_LocationServerErrorCauses,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"locationServerErrorCauses"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct ECID_Error, choice.targetDeviceErrorCauses),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_ECID_TargetDeviceErrorCauses,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"targetDeviceErrorCauses"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_ECID_Error_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* locationServerErrorCauses */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* targetDeviceErrorCauses */
};
asn_CHOICE_specifics_t asn_SPC_ECID_Error_specs_1 = {
	sizeof(struct ECID_Error),
	offsetof(struct ECID_Error, _asn_ctx),
	offsetof(struct ECID_Error, present),
	sizeof(((struct ECID_Error *)0)->present),
	asn_MAP_ECID_Error_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0,
	2	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_ECID_Error = {
	"ECID-Error",
	"ECID-Error",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, &asn_PER_type_ECID_Error_constr_1, CHOICE_constraint },
	asn_MBR_ECID_Error_1,
	2,	/* Elements count */
	&asn_SPC_ECID_Error_specs_1	/* Additional specs */
};
