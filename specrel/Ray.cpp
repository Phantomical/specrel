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

namespace
{
	//Transformrms a direction as if it was a position
	Vector3d TransformDir(const Vector3d& dir, const ReferenceFrame& old, const ReferenceFrame& new_)
	{
		ReferenceFrame change = new_ - old;

		double gamma = change.Gamma();
		Vector3d vdir = normalize(change.Velocity);

		// If there is no change between frames
		// don't do anything
		if (sqrmagnitude(vdir) == 0.0)
			return dir;

		return normalize(change.Velocity + (gamma - 1) * dot(dir, vdir) * vdir);
	}
}

Ray LorentzTransform(const Ray& ray, const ReferenceFrame& new_)
{
	return Ray(
		LorentzTransform(ray.Origin, ray.RefFrame, new_),
		TransformDir(ray.Direction, ray.RefFrame, new_),
		new_, ray.MinDistance);
}
