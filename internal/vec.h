#ifndef _GMTK_VEC_H_
#define _GMTK_VEC_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "..\util.h"
#include <math.h>
#include <ostream>

//

#define GMTK_VEC_LOOP(oper) GMTK_UNROLL_LOOP(i,d,oper)

//

#define GMTK_VEC_UN_OP(op) \
	inline vec<d, T> operator op () const \
	{ vec<d, T> res; GMTK_VEC_LOOP(res.data[i] = op data[i]); return res; }

#define GMTK_VEC_VEC_OP(op) \
	inline vec<d, T> operator op (const vec<d, T>& v) const \
	{ vec<d, T> res; GMTK_VEC_LOOP(res.data[i] = data[i] op v.data[i]); return res; }

#define GMTK_VEC_SCL_OP(op) \
	inline vec<d, T> operator op (const T& v) const \
	{ vec<d, T> res; GMTK_VEC_LOOP(res.data[i] = data[i] op v); return res; }

#define GMTK_VEC_VEC_ROP(op) \
	inline vec<d, T>& operator op (const vec<d, T>& v) \
	{ GMTK_VEC_LOOP(data[i] op v.data[i]); return *this; }

#define GMTK_VEC_SCL_ROP(op) \
	inline vec<d, T>& operator op (const T& v) \
	{ GMTK_VEC_LOOP(data[i] op v); return *this; }

//

