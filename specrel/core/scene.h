#ifndef SPECREL_SCENE_
#define SPECREL_SCENE_H

#include "LightBase.h"
#include "ObjectBase.h"

struct Scene
{
	std::vector<LightBasePtr> Lights;   // All the lights in the scene
	std::vector<ObjectBasePtr> Objects; // All the objects in the scene

	void GetIntersections(const Ray&, std::vector<Intersection>&) const;
	Intersection NearestIntersection(const Ray&) const;
};

#endif
