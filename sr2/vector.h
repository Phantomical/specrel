#ifndef SPECREL_VECTOR_H
#define SPECREL_VECTOR_H

#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>

template<typename, size_t> struct vector;

template<typename vTy, size_t N>
struct vector_data
{
	typedef vTy value_type;
	static constexpr size_t size = N;

	value_type data[size];

	vector_data() = default;
	vector_data(const vector<value_type, size - 1>& v, const value_type& n);
	template<typename vTy, typename... vArgs>
	vector_data(const vTy& arg, const vArgs&... args)
	{
		fill<0, vArgs...>(arg, args...);
	}
private:
	template<size_t idx, typename... vArgs>
	void fill(const value_type& val, const vArgs&... args)
	{
		static_assert(idx < size, "Passed more arguments than elements in the vector");
		data[idx] = val;
		fill<idx + 1, vArgs...>(args...);
	}
	template<size_t idx>
	void fill(const value_type& val)
	{
		static_assert(idx < size, "Passed more arguments than elements in the vector");
		data[idx] = val;
	}
};



template<typename vTy, size_t N>
struct vector : vector_data<vTy, N>
{
	typedef vector_data<value_type, size> data_type;
	typedef typename data_type::value_type value_type;
	static constexpr size_t size = data_type::size;

	static_assert(size != 1 || size != 0, "Vectors of size 1 or 0 are not valid");

	vector() = default;
	vector(const data_type& data) :
		data_type(data)
	{

	}
	vector(const value_type* vals)
	{
		std::memcpy(data, vals, sizeof(value_type) * N);
	}
	vector(const vector<vTy, size - 1>& v, const value_type& n) :
		data_type(v, n)
	{

	}
	template<typename vTy1, typename... vArgs>
	vector(const vTy1& v, const vArgs&... args) :
		data_type(v, args...)
	{

	}
	vector(const std::initializer_list<value_type>& lst)
	{
		for (size_t i = 0; i < size && i < lst.size(); ++i)
			data[i] = *(lst.begin()+i);
	}

	void fill(value_type v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] = v;
	}

	value_type& operator[](const size_t idx)
	{
		return data[idx];
	}
	const value_type& operator[](const size_t idx) const
	{
		return data[idx];
	}

	value_type* begin()
	{
		return data;
	}
	const value_type* begin() const
	{
		return data;
	}

	value_type* end()
	{
		return data + size;
	}
	const value_type* end() const
	{
		return data + size;
	}

	value_type sum() const
	{
		return std::accumulate(begin(), end(), value_type(0.0));
	}

	template<typename oTy>
	explicit operator vector<oTy, size>() const
	{
		vector<oTy, size> res;
		for (size_t i = 0; i < size; ++i)
			res.data[i] = static_cast<oTy>(data[i]);
		return res;
	}
	template<size_t nsz>
	explicit operator vector<value_type, nsz>() const
	{
		vector<value_type, nsz> res;
		size_t i = 0;
		for (; i < nsz && i < size; ++i)
			res[i] = data[i];
		for (; i < nsz; ++i)
			res[i] = value_type();
		return res;
	}
	template<typename oTy, size_t nsz>
	explicit operator vector<oTy, nsz>() const
	{
		return static_cast<vector<oTy, nsz>>(static_cast<vector<value_type, N>>(*this));
	}

	value_type magnitude() const;
	value_type sqrmagnitude() const;

	vector normalized() const
	{
		value_type q = value_type(1.0) / magnitude();
		return *this * q;
	}
	void normalize()
	{
		value_type q = value_type(1.0) / magnitude();
		*this *= q;
	}

	template<size_t nsz>
	//WARNING: If start + nsz is greater than the size of the vector, the result is undefined
	vector<value_type, nsz> subvector(size_t start = 0) const
	{
		static_assert(nsz < size, "A subvector must be smaller then the vector it is selected from");
		return vector<value_type, nsz>(data + start);
	}
	template<size_t nsz>
	//An alias for subvector
	vector<value_type, nsz> subvec(size_t start = 0) const
	{
		return subvector<nsz>(start);
	}

	vector& operator +=(const vector& v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] += v.data[i];
	}
	vector& operator -=(const vector& v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] -= v.data[i];
	}
	vector& operator *=(const vector& v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] *= v.data[i];
	}
	vector& operator /=(const vector& v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] /= v.data[i];
	}

	vector& operator +=(const double v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] += v;
	}
	vector& operator -=(const double v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] -= v;
	}
	vector& operator *=(const double v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] *= v;
	}
	vector& operator /=(const double v)
	{
		for (size_t i = 0; i < size; ++i)
			data[i] /= v;
	}

	vector operator-() const
	{
		vector res;
		for (size_t i = 0; i < size; ++i)
			res.data[i] = -data[i];
		return res;
	}
	const vector& operator+() const
	{
		return *this;
	}

	static const vector zero()
	{
		vector(vector<value_type, size - 1>::zero(), 0.0);
	}
};

