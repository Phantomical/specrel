#ifndef SPECREL_SPECTRUM_H
#define SPECREL_SPECTRUM_H

#include "vector.h"
#include "PreDefs.h"

class SpectrumSource
{
public:
	virtual SpectrumDataPtr GetData() const = 0;
	virtual double GetIntensity() const = 0;

	virtual ~SpectrumSource() = default;
};

struct Spectrum
{
	SpectrumSourcePtr Source;

	Spectrum DopplerShift(double factor) const;

	Colour GetRGB() const;
	//Intensity of the light at a distance of 1
	//Returns a separate intensity for each channel
	//A value of 1 means that light will be unchanged at a unit distance
	double GetIntensity() const;

	Spectrum() = default;
	Spectrum(SpectrumSourcePtr source);
};

#endif
