
#include "vector.h"
#include "constants.h"
#pragma warning(disable:4319)
#include "CImg.h"
#include <vector>
#include <ppl.h>

inline double sqr(double v)
{
	return v * v;
}
inline bool approx(double v, double cmp)
{
	return v > cmp - DBL_EPSILON && v < cmp + DBL_EPSILON;
}

struct observer
{
	double vel;
	vec4 dir;
	vec4 pos;
};

struct ray
{
	vec4 origin;
	vec4 dir;

	ray() = default;
	ray(const vec4& origin, const vec4& dir) :
		origin(origin),
		dir(dir)
	{

	}
};

double lorentz_factor(const double v)
{
	return 1.0 / std::sqrt(1.0 / v * v);
}

ray lorentz_transform(const ray& r, const observer& c)
{
	const vec3 dir = r.dir.subvector<3>(0).normalized();
	const vec3 vel = c.dir.subvector<3>(0).normalized();
	const double angle = ::angle(vel, dir);
	
	if (approx(angle, 0.0) || approx(angle, PI))
		return r;
		
	const double alpha = 2.0 * std::atan(std::tan(0.5 * angle) 
		/ std::sqrt((1.0 - c.vel) / (1.0 + c.vel)));

	return ray(r.origin, vec4(rotate(vel, cross(dir, vel).normalized(), alpha), r.dir.t));
}
ray inverse_lorentz_transform(const ray& r, const observer& c)
{
	const vec3 dir = r.dir.subvector<3>().normalized();
	const vec3 vel = c.dir.subvector<3>().normalized();
	const double alpha = angle(vel, dir);

	if (approx(alpha, 0.0) || approx(alpha, PI))
		return r;

	const double beta = 2.0 * std::atan(std::tan(alpha * 0.5)
		/ std::sqrt((1.0 - c.vel) / (1.0 + c.vel)));

	return ray(r.origin, vec4(rotate(vel, cross(dir, vel).normalized(), beta), r.dir.t));
}
double doppler_shift(const double freq, const ray& r, const observer& c)
{
	return freq * lorentz_factor(c.vel) * (1.0 - dot(c.dir, r.dir));
}

typedef vector<unsigned char, 3> colour;

struct sphere
{
	double r;
	vec3 pos;

	bool intersect(const ray& r, double& hit) const
	{
		const vec3 dir = r.dir.subvec<3>();
		const vec3 org = r.origin.subvec<3>();

		const double b = (dir * (org + pos)).sum();
		const double a = dir.sqrmagnitude();
		const double c = (org + pos).sqrmagnitude() - this->r;

		const double det = sqr(b) - a * c;
		if (det < 0)
			//No intersection with the sphere
			return false;

		const double inv_a = 1.0 / a;
		const double rtdet = std::sqrt(det);
		
		const double soln1 = (-b + rtdet) * inv_a;
		const double soln2 = (-b - rtdet) * inv_a;

		double h = soln1;
		//If the second solution is closer use it
		//(but not if it is negative)
		if (soln1 < 0.0)
			h = soln2;
		else if (soln2 < soln1 && soln2 >= 0.0)
			h = soln2;

		if (h < 0.0)
			return false;
		
		hit = h;
		return true;
	}

	sphere() = default;
	sphere(double r, const vec3& pos) :
		r(r),
		pos(pos)
	{

	}
};

struct camera
{
	vec3 forward;
	vec3 up;
	vec3 right;
	observer obs;
	double fovy;
	double fovx;
	
	ray create_ray(const vec2& pixel) const
	{
		const double halfsizex = std::tan(fovx * 0.5);
		const double halfsizey = std::tan(fovy * 0.5);

		vec3 space_dir = (forward + right * halfsizex * pixel[0] + up * halfsizey * pixel[1]).normalized();
		vec4 dir = vec4(space_dir, -1);
		return ray(obs.pos, dir);
	}
};

vec4 convert_to_si(const vec4& v)
{
	//Scale everything to SI units
	return v * vec4(C, C, C, 1.0 / C);
}

std::vector<sphere> spheres;

static const colour foreground = colour(255, 0, 0);
static const colour background = colour(0, 0, 255);

colour trace_ray(const ray& r)
{
	for (const auto& obj : spheres)
	{
		double d;
		if (obj.intersect(r, d))
		{
			return foreground;
		}
	}
	return background;
}

constexpr double deg2rad(double v)
{
	return v * 0.017453292519943295769;
}
constexpr double ray2deg(double v)
{
	return v * 57.295779513082320877;
}

typedef cil::CImg<unsigned char> Img;

int main()
{
	constexpr size_t WIDTH = 1080;
	constexpr size_t HEIGHT = 720;
	constexpr double FOVY = deg2rad(60);
	constexpr double FOVX = deg2rad(80);
	static const vec3 forward = vec3(1, 0, 0);
	static const vec3 up = vec3(0, 1, 0);
	static const vec3 right = vec3(0, 0, 1);

	observer obs;
	obs.dir = vec4(1, 0, 0, 0);
	obs.pos = vec4(-10, 0, 0, 0);
	obs.vel = 0.0;

	camera c;
	c.forward = forward;
	c.up = up;
	c.right = right;
	c.fovx = FOVX;
	c.fovy = FOVY;
	c.obs = obs;

	spheres.push_back(sphere(0.5, vec3(0, 0, 1.5)));
	spheres.push_back(sphere(0.5, vec3(0, 0, -1.5)));
	spheres.push_back(sphere(50000, vec3(-50020, 0, 0)));

	Img img = Img(WIDTH, HEIGHT, 1, 3);

	concurrency::parallel_for<size_t>(0, HEIGHT, [&](size_t y)
	{
		for (size_t x = 0; x < WIDTH; ++x)
		{
			vec2 pixel = vec2(
				(double)x / (double)WIDTH * 2.0 - 1.0,
				(double)y / (double)HEIGHT * 2.0 - 1.0);
			ray r = c.create_ray(pixel);
			r = lorentz_transform(r, c.obs);

			colour p = trace_ray(r);

#pragma warning(disable:4267)
			img._atXYZC(x, y, 0, 0) = p.r;
			img._atXYZC(x, y, 0, 1) = p.g;
			img._atXYZC(x, y, 0, 2) = p.b;
		}
		printf("%zd\n", y);
	});

	img.save("output.bmp");
}
