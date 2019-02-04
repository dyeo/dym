#ifndef _GMTK_MAT4_H_
#define _GMTK_MAT4_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "mat.h"

//

#define GMTK_MAT4_LOOP(oper) GMTK_STATIC_LOOP(i, 16, oper)

#define GMTK_MAT4_LOOP_2D(oper) GMTK_STATIC_2D_LOOP(i, j, 4, 4, oper)

//

#define GMTK_MAT4_INIT(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) : arr { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p } { }

#define GMTK_MAT4_UN_OP(op) \
	inline mat<4, 4, T> operator op () const \
	{ mat<4, 4, T> res(static_cast<T>(0)); GMTK_MAT4_LOOP(res.arr[i] = op arr[i]); return res; }

#define GMTK_MAT4_MAT_OP(op) \
	inline mat<4, 4, T> operator op (const mat<4, 4, T>& v) const \
	{ mat<4, 4, T> res(static_cast<T>(0)); GMTK_MAT4_LOOP(res.arr[i] = arr[i] op v.arr[i]); return res; }

#define GMTK_MAT4_SCL_OP(op) \
	inline mat<4, 4, T> operator op (const T& v) const \
	{ mat<4, 4, T> res(static_cast<T>(0)); GMTK_MAT4_LOOP(res.arr[i] = arr[i] op v); return res; }

#define GMTK_MAT4_MAT_ROP(op) \
	inline mat<4, 4, T>& operator op (const mat<4, 4, T>& v) \
	{ GMTK_MAT4_LOOP(arr[i] op v.arr[i]); return *this; }

#define GMTK_MAT4_SCL_ROP(op) \
	inline mat<4, 4, T>& operator op (const T& v) \
	{ GMTK_MAT4_LOOP(arr[i] op v); return *this; }

//

namespace GMTK_NAMESPACE
{////

	//! A column-major matrix spanning r rows and c columns
	template <typename T> struct mat <4, 4, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		inline constexpr int rows() const
		{
			return 4;
		}

		inline constexpr int cols() const
		{
			return 4;
		}

		inline constexpr int dim() const
		{
			return 4;
		}

		//! Unioned data members
		union
		{
			struct { vec<4, T> data[4]; };
			struct { T arr[16]; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline mat()
			GMTK_MAT4_INIT(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
						   static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
						   static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
						   static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1))

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> l)
			GMTK_MAT4_INIT(     *(l.begin()),  *(l.begin() + 1),  *(l.begin() + 2),  *(l.begin() + 3),
						    *(l.begin() + 4),  *(l.begin() + 5),  *(l.begin() + 6),  *(l.begin() + 7),
						    *(l.begin() + 8),  *(l.begin() + 9), *(l.begin() + 10), *(l.begin() + 11),
						   *(l.begin() + 12), *(l.begin() + 13), *(l.begin() + 14), *(l.begin() + 15))

		//! Copy constructor
		inline mat(const mat<4, 4, T>& v)
			GMTK_MAT4_INIT( v.arr[0],  v.arr[1],  v.arr[2],  v.arr[3],
						    v.arr[4],  v.arr[5],  v.arr[6],  v.arr[7],
						    v.arr[8],  v.arr[9], v.arr[10], v.arr[11],
						   v.arr[12], v.arr[13], v.arr[14], v.arr[15])
			
		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit inline mat(const mat<4, 4, U>& v)
			GMTK_MAT4_INIT( static_cast<T>(v.arr[0]),  static_cast<T>(v.arr[1]),  static_cast<T>(v.arr[2]),  static_cast<T>(v.arr[3]),
						    static_cast<T>(v.arr[4]),  static_cast<T>(v.arr[5]),  static_cast<T>(v.arr[6]),  static_cast<T>(v.arr[7]),
						    static_cast<T>(v.arr[8]),  static_cast<T>(v.arr[9]), static_cast<T>(v.arr[10]), static_cast<T>(v.arr[11]),
						   static_cast<T>(v.arr[12]), static_cast<T>(v.arr[13]), static_cast<T>(v.arr[14]), static_cast<T>(v.arr[15]))

		//! Fill constructor
		explicit inline mat(const T& s) 
			GMTK_MAT4_INIT(s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s)

