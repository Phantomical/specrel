#ifndef SPECREL_INTERSECTION_H
#define SPECREL_INTERSECTION_H

#include "Transform.h"
#include "PreDefs.h"

struct Intersection
{
	ReferenceFrame RefFrame;      // The reference frame that the point for the intersection is in
	Vector4d Position;            // The position of the intersection
	Vector3d Normal;              // Normal vector (For reflection and refraction)
	// Velocity of the surface relative to the object
	// This is _NOT_ the velocity of the object 
	Vector3d Velocity;
	double Specularity;           // How reflective the surface is at the intersection
	double Transparancy;          // How transparent the surface is
	ColourSourcePtr ColourSource; // Source for the colour at that point

};

#endif
