#ifndef _GMTK_MAT_H_
#define _GMTK_MAT_H_

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

#define GMTK_IDENT_LOOP(oper) GMTK_UNROLL_LOOP(i, GMTK_MIN_OF(r, c), oper)

#define GMTK_MAT_LOOP(oper) GMTK_UNROLL_2D_LOOP(i, j, c, r, oper)

#define GMTK_MAT_LOOP2(oper) GMTK_UNROLL_LONG_LOOP(i, r*c, oper)

#define GMTK_MAT_OPERATOR(oper) { mat<T, r, c> res; GMTK_MAT_LOOP(res[i][j] = oper); return res; }

#define GMTK_MAT_OPERATOR2(oper) { mat<T, r, c> res; GMTK_MAT_LOOP2(res(i) = oper); return res; }

#define GMTK_MAT_REF_OPERATOR(oper) { GMTK_MAT_LOOP(oper); return *this; }

#define GMTK_MAT_REF_OPERATOR2(oper) { GMTK_MAT_LOOP2(oper); return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T, int r, int c>
	//! A column-major matrix spanning r rows and c columns
	struct mat
	{
		//////////////////
		//! DATA MEMBERS //
		//////////////////

		inline int rows() const
		{
			return r;
		}

		inline int cols() const
		{
			return c;
		}

		inline int dim() const
		{
			return GMTK_MIN_OF(r, c);
		}

		//! Unioned data members
		union
		{
			struct { vec<T, r> data[c]; };
			struct { T arr[(c*r)]; };
		};

		//////////////////
		//! CONSTRUCTORS //
		//////////////////

		//! Default constructor
		inline mat()
		{
			GMTK_MAT_LOOP2(arr[i] = static_cast<T>(0));
		}

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		inline mat(std::initializer_list<T> list)
		{
			GMTK_MAT_LOOP2(arr[i] = *(list.begin() + i));
		}
		
		//! Copy constructor
		inline mat(const mat<T, r, c>& v) {
			GMTK_MAT_LOOP2(arr[i] = v.arr[i]);
		}

		template<int rm, int cm>
		//! Minor matrix constructor
		inline mat(const mat<T, rm, cm>& m)
		{
			GMTK_STATIC_ASSERT((rm < r) && (cm < c));
			GMTK_UNROLL_2D_LOOP(i, j, cm, rm, data[i][j] = m.data[i][j]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> explicit inline mat(const mat<U, r, c>& v) {
			GMTK_MAT_LOOP2(arr[i] = static_cast<T>(v.arr[i]));
		}

		//! Fill constructor
		explicit inline mat(const T& s) {
			GMTK_MAT_LOOP2(arr[i] = s);
		}

		//! Array initializer
		explicit inline mat(const T* a) {
			GMTK_MAT_LOOP2(arr[i] = a[i]);
		}

		//

		/*inline mat<T, 3, 3>(const mat<T, 2, 2>& m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = 0;
			arr[3] = m.arr[2];
			arr[4] = m.arr[3];
			arr[5] = 0;
			arr[6] = 0;
			arr[7] = 0;
			arr[8] = 1;
		}

		inline mat<T, 4, 4>(const mat<T, 2, 2>& m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = 0;
			arr[3] = 0;
			arr[4] = m.arr[2];
			arr[5] = m.arr[3];
			arr[6] = 0;
			arr[7] = 0;
			arr[8] = 0;
			arr[9] = 0;
			arr[10] = 1;
			arr[11] = 0;
			arr[12] = 0;
			arr[13] = 0;
			arr[14] = 0;
			arr[15] = 1;
		}

		inline mat<T, 4, 4>(const mat<T, 3, 3>& m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = m.arr[2];
			arr[3] = 0;
			arr[4] = m.arr[4];
			arr[5] = m.arr[5];
			arr[6] = m.arr[6];
			arr[7] = 0;
			arr[8] = m.arr[7];
			arr[9] = m.arr[8];
			arr[10] = m.arr[9];
			arr[11] = 0;
			arr[12] = 0;
			arr[13] = 0;
			arr[14] = 0;
			arr[15] = 1;
		}*/

		//////////////////////
		//! ACCESS OPERATORS //
		//////////////////////
		
		//! Matrix index operator - returns column
		inline vec<T, r>& operator[](const int i) {
			return data[i];
		}

		//! Matrix const index operator - returns column
		inline const vec<T, r>& operator[](const int i) const {
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

		///////////////
		//! OPERATORS //
		///////////////

		//! Returns a negative matrix
		inline mat<T, r, c> operator-() const {
			GMTK_MAT_OPERATOR2(-arr[i]);
		}

		//! Component-wise matrix addition
		inline mat<T, r, c> operator+(const mat<T, r, c>& m) const {
			GMTK_MAT_OPERATOR2(arr[i] + m.arr[i]);
		}

		//! Component-wise matrix subtraction
		inline mat<T, r, c> operator-(const mat<T, r, c>& m) const {
			GMTK_MAT_OPERATOR2(arr[i] - m.arr[i]);
		}
		
		//! Component-wise matrix division
		inline mat<T, r, c> operator/(const mat<T, r, c>& m) const {
			GMTK_MAT_OPERATOR2(arr[i] / m.arr[i]);
		}

		//

		//! Component-wise scalar addition
		inline mat<T, r, c> operator+(const T& s) const {
			GMTK_MAT_OPERATOR2(arr[i] + s);
		}

		//! Component-wise scalar subtraction
		inline mat<T, r, c> operator-(const T& s) const {
			GMTK_MAT_OPERATOR2(arr[i] - s);
		}

		//! Component-wise scalar division
		inline mat<T, r, c> operator/(const T& s) const {
			GMTK_MAT_OPERATOR2(arr[i] / s);
		}

		//! Component-wise scalar multiplication
		inline mat<T, r, c> operator*(const T& s) const {
			GMTK_MAT_OPERATOR2(arr[i] * s);
		}

		//

		//! Component-wise matrix reference addition
		inline mat<T, r, c>& operator+=(const mat<T, r, c>& m) {
			GMTK_MAT_REF_OPERATOR2(arr[i] += m.arr[i]);
		}

		//! Component-wise matrix reference subtraction
		inline mat<T, r, c>& operator-=(const mat<T, r, c>& m) {
			GMTK_MAT_REF_OPERATOR2(arr[i] -= m.arr[i]);
		}

		//! Component-wise matrix reference division
		inline mat<T, r, c>& operator/=(const mat<T, r, c>& m) {
			GMTK_MAT_REF_OPERATOR2(arr[i] /= m.arr[i]);
		}

		//

		//! Component-wise scalar reference addition
		inline mat<T, r, c>& operator+=(const T& s) {
			GMTK_MAT_REF_OPERATOR2(arr[i] += s);
		}

		//! Component-wise scalar reference subtraction
		inline mat<T, r, c>& operator-=(const T& s) {
			GMTK_MAT_REF_OPERATOR2(arr[i] -= s);
		}

		//! Component-wise scalar reference division
		inline mat<T, r, c>& operator/=(const T& s) {
			GMTK_MAT_REF_OPERATOR2(arr[i] /= s);
		}

		//! Component-wise scalar reference multiplication
		inline mat<T, r, c>& operator*=(const T& s) {
			GMTK_MAT_REF_OPERATOR2(arr[i] *= s);
		}

		static mat<T, r, c> identity()
		{
			mat<T, r, c> res;
			GMTK_IDENT_LOOP(res.data[i][i] = static_cast<T>(1));
			return res;
		}
		
	}; //! struct mat

	///////////////////
	//! MATRIX OUTPUT //
	///////////////////

	template <typename T, int r, int c>
	inline std::ostream& operator<<(std::ostream& os, const mat<T, r, c>& v) {
	#ifdef GMTK_DISPLAY_ROW_COLUMN
		const mat<T, r, c>& t = transpose(v);
		GMTK_UNROLL_LOOP(i, c, os << "| "; GMTK_UNROLL_LOOP(j, r, os << t[i][j] << ' ';); os << "|\n");
	#else
		GMTK_UNROLL_LOOP(i, c, os << v.data[i]; (i < c-1) ? os << '\n' : os << ' ');
	#endif
		return os;
	}

	///////////////////////////////////
	//! MATRIX&MATRIX MULTIPLICATION //
	///////////////////////////////////

	template <typename T, int r1, int r2, int c1, int c2> 
	//! Matrix product
	//! Accepts a r1 x c1 matrix and a r2 x c2 matrix where c1 and r2 are equal
	//! Returns a r1 x c2 matrix that is the product of the two original matrices
	//! Is not commutative
	inline mat<T, r1, c2> operator*(const mat<T, r1, c1>& m, const mat<T, r2, c2>& n) {
		GMTK_STATIC_ASSERT(c1 == r2); //! no.columns of m and no.rows of n must be equal!!!
		mat<T, r1, c2> res;
		GMTK_UNROLL_3D_LOOP(i, j, k, r1, c2, r2, res[j][i] += m.data[k][i] * n.data[j][k]);
		return res;
	}

	///////////////////////////////////
	//! MATRIX&VECTOR MULTIPLICATION //
	///////////////////////////////////

	template <typename T, int r, int c>
	//! Matrix-vector multiplication: column vector (matrix row)
	inline const vec<T, c> operator*(const mat<T, r, c>& m, const vec<T, c>& v) {
		vec<T, c> res(static_cast<T>(0));
		GMTK_UNROLL_2D_LOOP(i, j, r, c, res.data[i] += m.data[j][i] * v.data[j]);
		return res;
	}

	template <typename T, int r, int c>
	//! Matrix-vector multiplication: row vector (matrix column)
	inline const vec<T, c> operator*(const vec<T, c>& v, const mat<T, r, c>& m) {
		vec<T, c> res(static_cast<T>(0));
		GMTK_UNROLL_2D_LOOP(i, j, c, r, res.data[i] += m.data[i][j] * v.data[j]);
		return res;
	}

	///////////////////////////
	//! MATRIX FREE-FUNCTIONS //
	///////////////////////////

	template <typename T, int r, int c>
	//! Component-wise matrix multiplication
	inline mat<T, r, c> mult(const mat<T, r, c>& m, const mat<T, r, c>& n) {
		GMTK_MAT_OPERATOR2(m.arr[i] * n.arr[i]);
	}

	template <typename T, int r, int c>
	//! Returns sum of the matrix diagonal
	inline T trace(const mat<T, r, c>& m)
	{
		T res = 0;
		GMTK_IDENT_LOOP(res += m.data[i][i];);
		return res;
	}

	template <typename T, int r, int c>
	//! Returns minor matrix of the current matrix, "crossing out" the specified row and column
	inline mat<T, r - 1, c - 1> minor(const mat<T, r, c>& m, int rx, int cx)
	{
		mat<T, r - 1, c - 1> res;

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
	
	template <typename T, int d>
	//! Calculates the determinant of a matrix
	inline T det(const mat<T, d, d>& m)
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

		lu_decomp(A, L, U, d);

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
	inline void _lu_decomp(const T *A, T *L, T *U, const int d)
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

	template <typename T, int d>
	// decomposes a matrix into lower and upper traingular cofactor matrices
	inline void ludecompose(const mat<T, d, d> &m, mat<T,d,d> &l, mat<T,d,d> &u)
	{
		_lu_decomp(m.arr, l.arr, u.arr, d);
	}

	template <typename T, int r, int c>
	//! Flips the matrix along its diagonal (rows become columns, columns become rows)
	inline mat<T, c, r> transpose(const mat<T, r, c>& m)
	{
		mat<T, c, r> res;
		GMTK_MAT_LOOP(res[j][i] = m[i][j]);
		return res;
	}

	template <typename T, int r, int c>
	//! Generates a matrix one dimension larger that is a composition of the target matrix and an identity matrix
	inline mat<T, r + 1, c + 1> affine(const mat<T, r, c>& m)
	{
		mat<T, r + 1, c + 1> res = m;
		res[c][r] = static_cast<T>(1);
		return res;
	}

	template <typename T, int d>
	inline mat<T, d, d> cofactor(const mat<T, d, d>& m)
	{
		mat<T, d, d> res;
		GMTK_UNROLL_LOOP(j, d,
			GMTK_UNROLL_LOOP(i, d,

				res[i][j] = pow(-1,(i+1)+(j+1)) * det(minor(m, j, i));
				
			);
		);
		return res;
	}

	template <typename T, int d>
	//! Returns an adjoint of matrix m
	inline mat<T, d, d> adjoint(const mat<T, d, d>& m)
	{
		return transpose(cofactor(m));
	}

	template<typename T, int d>
	//! Inverts the matrix, such that m * inverse(m) = the identity
	inline mat<T, d, d> inverse(const mat<T, d, d>& m)
	{
		return adjoint(m) / det(m);
	}

}////

//

#endif //_GMTK_MAT_H_