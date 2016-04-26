#ifndef SPECREL_RAY_H
#define SPECREL_RAY_H

#include "RefFrame.h"

struct Ray
{
	ReferenceFrame RefFrame; // The reference frame that hte ray is ins
	Vector3d Direction;      // The direction in space that the ray is going
	Position Origin;         // The point that the ray was launched from
	double TimeDirection;    // The direction in time that the ray is going (This should only ever be 1 or -1)

	Ray() = default;
	Ray(const Vector3d& dir, const Position& origin, const double tdir = 1.0, const ReferenceFrame& frame = ReferenceFrame::Default);
};

Ray TransformRay(const Ray&, const ReferenceFrame& new_);

#endif