		//! Array initializer
		explicit inline mat(const T* a)
			GMTK_MAT4_INIT( a[0],  a[1],  a[2],  a[3],
						    a[4],  a[5],  a[6],  a[7],
						    a[8],  a[9], a[10], a[11],
						   a[12], a[13], a[14], a[15])

		//! Value constructor
		inline mat(const T& s0, const T& s1, const T& s2, const T& s3,
			const T& s4, const T& s5, const T& s6, const T& s7,
			const T& s8, const T& s9, const T& s10, const T& s11,
			const T& s12, const T& s13, const T& s14, const T& s15)
			GMTK_MAT4_INIT( s0,  s1,  s2,  s3,
						    s4,  s5,  s6,  s7,
						    s8,  s9, s10, s11,
						   s12, s13, s14, s15)
			
		//! Explicit type-conversionm value constructor
		template<typename U>
		explicit inline mat(const U& s0, const U& s1, const U& s2, const U& s3,
			const U& s4, const U& s5, const U& s6, const U& s7,
			const U& s8, const U& s9, const U& s10, const U& s11,
			const U& s12, const U& s13, const U& s14, const U& s15)
			GMTK_MAT4_INIT( static_cast<T>(s0),  static_cast<T>(s1),  static_cast<T>(s2),  static_cast<T>(s3),
						    static_cast<T>(s4),  static_cast<T>(s5),  static_cast<T>(s6),  static_cast<T>(s7),
						    static_cast<T>(s8),  static_cast<T>(s9), static_cast<T>(s10), static_cast<T>(s11),
						   static_cast<T>(s12), static_cast<T>(s13), static_cast<T>(s14), static_cast<T>(s15))

		//! Inserts a 2x2 matrix into the top-left portion of a 4x4 identity matrix
		//! ident adjusts the identity value
		inline mat(const mat<2, 2, T>& m, const T& ident = static_cast<T>(1))
			GMTK_MAT4_INIT(m.arr[0], m.arr[1],     0,     0, 
						   m.arr[2], m.arr[3],     0,     0, 
							      0,        0, ident,     0, 
				                  0,	    0,     0, ident)

		//! Inserts a 3x3 matrix into the top-left portion of a 4x4 identity matrix
		//! ident adjusts the identity value
		inline mat(const mat<3, 3, T>& m, const T& ident = static_cast<T>(1))
			GMTK_MAT4_INIT(m.arr[0], m.arr[1], m.arr[2],     0,
						   m.arr[3], m.arr[4], m.arr[5],     0,
						   m.arr[6], m.arr[7], m.arr[8],     0,
						          0,        0,        0, ident)

		//! Creates a homogeneous transformation matrix out of a rotation matrix and a displacement vector
		inline mat(const mat<3, 3, T>& r, const vec<3, T>& d)
			GMTK_MAT4_INIT(r.arr[0],   r.arr[1],  r.arr[2], 0,
						   r.arr[3],   r.arr[4],  r.arr[5], 0, 
						   r.arr[6],   r.arr[7],  r.arr[8], 0,
						   d.data[0], d.data[1], d.data[2], static_cast<T>(1))

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
		inline vec<4, T> col(const int i) const {
			return data[i];
		}

		//! Row function - returns row as vector of T
		inline vec<4, T> row(const int i) const {
			vec<4, T> v = vec4(arr[i],arr[i+4],arr[i+8],arr[i+12]);
			return v;
		}

		//! Matrix index operator - returns column as vector of T
		inline vec<4, T>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column as vector of T
		inline const vec<4, T>& operator[](const int i) const {
			return data[i];
		}

		//! Matrix linear array index operator - returns element as T
		inline T& operator()(const int i) {
			return arr[i];
		}

		//! Matrix linear array const index operator - returns element as T
		inline const T& operator()(const int i) const {
			return arr[i];
		}

		///////////////////////
		//! ACCESS FUNCTIONS //
		///////////////////////

		//! right
		inline vec<3, T> right() const {
			return data[0];
		}

		//! up
		inline vec<3, T> up() const {
			return data[1];
		}

		//! forward
		inline vec<3, T> forward() const {
			return data[2];
		}

		//! translation
		inline vec<3, T> translation() const {
			return data[3];
		}

		////////////////
		//! OPERATORS //
		////////////////
		
		//! Component-wise unary negation
		GMTK_MAT4_UN_OP(-)
		//! Component-wise unary negation
		GMTK_MAT4_UN_OP(~)
		//! Vector assignment
		GMTK_MAT4_MAT_ROP(=)
		
