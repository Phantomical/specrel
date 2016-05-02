#include "Sphere.h"

IntersectionList Sphere::AllIntersections(const Ray& inray) const
{
	Ray ray = LorentzTransform(inray, RefFrame);

#define D ray.Direction
#define O ray.Origin
#define S InitialPosition
#define V RefFrame.Velocity

	double b = -(D.x*O.x) - D.y*O.y - D.z*O.z - D.x*S.x - D.y*S.y - D.z*S.z - D.x*O.t*V.x +
		O.x*V.x + D.x*S.t*V.x + S.x*V.x + O.t*V.x*V.x - S.t*V.x*V.x -
		D.y*O.t*V.y + O.y*V.y + D.y*S.t*V.y + S.y*V.y + O.t*V.y*V.y -
		S.t*V.y*V.y - D.z*O.t*V.z + O.z*V.z + D.z*S.t*V.z + S.z*V.z +
		O.t*V.z*V.z - S.t*V.z*V.z;
	double a = D.x*D.x + D.y*D.y + D.z*D.z - 2 * D.x*V.x +
		V.x*V.x - 2 * D.y*V.y + V.y*V.y - 2 * D.z*V.z + V.z*V.z;
	double c = O.x*O.x + O.y*O.y + O.z*O.z - Radius*Radius +
		S.x*S.x + S.y*S.y + 2 * O.z*S.z + S.z*S.z +
		2 * O.t*S.x*V.x - 2 * S.t*S.x*V.x + O.t*O.t*V.x*V.x -
		2 * O.t*S.t*V.x*V.x + S.t*S.t*V.x*V.x +
		2 * O.x*(S.x + (O.t - S.t)*V.x) + 2 * O.t*S.y*V.y - 2 * S.t*S.y*V.y +
		O.t*O.t*V.y*V.y - 2 * O.t*S.t*V.y*V.y +
		S.t*S.t*V.y*V.y + 2 * O.y*(S.y + O.t*V.y - S.t*V.y) +
		2 * O.t*O.z*V.z - 2 * O.z*S.t*V.z + 2 * O.t*S.z*V.z - 2 * S.t*S.z*V.z +
		O.t*O.t*V.z*V.z - 2 * O.t*S.t*V.z*V.z +
		S.t*S.t*V.z*V.z;

#undef D
#undef O
#undef S
#undef V

	double det = b * b - a * c;

	if (det < 0)
		return IntersectionList();

	double rtdet = std::sqrt(det);

	double inv2a = 1.0 / a;
	double r1 = (b + rtdet) * inv2a;
	double r2 = (b - rtdet) * inv2a;

	IntersectionList lst;
	{
		Intersection isect;
		isect.Position = ray.Origin + ray.GetFourVelocity() * r1;
		isect.Normal = subvec<3>(isect.Position) - subvec<3>(InitialPosition);
		isect.SurfaceVel = Vector3d::zero();
		isect.RefFrame = RefFrame;
		isect.Object = ObjectRef(this);
		isect.Colour = ColourSource;
		lst.push_back(isect);
	}
	{
		Intersection isect;
		isect.Position = ray.Origin + ray.GetFourVelocity() * r2;
		isect.Normal = subvec<3>(isect.Position) - subvec<3>(InitialPosition);
		isect.SurfaceVel = Vector3d::zero();
		isect.RefFrame = RefFrame;
		isect.Object = ObjectRef(this);
		isect.Colour = ColourSource;
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

Sphere::Sphere(const Vector4d& pos, double radius, ColourSourcePtr colour, const ReferenceFrame& ref_frame) :
	RefFrame(ref_frame),
	InitialPosition(pos),
	Radius(radius),
	ColourSource(colour)
{

}
