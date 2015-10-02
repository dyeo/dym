#ifndef _GMTK_VEC3_H_
#define _GMTK_VEC3_H_

//

#include "vec.h"

//

#define GMTK_VEC3_LOOP(oper) GMTK_UNROLL_LOOP(i,3,oper)

#define GMTK_VEC3_OPERATOR(oper) \
		{ vec<T,3> res; \
		GMTK_VEC3_LOOP(res[i] = oper); \
		return res; }

#define GMTK_VEC3_REF_OPERATOR(oper) \
		{ GMTK_VEC3_LOOP(oper); \
		return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec < T, 3 >
	{
		union
		{
			struct { T data[3]; };
			struct { T x, y, z; };
			struct { vec<T, 2> xy; };
		};

		// Initialize vec3 with three values
		inline vec(const T& s0, const T& s1, const T& s2)
		{
			data[0] = s0;
			data[1] = s1;
			data[2] = s2;
		}

		// Initialize vec3 with a vec2 and a third value
		inline vec(const vec<T, 2>& v01, const T& s2)
		{
			data[0] = v01.data[0];
			data[1] = v01.data[1];
			data[2] = s2;
		}

		// Default constructor
		inline vec() {
		}

		// Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC_LOOP(data[i] = *(list.begin() + i));
		}

		// Copy constructor
		inline vec(const vec<T, 3>& v) {
			GMTK_VEC3_LOOP(data[i] = v.data[i]);
		}

		// Explicit type-conversion copy constructor
		template<typename U> explicit inline vec(const vec<U, 2>& v) {
			GMTK_VEC3_LOOP(data[i] = static_cast<T>(v[i]));
		}

		// Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC3_LOOP(data[i] = s);
		}

		// Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC3_LOOP(data[i] = a[i]);
		}

		// Vector index operator
		inline T& operator[](const int i) {
			return data[i];
		}

		// Vector const index operator
		inline const T& operator[](const int i) const {
			return data[i];
		}

		// Returns a negative vector
		inline vec<T, 3> operator-() const {
			GMTK_VEC3_OPERATOR(-data[i]);
		}

		// Component-wise vector multiplication
		inline vec<T, 3> operator*(const vec<T, 3>& v) const {
			GMTK_VEC3_OPERATOR(data[i] * v.data[i]);
		}

		// Component-wise vector division
		inline vec<T, 3> operator/(const vec<T, 3>& v) const {
			GMTK_VEC3_OPERATOR(data[i] / v.data[i]);
		}

		// Component-wise vector addition
		inline vec<T, 3> operator+(const vec<T, 3>& v) const {
			GMTK_VEC3_OPERATOR(data[i] + v.data[i]);
		}

		// Component-wise vector subtraction
		inline vec<T, 3> operator-(const vec<T, 3>& v) const {
			GMTK_VEC3_OPERATOR(data[i] - v.data[i]);
		}

		// Component-wise vector reference multiplication
		inline vec<T, 3>& operator*=(const vec<T, 3>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] *= v.data[i]);
		}

		// Component-wise vector reference division
		inline vec<T, 3>& operator/=(const vec<T, 3>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] /= v.data[i]);
		}

		// Component-wise vector reference addition
		inline vec<T, 3>& operator+=(const vec<T, 3>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] += v.data[i]);
		}

		// Component-wise vector reference subtraction
		inline vec<T, 3>& operator-=(const vec<T, 3>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] -= v.data[i]);
		}

		// Component-wise scalar multiplication
		inline vec<T, 3> operator*(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] * s);
		}

		// Component-wise scalar division
		inline vec<T, 3> operator/(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] / s);
		}

		// Component-wise scalar addition
		inline vec<T, 3> operator+(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] + s);
		}

		// Component-wise scalar subtraction
		inline vec<T, 3> operator-(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] - s);
		}

		// Component-wise scalar reference multiplication
		inline vec<T, 3>& operator*=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] *= s);
		}

		// Component-wise scalar reference division
		inline vec<T, 3>& operator/=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] /= s);
		}

		// Component-wise scalar reference addition
		inline vec<T, 3>& operator+=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] += s);
		}

		// Component-wise scalar reference subtraction
		inline vec<T, 3>& operator-=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] -= s);
		}

	};

	typedef vec<float, 3> vec3, vec3f;
	typedef vec<double, 3> vec3d;

	typedef vec<unsigned char, 3> vec3uc;
	typedef vec<char, 3> vec3c;

	typedef vec<unsigned short, 3> vec3us;
	typedef vec<short, 3> vec3s;

	typedef vec<unsigned int, 3> vec3ui;
	typedef vec<int, 3> vec3i;

	typedef vec<unsigned long, 3> vec3ul;
	typedef vec<long, 3> vec3l;

}////

#endif