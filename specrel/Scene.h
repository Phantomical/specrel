#pragma once

#include "ObjectBase.h"
#include "LightBase.h"

// Exception to only be used by Scene
// It is thrown when an intersection has to be 
// returned but no intersection has occured
class NoIntersectionException : public std::exception
{
private:
	Ray ErroredRay;

	NoIntersectionException(const Ray& erred_ray);

	friend struct Scene;

public:
	const Ray& GetRay() const;
};

struct Scene
{
	std::vector<ObjectPtr> Objects;
	std::vector<LightPtr> Lights;

	// Indicates whether a ray intersects with anything in the scene
	bool AnyIntersections(const Ray& ray) const;
	// Returns all intersections in a vector
	IntersectionList AllIntersections(const Ray& ray) const;
	// Returns the nearest intersection if there is one.
	// If there is no intersection it throws NoIntersectionException
	Intersection NearestIntersection(const Ray& ray) const;
	bool TryNearestIntersection(const Ray& ray, Intersection& isect) const;

	void AddObject(ObjectPtr object);
	void AddLight(LightPtr light);

};

