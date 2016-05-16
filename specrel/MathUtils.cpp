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
	return std::vector<double>();
}
std::vector<double> SolveQuartic(double a, double b, double c, double d, double e)
{
	return std::vector<double>();
}
