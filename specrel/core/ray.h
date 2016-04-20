#ifndef SPECREL_RAY_H
#define SPECREL_RAY_H

#include "transform.h"

//Represents a ray in the global reference frame
//Rays will always be in the global reference frame
class Ray
{
public:
	ReferenceFrame RefFrame; // The reference frame of the ray
	Vector4d Direction;      // The direction of the ray, the t component should always be one
	Vector4d Origin;         // The starting point of the ray
	double SumWeight;        // The contribution of this ray to the colour of the point it is being traced from

	Ray() = default;
	//Creates a ray with direction dir in a specific reference frame
	Ray(const Vector4d& origin, const Vector4d& dir, const ReferenceFrame& ref_frame = ReferenceFrame::Default, double weight = 1.0);
	Ray(const Transform& origin, const Vector4d& dir, double weight = 1.0);
};

#endif
