#include "SerializationDefs.h"
#include "..\InfiniteCylinderY.h"
#include <iostream>

DESERIALIZER_DEFS(InfiniteCylinderY, "infinite_cylinder_y");

bool InfiniteCylinderYDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != TokenName)
	{
		log << "[ERROR] " << TypeName << " was passed an instance of type \"" 
			<< info.TypeName.c_str() << "\"." << std::endl;
		return false;
	}

	bool errorbit = false;
	ColourSourcePtr colour;
	Vector3d vel;
	Vector4d pos;
	double radius = 0.0;

	if (!GetColour(colour, info, log))
		errorbit = true;

	if (!GetVelocity(vel, info, log))
		errorbit = true;

	if (!GetPosition(pos, vel == ReferenceFrame::Default.Velocity, info, log))
		errorbit = true;

	{
		auto it = info.Values.find("radius");

		if (it == info.Values.end())
		{
			log << "[ERROR] No radius found in element of type \"" 
				<< TypeName << "\"." << std::endl;
			errorbit = true;
		}
		else if (it->second.Type != Value::NUMBER)
		{
			log << "[ERROR] Radius value is not a number." << std::endl;
			errorbit = true;
		}
		else
		{
			radius = it->second.Number;
		}
	}

	if (!errorbit)
	{
		InfiniteCylinderY* cyl = new InfiniteCylinderY;
		cyl->Colour = colour;
		cyl->InitialPosition = pos;
		cyl->Radius = radius;
		cyl->RefFrame = ReferenceFrame(vel);
		frame->Scene->AddObject(ObjectPtr(cyl));
	}

	return !errorbit;
}

