#ifndef SPECREL_SPECTRUM_H
#define SPECREL_SPECTRUM_H

#include "vector.h"
#include "PreDefs.h"

class SpectrumSource
{
public:
	virtual SpectrumDataPtr GetDataPtr() const = 0;

	virtual ~SpectrumSource() = default;
};

struct Spectrum
{
	SpectrumSourcePtr Source;

	Spectrum DopplerShift(double factor) const;

	Colour GetRGB() const;
	//Intensity of the light at a distance of 1
	double GetIntensity() const;

	Spectrum() = default;
	Spectrum(SpectrumSourcePtr source);
};

#endif