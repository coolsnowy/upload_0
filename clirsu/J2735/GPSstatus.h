/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#ifndef	_GPSstatus_H_
#define	_GPSstatus_H_


#include <asn_application.h>

/* Including external dependencies */
#include <BIT_STRING.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum GPSstatus {
	GPSstatus_unavailable	= 0,
	GPSstatus_isHealthy	= 1,
	GPSstatus_isMonitored	= 2,
	GPSstatus_baseStationType	= 3,
	GPSstatus_aPDOPofUnder5	= 4,
	GPSstatus_inViewOfUnder5	= 5,
	GPSstatus_localCorrectionsPresent	= 6,
	GPSstatus_networkCorrectionsPresent	= 7
} e_GPSstatus;

/* GPSstatus */
typedef BIT_STRING_t	 GPSstatus_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_GPSstatus;
asn_struct_free_f GPSstatus_free;
asn_struct_print_f GPSstatus_print;
asn_constr_check_f GPSstatus_constraint;
ber_type_decoder_f GPSstatus_decode_ber;
der_type_encoder_f GPSstatus_encode_der;
xer_type_decoder_f GPSstatus_decode_xer;
xer_type_encoder_f GPSstatus_encode_xer;

#ifdef __cplusplus
}
#endif

#endif	/* _GPSstatus_H_ */
#include <asn_internal.h>
