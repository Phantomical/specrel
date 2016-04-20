#ifndef SPECREL_SCENE_H
#define SPECREL_SCENE_H

#include "LightBase.h"
#include "ObjectBase.h"

class Scene
{
public:
	std::vector<LightBasePtr> Lights;   // All the lights in the scene
	std::vector<ObjectBasePtr> Objects; // All the objects in the scene

	void GetIntersections(const Ray&, std::vector<Intersection>&) const;
	Intersection NearestIntersection(const Ray&) const;

	virtual Colour GetColour(
		const Intersection& i,
		const ReferenceFrame& frame) = 0;
};

#endif
