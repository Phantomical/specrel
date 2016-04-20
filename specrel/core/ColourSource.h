#ifndef SPECREL_COLOUR_SOURCE_
#define SPECREL_COLOUR_SOURCE_H

#include "ref_frame.h"
#include <memory>

class ColourSource
{
	//Returns the colour in a specific reference frame
	virtual Colour GetColour(const ReferenceFrame& frame) = 0;

	virtual ~ColourSource() = default;
};

typedef std::shared_ptr<ColourSource> ColourSourcePtr;

#endif
