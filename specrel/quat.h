#ifndef SPECREL_QUAT_
#define SPECREL_QUAT_H

#include "vector.h"

template<typename vTy>
struct quaternion
{
	typedef vTy value_type;
	typedef vector<value_type, 3> vector_type;
	union
	{
		struct
		{
			union
			{
				vector_type v;
				struct
				{
					value_type x;
					value_type y;
					value_type z;
				};
			};

			value_type w;
		};
		value_type data[4];
	};

	quaternion() { }
	quaternion(const vector_type& v, value_type w) :
		v(v),
		w(w)
	{

	}
	quaternion(value_type x, value_type y, value_type z, value_type w) :
		v(x, y, z),
		w(w)
	{

	}

	value_type& operator[](size_t idx)
	{
		return data[idx];
	}
	const value_type& operator[](size_t idx) const
	{
		return data[idx];
	}

	value_type sqrmagnitude() const
	{
		return dot(v, v) + w * w;
	}
	value_type magnitude() const
	{
		return std::sqrt(sqrmagnitude());
	}

	void normalize()
	{
		value_type q = 1.0 / magnitude();
		*this *= q;
	}
	quaternion normalized() const
	{
		value_type q = 1.0 / magnitude();
		return quaternion(v * q, w * q);
	}

	quaternion conjugate() const
	{
		return quaternion(-v, w);
	}

	quaternion& operator +=(value_type val)
	{
		v += val;
		w += val;
		return *this;
	}
	quaternion& operator -=(value_type val)
	{
		v -= val;
		w -= val;
		return *this;
	}
	quaternion& operator *=(value_type val)
	{
		v *= val;
		w *= val;
		return *this;
	}
	quaternion& operator /=(value_type val)
	{
		v /= val;
		w /= val;
		return *this;
	}
};

template<typename vTy>
quaternion<vTy> operator *(const quaternion<vTy>& a, const quaternion<vTy>& b)
{
	return quaternion<vTy>(aw * b.v + b.w * a.v + cross(a.v, b.v), a.w * b.w - dot(a.v, b.v));
}
template<typename vTy>
quaternion<vTy> operator /(const quaternion<vTy>& a, const quaternion<vTy>& b)
{
	return quaternion<vTy>(-cross(a.v, b.v) - a.w * b.v + b.w * a.v, a.w * b.w + dot(a.v, b.v));
}

template<typename vTy>
typename quaternion<vTy>::vector_type operator *(const quaternion<vTy>& a, const typename quaternion<vTy>::vector_type& b)
{
	return (a * quaternion<vTy>(b, 0)).v;
}

template<typename vTy>
quaternion<vTy> operator +(const quaternion<vTy>& a, const vTy& b)
{
	return quaternion<vTy>(a.v + b.v, a.w + b.w);
}
template<typename vTy>
quaternion<vTy> operator -(const quaternion<vTy>& a, const vTy& b)
{
	return quaternion<vTy>(a.v - b.v, a.w - b.w);
}
template<typename vTy> 
quaternion<vTy> operator *(const quaternion<vTy>& a, const vTy& b)
{
	return quaternion<vTy>(a.v * b.v, a.w * b.w);
}
template<typename vTy>
quaternion<vTy> operator /(const quaternion<vTy>& a, const vTy& b)
{
	return quaternion<vTy>(a.v / b.v, a.w / b.w);
}

template<typename vTy>
auto conjugate(const quaternion<vTy>& q)
{
	return q.conjugate();
}
template<typename vTy>
auto sqrmagnitude(const quaternion<vTy>& q)
{
	return q.sqrmagnitude();
}
template<typename vTy>
auto magnitude(const quaternion<vTy>& q)
{
	return q.magnitude();
}

typedef quaternion<double> Quaterniond;

#endif