template<typename vTy>
struct vector<vTy, 1>
{
	typedef vTy value_type;
	static constexpr size_t size = 1;
	
	value_type data[size];

	vector() = default;
	vector(value_type v)
	{
		data[0] = v;
	}

	static const vector zero()
	{
		return vector(0.0);
	}
};

template<typename vTy>
struct vector_data<vTy, 2>
{
	typedef vTy value_type;
	static constexpr size_t size = 2;
	union
	{
		value_type data[size];
		struct
		{
			value_type x;
			value_type y;
		};
	};

	vector_data() = default;
	vector_data(const value_type& x, const value_type& y) :
		x(x),
		y(y)
	{

	}
};
template<typename vTy>
struct vector_data<vTy, 3>
{
	typedef vTy value_type;
	static constexpr size_t size = 3;
	union
	{
		value_type data[size];
		struct
		{
			value_type x;
			value_type y;
			value_type z;
		};
		struct
		{
			value_type r;
			value_type g;
			value_type b;
		};
	};

	vector_data() = default;
	vector_data(const vector<value_type, size - 1>& v, const value_type& n)
	{
		std::copy(v.data, v.data + (size - 1), data);
		data[size - 1] = n;
	}
	vector_data(const value_type& x, const value_type& y, const value_type& z) :
		x(x),
		y(y),
		z(z)
	{

	}
};
template<typename vTy>
struct vector_data<vTy, 4>
{
	typedef vTy value_type;
	static constexpr size_t size = 4;
	union
	{
		value_type data[size];
		struct
		{
			value_type x;
			value_type y;
			value_type z;
			value_type t;
		};
		struct
		{
			value_type r;
			value_type g;
			value_type b;
			value_type a;
		};
	};

	vector_data() = default;
	vector_data(const vector<value_type, size - 1>& v, const value_type& n)
	{
		std::copy(v.data, v.data + (size - 1), data);
		data[size - 1] = n;
	}	
	vector_data(const value_type& x, const value_type& y, const value_type& z, const value_type& t) :
		x(x),
		y(y),
		z(z),
		t(t)
	{

	}
};

template<typename vTy, size_t N>
vector_data<vTy, N>::vector_data(const vector<value_type, size-1>& v, const value_type& n)
{
	std::copy(v.data, v.data + (size - 1), data);
	data[size - 1] = n;
}

template<typename vTy, size_t N>
vector<vTy, N> operator +(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] + b[i];
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator -(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] - b[i];
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator *(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] * b[i];
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator /(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] / b[i];
	return res;
}

template<typename vTy, size_t N>
vector<vTy, N> operator +(const vector<vTy, N>& a, const typename vector<vTy, N>::value_type b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] + b;
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator -(const vector<vTy, N>& a, const typename vector<vTy, N>::value_type b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] - b;
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator *(const vector<vTy, N>& a, const typename vector<vTy, N>::value_type b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] * b;
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator /(const vector<vTy, N>& a, const typename vector<vTy, N>::value_type b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a[i] / b;
	return res;
}

