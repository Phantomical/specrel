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

	InfiniteCylinderY* cyl = new InfiniteCylinderY;
	ObjectPtr obj = ObjectPtr(cyl);
	bool errorbit = false;
	ColourSourcePtr colour;
	Vector3d vel;
	Vector4d pos;

	if (!GetColour(colour, info, log))
		errorbit = true;

	if (!GetVelocity(vel, info, log))
		errorbit = true;

	if (!GetPosition(pos, vel == ReferenceFrame::Default.Velocity, info, log))
		errorbit = true;

	DESERIALIZE(Radius, "radius", cyl, info, log, errorbit);

	if (!errorbit)
	{
		cyl->Colour = colour;
		cyl->InitialPosition = pos;
		cyl->RefFrame = ReferenceFrame(vel);
		frame->Scene->AddObject(ObjectPtr(cyl));
	}

	return !errorbit;
}

