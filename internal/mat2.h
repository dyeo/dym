#ifndef _GMTK_MAT2_H_
#define _GMTK_MAT2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "mat.h"
#include "..\angle.h"

//

#define GMTK_MAT2_LOOP(oper) GMTK_STATIC_LOOP(i, 4, oper)

#define GMTK_MAT2_LOOP_2D(oper) GMTK_STATIC_2D_LOOP(i, j, 2, 2, oper)

//

#define GMTK_MAT2_INIT(a,b,c,d) : arr { a, b, c, d } { }

#define GMTK_MAT2_UN_OP(op) \
	inline mat<2, 2, T> operator op () const \
	{ mat<2, 2, T> res(static_cast<T>(0)); GMTK_MAT2_LOOP(res.arr[i] = op arr[i]); return res; }

#define GMTK_MAT2_MAT_OP(op) \
	inline mat<2, 2, T> operator op (const mat<2, 2, T>& v) const \
	{ mat<2, 2, T> res(static_cast<T>(0)); GMTK_MAT2_LOOP(res.arr[i] = arr[i] op v.arr[i]); return res; }

#define GMTK_MAT2_SCL_OP(op) \
	inline mat<2, 2, T> operator op (const T& v) const \
	{ mat<2, 2, T> res(static_cast<T>(0)); GMTK_MAT2_LOOP(res.arr[i] = arr[i] op v); return res; }

#define GMTK_MAT2_MAT_ROP(op) \
	inline mat<2, 2, T>& operator op (const mat<2, 2, T>& v) \
	{ GMTK_MAT2_LOOP(arr[i] op v.arr[i]); return *this; }

#define GMTK_MAT2_SCL_ROP(op) \
	inline mat<2, 2, T>& operator op (const T& v) \
	{ GMTK_MAT2_LOOP(arr[i] op v); return *this; }

//

namespace GMTK_NAMESPACE
{////

	//! A column-major matrix spanning r rows and c columns
	template <typename T> struct mat <2, 2, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		inline constexpr int rows() const
		{
			return 2;
		}

		inline constexpr int cols() const
		{
			return 2;
		}

		inline constexpr int dim() const
		{
			return 2;
		}

		//! Unioned data members
		union
		{
			struct { vec<2, T> data[2]; };
			struct { T arr[4]; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline mat()
			GMTK_MAT2_INIT(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1))

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> l)
			GMTK_MAT2_INIT(*(l.begin()), *(l.begin() + 1), *(l.begin() + 2), *(l.begin() + 3))

