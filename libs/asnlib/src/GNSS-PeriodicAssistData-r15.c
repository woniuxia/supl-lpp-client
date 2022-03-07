/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LPP-PDU-Definitions"
 * 	found in "/home/martin/repos/LPP-Client/asn/LPP.asn"
 * 	`asn1c -fcompound-names -no-gen-OER -pdu=all -no-gen-example -S /home/martin/repos/LPP-Client/ASN1C/skeletons`
 */

#include "GNSS-PeriodicAssistData-r15.h"

static asn_TYPE_member_t asn_MBR_ext1_11[] = {
	{ ATF_POINTER, 4, offsetof(struct GNSS_PeriodicAssistData_r15__ext1, gnss_SSR_PeriodicURA_r16),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicURA-r16"
		},
	{ ATF_POINTER, 3, offsetof(struct GNSS_PeriodicAssistData_r15__ext1, gnss_SSR_PeriodicPhaseBias_r16),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicPhaseBias-r16"
		},
	{ ATF_POINTER, 2, offsetof(struct GNSS_PeriodicAssistData_r15__ext1, gnss_SSR_PeriodicSTEC_Correction_r16),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicSTEC-Correction-r16"
		},
	{ ATF_POINTER, 1, offsetof(struct GNSS_PeriodicAssistData_r15__ext1, gnss_SSR_PeriodicGriddedCorrection_r16),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicGriddedCorrection-r16"
		},
};
static const int asn_MAP_ext1_oms_11[] = { 0, 1, 2, 3 };
static const ber_tlv_tag_t asn_DEF_ext1_tags_11[] = {
	(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ext1_tag2el_11[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* gnss-SSR-PeriodicURA-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* gnss-SSR-PeriodicPhaseBias-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* gnss-SSR-PeriodicSTEC-Correction-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 } /* gnss-SSR-PeriodicGriddedCorrection-r16 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ext1_specs_11 = {
	sizeof(struct GNSS_PeriodicAssistData_r15__ext1),
	offsetof(struct GNSS_PeriodicAssistData_r15__ext1, _asn_ctx),
	asn_MAP_ext1_tag2el_11,
	4,	/* Count of tags in the map */
	asn_MAP_ext1_oms_11,	/* Optional members */
	4, 0,	/* Root/Additions */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ext1_11 = {
	"ext1",
	"ext1",
	&asn_OP_SEQUENCE,
	asn_DEF_ext1_tags_11,
	sizeof(asn_DEF_ext1_tags_11)
		/sizeof(asn_DEF_ext1_tags_11[0]) - 1, /* 1 */
	asn_DEF_ext1_tags_11,	/* Same as above */
	sizeof(asn_DEF_ext1_tags_11)
		/sizeof(asn_DEF_ext1_tags_11[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ext1_11,
	4,	/* Elements count */
	&asn_SPC_ext1_specs_11	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_GNSS_PeriodicAssistData_r15_1[] = {
	{ ATF_POINTER, 9, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_RTK_PeriodicObservations_r15),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-RTK-PeriodicObservations-r15"
		},
	{ ATF_POINTER, 8, offsetof(struct GNSS_PeriodicAssistData_r15, glo_RTK_PeriodicBiasInformation_r15),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"glo-RTK-PeriodicBiasInformation-r15"
		},
	{ ATF_POINTER, 7, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_RTK_MAC_PeriodicCorrectionDifferences_r15),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-RTK-MAC-PeriodicCorrectionDifferences-r15"
		},
	{ ATF_POINTER, 6, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_RTK_PeriodicResiduals_r15),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-RTK-PeriodicResiduals-r15"
		},
	{ ATF_POINTER, 5, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_RTK_FKP_PeriodicGradients_r15),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-RTK-FKP-PeriodicGradients-r15"
		},
	{ ATF_POINTER, 4, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_SSR_PeriodicOrbitCorrections_r15),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicOrbitCorrections-r15"
		},
	{ ATF_POINTER, 3, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_SSR_PeriodicClockCorrections_r15),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicClockCorrections-r15"
		},
	{ ATF_POINTER, 2, offsetof(struct GNSS_PeriodicAssistData_r15, gnss_SSR_PeriodicCodeBias_r15),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_GNSS_PeriodicControlParam_r15,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"gnss-SSR-PeriodicCodeBias-r15"
		},
	{ ATF_POINTER, 1, offsetof(struct GNSS_PeriodicAssistData_r15, ext1),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		0,
		&asn_DEF_ext1_11,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ext1"
		},
};
static const int asn_MAP_GNSS_PeriodicAssistData_r15_oms_1[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
static const ber_tlv_tag_t asn_DEF_GNSS_PeriodicAssistData_r15_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_GNSS_PeriodicAssistData_r15_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* gnss-RTK-PeriodicObservations-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* glo-RTK-PeriodicBiasInformation-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* gnss-RTK-MAC-PeriodicCorrectionDifferences-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* gnss-RTK-PeriodicResiduals-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* gnss-RTK-FKP-PeriodicGradients-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* gnss-SSR-PeriodicOrbitCorrections-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* gnss-SSR-PeriodicClockCorrections-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* gnss-SSR-PeriodicCodeBias-r15 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 } /* ext1 */
};
asn_SEQUENCE_specifics_t asn_SPC_GNSS_PeriodicAssistData_r15_specs_1 = {
	sizeof(struct GNSS_PeriodicAssistData_r15),
	offsetof(struct GNSS_PeriodicAssistData_r15, _asn_ctx),
	asn_MAP_GNSS_PeriodicAssistData_r15_tag2el_1,
	9,	/* Count of tags in the map */
	asn_MAP_GNSS_PeriodicAssistData_r15_oms_1,	/* Optional members */
	8, 1,	/* Root/Additions */
	8,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_GNSS_PeriodicAssistData_r15 = {
	"GNSS-PeriodicAssistData-r15",
	"GNSS-PeriodicAssistData-r15",
	&asn_OP_SEQUENCE,
	asn_DEF_GNSS_PeriodicAssistData_r15_tags_1,
	sizeof(asn_DEF_GNSS_PeriodicAssistData_r15_tags_1)
		/sizeof(asn_DEF_GNSS_PeriodicAssistData_r15_tags_1[0]), /* 1 */
	asn_DEF_GNSS_PeriodicAssistData_r15_tags_1,	/* Same as above */
	sizeof(asn_DEF_GNSS_PeriodicAssistData_r15_tags_1)
		/sizeof(asn_DEF_GNSS_PeriodicAssistData_r15_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_GNSS_PeriodicAssistData_r15_1,
	9,	/* Elements count */
	&asn_SPC_GNSS_PeriodicAssistData_r15_specs_1	/* Additional specs */
};
