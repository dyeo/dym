#ifndef _DYM_MAT_H_
#define _DYM_MAT_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "util.h"
#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

//

#include <cmath>
#include <ostream>

//

namespace dym
{////

	//! A column-major matrix spanning R rows and C columns
	template <int C, int R = C, typename T = float>
	struct mat
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		constexpr int rows() const
		{
			return R;
		}
		constexpr int cols() const
		{
			return C;
		}
		constexpr int dim() const
		{
			return DYM_MIN_OF(R, C);
		}

		//! Unioned data members
		union
		{
			struct
			{
				vec<R, T> data[C];
			};
			struct
			{
				T arr[(C * R)];
			};
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		constexpr mat()
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = static_cast<T>(0);
			}
		}

		~mat() = default;

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		constexpr mat(std::initializer_list<T> list)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = *(list.begin() + i);
			}
		}

		//! Copy constructor
		constexpr mat(const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = v.arr[i];
			}
		}

		//! Minor matrix constructor
		template<int C1, int R1>
		constexpr mat(const mat<C1, R1, T> &m)
		{
			DYM_STATIC_ASSERT((R1 < R) && (C1 < C));
			for (std::size_t i = 0; i < C1; ++i)
			{
				for (std::size_t j = 0; j < R1; ++j)
				{
					data[i][j] = m.data[i][j];
				}
			}
		}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit constexpr mat(const mat<C, R, U> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = static_cast<T>(v.arr[i]);
			}
		}

		//! Fill constructor
		explicit constexpr mat(const T &s)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = s;
			}
		}

		//! Array initializer
		explicit constexpr mat(const T *a)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = a[i];
			}
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Matrix index operator - returns column
		vec<R, T> &operator[](const int i)
		{
			return data[i];
		}

		//! Matrix const index operator - returns column
		const vec<R, T> &operator[](const int i) const
		{
			return data[i];
		}

		//! Matrix linear array index operator - returns element 
		T &operator()(const int i)
		{
			return arr[i];
		}

		//! Matrix linear array const index operator - returns element
		const T &operator()(const int i) const
		{
			return arr[i];
		}

		///////////////////////////
		//! ARITHMETIC OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		mat<C, R, T> operator - () const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = -arr[i];
			}
			return res;
		}
		//! Component-wise unary negation
		mat<C, R, T> operator ~ () const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = ~arr[i];
			}
			return res;
		}
		//! Vector assignment
		mat<C, R, T> &operator = (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] = v.arr[i];
			}
			return *this;
		}

		//! Component-wise matrix addition
		mat<C, R, T> operator + (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] + v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix subtraction
		mat<C, R, T> operator - (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] - v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix OR
		mat<C, R, T> operator | (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] | v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix AND
		mat<C, R, T> operator & (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] & v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix XOR
		mat<C, R, T> operator ^ (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] ^ v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix modulus
		mat<C, R, T> operator % (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] % v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix shift left
		mat<C, R, T> operator << (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] << v.arr[i];
			}
			return res;
		}
		//! Component-wise matrix shift right
		mat<C, R, T> operator >> (const mat<C, R, T> &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] >> v.arr[i];
			}
			return res;
		}

		//! Component-wise scalar multiplication
		mat<C, R, T> operator * (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] * v;
			}
			return res;
		}
		//! Component-wise scalar division
		mat<C, R, T> operator / (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] / v;
			}
			return res;
		}
		//! Component-wise scalar addition
		mat<C, R, T> operator + (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] + v;
			}
			return res;
		}
		//! Component-wise scalar subtraction
		mat<C, R, T> operator - (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] - v;
			}
			return res;
		}
		//! Component-wise scalar OR
		mat<C, R, T> operator | (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] | v;
			}
			return res;
		}
		//! Component-wise scalar AND
		mat<C, R, T> operator & (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] & v;
			}
			return res;
		}
		//! Component-wise scalar XOR
		mat<C, R, T> operator ^ (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] ^ v;
			}
			return res;
		}
		//! Component-wise scalar modulus
		mat<C, R, T> operator % (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] % v;
			}
			return res;
		}
		//! Component-wise scalar shift left
		mat<C, R, T> operator << (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] << v;
			}
			return res;
		}
		//! Component-wise scalar shift right
		mat<C, R, T> operator >> (const T &v) const
		{
			mat<C, R, T> res; for (std::size_t i = 0; i < R * C; ++i)
			{
				res.arr[i] = arr[i] >> v;
			}
			return res;
		}

		//! Component-wise matrix reference addition
		mat<C, R, T> &operator += (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] += v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference subtraction
		mat<C, R, T> &operator -= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] -= v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference OR
		mat<C, R, T> &operator |= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] |= v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference AND
		mat<C, R, T> &operator &= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] &= v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference XOR
		mat<C, R, T> &operator ^= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] ^= v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference modulus
		mat<C, R, T> &operator %= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] %= v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference shift left
		mat<C, R, T> &operator <<= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] <<= v.arr[i];
			}
			return *this;
		}
		//! Component-wise matrix reference shift right
		mat<C, R, T> &operator >>= (const mat<C, R, T> &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] >>= v.arr[i];
			}
			return *this;
		}

		//! Component-wise scalar reference multiplication
		mat<C, R, T> &operator *= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] *= v;
			}
			return *this;
		}
		//! Component-wise scalar reference division
		mat<C, R, T> &operator /= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] /= v;
			}
			return *this;
		}
		//! Component-wise scalar reference addition
		mat<C, R, T> &operator += (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] += v;
			}
			return *this;
		}
		//! Component-wise scalar reference subtraction
		mat<C, R, T> &operator -= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] -= v;
			}
			return *this;
		}
		//! Component-wise scalar reference OR
		mat<C, R, T> &operator |= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] |= v;
			}
			return *this;
		}
		//! Component-wise scalar reference AND
		mat<C, R, T> &operator &= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] &= v;
			}
			return *this;
		}
		//! Component-wise scalar reference XOR
		mat<C, R, T> &operator ^= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] ^= v;
			}
			return *this;
		}
		//! Component-wise scalar reference modulus
		mat<C, R, T> &operator %= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] %= v;
			}
			return *this;
		}
		//! Component-wise scalar reference shift left
		mat<C, R, T> &operator <<= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] <<= v;
			}
			return *this;
		}
		//! Component-wise scalar reference shift right
		mat<C, R, T> &operator >>= (const T &v)
		{
			for (std::size_t i = 0; i < R * C; ++i)
			{
				arr[i] >>= v;
			}
			return *this;
		}

		//! Matrix identity
		static constexpr mat<C, R, T> identity()
		{
			mat<C, R, T> res(static_cast<T>(0));
			for (std::size_t i = 0; i < DYM_MIN_OF(R, C); ++i)
			{
				res.data[i][i] = static_cast<T>(1);
			}
			return res;
		}

		//! Zero matrix
		static constexpr mat<C, R, T> zero()
		{
			mat<C, R, T> res;
			for (std::size_t i = 0; i < C * R; ++i)
			{
				res[i] = static_cast<T>(0);
			}
			return res;
		}

		//! Unit matrix
		static constexpr mat<C, R, T> one()
		{
			mat<C, R, T> res;
			for (std::size_t i = 0; i < C * R; ++i)
			{
				res[i] = static_cast<T>(1);
			}
			return res;
		}

	}; //! struct mat

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <int C, int R, typename T>
	static std::ostream &operator<<(std::ostream &os, const mat<C, R, T> &v)
	{
		#ifdef DYM_OUTPUT_ROW_MAJOR
		const mat<C, R, T> &t = transpose(v);
		for (std::size_t i = 0; i < C; ++i)
		{
			os << "| ";
			for (std::size_t j = 0; j < R; ++j)
			{
				os << t[i][j] << ' ';
			}
			os << "|\n";
		};
		#else
		for (std::size_t i = 0; i < C; ++i)
		{
			os << v.data[i]; (i < C - 1) ? os << '\n' : os << ' ';
		}
		#endif
		return os;
	}

	///////////////////////////////////
	//! MATRIX&MATRIX MULTIPLICATION //
	///////////////////////////////////

	template <size_t N, typename T>
	static mat<N, N, T> strassen(const mat<N, N, T> &m, const mat<N, N, T> &n)
	{
	    if (N == 1)
		{
	        return mat<1, 1, T> C;
	        C(0, 0) = A(0, 0) * B(0, 0);
	        return C;
	    }
	
	    // Split A and B into submatrices
	    mat<N/2, N/2, T> A11, A12, A21, A22;
	    mat<N/2, N/2, T> B11, B12, B21, B22;
	    split(A, A11, A12, A21, A22);
	    split(B, B11, B12, B21, B22);
	
	    // Compute the 7 products using Strassen's algorithm
	    mat<N/2, N/2, T> P1 = strassen(A11 + A22, B11 + B22);
	    mat<N/2, N/2, T> P2 = strassen(A11 + A22, B11);
	    mat<N/2, N/2, T> P3 = strassen(A11, B12 - B22);
	    mat<N/2, N/2, T> P4 = strassen(A11, B21 - B11);
	    mat<N/2, N/2, T> P5 = strassen(A11 + A12, B22);
	    mat<N/2, N/2, T> P6 = strassen(A21 - A11, B11 + B12);
	    mat<N/2, N/2, T> P7 = strassen(A12 - A22, B21 + B22);
	
	    // Compute the submatrices of the result matrix
	    mat<N/2, N/2, T> C11 = P1 + P4 - P5 + P7;
	    mat<N/2, N/2, T> C12 = P3 + P5;
	    mat<N/2, N/2, T> C21 = P2 + P4;
	    mat<N/2, N/2, T> C22 = P1 - P2 + P3 + P6;
	
	    // Combine the submatrices into the result matrix
	    mat<N, N, T> C;
	    join(C11, C12, C21, C22, C);
	    return C;
	}

	template <size_t N, typename T>
	static void split(const mat<N, N, T>& M, mat<N/2, N/2, T>& M11, mat<N/2, N/2, T>& M12, mat<N/2, N/2, T>& M21, mat<N/2, N/2, T>& M22)
	{
	    for (size_t i = 0; i < N/2; ++i)
		{
	        for (size_t j = 0; j < N/2; ++j)
			{
	            M11(i, j) = M(i, j);
		        M12(i, j) = M(i, j + N/2);
		        M21(i, j) = M(i + N/2, j);
		        M22(i, j) = M(i + N/2, j + N/2);
		    }
		}
	}

	template <size_t N, typename T>
	static void join(const mat<N/2, N/2, T>& M11, const mat<N/2, N/2, T>& M12, const mat<N/2, N/2, T>& M21, const mat<N/2, N/2, T>& M22, mat<N, N, T>& M)
	{
		for (size_t i = 0; i < N/2; ++i)
		{
			for (size_t j = 0; j < N/2; ++j)
			{
				M(i, j) = M11(i, j);
				M(i, j + N/2) = M12(i, j);
				M(i + N/2, j) = M21(i, j);
				M(i + N/2, j + N/2) = M22(i, j);
			}
		}
	}

	//! Matrix product
	//! Accepts a R1 x C1 matrix and a R2 x C2 matrix where C1 and R2 are equal
	//! Returns a R1 x C2 matrix that is the product of the two original matrices
	//! Is not commutative
	template <int C1, int R1, int C2, int R2, typename T>
	static mat<C2, R1, T> operator*(const mat<C1, R1, T> &m, const mat<C2, R2, T> &n)
	{
		DYM_STATIC_ASSERT(C1 == R2); //! no.columns of m and no.rows of n must be equal!!!
		mat<C2, R1, T> res(static_cast<T>(0));
		for (std::size_t i = 0; i < R1; ++i)
		{
			for (std::size_t j = 0; j < C2; ++j)
			{
				for (std::size_t k = 0; k < R2; ++k)
				{
					res[j][i] += m.data[k][i] * n.data[j][k];
				}
			}
		}
		return res;
	}

	//! Matrix product (reference)
	//! Accepts two matrices where cols and rows are equal
	//! Is not commutative
	template <int C, int R, typename T>
	static mat<C, R, T> &operator*=(mat<C, R, T> &m, const mat<C, R, T> &n)
	{
		mat<C, R, T> res(static_cast<T>(0));
		for (std::size_t i = 0; i < R; ++i)
		{
			for (std::size_t j = 0; j < C; ++j)
			{
				for (std::size_t k = 0; k < R; ++k)
				{
					res[j][i] += m.data[k][i] * n.data[j][k];
				}
			}
		}
		return m = res;
	}

	///////////////////////////////////
	//! MATRIX&VECTOR MULTIPLICATION //
	///////////////////////////////////

	//! Matrix-vector multiplication: column vector (matrix row)
	template <int C, int R, typename T>
	static vec<R, T> operator*(const mat<C, R, T> &m, const vec<R, T> &v)
	{
		vec<R, T> res(static_cast<T>(0));
		for (std::size_t i = 0; i < R; ++i)
		{
			for (std::size_t j = 0; j < C; ++j)
			{
				res.data[i] += m.data[j][i] * v.data[j];
			}
		}
		return res;
	}

	//! Matrix-vector multiplication: row vector (matrix column)
	template <int C, int R, typename T>
	static vec<C, T> operator*(const vec<C, T> &v, const mat<C, R, T> &m)
	{
		vec<C, T> res(static_cast<T>(0));
		for (std::size_t i = 0; i < C; ++i)
		{
			for (std::size_t j = 0; j < R; ++j)
			{
				res.data[i] += m.data[i][j] * v.data[j];
			}
		}
		return res;
	}

	//! Matrix-vector multiplication: row vector (matrix column, reference)
	template <int C, int R, typename T>
	static vec<C, T> &operator*=(vec<C, T> &v, const mat<C, R, T> &m)
	{
		vec<C, T> res(static_cast<T>(0));
		for (std::size_t i = 0; i < C; ++i)
		{
			for (std::size_t j = 0; j < R; ++j)
			{
				res.data[i] += m.data[i][j] * v.data[j];
			}
		}
		return v = res;
	}

	///////////////////////////////////
	//! MATRIX&SCALAR MULTIPLICATION //
	///////////////////////////////////

	//! Matrix-scalar multiplication
	template <int C, int R, typename T>
	static mat<C, R, T> operator*(const T &v, const mat<C, R, T> &m)
	{
		mat<C, R, T> res;
		for (std::size_t i = 0; i < R * C; ++i)
		{
			res.arr[i] = v * m.arr[i];
		}
		return res;
	}

	//! Matrix-scalar multiplication (odd-typed)
	template <int C, int R, typename T, typename U>
	static mat<C, R, T> operator*(const U &v, const mat<C, R, T> &m)
	{
		mat<C, R, T> res;
		for (std::size_t i = 0; i < R * C; ++i)
		{
			res.arr[i] = static_cast<T>(v) * m.arr[i];
		}
		return res;
	}

	/////////////////////
	//! FREE-FUNCTIONS //
	/////////////////////

	//! Component-wise matrix multiplication
	template <int C, int R, typename T>
	static mat<C, R, T> mult(const mat<C, R, T> &m, const mat<C, R, T> &n)
	{
		mat<C, R, T> res;
		for (std::size_t i = 0; i < R * C; ++i)
		{
			res.arr[i] = m.arr[i] * n.arr[i];
		}
		return res;
	}

	//! Returns sum of the matrix diagonal
	template <int C, int R, typename T>
	static T trace(const mat<C, R, T> &m)
	{
		T res = 0;
		for (std::size_t i = 0; i < DYM_MIN_OF(R, C); ++i)
		{
			res += m.data[i][i];
		}
		return res;
	}

	//! Returns minor matrix of the current matrix, "crossing out" the specified row and column
	template <int C, int R, typename T>
	static mat<C - 1, R - 1, T> minor(const mat<C, R, T> &m, int rx, int cx)
	{
		mat<C - 1, R - 1, T> res(static_cast<T>(0));

		int mini = 0;
		int minj = 0;

		for (std::size_t i = 0; i < R; ++i)
		{
			if (i != rx)
			{
				minj = 0; for (std::size_t j = 0; j < C; ++j)
				{
					if (j != cx)
					{
						res.data[minj][mini] = m.data[j][i]; minj++;
					}
				} mini++;
			}
		}
		return res;
	}

	//! Calculates the determinant of a matrix
	template <int D, typename T>
	static T det(const mat<D, D, T> &m)
	{
		if (D == 1) return m[0];

		T res = 0;

		mat<D, D, T> l, u;

		ludecompose(m, l, u, D);

		T ls = 1, us = 1;

		for (std::size_t s = 0; s < D; ++s)
		{
			ls *= l[s * D + s];
			us *= u[s * D + s];
		}
		res = ls * us;

		return res;
	}

	//! Decomposes a matrix into lower and upper traingular cofactor matrices
	template <int D, typename T>
	static void ludecompose(const mat<D, D, T> &m, mat<D, D, T> &l, mat<D, D, T> &u)
	{
		int i, j, k;
		T sum = 0;

		for (i = 0; i < D; i++)
		{
			u[i * D + i] = 1;
		}
		for (j = 0; j < D; j++)
		{
			for (i = j; i < D; i++)
			{
				sum = 0;
				for (k = 0; k < j; k++)
				{
					sum = sum + l[i * D + k] * u[k * D + j];
				}
				l[i * D + j] = m[i * D + j] - sum;
			}
			for (i = j; i < D; i++)
			{
				sum = 0;
				for (k = 0; k < j; k++)
				{
					sum = sum + l[j * D + k] * u[k * D + i];
				}
				if (l[j * D + j] == 0)
				{
					return;
				}
				u[j * D + i] = (m[j * D + i] - sum) / l[j * D + j];
			}
		}
	}

	//! Flips the matrix along its diagonal (rows become columns, columns become rows)
	template <int R, int C, typename T>
	static mat<R, C, T> transpose(const mat<C, R, T> &m)
	{
		mat<R, C, T> res(static_cast<T>(0));
		for (std::size_t i = 0; i < C; ++i)
		{
			for (std::size_t j = 0; j < R; ++j)
			{
				res[j][i] = m[i][j];
			}
		}
		return res;
	}

	//! Generates a matrix one dimension larger that is a composition of the target matrix and an identity matrix
	template <int R, int C, typename T>
	static mat<C + 1, R + 1, T> affine(const mat<C, R, T> &m)
	{
		mat<C + 1, R + 1, T> res = m;
		res[C][R] = static_cast<T>(1);
		return res;
	}

	template <int D, typename T>
	static mat<D, D, T> cofactor(const mat<D, D, T> &m)
	{
		mat<D, D, T> res(static_cast<T>(0));
		for (std::size_t j = 0; j < D; ++j)
		{
			for (std::size_t i = 0; i < D; ++i)
			{
				res[i][j] = pow(-1, (i + 1) + (j + 1)) * det(minor(m, j, i));
			}
		}
		return res;
	}

	//! Returns true if the matrix has no inverse, false otherwise
	template <int D, typename T>
	static bool issingular(const mat<D, D, T> &m)
	{
		return det(m) == static_cast<T>(0);
	}

	//! Returns an adjoint of matrix m
	template <int D, typename T>
	static mat<D, D, T> adjoint(const mat<D, D, T> &m)
	{
		return transpose(cofactor(m));
	}

	//! Inverts the matrix, such that m * inverse(m) = the identity
	template<int D, typename T>
	static mat<D, D, T> inverse(const mat<D, D, T> &m)
	{
		return adjoint(m) / det(m);
	}

	//! Component-wise saturation (clamp01)
	template<int C, int R, typename T = float>
	static mat<C, R, T> saturate(const mat<C, R, T> &m)
	{
		return max(mat<C, R, T>::zero(), min(m, mat<C, R, T>::one()));
	}

}////

//

#pragma warning(pop)

//

#endif //_DYM_MAT_H_