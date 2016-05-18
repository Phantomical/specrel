#include "MathUtils.h"
#include <cmath>
#include <complex>

namespace
{
	template<size_t N> constexpr double pow(double v)
	{
		return v * pow<N - 1>(v);
	}

	template<> constexpr double pow<1>(double v)
	{
		return v;
	}
	template<> constexpr double pow<0>(double)
	{
		return 1.0;
	}

	bool approx0(double v)
	{
		return v > std::numeric_limits<double>::epsilon() &&
			v < std::numeric_limits<double>::epsilon();
	}
}

#define Power(v, n) pow<n>(v)

double BringRadical(double v)
{
	constexpr double a = 1.0559342467498000762782431508445;
	return a*std::sin(v);
}

std::vector<double> SolveQuadratic(double a, double b, double c)
{
	double det = b * b - 4 * a * c;

	if (det < 0.0)
		return std::vector<double>();

	std::vector<double> slns;

	double rtdet = std::sqrt(det);
	slns.push_back((-b + rtdet) / (2 * a));
	slns.push_back((-b - rtdet) / (2 * a));
	return slns;
}
std::vector<double> SolveCubic(double a, double b, double c, double d)
{
	std::vector<double> slns;

	{
		constexpr auto tmp3 = 1.2599210498948731648;
		constexpr auto tmp29 = 1.7320508075688772935;
		constexpr auto tmp34 = 1.5874010519681994748;
		const auto tmp38 = (3.*a);
		const auto tmp37 = (b / tmp38);
		const auto tmp36 = (-tmp37);
		const auto tmp19 = Power(b, 3);
		const auto tmp18 = (2 * tmp19);
		const auto tmp17 = (-tmp18);
		const auto tmp16 = (b*c);
		const auto tmp15 = (a*tmp16);
		const auto tmp14 = (9 * tmp15);
		const auto tmp13 = (tmp17 + tmp14);
		const auto tmp12 = Power(a, 2);
		const auto tmp11 = (tmp12*d);
		const auto tmp10 = (27 * tmp11);
		const auto tmp9 = (tmp13 - tmp10);
		const auto tmp26 = Power(b, 2);
		const auto tmp25 = (-tmp26);
		const auto tmp24 = (a*c);
		const auto tmp23 = (3 * tmp24);
		const auto tmp22 = (tmp25 + tmp23);
		const auto tmp21 = Power(tmp22, 3);
		const auto tmp20 = (4 * tmp21);
		const auto tmp8 = Power(tmp9, 2);
		const auto tmp7 = (tmp20 + tmp8);
		const auto tmp6 = std::sqrt(std::complex<double>(tmp7));
		const auto tmp5 = (tmp9 + tmp6);
		const auto tmp4 = std::pow(tmp5, 0.3333333333333333);
		const auto tmp33 = (a*tmp4);
		const auto tmp2 = (tmp3*a);
		const auto tmp30 = std::complex<double>(0, 1);
		const auto tmp28 = (tmp30*tmp29);
		const auto tmp35 = (1.0 - tmp28);
		const auto tmp32 = (tmp34*tmp33);
		const auto tmp31 = (3.0*tmp32);
		const auto tmp27 = (1.0 + tmp28);
		const auto tmp1 = (6.0*tmp2);
		const auto r1 = (tmp36 - ((tmp3*tmp22) / (3.*tmp33))) + (tmp4 / (3.*tmp2));
		const auto r2 = (tmp36 + ((tmp27*tmp22) / tmp31)) - ((tmp35*tmp4) / tmp1);
		const auto r3 = (tmp36 + ((tmp35*tmp22) / tmp31)) - ((tmp27*tmp4) / tmp1);

		if (approx0(r1.imag()))
			slns.push_back(r1.real());
		if (approx0(r2.imag()))
			slns.push_back(r2.real());
		if (approx0(r3.imag()))
			slns.push_back(r3.real());
	}
	return std::vector<double>();
}
std::vector<double> SolveQuartic(double a, double b, double c, double d, double e)
{
	std::vector<double> slns;

	{
		const auto tmp79 = (4.*a);
		const auto tmp78 = (b / tmp79);
		const auto tmp77 = (-tmp78);
		const auto tmp56 = Power(a, 2);
		const auto tmp55 = (4.*tmp56);
		const auto tmp24 = Power(b, 2);
		const auto tmp54 = (tmp24 / tmp55);
		const auto tmp53 = (2 * c);
		const auto tmp52 = (3.*a);
		const auto tmp51 = (tmp53 / tmp52);
		const auto tmp50 = (tmp54 - tmp51);
		const auto tmp44 = Power(c, 2);
		const auto tmp43 = (b*d);
		const auto tmp42 = (3 * tmp43);
		const auto tmp41 = (tmp44 - tmp42);
		const auto tmp40 = (a*e);
		const auto tmp39 = (12 * tmp40);
		const auto tmp38 = (tmp41 + tmp39);
		const auto tmp11 = 1.2599210498948731648;
		const auto tmp49 = (tmp11*tmp38);
		const auto tmp34 = Power(c, 3);
		const auto tmp33 = (2 * tmp34);
		const auto tmp32 = (c*d);
		const auto tmp31 = (b*tmp32);
		const auto tmp30 = (9 * tmp31);
		const auto tmp29 = (tmp33 - tmp30);
		const auto tmp28 = Power(d, 2);
		const auto tmp27 = (a*tmp28);
		const auto tmp26 = (27 * tmp27);
		const auto tmp25 = (tmp29 + tmp26);
		const auto tmp23 = (tmp24*e);
		const auto tmp22 = (27 * tmp23);
		const auto tmp21 = (tmp25 + tmp22);
		const auto tmp20 = (c*e);
		const auto tmp19 = (a*tmp20);
		const auto tmp18 = (72 * tmp19);
		const auto tmp17 = (tmp21 - tmp18);
		const auto tmp37 = Power(tmp38, 3);
		const auto tmp36 = (4 * tmp37);
		const auto tmp35 = (-tmp36);
		const auto tmp16 = Power(tmp17, 2);
		const auto tmp15 = (tmp35 + tmp16);
		const auto tmp14 = std::sqrt(std::complex<double>(tmp15));
		const auto tmp13 = (tmp17 + tmp14);
		const auto tmp12 = std::pow(tmp13, 0.3333333333333333);
		const auto tmp48 = (a*tmp12);
		const auto tmp47 = (3.*tmp48);
		const auto tmp46 = (tmp49 / tmp47);
		const auto tmp45 = (tmp50 + tmp46);
		const auto tmp10 = (tmp11*a);
		const auto tmp9 = (3.*tmp10);
		const auto tmp8 = (tmp12 / tmp9);
		const auto tmp7 = (tmp45 + tmp8);
		const auto tmp6 = std::sqrt(tmp7);
		const auto tmp76 = (tmp6 / 2.);
		const auto tmp85 = (tmp77 - tmp76);
		const auto tmp74 = (2.*tmp56);
		const auto tmp73 = (tmp24 / tmp74);
		const auto tmp72 = (4 * c);
		const auto tmp71 = (tmp72 / tmp52);
		const auto tmp70 = (tmp73 - tmp71);
		const auto tmp69 = (tmp70 - tmp46);
		const auto tmp68 = (tmp69 - tmp8);
		const auto tmp67 = Power(b, 3);
		const auto tmp66 = Power(a, 3);
		const auto tmp65 = (tmp67 / tmp66);
		const auto tmp64 = (-tmp65);
		const auto tmp63 = (b*c);
		const auto tmp62 = (4 * tmp63);
		const auto tmp61 = (tmp62 / tmp56);
		const auto tmp60 = (tmp64 + tmp61);
		const auto tmp59 = (8 * d);
		const auto tmp58 = (tmp59 / a);
		const auto tmp57 = (tmp60 - tmp58);
		const auto tmp5 = (4.*tmp6);
		const auto tmp4 = (tmp57 / tmp5);
		const auto tmp84 = (tmp68 - tmp4);
		const auto tmp83 = std::sqrt(tmp84);
		const auto tmp82 = (tmp83 / 2.);
		const auto tmp75 = (tmp77 + tmp76);
		const auto tmp3 = (tmp68 + tmp4);
		const auto tmp2 = std::sqrt(tmp3);
		const auto tmp1 = (tmp2 / 2.);
		const auto r1 = tmp85 - tmp82;
		const auto r2 = tmp85 + tmp82;
		const auto r3 = tmp75 - tmp1;
		const auto r4 = tmp75 + tmp1;
		
		if (approx0(r1.imag()))
			slns.push_back(r1.real());
		if (approx0(r2.imag()))
			slns.push_back(r2.real());
		if (approx0(r3.imag()))
			slns.push_back(r3.real());
		if (approx0(r4.imag()))
			slns.push_back(r4.real());
	}

	return slns;
}
