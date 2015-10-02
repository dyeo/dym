#ifndef _GMATH_VEC_H_
#define _GMATH_VEC_H_

//

#include "util.h"
#include <math.h>
#include <ostream>

//

// Unrolls a component-wise vector manipulation for generic implementation
#define GMATH_VEC_LOOP(oper) GMATH_UNROLL_LOOP(i,d,oper)

//

#define GMATH_VEC_OPERATOR(oper) { vec<T,d> res; GMATH_VEC_LOOP(res[i] = oper); return res; }

//

#define GMATH_VEC_REF_OPERATOR(oper) { GMATH_VEC_LOOP(oper); return *this; }

//

namespace gmath
{////

	
	template <typename T, int d>
	// A d-length vector of type T
	struct vec
	{
		//////////////////
		// DATA MEMBERS //
		//////////////////
		
		// Expose vector type
		typedef T type;

		// Array containing vector data
		T data[d];

		//////////////////
		// CONSTRUCTORS //
		//////////////////
		
		// Default constructor
		inline vec() {
			GMATH_VEC_LOOP(data[i] = static_cast<T>(0));
		}

		// Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMATH_VEC_LOOP(data[i] = *(list.begin() + i));
		}

		// Copy constructor
		inline vec(const vec<T, d>& v) {
			GMATH_VEC_LOOP(data[i] = v.data[i]);
		}

		// Explicit type-conversion copy constructor
		template<typename U> explicit inline vec(const vec<U, d>& v) {
			GMATH_VEC_LOOP(data[i] = static_cast<T>(v[i]));
		}

		// Fill constructor
		explicit inline vec(const T& s) {
			GMATH_VEC_LOOP(data[i] = s);
		}

		// Array initializer
		explicit inline vec(const T* a) {
			GMATH_VEC_LOOP(data[i] = a[i]);
		}

		//////////////////////
		// ACCESS OPERATORS //
		//////////////////////

		// Vector index operator
		inline T& operator[](const int i) {
			return data[i];
		}

		// Vector const index operator
		inline const T& operator[](const int i) const {
			return data[i];
		}

		//////////////////////////
		// RIGHT-HAND OPERATORS //
		//////////////////////////

		// Returns a negative vector
		inline vec<T, d> operator-() const {
			GMATH_VEC_OPERATOR(-data[i]);
		}

		// Component-wise vector multiplication
		inline vec<T, d> operator*(const vec<T, d>& v) const {
			GMATH_VEC_OPERATOR(data[i] * v.data[i]);
		}

		// Component-wise vector division
		inline vec<T, d> operator/(const vec<T, d>& v) const {
			GMATH_VEC_OPERATOR(data[i] / v.data[i]);
		}

		// Component-wise vector addition
		inline vec<T, d> operator+(const vec<T, d>& v) const {
			GMATH_VEC_OPERATOR(data[i] + v.data[i]);
		}

		// Component-wise vector subtraction
		inline vec<T, d> operator-(const vec<T, d>& v) const {
			GMATH_VEC_OPERATOR(data[i] - v.data[i]);
		}

		// Component-wise vector reference multiplication
		inline vec<T, d>& operator*=(const vec<T, d>& v) {
			GMATH_VEC_REF_OPERATOR(data[i] *= v.data[i]);
		}

		// Component-wise vector reference division
		inline vec<T, d>& operator/=(const vec<T, d>& v) {
			GMATH_VEC_REF_OPERATOR(data[i] /= v.data[i]);
		}

		// Component-wise vector reference addition
		inline vec<T, d>& operator+=(const vec<T, d>& v) {
			GMATH_VEC_REF_OPERATOR(data[i] += v.data[i]);
		}

		// Component-wise vector reference subtraction
		inline vec<T, d>& operator-=(const vec<T, d>& v) {
			GMATH_VEC_REF_OPERATOR(data[i] -= v.data[i]);
		}

		// Component-wise scalar multiplication
		inline vec<T, d> operator*(const T& s) const {
			GMATH_VEC_OPERATOR(data[i] * s);
		}

		// Component-wise scalar division
		inline vec<T, d> operator/(const T& s) const {
			GMATH_VEC_OPERATOR(data[i] / s);
		}

		// Component-wise scalar addition
		inline vec<T, d> operator+(const T& s) const {
			GMATH_VEC_OPERATOR(data[i] + s);
		}

		// Component-wise scalar subtraction
		inline vec<T, d> operator-(const T& s) const {
			GMATH_VEC_OPERATOR(data[i] - s);
		}

		// Component-wise scalar reference multiplication
		inline vec<T, d>& operator*=(const T& s) {
			GMATH_VEC_REF_OPERATOR(data[i] *= s);
		}

		// Component-wise scalar reference division
		inline vec<T, d>& operator/=(const T& s) {
			GMATH_VEC_REF_OPERATOR(data[i] /= s);
		}

		// Component-wise scalar reference addition
		inline vec<T, d>& operator+=(const T& s) {
			GMATH_VEC_REF_OPERATOR(data[i] += s);
		}

