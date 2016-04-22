#include "Ray.h"

Ray::Ray(const Vector3d& dir, const Position& origin, const ReferenceFrame& frame) :
	RefFrame(frame),
	Direction(dir),
	Origin(origin)
{

}

Ray TransformRay(const Ray& ray, const ReferenceFrame& new_)
{
	ReferenceFrame relative = ReferenceFrame(ray.RefFrame.Velocity - new_.Velocity);
	double velocity = magnitude(relative.Velocity);
	Vector3d dir = relative.Velocity * (1.0 / velocity);

	Vector3d ndir = normalize(TransformVelocity(ray.Direction, ray.RefFrame, new_));
	Vector3d norg = TransformPosition(ray.Origin, ray.RefFrame, new_);

	return Ray(ndir, norg, new_);
}
