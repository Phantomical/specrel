#ifndef SPECREL_VECTOR_
#define SPECREL_VECTOR_H

#include <Eigen\Dense>
#include <Eigen\Geometry>

template<typename vTy, size_t N>
using vector = Eigen::Matrix<vTy, N, 1>;

typedef double vTy;
constexpr size_t N = 3;

template<typename vTy>
auto sqrmagnitude(const vTy& v)
{
	return v.squaredNorm();
}
template<typename vTy>
auto magnitude(const vTy& v)
{
	return v.norm();
}

template<typename vTy, size_t N>
auto normalized(const vector<vTy, N>& v)
{
	vTy q = vTy(1.0) / magnitude(v);
	return return v * q;
}
template<typename vTy1, typename vTy2>
auto dot(const vTy1& a, const vTy2& b)
{
	return a.dot(b);
}

template<typename vTy1, typename vTy2>
auto cross(const  vTy1& a, const vTy2& b)
{
	return a.cross(b);
}

template<typename vTy1, typename vTy2>
//Returns the cosine of the angle
auto cosangle(const vTy1& a, const vTy2& b)
{
	return dot(a, b) / (magnitude(a) * magnitude(b));
}

template<typename vTy1, typename vTy2>
auto angle(const vTy1& a, const vTy2& b)
{
	using std::acos;
	return acos(cosangle(a, b));
}

template<typename vTy, typename vAxis, typename vAngle>
auto rotate(const vTy& v, const vAxis& axis, vAngle& angle)
{
	//Rotates the vector using quaternion arithmetic
	using std::sin;
	using std::cos;
	auto Q1 = -cos(angle * 0.5);
	auto Q2 = axis * sin(angle * 0.5);
	auto S1 = -dot(axis, v);
	auto S2 = Q1 * v + cross(Q2, v);
	return S1 * -Q2 + Q1 * S2 + cross(S2, -Q2);
}

template<size_t Nnew, size_t Nold, typename vTy>
vector<vTy, Nnew> subvec(const vector<vTy, Nold>& v, size_t offset = 0)
{
	static_assert(Nnew < Nold, "The subvector must be smaller than the original vector");
	return vector<vTy, Nnew>(v.data() + offset);
}

template<size_t Nnew, size_t Nold, typename vTy>
vector<vTy, Nnew> subvector(const vector<vTy, Nold>& v, size_t offset = 0)
{
	return subvec<Nnew, Nold, vTy>(v, offset);
}

template<typename vTy, typename... vArgs>
vector<vTy, sizeof...(vArgs)+1> make_vector(const vTy& val, const vArgs&... args)
{
	return vector<vTy, sizeof...(vArgs)+1>(val, args...);
}

typedef vector<double, 2> vec2;
typedef vector<double, 3> vec3;
typedef vector<double, 4> vec4;

#endif