		//! Copy constructor
		inline mat(const mat<2, 2, T>& v)
			GMTK_MAT2_INIT(v.arr[0], v.arr[1], v.arr[2], v.arr[3])

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit inline mat(const mat<2, 2, U>& v)
			GMTK_MAT2_INIT(static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]), static_cast<T>(v.arr[3]))

		//! Fill constructor
		explicit inline mat(const T& s)
			GMTK_MAT2_INIT(s, s, s, s)

		//! Array initializer
		explicit inline mat(const T* a)
			GMTK_MAT2_INIT(a[0], a[1], a[2], a[3])

		//! Value constructor
		inline mat(const T& s0, const T& s1, const T& s2, const T& s3) 
			GMTK_MAT2_INIT(s0, s1, s2, s3)

		//! Explicit type-conversionm value constructor
		template<typename U>
		explicit inline mat(const U& s0, const U& s1, const U& s2, const U& s3) 
			GMTK_MAT2_INIT(static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(s3))

		//! Constructs a 2x2 matrix using the top-left portion of a 3x3 matrix;
		inline mat(const mat<3, 3, T>& m)
			GMTK_MAT2_INIT(m.arr[0], m.arr[1], m.arr[3], m.arr[4])

		//! Constructs a 2x2 matrix using the top-left portion of a 4x4 matrix;
		inline mat(const mat<4, 4, T>& m)
			GMTK_MAT2_INIT(m.arr[0], m.arr[1], m.arr[4], m.arr[5])

		//! Minor matrix constructor
		template<int cm, int rm>
		inline mat(const mat<cm, rm, T>& m)
		{
			GMTK_STATIC_ASSERT((rm < r) && (cm < c));
			GMTK_UNROLL_2D_LOOP(i, j, cm, rm, data[i][j] = m.data[i][j]);
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Column function - returns column as vector of T
		inline vec<2, T> col(const int i) {
			return data[i];
		}

		//! Row function - returns row as vector of T
		inline vec<2, T> row(const int i) {
			vec<2, T> v = vec<2, T>(arr[i], arr[i + 2]);
			return v;
		}

		//! Matrix index operator - returns column
		inline vec<2, T>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column
		inline const vec<2, T>& operator[](const int i) const {
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
		
		//! Component-wise unary negation
		GMTK_MAT2_UN_OP(-)
		//! Component-wise unary negation
		GMTK_MAT2_UN_OP(~)
		//! Vector assignment
		GMTK_MAT2_MAT_ROP(=)
		
		//! Component-wise matrix addition
		GMTK_MAT2_MAT_OP(+)		
		//! Component-wise matrix subtraction
		GMTK_MAT2_MAT_OP(-)		
		//! Component-wise matrix OR
		GMTK_MAT2_MAT_OP(|)
		//! Component-wise matrix AND
		GMTK_MAT2_MAT_OP(&)
		//! Component-wise matrix XOR
		GMTK_MAT2_MAT_OP(^)
		//! Component-wise matrix modulus
		GMTK_MAT2_MAT_OP(%)
		//! Component-wise matrix shift left
		GMTK_MAT2_MAT_OP(<<)
		//! Component-wise matrix shift right
		GMTK_MAT2_MAT_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_MAT2_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_MAT2_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_MAT2_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_MAT2_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_MAT2_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_MAT2_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_MAT2_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_MAT2_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_MAT2_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_MAT2_SCL_OP(>>)
							
		//! Component-wise matrix reference addition
		GMTK_MAT2_MAT_ROP(+=)		
		//! Component-wise matrix reference subtraction
		GMTK_MAT2_MAT_ROP(-=)
		//! Component-wise matrix reference OR
		GMTK_MAT2_MAT_ROP(|=)
		//! Component-wise matrix reference AND
		GMTK_MAT2_MAT_ROP(&=)
		//! Component-wise matrix reference XOR
		GMTK_MAT2_MAT_ROP(^=)
		//! Component-wise matrix reference modulus
		GMTK_MAT2_MAT_ROP(%=)
		//! Component-wise matrix reference shift left
		GMTK_MAT2_MAT_ROP(<<=)
		//! Component-wise matrix reference shift right
		GMTK_MAT2_MAT_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_MAT2_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_MAT2_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_MAT2_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_MAT2_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_MAT2_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_MAT2_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_MAT2_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_MAT2_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_MAT2_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_MAT2_SCL_ROP(>>=)
		
		/////////////////////////////////
		//! MATRIX GENERATOR FUNCTIONS //
		/////////////////////////////////

		//! Generates a 2x2 identity matrix
		static inline constexpr mat<2, 2, T> identity()
		{
			return mat<2, 2, T>(1, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		inline static mat<2, 2, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3)
		{
			return mat<2, 2, T>
				(s0, s2,
				 s1, s3);
		}

		//! Creates a 2x2 matrix using 2 row vectors
		inline static mat<2, 2, T> fromrows(vec<2, T> r0, vec<2, T> r1)
		{
			return mat<2, 2, T>
				(r0.x, r1.x,
				 r0.y, r1.y);
		}

		//! Creates a 2x2 matrix using 2 column vectors
		inline static mat<2, 2, T> fromcols(vec<2, T> c0, vec<2, T> c1)
		{
			return mat<2, 2, T>
				(c0.x, c0.y,
				c1.x, c1.y);
		}
		
		//! Generates a clockwise rotation matrix using an angle
		inline static mat<2, 2, T> rotate(const ang<T>& a)
		{
			const T ca = cos(a.radians());
			const T sa = sin(a.radians());
			return mat<2, 2, T>(ca, sa, -sa, ca);
		}

		//! Generates a clockwise rotation matrix using an angle
		inline static mat<2, 2, T> rotatecw(const ang<T>& a)
		{
			return rotate(a);
		}

		//! Generates a counter-clockwise rotation matrix using an angle
		inline static mat<2, 2, T> rotateccw(const ang<T>& a)
		{
			float ca = cos(a.radians());
			float sa = sin(a.radians());
			return mat<2, 2, T>(ca, -sa, sa, ca);
		}

		//! Generates a scaling matrix using a single scaling value
		inline static mat<2, 2, T> scale(const T& s)
		{
			return mat<2, 2, T>(s, 0, 0, s);
		}

		//! Generates a scaling matrix using an x and y scaling value
		inline static mat<2, 2, T> scale(const T& x, const T& y)
		{
			return mat<2, 2, T>(x, 0, 0, y);
		}

		//! Shears along the x axis
		inline static mat<2, 2, T> shearx(const T& k)
		{
			return mat<2, 2, T>(1, 0, k, 1);
		}

		//! Shears along the y axis
		inline static mat<2, 2, T> sheary(const T& k)
		{
			return mat<2, 2, T>(1, k, 0, 1);
		}

		inline static mat<3, 3, T> translate_affine(const T& x, const T& y)
		{
			mat<3, 3, T> res = mat<3, 3, T>::identity();
			res[2] = vec<T, 3>(x, y, 1);
		}

		inline static mat<3, 3, T> translate_affine(const vec<2, T>& t)
		{
			return translate_affine(t.x, t.y);
		}

	}; //! struct mat

	//! Matrix determinant
	template<typename T>
	inline T det(const mat<2, 2, T>& m)
	{
		return (m.arr[0] * m.arr[3]) 
			- (m.arr[1] * m.arr[2]);
	}

	//! Inverts the matrix, such that m * inverse(m) = the identity
	template<typename T>
	inline mat<2, 2, T> inverse(const mat<2, 2, T>& m)
	{
		return mat<2, 2, T>(m.arr[3], -m.arr[1], -m.arr[2], m.arr[0]) / det(m);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////
	
	typedef mat<2, 2, float>			mat2, mat2f;
	typedef mat<2, 2, double>			mat2d;
	typedef mat<2, 2, unsigned char>	mat2uc;
	typedef mat<2, 2, char>				mat2c;
	typedef mat<2, 2, unsigned short>	mat2us;
	typedef mat<2, 2, short>			mat2s;
	typedef mat<2, 2, unsigned int>		mat2ui;
	typedef mat<2, 2, int>				mat2i;
	typedef mat<2, 2, unsigned long>	mat2ul;
	typedef mat<2, 2, long>				mat2l;

}////

//

#undef GMTK_MAT2_LOOP
#undef GMTK_MAT2_LOOP_2D

#undef GMTK_MAT2_INIT
#undef GMTK_MAT2_UN_OP
#undef GMTK_MAT2_VEC_OP
#undef GMTK_MAT2_SCL_OP
#undef GMTK_MAT2_VEC_ROP
#undef GMTK_MAT2_SCL_ROP

//

#pragma warning(pop)

//

#endif//_GMTK_MAT2_H_