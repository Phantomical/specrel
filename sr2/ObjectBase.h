#ifndef SPECREL_OBJECTBASE_H
#define SPECREL_OBJECTBASE_H

#include "Intersection.h"
#include "Ray.h"

class ObjectBase
{
public:
	virtual Position GetPosition(double time) const = 0;
	virtual ReferenceFrame GetReferenceFrame(double time) const = 0;
	//Returns all intersections with the object
	virtual IntersectionList Intersect(const Ray& ray) const = 0;

	virtual ~ObjectBase() = default;
};

#endif
