#include "ray.h"

Ray::Ray(const Vector4d& origin, const Vector4d& dir, const ReferenceFrame& ref_frame) :
	Origin(origin),
	Direction(dir),
	RefFrame(ref_frame)
{

}
Ray::Ray(const Transform& origin, const Vector4d& dir) :
	RefFrame(origin.RefFrame),
	Direction(dir),
	Origin(origin.Position)
{

}

Ray TransformRay(const Ray& ray, const ReferenceFrame& new_frame)
{
	Vector4d new_org = TransformPosition(ray.Origin, ray.RefFrame, new_frame);
	Vector4d new_dir = TransformVelocity(ray.Direction, ray.RefFrame, new_frame);
	return Ray(new_org, new_dir, new_frame);
}

