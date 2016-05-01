#include "Frame.h"
#include "Sphere.h"
#include "RgbColourSource.h"

int main()
{
	ScenePtr scene = MakePtr<Scene>();
	ColourSourcePtr source = MakePtr<RgbColourSource>(Colour(1.0f, 0.0f, 0.0f));
	ObjectPtr sphere = MakePtr<Sphere>(Vector4d(0.0, 0.0, 0.0, 0.0), 2.5, source);

	scene->Objects.push_back(sphere);

	Camera viewpoint = Camera(Vector4d(0.0, 0.0, -10.0, 0.0));
	
	Frame frame = Frame(1080, 720, scene, viewpoint, Colour(0.0f, 0.0f, 1.0f), 512);

	frame.TraceFrame();

	frame.Save("output.bmp");

	return 0;
}
