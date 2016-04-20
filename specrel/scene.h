#ifndef SPECREL_SCENE_H
#define SPECREL_SCENE_H

#include "LightBase.h"
#include "ObjectBase.h"
#include "Camera.h"

class Scene
{
public:
	std::vector<LightBasePtr> Lights;   // All the lights in the scene
	std::vector<ObjectBasePtr> Objects; // All the objects in the scene
	Camera Viewpoint;                   // The viewpoint that the scene will be traced from

	void GetIntersections(const Ray&, std::vector<Intersection>&) const;
	//Returns true if an intersection was found, false otherwise
	bool NearestIntersection(const Ray&, Intersection&) const;
};

#endif
