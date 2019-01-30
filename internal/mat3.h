#ifndef _GMTK_MAT3_H_
#define _GMTK_MAT3_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "mat.h"

//

#define GMTK_IDENT3_LOOP(oper) GMTK_UNROLL_LOOP(i, 3, oper)

#define GMTK_MAT3_LOOP(oper) GMTK_UNROLL_2D_LOOP(i, j, 3, 3, oper)

#define GMTK_MAT3_LOOP2(oper) GMTK_UNROLL_LONG_LOOP(i, 9, oper)

#define GMTK_MAT3_OPERATOR(oper) { mat<T, 3, 3> res; GMTK_MAT3_LOOP(res[i][j] = oper); return res; }

#define GMTK_MAT3_OPERATOR2(oper) { mat<T, 3, 3> res; GMTK_MAT3_LOOP2(res(i) = oper); return res; }

#define GMTK_MAT3_REF_OPERATOR(oper) { GMTK_MAT3_LOOP(oper); return *this; }

#define GMTK_MAT3_REF_OPERATOR2(oper) { GMTK_MAT3_LOOP2(oper); return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T>
	//! A column-major matrix spanning r rows and c columns
	struct mat<T, 3, 3>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		int rows() const
		{
			return 3;
		}

		int cols() const
		{
			return 3;
		}

		inline int dim() const
		{
			return 3;
		}

		//! Unioned data members
		union
		{
			struct { vec<T, 3> data[3]; };
			struct { T arr[(9)]; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline mat()
		{
			GMTK_MAT3_LOOP(data[i][j] = static_cast<T>(i == j));
		}

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> list)
		{
			GMTK_MAT3_LOOP2(arr[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline mat(const mat<T, 3, 3>& v) {
			GMTK_MAT3_LOOP2(arr[i] = v.arr[i]);
		}

		template<int rm, int cm>
		//! Minor matrix constructor
		inline mat(const mat<T, rm, cm>& m)
		{
			GMTK_STATIC_ASSERT((rm < r) && (cm < c));
			GMTK_UNROLL_2D_LOOP(i, j, cm, rm, data[i][j] = m.data[i][j]);
		}

		template<typename U>
		//! Explicit type-conversion copy constructor
		explicit inline mat(const mat<U, 3, 3>& v) {
			GMTK_MAT3_LOOP2(arr[i] = static_cast<T>(v.arr[i]));
		}

		//! Fill constructor
		explicit inline mat(const T& s) {
			GMTK_MAT3_LOOP2(arr[i] = s);
		}

		//! Array initializer
		explicit inline mat(const T* a) {
			GMTK_MAT3_LOOP2(arr[i] = a[i]);
		}

		inline mat(const T& s0, const T& s1, const T& s2, const T& s3, const T& s4, const T& s5, const T& s6, const T& s7, const T& s8) {
			arr[0] = s0;
			arr[1] = s1;
			arr[2] = s2;
			arr[3] = s3;
			arr[4] = s4;
			arr[5] = s5;
			arr[6] = s6;
			arr[7] = s7;
			arr[8] = s8;
		}

		template<typename U>
		explicit inline mat(const U& s0, const U& s1, const U& s2, const U& s3, const U& s4, const U& s5, const U& s6, const U& s7, const U& s8) {
			arr[0] = static_cast<T>(s0);
			arr[1] = static_cast<T>(s1);
			arr[2] = static_cast<T>(s2);
			arr[3] = static_cast<T>(s3);
			arr[4] = static_cast<T>(s4);
			arr[5] = static_cast<T>(s5);
			arr[6] = static_cast<T>(s6);
			arr[7] = static_cast<T>(s7);
			arr[8] = static_cast<T>(s8);
		}

		//

		//! Inserts a 2x2 matrix into the top-left portion of a 3x3 identity matrix
		//! ident adjusts the identity value
		inline mat(const mat<T, 2, 2>& m, const T& ident = static_cast<T>(1))
		{
		arr[0] = m.arr[0];
		arr[1] = m.arr[1];
		arr[2] = 0;
		arr[3] = m.arr[2];
		arr[4] = m.arr[3];
		arr[5] = 0;
		arr[6] = 0;
		arr[7] = 0;
		arr[8] = ident;
		}

		//! Constructs a 3x3 matrix using the top-left portion of a 4x4 matrix
		inline mat(const mat<T, 4, 4>& m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = m.arr[2];

			arr[3] = m.arr[4];
			arr[4] = m.arr[5];
			arr[5] = m.arr[6];

			arr[6] = m.arr[8];
			arr[7] = m.arr[9];
			arr[8] = m.arr[10];
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////
		
		//! Column function - returns column as vector of T
		inline vec<T, 3> col(const int i) const {
			return data[i];
		}

		//! Row function - returns row as vector of T
		inline vec<T, 3> row(const int i) const {
			vec<T, 3> v = vec4(arr[i], arr[i + 3], arr[i + 6]);
			return v;
		}

		//! Matrix index operator - returns column
		inline vec<T, 3>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column
		inline const vec<T, 3>& operator[](const int i) const {
			return data[i];
		}

		//! Matrix linear array index operator - returns element 
		inline T& operator()(const int i) {
			return arr[i];
		}

		//! Matrix linear array const index operator - returns element
		inline const T& operator()(const int i) const {
			return arr[i];
		}

		////////////////
		//! OPERATORS //
		////////////////

		//! Returns a negative matrix
		inline mat<T, 3, 3> operator-() const {
			GMTK_MAT3_OPERATOR2(-arr[i]);
		}

		//! Component-wise matrix addition
		inline mat<T, 3, 3> operator+(const mat<T, 3, 3>& m) const {
			GMTK_MAT3_OPERATOR2(arr[i] + m.arr[i]);
		}

		//! Component-wise matrix subtraction
		inline mat<T, 3, 3> operator-(const mat<T, 3, 3>& m) const {
			GMTK_MAT3_OPERATOR2(arr[i] - m.arr[i]);
		}

		//! Component-wise matrix division
		inline mat<T, 3, 3> operator/(const mat<T, 3, 3>& m) const {
			GMTK_MAT3_OPERATOR2(arr[i] / m.arr[i]);
		}

		//

		//! Component-wise scalar addition
		inline mat<T, 3, 3> operator+(const T& s) const {
			GMTK_MAT3_OPERATOR2(arr[i] + s);
		}

		//! Component-wise scalar subtraction
		inline mat<T, 3, 3> operator-(const T& s) const {
			GMTK_MAT3_OPERATOR2(arr[i] - s);
		}

		//! Component-wise scalar division
		inline mat<T, 3, 3> operator/(const T& s) const {
			GMTK_MAT3_OPERATOR2(arr[i] / s);
		}

		//! Component-wise scalar multiplication
		inline mat<T, 3, 3> operator*(const T& s) const {
			GMTK_MAT3_OPERATOR2(arr[i] * s);
		}

		//

		//! Component-wise matrix reference addition
		inline mat<T, 3, 3>& operator+=(const mat<T, 3, 3>& m) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] += m.arr[i]);
		}

		//! Component-wise matrix reference subtraction
		inline mat<T, 3, 3>& operator-=(const mat<T, 3, 3>& m) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] -= m.arr[i]);
		}

		//! Component-wise matrix reference division
		inline mat<T, 3, 3>& operator/=(const mat<T, 3, 3>& m) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] /= m.arr[i]);
		}

		//

		//! Component-wise scalar reference addition
		inline mat<T, 3, 3>& operator+=(const T& s) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] += s);
		}

		//! Component-wise scalar reference subtraction
		inline mat<T, 3, 3>& operator-=(const T& s) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] -= s);
		}

		//! Component-wise scalar reference division
		inline mat<T, 3, 3>& operator/=(const T& s) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] /= s);
		}

		//! Component-wise scalar reference multiplication
		inline mat<T, 3, 3>& operator*=(const T& s) {
			GMTK_MAT3_REF_OPERATOR2(arr[i] *= s);
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Returns an identity matrix
		static inline constexpr mat<T, 3, 3> identity()
		{
			return mat<T, 3, 3>(1, 0, 0, 0, 1, 0, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		inline static mat<T, 3, 3> roworder(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8)
		{
			return mat<T, 3, 3>
				(s0, s3, s6,
				s1, s4, s7,
				s2, s5, s8);
		}

		//! Creates a 3x3 matrix using 3 row vectors
		inline static mat<T, 3, 3> fromrows(vec<T, 3> r0, vec<T, 3> r1, vec<T, 3> r2)
		{
			return mat<T, 3, 3>
				(r0.x, r1.x, r2.x,
				r0.y, r1.y, r2.y,
				r0.z, r1.z, r2.z);
		}

		//! Creates a 3x3 matrix using 3 column vectors
		inline static mat<T, 3, 3> fromcols(vec<T, 3> c0, vec<T, 3> c1, vec<T, 3> c2)
		{
			return mat<T, 3, 3>
				(c0.x, c0.y, c0.z,
				c1.x, c1.y, c1.z,
				c2.x, c2.y, c2.z);
		}

		//! Rotate an axis about a given angle
		inline static mat<T, 3, 3> rotate(const Angle<T>& an, const vec<T, 3>& ax)
		{
			T c = cos(an.radians());
			T s = sin(an.radians());
			T t = 1 - c;
			return mat<T, 3, 3>
				((t*ax.x*ax.x) + c,			(t*ax.x*ax.y) + ax.z*s,		(t*ax.x*ax.z) - ax.y*s,
				 (t*ax.x*ax.y) - ax.z*s,	(t*ax.y*ax.y) + c,			(t*ax.y*ax.z) + ax.x*s,
				 (t*ax.x*ax.z) + ax.y*s,	(t*ax.y*ax.z) - ax.x*s,		(t*ax.z*ax.z) + c);
		}

		//! Rotate axis x about a given angle
		inline static mat<T, 3, 3> rotatex(const Angle<T>& x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<T, 3, 3>
				(1, 0, 0, 
				 0, c, s,
				 0, -s, c);
		}

		//! Rotate axis y about a given angle
		inline static mat<T, 3, 3> rotatey(const Angle<T>& x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<T, 3, 3>
				(c, 0, -s,
				 0, 1, 0,
				 s, 0, c);
		}

		//! Rotate axis z about a given angle
		inline static mat<T, 3, 3> rotatez(const Angle<T>& x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<T, 3, 3>
				(c, s, 0,
				-s, c, 0,
				 0, 0, 1);
		}

		inline static mat<T, 3, 3> scale(const T& s)
		{
			return mat<T, 3, 3>(s, 0, 0, 0, s, 0, 0, 0, s);
		}

		inline static mat<T, 3, 3> scale(const T& x, const T& y, const T& z)
		{
			return mat<T, 3, 3>(x, 0, 0, 0, y, 0, 0, 0, z);
		}

		inline static mat<T, 3, 3> scale(const vec<T, 3>& v)
		{
			return mat<T, 3, 3>(v.x, 0, 0, 0, v.y, 0, 0, 0, v.z);
		}

		inline static mat<T, 3, 3> translate(const T& x, const T& y)
		{
			return mat<T, 3, 3>(1, 0, 0, 0, 1, 0, x, y, 1);
		}

		inline static mat<T, 3, 3> translate(const vec<T, 3>& v)
		{
			return translate(v.x, v.y, v.z);
		}

		inline static mat<T, 4, 4> translate_affine(const T& x, const T& y, const T& z)
		{
			mat<T, 4, 4> res = mat<4, 4>::identity();
			res[3] = vec<T, 4>(x, y, z, 1);
			return res;
		}

		inline static mat<T, 4, 4> translate_affine(const vec<T, 3>& v)
		{
			return translate(v.x, v.y, v.z);
		}

	}; //! struct mat

	template<typename T>
	inline T det(const mat<T, 3, 3>& m)
	{
		return (m.arr[0] * m.arr[4] * m.arr[8]) - (m.arr[0] * m.arr[5] * m.arr[7]) - (m.arr[1] * m.arr[3] * m.arr[8]) + (m.arr[1] * m.arr[5] * m.arr[6]) + (m.arr[2] * m.arr[3] * m.arr[7]) - (m.arr[2] * m.arr[4] * m.arr[6]);
	}

	//
	
	typedef mat<float, 3, 3>			mat3, mat3f;
	typedef mat<double, 3, 3>			mat3d;
	typedef mat<unsigned char, 3, 3>	mat3uc;
	typedef mat<char, 3, 3>				mat3c;
	typedef mat<unsigned short, 3, 3>	mat3us;
	typedef mat<short, 3, 3>			mat3s;
	typedef mat<unsigned int, 3, 3>		mat3ui;
	typedef mat<int, 3, 3>				mat3i;
	typedef mat<unsigned long, 3, 3>	mat3ul;
	typedef mat<long, 3, 3>				mat3l;

}////

//

#pragma warning(pop)

//

#endif//_GMTK_MAT3_H_