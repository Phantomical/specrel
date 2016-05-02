#include "Frame.h"
#include "Sphere.h"
#include "RgbColourSource.h"

int main()
{
	ScenePtr scene = MakePtr<Scene>();
	ColourSourcePtr source1 = MakePtr<RgbColourSource>(Colour(1.0f, 0.0f, 0.0f));
	ColourSourcePtr source2 = MakePtr<RgbColourSource>(Colour(0.0f, 1.0f, 0.0f));
	ColourSourcePtr source3 = MakePtr<RgbColourSource>(Colour(0.0f, 0.0f, 1.0f));
	ObjectPtr sphere1 = MakePtr<Sphere>(Vector4d(1.5, -0.5, 0.0, 0.0), 2.5, source1);
	ObjectPtr sphere2 = MakePtr<Sphere>(Vector4d(-1.5, -0.5, 0.0, 0.0), 2.5, source2);
	ObjectPtr sphere3 = MakePtr<Sphere>(Vector4d(0.0, 1.0, -0.5, 0.0), 2.5, source3);

	scene->AddObject(sphere1);
	scene->AddObject(sphere2);
	scene->AddObject(sphere3);

	Camera viewpoint = Camera(Vector4d(0.0, 0.0, -15.0, 0.0), ReferenceFrame(Vector3d(0.0, 0.0, 0.9)));
	viewpoint.FovX = Deg2Rad(120);
	viewpoint.FovY = Deg2Rad(90);
	
	Frame frame = Frame(100, 75, scene, viewpoint, Colour(0.0f, 0.0f, 0.0f), 32);

	frame.TraceFrame();

	frame.Save("output.bmp");

	return 0;
}
