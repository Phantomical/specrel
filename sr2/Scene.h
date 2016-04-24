#ifndef SPECREL_SCENE_H
#define SPECREL_SCENE_H

#include <vector>
#include "Camera.h"
#include "LightBase.h"
#include "ObjectBase.h"
#include "LightRayInfo.h"

struct Scene
{
	std::vector<LightBasePtr> Lights;
	std::vector<ObjectBasePtr> Objects;

	IntersectionList GlobalIntersect(const Ray& ray) const;
	bool TryNearestIntersection(const Ray& ray, Intersection& isect) const;
	//Only returns true if the light is static and the intersection point is illuminated by it
	//If it returns true then information about the light ray will be placed in info (Which can be NULL)
	bool IlluminatedByStaticLight(const Intersection& isect, const LightBasePtr& light, LightRayInfo* info) const;

	bool IsLightShape(ObjectBasePtr object) const;
};

typedef std::shared_ptr<Scene> ScenePtr;

#endif
