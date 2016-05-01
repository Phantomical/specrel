#pragma once

#include "ColourSource.h"

class RgbColourSource : public ColourSource
{
public:
	Colour RgbValue;
	
	Colour GetColour() const;
	virtual Colour GetColour(const Intersection&) const override final;

	RgbColourSource() = default;
	RgbColourSource(const Colour& colour);
};
