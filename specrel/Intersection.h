#pragma once

#include "PreDefs.h"
#include "ReferenceFrame.h"
#include <vector>

struct Intersection
{
	ReferenceFrame RefFrame; // The reference frame of the intersection
	Vector4d Position;       // The position of the intersection
	Vector3d SurfaceVel;     // The surface velocity of the intersection relative to the reference frame
	Vector3d Normal;         // The surface normal
	ObjectRef Object;        // The object that was intersected
};

typedef std::vector<Intersection> IntersectionList;
