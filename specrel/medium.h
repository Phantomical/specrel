#ifndef SPECREL_MEDIUM_H
#define SPECREL_MEDIUM_H

#include "RefFrame.h"

struct Medium
{
	double RefractiveIndex;  // Refractive index of the medium (speed of light in the medium / speed of light in vacuum)
	ReferenceFrame RefFrame; // Velocity of the substance in this medium

	Medium() = default;
	Medium(double refractive_index);

	static const Medium Vacuum;
};

#endif
