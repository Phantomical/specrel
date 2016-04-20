#ifndef SPECREL_OBJECTBASE_H
#define SPECREL_OBJECTBASE_H

#include "Medium.h"
#include "Intersection.h"
#include "Ray.h"
#include <vector>
#include <memory>

class ObjectBase
{
protected:
	Medium InternalMedium;   // The information of the medium inside the object (used for refraction)
	ReferenceFrame RefFrame; // Reference frame of the object
	bool Transparent;        // Whether the object is transparent or not

public:
	Medium GetInternalMedium() const;
	ReferenceFrame GetRefFrame() const;
	bool IsTransparent() const;

	//Indicates whether a given ray intersects this object
	virtual bool Intersect(const Ray&, std::vector<Intersection>& intersections) const = 0;

	virtual ~ObjectBase() = default;
};

#endif
