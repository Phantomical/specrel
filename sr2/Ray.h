#ifndef SPECREL_RAY_H
#define SPECREL_RAY_H

#include "RefFrame.h"

struct Ray
{
	ReferenceFrame RefFrame;
	Vector3d Direction;
	Position Origin;

	Ray() = default;
	Ray(const Vector3d& dir, const Position& origin, const ReferenceFrame& frame = ReferenceFrame::Default);
};

Ray TransformRay(const Ray&, const ReferenceFrame& new_);

#endif
