#pragma once

#include "Vector.h"

typedef double vTy;
constexpr size_t M = 5;
constexpr size_t N = 6;

template<typename vTy, size_t M, size_t N>
struct matrix
{
	typedef vTy value_type;
	static constexpr size_t size = M * N;
	static constexpr size_t rows = M;
	static constexpr size_t cols = N;
	static constexpr bool square = M == N;

	union
	{
		value_type m[rows][cols];
		value_type data[size];
	};

	matrix() = default;
	matrix(value_type v)
	{
		for (size_t m = 0; m < M; ++m)
			for (size_t n = 0; n < N; ++n)
				this->m[m][n] = v;
	}
	matrix(const value_type* vals)
	{
		std::copy(vals, vals + size, data);
	}
	matrix(std::initializer_list<value_type> lst)
	{
		std::copy(lst.begin(), lst.end(), data);
	}

	value_type* operator[](const size_t idx)
	{
		return m[idx];
	}
	const value_type* operator[](const size_t idx) const
	{
		return m[idx];
	}
};

template<typename vTy, size_t sz>
matrix<vTy, sz, sz> identity()
{
	matrix<vTy, sz, sz> mat{ 0.0 };
	for (size_t i = 0; i < sz; ++i)
		mat[i][i] = 1.0;
	return mat;
}
template<typename vMty>
typename std::enable_if<vMty::rows == vMty::cols, vMty>::type identity()
{
	return identity<typename vMty::value_type, vMty::rows>();
}

template<size_t newM, size_t newN, typename vTy, size_t oldM, size_t oldN>
matrix<vTy, newM, newN> submat(const matrix<vTy, oldM, oldN>& m, size_t offset_m = 0, size_t offset_n = 0)
{
	matrix<vTy, newM, newN> res;
	for (size_t m = 0; m < newM; ++m)
		for (size_t n = 0; n < newN; ++n)
			res.m[m][n] = m.m[m + offset_m][n + offset_n];
	return res;
}

#define DEF_MAT_OP(op) \
template<typename vTy, size_t M, size_t N>\
matrix<vTy, M, N> operator op(const matrix<vTy, M, N>& mat, const typename matrix<vTy, M, N>::value_type& v)\
{\
	matrix<vTy, M, N> res;\
	for (size_t m = 0; m < M; ++m)\
		for (size_t n = 0; n < N; ++n)\
			res.m[m][n] = mat.m[m][n] + v;\
	return res;\
}\
template<typename vTy, size_t M, size_t N>\
matrix<vTy, M, N>& operator op##=(matrix<vTy, M, N>& mat, const typename matrix<vTy, M, N>::value_type& v)\
{\
	for (size_t m = 0; m < M; ++m)\
		for (size_t n = 0; n < N; ++n)\
			mat.m[m][n] op##= v;\
	return mat\
}

DEF_MAT_OP(+)
DEF_MAT_OP(-)
DEF_MAT_OP(*)
DEF_MAT_OP(/ )

#undef DEF_MAT_OP

template<typename vTy>
vTy det(const matrix<vTy, 2, 2>& m)
{
	return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}
template<typename vTy>
matrix<vTy, 2, 2> inverse(const matrix<vTy, 2, 2>& m)
{
	matrix<vTy, 2, 2> res;
	res[0][0] = m[1][1];
	res[0][1] = -m[0][1];
	res[1][0] = -m[1][0];
	res[1][1] = m[0][0];
	res *= 1.0 / det(m);
	return res;
}

template<typename vTy>
vTy det(const matrix<vTy, 3, 3>& a)
{
	return (a[0][0] * a[1][1] * a[2][2]
		+ a[1][0] * a[2][1] * a[0][2]
		+ a[2][0] * a[0][1] * a[1][2]
		- a[0][0] * a[2][1] * a[1][2]
		- a[2][1] * a[1][1] * a[0][2]
		- a[1][0] * a[0][1] * a[2][2]);
}
template<typename vTy>
vTy det(const matrix<vTy, 4, 4>& m)
{
	return
		m[0][3] * m[1][2] * m[2][1] * m[3][0] - m[0][2] * m[1][3] * m[2][1] * m[3][0] -
		m[0][3] * m[1][1] * m[2][2] * m[3][0] + m[0][1] * m[1][3] * m[2][2] * m[3][0] +
		m[0][2] * m[1][1] * m[2][3] * m[3][0] - m[0][1] * m[1][2] * m[2][3] * m[3][0] -
		m[0][3] * m[1][2] * m[2][0] * m[3][1] + m[0][2] * m[1][3] * m[2][0] * m[3][1] +
		m[0][3] * m[1][0] * m[2][2] * m[3][1] - m[0][0] * m[1][3] * m[2][2] * m[3][1] -
		m[0][2] * m[1][0] * m[2][3] * m[3][1] + m[0][0] * m[1][2] * m[2][3] * m[3][1] +
		m[0][3] * m[1][1] * m[2][0] * m[3][2] - m[0][1] * m[1][3] * m[2][0] * m[3][2] -
		m[0][3] * m[1][0] * m[2][1] * m[3][2] + m[0][0] * m[1][3] * m[2][1] * m[3][2] +
		m[0][1] * m[1][0] * m[2][3] * m[3][2] - m[0][0] * m[1][1] * m[2][3] * m[3][2] -
		m[0][2] * m[1][1] * m[2][0] * m[3][3] + m[0][1] * m[1][2] * m[2][0] * m[3][3] +
		m[0][2] * m[1][0] * m[2][1] * m[3][3] - m[0][0] * m[1][2] * m[2][1] * m[3][3] -
		m[0][1] * m[1][0] * m[2][2] * m[3][3] + m[0][0] * m[1][1] * m[2][2] * m[3][3];
}

