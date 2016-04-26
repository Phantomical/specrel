#ifndef SPECREL_INTERSECTION_H
#define SPECREL_INTERSECTION_H

#include "RefFrame.h"
#include <vector>

struct Intersection
{
	ReferenceFrame RefFrame;  // The reference frame of this intersection
	Position Position;        // Position where the ray intersected the object
	Vector3d Normal;          // Surface normal at the intersection point
	Velocity SurfaceVel;      // Velocity of the surface at the intersection point (This does not include the velocity of the object)
	ColourSourcePtr Source;   // Spectrum at the point (Without doppler shift)
	const ObjectBase* Object; // The object that has been intersected
};

typedef std::vector<Intersection> IntersectionList;

#endif