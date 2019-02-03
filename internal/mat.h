#ifndef _GMTK_MAT_H_
#define _GMTK_MAT_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "..\util.h"
#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

//

#include <math.h>
#include <ostream>

//

#define GMTK_MAT_IDENT_LOOP(oper) GMTK_UNROLL_LOOP(i, GMTK_MIN_OF(r, c), oper)

#define GMTK_MAT_LOOP(oper) GMTK_UNROLL_LONG_LOOP(i, r*c, oper)

#define GMTK_MAT_LOOP_2D(oper) GMTK_UNROLL_2D_LOOP(i, j, c, r, oper)

//

#define GMTK_MAT_UN_OP(op) \
	inline mat<c, r, T> operator op () const \
	{ mat<c, r, T> res(static_cast<T>(0)); GMTK_mat_LOOP(res.arr[i] = op arr[i]); return res; }

#define GMTK_MAT_MAT_OP(op) \
	inline mat<c, r, T> operator op (const mat<c, r, T>& v) const \
	{ mat<c, r, T> res(static_cast<T>(0)); GMTK_mat_LOOP(res.arr[i] = arr[i] op v.arr[i]); return res; }

#define GMTK_MAT_SCL_OP(op) \
	inline mat<c, r, T> operator op (const T& v) const \
	{ mat<c, r, T> res(static_cast<T>(0)); GMTK_mat_LOOP(res.arr[i] = arr[i] op v); return res; }

#define GMTK_MAT_MAT_ROP(op) \
	inline mat<c, r, T>& operator op (const mat<c, r, T>& v) \
	{ GMTK_mat_LOOP(arr[i] op v.arr[i]); return *this; }

#define GMTK_MAT_SCL_ROP(op) \
	inline mat<c, r, T>& operator op (const T& v) \
	{ GMTK_mat_LOOP(arr[i] op v); return *this; }

//

#define GMTK_MAT_OPERATION(oper) { mat<c, r, T> res; GMTK_MAT_LOOP(res.arr[i] = oper); return res; }

//

namespace GMTK_NAMESPACE
{////

	//! A column-major matrix spanning r rows and c columns
	template <int c, int r = c, typename T = float>
	struct mat
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		inline constexpr int rows() const
		{
			return r;
		}

		inline constexpr int cols() const
		{
			return c;
		}

		inline constexpr int dim() const
		{
			return GMTK_MIN_OF(r, c);
		}

		//! Unioned data members
		union
		{
			struct { vec<r, T> data[c]; };
			struct { T arr[(c*r)]; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline mat()
		{
			GMTK_MAT_LOOP(arr[i] = static_cast<T>(0));
		}

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> list)
		{
			GMTK_MAT_LOOP(arr[i] = *(list.begin() + i));
		}
		
		//! Copy constructor
		inline mat(const mat<c, r, T>& v) {
			GMTK_MAT_LOOP(arr[i] = v.arr[i]);
		}

