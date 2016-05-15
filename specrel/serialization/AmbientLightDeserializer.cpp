#include "SerializationDefs.h"
#include "..\RgbColourSource.h"
#include "..\AmbientLight.h"
#include <iostream>

DESERIALIZER_DEFS(AmbientLight, "ambient_light");

bool AmbientLightDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	ColourSourcePtr src;

	bool errorbit = false;

	if (!GetColour(src, info, log))
	{
		auto it = info.Values.find("intensity");

		if (it == info.Values.end())
		{
			log << "[ERROR] \"ambient_light\" has no colour source." << std::endl;
			errorbit = true;
		}
		else
		{
			Vector3d colour;
			if (!GetVector(colour, it->second))
			{
				log << "[ERROR] The value of \"intensity\" is not a colour value." << std::endl;
				errorbit = true;
			}
			else
			{
				src = ColourSourcePtr(new RgbColourSource(static_cast<Colour>(colour)));
			}
		}
	}

	if (!errorbit)
	{
		Colour colour;
		if (src->GetColour(colour))
		{
			frame->Scene->AddLight(LightPtr(new AmbientLight(colour)));
		}
		else
		{
			log << "[ERROR] \"intensity\" is not a colour source that is position-independant" << std::endl;
			errorbit = true;
		}
	}

	return !errorbit;
}
