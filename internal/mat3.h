#ifndef _GMTK_MAT3_H_
#define _GMTK_MAT3_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "mat.h"

//

#define GMTK_MAT3_LOOP(oper) GMTK_STATIC_LOOP(i, 9, oper)

#define GMTK_MAT3_LOOP_2D(oper) GMTK_STATIC_2D_LOOP(i, j, 3, 3, oper)

//

#define GMTK_MAT3_INIT(a,b,c,d,e,f,g,h,i) : arr { a, b, c, d, e, f, g, h, i } { }

#define GMTK_MAT3_UN_OP(op) \
	inline mat<3, 3, T> operator op () const \
	{ mat<3, 3, T> res(static_cast<T>(0)); GMTK_MAT3_LOOP(res.arr[i] = op arr[i]); return res; }

#define GMTK_MAT3_MAT_OP(op) \
	inline mat<3, 3, T> operator op (const mat<3, 3, T>& v) const \
	{ mat<3, 3, T> res(static_cast<T>(0)); GMTK_MAT3_LOOP(res.arr[i] = arr[i] op v.arr[i]); return res; }

#define GMTK_MAT3_SCL_OP(op) \
	inline mat<3, 3, T> operator op (const T& v) const \
	{ mat<3, 3, T> res(static_cast<T>(0)); GMTK_MAT3_LOOP(res.arr[i] = arr[i] op v); return res; }

#define GMTK_MAT3_MAT_ROP(op) \
	inline mat<3, 3, T>& operator op (const mat<3, 3, T>& v) \
	{ GMTK_MAT3_LOOP(arr[i] op v.arr[i]); return *this; }

#define GMTK_MAT3_SCL_ROP(op) \
	inline mat<3, 3, T>& operator op (const T& v) \
	{ GMTK_MAT3_LOOP(arr[i] op v); return *this; }

//

namespace GMTK_NAMESPACE
{////

	//! A column-major matrix spanning r rows and c columns
	template <typename T> struct mat <3, 3, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		inline constexpr int rows() const
		{
			return 3;
		}

		inline constexpr int cols() const
		{
			return 3;
		}

		inline constexpr int dim() const
		{
			return 3;
		}

