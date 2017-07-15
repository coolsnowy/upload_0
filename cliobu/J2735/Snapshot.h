/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#ifndef	_Snapshot_H_
#define	_Snapshot_H_


#include <asn_application.h>

/* Including external dependencies */
#include "FullPositionVector.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct VehicleSafetyExtension;
struct VehicleStatus;

/* Snapshot */
typedef struct Snapshot {
	FullPositionVector_t	 thePosition;
	struct VehicleSafetyExtension	*safetyExt	/* OPTIONAL */;
	struct VehicleStatus	*datSet	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Snapshot_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Snapshot;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "VehicleSafetyExtension.h"
#include "VehicleStatus.h"

#endif	/* _Snapshot_H_ */
#include <asn_internal.h>
