#ifndef SPECREL_INTERSECTION_H
#define SPECREL_INTERSECTION_H

#include "Transform.h"
#include "ColourSource.h"

struct Intersection
{
	ReferenceFrame RefFrame; // The reference frame that the point for the intersection is in
	Vector4d Position;       // The position of the intersection
	Vector3d Normal;         // Normal vector (For reflection and refraction)
	// Velocity of the surface relative to the object
	// This is _NOT_ the velocity of the object 
	Vector3d Velocity;
	Colour SurfaceColour;    // Colour of the surface at the point of intersection (Not including reflected rays or subsurface rays)

};

#endif
