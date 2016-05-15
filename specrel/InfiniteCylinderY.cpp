#include "InfiniteCylinderY.h"

#define V RefFrame.Velocity
#define S InitialPosition
#define O ray.Origin
#define D ray.Direction

IntersectionList InfiniteCylinderY::AllIntersections(const Ray& ray_) const
{
	Ray ray = LorentzTransform(ray_, RefFrame);

	double r1;
	double r2;

	{
		double tmp92 = (D.x*O.x);
		double tmp91 = (-tmp92);
		double tmp90 = (D.z*O.z);
		double tmp89 = (tmp91 - tmp90);
		double tmp88 = (D.x*S.x);
		double tmp87 = (tmp89 + tmp88);
		double tmp86 = (D.z*S.z);
		double tmp85 = (tmp87 + tmp86);
		double tmp33 = (O.t*V.x);
		double tmp84 = (D.x*tmp33);
		double tmp83 = (tmp85 - tmp84);
		double tmp39 = (O.x*V.x);
		double tmp82 = (tmp83 + tmp39);
		double tmp38 = (S.x*V.x);
		double tmp81 = (tmp82 - tmp38);
		double tmp7 = V.x * V.x;
		double tmp36 = (O.t*tmp7);
		double tmp80 = (tmp81 + tmp36);
		double tmp22 = (O.t*V.y);
		double tmp79 = (D.z*tmp22);
		double tmp78 = (tmp80 - tmp79);
		double tmp29 = (O.z*V.y);
		double tmp77 = (tmp78 + tmp29);
		double tmp27 = (S.z*V.y);
		double tmp76 = (tmp77 - tmp27);
		double tmp2 = V.y * V.y;
		double tmp25 = (O.t*tmp2);
		double tmp75 = (tmp76 + tmp25);
		double tmp74 = O.x * O.x;
		double tmp73 = O.z*O.z;
		double tmp72 = (tmp74 + tmp73);
		double tmp71 = Radius * Radius;
		double tmp70 = (tmp72 - tmp71);
		double tmp69 = (O.x*S.x);
		double tmp68 = (2 * tmp69);
		double tmp67 = (tmp70 - tmp68);
		double tmp66 = S.x*S.x;
		double tmp65 = (tmp67 + tmp66);
		double tmp64 = (O.z*S.z);
		double tmp63 = (2 * tmp64);
		double tmp62 = (tmp65 - tmp63);
		double tmp61 = S.z*S.z;
		double tmp60 = (tmp62 + tmp61);
		double tmp59 = (O.t*tmp39);
		double tmp58 = (2 * tmp59);
		double tmp57 = (tmp60 + tmp58);
		double tmp56 = (O.t*tmp38);
		double tmp55 = (2 * tmp56);
		double tmp54 = (tmp57 - tmp55);
		double tmp45 = O.t*O.t;
		double tmp53 = (tmp45*tmp7);
		double tmp52 = (tmp54 + tmp53);
		double tmp51 = (O.t*tmp29);
		double tmp50 = (2 * tmp51);
		double tmp49 = (tmp52 + tmp50);
		double tmp48 = (O.t*tmp27);
		double tmp47 = (2 * tmp48);
		double tmp46 = (tmp49 - tmp47);
		double tmp44 = (tmp45*tmp2);
		double tmp43 = (tmp46 + tmp44);
		double tmp13 = D.x*D.x;
		double tmp12 = D.z*D.z;
		double tmp11 = (tmp13 + tmp12);
		double tmp10 = (D.x*V.x);
		double tmp9 = (2 * tmp10);
		double tmp8 = (tmp11 - tmp9);
		double tmp6 = (tmp8 + tmp7);
		double tmp5 = (D.z*V.y);
		double tmp4 = (2 * tmp5);
		double tmp3 = (tmp6 - tmp4);
		double tmp1 = (tmp3 + tmp2);
		double tmp42 = (tmp1*tmp43);
		double tmp41 = (4 * tmp42);
		double tmp40 = (-tmp41);
		double tmp37 = (tmp39 - tmp38);
		double tmp35 = (tmp37 + tmp36);
		double tmp34 = (O.x - S.x);
		double tmp32 = (tmp34 + tmp33);
		double tmp31 = (D.x*tmp32);
		double tmp30 = (tmp35 - tmp31);
		double tmp28 = (tmp30 + tmp29);
		double tmp26 = (tmp28 - tmp27);
		double tmp24 = (tmp26 + tmp25);
		double tmp23 = (O.z - S.z);
		double tmp21 = (tmp23 + tmp22);
		double tmp20 = (D.z*tmp21);
		double tmp19 = (tmp24 - tmp20);
		double tmp18 = tmp19*tmp19;
		double tmp17 = (4 * tmp18);
		double tmp16 = (tmp40 + tmp17);

		if (tmp16 < 0)
			return IntersectionList();

		double tmp15 = sqrt(tmp16);
		double tmp14 = (tmp15 / 2.);
		r1 = ((tmp75 - tmp14) / tmp1);
		r2 = ((tmp75 + tmp14) / tmp1);
	}

	IntersectionList lst;

	Intersection isect;
	isect.Colour = Colour;
	isect.IncomingDir = ray.Direction;
	isect.RefFrame = RefFrame;
	isect.SurfaceVel = Vector3d::zero();
	isect.Object = ObjectRef(this);

	{
		Vector4d position = ray.GetFourVelocity() * r1;
		Vector2d nrm = position.xz() - (InitialPosition.xz() + RefFrame.Velocity.xz() * (position.t - InitialPosition.t));

		isect.Position = position;
		isect.Normal = Vector3d(nrm.x, 0.0, nrm.y);

		lst.push_back(isect);
	}

	{
		Vector4d position = ray.GetFourVelocity() * r2;
		Vector2d nrm = position.xz() - (InitialPosition.xz() + RefFrame.Velocity.xz() * (position.t - InitialPosition.t));

		isect.Position = position;
		isect.Normal = Vector3d(nrm.x, 0.0, nrm.y);

		lst.push_back(isect);
	}

	return lst;
}
bool InfiniteCylinderY::AnyIntersections(const Ray& ray_) const
{
	Ray ray = LorentzTransform(ray_, RefFrame);

	double tmp33 = (O.t*V.x);
	double tmp39 = (O.x*V.x);
	double tmp38 = (S.x*V.x);
	double tmp7 = V.x * V.x;
	double tmp36 = (O.t*tmp7);
	double tmp22 = (O.t*V.y);
	double tmp29 = (O.z*V.y);
	double tmp27 = (S.z*V.y);
	double tmp2 = V.y * V.y;
	double tmp25 = (O.t*tmp2);
	double tmp74 = O.x * O.x;
	double tmp73 = O.z*O.z;
	double tmp72 = (tmp74 + tmp73);
	double tmp71 = Radius * Radius;
	double tmp70 = (tmp72 - tmp71);
	double tmp69 = (O.x*S.x);
	double tmp68 = (2 * tmp69);
	double tmp67 = (tmp70 - tmp68);
	double tmp66 = S.x*S.x;
	double tmp65 = (tmp67 + tmp66);
	double tmp64 = (O.z*S.z);
	double tmp63 = (2 * tmp64);
	double tmp62 = (tmp65 - tmp63);
	double tmp61 = S.z*S.z;
	double tmp60 = (tmp62 + tmp61);
	double tmp59 = (O.t*tmp39);
	double tmp58 = (2 * tmp59);
	double tmp57 = (tmp60 + tmp58);
	double tmp56 = (O.t*tmp38);
	double tmp55 = (2 * tmp56);
	double tmp54 = (tmp57 - tmp55);
	double tmp45 = O.t*O.t;
	double tmp53 = (tmp45*tmp7);
	double tmp52 = (tmp54 + tmp53);
	double tmp51 = (O.t*tmp29);
	double tmp50 = (2 * tmp51);
	double tmp49 = (tmp52 + tmp50);
	double tmp48 = (O.t*tmp27);
	double tmp47 = (2 * tmp48);
	double tmp46 = (tmp49 - tmp47);
	double tmp44 = (tmp45*tmp2);
	double tmp43 = (tmp46 + tmp44);
	double tmp13 = D.x*D.x;
	double tmp12 = D.z*D.z;
	double tmp11 = (tmp13 + tmp12);
	double tmp10 = (D.x*V.x);
	double tmp9 = (2 * tmp10);
	double tmp8 = (tmp11 - tmp9);
	double tmp6 = (tmp8 + tmp7);
	double tmp5 = (D.z*V.y);
	double tmp4 = (2 * tmp5);
	double tmp3 = (tmp6 - tmp4);
	double tmp1 = (tmp3 + tmp2);
	double tmp42 = (tmp1*tmp43);
	double tmp41 = (4 * tmp42);
	double tmp40 = (-tmp41);
	double tmp37 = (tmp39 - tmp38);
	double tmp35 = (tmp37 + tmp36);
	double tmp34 = (O.x - S.x);
	double tmp32 = (tmp34 + tmp33);
	double tmp31 = (D.x*tmp32);
	double tmp30 = (tmp35 - tmp31);
	double tmp28 = (tmp30 + tmp29);
	double tmp26 = (tmp28 - tmp27);
	double tmp24 = (tmp26 + tmp25);
	double tmp23 = (O.z - S.z);
	double tmp21 = (tmp23 + tmp22);
	double tmp20 = (D.z*tmp21);
	double tmp19 = (tmp24 - tmp20);
	double tmp18 = tmp19*tmp19;
	double tmp17 = (4 * tmp18);
	double tmp16 = (tmp40 + tmp17);

	return tmp16 < 0;
}
