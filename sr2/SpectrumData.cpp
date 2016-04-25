#include "SpectrumData.h"
#include "Constants.h"
#include <algorithm>

#define NUM_SAMPLES NumSamples
static constexpr double X_DIVISOR = 416.66666666666666667;

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

	static constexpr double sample_multiplier = 1.0 / X_DIVISOR;
	//The power of 10 that are first sample is at
	static constexpr double power_start = 8.0;

	return std::pow(10.0, idx * sample_multiplier + power_start);
}
double SpectrumData::WavelengthAtPosition(size_t idx) const
{
	return 1.0 / FrequencyAtPosition(idx);
}

double SpectrumData::RadianceAtPosition(double pos) const
{
	double start = Clamp<double>(std::floor(pos), NumSamples, 0.0);
	double end = Clamp<double>(std::ceil(pos), NumSamples, 0.0);
	double f = pos - start;

	return CubicInterp(start, end, f);
}
double SpectrumData::FrequencyPosition(double freq) const
{
	// Solves the equation x = 100 * (log10(freq) - 8)
	// If the equation in FrequencyAtPosition changes then
	// this equation must be changed too

	return X_DIVISOR * (std::log10(freq) - 8.0);
}
size_t SpectrumData::FrequencyIndex(double freq) const
{
	return static_cast<size_t>(FrequencyPosition(freq) + 0.5);
}

SpectrumDataPtr operator +(SpectrumDataPtr a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] + b->Samples[i];
	}

	return res;
}
SpectrumDataPtr operator -(SpectrumDataPtr a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] - b->Samples[i];
	}

	return res;
}
SpectrumDataPtr operator *(SpectrumDataPtr a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] * b->Samples[i];
	}

	return res;
}
SpectrumDataPtr operator /(SpectrumDataPtr a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] / b->Samples[i];
	}

	return res;
}

SpectrumDataPtr operator +(SpectrumDataPtr a, double b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] + b;
	}
}
SpectrumDataPtr operator -(SpectrumDataPtr a, double b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] - b;
	}
}
SpectrumDataPtr operator *(SpectrumDataPtr a, double b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] * b;
	}
}
SpectrumDataPtr operator /(SpectrumDataPtr a, double b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NUM_SAMPLES; ++i)
	{
		res->Samples[i] = a->Samples[i] / b;
	}
}

SpectrumDataPtr operator +(double a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		res->Samples[i] = a + b->Samples[i];
	}

	return res;
}
SpectrumDataPtr operator -(double a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		res->Samples[i] = a - b->Samples[i];
	}

	return res;
}
SpectrumDataPtr operator *(double a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		res->Samples[i] = a * b->Samples[i];
	}

	return res;
}
SpectrumDataPtr operator /(double a, SpectrumDataPtr b)
{
	SpectrumDataPtr res = MakePtr<SpectrumDataPtr>();

	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		res->Samples[i] = a / b->Samples[i];
	}

	res;
}

SpectrumDataPtr operator +=(SpectrumDataPtr a, SpectrumDataPtr b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] += b->Samples[i];
	}

	return a;
}
SpectrumDataPtr operator -=(SpectrumDataPtr a, SpectrumDataPtr b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] -= b->Samples[i];
	}

	return a;
}
SpectrumDataPtr operator *=(SpectrumDataPtr a, SpectrumDataPtr b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] *= b->Samples[i];
	}

	return a;
}
SpectrumDataPtr operator /=(SpectrumDataPtr a, SpectrumDataPtr b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] /= b->Samples[i];
	}

	return a;
}

SpectrumDataPtr operator +=(SpectrumDataPtr a, double b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] += b;
	}

	return a;
}
SpectrumDataPtr operator -=(SpectrumDataPtr a, double b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] -= b;
	}

	return a;
}
SpectrumDataPtr operator *=(SpectrumDataPtr a, double b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] *= b;
	}

	return a;
}
SpectrumDataPtr operator /=(SpectrumDataPtr a, double b)
{
	for (size_t i = 0; i < SpectrumData::NumSamples; ++i)
	{
		a->Samples[i] /= b;
	}

	return a;
}
