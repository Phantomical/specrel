#include "Ray.h"
#include <limits>

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
	constexpr double PI = 3.1415926535897932385;
	inline bool approx(double v, double cmp)
	{
		return v > cmp - std::numeric_limits<double>::epsilon()
			&& v < cmp + std::numeric_limits<double>::epsilon();
	}

	Vector3d TransformDir(const Vector3d& dir, const ReferenceFrame& old, const ReferenceFrame& new_)
	{
		ReferenceFrame change = new_ - old;

		Vector3d vdir = normalize(change.Velocity);
		double vel = magnitude(change.Velocity);
		double cosalpha = cosangle(vdir, dir);

		if (cosalpha == 1.0  || vel==0.0)
			return dir;

		double beta = std::acos((cosalpha - vel) / (1 - vel * cosalpha));

		return rotate(vdir, normalize(cross(dir, vdir)), beta);
	}
}

Ray LorentzTransform(const Ray& ray, const ReferenceFrame& new_)
{
	return Ray(
		ray.Origin,//LorentzTransform(ray.Origin, ray.RefFrame, new_),
		TransformDir(ray.Direction, ray.RefFrame, new_),
		new_, ray.MinDistance);
}
