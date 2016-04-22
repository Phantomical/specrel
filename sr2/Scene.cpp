#include "Scene.h"
#include "LightRayInfo.h"
#include <limits>

IntersectionList Scene::GlobalIntersect(const Ray& ray) const
{
	IntersectionList lst;
	for (const auto& object : Objects)
	{
		IntersectionList isects = object->Intersect(ray);
		lst.insert(lst.end(), isects.begin(), isects.end());
	}
	return lst;
}
Intersection Scene::NearestIntersection(const Ray& ray) const
{
	IntersectionList lst = GlobalIntersect(ray);
	double dis2 = std::numeric_limits<double>::max();
	Intersection nearest;
	for (const auto& isect : lst)
	{
		Position c = TransformPosition(isect.Position, isect.RefFrame, ray.RefFrame);
		double ndis2 = sqrdistance(c, ray.Origin);
		if (ndis2 < dis2)
		{
			dis2 = ndis2;
			nearest = isect;
		}
	}
	return nearest;
}

bool Scene::IlluminatedByStaticLight(const Intersection& isect, const LightBasePtr& light, LightRayInfo* info) const
{
	//This method doesn't know how to deal with lights that change position
	if (!light->IsStatic())
		return false;

	//A static light must never be moving, therefore we can use the default reference
	//frame and avoid the virtual function call
	ReferenceFrame lightref = ReferenceFrame::Default;
	Vector4d orig = TransformPosition(isect.Position, isect.RefFrame, lightref);
	Vector3d dest = light->GetPositionAtTime(0.0).subvec<3>();
	Vector3d dir = normalize(dest - orig.subvec<3>());

	Ray lightray = Ray(dir, orig, lightref);
	Intersection nearest = NearestIntersection(lightray);
	
	//distance from the light to the origin of the ray
	double dis2light2 = sqrdistance(orig.subvec<3>(), dest);

	Intersection nearest = NearestIntersection(lightray);

	if (sqrdistance(nearest.Position.subvec<3>(), orig.subvec<3>()) < dis2light2)
		return false;

	if (info != nullptr)
	{
		//Because it is a light ray, this is both the time and the distance
		double dis = std::sqrt(dis2light2);
		info->Light = light;
		info->Origin = isect;
		info->LightRay = lightray;
		info->RelVelocity = isect.SurfaceVel
			+ isect.Object->GetReferenceFrame(orig.t - dis).Velocity;
		info->Distance = dis;
	}
	
	return true;
}
