#include "Sphere.h"

IntersectionList Sphere::AllIntersections(const Ray& inray) const
{
	Ray ray = LorentzTransform(inray, RefFrame);

	double b = -(-dot(ray.Direction, subvec<3>(ray.Origin))
		- dot(ray.Direction, subvec<3>(ray.Origin))
		+ dot(subvec<3>(ray.Origin), RefFrame.Velocity)
		+ ray.Origin.t * ray.RefFrame.Velocity.sqrmagnitude()
		- ray.Origin.t * dot(ray.Direction, RefFrame.Velocity)
		- InitialPosition.t * RefFrame.Velocity.sqrmagnitude()
		+ InitialPosition.t * dot(ray.Direction, RefFrame.Velocity)
		+ dot(subvec<3>(InitialPosition), RefFrame.Velocity));
	double a = ray.Direction.sqrmagnitude() - 2 * dot(ray.Direction, RefFrame.Velocity)
		+ RefFrame.Velocity.sqrmagnitude();
	double c = subvec<3>(ray.Origin).sqrmagnitude() - Radius * Radius
		+ subvec<3>(InitialPosition).sqrmagnitude()
		+ subvec<3>(InitialPosition).sqrmagnitude() * RefFrame.Velocity.sqrmagnitude()
		+ 2 * dot(subvec<3>(InitialPosition), subvec<3>(ray.Origin))
		+ 2 * ray.Origin.t * dot(subvec<3>(InitialPosition), RefFrame.Velocity)
		- 2 * InitialPosition.t * dot(subvec<3>(InitialPosition), RefFrame.Velocity);

	double det = b * b - 4 * a * c;

	if (det < 0)
		return IntersectionList();

	double rtdet = std::sqrt(det);

	double inv2a = 0.5 / a;
	double r1 = (-b + rtdet) * inv2a;
	double r2 = (-b - rtdet) * inv2a;

	IntersectionList lst;
	{
		Intersection isect;
		isect.Position = ray.Origin + ray.GetFourVelocity() * r1;
		isect.Normal = subvec<3>(isect.Position) - subvec<3>(InitialPosition);
		isect.SurfaceVel = Vector3d::zero();
		isect.RefFrame = RefFrame;
		isect.Object = ObjectRef(this);
		lst.push_back(isect);
	}
	{
		Intersection isect;
		isect.Position = ray.Origin + ray.GetFourVelocity() * r2;
		isect.Normal = subvec<3>(isect.Position) - subvec<3>(InitialPosition);
		isect.SurfaceVel = Vector3d::zero();
		isect.RefFrame = RefFrame;
		isect.Object = ObjectRef(this);
		lst.push_back(isect);
	}
	return lst;
}
bool Sphere::AnyIntersections(const Ray& inray) const
{
	Ray ray = LorentzTransform(inray, RefFrame);

	double b = -(-dot(ray.Direction, subvec<3>(ray.Origin))
		- dot(ray.Direction, subvec<3>(ray.Origin))
		+ dot(subvec<3>(ray.Origin), RefFrame.Velocity)
		+ ray.Origin.t * ray.RefFrame.Velocity.sqrmagnitude()
		- ray.Origin.t * dot(ray.Direction, RefFrame.Velocity)
		- InitialPosition.t * RefFrame.Velocity.sqrmagnitude()
		+ InitialPosition.t * dot(ray.Direction, RefFrame.Velocity)
		+ dot(subvec<3>(InitialPosition), RefFrame.Velocity));
	double a = ray.Direction.sqrmagnitude() - 2 * dot(ray.Direction, RefFrame.Velocity)
		+ RefFrame.Velocity.sqrmagnitude();
	double c = subvec<3>(ray.Origin).sqrmagnitude() - Radius * Radius
		+ subvec<3>(InitialPosition).sqrmagnitude()
		+ subvec<3>(InitialPosition).sqrmagnitude() * RefFrame.Velocity.sqrmagnitude()
		+ 2 * dot(subvec<3>(InitialPosition), subvec<3>(ray.Origin))
		+ 2 * ray.Origin.t * dot(subvec<3>(InitialPosition), RefFrame.Velocity)
		- 2 * InitialPosition.t * dot(subvec<3>(InitialPosition), RefFrame.Velocity);

	//Determinant
	double det = b * b - 4 * a * c;

	return det >= 0;
}

Sphere::Sphere(const Vector4d& pos, double radius, const ReferenceFrame& ref_frame) :
	RefFrame(ref_frame),
	InitialPosition(pos),
	Radius(radius)
{

}
