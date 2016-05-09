#include "Sphere.h"

/*
(D|O|S|V)(x|y|z|t)
$1.$2

Power\((...), 2\)
$1*$1
*/

IntersectionList Sphere::AllIntersections(const Ray& inray) const
{
	Ray ray = LorentzTransform(inray, RefFrame);

#define D ray.Direction
#define O ray.Origin
#define S InitialPosition
#define V RefFrame.Velocity

	double r1, r2;

	{
		double tmp181 = (D.x*O.x);
		double tmp180 = (-tmp181);
		double tmp179 = (D.y*O.y);
		double tmp149 = (D.z*O.z);
		double tmp176 = (D.x*S.x);
		double tmp174 = (D.y*S.y);
		double tmp148 = (D.z*S.z);
		double tmp139 = (O.t*V.x);
		double tmp171 = (D.x*tmp139);
		double tmp146 = (O.x*V.x);
		double tmp137 = (S.t*V.x);
		double tmp168 = (D.x*tmp137);
		double tmp91 = (S.x*V.x);
		double tmp12 = V.x*V.x;
		double tmp143 = (O.t*tmp12);
		double tmp85 = (S.t*tmp12);
		double tmp57 = (O.t*V.y);
		double tmp163 = (D.y*tmp57);
		double tmp133 = (O.y*V.y);
		double tmp55 = (S.t*V.y);
		double tmp160 = (D.y*tmp55);
		double tmp69 = (S.y*V.y);
		double tmp7 = V.y*V.y;
		double tmp130 = (O.t*tmp7);
		double tmp63 = (S.t*tmp7);
		double tmp122 = (O.t*V.z);
		double tmp121 = (D.z*tmp122);
		double tmp50 = (O.z*V.z);
		double tmp46 = (S.t*V.z);
		double tmp118 = (D.z*tmp46);
		double tmp39 = (S.z*V.z);
		double tmp2 = V.z*V.z;
		double tmp115 = (O.t*tmp2);
		double tmp32 = (S.t*tmp2);
		double tmp147 = (tmp149 - tmp148);
		double tmp145 = (tmp147 - tmp146);
		double tmp144 = (tmp145 + tmp91);
		double tmp142 = (tmp144 - tmp143);
		double tmp141 = (tmp142 + tmp85);
		double tmp140 = (O.x - S.x);
		double tmp138 = (tmp140 + tmp139);
		double tmp136 = (tmp138 - tmp137);
		double tmp135 = (D.x*tmp136);
		double tmp134 = (tmp141 + tmp135);
		double tmp132 = (tmp134 - tmp133);
		double tmp131 = (tmp132 + tmp69);
		double tmp129 = (tmp131 - tmp130);
		double tmp128 = (tmp129 + tmp63);
		double tmp127 = (O.y - S.y);
		double tmp126 = (tmp127 + tmp57);
		double tmp125 = (tmp126 - tmp55);
		double tmp124 = (D.y*tmp125);
		double tmp123 = (tmp128 + tmp124);
		double tmp120 = (tmp123 + tmp121);
		double tmp119 = (tmp120 - tmp50);
		double tmp117 = (tmp119 - tmp118);
		double tmp116 = (tmp117 + tmp39);
		double tmp114 = (tmp116 - tmp115);
		double tmp113 = (tmp114 + tmp32);
		double tmp112 = tmp113*tmp113;
		double tmp111 = (4 * tmp112);
		double tmp110 = O.x*O.x;
		double tmp109 = O.y*O.y;
		double tmp108 = (tmp110 + tmp109);
		double tmp107 = O.z*O.z;
		double tmp106 = (tmp108 + tmp107);
		double tmp105 = Radius * Radius;
		double tmp104 = (tmp106 - tmp105);
		double tmp103 = S.x*S.x;
		double tmp102 = (tmp104 + tmp103);
		double tmp101 = S.y*S.y;
		double tmp100 = (tmp102 + tmp101);
		double tmp99 = (O.z*S.z);
		double tmp98 = (2 * tmp99);
		double tmp97 = (tmp100 - tmp98);
		double tmp96 = S.z*S.z;
		double tmp95 = (tmp97 + tmp96);
		double tmp94 = (O.t*tmp91);
		double tmp93 = (2 * tmp94);
		double tmp92 = (tmp95 - tmp93);
		double tmp90 = (S.t*tmp91);
		double tmp89 = (2 * tmp90);
		double tmp88 = (tmp92 + tmp89);
		double tmp35 = O.t*O.t;
		double tmp87 = (tmp35*tmp12);
		double tmp86 = (tmp88 + tmp87);
		double tmp84 = (O.t*tmp85);
		double tmp83 = (2 * tmp84);
		double tmp82 = (tmp86 - tmp83);
		double tmp28 = S.t*S.t;
		double tmp81 = (tmp28*tmp12);
		double tmp80 = (tmp82 + tmp81);
		double tmp79 = (-O.t);
		double tmp78 = (tmp79 + S.t);
		double tmp77 = (tmp78*V.x);
		double tmp76 = (S.x + tmp77);
		double tmp75 = (O.x*tmp76);
		double tmp74 = (2 * tmp75);
		double tmp73 = (tmp80 - tmp74);
		double tmp72 = (O.t*tmp69);
		double tmp71 = (2 * tmp72);
		double tmp70 = (tmp73 - tmp71);
		double tmp68 = (S.t*tmp69);
		double tmp67 = (2 * tmp68);
		double tmp66 = (tmp70 + tmp67);
		double tmp65 = (tmp35*tmp7);
		double tmp64 = (tmp66 + tmp65);
		double tmp62 = (O.t*tmp63);
		double tmp61 = (2 * tmp62);
		double tmp60 = (tmp64 - tmp61);
		double tmp59 = (tmp28*tmp7);
		double tmp58 = (tmp60 + tmp59);
		double tmp56 = (S.y - tmp57);
		double tmp54 = (tmp56 + tmp55);
		double tmp53 = (O.y*tmp54);
		double tmp52 = (2 * tmp53);
		double tmp51 = (tmp58 - tmp52);
		double tmp49 = (O.t*tmp50);
		double tmp48 = (2 * tmp49);
		double tmp47 = (tmp51 + tmp48);
		double tmp45 = (O.z*tmp46);
		double tmp44 = (2 * tmp45);
		double tmp43 = (tmp47 - tmp44);
		double tmp42 = (O.t*tmp39);
		double tmp41 = (2 * tmp42);
		double tmp40 = (tmp43 - tmp41);
		double tmp38 = (S.t*tmp39);
		double tmp37 = (2 * tmp38);
		double tmp36 = (tmp40 + tmp37);
		double tmp34 = (tmp35*tmp2);
		double tmp33 = (tmp36 + tmp34);
		double tmp31 = (O.t*tmp32);
		double tmp30 = (2 * tmp31);
		double tmp29 = (tmp33 - tmp30);
		double tmp27 = (tmp28*tmp2);
		double tmp26 = (tmp29 + tmp27);
		double tmp20 = D.x*D.x;
		double tmp19 = D.y*D.y;
		double tmp18 = (tmp20 + tmp19);
		double tmp17 = D.z*D.z;
		double tmp16 = (tmp18 + tmp17);
		double tmp15 = (D.x*V.x);
		double tmp14 = (2 * tmp15);
		double tmp13 = (tmp16 - tmp14);
		double tmp11 = (tmp13 + tmp12);
		double tmp10 = (D.y*V.y);
		double tmp9 = (2 * tmp10);
		double tmp8 = (tmp11 - tmp9);
		double tmp6 = (tmp8 + tmp7);
		double tmp5 = (D.z*V.z);
		double tmp4 = (2 * tmp5);
		double tmp3 = (tmp6 - tmp4);
		double tmp1 = (tmp3 + tmp2);
		double tmp25 = (tmp1*tmp26);
		double tmp24 = (4 * tmp25);
		double tmp23 = (tmp111 - tmp24);

		if (tmp23 < 0.0)
			//Determinant is less than 0 (No solutions)
			return IntersectionList();

		double tmp22 = sqrt(tmp23);
		double tmp178 = (tmp180 - tmp179);
		double tmp177 = (tmp178 - tmp149);
		double tmp175 = (tmp177 + tmp176);
		double tmp173 = (tmp175 + tmp174);
		double tmp172 = (tmp173 + tmp148);
		double tmp170 = (tmp172 - tmp171);
		double tmp169 = (tmp170 + tmp146);
		double tmp167 = (tmp169 + tmp168);
		double tmp166 = (tmp167 - tmp91);
		double tmp165 = (tmp166 + tmp143);
		double tmp164 = (tmp165 - tmp85);
		double tmp162 = (tmp164 - tmp163);
		double tmp161 = (tmp162 + tmp133);
		double tmp159 = (tmp161 + tmp160);
		double tmp158 = (tmp159 - tmp69);
		double tmp157 = (tmp158 + tmp130);
		double tmp156 = (tmp157 - tmp63);
		double tmp155 = (tmp156 - tmp121);
		double tmp154 = (tmp155 + tmp50);
		double tmp153 = (tmp154 + tmp118);
		double tmp152 = (tmp153 - tmp39);
		double tmp151 = (tmp152 + tmp115);
		double tmp150 = (tmp151 - tmp32);
		double tmp21 = (tmp22 / 2.);
		r2 = ((tmp150 + tmp21) / tmp1);
		r1 = ((tmp150 - tmp21) / tmp1);

	}

#undef D
#undef O
#undef S
#undef V

	IntersectionList lst;
	Intersection isect;
	isect.SurfaceVel = Vector3d::zero();
	isect.RefFrame = RefFrame;
	isect.Object = ObjectRef(this);
	isect.Colour = ColourSource;
	isect.IncomingDir = ray.Direction;
	{
		isect.Position = ray.Origin + ray.GetFourVelocity() * r1;
		Vector3d PosAtTime = subvec<3>(InitialPosition) + RefFrame.Velocity * (InitialPosition.t - isect.Position.t);
		isect.Normal = normalize(subvec<3>(isect.Position) - PosAtTime);
		lst.push_back(isect);
	}
	{
		isect.Position = ray.Origin + ray.GetFourVelocity() * r2;
		Vector3d PosAtTime = subvec<3>(InitialPosition) + RefFrame.Velocity * (InitialPosition.t - isect.Position.t);
		isect.Normal = normalize(subvec<3>(isect.Position) - PosAtTime);
		lst.push_back(isect);
	}
	return lst;
}
bool Sphere::AnyIntersections(const Ray& inray) const
{
	Ray ray = LorentzTransform(inray, RefFrame);

#define D ray.Direction
#define O ray.Origin
#define S InitialPosition
#define V RefFrame.Velocity

	double tmp149 = (D.z*O.z);
	double tmp148 = (D.z*S.z);
	double tmp139 = (O.t*V.x);
	double tmp146 = (O.x*V.x);
	double tmp137 = (S.t*V.x);
	double tmp91 = (S.x*V.x);
	double tmp12 = V.x*V.x;
	double tmp143 = (O.t*tmp12);
	double tmp85 = (S.t*tmp12);
	double tmp57 = (O.t*V.y);
	double tmp133 = (O.y*V.y);
	double tmp55 = (S.t*V.y);
	double tmp69 = (S.y*V.y);
	double tmp7 = V.y*V.y;
	double tmp130 = (O.t*tmp7);
	double tmp63 = (S.t*tmp7);
	double tmp122 = (O.t*V.z);
	double tmp121 = (D.z*tmp122);
	double tmp50 = (O.z*V.z);
	double tmp46 = (S.t*V.z);
	double tmp118 = (D.z*tmp46);
	double tmp39 = (S.z*V.z);
	double tmp2 = V.z*V.z;
	double tmp115 = (O.t*tmp2);
	double tmp32 = (S.t*tmp2);
	double tmp147 = (tmp149 - tmp148);
	double tmp145 = (tmp147 - tmp146);
	double tmp144 = (tmp145 + tmp91);
	double tmp142 = (tmp144 - tmp143);
	double tmp141 = (tmp142 + tmp85);
	double tmp140 = (O.x - S.x);
	double tmp138 = (tmp140 + tmp139);
	double tmp136 = (tmp138 - tmp137);
	double tmp135 = (D.x*tmp136);
	double tmp134 = (tmp141 + tmp135);
	double tmp132 = (tmp134 - tmp133);
	double tmp131 = (tmp132 + tmp69);
	double tmp129 = (tmp131 - tmp130);
	double tmp128 = (tmp129 + tmp63);
	double tmp127 = (O.y - S.y);
	double tmp126 = (tmp127 + tmp57);
	double tmp125 = (tmp126 - tmp55);
	double tmp124 = (D.y*tmp125);
	double tmp123 = (tmp128 + tmp124);
	double tmp120 = (tmp123 + tmp121);
	double tmp119 = (tmp120 - tmp50);
	double tmp117 = (tmp119 - tmp118);
	double tmp116 = (tmp117 + tmp39);
	double tmp114 = (tmp116 - tmp115);
	double tmp113 = (tmp114 + tmp32);
	double tmp112 = tmp113*tmp113;
	double tmp111 = (4 * tmp112);
	double tmp110 = O.x*O.x;
	double tmp109 = O.y*O.y;
	double tmp108 = (tmp110 + tmp109);
	double tmp107 = O.z*O.z;
	double tmp106 = (tmp108 + tmp107);
	double tmp105 = Radius * Radius;
	double tmp104 = (tmp106 - tmp105);
	double tmp103 = S.x*S.x;
	double tmp102 = (tmp104 + tmp103);
	double tmp101 = S.y*S.y;
	double tmp100 = (tmp102 + tmp101);
	double tmp99 = (O.z*S.z);
	double tmp98 = (2 * tmp99);
	double tmp97 = (tmp100 - tmp98);
	double tmp96 = S.z*S.z;
	double tmp95 = (tmp97 + tmp96);
	double tmp94 = (O.t*tmp91);
	double tmp93 = (2 * tmp94);
	double tmp92 = (tmp95 - tmp93);
	double tmp90 = (S.t*tmp91);
	double tmp89 = (2 * tmp90);
	double tmp88 = (tmp92 + tmp89);
	double tmp35 = O.t*O.t;
	double tmp87 = (tmp35*tmp12);
	double tmp86 = (tmp88 + tmp87);
	double tmp84 = (O.t*tmp85);
	double tmp83 = (2 * tmp84);
	double tmp82 = (tmp86 - tmp83);
	double tmp28 = S.t*S.t;
	double tmp81 = (tmp28*tmp12);
	double tmp80 = (tmp82 + tmp81);
	double tmp79 = (-O.t);
	double tmp78 = (tmp79 + S.t);
	double tmp77 = (tmp78*V.x);
	double tmp76 = (S.x + tmp77);
	double tmp75 = (O.x*tmp76);
	double tmp74 = (2 * tmp75);
	double tmp73 = (tmp80 - tmp74);
	double tmp72 = (O.t*tmp69);
	double tmp71 = (2 * tmp72);
	double tmp70 = (tmp73 - tmp71);
	double tmp68 = (S.t*tmp69);
	double tmp67 = (2 * tmp68);
	double tmp66 = (tmp70 + tmp67);
	double tmp65 = (tmp35*tmp7);
	double tmp64 = (tmp66 + tmp65);
	double tmp62 = (O.t*tmp63);
	double tmp61 = (2 * tmp62);
	double tmp60 = (tmp64 - tmp61);
	double tmp59 = (tmp28*tmp7);
	double tmp58 = (tmp60 + tmp59);
	double tmp56 = (S.y - tmp57);
	double tmp54 = (tmp56 + tmp55);
	double tmp53 = (O.y*tmp54);
	double tmp52 = (2 * tmp53);
	double tmp51 = (tmp58 - tmp52);
	double tmp49 = (O.t*tmp50);
	double tmp48 = (2 * tmp49);
	double tmp47 = (tmp51 + tmp48);
	double tmp45 = (O.z*tmp46);
	double tmp44 = (2 * tmp45);
	double tmp43 = (tmp47 - tmp44);
	double tmp42 = (O.t*tmp39);
	double tmp41 = (2 * tmp42);
	double tmp40 = (tmp43 - tmp41);
	double tmp38 = (S.t*tmp39);
	double tmp37 = (2 * tmp38);
	double tmp36 = (tmp40 + tmp37);
	double tmp34 = (tmp35*tmp2);
	double tmp33 = (tmp36 + tmp34);
	double tmp31 = (O.t*tmp32);
	double tmp30 = (2 * tmp31);
	double tmp29 = (tmp33 - tmp30);
	double tmp27 = (tmp28*tmp2);
	double tmp26 = (tmp29 + tmp27);
	double tmp20 = D.x*D.x;
	double tmp19 = D.y*D.y;
	double tmp18 = (tmp20 + tmp19);
	double tmp17 = D.z*D.z;
	double tmp16 = (tmp18 + tmp17);
	double tmp15 = (D.x*V.x);
	double tmp14 = (2 * tmp15);
	double tmp13 = (tmp16 - tmp14);
	double tmp11 = (tmp13 + tmp12);
	double tmp10 = (D.y*V.y);
	double tmp9 = (2 * tmp10);
	double tmp8 = (tmp11 - tmp9);
	double tmp6 = (tmp8 + tmp7);
	double tmp5 = (D.z*V.z);
	double tmp4 = (2 * tmp5);
	double tmp3 = (tmp6 - tmp4);
	double tmp1 = (tmp3 + tmp2);
	double tmp25 = (tmp1*tmp26);
	double tmp24 = (4 * tmp25);
	double det = (tmp111 - tmp24);

#undef D
#undef O
#undef S
#undef V

	return det >= 0;
}

Sphere::Sphere(const Vector4d& pos, double radius, ColourSourcePtr colour, const ReferenceFrame& ref_frame) :
	RefFrame(ref_frame),
	InitialPosition(pos),
	Radius(radius),
	ColourSource(colour)
{

}