		//! Unioned data members
		union
		{
			struct { vec<3, T> data[3]; };
			struct { T arr[9]; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline mat()
			GMTK_MAT3_INIT(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), 
						   static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), 
						   static_cast<T>(0), static_cast<T>(0), static_cast<T>(1))

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> l)
			GMTK_MAT3_INIT(    *(l.begin()), *(l.begin() + 1), *(l.begin() + 2), 
						   *(l.begin() + 3), *(l.begin() + 4), *(l.begin() + 5), 
						   *(l.begin() + 6), *(l.begin() + 7), *(l.begin() + 8))

		//! Copy constructor
		inline mat(const mat<3, 3, T>& v)
			GMTK_MAT3_INIT(v.arr[0], v.arr[1], v.arr[2],
						   v.arr[3], v.arr[4], v.arr[5],
						   v.arr[6], v.arr[7], v.arr[8])

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit inline mat(const mat<3, 3, U>& v)
			GMTK_MAT3_INIT(static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]),
						   static_cast<T>(v.arr[3]), static_cast<T>(v.arr[4]), static_cast<T>(v.arr[5]),
						   static_cast<T>(v.arr[6]), static_cast<T>(v.arr[7]), static_cast<T>(v.arr[8]))

		//! Fill constructor
		explicit inline mat(const T& s) 
			GMTK_MAT3_INIT(s,s,s,s,s,s,s,s,s)

		//! Array initializer
		explicit inline mat(const T* a)
			GMTK_MAT3_INIT(a[0], a[1], a[2],
						   a[3], a[4], a[5],
						   a[6], a[7], a[8])
			
		//! Value constructor
		inline mat(const T& s0, const T& s1, const T& s2, const T& s3, const T& s4, const T& s5, const T& s6, const T& s7, const T& s8)
			GMTK_MAT3_INIT(s0, s1, s2,
						   s3, s4, s5,
						   s6, s7, s8)
			
		//! Explicit type-conversionm value constructor
		template<typename U>
		explicit inline mat(const U& s0, const U& s1, const U& s2, const U& s3, const U& s4, const U& s5, const U& s6, const U& s7, const U& s8)
			GMTK_MAT3_INIT(static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2),
						   static_cast<T>(s3), static_cast<T>(s4), static_cast<T>(s5),
						   static_cast<T>(s6), static_cast<T>(s7), static_cast<T>(s8))

		//! Inserts a 2x2 matrix into the top-left portion of a 3x3 identity matrix
		//! ident adjusts the identity value
		inline mat(const mat<2, 2, T>& m, const T& ident = static_cast<T>(1))
			GMTK_MAT3_INIT(m.arr[0], m.arr[1],     0,
						   m.arr[2], m.arr[3],     0,
							      0,        0, ident)

		//! Constructs a 3x3 matrix using the top-left portion of a 4x4 matrix
		inline mat(const mat<4, 4, T>& m)
			GMTK_MAT3_INIT(m.arr[0], m.arr[1], m.arr[2],
						   m.arr[4], m.arr[5], m.arr[6],
						   m.arr[8], m.arr[9], m.arr[10])

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
		inline vec<3, T> col(const int i) const {
			return data[i];
		}

		//! Row function - returns row as vector of T
		inline vec<3, T> row(const int i) const {
			vec<3, T> v = vec<3, T>(arr[i], arr[i + 3], arr[i + 6]);
			return v;
		}

		//! Matrix index operator - returns column
		inline vec<3, T>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column
		inline const vec<3, T>& operator[](const int i) const {
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
		GMTK_MAT3_UN_OP(-)
		//! Component-wise unary negation
		GMTK_MAT3_UN_OP(~)
		//! Vector assignment
		GMTK_MAT3_MAT_ROP(=)
		
		//! Component-wise matrix addition
		GMTK_MAT3_MAT_OP(+)		
		//! Component-wise matrix subtraction
		GMTK_MAT3_MAT_OP(-)		
		//! Component-wise matrix OR
		GMTK_MAT3_MAT_OP(|)
		//! Component-wise matrix AND
		GMTK_MAT3_MAT_OP(&)
		//! Component-wise matrix XOR
		GMTK_MAT3_MAT_OP(^)
		//! Component-wise matrix modulus
		GMTK_MAT3_MAT_OP(%)
		//! Component-wise matrix shift left
		GMTK_MAT3_MAT_OP(<<)
		//! Component-wise matrix shift right
		GMTK_MAT3_MAT_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_MAT3_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_MAT3_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_MAT3_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_MAT3_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_MAT3_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_MAT3_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_MAT3_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_MAT3_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_MAT3_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_MAT3_SCL_OP(>>)
							
		//! Component-wise matrix reference addition
		GMTK_MAT3_MAT_ROP(+=)		
		//! Component-wise matrix reference subtraction
		GMTK_MAT3_MAT_ROP(-=)
		//! Component-wise matrix reference OR
		GMTK_MAT3_MAT_ROP(|=)
		//! Component-wise matrix reference AND
		GMTK_MAT3_MAT_ROP(&=)
		//! Component-wise matrix reference XOR
		GMTK_MAT3_MAT_ROP(^=)
		//! Component-wise matrix reference modulus
		GMTK_MAT3_MAT_ROP(%=)
		//! Component-wise matrix reference shift left
		GMTK_MAT3_MAT_ROP(<<=)
		//! Component-wise matrix reference shift right
		GMTK_MAT3_MAT_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_MAT3_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_MAT3_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_MAT3_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_MAT3_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_MAT3_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_MAT3_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_MAT3_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_MAT3_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_MAT3_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_MAT3_SCL_ROP(>>=)

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Returns an identity matrix
		static inline constexpr mat<3, 3, T> identity()
		{
			return mat<3, 3, T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		inline static mat<3, 3, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8)
		{
			return mat<3, 3, T>
				(s0, s3, s6,
				s1, s4, s7,
				s2, s5, s8);
		}

		//! Creates a 3x3 matrix using 3 row vectors
		inline static mat<3, 3, T> fromrows(vec<3, T> r0, vec<3, T> r1, vec<3, T> r2)
		{
			return mat<3, 3, T>
				(r0.x, r1.x, r2.x,
				r0.y, r1.y, r2.y,
				r0.z, r1.z, r2.z);
		}

		//! Creates a 3x3 matrix using 3 column vectors
		inline static mat<3, 3, T> fromcols(vec<3, T> c0, vec<3, T> c1, vec<3, T> c2)
		{
			return mat<3, 3, T>
				(c0.x, c0.y, c0.z,
				c1.x, c1.y, c1.z,
				c2.x, c2.y, c2.z);
		}

		//! Rotate an axis about a given angle
		inline static mat<3, 3, T> rotate(const ang<T>& an, const vec<3, T>& ax)
		{
			T c = cos(an.radians());
			T s = sin(an.radians());
			T t = 1 - c;
			return mat<3, 3, T>
				((t*ax.x*ax.x) + c,			(t*ax.x*ax.y) + ax.z*s,		(t*ax.x*ax.z) - ax.y*s,
				 (t*ax.x*ax.y) - ax.z*s,	(t*ax.y*ax.y) + c,			(t*ax.y*ax.z) + ax.x*s,
				 (t*ax.x*ax.z) + ax.y*s,	(t*ax.y*ax.z) - ax.x*s,		(t*ax.z*ax.z) + c);
		}

		//! Rotate axis x about a given angle
		inline static mat<3, 3, T> rotatex(const ang<T>& x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<3, 3, T>
				(1, 0, 0, 
				 0, c, s,
				 0, -s, c);
		}

		//! Rotate axis y about a given angle
		inline static mat<3, 3, T> rotatey(const ang<T>& x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<3, 3, T>
				(c, 0, -s,
				 0, 1, 0,
				 s, 0, c);
		}

		//! Rotate axis z about a given angle
		inline static mat<3, 3, T> rotatez(const ang<T>& x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<3, 3, T>
				(c, s, 0,
				-s, c, 0,
				 0, 0, 1);
		}

		inline static mat<3, 3, T> scale(const T& s)
		{
			return mat<3, 3, T>(s, 0, 0, 0, s, 0, 0, 0, s);
		}

		inline static mat<3, 3, T> scale(const T& x, const T& y, const T& z)
		{
			return mat<3, 3, T>(x, 0, 0, 0, y, 0, 0, 0, z);
		}

		inline static mat<3, 3, T> scale(const vec<3, T>& v)
		{
			return mat<3, 3, T>(v.x, 0, 0, 0, v.y, 0, 0, 0, v.z);
		}

		inline static mat<3, 3, T> translate(const T& x, const T& y)
		{
			return mat<3, 3, T>(1, 0, 0, 0, 1, 0, x, y, 1);
		}

		inline static mat<3, 3, T> translate(const vec<3, T>& v)
		{
			return translate(v.x, v.y, v.z);
		}

		inline static mat<4, 4, T> translate_affine(const T& x, const T& y, const T& z)
		{
			mat<4, 4, T> res = mat<4, 4, T>::identity();
			res[3] = vec<4, T>(x, y, z, 1);
			return res;
		}

		inline static mat<4, 4, T> translate_affine(const vec<3, T>& v)
		{
			return translate(v.x, v.y, v.z);
		}

	}; //! struct mat

	//! Matrix determinant
	template<typename T>
	inline T det(const mat<3, 3, T>& m)
	{
		return (m.arr[0] * m.arr[4] * m.arr[8]) 
			- (m.arr[0] * m.arr[5] * m.arr[7]) 
			- (m.arr[1] * m.arr[3] * m.arr[8]) 
			+ (m.arr[1] * m.arr[5] * m.arr[6]) 
			+ (m.arr[2] * m.arr[3] * m.arr[7]) 
			- (m.arr[2] * m.arr[4] * m.arr[6]);
	}

	//! Inverts the matrix, such that m * inverse(m) = the identity
	template<typename T>
	inline mat<3, 3, T> inverse(const mat<3, 3, T>& m)
	{
		return adjoint(m) / det(m);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef mat<3, 3, float>			mat3, mat3f;
	typedef mat<3, 3, double>			mat3d;
	typedef mat<3, 3, unsigned char>	mat3uc;
	typedef mat<3, 3, char>				mat3c;
	typedef mat<3, 3, unsigned short>	mat3us;
	typedef mat<3, 3, short>			mat3s;
	typedef mat<3, 3, unsigned int>		mat3ui;
	typedef mat<3, 3, int>				mat3i;
	typedef mat<3, 3, unsigned long>	mat3ul;
	typedef mat<3, 3, long>				mat3l;

}////

//

#undef GMTK_MAT3_LOOP
#undef GMTK_MAT3_LOOP_2D

#undef GMTK_MAT3_INIT
#undef GMTK_MAT3_UN_OP
#undef GMTK_MAT3_VEC_OP
#undef GMTK_MAT3_SCL_OP
#undef GMTK_MAT3_VEC_ROP
#undef GMTK_MAT3_SCL_ROP

//

#pragma warning(pop)

//

#endif//_GMTK_MAT3_H_