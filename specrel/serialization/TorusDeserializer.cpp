#include "SerializationDefs.h"
#include "..\Torus.h"
#include <iostream>

DESERIALIZER_DEFS(Torus, "torus");

DECL_FUNC(RingRadius, "ring_radius");
DECL_FUNC(Radius, "radius");

bool TorusDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != this->TokenName)
	{
		log << "[ERROR] " << TypeName << " deserializer passed an object not of type \""
			<< TokenName << "\". Object type was: \"" << info.TypeName.c_str() << "." << std::endl;
		return false;
	}

	Torus* torus = new Torus;
	ObjectPtr object = ObjectPtr(torus);

	bool is_static = true;
	bool errorbit = false;

	if (!GetReferenceFrame(torus->RefFrame, info, log))
		errorbit = true;
	else
		is_static = torus->RefFrame.Velocity == ReferenceFrame::Default.Velocity;

	if (!GetPosition(torus->InitialPosition, is_static, info, log))
		errorbit = true;

	if (!GetColour(torus->Colour, info, log))
		errorbit = true;

	DESERIALIZE(RingRadius, "ring_radius", torus, info, log, errorbit);
	DESERIALIZE(Radius, "radius", torus, info, log, errorbit);

	if (!errorbit)
	{
		if (frame->Scene)
			frame->Scene->AddObject(object);
	}

	return !errorbit;
}
