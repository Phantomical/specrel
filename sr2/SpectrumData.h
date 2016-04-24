#ifndef SPECREL_SPECTRUMDATA_H
#define SPECREL_SPECTRUMDATA_H

#include "PreDefs.h"

struct SpectrumData
{
	double Samples[1200];

	double FrequencyAtPosition(size_t idx) const;
	double WavelengthAtPosition(size_t idx) const;

	double RadianceAtPosition(double pos) const;

	size_t FrequencyPosition(double freq) const;
};

#endif
