#include "Ray.h"

Vector4d Ray::GetFourVelocity() const
{
	//Rays always are shot backwards in time
	return Vector4d(Direction, -1.0);
}

Ray::Ray(const Vector4d& origin, const Vector3d& dir, const ReferenceFrame& ref_frame, double min_dist) :
	MinDistance(min_dist),
	Direction(dir),
	Origin(origin),
	RefFrame(ref_frame)
{

}

Ray LorentzTransform(const Ray& ray, const ReferenceFrame& new_)
{
	return Ray(
		LorentzTransform(ray.Origin, ray.RefFrame, new_),
		normalize(LorentzTransform(ray.Direction, ray.RefFrame, new_)),
		new_, ray.MinDistance);
}
