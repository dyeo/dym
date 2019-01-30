#ifndef _GMTK_VEC2_H_
#define _GMTK_VEC2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"

//

#define GMTK_VEC2_LOOP(oper) GMTK_UNROLL_LOOP(i,2,oper)

#define GMTK_VEC2_OPERATOR(oper) \
		{ vec<T,2> res; \
		GMTK_VEC2_LOOP(res[i] = oper); \
		return res; }

#define GMTK_VEC2_REF_OPERATOR(oper) \
				{ GMTK_VEC2_LOOP(oper); \
		return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec < T, 2 >
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[2]; };
			struct { T x, y; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec2 with two values
		inline vec(const T& s0, const T& s1)
		{
			data[0] = s0;
			data[1] = s1;
		}

		//! Default constructor
		inline vec() {
			GMTK_VEC2_LOOP(data[i] = static_cast<T>(0));
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC2_LOOP(data[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline vec(const vec<T, 2>& v) {
			GMTK_VEC2_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<T, d2> &v) {
			GMTK_STATIC_ASSERT(d2 >= 2);
			GMTK_VEC2_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> explicit inline vec(const vec<U, 2>& v) {
			GMTK_VEC2_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC2_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC2_LOOP(data[i] = a[i]);
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
		inline vec<T, 2> operator-() const {
			GMTK_VEC2_OPERATOR(-data[i]);
		}

		//! Component-wise vector multiplication
		inline vec<T, 2> operator*(const vec<T, 2>& v) const {
			GMTK_VEC2_OPERATOR(data[i] * v.data[i]);
		}

		//! Component-wise vector division
		inline vec<T, 2> operator/(const vec<T, 2>& v) const {
			GMTK_VEC2_OPERATOR(data[i] / v.data[i]);
		}

		//! Component-wise vector addition
		inline vec<T, 2> operator+(const vec<T, 2>& v) const {
			GMTK_VEC2_OPERATOR(data[i] + v.data[i]);
		}

		//! Component-wise vector subtraction
		inline vec<T, 2> operator-(const vec<T, 2>& v) const {
			GMTK_VEC2_OPERATOR(data[i] - v.data[i]);
		}

		//! Component-wise vector reference multiplication
		inline vec<T, 2>& operator*=(const vec<T, 2>& v) {
			GMTK_VEC2_REF_OPERATOR(data[i] *= v.data[i]);
		}

		//! Component-wise vector reference division
		inline vec<T, 2>& operator/=(const vec<T, 2>& v) {
			GMTK_VEC2_REF_OPERATOR(data[i] /= v.data[i]);
		}

		//! Component-wise vector reference addition
		inline vec<T, 2>& operator+=(const vec<T, 2>& v) {
			GMTK_VEC2_REF_OPERATOR(data[i] += v.data[i]);
		}

		//! Component-wise vector reference subtraction
		inline vec<T, 2>& operator-=(const vec<T, 2>& v) {
			GMTK_VEC2_REF_OPERATOR(data[i] -= v.data[i]);
		}

		//! Component-wise scalar multiplication
		inline vec<T, 2> operator*(const T& s) const {
			GMTK_VEC2_OPERATOR(data[i] * s);
		}

		//! Component-wise scalar division
		inline vec<T, 2> operator/(const T& s) const {
			GMTK_VEC2_OPERATOR(data[i] / s);
		}

		//! Component-wise scalar addition
		inline vec<T, 2> operator+(const T& s) const {
			GMTK_VEC2_OPERATOR(data[i] + s);
		}

		//! Component-wise scalar subtraction
		inline vec<T, 2> operator-(const T& s) const {
			GMTK_VEC2_OPERATOR(data[i] - s);
		}

		//! Component-wise scalar reference multiplication
		inline vec<T, 2>& operator*=(const T& s) {
			GMTK_VEC2_REF_OPERATOR(data[i] *= s);
		}

		//! Component-wise scalar reference division
		inline vec<T, 2>& operator/=(const T& s) {
			GMTK_VEC2_REF_OPERATOR(data[i] /= s);
		}

		//! Component-wise scalar reference addition
		inline vec<T, 2>& operator+=(const T& s) {
			GMTK_VEC2_REF_OPERATOR(data[i] += s);
		}

		//! Component-wise scalar reference subtraction
		inline vec<T, 2>& operator-=(const T& s) {
			GMTK_VEC2_REF_OPERATOR(data[i] -= s);
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////
		
		//! Zero vector (0,0)
		static inline constexpr vec<T, 2> zero() { return vec<T, 2>(0, 0); }
		
		//! One vector (1,1)
		static inline constexpr vec<T, 2> one() { return vec<T, 2>(1, 1); }

		//! Up vector (0,1)
		static inline constexpr vec<T, 2> up() { return vec<T, 2>(0, 1); }

		//! Down vector (0,-1)
		static inline constexpr vec<T, 2> down() { return vec<T, 2>(0, -1); }

		//! Right vector (1,0)
		static inline constexpr vec<T, 2> right() { return vec<T, 2>(1, 0); }

		//! Left vector (-1,0)
		static inline constexpr vec<T, 2> left() { return vec<T, 2>(-1, 0); }

	}; //! struct vec2

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef vec<float, 2> vec2, vec2f;
	typedef vec<double, 2> vec2d;

	typedef vec<unsigned char, 2> vec2uc;
	typedef vec<char, 2> vec2c;

	typedef vec<unsigned short, 2> vec2us;
	typedef vec<short, 2> vec2s;

	typedef vec<unsigned int, 2> vec2ui;
	typedef vec<int, 2> vec2i;

	typedef vec<unsigned long, 2> vec2ul;
	typedef vec<long, 2> vec2l;

}////

//

#pragma warning(pop)

//

#endif