/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#include "FullPositionVector.h"

static asn_TYPE_member_t asn_MBR_FullPositionVector_1[] = {
	{ ATF_POINTER, 1, offsetof(struct FullPositionVector, utcTime),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_DDateTime,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"utcTime"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FullPositionVector, Long),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Longitude,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"long"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct FullPositionVector, lat),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Latitude,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"lat"
		},
	{ ATF_POINTER, 7, offsetof(struct FullPositionVector, elevation),
		(ASN_TAG_CLASS_CONTEXT | (3 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Elevation,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"elevation"
		},
	{ ATF_POINTER, 6, offsetof(struct FullPositionVector, heading),
		(ASN_TAG_CLASS_CONTEXT | (4 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_Heading,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"heading"
		},
	{ ATF_POINTER, 5, offsetof(struct FullPositionVector, speed),
		(ASN_TAG_CLASS_CONTEXT | (5 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TransmissionAndSpeed,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"speed"
		},
	{ ATF_POINTER, 4, offsetof(struct FullPositionVector, posAccuracy),
		(ASN_TAG_CLASS_CONTEXT | (6 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionalAccuracy,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"posAccuracy"
		},
	{ ATF_POINTER, 3, offsetof(struct FullPositionVector, timeConfidence),
		(ASN_TAG_CLASS_CONTEXT | (7 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_TimeConfidence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"timeConfidence"
		},
	{ ATF_POINTER, 2, offsetof(struct FullPositionVector, posConfidence),
		(ASN_TAG_CLASS_CONTEXT | (8 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_PositionConfidenceSet,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"posConfidence"
		},
	{ ATF_POINTER, 1, offsetof(struct FullPositionVector, speedConfidence),
		(ASN_TAG_CLASS_CONTEXT | (9 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SpeedandHeadingandThrottleConfidence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"speedConfidence"
		},
};
static ber_tlv_tag_t asn_DEF_FullPositionVector_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_FullPositionVector_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* utcTime at 1049 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* long at 1050 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 }, /* lat at 1051 */
    { (ASN_TAG_CLASS_CONTEXT | (3 << 2)), 3, 0, 0 }, /* elevation at 1052 */
    { (ASN_TAG_CLASS_CONTEXT | (4 << 2)), 4, 0, 0 }, /* heading at 1053 */
    { (ASN_TAG_CLASS_CONTEXT | (5 << 2)), 5, 0, 0 }, /* speed at 1054 */
    { (ASN_TAG_CLASS_CONTEXT | (6 << 2)), 6, 0, 0 }, /* posAccuracy at 1055 */
    { (ASN_TAG_CLASS_CONTEXT | (7 << 2)), 7, 0, 0 }, /* timeConfidence at 1056 */
    { (ASN_TAG_CLASS_CONTEXT | (8 << 2)), 8, 0, 0 }, /* posConfidence at 1057 */
    { (ASN_TAG_CLASS_CONTEXT | (9 << 2)), 9, 0, 0 } /* speedConfidence at 1058 */
};
static asn_SEQUENCE_specifics_t asn_SPC_FullPositionVector_specs_1 = {
	sizeof(struct FullPositionVector),
	offsetof(struct FullPositionVector, _asn_ctx),
	asn_MAP_FullPositionVector_tag2el_1,
	10,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	9,	/* Start extensions */
	11	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_FullPositionVector = {
	"FullPositionVector",
	"FullPositionVector",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_FullPositionVector_tags_1,
	sizeof(asn_DEF_FullPositionVector_tags_1)
		/sizeof(asn_DEF_FullPositionVector_tags_1[0]), /* 1 */
	asn_DEF_FullPositionVector_tags_1,	/* Same as above */
	sizeof(asn_DEF_FullPositionVector_tags_1)
		/sizeof(asn_DEF_FullPositionVector_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_FullPositionVector_1,
	10,	/* Elements count */
	&asn_SPC_FullPositionVector_specs_1	/* Additional specs */
};

