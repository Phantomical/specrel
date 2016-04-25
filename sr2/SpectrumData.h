#ifndef SPECREL_SPECTRUMDATA_H
#define SPECREL_SPECTRUMDATA_H

#include "PreDefs.h"

struct SpectrumData
{
	static constexpr size_t NumSamples = 1200;

	double Samples[NumSamples];

	double FrequencyAtPosition(size_t idx) const;
	double WavelengthAtPosition(size_t idx) const;

	double RadianceAtPosition(double pos) const;

	double FrequencyPosition(double freq) const;
	size_t FrequencyIndex(double freq) const;
};

SpectrumDataPtr operator +(SpectrumDataPtr a, SpectrumDataPtr b);
SpectrumDataPtr operator -(SpectrumDataPtr a, SpectrumDataPtr b);
SpectrumDataPtr operator *(SpectrumDataPtr a, SpectrumDataPtr b);
SpectrumDataPtr operator /(SpectrumDataPtr a, SpectrumDataPtr b);

SpectrumDataPtr operator +(SpectrumDataPtr a, double b);
SpectrumDataPtr operator -(SpectrumDataPtr a, double b);
SpectrumDataPtr operator *(SpectrumDataPtr a, double b);
SpectrumDataPtr operator /(SpectrumDataPtr a, double b);

SpectrumDataPtr operator +(double a, SpectrumDataPtr b);
SpectrumDataPtr operator -(double a, SpectrumDataPtr b);
SpectrumDataPtr operator *(double a, SpectrumDataPtr b);
SpectrumDataPtr operator /(double a, SpectrumDataPtr b);

SpectrumDataPtr operator +=(SpectrumDataPtr a, SpectrumDataPtr b);
SpectrumDataPtr operator -=(SpectrumDataPtr a, SpectrumDataPtr b);
SpectrumDataPtr operator *=(SpectrumDataPtr a, SpectrumDataPtr b);
SpectrumDataPtr operator /=(SpectrumDataPtr a, SpectrumDataPtr b);

SpectrumDataPtr operator +=(SpectrumDataPtr a, double b);
SpectrumDataPtr operator -=(SpectrumDataPtr a, double b);
SpectrumDataPtr operator *=(SpectrumDataPtr a, double b);
SpectrumDataPtr operator /=(SpectrumDataPtr a, double b);

#endif
