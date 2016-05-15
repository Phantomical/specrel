#pragma once

#include "PreDefs.h"

class ColourSource
{
public:
	// Returns the colour at the given intersection
	virtual Colour GetColour(const Intersection&) const = 0;
	// Returns the colour irrespective of the position
	virtual bool GetColour(Colour& out) const;

	virtual ~ColourSource() = default;
};
