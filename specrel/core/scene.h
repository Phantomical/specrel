#ifndef SPECREL_SCENE_
#define SPECREL_SCENE_H

#include "transform.h"
#include "medium.h"
#include <vector>
#include <memory>

//Represents a ray in the global reference frame
//Rays will always be in the global reference frame
class Ray
{
public:
	ReferenceFrame RefFrame; // The reference frame of the ray
	Vector4d Direction;      // The direction of the ray, the t component should always be one
	Vector4d Origin;         // The starting point of the ray
	double SumWeight;        // The contribution of this ray to the colour of the point it is being traced from

	Ray() = default;
	//Creates a ray with direction dir in a specific reference frame
	Ray(const Vector4d& origin, const Vector4d& dir, const ReferenceFrame& ref_frame = ReferenceFrame::Default, double weight = 1.0);
	Ray(const Transform& origin, const Vector4d& dir, double weight = 1.0);
};

class ObjectBase
{
protected:
	Medium InternalMedium;    // The information of the medium inside the object (used for refraction)
	ReferenceFrame RefFrame;  // Reference frame of the object
	bool Transparent;         // Whether the object is transparent or not

public:
	Medium GetInternalMedium() const;
	ReferenceFrame GetRefFrame() const;
	bool IsTransparent() const;

	//Indicates whether a ray intersects an object
	virtual bool Intersects(const Ray&, std::vector<Vector4d>& intersection_points) const = 0;
	//Returns the colour of the object when it is intersected by the ray at intersection
	virtual Colour GetColour(const Ray&, const Vector4d& intersection) const = 0;
	//Returns any rays that would be traced by getting the colour of this point
	virtual void GetChildRays(const Ray&, const Transform& intersection, std::vector<Ray>& child_rays) const = 0;

	virtual ~ObjectBase() = default;
};

class LightBase
{
protected:
	Transform LightTransform;       // The location of the light

public:
	ReferenceFrame GetRefFrame() const;
	Transform GetTransform() const;

	//Indicates whether a ray would be illuminated by this light, and,
	//if it does, returns the colour that the ray would be in light_colour
	virtual bool Illuminates(const Ray&, Colour& light_colour) const = 0;

	virtual ~LightBase() = default;
};

typedef std::shared_ptr<LightBase> LightBasePtr;
typedef std::shared_ptr<ObjectBase> ObjectBasePtr;

struct Contact
{
	Transform Position;   // The point at which the ray collided with the object
	ObjectBasePtr Object; // The object that the ray collided with
};

struct Scene
{
	std::vector<LightBasePtr> Lights;   // All the lights in the scene
	std::vector<ObjectBasePtr> Objects; // All the objects in the scene

	bool DirectlyIlluminatedByLight(LightBasePtr light, const Transform& srcpt) const;
	//Generates all the points where the ray would intersect with an object
	void GetRayContactPoints(const Ray& ray, std::vector<Contact>& contacts) const;
	Contact GetNearestContactPoint(const Ray& ray) const;
};

#endif
