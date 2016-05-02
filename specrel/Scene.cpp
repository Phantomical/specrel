#include "Scene.h"
#include <cassert>

NoIntersectionException::NoIntersectionException(const Ray& err) :
	ErroredRay(err)
{

}

const Ray& NoIntersectionException::GetRay() const
{
	return ErroredRay;
}

IntersectionList Scene::AllIntersections(const Ray& ray) const
{
	IntersectionList isects;

	// Intersect with every object in the scene
	for (auto obj : Objects)
	{
		IntersectionList obj_isects = obj->AllIntersections(ray);
		// Add all intersections
		isects.insert(isects.end(), obj_isects.begin(), obj_isects.end());
	}

	return isects;
}
Intersection Scene::NearestIntersection(const Ray& ray) const
{
	Intersection isect;
	if (TryNearestIntersection(ray, isect))
		return isect;
	throw NoIntersectionException(ray);
}
bool Scene::TryNearestIntersection(const Ray& ray, Intersection& nearest) const
{
	IntersectionList isects = AllIntersections(ray);

	if (isects.empty())
		return false;

	double dis = std::numeric_limits<double>::max();
	// Will be set if an object in front of the ray origin is found
	bool found1 = false;

	for (const auto& isect : isects)
	{
		// The ray should always intersect before it was 
		// launched because we are raytracing backwards in time
		// (Unless it is behind us)
		double ndis = ray.Origin.t - isect.Position.t;

		if (ndis < ray.MinDistance)
			// The intersection is behind the 
			// minimum distance of the ray
			continue;

		if (ndis < dis)
		{
			nearest = isect;
			found1 = true;
			dis = ndis;
		}
	}

	return found1;
}

void Scene::AddObject(ObjectPtr object)
{
	Objects.push_back(object);
}
