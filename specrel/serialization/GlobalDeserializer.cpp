#include "GlobalDeserializer.h"
#include "..\Frame.h"
#include "..\RgbColourSource.h"
#include <iostream>

#define NOT_PRESENT(mem, type) "[ERROR] \"" #mem "\" is not present in \"" #type "\"."
#define CHECK_PRESENT(mem, type) do { if(mem == info.Values.end()) { log << NOT_PRESENT(mem, type) << std::endl; errorbit = true; } } while (false)
#define NAN(val) "[ERROR] \"" #val "\" is not a number."
#define NAV(val) "[ERROR] \"" #val "\" is not a vector."

#define GET_NUMBER(tgt, val) do { if (!GetNumber(tgt, val->second)) { log << NAN(val) << std::endl; errorbit = true; } } while(false)
#define GET_VECTOR(tgt, val) do { if (!GetVector(tgt, val->second)) { log << NAV(val) << std::endl; errorbit = true; } } while(false)


bool GlobalDeserializer::DeserializeToFrame(FramePtr frame, const TypeInfo& info, std::ostream& log)
{
	if (info.TypeName != "global")
	{
		log << "[ERROR] Global deserializer passed a type of type: "
			<< info.TypeName.c_str() << "." << std::endl;
		return false;
	}

	double _width;
	double _height;

	bool errorbit = false;

	auto width = info.Values.find("width");
	auto height = info.Values.find("height");
	auto samples = info.Values.find("samples");
	auto background = info.Values.find("background");

	CHECK_PRESENT(width, global);
	CHECK_PRESENT(height, global);

	if (errorbit)
		return false;

	GET_NUMBER(_width, width);
	GET_NUMBER(_height, height);

	if (errorbit)
		return false;

	if (_width < 0)
	{
		log << "[ERROR] \"width\" is negative." << std::endl;
		errorbit = true;
	}
	if (_height < 0)
	{
		log << "[ERROR] \"height\" is negative." << std::endl;
		errorbit = true;
	}

	if (samples == info.Values.end())
	{
		frame->NumSamples = Frame::DefaultNumSamples;
	}
	else
	{
		double _samples;
		GET_NUMBER(_samples, samples);
		if (_samples < 0)
		{
			log << "[WARNING] \"samples\" is negative. Setting \"samples\" to "
				<< Frame::DefaultNumSamples << " samples per pixel." << std::endl;

			frame->NumSamples = Frame::DefaultNumSamples;
		}
		else if (_samples < 1)
		{
			log << "[WARNING] \"samples\" is less than 1. Setting \"samples\" to 1."
				<< std::endl;
			frame->NumSamples = 1;
		}
		else
		{
			frame->NumSamples = (size_t)_samples;
		}
	}

	if (background == info.Values.end())
	{
		frame->Background = Frame::DefaultBackground;
	}
	else
	{
		auto it = info.Values.find("background");

		if (it == info.Values.end())
		{
			log << "[ERROR] No colour found in type: " << info.TypeName.c_str() << "." << std::endl;
			return false;
		}
		if (it->second.Type != Value::VEC3)
		{
			log << "[ERROR] Background colour value in type: " << info.TypeName.c_str()
				<< " was not a colour." << std::endl;
			return false;
		}

		frame->Background = static_cast<Colour>(it->second.Vec3);
		return true;
	}

	if (!errorbit)
	{
		frame->SetFrameSize((size_t)_width, (size_t)_height);
	}

	return !errorbit;
}
