#include "SerializationDefs.h"
#include "..\RgbColourSource.h"
#include "..\DirectionalLight.h"
#include <iostream>

DESERIALIZER_DEFS(DirectionalLight, "directional_light");

#define NAV(val) "[ERROR] \"" #val "\" is not a vector."
#define GET_VECTOR(tgt, val) do { if (!GetVector(tgt, val->second)) { log << NAV(val) << std::endl; errorbit = true; } } while(false)

bool DirectionalLightDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != "directional_light")
	{
		log << "[ERROR] DirectionalLightDeserializer passed a type of \"" << info.TypeName.c_str()
			<< "\" instead of \"directional_light\"." << std::endl;
		return false;
	}

	Vector3d dir;
	ColourSourcePtr src;
	bool errorbit = false;

	if (!GetColour(src, info, log))
	{
		auto it = info.Values.find("intensity");

		if (it == info.Values.end())
		{
			log << "[ERROR] \"directional_light\" has no colour source." << std::endl;
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

	auto direction = info.Values.find("direction");

	if (direction == info.Values.end())
	{
		log << "[ERROR] No direction present in type \"directional_light\"." << std::endl;
		errorbit = true;
	}
	else
	{
		GET_VECTOR(dir, direction);
	}

	if (!errorbit)
	{
		Colour colour;
		if (src->GetColour(colour))
		{
			frame->Scene->AddLight(LightPtr(new DirectionalLight(dir, colour)));
		}
		else
		{
			log << "[ERROR] Colour source of \"directional_light\" was not position-independant." << std::endl;
			errorbit = true;
		}
	}

	return !errorbit;
}
