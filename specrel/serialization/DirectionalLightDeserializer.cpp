#include "SerializationDefs.h"
#include "..\RgbColourSource.h"
#include "..\DirectionalLight.h"
#include <iostream>

DESERIALIZER_DEFS(DirectionalLight, "directional_light");

bool DirectionalLightDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != "directional_light")
	{
		log << "[ERROR] DirectionalLightDeserializer passed a type of \"" << info.TypeName.c_str()
			<< "\" instead of \"directional_light\"." << std::endl;
		return false;
	}

	DirectionalLight* light = new DirectionalLight;
	LightPtr ptr = LightPtr(light);

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

	DESERIALIZE(Direction, "direction", light, info, log, errorbit);

	if (!errorbit)
	{
		Colour colour;
		if (src->GetColour(colour))
		{
			light->Intensity = colour;
			frame->Scene->AddLight(ptr);
		}
		else
		{
			log << "[ERROR] Colour source of \"directional_light\" was not position-independant." << std::endl;
			errorbit = true;
		}
	}

	return !errorbit;
}