		template<int cm, int rm>
		//! Minor matrix constructor
		inline mat(const mat<cm, rm, T>& m)
		{
			GMTK_STATIC_ASSERT((rm < r) && (cm < c));
			GMTK_UNROLL_2D_LOOP(i, j, cm, rm, data[i][j] = m.data[i][j]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> explicit inline mat(const mat<c, r, U>& v) {
			GMTK_MAT_LOOP(arr[i] = static_cast<T>(v.arr[i]));
		}

		//! Fill constructor
		explicit inline mat(const T& s) {
			GMTK_MAT_LOOP(arr[i] = s);
		}

		//! Array initializer
		explicit inline mat(const T* a) {
			GMTK_MAT_LOOP(arr[i] = a[i]);
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////
		
		//! Matrix index operator - returns column
		inline vec<r, T>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column
		inline const vec<r, T>& operator[](const int i) const {
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

		///////////////////////////
		//! ARITHMETIC OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		GMTK_MAT_UN_OP(-)
		//! Component-wise unary negation
		GMTK_MAT_UN_OP(~)
		//! Vector assignment
		GMTK_MAT_MAT_ROP(=)
		
		//! Component-wise matrix addition
		GMTK_MAT_MAT_OP(+)		
		//! Component-wise matrix subtraction
		GMTK_MAT_MAT_OP(-)		
		//! Component-wise matrix OR
		GMTK_MAT_MAT_OP(|)
		//! Component-wise matrix AND
		GMTK_MAT_MAT_OP(&)
		//! Component-wise matrix XOR
		GMTK_MAT_MAT_OP(^)
		//! Component-wise matrix modulus
		GMTK_MAT_MAT_OP(%)
		//! Component-wise matrix shift left
		GMTK_MAT_MAT_OP(<<)
		//! Component-wise matrix shift right
		GMTK_MAT_MAT_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_MAT_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_MAT_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_MAT_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_MAT_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_MAT_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_MAT_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_MAT_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_MAT_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_MAT_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_MAT_SCL_OP(>>)
							
		//! Component-wise matrix reference addition
		GMTK_MAT_MAT_ROP(+=)		
		//! Component-wise matrix reference subtraction
		GMTK_MAT_MAT_ROP(-=)
		//! Component-wise matrix reference OR
		GMTK_MAT_MAT_ROP(|=)
		//! Component-wise matrix reference AND
		GMTK_MAT_MAT_ROP(&=)
		//! Component-wise matrix reference XOR
		GMTK_MAT_MAT_ROP(^=)
		//! Component-wise matrix reference modulus
		GMTK_MAT_MAT_ROP(%=)
		//! Component-wise matrix reference shift left
		GMTK_MAT_MAT_ROP(<<=)
		//! Component-wise matrix reference shift right
		GMTK_MAT_MAT_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_MAT_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_MAT_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_MAT_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_MAT_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_MAT_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_MAT_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_MAT_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_MAT_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_MAT_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_MAT_SCL_ROP(>>=)

		//! Matrix identity
		static mat<c, r, T> identity()
		{
			mat<c, r, T> res(static_cast<T>(0));
			GMTK_MAT_IDENT_LOOP(res.data[i][i] = static_cast<T>(1));
			return res;
		}
		
	}; //! struct mat

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <int c, int r, typename T>
	inline std::ostream& operator<<(std::ostream& os, const mat<c, r, T>& v) {
	#ifdef GMTK_DISPLAY_ROW_COLUMN
		const mat<c, r, T>& t = transpose(v);
		GMTK_UNROLL_LOOP(i, c, os << "| "; GMTK_UNROLL_LOOP(j, r, os << t[i][j] << ' ';); os << "|\n");
	#else
		GMTK_UNROLL_LOOP(i, c, os << v.data[i]; (i < c-1) ? os << '\n' : os << ' ');
	#endif
		return os;
	}

	///////////////////////////////////
	//! MATRIX&MATRIX MULTIPLICATION //
	///////////////////////////////////

	//! Matrix product
	//! Accepts a r1 x c1 matrix and a r2 x c2 matrix where c1 and r2 are equal
	//! Returns a r1 x c2 matrix that is the product of the two original matrices
	//! Is not commutative
	template <int c1, int c2, int r1, int r2, typename T>
	inline mat<c2, r1, T> operator*(const mat<c1, r1, T>& m, const mat<c2, r2, T>& n) {
		GMTK_STATIC_ASSERT(c1 == r2); //! no.columns of m and no.rows of n must be equal!!!
		mat<c2, r1, T> res(static_cast<T>(0));
		GMTK_UNROLL_3D_LOOP(i, j, k, r1, c2, r2, res[j][i] += m.data[k][i] * n.data[j][k]);
		return res;
	}
	
	//! Matrix product (reference)
	//! Accepts two matrices where cols and rows are equal
	//! Is not commutative
	template <int c, int r, typename T>
	inline mat<c, r, T>& operator*=(mat<c, r, T>& m, const mat<c, r, T>& n) {
		mat<c, r, T> res(static_cast<T>(0));
		GMTK_UNROLL_3D_LOOP(i, j, k, r, c, r, res[j][i] += m.data[k][i] * n.data[j][k]);
		return m = res;
	}

	///////////////////////////////////
	//! MATRIX&VECTOR MULTIPLICATION //
	///////////////////////////////////

	//! Matrix-vector multiplication: column vector (matrix row)
	template <int c, int r, typename T>
	inline vec<r, T> operator*(const mat<c, r, T>& m, const vec<r, T>& v) {
		vec<r, T> res(static_cast<T>(0));
		GMTK_UNROLL_2D_LOOP(i, j, r, c, res.data[i] += m.data[j][i] * v.data[j]);
		return res;
	}

	//! Matrix-vector multiplication: row vector (matrix column)
	template <int c, int r, typename T>
	inline vec<c, T> operator*(const vec<c, T>& v, const mat<c, r, T>& m) {
		vec<c, T> res(static_cast<T>(0));
		GMTK_UNROLL_2D_LOOP(i, j, c, r, res.data[i] += m.data[i][j] * v.data[j]);
		return res;
	}

	//! Matrix-vector multiplication: row vector (matrix column, reference)
	template <int c, int r, typename T>
	inline vec<c, T>& operator*=(vec<c, T>& v, const mat<c, r, T>& m) {
		vec<c, T> res(static_cast<T>(0));
		GMTK_UNROLL_2D_LOOP(i, j, c, r, res.data[i] += m.data[i][j] * v.data[j]);
		return v = res;
	}

	///////////////////////////////////
	//! MATRIX&SCALAR MULTIPLICATION //
	///////////////////////////////////
	
	//! Matrix-scalar multiplication
	template <int c, int r, typename T>
	inline const mat<c, r, T> operator*(const T& v, const mat<c, r, T>& m)
		GMTK_MAT_OPERATION(v * m.arr[i])

	//! Matrix-scalar multiplication (odd-typed)
	template <typename U, int c, int r, typename T>
	inline const mat<c, r, T> operator*(const U& v, const mat<c, r, T>& m)
		GMTK_MAT_OPERATION(static_cast<T>(v) * m.arr[i])

	/////////////////////
	//! FREE-FUNCTIONS //
	/////////////////////

	//! Component-wise matrix multiplication
	template <int c, int r, typename T>
	inline mat<c, r, T> mult(const mat<c, r, T>& m, const mat<c, r, T>& n) {
		GMTK_MAT_OPERATOR(m.arr[i] * n.arr[i]);
	}

	//! Returns sum of the matrix diagonal
	template <int c, int r, typename T>
	inline T trace(const mat<c, r, T>& m)
	{
		T res = 0;
		GMTK_MAT_IDENT_LOOP(res += m.data[i][i];);
		return res;
	}

	//! Returns minor matrix of the current matrix, "crossing out" the specified row and column
	template <int c, int r, typename T>
	inline mat<c - 1, r - 1, T> minor(const mat<c, r, T>& m, int rx, int cx)
	{
		mat<c - 1, r - 1, T> res(static_cast<T>(0));

		int mini = 0;
		int minj = 0;

		GMTK_UNROLL_LOOP(i, r,
			if (i != rx)
			{
				minj = 0;
				GMTK_UNROLL_LOOP(j, c,
					if (j != cx)
					{
						res.data[minj][mini] = m.data[j][i];
						minj++;
					}
				);
				mini++;
			}
		);
		return res;
	}

	//! Calculates the determinant of a matrix
	template <int d, typename T>
	inline T det(const mat<d, d, T>& m)
	{
		return _dethelper<T>((T *)m.arr, d);
	}

	template <typename T>
	inline T _dethelper(T *A, const int d)
	{
		if (d == 1) return A[0];
					
		T res = 0;

		T *L = new T[sq(d)];
		T *U = new T[sq(d)];

		_ludecomphelper(A, L, U, d);

		T ls = 1, us = 1;

		for (int s = 0; s < d; ++s)
		{
			ls *= L[s*d + s];
			us *= U[s*d + s];
		}

		res = ls * us;

		delete[] L;
		delete[] U;

		return res;
	}
	
	template <typename T>
	inline void _ludecomphelper(const T *A, T *L, T *U, const int d)
	{
		int i, j, k;
		T sum = 0;

		for (i = 0; i < d; i++)
		{
			U[i*d + i] = 1;
		}

		for (j = 0; j < d; j++)
		{
			for (i = j; i < d; i++)
			{
				sum = 0;
				for (k = 0; k < j; k++) {
					sum = sum + L[i*d + k] * U[k*d + j];
				}
				L[i*d + j] = A[i*d + j] - sum;
			}

			for (i = j; i < d; i++)
			{
				sum = 0;
				for (k = 0; k < j; k++)
				{
					sum = sum + L[j*d + k] * U[k*d + i];
				}
				if (L[j*d + j] == 0)
				{
					return;
				}
				U[j*d + i] = (A[j*d + i] - sum) / L[j*d + j];
			}
		}
	}

	//! Decomposes a matrix into lower and upper traingular cofactor matrices
	template <int d, typename T>
	inline void ludecompose(const mat<d, d, T> &m, mat<d, d, T> &l, mat<d, d, T> &u)
	{
		_ludecomphelper(m.arr, l.arr, u.arr, d);
	}

	//! Flips the matrix along its diagonal (rows become columns, columns become rows)
	template <int r, int c, typename T>
	inline mat<r, c, T> transpose(const mat<c, r, T>& m)
	{
		mat<r, c, T> res(static_cast<T>(0));
		GMTK_MAT_LOOP_2D(res[j][i] = m[i][j]);
		return res;
	}

	//! Generates a matrix one dimension larger that is a composition of the target matrix and an identity matrix
	template <int r, int c, typename T>
	inline mat<c + 1, r + 1, T> affine(const mat<c, r, T>& m)
	{
		mat<c + 1, r + 1, T> res = m;
		res[c][r] = static_cast<T>(1);
		return res;
	}

	template <int d, typename T>
	inline mat<d, d, T> cofactor(const mat<d, d, T>& m)
	{
		mat<d, d, T> res(static_cast<T>(0));
		GMTK_UNROLL_LOOP(j, d,
			GMTK_UNROLL_LOOP(i, d,

				res[i][j] = pow(-1,(i+1)+(j+1)) * det(minor(m, j, i));
				
			);
		);
		return res;
	}

	//! Returns true if the matrix has no inverse, false otherwise
	template <int d, typename T>
	inline bool issingular(const mat<d, d, T>& m)
	{
		return det(m) == static_cast<T>(0);
	}

	//! Returns an adjoint of matrix m
	template <int d, typename T>
	inline mat<d, d, T> adjoint(const mat<d, d, T>& m)
	{
		return transpose(cofactor(m));
	}

	//! Inverts the matrix, such that m * inverse(m) = the identity
	template<int d, typename T>
	inline mat<d, d, T> inverse(const mat<d, d, T>& m)
	{
		return adjoint(m) / det(m);
	}

}////

//

#undef GMTK_MAT_IDENT_LOOP
#undef GMTK_MAT_LOOP
#undef GMTK_MAT_LOOP_2D
#undef GMTK_MAT_UN_OP
#undef GMTK_MAT_MAT_OP
#undef GMTK_MAT_SCL_OP
#undef GMTK_MAT_MAT_ROP
#undef GMTK_MAT_SCL_ROP
#undef GMTK_MAT_OPERATION

//

#pragma warning(pop)

//

#endif //_GMTK_MAT_H_