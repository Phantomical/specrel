#ifndef SPECREL_COLOUR_SOURCE_H
#define SPECREL_COLOUR_SOURCE_H

#include "RefFrame.h"
#include "Intersection.h"
#include "vector.h"
#include <memory>

class ColourSource
{
	//Returns the colour in a specific reference frame
	virtual Colour GetColour(const Intersection& intersection, const ReferenceFrame& frame) const = 0;

	virtual ~ColourSource() = default;

};

typedef std::shared_ptr<ColourSource> ColourSourcePtr;

#endif
