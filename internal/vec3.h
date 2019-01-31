#ifndef _GMTK_VEC3_H_
#define _GMTK_VEC3_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"

//

#define GMTK_VEC3_LOOP(oper) GMTK_UNROLL_LOOP(i,3,oper)

#define GMTK_VEC3_OPERATOR(oper) \
		{ vec<3, T> res; \
		GMTK_VEC3_LOOP(res[i] = oper); \
		return res; }

#define GMTK_VEC3_REF_OPERATOR(oper) \
		{ GMTK_VEC3_LOOP(oper); \
		return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <3, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[3]; };
			struct { T x, y, z; };
			struct { vec<2, T> xy; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec3 with three values
		inline vec(const T& s0, const T& s1, const T& s2)
		{
			data[0] = s0;
			data[1] = s1;
			data[2] = s2;
		}

		//! Initialize vec3 with a vec2 and a third value
		inline vec(const vec<2, T>& v01, const T& s2)
		{
			data[0] = v01.data[0];
			data[1] = v01.data[1];
			data[2] = s2;
		}

		//! Default constructor
		inline vec() {
			GMTK_VEC3_LOOP(data[i] = static_cast<T>(0));
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC3_LOOP(data[i] = *(list.begin() + i));
		}
		
		//! Copy constructor
		inline vec(const vec<3, T>& v) {
			GMTK_VEC3_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 3);
			GMTK_VEC3_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<3, U>& v) {
			GMTK_VEC3_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC3_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC3_LOOP(data[i] = a[i]);
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
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Returns a negative vector
		inline vec<3, T> operator-() const {
			GMTK_VEC3_OPERATOR(-data[i]);
		}

		//! Component-wise vector multiplication
		inline vec<3, T> operator*(const vec<3, T>& v) const {
			GMTK_VEC3_OPERATOR(data[i] * v.data[i]);
		}

		//! Component-wise vector division
		inline vec<3, T> operator/(const vec<3, T>& v) const {
			GMTK_VEC3_OPERATOR(data[i] / v.data[i]);
		}

		//! Component-wise vector addition
		inline vec<3, T> operator+(const vec<3, T>& v) const {
			GMTK_VEC3_OPERATOR(data[i] + v.data[i]);
		}

		//! Component-wise vector subtraction
		inline vec<3, T> operator-(const vec<3, T>& v) const {
			GMTK_VEC3_OPERATOR(data[i] - v.data[i]);
		}

		//! Component-wise vector reference multiplication
		inline vec<3, T>& operator*=(const vec<3, T>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] *= v.data[i]);
		}

		//! Component-wise vector reference division
		inline vec<3, T>& operator/=(const vec<3, T>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] /= v.data[i]);
		}

		//! Component-wise vector reference addition
		inline vec<3, T>& operator+=(const vec<3, T>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] += v.data[i]);
		}

		//! Component-wise vector reference subtraction
		inline vec<3, T>& operator-=(const vec<3, T>& v) {
			GMTK_VEC3_REF_OPERATOR(data[i] -= v.data[i]);
		}

		//! Component-wise scalar multiplication
		inline vec<3, T> operator*(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] * s);
		}

		//! Component-wise scalar division
		inline vec<3, T> operator/(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] / s);
		}

		//! Component-wise scalar addition
		inline vec<3, T> operator+(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] + s);
		}

		//! Component-wise scalar subtraction
		inline vec<3, T> operator-(const T& s) const {
			GMTK_VEC3_OPERATOR(data[i] - s);
		}

		//! Component-wise scalar reference multiplication
		inline vec<3, T>& operator*=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] *= s);
		}

		//! Component-wise scalar reference division
		inline vec<3, T>& operator/=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] /= s);
		}

		//! Component-wise scalar reference addition
		inline vec<3, T>& operator+=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] += s);
		}

		//! Component-wise scalar reference subtraction
		inline vec<3, T>& operator-=(const T& s) {
			GMTK_VEC3_REF_OPERATOR(data[i] -= s);
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Zero vector (0,0,0)
		static inline constexpr vec<3, T> zero() { return vec<3, T>(0, 0, 0); }

		//! One vector (1,1,1)
		static inline constexpr vec<3, T> one() { return vec<3, T>(1, 1, 1); }

		//! Up vector (0,1,0)
		static inline constexpr vec<3, T> up() { return vec<3, T>(0, 1, 0); }

		//! Down vector (0,-1,0)
		static inline constexpr vec<3, T> down() { return vec<3, T>(0, -1, 0); }

		//! Right vector (1,0,0)
		static inline constexpr vec<3, T> right() { return vec<3, T>(1, 0, 0); }

		//! Left vector (-1,0,0)
		static inline constexpr vec<3, T> left() { return vec<3, T>(-1, 0, 0); }

		//! Forward vector (0,0,1)
		static inline constexpr vec<3, T> forward() { return vec<3, T>(0, 0, 1); }

		//! Back vector (0,0,-1)
		static inline constexpr vec<3, T> back() { return vec<3, T>(0, 0, -1); }

	}; //! struct vec3

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef vec<3, float>			vec3, vec3f;
	typedef vec<3, double>			vec3d;
	typedef vec<3, unsigned char>	vec3uc;
	typedef vec<3, char>			vec3c;
	typedef vec<3, unsigned short>	vec3us;
	typedef vec<3, short>			vec3s;
	typedef vec<3, unsigned int>	vec3ui;
	typedef vec<3, int>				vec3i;
	typedef vec<3, unsigned long>	vec3ul;
	typedef vec<3, long>			vec3l;

}////

//

#pragma warning(pop)

//

#endif