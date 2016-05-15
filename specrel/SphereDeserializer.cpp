#include "SphereDeserializer.h"
#include "Sphere.h"
#include "Frame.h"
#include <iostream>

bool SphereDeserializer::DeserializeToScene(FramePtr frame, const TypeInfo& info, std::ostream& log)
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

	auto it = info.Values.find("radius");

	if (it == info.Values.end())
	{
		log << "[ERROR] No radius found in element of type sphere." << std::endl;
		error = true;
	}
	else if (it->second.Type != Value::NUMBER)
	{
		log << "[ERROR] Radius value is not a number." << std::endl;
		error = true;
	}
	else
	{
		sphere->Radius = it->second.Number;
	}

	if (!error)
	{
		if (frame->Scene)
			frame->Scene->AddObject(sphereptr);
	}

	return !error;

}