template<typename vTy>
matrix<vTy, 3, 3> inverse(const matrix<vTy, 3, 3>& a)
{
	vTy invdet = 1.0 / det(a);

	matrix<vTy, 3, 3> res;
	res[0][0] = a[1][1] * a[2][2] - a[1][2] * a[2][1];
	res[0][1] = a[0][2] * a[2][1] - a[0][1] * a[2][2];
	res[0][2] = a[0][1] * a[1][2] - a[0][2] * a[1][1];
	res[1][0] = a[1][2] * a[2][0] - a[1][0] * a[2][2];
	res[1][1] = a[0][0] * a[2][2] - a[0][2] * a[2][0];
	res[1][2] = a[0][2] * a[1][0] - a[0][0] * a[1][2];
	res[2][0] = a[1][0] * a[2][1] - a[1][1] * a[2][0];
	res[2][1] = a[0][1] * a[2][0] - a[0][0] * a[2][1];
	res[2][2] = a[0][0] * a[1][1] - a[0][1] * a[1][2];
	res *= invdet;
	return res;
}
template<typename vTy>
matrix<vTy, 4, 4> inverse(const matrix<vTy, 4, 4>& m)
{
	matrix<vTy, 4, 4> res;
	res[0][0] = m[1][2] * m[2][3] * m[3][1] - m[1][3] * m[2][2] * m[3][1] + m[1][3] * m[2][1] * m[3][2] - m[1][1] * m[2][3] * m[3][2] - m[1][2] * m[2][1] * m[3][3] + m[1][1] * m[2][2] * m[3][3];
	res[0][1] = m[0][3] * m[2][2] * m[3][1] - m[0][2] * m[2][3] * m[3][1] - m[0][3] * m[2][1] * m[3][2] + m[0][1] * m[2][3] * m[3][2] + m[0][2] * m[2][1] * m[3][3] - m[0][1] * m[2][2] * m[3][3];
	res[0][2] = m[0][2] * m[1][3] * m[3][1] - m[0][3] * m[1][2] * m[3][1] + m[0][3] * m[1][1] * m[3][2] - m[0][1] * m[1][3] * m[3][2] - m[0][2] * m[1][1] * m[3][3] + m[0][1] * m[1][2] * m[3][3];
	res[0][3] = m[0][3] * m[1][2] * m[2][1] - m[0][2] * m[1][3] * m[2][1] - m[0][3] * m[1][1] * m[2][2] + m[0][1] * m[1][3] * m[2][2] + m[0][2] * m[1][1] * m[2][3] - m[0][1] * m[1][2] * m[2][3];
	res[1][0] = m[1][3] * m[2][2] * m[3][0] - m[1][2] * m[2][3] * m[3][0] - m[1][3] * m[2][0] * m[3][2] + m[1][0] * m[2][3] * m[3][2] + m[1][2] * m[2][0] * m[3][3] - m[1][0] * m[2][2] * m[3][3];
	res[1][1] = m[0][2] * m[2][3] * m[3][0] - m[0][3] * m[2][2] * m[3][0] + m[0][3] * m[2][0] * m[3][2] - m[0][0] * m[2][3] * m[3][2] - m[0][2] * m[2][0] * m[3][3] + m[0][0] * m[2][2] * m[3][3];
	res[1][2] = m[0][3] * m[1][2] * m[3][0] - m[0][2] * m[1][3] * m[3][0] - m[0][3] * m[1][0] * m[3][2] + m[0][0] * m[1][3] * m[3][2] + m[0][2] * m[1][0] * m[3][3] - m[0][0] * m[1][2] * m[3][3];
	res[1][3] = m[0][2] * m[1][3] * m[2][0] - m[0][3] * m[1][2] * m[2][0] + m[0][3] * m[1][0] * m[2][2] - m[0][0] * m[1][3] * m[2][2] - m[0][2] * m[1][0] * m[2][3] + m[0][0] * m[1][2] * m[2][3];
	res[2][0] = m[1][1] * m[2][3] * m[3][0] - m[1][3] * m[2][1] * m[3][0] + m[1][3] * m[2][0] * m[3][1] - m[1][0] * m[2][3] * m[3][1] - m[1][1] * m[2][0] * m[3][3] + m[1][0] * m[2][1] * m[3][3];
	res[2][1] = m[0][3] * m[2][1] * m[3][0] - m[0][1] * m[2][3] * m[3][0] - m[0][3] * m[2][0] * m[3][1] + m[0][0] * m[2][3] * m[3][1] + m[0][1] * m[2][0] * m[3][3] - m[0][0] * m[2][1] * m[3][3];
	res[2][2] = m[0][1] * m[1][3] * m[3][0] - m[0][3] * m[1][1] * m[3][0] + m[0][3] * m[1][0] * m[3][1] - m[0][0] * m[1][3] * m[3][1] - m[0][1] * m[1][0] * m[3][3] + m[0][0] * m[1][1] * m[3][3];
	res[2][3] = m[0][3] * m[1][1] * m[2][0] - m[0][1] * m[1][3] * m[2][0] - m[0][3] * m[1][0] * m[2][1] + m[0][0] * m[1][3] * m[2][1] + m[0][1] * m[1][0] * m[2][3] - m[0][0] * m[1][1] * m[2][3];
	res[3][0] = m[1][2] * m[2][1] * m[3][0] - m[1][1] * m[2][2] * m[3][0] - m[1][2] * m[2][0] * m[3][1] + m[1][0] * m[2][2] * m[3][1] + m[1][1] * m[2][0] * m[3][2] - m[1][0] * m[2][1] * m[3][2];
	res[3][1] = m[0][1] * m[2][2] * m[3][0] - m[0][2] * m[2][1] * m[3][0] + m[0][2] * m[2][0] * m[3][1] - m[0][0] * m[2][2] * m[3][1] - m[0][1] * m[2][0] * m[3][2] + m[0][0] * m[2][1] * m[3][2];
	res[3][2] = m[0][2] * m[1][1] * m[3][0] - m[0][1] * m[1][2] * m[3][0] - m[0][2] * m[1][0] * m[3][1] + m[0][0] * m[1][2] * m[3][1] + m[0][1] * m[1][0] * m[3][2] - m[0][0] * m[1][1] * m[3][2];
	res[3][3] = m[0][1] * m[1][2] * m[2][0] - m[0][2] * m[1][1] * m[2][0] + m[0][2] * m[1][0] * m[2][1] - m[0][0] * m[1][2] * m[2][1] - m[0][1] * m[1][0] * m[2][2] + m[0][0] * m[1][1] * m[2][2];
	res *= 1.0 / det(m);
	return res;
}

