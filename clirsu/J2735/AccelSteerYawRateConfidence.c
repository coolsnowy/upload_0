/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#include "AccelSteerYawRateConfidence.h"

static asn_TYPE_member_t asn_MBR_AccelSteerYawRateConfidence_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct AccelSteerYawRateConfidence, yawRate),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_YawRateConfidence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"yawRate"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AccelSteerYawRateConfidence, acceleration),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_AccelerationConfidence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"acceleration"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct AccelSteerYawRateConfidence, steeringWheelAngle),
		(ASN_TAG_CLASS_CONTEXT | (2 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_SteeringWheelAngleConfidence,
		0,	/* Defer constraints checking to the member type */
		0,	/* PER is not compiled, use -gen-PER */
		0,
		"steeringWheelAngle"
		},
};
static ber_tlv_tag_t asn_DEF_AccelSteerYawRateConfidence_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static asn_TYPE_tag2member_t asn_MAP_AccelSteerYawRateConfidence_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* yawRate at 536 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 }, /* acceleration at 538 */
    { (ASN_TAG_CLASS_CONTEXT | (2 << 2)), 2, 0, 0 } /* steeringWheelAngle at 542 */
};
static asn_SEQUENCE_specifics_t asn_SPC_AccelSteerYawRateConfidence_specs_1 = {
	sizeof(struct AccelSteerYawRateConfidence),
	offsetof(struct AccelSteerYawRateConfidence, _asn_ctx),
	asn_MAP_AccelSteerYawRateConfidence_tag2el_1,
	3,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* Start extensions */
	-1	/* Stop extensions */
};
asn_TYPE_descriptor_t asn_DEF_AccelSteerYawRateConfidence = {
	"AccelSteerYawRateConfidence",
	"AccelSteerYawRateConfidence",
	SEQUENCE_free,
	SEQUENCE_print,
	SEQUENCE_constraint,
	SEQUENCE_decode_ber,
	SEQUENCE_encode_der,
	SEQUENCE_decode_xer,
	SEQUENCE_encode_xer,
	0, 0,	/* No PER support, use "-gen-PER" to enable */
	0,	/* Use generic outmost tag fetcher */
	asn_DEF_AccelSteerYawRateConfidence_tags_1,
	sizeof(asn_DEF_AccelSteerYawRateConfidence_tags_1)
		/sizeof(asn_DEF_AccelSteerYawRateConfidence_tags_1[0]), /* 1 */
	asn_DEF_AccelSteerYawRateConfidence_tags_1,	/* Same as above */
	sizeof(asn_DEF_AccelSteerYawRateConfidence_tags_1)
		/sizeof(asn_DEF_AccelSteerYawRateConfidence_tags_1[0]), /* 1 */
	0,	/* No PER visible constraints */
	asn_MBR_AccelSteerYawRateConfidence_1,
	3,	/* Elements count */
	&asn_SPC_AccelSteerYawRateConfidence_specs_1	/* Additional specs */
};

