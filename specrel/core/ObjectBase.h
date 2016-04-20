#ifndef SPECREL_OBJECTBASE_H
#define SPECREL_OBJECTBASE_H

#include "medium.h"
#include "intersection.h"
#include "ray.h"
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

	//Indicates whether a ray intersects an object
	virtual bool Intersects(const Ray&, std::vector<Intersection>& intersections) const = 0;
	//Returns the colour of the object when it is intersected by the ray at intersection
	virtual Colour GetColour(const Ray&, const Intersection& intersection) const = 0;
	//Returns any rays that would be traced by getting the colour of this point
	virtual std::vector<Ray> GetChildRays(const Ray&, const Intersection& intersection) const = 0;

	virtual ~ObjectBase() = default;
};

typedef std::shared_ptr<ObjectBase> ObjectBasePtr;

#endif
