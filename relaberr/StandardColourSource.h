#pragma once

#include "ColourSource.h"

class StandardColourSource : public ColourSource
{
public:
	Colour Rgb;

	virtual Colour GetRGB() const
	{
		return Rgb;
	}

	StandardColourSource() = default;
	StandardColourSource(const Colour& rgb) :
		Rgb(rgb)
	{

	}
};
