#pragma once

#include "Intersection.h"
#include "Ray.h"

class ObjectBase
{
public:
	virtual IntersectionList AllIntersections(const Ray& ray) const = 0;
	virtual bool AnyIntersections(const Ray& ray) const;

	ObjectBase() = default;
};

