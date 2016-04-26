#ifndef SPECREL_FRAME_H
#define SPECREL_FRAME_H

#include "Scene.h"

#ifdef _MSC_VER
#include <codeanalysis\warnings.h>
#pragma warning(push)
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#pragma warning(disable:4319)
#include <CImg.h>
#pragma warning(pop) 
#else
#include <CImg.h>
#endif

typedef vector<size_t, 2> Vector2s;

struct Frame
{
public:
	// The image that the scene is being rendered to
	cil::CImg<typename Colour::value_type> Image;
	ScenePtr FrameScene;    // The scene which is being rendered
	Camera Viewpoint;       // The viewpoint from which the scene is being rendered
	size_t SamplesPerPixel; // The number of samples that will be gathered for each pixel
	Colour Background;      // The colour that will be used when there is no object

	Vector2s ImageSize() const;
	//Saves the file with the given name
	//It can optionally append a certain number of digits to the filename
	void Save(const std::string& name, int digits = -1, int ndigits = 6) const;

	//Shoots a ray through the point on the screen indicated by pixel
	//trace_forward indicates whether the ray should go into the past or the future
	Ray CreateRay(const Vector2d& pixel, bool trace_forward = false) const;
	Colour TraceRay(const Ray& ray) const;

	void DrawPixel(const Vector2s& pixel);
	void DrawFrame(bool multithreaded = true);

	Frame(const Vector2s& size);
	Frame(const Vector2s& size, const Camera& viewpoint);
	Frame(const Vector2s& size, const Camera& viewpoint, ScenePtr scene);
};

#endif
