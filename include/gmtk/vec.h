#ifndef _GMTK_VEC_H_
#define _GMTK_VEC_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "util.h"
#include "angle.h"
#include <cmath>
#include <ostream>

//

namespace GMTK_NAMESPACE
{////

	//! A d-length vector of type T
	template <int d, typename T = float>
	struct vec
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		//! Array containing vector data
		T data[d];

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline vec()
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = static_cast<T>(0); }
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = *(list.begin() + i); }
		}

		//! Copy constructor
		inline vec(const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = v.data[i]; }
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T>& v)
		{
			GMTK_STATIC_ASSERT(d2 >= d);
			for(std::size_t i = 0; i < d; ++i) { data[i] = v.data[i]; }
		}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit inline vec(const vec<d, U>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = static_cast<T>(v[i]); }
		}

		//! Fill constructor
		explicit inline vec(const T& s)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = s; }
		}

		//! Array initializer
		explicit inline vec(const T* a)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = a[i]; }
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		inline T& operator[](const int i)
		{
			return data[i];
		}

		//! Vector const index operator
		inline const T& operator[](const int i) const
		{
			return data[i];
		}

		///////////////////////////
		//! ARITHMETIC OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		inline vec<d, T> operator - () const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = -data[i]; }
			return res;
		}
		//! Component-wise unary negation
		inline vec<d, T> operator ~ () const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = ~data[i]; }
			return res;
		}
		//! Vector assignment
		inline vec<d, T>& operator = (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] = v.data[i]; }
			return *this;
		}

		//! Component-wise vector multiplication
		inline vec<d, T> operator * (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] * v.data[i]; }
			return res;
		}
		//! Component-wise vector division
		inline vec<d, T> operator / (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] / v.data[i]; }
			return res;
		}
		//! Component-wise vector addition
		inline vec<d, T> operator + (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] + v.data[i]; }
			return res;
		}
		//! Component-wise vector subtraction
		inline vec<d, T> operator - (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] - v.data[i]; }
			return res;
		}
		//! Component-wise vector OR
		inline vec<d, T> operator | (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] | v.data[i]; }
			return res;
		}
		//! Component-wise vector AND
		inline vec<d, T> operator & (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] & v.data[i]; }
			return res;
		}
		//! Component-wise vector XOR
		inline vec<d, T> operator ^ (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] ^ v.data[i]; }
			return res;
		}
		//! Component-wise vector modulus
		inline vec<d, T> operator % (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] % v.data[i]; }
			return res;
		}
		//! Component-wise vector shift left
		inline vec<d, T> operator << (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] << v.data[i]; }
			return res;
		}
		//! Component-wise vector shift right
		inline vec<d, T> operator >> (const vec<d, T>& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] >> v.data[i]; }
			return res;
		}

		//! Component-wise scalar multiplication
		inline vec<d, T> operator * (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] * v; }
			return res;
		}
		//! Component-wise scalar division
		inline vec<d, T> operator / (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] / v; }
			return res;
		}
		//! Component-wise scalar addition
		inline vec<d, T> operator + (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] + v; }
			return res;
		}
		//! Component-wise scalar subtraction
		inline vec<d, T> operator - (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] - v; }
			return res;
		}
		//! Component-wise scalar OR
		inline vec<d, T> operator | (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] | v; }
			return res;
		}
		//! Component-wise scalar AND
		inline vec<d, T> operator & (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] & v; }
			return res;
		}
		//! Component-wise scalar XOR
		inline vec<d, T> operator ^ (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] ^ v; }
			return res;
		}
		//! Component-wise scalar modulus
		inline vec<d, T> operator % (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] % v; }
			return res;
		}
		//! Component-wise scalar shift left
		inline vec<d, T> operator << (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] << v; }
			return res;
		}
		//! Component-wise scalar shift right
		inline vec<d, T> operator >> (const T& v) const
		{
			vec<d, T> res;
			for(std::size_t i = 0; i < d; ++i) { res.data[i] = data[i] >> v; }
			return res;
		}

		//! Component-wise vector reference multiplication
		inline vec<d, T>& operator *= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] *= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference division
		inline vec<d, T>& operator /= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] /= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference addition
		inline vec<d, T>& operator += (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] += v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference subtraction
		inline vec<d, T>& operator -= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] -= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference OR
		inline vec<d, T>& operator |= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] |= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference AND
		inline vec<d, T>& operator &= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] &= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference XOR
		inline vec<d, T>& operator ^= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] ^= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference modulus
		inline vec<d, T>& operator %= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] %= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference shift left
		inline vec<d, T>& operator <<= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] <<= v.data[i]; }
			return *this;
		}
		//! Component-wise vector reference shift right
		inline vec<d, T>& operator >>= (const vec<d, T>& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] >>= v.data[i]; }
			return *this;
		}

		//! Component-wise scalar reference multiplication
		inline vec<d, T>& operator *= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] *= v; }
			return *this;
		}
		//! Component-wise scalar reference division
		inline vec<d, T>& operator /= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] /= v; }
			return *this;
		}
		//! Component-wise scalar reference addition
		inline vec<d, T>& operator += (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] += v; }
			return *this;
		}
		//! Component-wise scalar reference subtraction
		inline vec<d, T>& operator -= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] -= v; }
			return *this;
		}
		//! Component-wise scalar reference OR
		inline vec<d, T>& operator |= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] |= v; }
			return *this;
		}
		//! Component-wise scalar reference AND
		inline vec<d, T>& operator &= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] &= v; }
			return *this;
		}
		//! Component-wise scalar reference XOR
		inline vec<d, T>& operator ^= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] ^= v; }
			return *this;
		}
		//! Component-wise scalar reference modulus
		inline vec<d, T>& operator %= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] %= v; }
			return *this;
		}
		//! Component-wise scalar reference shift left
		inline vec<d, T>& operator <<= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] <<= v; }
			return *this;
		}
		//! Component-wise scalar reference shift right
		inline vec<d, T>& operator >>= (const T& v)
		{
			for(std::size_t i = 0; i < d; ++i) { data[i] >>= v; }
			return *this;
		}

		//! Component-wise equality comparison
		inline bool operator == (const vec<d, T>& v) const
		{
			bool r = true;
			for(std::size_t i = 0; i < d; ++i) { r &= data[i] == v.data[i]; }
			return r;
		}
		//! Component-wise inequality comparison
		inline bool operator != (const vec<d, T>& v) const
		{
			bool r = true;
			for(std::size_t i = 0; i < d; ++i) { r |= data[i] != v.data[i]; }
			return r;
		}

	}; //! struct vec

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <int d, typename T = float>
	inline std::ostream& operator<<(std::ostream& os, const vec<d, T>& v)
	{
		os << "| ";
		for(std::size_t i = 0; i < d; ++i) { os << v.data[i] << ' '; }
		os << "|";
		return os;
	}

	//! Scalar-Vector multiplication
	template <int d, typename T = float>
	inline vec<d, T> operator*(const T& l, const vec<d, T>& r)
	{
		vec<d, T> res;
		for(std::size_t i = 0; i < d; ++i) { res.data[i] = l * r[i]; }
		return res;
	}

	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Calculates the dot or scalar product of two vectors
	template <int d, typename T = float>
	inline T dot(const vec<d, T>& l, const vec<d, T>& r)
	{
		T res = 0;
		for(std::size_t i = 0; i < d; ++i) { res += l[i] * r[i]; }
		return res;
	}

	//! Calculates the angle between two vectors
	template <int d, typename T = float>
	inline ang<T> angle(const vec<d, T>& l, const vec<d, T>& r)
	{
		T dp = dot(l, r) / (magnitude(l) * magnitude(r));
		return radians(acos(dp));
	}

	//! Rotates the source vector around the ais vector by the specified angle
	template <int d, typename T = float>
	inline vec<d, T> rotatearound(const vec<d, T>& src, const vec<d, T>& axs, const ang<T>& dlt)
	{
		T ct = cos(dlt.radians());
		T st = sin(dlt.radians());
		return (src * ct) + (cross(axs, src) * st) + (axs * dot(axs, src)) * (1 - ct);
	}

	//! Projects a vector onto another vector
	template <int d, typename T = float>
	inline vec<d, T> project(const vec<d, T>& l, const vec<d, T>& r)
	{
		vec<d, T> normal = normalize(r);
		return normal * dot(l, normal);
	}

	//! Calculates the cross product of two vectors
	template <typename T = float>
	inline T cross(const vec<2, T>& l, const vec<2, T>& r)
	{
		return (l.data[0] * r.data[1]) - (l.data[0] * r.data[1]);
	}

	//! Calculates the cross product of two vectors
	template <typename T = float>
	inline vec<3, T> cross(const vec<3, T>& l, const vec<3, T>& r)
	{
		vec<3, T> res;
		res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
		res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
		res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
		return res;
	}

	//! Calculates the cross product of two vectors
	template <typename T = float>
	inline vec<4, T> cross(const vec<4, T>& l, const vec<4, T>& r)
	{
		vec<4, T> res;
		res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
		res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
		res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
		res.data[3] = static_cast<T>(0);
		return res;
	}

	//! Returns length squared of vector
	template <int d, typename T = float>
	inline T lengthsq(const vec<d, T>& v)
	{
		T res = 0;
		for(std::size_t i = 0; i < d; ++i) { res += sq(v.data[i]); }
		return res;
	}

	//! Returns length of vector, or sqrt(lengthsq)
	template <int d, typename T = float>
	inline T length(const vec<d, T>& v)
	{
		T res = 0;
		for(std::size_t i = 0; i < d; ++i) { res += sq(v.data[i]); }
		return sqrt(res);
	}

	//! Returns magnitude of vector, or length
	template <int d, typename T = float>
	inline T magnitude(const vec<d, T>& v)
	{
		return length(v);
	}

	//! Normalizes vector so it is a unit vector
	template <int d, typename T = float>
	inline vec<d, T> normalize(const vec<d, T>& v)
	{
		return v / length(v);
	}

	//! Returns a component-wise minimum of two vectors
	template <int d, typename T = float>
	inline vec<d, T> min(const vec<d, T>& l, const vec<d, T>& r)
	{
		vec<d, T> res;
		for(std::size_t i = 0; i < d; ++i) { res.data[i] = (l[i] < r[i]) ? l[i] : r[i]; }
		return res;
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template <int d, typename T = float>
	inline vec<d, T> min(const vec<d, T>& l, const T& r)
	{
		vec<d, T> res;
		for(std::size_t i = 0; i < d; ++i) { res.data[i] = (l[i] < r) ? l[i] : r; }
		return res;
	}

	//! Returns a component-wise minimum of two vectors
	template <int d, typename T = float>
	inline vec<d, T> max(const vec<d, T>& l, const vec<d, T>& r)
	{
		vec<d, T> res;
		for(std::size_t i = 0; i < d; ++i) { res.data[i] = (l[i] > r[i]) ? l[i] : r[i]; }
		return res;
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template <int d, typename T = float>
	inline vec<d, T> max(const vec<d, T>& l, const T& r)
	{
		vec<d, T> res;
		for(std::size_t i = 0; i < d; ++i) { res.data[i] = (l[i] > r) ? l[i] : r; }
		return res;
	}

	//! Clamps the value of a vector between a min and max vector
	template <int d, typename T = float>
	inline vec<d, T> clamp(const vec<d, T>& v, const vec<d, T>& minV, const vec<d, T>& maxV)
	{
		return min(max(v, minV), maxV);
	}

	//! Clamps the value of a vector between a min and max scalar
	template <int d, typename T = float>
	inline vec<d, T> clamp(const vec<d, T>& v, const T& minV, const T& maxV)
	{
		return min(max(v, minV), maxV);
	}

	//! Computes the distance between two vectors
	template <int d, typename T = float>
	inline T distance(const vec<d, T>& l, const vec<d, T>& r)
	{
		return length(l - r);
	}

	//! Computes the distance squared between two vectors
	template <int d, typename T = float>
	inline T distancesq(const vec<d, T>& l, const vec<d, T>& r)
	{
		return lengthsq(l - r);
	}

	//! Faces a normal forward according to the dot product of nRef and i
	template<int d, typename T = float>
	inline vec<d, T> faceforward(const vec<d, T>& n, const vec<d, T>& i, const vec<d, T>& nRef)
	{
		return (dot(nRef, i) < 0) ? n : -n;
	}

	//! Computes the reflection of vector v acording to the plane of normal vector 'n'
	template<int d, typename T = float>
	inline vec<d, T> reflect(const vec<d, T>& v, const vec<d, T>& n)
	{
		return v - 2.0f * dot(n, v) * n;
	}

	//! GLSL refraction function
	template<int d, typename T = float>
	inline vec<d, T> refract(const vec<d, T>& v, const vec<d, T>& n, float r)
	{
		float dir = static_cast<T>(1.0) - r * r * (static_cast<T>(1.0) - dot(n, v) * dot(n, v));
		if (dir < static_cast<T>(0.0)) return vec<d, T>(static_cast<T>(0.0)); //! total internal reflection
		return r * v - (r * dot(n, v) + sqrt(dir)) * n;
	}

	//! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
	template<int d, typename T = float>
	inline vec<d + 1, T> affine(const vec<d, T>& v)
	{
		vec<d + 1, T> res;
		for(std::size_t i = 0; i < d; ++i) { res[i] = v[i]; }
		res[d] = static_cast<T>(1);
		return res;
	}

	//! Point vector constructor (xyz,1)
	template<typename T = float>
	inline vec<4, T> point(const vec<3, T>& xyz)
	{
		return vec<4, T>(xyz.data[0], xyz.data[1], xyz.data[2], 1);
	}

	//! Point vector constructor (x,y,z,1)
	template<typename T = float>
	inline vec<4, T> point(const T& x, const T& y, const T& z)
	{
		return vec<4, T>(x, y, z, 1);
	}

	//! Returns whether vector is NaN
	template<int d, typename T = float>
	inline bool isnan(const vec<d, T>& v)
	{
		bool r = true;
		for(std::size_t i = 0; i < d; ++i) { r &= std::isnan(v[i]); }
		return r;
	}

	//! Returns whether vector is inf
	template<int d, typename T = float>
	inline bool isinf(const vec<d, T>& v)
	{
		bool r = true;
		for(std::size_t i = 0; i < d; ++i) { r &= std::isinf(v[i]); }
		return r;
	}

	//! Relative equality (for floating-point vectors)
	template<int d, typename T = float>
	inline bool req(const vec<d, T>& a, const vec<d, T>& b, T rng = 1e-8)
	{
		bool r = true;
		for(std::size_t i = 0; i < d; ++i) { r &= req(a[i], b[i], rng); }
		return r;
	}

}////

//

#pragma warning(pop)

//

#endif //_GMTK_VEC