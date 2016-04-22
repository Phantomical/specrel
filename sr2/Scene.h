#ifndef SPECREL_SCENE_
#define SPECREL_SCENE_H

#include <vector>
#include "LightBase.h"
#include "ObjectBase.h"
#include "Camera.h"

struct Scene
{
	std::vector<LightBasePtr> Lights;
	std::vector<ObjectBasePtr> Objects;
	Camera Viewpoint;


	IntersectionList GlobalIntersect(const Ray& ray) const;
	Intersection NearestIntersection(const Ray& ray) const;
};

#endif
