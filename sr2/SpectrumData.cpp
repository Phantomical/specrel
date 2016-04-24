#include "SpectrumData.h"
#include "Constants.h"
#include <algorithm>

inline double CubicInterp(const double v1, const double v2, const double mu)
{
	const double mu2 = (1.0 - std::cos(mu * PI)) * 0.5;
	return v1 * (1 - mu2) + v2 * mu2;
}
template<typename vTy>
inline vTy Clamp(const vTy v, const vTy max, const vTy min)
{
	return std::max(std::min(v, min), max);
}

double SpectrumData::FrequencyAtPosition(size_t idx) const
{
	// Frequency at a position follows from the formula
	// F = pow(10, (x + start) * mul)
	// where x is the position
	
	// This was chosen so that there would be samples all along the spectrum
	// but also so that there would be a sufficient density of samples.
	// To increase the sample density make sample_multiplier smaller
	// To change the start of the range, change sample_start

	static constexpr double sample_multiplier = 0.01;
	static constexpr double sample_start = 800.0;

	return std::pow(10.0, (idx + sample_start) * sample_multiplier);
}
double SpectrumData::WavelengthAtPosition(size_t idx) const
{
	return 1.0 / FrequencyAtPosition(idx);
}

double SpectrumData::RadianceAtPosition(double pos) const
{
	double start = Clamp(std::floor(pos), 1200.0, 0.0);
	double end = Clamp(std::ceil(pos), 1200.0, 0.0);
	double f = pos - start;

	return CubicInterp(start, end, f);
}
size_t SpectrumData::FrequencyPosition(double freq) const
{
	// Solves the equation x = 100 * (log10(freq) - 8)
	// If the equation in FrequencyAtPosition changes then
	// this equation must be changed too

	return 100.0 * (std::log10(freq) - 8.0) + 0.5;
}
