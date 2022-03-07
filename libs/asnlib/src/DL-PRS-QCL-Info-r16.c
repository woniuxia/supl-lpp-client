/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "LPP-PDU-Definitions"
 * 	found in "/home/martin/repos/LPP-Client/asn/LPP.asn"
 * 	`asn1c -fcompound-names -no-gen-OER -pdu=all -no-gen-example -S /home/martin/repos/LPP-Client/ASN1C/skeletons`
 */

#include "DL-PRS-QCL-Info-r16.h"

/*
 * This type is implemented using NativeEnumerated,
 * so here we adjust the DEF accordingly.
 */
static int
memb_ssb_Index_r16_constraint_2(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 63)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_per_constraints_t asn_PER_type_rs_Type_r16_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  2 }	/* (0..2) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_per_constraints_t asn_PER_memb_ssb_Index_r16_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 6,  6,  0,  63 }	/* (0..63) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_per_constraints_t asn_PER_type_DL_PRS_QCL_Info_r16_constr_1 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 1,  1,  0,  1 }	/* (0..1) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static const asn_INTEGER_enum_map_t asn_MAP_rs_Type_r16_value2enum_5[] = {
	{ 0,	5,	"typeC" },
	{ 1,	5,	"typeD" },
	{ 2,	16,	"typeC-plus-typeD" }
};
static const unsigned int asn_MAP_rs_Type_r16_enum2value_5[] = {
	0,	/* typeC(0) */
	2,	/* typeC-plus-typeD(2) */
	1	/* typeD(1) */
};
static const asn_INTEGER_specifics_t asn_SPC_rs_Type_r16_specs_5 = {
	asn_MAP_rs_Type_r16_value2enum_5,	/* "tag" => N; sorted by tag */
	asn_MAP_rs_Type_r16_enum2value_5,	/* N => "tag"; sorted by N */
	3,	/* Number of elements in the maps */
	0,	/* Enumeration is not extensible */
	1,	/* Strict enumeration */
	0,	/* Native long size */
	0
};
static const ber_tlv_tag_t asn_DEF_rs_Type_r16_tags_5[] = {
	(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (10 << 2))
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_rs_Type_r16_5 = {
	"rs-Type-r16",
	"rs-Type-r16",
	&asn_OP_NativeEnumerated,
	asn_DEF_rs_Type_r16_tags_5,
	sizeof(asn_DEF_rs_Type_r16_tags_5)
		/sizeof(asn_DEF_rs_Type_r16_tags_5[0]) - 1, /* 1 */
	asn_DEF_rs_Type_r16_tags_5,	/* Same as above */
	sizeof(asn_DEF_rs_Type_r16_tags_5)
		/sizeof(asn_DEF_rs_Type_r16_tags_5[0]), /* 2 */
	{ 0, &asn_PER_type_rs_Type_r16_constr_5, NativeEnumerated_constraint },
	0, 0,	/* Defined elsewhere */
	&asn_SPC_rs_Type_r16_specs_5	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_ssb_r16_2[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16__ssb_r16, pci_r16),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NR_PhysCellId_r16,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"pci-r16"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16__ssb_r16, ssb_Index_r16),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NativeInteger,
		0,
		{ 0, &asn_PER_memb_ssb_Index_r16_constr_4,  memb_ssb_Index_r16_constraint_2 },
		0, 0, /* No default value */
		"ssb-Index-r16"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16__ssb_r16, rs_Type_r16),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_rs_Type_r16_5,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"rs-Type-r16"
		},
};
static const ber_tlv_tag_t asn_DEF_ssb_r16_tags_2[] = {
	(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_ssb_r16_tag2el_2[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* pci-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* ssb-Index-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* rs-Type-r16 */
};
static asn_SEQUENCE_specifics_t asn_SPC_ssb_r16_specs_2 = {
	sizeof(struct DL_PRS_QCL_Info_r16__ssb_r16),
	offsetof(struct DL_PRS_QCL_Info_r16__ssb_r16, _asn_ctx),
	asn_MAP_ssb_r16_tag2el_2,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_ssb_r16_2 = {
	"ssb-r16",
	"ssb-r16",
	&asn_OP_SEQUENCE,
	asn_DEF_ssb_r16_tags_2,
	sizeof(asn_DEF_ssb_r16_tags_2)
		/sizeof(asn_DEF_ssb_r16_tags_2[0]) - 1, /* 1 */
	asn_DEF_ssb_r16_tags_2,	/* Same as above */
	sizeof(asn_DEF_ssb_r16_tags_2)
		/sizeof(asn_DEF_ssb_r16_tags_2[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_ssb_r16_2,
	3,	/* Elements count */
	&asn_SPC_ssb_r16_specs_2	/* Additional specs */
};

static asn_TYPE_member_t asn_MBR_dl_PRS_r16_9[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16__dl_PRS_r16, qcl_dl_PRS_ResourceId_r16),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NR_DL_PRS_ResourceID_r16,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"qcl-dl-PRS-ResourceId-r16"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16__dl_PRS_r16, qcl_dl_PRS_ResourceSetId_r16),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_NR_DL_PRS_ResourceSetID_r16,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"qcl-dl-PRS-ResourceSetId-r16"
		},
};
static const ber_tlv_tag_t asn_DEF_dl_PRS_r16_tags_9[] = {
	(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_dl_PRS_r16_tag2el_9[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* qcl-dl-PRS-ResourceId-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* qcl-dl-PRS-ResourceSetId-r16 */
};
static asn_SEQUENCE_specifics_t asn_SPC_dl_PRS_r16_specs_9 = {
	sizeof(struct DL_PRS_QCL_Info_r16__dl_PRS_r16),
	offsetof(struct DL_PRS_QCL_Info_r16__dl_PRS_r16, _asn_ctx),
	asn_MAP_dl_PRS_r16_tag2el_9,
	2,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
static /* Use -fall-defs-global to expose */
asn_TYPE_descriptor_t asn_DEF_dl_PRS_r16_9 = {
	"dl-PRS-r16",
	"dl-PRS-r16",
	&asn_OP_SEQUENCE,
	asn_DEF_dl_PRS_r16_tags_9,
	sizeof(asn_DEF_dl_PRS_r16_tags_9)
		/sizeof(asn_DEF_dl_PRS_r16_tags_9[0]) - 1, /* 1 */
	asn_DEF_dl_PRS_r16_tags_9,	/* Same as above */
	sizeof(asn_DEF_dl_PRS_r16_tags_9)
		/sizeof(asn_DEF_dl_PRS_r16_tags_9[0]), /* 2 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_dl_PRS_r16_9,
	2,	/* Elements count */
	&asn_SPC_dl_PRS_r16_specs_9	/* Additional specs */
};

asn_TYPE_member_t asn_MBR_DL_PRS_QCL_Info_r16_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16, choice.ssb_r16),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		0,
		&asn_DEF_ssb_r16_2,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"ssb-r16"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct DL_PRS_QCL_Info_r16, choice.dl_PRS_r16),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		0,
		&asn_DEF_dl_PRS_r16_9,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"dl-PRS-r16"
		},
};
static const asn_TYPE_tag2member_t asn_MAP_DL_PRS_QCL_Info_r16_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* ssb-r16 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* dl-PRS-r16 */
};
asn_CHOICE_specifics_t asn_SPC_DL_PRS_QCL_Info_r16_specs_1 = {
	sizeof(struct DL_PRS_QCL_Info_r16),
	offsetof(struct DL_PRS_QCL_Info_r16, _asn_ctx),
	offsetof(struct DL_PRS_QCL_Info_r16, present),
	sizeof(((struct DL_PRS_QCL_Info_r16 *)0)->present),
	asn_MAP_DL_PRS_QCL_Info_r16_tag2el_1,
	2,	/* Count of tags in the map */
	0, 0,
	-1	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_DL_PRS_QCL_Info_r16 = {
	"DL-PRS-QCL-Info-r16",
	"DL-PRS-QCL-Info-r16",
	&asn_OP_CHOICE,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	{ 0, &asn_PER_type_DL_PRS_QCL_Info_r16_constr_1, CHOICE_constraint },
	asn_MBR_DL_PRS_QCL_Info_r16_1,
	2,	/* Elements count */
	&asn_SPC_DL_PRS_QCL_Info_r16_specs_1	/* Additional specs */
};
