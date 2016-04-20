#include "Scene.h"

void Scene::GetIntersections(const Ray& ray, std::vector<Intersection>& intersections) const
{
	std::vector<Intersection> object_intersections;
	for (const auto& object : Objects)
	{
		Ray ray_in_frame = TransformRay(ray, object->GetRefFrame());
		if (object->Intersect(ray_in_frame, object_intersections))
		{
			intersections.insert(intersections.end(), 
				object_intersections.begin(), 
				object_intersections.end());
		}
		object_intersections.clear();
	}
}

bool Scene::NearestIntersection(const Ray& ray, Intersection& out) const
{
	std::vector<Intersection> intersections;
	GetIntersections(ray, intersections);
	if (intersections.empty())
		return false;

	double nearest2 = std::numeric_limits<double>::max();
	for (const auto& it : intersections)
	{
		Vector4d origin = TransformPosition(ray.Origin, ray.RefFrame, it.RefFrame);
		//Use distance squared to avoid the square root every time
		//and because it preserves the order anyway
		double dis2 = sqrdistance(origin, it.Position);
		if (dis2 < nearest2)
		{
			//The intersection was the closest
			nearest2 = dis2;
			out = it;
		}
	}

	return true;
}
