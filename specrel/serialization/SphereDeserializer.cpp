#include "SerializationDefs.h"
#include "..\Sphere.h"
#include "..\Frame.h"
#include <iostream>

DESERIALIZER_DEFS(Sphere, "sphere");

DECL_FUNC(Radius, "radius");

bool SphereDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != "sphere")
	{
		log << "[ERROR] Sphere deserializer passed an object not of type \"sphere\"."
			"Object type was: \"" << info.TypeName.c_str() << "." << std::endl;
		return false;
	}

	Sphere* sphere = new Sphere();
	// Deletes the sphere if an exception is thrown
	// Don't move this to the end of the method!
	ObjectPtr sphereptr = ObjectPtr(sphere);

	bool is_static = true;
	bool error = false;

	if (!GetReferenceFrame(sphere->RefFrame, info, log))
		error = true;
	else
		is_static = sphere->RefFrame.Velocity == ReferenceFrame::Default.Velocity;

	if (!GetPosition(sphere->InitialPosition, is_static, info, log))
		error = true;

	if (!GetColour(sphere->ColourSource, info, log))
		error = true;

	DESERIALIZE(Radius, "radius", sphere, info, log, error);

	if (!error)
	{
		if (frame->Scene)
			frame->Scene->AddObject(sphereptr);
	}

	return !error;

}