		// Component-wise scalar reference subtraction
		inline vec<T, d>& operator-=(const T& s) {
			GMATH_VEC_REF_OPERATOR(data[i] -= s);
		}

	}; // struct vec

	/////////////////////
	// MISC. OPERATORS //
	/////////////////////

	template <typename T, int d>
	inline std::ostream& operator<<(std::ostream& os, const vec<T, d>& v)
	{
		os << "| ";
		GMATH_VEC_LOOP(os << v.data[i] << ' ');
		os << "|";
		return os;
	}

	////////////////////
	// FREE FUNCTIONS //
	////////////////////

	template <typename T, int d>
	// Calculates the dot or scalar product of two vectors
	inline T dot(const vec<T, d>& l, const vec<T, d>& r)
	{
		T res = 0;
		GMATH_VEC_LOOP(res += l[i] * r[i]);
		return res;
	}

	template <typename T>
	// Calculates the cross product of two vectors
	inline T cross(const vec<T, 2>& l, const vec<T, 2>& r)
	{
		return (l.data[0] * r.data[1]) - (l.data[0] * r.data[1]);
	}

	template <typename T>
	// Calculates the cross product of two vectors
	inline vec<T, 3> cross(const vec<T, 3>& l, const vec<T, 3>& r)
	{
		vec<T, 3> res;
		res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
		res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
		res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
		return res;
	}

	template <typename T>
	// Calculates the cross product of two vectors
	inline vec<T, 4> cross(const vec<T, 4>& l, const vec<T, 4>& r)
	{
		vec<T, 4> res;
		res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
		res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
		res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
		res.data[3] = static_cast<T>(0);
		return res;
	}

	template <typename T, int d>
	// Returns length squared of vector
	inline T lengthsq(const vec<T, d>& v)
	{
		T res = 0;
		GMATH_UNROLL_LOOP(i, d, res += sq(v.data[i]));
		return res;
	}

	template <typename T, int d>
	// Returns length of vector, or sqrt(lengthsq)
	inline T length(const vec<T, d>& v)
	{
		T res = 0;
		GMATH_UNROLL_LOOP(i, d, res += sq(v.data[i]));
		return sqrt(res);
	}

	template <typename T, int d>
	// Normalizes vector so it is a unit vector
	inline vec<T, d> normalize(const vec<T, d>& v)
	{
		return v * gmath::invsqrt(lengthsq(v));
	}

	template <typename T, int d>
	// Returns a component-wise minimum of two vectors
	inline vec<T, d> min(const vec<T, d>& l, const vec<T, d>& r)
	{
		GMATH_VEC_OPERATOR((l[i] < r[i]) ? l[i] : r[i]);
	}

	template <typename T, int d>
	// Returns a component-wise maximum of a vector and a scalar
	inline vec<T, d> min(const vec<T, d>& l, const T& r)
	{
		GMATH_VEC_OPERATOR((l[i] < r) ? l[i] : r);
	}

	template <typename T, int d>
	// Returns a component-wise minimum of two vectors
	inline vec<T, d> max(const vec<T, d>& l, const vec<T, d>& r)
	{
		GMATH_VEC_OPERATOR((l[i] > r[i]) ? l[i] : r[i]);
	}

	template <typename T, int d>
	// Returns a component-wise maximum of a vector and a scalar
	inline vec<T, d> max(const vec<T, d>& l, const T& r)
	{
		GMATH_VEC_OPERATOR((l[i] > r) ? l[i] : r);
	}

	template <typename T, int d>
	// Clamps the value of a vector between a min and max vector
	inline vec<T, d> clamp(const vec<T, d>& v, const vec<T, d>& minV, const vec<T, d>& maxV)
	{
		return min(max(v, minV), maxV);
	}

	template <typename T, int d>
	// Clamps the value of a vector between a min and max scalar
	inline vec<T, d> clamp(const vec<T, d>& v, const T& minV, const T& maxV)
	{
		return min(max(v, minV), maxV);
	}

	template <typename T, int d>
	// Computes the distance between two vectors
	inline T distance(const vec<T, d>& l, const vec<T, d>& r)
	{
		return length(l - r);
	}

	template <typename T, int d>
	// Computes the distance squared between two vectors
	inline T distancesq(const vec<T, d>& l, vec<T, d>& r)
	{
		return lengthsq(l - r);
	}

	template<typename T, int d>
	// Faces a normal forward according to the dot product of nRef and i
	inline vec<T, d> faceforward(const vec<T, d>& n, const vec<T, d>& i, const vec<T, d>& nRef)
	{
		return (dot(nRef, i) < 0) ? n : -n;
	}
	
	template<typename T, int d>
	// Computes the reflection of vector v acording to the plane of normal vector 'n'
	inline vec<T, d> reflect(const vec<T, d>& v, const vec<T, d>& n)
	{
		return v - 2.0f * dot(n, v) * n;
	}

	template<typename T, int d>
	// GLSL refraction function
	inline vec<T, d> refract(const vec<T, d>& v, const vec<T, d>& n, float r)
	{
		float dir = 1.0 - r * r * (1.0 - dot(n, v) * dot(n, v));
		if (dir < 0.0) return vec<T, d>(0.0); // total internal reflection
		return r * v - (r * dot(n, v) + sqrt(dir)) * n;
	}

	template<typename T, int d>
	// Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
	inline vec<T, d + 1> affine(const vec<T, d>&v)
	{
		vec<T, d + 1> res;
		GMATH_VEC_LOOP(res[i] = v[i]);
		res[d] = static_cast<T>(1);
		return res;
	}

	//heh

}////

//

#endif //_GMATH_VEC