		//! Component-wise matrix addition
		GMTK_MAT4_MAT_OP(+)		
		//! Component-wise matrix subtraction
		GMTK_MAT4_MAT_OP(-)		
		//! Component-wise matrix OR
		GMTK_MAT4_MAT_OP(|)
		//! Component-wise matrix AND
		GMTK_MAT4_MAT_OP(&)
		//! Component-wise matrix XOR
		GMTK_MAT4_MAT_OP(^)
		//! Component-wise matrix modulus
		GMTK_MAT4_MAT_OP(%)
		//! Component-wise matrix shift left
		GMTK_MAT4_MAT_OP(<<)
		//! Component-wise matrix shift right
		GMTK_MAT4_MAT_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_MAT4_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_MAT4_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_MAT4_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_MAT4_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_MAT4_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_MAT4_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_MAT4_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_MAT4_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_MAT4_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_MAT4_SCL_OP(>>)
							
		//! Component-wise matrix reference addition
		GMTK_MAT4_MAT_ROP(+=)		
		//! Component-wise matrix reference subtraction
		GMTK_MAT4_MAT_ROP(-=)
		//! Component-wise matrix reference OR
		GMTK_MAT4_MAT_ROP(|=)
		//! Component-wise matrix reference AND
		GMTK_MAT4_MAT_ROP(&=)
		//! Component-wise matrix reference XOR
		GMTK_MAT4_MAT_ROP(^=)
		//! Component-wise matrix reference modulus
		GMTK_MAT4_MAT_ROP(%=)
		//! Component-wise matrix reference shift left
		GMTK_MAT4_MAT_ROP(<<=)
		//! Component-wise matrix reference shift right
		GMTK_MAT4_MAT_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_MAT4_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_MAT4_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_MAT4_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_MAT4_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_MAT4_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_MAT4_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_MAT4_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_MAT4_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_MAT4_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_MAT4_SCL_ROP(>>=)

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! returns an identity matrix
		static inline constexpr mat<4, 4, T> identity()
		{
			return mat<4, 4, T>
				(1, 0, 0, 0,
				 0, 1, 0, 0,
				 0, 0, 1, 0,
				 0, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		inline static mat<4, 4, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8, const T &s9, const T &s10, const T &s11, const T &s12, const T &s13, const T &s14, const T &s15)
		{
			return mat<4, 4, T>
				(s0, s4, s8, s12,
				s1, s5, s9, s13,
				s2, s6, s10, s14,
				s3, s7, s11, s15);
		}

		//! Creates a 4x4 matrix using 4 row vectors
		inline static mat<4, 4, T> fromrows(vec<4, T> r0, vec<4, T> r1, vec<4, T> r2, vec<4, T> r3)
		{
			return mat<4, 4, T>(r0.x, r1.x, r2.x, r3.x,
				r0.y, r1.y, r2.y, r3.y,
				r0.z, r1.z, r2.z, r3.z,
				r0.w, r1.w, r2.w, r3.w);
		}

		//! Creates a 4x4 matrix using 4 column vectors
		inline static mat<4, 4, T> fromcols(vec<4, T> c0, vec<4, T> c1, vec<4, T> c2, vec<4, T> c3)
		{
			return mat<4, 4, T>
				(c0.x, c0.y, c0.z, c0.w,
				c1.x, c1.y, c1.z, c1.w,
				c2.x, c2.y, c2.z, c2.w,
				c3.x, c3.y, c3.z, c3.w );
		}

		inline static mat<4, 4, T> rotate(const ang<T>& an, const vec<3, T>& ax)
		{
			const T c = cos(an.radians());
			const T s = sin(an.radians());
			const T t = 1 - c;
			return mat<4, 4, T>
				((t*ax.x*ax.x) + c, (t*ax.x*ax.y) + ax.z*s, (t*ax.x*ax.z) - ax.y*s, 0,
				(t*ax.x*ax.y) - ax.z*s, (t*ax.y*ax.y) + c, (t*ax.y*ax.z) + ax.x*s, 0,
				(t*ax.x*ax.z) + ax.y*s, (t*ax.y*ax.z) - ax.x*s, (t*ax.z*ax.z) + c, 0,
				 0, 0, 0, 1);
		}

		inline static mat<4, 4, T> rotatex(const ang<T>& x)
		{
			const T c = cos(x.radians());
			const T s = sin(x.radians());
			return mat<4, 4, T>
				(1, 0, 0, 0,
				0, c, s, 0,
				0, -s, c, 0,
				0, 0, 0, 1);
		}

		inline static mat<4, 4, T> rotatey(const ang<T>& x)
		{
			const T c = cos(x.radians());
			const T s = sin(x.radians());
			return mat<4, 4, T>
				(c, 0, -s, 0,
				0, 1, 0, 0,
				s, 0, c, 0,
				0, 0, 0, 1);
		}

		inline static mat<4, 4, T> rotatez(const ang<T>& x)
		{
			const T c = cos(x.radians());
			const T s = sin(x.radians());
			return mat<4, 4, T>
				(c, s, 0, 0,
				-s, c, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		inline static mat<4, 4, T> scale(const T& s)
		{
			return mat<4, 4, T>
				(s, 0, 0, 0, 
				0, s, 0, 0, 
				0, 0, s, 0,   
				0, 0, 0, 1);
		}

		inline static mat<4, 4, T> scale(const T& x, const T& y, const T& z)
		{
			return mat<4, 4, T>
				(x, 0, 0, 0, 
				0, y, 0, 0, 
				0, 0, z, 0, 
				0, 0, 0, 1);
		}

		inline static mat<4, 4, T> scale(const vec<3, T>& v)
		{
			return mat<4, 4, T>
				(v.x, 0, 0, 0, 
				0, v.y, 0, 0, 
				0, 0, v.z, 0,	
				0, 0, 0, 1);
		}

		inline static mat<4, 4, T> translate(const T& x, const T& y, const T& z)
		{
			return mat<4, 4, T>
				(1, 0, 0, 0, 
				0, 1, 0, 0, 
				0, 0, 1, 0, 
				x, y, z, 1);
		}

		inline static mat<4, 4, T> translate(const vec<3, T>& v)
		{
			return translate(v.x, v.y, v.z);
		}

		//! generates a generic frustum transformation
		inline static mat<4, 4, T> frustum(const T &left, const T &right, const T &bottom, const T &top, const T &near, const T &far)
		{
			const T n2 = 2 * near;
			const T rml = right - left;
			const T tmb = top - bottom;
			const T nmf = near - far;

			return mat<4, 4, T>
				(n2 / rml, 0.f, 0.f, 0.f,
				 0.f, n2 / tmb, 0.f, 0.f,
				 (right + left) / rml, (top + bottom) / tmb, (near + far) / nmf, -1.f,
				 0.f, 0.f, (n2*far) / nmf, 0.f);
		}

		//! generates a 3d-perspective frustum transformation
		inline static mat<4, 4, T> perspective(const ang<T> &fovy, const T &aspect, const T &near, const T &far)
		{
			const T ys = static_cast<T>(1.0) / tan(fovy.radians()*static_cast<T>(0.5));
			const T xs = ys / aspect;
			const T nmf = near - far;
			const T B = (near + far) / nmf;
			const T C = (static_cast<T>(2.0) * near * far) / nmf;

			return mat<4, 4, T>(
				 xs, 0, 0, 0,
				 0, ys, 0, 0,
				 0, 0, B, -1,
				 0, 0, C, 0);
		}

		//! generates a 3d-orthographic (flat) frustum transformation
		inline static mat<4, 4, T> ortho(const T &left, const T &right, const T &bottom, const T &top, const T &near, const T &far)
        {
            return mat<4, 4, T>
                (static_cast<T>(2.0) / (right - left), 0, 0, 0,
                0, static_cast<T>(2.0) / (top - bottom), 0, 0,
                0, 0, static_cast<T>(2.0) / (near - far), 0,
                (left + right) / (left - right), (bottom + top) / (bottom - top), (near + far) / (far - near), 1);
        }

		//! generates a catmull-rom identity transformation
		inline static mat<4, 4, T> catmull()
		{
			return mat<4, 4, T>::roworder(
				-0.5f, 1.5f, -1.5f, 0.5f,
				1.0f, -2.5f, 2.0f, -0.5f,
				-0.5f, 0.0f, 0.5f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f);
		}

		//! generates a bezier identity transformation
		inline static mat<4, 4, T> bezier()
		{
			return mat<4, 4, T>::roworder(
				-1.0f, 3.0f,-3.0f, 1.0f,
				 3.0f,-6.0f, 3.0f, 0.0f,
				-3.0f, 3.0f, 0.0f, 0.0f,
				 1.0f, 0.0f, 0.0f, 0.0f);
		}

	}; //! struct mat

	//! Matrix determinant
	template<typename T>
	inline T det(const mat<4, 4, T>& m)
	{
		return (m.arr[0] * m.arr[5] * m.arr[10] * m.arr[15]) 
			 - (m.arr[0] * m.arr[5] * m.arr[11] * m.arr[14]) 
			 - (m.arr[0] * m.arr[6] * m.arr[9] * m.arr[15]) 
			 + (m.arr[0] * m.arr[6] * m.arr[11] * m.arr[13]) 
			 + (m.arr[0] * m.arr[7] * m.arr[9] * m.arr[14]) 
			 - (m.arr[0] * m.arr[7] * m.arr[10] * m.arr[13]) 
			 - (m.arr[1] * m.arr[4] * m.arr[10] * m.arr[15]) 
			 + (m.arr[1] * m.arr[4] * m.arr[11] * m.arr[14]) 
			 + (m.arr[1] * m.arr[6] * m.arr[8] * m.arr[15]) 
			 - (m.arr[1] * m.arr[6] * m.arr[11] * m.arr[12]) 
			 - (m.arr[1] * m.arr[7] * m.arr[8] * m.arr[14])
			 + (m.arr[1] * m.arr[7] * m.arr[10] * m.arr[12]) 
			 + (m.arr[2] * m.arr[4] * m.arr[9] * m.arr[15]) 
			 - (m.arr[2] * m.arr[4] * m.arr[11] * m.arr[13]) 
			 - (m.arr[2] * m.arr[5] * m.arr[8] * m.arr[15]) 
			 + (m.arr[2] * m.arr[5] * m.arr[11] * m.arr[12]) 
			 + (m.arr[2] * m.arr[7] * m.arr[8] * m.arr[13]) 
			 - (m.arr[2] * m.arr[7] * m.arr[9] * m.arr[12]) 
			 - (m.arr[3] * m.arr[4] * m.arr[9] * m.arr[14]) 
			 + (m.arr[3] * m.arr[4] * m.arr[10] * m.arr[13]) 
			 + (m.arr[3] * m.arr[5] * m.arr[8] * m.arr[14]) 
			 - (m.arr[3] * m.arr[5] * m.arr[10] * m.arr[12]) 
			 - (m.arr[3] * m.arr[6] * m.arr[8] * m.arr[13]) 
			 + (m.arr[3] * m.arr[6] * m.arr[9] * m.arr[12]);
	}

	//! Inverts the matrix, such that m * inverse(m) = the identity
	template<typename T>
	inline mat<4, 4, T> inverse(const mat<4, 4, T>& m)
	{
		return adjoint(m) / det(m);
	}

	template<typename T>
	inline mat<4, 4, T> fastinverse(const mat<4, 4, T>& m)
	{
		mat3 rotation = m;
		vec3 translation(m.translation());

		rotation = transpose(rotation);

		translation = -rotation * translation;

		return mat4(rotation, translation);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef mat<4, 4, float>			mat4, mat4f;
	typedef mat<4, 4, double>			mat4d;
	typedef mat<4, 4, unsigned char>	mat4uc;
	typedef mat<4, 4, char>				mat4c;
	typedef mat<4, 4, unsigned short>	mat4us;
	typedef mat<4, 4, short>			mat4s;
	typedef mat<4, 4, unsigned int>		mat4ui;
	typedef mat<4, 4, int>				mat4i;
	typedef mat<4, 4, unsigned long>	mat4ul;
	typedef mat<4, 4, long>				mat4l;

}////

//

#undef GMTK_MAT4_LOOP
#undef GMTK_MAT4_LOOP_2D

#undef GMTK_MAT4_INIT
#undef GMTK_MAT4_UN_OP
#undef GMTK_MAT4_VEC_OP
#undef GMTK_MAT4_SCL_OP
#undef GMTK_MAT4_VEC_ROP
#undef GMTK_MAT4_SCL_ROP

//

#pragma warning(pop)

//

#endif//_GMTK_MAT4_H_