#ifndef SPECREL_LIGHTRAYINFO_H
#define SPECREL_LIGHTRAYINFO_H

#include "Ray.h"
#include "Intersection.h"

struct LightRayInfo
{
	LightBasePtr Light;   // The light that is being checked for illumination
	Intersection Origin;  // The intersection that the ray was launched from
	Ray LightRay;         // The ray that goes from the intersection to the light
	Velocity RelVelocity; // The relative velocity between the intersection point and the light
	double Distance;      // The distance to the light from the intersection
	double IntersectTime; // The time at which the ray intersected the light
};

#endif
