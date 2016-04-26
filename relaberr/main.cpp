#include "Frame.h"
#include "StaticPointLight.h"
#include "StandardColourSource.h"
#include "StaticSphere.h"

constexpr double deg2rad(double deg)
{
	return deg * 0.017453292519943295769;
}

int main()
{
	ScenePtr scene = MakePtr<ScenePtr>();
	ColourSourcePtr red = MakePtr<ColourSource>(new StandardColourSource(Colour(1.0f, 0.0f, 0.0f)));
	ColourSourcePtr blue = MakePtr<ColourSource>(new StandardColourSource(Colour(0.0f, 0.0f, 1.0f)));

	scene->Lights.push_back(MakePtr<LightBasePtr>(new StaticPointLight(Vector3d(0, 6, 0), red)));

	scene->Objects.push_back(MakePtr<ObjectBasePtr>(new StaticSphere(Vector3d::zero(), 5.0, blue)));

	Camera cam;
	cam.Forward = Vector3d(0.0, 0.0, 1.0);
	cam.Up = Vector3d(0.0, 1.0, 0.0);
	cam.Right = Vector3d(1.0, 0.0, 0.0);
	cam.FovY = deg2rad(60);
	cam.FovX = deg2rad(80);
	cam.Position = Position(0.0, 0.0, -15.0, 0.0);
	cam.RefFrame = ReferenceFrame::Default;

	Frame frame = Frame(Vector2s(500, 375), cam, scene);

	frame.DrawFrame(false);

	frame.Save("output.bmp");

	return 0;
}
