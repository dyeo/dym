#ifndef _GMTK_MAT2_H_
#define _GMTK_MAT2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "mat.h"
#include "..\angle.h"

//

#define GMTK_IDENT2_LOOP(oper) GMTK_UNROLL_LOOP(i, 2, oper)

#define GMTK_MAT2_LOOP(oper) GMTK_UNROLL_2D_LOOP(i, j, 2, 2, oper)

#define GMTK_MAT2_LOOP2(oper) GMTK_UNROLL_LONG_LOOP(i, 4, oper)

#define GMTK_MAT2_OPERATOR(oper) { mat<T, 2, 2> res; GMTK_MAT2_LOOP(res[i][j] = oper); return res; }

#define GMTK_MAT2_OPERATOR2(oper) { mat<T, 2, 2> res; GMTK_MAT2_LOOP2(res(i) = oper); return res; }

#define GMTK_MAT2_REF_OPERATOR(oper) { GMTK_MAT2_LOOP(oper); return *this; }

#define GMTK_MAT2_REF_OPERATOR2(oper) { GMTK_MAT2_LOOP2(oper); return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T>
	//! A column-major matrix spanning r rows and c columns
	struct mat<T, 2, 2>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		int rows() const
		{
			return 2;
		}

		int cols() const
		{
			return 2;
		}

		inline int dim() const
		{
			return 2;
		}

		//! Unioned data members
		union
		{
			struct { vec<T, 2> data[2]; };
			struct { T arr[(4)]; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline mat()
		{
			GMTK_MAT2_LOOP(data[i][j] = static_cast<T>(i == j));
		}

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> list)
		{
			GMTK_MAT2_LOOP2(arr[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline mat(const mat<T, 2, 2>& v) {
			GMTK_MAT2_LOOP2(arr[i] = v.arr[i]);
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
		explicit inline mat(const mat<U, 2, 2>& v) {
			GMTK_MAT2_LOOP2(arr[i] = static_cast<T>(v.arr[i]));
		}

		//! Fill constructor
		explicit inline mat(const T& s) {
			GMTK_MAT2_LOOP2(arr[i] = s);
		}

		//! Array initializer
		explicit inline mat(const T* a) {
			GMTK_MAT2_LOOP2(arr[i] = a[i]);
		}

		inline mat(const T& s0, const T& s1, const T& s2, const T& s3) {
			arr[0] = s0;
			arr[1] = s1;
			arr[2] = s2;
			arr[3] = s3;
		}

		template<typename U>
		explicit inline mat(const U& s0, const U& s1, const U& s2, const U& s3) {
			arr[0] = static_cast<T>(s0);
			arr[1] = static_cast<T>(s1);
			arr[2] = static_cast<T>(s2);
			arr[3] = static_cast<T>(s3);
		}

		//! Constructs a 2x2 matrix using the top-left portion of a 3x3 matrix;
		inline mat(const mat<T, 3, 3>& m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = m.arr[3];
			arr[3] = m.arr[4];
		}

		//! Constructs a 2x2 matrix using the top-left portion of a 4x4 matrix;
		inline mat(const mat<T, 4, 4>& m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = m.arr[4];
			arr[3] = m.arr[5];
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Column function - returns column as vector of T
		inline vec<T, 2> col(const int i) {
			return data[i];
		}

		//! Row function - returns row as vector of T
		inline vec<T, 2> row(const int i) {
			vec<T, 2> v = vec4(arr[i], arr[i + 2]);
			return v;
		}

		//! Matrix index operator - returns column
		inline vec<T, 2>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column
		inline const vec<T, 2>& operator[](const int i) const {
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
		inline mat<T, 2, 2> operator-() const {
			GMTK_MAT2_OPERATOR2(-arr[i]);
		}

		//! Component-wise matrix addition
		inline mat<T, 2, 2> operator+(const mat<T, 2, 2>& m) const {
			GMTK_MAT2_OPERATOR2(arr[i] + m.arr[i]);
		}

		//! Component-wise matrix subtraction
		inline mat<T, 2, 2> operator-(const mat<T, 2, 2>& m) const {
			GMTK_MAT2_OPERATOR2(arr[i] - m.arr[i]);
		}

		//! Component-wise matrix division
		inline mat<T, 2, 2> operator/(const mat<T, 2, 2>& m) const {
			GMTK_MAT2_OPERATOR2(arr[i] / m.arr[i]);
		}

		//

		//! Component-wise scalar addition
		inline mat<T, 2, 2> operator+(const T& s) const {
			GMTK_MAT2_OPERATOR2(arr[i] + s);
		}

		//! Component-wise scalar subtraction
		inline mat<T, 2, 2> operator-(const T& s) const {
			GMTK_MAT2_OPERATOR2(arr[i] - s);
		}

		//! Component-wise scalar division
		inline mat<T, 2, 2> operator/(const T& s) const {
			GMTK_MAT2_OPERATOR2(arr[i] / s);
		}

		//! Component-wise scalar multiplication
		inline mat<T, 2, 2> operator*(const T& s) const {
			GMTK_MAT2_OPERATOR2(arr[i] * s);
		}

		//

		//! Component-wise matrix reference addition
		inline mat<T, 2, 2>& operator+=(const mat<T, 2, 2>& m) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] += m.arr[i]);
		}

		//! Component-wise matrix reference subtraction
		inline mat<T, 2, 2>& operator-=(const mat<T, 2, 2>& m) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] -= m.arr[i]);
		}

		//! Component-wise matrix reference division
		inline mat<T, 2, 2>& operator/=(const mat<T, 2, 2>& m) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] /= m.arr[i]);
		}

		//

		//! Component-wise scalar reference addition
		inline mat<T, 2, 2>& operator+=(const T& s) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] += s);
		}

		//! Component-wise scalar reference subtraction
		inline mat<T, 2, 2>& operator-=(const T& s) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] -= s);
		}

		//! Component-wise scalar reference division
		inline mat<T, 2, 2>& operator/=(const T& s) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] /= s);
		}

		//! Component-wise scalar reference multiplication
		inline mat<T, 2, 2>& operator*=(const T& s) {
			GMTK_MAT2_REF_OPERATOR2(arr[i] *= s);
		}
		
		/////////////////////////////////
		//! MATRIX GENERATOR FUNCTIONS //
		/////////////////////////////////

		//! Generates a 2x2 identity matrix
		static inline constexpr mat<T, 2, 2> identity()
		{
			return mat<T, 2, 2>(1, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		inline static mat<T, 2, 2> roworder(const T &s0, const T &s1, const T &s2, const T &s3)
		{
			return mat<T, 2, 2>
				(s0, s2,
				 s1, s3);
		}

		//! Creates a 2x2 matrix using 2 row vectors
		inline static mat<T, 2, 2> fromrows(vec<T, 2> r0, vec<T, 2> r1)
		{
			return mat<T, 2, 2>
				(r0.x, r1.x,
				 r0.y, r1.y);
		}

		//! Creates a 2x2 matrix using 2 column vectors
		inline static mat<T, 2, 2> fromcols(vec<T, 2> c0, vec<T, 2> c1)
		{
			return mat<T, 2, 2>
				(c0.x, c0.y,
				c1.x, c1.y);
		}
		
		//! Generates a clockwise rotation matrix using an angle
		inline static mat<T, 2, 2> rotate(const Angle<T>& a)
		{
			float ca = cos(a.radians());
			float sa = sin(a.radians());
			return mat<T, 2, 2>(ca, sa, -sa, ca);
		}

		//! Generates a clockwise rotation matrix using an angle
		inline static mat<T, 2, 2> rotatecw(const Angle<T>& a)
		{
			return rotate(a);
		}

		//! Generates a counter-clockwise rotation matrix using an angle
		inline static mat<T, 2, 2> rotateccw(const Angle<T>& a)
		{
			float ca = cos(a.radians());
			float sa = sin(a.radians());
			return mat<T, 2, 2>(ca, -sa, sa, ca);
		}

		//! Generates a scaling matrix using a single scaling value
		inline static mat<T, 2, 2> scale(const T& s)
		{
			return mat<T, 2, 2>(s, 0, 0, s);
		}

		//! Generates a scaling matrix using an x and y scaling value
		inline static mat<T, 2, 2> scale(const T& x, const T& y)
		{
			return mat<T, 2, 2>(x, 0, 0, y);
		}

		//! Shears along the x axis
		inline static mat<T, 2, 2> shearx(const T& k)
		{
			return mat<T, 2, 2>(1, 0, k, 1);
		}

		//! Shears along the y axis
		inline static mat<T, 2, 2> sheary(const T& k)
		{
			return mat<T, 2, 2>(1, k, 0, 1);
		}

		inline static mat<T, 3, 3> translate_affine(const T& x, const T& y)
		{
			mat<T, 3, 3> res = mat<T, 3, 3>::identity();
			res[2] = vec<T, 3>(x, y, 1);
		}

		inline static mat<T, 3, 3> translate_affine(const vec<T, 2>& t)
		{
			return translate_affine(t.x, t.y);
		}

	}; //! struct mat

	template<typename T>
	inline T det(const mat<T, 2, 2>& m)
	{
		return (m.arr[0] * m.arr[3]) - (m.arr[1] * m.arr[2]);
	}

	//
	
	typedef mat<float, 2, 2>			mat2, mat2f;
	typedef mat<double, 2, 2>			mat2d;
	typedef mat<unsigned char, 2, 2>	mat2uc;
	typedef mat<char, 2, 2>				mat2c;
	typedef mat<unsigned short, 2, 2>	mat2us;
	typedef mat<short, 2, 2>			mat2s;
	typedef mat<unsigned int, 2, 2>		mat2ui;
	typedef mat<int, 2, 2>				mat2i;
	typedef mat<unsigned long, 2, 2>	mat2ul;
	typedef mat<long, 2, 2>				mat2l;

}////

//

#pragma warning(pop)

//

#endif//_GMTK_MAT2_H_