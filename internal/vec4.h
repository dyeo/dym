#ifndef _GMTK_VEC4_H_
#define _GMTK_VEC4_H_

//

#include "vec.h"

//

#define GMTK_VEC4_LOOP(oper) GMTK_UNROLL_LOOP(i,4,oper)

#define GMTK_VEC4_OPERATOR(oper) \
		{ vec<T,4> res; \
		GMTK_VEC4_LOOP(res[i] = oper); \
		return res; }

#define GMTK_VEC4_REF_OPERATOR(oper) \
				{ GMTK_VEC4_LOOP(oper); \
		return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec < T, 4 >
	{
		union
		{
			struct { T data[4]; };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { vec<T, 2> xy; };
			struct { vec<T, 3> xyz; };
			struct { vec<T, 3> rgb; };
		};

		//! Initialize vec4 with four values
		inline vec(const T& s0, const T& s1, const T& s2, const T& s3)
		{
			data[0] = s0;
			data[1] = s1;
			data[2] = s2;
			data[3] = s3;
		}

		//! Initialize vec4 with a vec3 and a fourth value
		inline vec(const vec<T, 3>& v012, const T& s3)
		{
			data[0] = v012.data[0];
			data[1] = v012.data[1];
			data[2] = v012.data[2];
			data[3] = s3;
		}

		//! Initialize vec4 with two vec2s
		inline vec(const vec<T, 2>& v01, const vec<T, 2>& v23)
		{
			data[0] = v01.data[0];
			data[1] = v01.data[1];
			data[2] = v23.data[0];
			data[2] = v23.data[1];
		}

		//! Default constructor
		inline vec() {
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC_LOOP(data[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline vec(const vec<T, 4>& v) {
			GMTK_VEC4_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> explicit inline vec(const vec<U, 2>& v) {
			GMTK_VEC4_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC4_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC4_LOOP(data[i] = a[i]);
		}

		//! Vector index operator
		inline T& operator[](const int i) {
			return data[i];
		}

		//! Vector const index operator
		inline const T& operator[](const int i) const {
			return data[i];
		}

		//! Returns a negative vector
		inline vec<T, 4> operator-() const {
			GMTK_VEC4_OPERATOR(-data[i]);
		}

		//! Component-wise vector multiplication
		inline vec<T, 4> operator*(const vec<T, 4>& v) const {
			GMTK_VEC4_OPERATOR(data[i] * v.data[i]);
		}

		//! Component-wise vector division
		inline vec<T, 4> operator/(const vec<T, 4>& v) const {
			GMTK_VEC4_OPERATOR(data[i] / v.data[i]);
		}

		//! Component-wise vector addition
		inline vec<T, 4> operator+(const vec<T, 4>& v) const {
			GMTK_VEC4_OPERATOR(data[i] + v.data[i]);
		}

		//! Component-wise vector subtraction
		inline vec<T, 4> operator-(const vec<T, 4>& v) const {
			GMTK_VEC4_OPERATOR(data[i] - v.data[i]);
		}

		//! Component-wise vector reference multiplication
		inline vec<T, 4>& operator*=(const vec<T, 4>& v) {
			GMTK_VEC4_REF_OPERATOR(data[i] *= v.data[i]);
		}

		//! Component-wise vector reference division
		inline vec<T, 4>& operator/=(const vec<T, 4>& v) {
			GMTK_VEC4_REF_OPERATOR(data[i] /= v.data[i]);
		}

		//! Component-wise vector reference addition
		inline vec<T, 4>& operator+=(const vec<T, 4>& v) {
			GMTK_VEC4_REF_OPERATOR(data[i] += v.data[i]);
		}

		//! Component-wise vector reference subtraction
		inline vec<T, 4>& operator-=(const vec<T, 4>& v) {
			GMTK_VEC4_REF_OPERATOR(data[i] -= v.data[i]);
		}

		//! Component-wise scalar multiplication
		inline vec<T, 4> operator*(const T& s) const {
			GMTK_VEC4_OPERATOR(data[i] * s);
		}

		//! Component-wise scalar division
		inline vec<T, 4> operator/(const T& s) const {
			GMTK_VEC4_OPERATOR(data[i] / s);
		}

		//! Component-wise scalar addition
		inline vec<T, 4> operator+(const T& s) const {
			GMTK_VEC4_OPERATOR(data[i] + s);
		}

		//! Component-wise scalar subtraction
		inline vec<T, 4> operator-(const T& s) const {
			GMTK_VEC4_OPERATOR(data[i] - s);
		}

		//! Component-wise scalar reference multiplication
		inline vec<T, 4>& operator*=(const T& s) {
			GMTK_VEC4_REF_OPERATOR(data[i] *= s);
		}

		//! Component-wise scalar reference division
		inline vec<T, 4>& operator/=(const T& s) {
			GMTK_VEC4_REF_OPERATOR(data[i] /= s);
		}

		//! Component-wise scalar reference addition
		inline vec<T, 4>& operator+=(const T& s) {
			GMTK_VEC4_REF_OPERATOR(data[i] += s);
		}

		//! Component-wise scalar reference subtraction
		inline vec<T, 4>& operator-=(const T& s) {
			GMTK_VEC4_REF_OPERATOR(data[i] -= s);
		}

		//! Zero vector (0,0,0,0)
		static inline vec<T, 4>& zero() const {
			return vec<T, 4>(0, 0, 0, 0);
		}

		//! One vector (1,1,1,1)
		static inline vec<T, 4>& one() const {
			return vec<T, 4>(1, 1, 1, 1);
		}

		//! Up vector (0,1,0,0)
		static inline vec<T, 4>& up() const {
			return vec<T, 4>(0, 1, 0, 0);
		}

		//! Down vector (0,-1,0,0)
		static inline vec<T, 4>& down() const {
			return vec<T, 4>(0, -1, 0, 0);
		}

		//! Right vector (1,0,0,0)
		static inline vec<T, 4>& right() const {
			return vec<T, 4>(1, 0, 0, 0);
		}

		//! Left vector (-1,0,0,0)
		static inline vec<T, 3>& left() const {
			return vec<T, 4>(-1, 0, 0, 0);
		}

		//! Forward vector (0,0,1,0)
		static inline vec<T, 4>& forward() const {
			return vec<T, 4>(0, 0, 1, 0);
		}

		//! Back vector (0,0,-1,0)
		static inline vec<T, 4>& back() const {
			return vec<T, 4>(0, 0, -1, 0);
		}

	};

	typedef vec<float, 4> vec4, vec4f;
	typedef vec<double, 4> vec4d;

	typedef vec<unsigned char, 4> vec4uc;
	typedef vec<char, 4> vec4c;

	typedef vec<unsigned short, 4> vec4us;
	typedef vec<short, 4> vec4s;

	typedef vec<unsigned int, 4> vec4ui;
	typedef vec<int, 4> vec4i;

	typedef vec<unsigned long, 4> vec4ul;
	typedef vec<long, 4> vec4l;

}////

#endif