#define GMTK_VEC_OPERATION(oper) { vec<d, T> res; GMTK_VEC_LOOP(res.data[i] = oper); return res; }

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
		inline vec() {
			GMTK_VEC_LOOP(data[i] = static_cast<T>(0));
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC_LOOP(data[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline vec(const vec<d, T>& v) {
			GMTK_VEC_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= d);
			GMTK_VEC_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<d, U>& v) {
			GMTK_VEC_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC_LOOP(data[i] = a[i]);
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		inline T& operator[](const int i) {
			return data[i];
		}

		//! Vector const index operator
		inline const T& operator[](const int i) const {
			return data[i];
		}

		///////////////////////////
		//! ARITHMETIC OPERATORS //
		///////////////////////////
		
		//! Component-wise unary negation
		GMTK_VEC_UN_OP(-)
		//! Component-wise unary negation
		GMTK_VEC_UN_OP(~)
		//! Vector assignment
		GMTK_VEC_VEC_ROP(=)
		
		//! Component-wise vector multiplication
		GMTK_VEC_VEC_OP(*)		
		//! Component-wise vector division
		GMTK_VEC_VEC_OP(/)		
		//! Component-wise vector addition
		GMTK_VEC_VEC_OP(+)		
		//! Component-wise vector subtraction
		GMTK_VEC_VEC_OP(-)		
		//! Component-wise vector OR
		GMTK_VEC_VEC_OP(|)
		//! Component-wise vector AND
		GMTK_VEC_VEC_OP(&)
		//! Component-wise vector XOR
		GMTK_VEC_VEC_OP(^)
		//! Component-wise vector modulus
		GMTK_VEC_VEC_OP(%)
		//! Component-wise vector shift left
		GMTK_VEC_VEC_OP(<<)
		//! Component-wise vector shift right
		GMTK_VEC_VEC_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_VEC_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_VEC_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_VEC_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_VEC_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_VEC_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_VEC_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_VEC_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_VEC_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_VEC_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_VEC_SCL_OP(>>)
						
		//! Component-wise vector reference multiplication
		GMTK_VEC_VEC_ROP(*=)		
		//! Component-wise vector reference division
		GMTK_VEC_VEC_ROP(/=)		
		//! Component-wise vector reference addition
		GMTK_VEC_VEC_ROP(+=)		
		//! Component-wise vector reference subtraction
		GMTK_VEC_VEC_ROP(-=)
		//! Component-wise vector reference OR
		GMTK_VEC_VEC_ROP(|=)
		//! Component-wise vector reference AND
		GMTK_VEC_VEC_ROP(&=)
		//! Component-wise vector reference XOR
		GMTK_VEC_VEC_ROP(^=)
		//! Component-wise vector reference modulus
		GMTK_VEC_VEC_ROP(%=)
		//! Component-wise vector reference shift left
		GMTK_VEC_VEC_ROP(<<=)
		//! Component-wise vector reference shift right
		GMTK_VEC_VEC_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_VEC_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_VEC_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_VEC_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_VEC_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_VEC_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_VEC_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_VEC_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_VEC_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_VEC_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_VEC_SCL_ROP(>>=)

	}; //! struct vec

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <int d, typename T>
	inline std::ostream& operator<<(std::ostream& os, const vec<d, T>& v)
	{
		os << "| ";
		GMTK_VEC_LOOP(os << v.data[i] << ' ');
		os << "|";
		return os;
	}

	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Calculates the dot or scalar product of two vectors
	template <int d, typename T>
	inline T dot(const vec<d, T>& l, const vec<d, T>& r)
	{
		T res = 0;
		GMTK_VEC_LOOP(res += l[i] * r[i]);
		return res;
	}

	//! Calculates the angle between two vectors
	template <int d, typename T>
	inline ang<T> angle(const vec<d, T> &l, const vec<d, T> &r)
	{
		T dp = dot(l, r) / (magnitude(l) * magnitude(r));
		return radians(acos(dp));
	}

	//! Rotates the source vector around the ais vector by the specified angle
	template <int d, typename T>
	inline vec<d, T> rotatearound(const vec<d, T> &src, const vec<d, T> &axs, const ang<T> &dlt)
	{
		T ct = cos(dlt.radians());
		T st = sin(dlt.radians());
		return (src * ct) + (cross(axs, src) * st) + (axs * dot(axs, src)) * (1 - ct);
	}
		
	//! Projects a vector onto another vector
	template <int d, typename T>
	inline vec<d, T> project(const vec<d, T> &l, const vec<d, T> &r)
	{
		vec<d, T> normal = normalize(r);
		return normal * dot(l, normal);
	}

	//! Calculates the cross product of two vectors
	template <typename T>
	inline T cross(const vec<2, T>& l, const vec<2, T>& r)
	{
		return (l.data[0] * r.data[1]) - (l.data[0] * r.data[1]);
	}

	//! Calculates the cross product of two vectors
	template <typename T>
	inline vec<3, T> cross(const vec<3, T>& l, const vec<3, T>& r)
	{
		vec<3, T> res;
		res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
		res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
		res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
		return res;
	}

	//! Calculates the cross product of two vectors
	template <typename T>
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
	template <int d, typename T>
	inline T lengthsq(const vec<d, T>& v)
	{
		T res = 0;
		GMTK_UNROLL_LOOP(i, d, res += sq(v.data[i]));
		return res;
	}

	//! Returns length of vector, or sqrt(lengthsq)
	template <int d, typename T>
	inline T length(const vec<d, T>& v)
	{
		T res = 0;
		GMTK_UNROLL_LOOP(i, d, res += sq(v.data[i]));
		return sqrt(res);
	}

	//! Returns magnitude of vector, or length
	template <int d, typename T>
	inline T magnitude(const vec<d, T>& v)
	{
		return length(v);
	}

	//! Normalizes vector so it is a unit vector
	template <int d, typename T>
	inline vec<d, T> normalize(const vec<d, T>& v)
	{
		return v / length(v);
	}

	//! Returns a component-wise minimum of two vectors
	template <int d, typename T>
	inline vec<d, T> min(const vec<d, T>& l, const vec<d, T>& r) 
		GMTK_VEC_OPERATION((l[i] < r[i]) ? l[i] : r[i])

	//! Returns a component-wise maximum of a vector and a scalar
	template <int d, typename T>
	inline vec<d, T> min(const vec<d, T>& l, const T& r) 
		GMTK_VEC_OPERATION((l[i] < r) ? l[i] : r)

	//! Returns a component-wise minimum of two vectors
	template <int d, typename T>
	inline vec<d, T> max(const vec<d, T>& l, const vec<d, T>& r) 
		GMTK_VEC_OPERATION((l[i] > r[i]) ? l[i] : r[i])

	//! Returns a component-wise maximum of a vector and a scalar
	template <int d, typename T>
	inline vec<d, T> max(const vec<d, T>& l, const T& r) 
		GMTK_VEC_OPERATION((l[i] > r) ? l[i] : r)

	//! Clamps the value of a vector between a min and max vector
	template <int d, typename T>
	inline vec<d, T> clamp(const vec<d, T>& v, const vec<d, T>& minV, const vec<d, T>& maxV)
	{
		return min(max(v, minV), maxV);
	}

	//! Clamps the value of a vector between a min and max scalar
	template <int d, typename T>
	inline vec<d, T> clamp(const vec<d, T>& v, const T& minV, const T& maxV)
	{
		return min(max(v, minV), maxV);
	}

	//! Computes the distance between two vectors
	template <int d, typename T>
	inline T distance(const vec<d, T>& l, const vec<d, T>& r)
	{
		return length(l - r);
	}

	//! Computes the distance squared between two vectors
	template <int d, typename T>
	inline T distancesq(const vec<d, T>& l, vec<d, T>& r)
	{
		return lengthsq(l - r);
	}

	//! Faces a normal forward according to the dot product of nRef and i
	template<int d, typename T>
	inline vec<d, T> faceforward(const vec<d, T>& n, const vec<d, T>& i, const vec<d, T>& nRef)
	{
		return (dot(nRef, i) < 0) ? n : -n;
	}

	//! Computes the reflection of vector v acording to the plane of normal vector 'n'
	template<int d, typename T>
	inline vec<d, T> reflect(const vec<d, T>& v, const vec<d, T>& n)
	{
		return v - 2.0f * dot(n, v) * n;
	}

	//! GLSL refraction function
	template<int d, typename T>
	inline vec<d, T> refract(const vec<d, T>& v, const vec<d, T>& n, float r)
	{
		float dir = static_cast<T>(1.0) - r * r * (static_cast<T>(1.0) - dot(n, v) * dot(n, v));
		if (dir < static_cast<T>(0.0)) return vec<d, T>(static_cast<T>(0.0)); //! total internal reflection
		return r * v - (r * dot(n, v) + sqrt(dir)) * n;
	}

	//! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
	template<int d, typename T>
	inline vec<d + 1, T> affine(const vec<d, T>&v)
	{
		vec<d + 1, T> res;
		GMTK_VEC_LOOP(res[i] = v[i]);
		res[d] = static_cast<T>(1);
		return res;
	}

	//! Point vector constructor (xyz,1)
	template<typename T = float>
	inline vec<4, T> point(const vec<3, T> &xyz)
	{
		return vec<4, T>(xyz.data[0], xyz.data[1], xyz.data[2], 1);
	}

	//! Point vector constructor (x,y,z,1)
	template<typename T = float>
	inline vec<4, T> point(const T &x, const T &y, const T &z)
	{
		return vec<4, T>(x, y, z, 1);
	}

}////

//

#undef GMTK_VEC_LOOP
#undef GMTK_VEC_UN_OP
#undef GMTK_VEC_VEC_OP
#undef GMTK_VEC_SCL_OP
#undef GMTK_VEC_VEC_ROP
#undef GMTK_VEC_SCL_ROP
#undef GMTK_VEC_OPERATION

//

#pragma warning(pop)

//

#endif //_GMTK_VEC