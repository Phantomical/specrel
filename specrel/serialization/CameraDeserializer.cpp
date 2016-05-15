#include "CameraDeserializer.h"
#include "..\Frame.h"
#include <iostream>

#define NOT_PRESENT(_1, _2, type) "[ERROR] Both \"" #_1 "\" and \"" #_2 "\" are not present in \"" #type "\"."
#define NAN(val) "[ERROR] \"" #val "\" is not a number."
#define NAV(val) "[ERROR] \"" #val "\" is not a vector."

#define GET_NUMBER(tgt, val) do { if (!GetNumber(tgt, val->second)) { log << NAN(val) << std::endl; errorbit = true; } } while(false)
#define GET_VECTOR(tgt, val) do { if (!GetVector(tgt, val->second)) { log << NAV(val) << std::endl; errorbit = true; } } while(false)

#define CHECK_PRESENT(outer, inner) do { if (inner == end) { log << NOT_PRESENT(outer, inner) << std::endl; errorbit = true; } } while(false)

bool CameraDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != "camera")
	{
		log << "[ERROR] Camera deserializer passed a type of type: " 
			<< info.TypeName.c_str() << "." << std::endl;
		return false;
	}

	Camera cam;

	bool errorbit = false;

	if (!GetReferenceFrame(cam.RefFrame, info, log))
		errorbit = true;
	if (!GetPosition(cam.Position, cam.RefFrame.Velocity == ReferenceFrame::Default.Velocity, info, log))
		errorbit = true;

	auto end = info.Values.end();

	auto forward = info.Values.find("forward");
	auto up = info.Values.find("up");
	auto right = info.Values.find("right");

	auto fovx = info.Values.find("fovx");
	auto fovy = info.Values.find("fovy");
	auto aspect = info.Values.find("aspect");

	if (forward == end)
	{
		CHECK_PRESENT(forward, up);
		CHECK_PRESENT(forward, right);

		if (!errorbit)
		{
			GET_VECTOR(cam.Up, up);
			GET_VECTOR(cam.Right, right);

			if (!errorbit)
			{
				cam.Forward = cross(cam.Up, cam.Right);
			}
		}
	}
	else if (up == end)
	{
		CHECK_PRESENT(up, right);

		if (!errorbit)
		{
			GET_VECTOR(cam.Forward, forward);
			GET_VECTOR(cam.Right, right);

			if (!errorbit)
			{
				cam.Up = cross(cam.Forward, cam.Right);
			}
		}
	}
	else if (right == end)
	{
		GET_VECTOR(cam.Forward, forward);
		GET_VECTOR(cam.Right, right);

		if (!errorbit)
		{
			cam.Right = cross(cam.Forward, cam.Right);
		}
	}
	else
	{
		GET_VECTOR(cam.Forward, forward);
		GET_VECTOR(cam.Up, up);
		GET_VECTOR(cam.Right, right);
	}

	if (aspect == end)
	{
		if (fovx == end)
		{
			log << NOT_PRESENT(aspect, fovx, camera) << std::endl;
			errorbit = true;
		}
		else if (fovy == end)
		{
			log << NOT_PRESENT(aspect, fovy, camera) << std::endl;
			errorbit = true;
		}
		else
		{
			GET_NUMBER(cam.FovX, fovx);
			GET_NUMBER(cam.FovY, fovy);
		}
	}
	else if (fovx == end)
	{
		if (fovy == end)
		{
			log << NOT_PRESENT(fovx, fovy, camera) << std::endl;
			errorbit = true;
		}
		else
		{
			double aspect_;
			GET_NUMBER(aspect_, aspect);
			GET_NUMBER(cam.FovY, fovy);

			if (!errorbit)
			{
				cam.FovX = cam.FovY * aspect_;
			}
		}
	}
	else if (fovy == end)
	{
		double aspect_;
		GET_NUMBER(aspect_, aspect);
		GET_NUMBER(cam.FovX, fovx);

		if (!errorbit)
		{
			cam.FovY = cam.FovX / aspect_;
		}
	}
	else
	{
		GET_NUMBER(cam.FovX, fovx);
		GET_NUMBER(cam.FovY, fovy);
	}

	if (!errorbit)
		frame->Viewpoint = cam;

	return !errorbit;
}
