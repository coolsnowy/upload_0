/*
 * Generated by asn1c-0.9.23 (http://lionet.info/asn1c)
 * From ASN.1 module "DSRC"
 * 	found in "DSRC_R36_Source.ASN"
 * 	`asn1c -S ../../../../tools/asn1c/skeletons -pdu=BasicSafetyMessage -fcompound-names`
 */

#ifndef	_Intersection_H_
#define	_Intersection_H_


#include <asn_application.h>

/* Including external dependencies */
#include "DescriptiveName.h"
#include "IntersectionID.h"
#include "Heading.h"
#include "LaneWidth.h"
#include "IntersectionStatusObject.h"
#include <asn_SEQUENCE_OF.h>
#include <constr_SEQUENCE_OF.h>
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct Position3D;
struct ApproachObject;
struct SignalControlZone;

/* Intersection */
typedef struct Intersection {
	DescriptiveName_t	*name	/* OPTIONAL */;
	IntersectionID_t	 id;
	struct Position3D	*refPoint	/* OPTIONAL */;
	IntersectionID_t	*refInterNum	/* OPTIONAL */;
	Heading_t	*orientation	/* OPTIONAL */;
	LaneWidth_t	*laneWidth	/* OPTIONAL */;
	IntersectionStatusObject_t	*type	/* OPTIONAL */;
	struct Intersection__approaches {
		A_SEQUENCE_OF(struct ApproachObject) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} approaches;
	struct Intersection__preemptZones {
		A_SEQUENCE_OF(struct SignalControlZone) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *preemptZones;
	struct Intersection__priorityZones {
		A_SEQUENCE_OF(struct SignalControlZone) list;
		
		/* Context for parsing across buffer boundaries */
		asn_struct_ctx_t _asn_ctx;
	} *priorityZones;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} Intersection_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_Intersection;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "Position3D.h"
#include "ApproachObject.h"
#include "SignalControlZone.h"

#endif	/* _Intersection_H_ */
#include <asn_internal.h>