template<typename vTy, size_t M1, size_t N, size_t N2>
matrix<vTy, M1, N2> operator *(const matrix<vTy, M1, N>& a, const matrix<vTy, N, N2>& b)
{
	matrix<vTy, M1, N2> res;
	for (size_t m = 0; m < M1; ++m)
	{
		for (size_t n = 0; n < N2; ++n)
		{
			vTy sum = vTy(0.0);
			for (size_t i = 0; i < N; ++i)
				sum += a[m][i] * b[i][n];
		}
	}
	return res;
}
template<typename vTy, size_t sz>
matrix<vTy, sz, sz> operator /(const matrix<vTy, sz, sz>& a, const matrix<vTy, sz, sz>& b)
{
	return a * inverse(b);
}

template<typename vTy, size_t sz>
vector<vTy, sz> operator *(const matrix<vTy, sz, sz>& a, const vector<vTy, sz>& b)
{
	matrix<vTy, sz, 1> mat{ b.data };
	auto res = a * mat;
	return vector<vTy, sz>(res.data);
}
template<typename vTy, size_t sz>
vector<vTy, sz> operator *(const vector<vTy, sz>& a, const matrix<vTy, sz, sz>& b)
{
	matrix<vTy, sz, 1> mat{ a.data };
	auto res =  mat * b;
	return vector<vTy, sz>(res.data);
}
typedef matrix<double, 4, 4> Matrix44d;
typedef Matrix44d Metric;