template<typename vTy, size_t N>
vector<vTy, N> operator +(const typename vector<vTy, N>::value_type a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a + b[i];
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator -(const typename vector<vTy, N>::value_type a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a - b[i];
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator *(const typename vector<vTy, N>::value_type a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a * b[i];
	return res;
}
template<typename vTy, size_t N>
vector<vTy, N> operator /(const typename vector<vTy, N>::value_type a, const vector<vTy, N>& b)
{
	vector<vTy, N> res;
	for (size_t i = 0; i < N; ++i)
		res[i] = a / b[i];
	return res;
}

template<typename vTy, size_t N>
vTy dot(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	vTy res = 0.0;
	for (size_t i = 0; i < N; ++i)
		res += a[i] * b[i];
	return res;
}
template<typename vTy, size_t N>
vTy sqrmagnitude(const vector<vTy, N>& v)
{
	return v.sqrmagnitude();
}
template<typename vTy, size_t N>
vTy magnitude(const vector<vTy, N>& v)
{
	return v.magnitude();
}

template<typename vTy, size_t N>
typename vector<vTy, N>::value_type vector<vTy, N>::magnitude() const
{
	return std::sqrt(sqrmagnitude());
}
template<typename vTy, size_t N>
typename vector<vTy, N>::value_type vector<vTy, N>::sqrmagnitude() const
{
	return dot(*this, *this);
}

template<typename vTy>
vector<vTy, 3> cross(const vector<vTy, 3>& a, const vector<vTy, 3>& b)
{
	return vector<vTy, 3>(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
template<typename vTy, size_t N>
//Returns the cosine of the angle
typename vector<vTy, N>::value_type cosangle(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	return dot(a, b) / (magnitude(a) * magnitude(b));
}
template<typename vTy, size_t N>
typename vector<vTy, N>::value_type angle(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	return acos(cosangle(a, b));
}
template<typename vTy>
inline vector<vTy, 3> rotate(const vector<vTy, 3>& v, const vector<vTy, 3>& axis, const typename vector<vTy, 3>::value_type& angle)
{
	//Rotates the vector using quaternion arithmetic
	using std::sin;
	using std::cos;
	typedef typename vector<vTy, 3>::value_type value_type;
	value_type Q1 = -cos(angle * 0.5);
	vector<vTy, 3> Q2 = axis * sin(angle * 0.5);
	value_type S1 = -dot(axis, v);
	vector<vTy, 3> S2 = Q1 * v + cross(Q2, v);
	return S1 * -Q2 + Q1 * S2 + cross(S2, -Q2);
}

template<size_t Nnew, typename vTy, size_t Nold>
inline vector<vTy, Nnew> subvec(const vector<vTy, Nold>& v, size_t offset = 0)
{
	return v.subvec<Nnew>(offset);
}

template<typename vTy, size_t N>
vTy distance(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	return magnitude(a - b);
}
template<typename vTy, size_t N>
vTy sqrdistance(const vector<vTy, N>& a, const vector<vTy, N>& b)
{
	return sqrmagnitude(a - b);
}

template<typename vTy, size_t N>
vector<vTy, N> normalize(const vector<vTy, N>& v)
{
	return v.normalized();
}

typedef vector<double, 2> vec2;
typedef vector<double, 3> vec3;
typedef vector<double, 4> vec4;

template<typename vTy, typename... vArgs>
vector<vTy, sizeof...(vArgs)+1> make_vector(const vTy& val, const vArgs&... args)
{
	return vector<vTy, sizeof...(vArgs)+1>({ val, args... });
}

typedef vec2 Vector2d;
typedef vec3 Vector3d;
typedef vec4 Vector4d;
typedef vector<float, 3> Colour;

#endif
