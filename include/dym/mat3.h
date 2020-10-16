#ifndef _DYM_MAT3_H_
#define _DYM_MAT3_H_

//

#pragma warning(push)
#pragma warning(disable:4456;disable:4127)

//

#include "mat.h"

//

namespace dym
{////

	//! A column-major matrix spanning r rows and c columns
	template <typename T> struct mat <3, 3, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		constexpr int rows() const
		{
			return 3;
		}

		constexpr int cols() const
		{
			return 3;
		}

		constexpr int dim() const
		{
			return 3;
		}

		//! Unioned data members
		union
		{
			struct
			{
				vec<3, T> data[3];
			};
			struct
			{
				T arr[9];
			};
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		constexpr mat()
			: arr{ static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) }
		{}

		~mat() = default;

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		constexpr mat(std::initializer_list<T> l)
			: arr{ *(l.begin()), *(l.begin() + 1), *(l.begin() + 2), *(l.begin() + 3), *(l.begin() + 4), *(l.begin() + 5), *(l.begin() + 6), *(l.begin() + 7), *(l.begin() + 8) }
		{}

		//! Copy constructor
		constexpr mat(const mat<3, 3, T> &v)
			: arr{ v.arr[0], v.arr[1], v.arr[2], v.arr[3], v.arr[4], v.arr[5], v.arr[6], v.arr[7], v.arr[8] }
		{}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit constexpr mat(const mat<3, 3, U> &v)
			: arr{ static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]), static_cast<T>(v.arr[3]), static_cast<T>(v.arr[4]), static_cast<T>(v.arr[5]), static_cast<T>(v.arr[6]), static_cast<T>(v.arr[7]), static_cast<T>(v.arr[8]) }
		{}

		//! Fill constructor
		explicit constexpr mat(const T &s)
			: arr{ s, s, s, s, s, s, s, s, s }
		{}

		//! Array initializer
		explicit constexpr mat(const T *a)
			: arr{ a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8] }
		{}

		//! Value constructor
		constexpr mat(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8)
			: arr{ s0, s1, s2, s3, s4, s5, s6, s7, s8 }
		{}

		//! Explicit type-conversionm value constructor
		template<typename U>
		explicit constexpr mat(const U &s0, const U &s1, const U &s2, const U &s3, const U &s4, const U &s5, const U &s6, const U &s7, const U &s8)
			: arr{ static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(s3), static_cast<T>(s4), static_cast<T>(s5), static_cast<T>(s6), static_cast<T>(s7), static_cast<T>(s8) }
		{}

		//! Inserts a 2x2 matrix into the top-left portion of a 3x3 identity matrix
		//! ident adjusts the identity value
		constexpr mat(const mat<2, 2, T> &m, const T &ident = static_cast<T>(1))
			: arr{ m.arr[0], m.arr[1], 0, m.arr[2], m.arr[3], 0, 0, 0, ident }
		{}

		//! Constructs a 3x3 matrix using the top-left portion of a 4x4 matrix
		constexpr mat(const mat<4, 4, T> &m)
			: arr{ m.arr[0], m.arr[1], m.arr[2], m.arr[4], m.arr[5], m.arr[6], m.arr[8], m.arr[9], m.arr[10] }
		{}

		//! Minor matrix constructor
		template<int cm, int rm>
		constexpr mat(const mat<cm, rm, T> &m)
		{
			DYM_STATIC_ASSERT((rm < r) && (cm < c));
			for (std::size_t i = 0; i < cm; ++i)
			{
				for (std::size_t j = 0; j < rm; ++j)
				{
					data[i][j] = m.data[i][j];
				}
			}
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Column function - returns column as vector of T
		vec<3, T> col(const std::size_t i) const
		{
			return data[i];
		}

		//! Row function - returns row as vector of T
		vec<3, T> row(const std::size_t i) const
		{
			vec<3, T> v = vec<3, T>(arr[i], arr[i + 3], arr[i + 6]);
			return v;
		}

		//! Matrix index operator - returns column
		vec<3, T> &operator[](const std::size_t i)
		{
			return data[i];
		}

		//! Matrix const index operator - returns column
		const vec<3, T> &operator[](const std::size_t i) const
		{
			return data[i];
		}

		//! Matrix linear array index operator - returns element 
		T &operator()(const std::size_t i)
		{
			return arr[i];
		}

		//! Matrix linear array const index operator - returns element
		const T &operator()(const std::size_t i) const
		{
			return arr[i];
		}

		////////////////
		//! OPERATORS //
		////////////////

		//! Component-wise unary negation
		mat<3, 3, T> operator - () const
		{
			return mat<3, 3, T>(-arr[0], -arr[1], -arr[2], -arr[3], -arr[4], -arr[5], -arr[6], -arr[7], -arr[8]);
		}
		//! Component-wise unary negation
		mat<3, 3, T> operator ~ () const
		{
			return mat<3, 3, T>(~arr[0], ~arr[1], ~arr[2], ~arr[3], ~arr[4], ~arr[5], ~arr[6], ~arr[7], ~arr[8]);
		}
		//! Vector assignment
		mat<3, 3, T> &operator = (const mat<3, 3, T> &m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = m.arr[2];
			arr[3] = m.arr[3];
			arr[4] = m.arr[4];
			arr[5] = m.arr[5];
			arr[6] = m.arr[6];
			arr[7] = m.arr[7];
			arr[8] = m.arr[8];
			return *this;
		}

		//! Component-wise matrix addition
		mat<3, 3, T> operator + (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] + m.arr[0], arr[1] + m.arr[1], arr[2] + m.arr[2], arr[3] + m.arr[3], arr[4] + m.arr[4], arr[5] + m.arr[5], arr[6] + m.arr[6], arr[7] + m.arr[7], arr[8] + m.arr[8]);
		}
		//! Component-wise matrix subtraction
		mat<3, 3, T> operator - (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] - m.arr[0], arr[1] - m.arr[1], arr[2] - m.arr[2], arr[3] - m.arr[3], arr[4] - m.arr[4], arr[5] - m.arr[5], arr[6] - m.arr[6], arr[7] - m.arr[7], arr[8] - m.arr[8]);
		}
		//! Component-wise matrix OR
		mat<3, 3, T> operator | (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] | m.arr[0], arr[1] | m.arr[1], arr[2] | m.arr[2], arr[3] | m.arr[3], arr[4] | m.arr[4], arr[5] | m.arr[5], arr[6] | m.arr[6], arr[7] | m.arr[7], arr[8] | m.arr[8]);
		}
		//! Component-wise matrix AND
		mat<3, 3, T> operator & (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] & m.arr[0], arr[1] & m.arr[1], arr[2] & m.arr[2], arr[3] & m.arr[3], arr[4] & m.arr[4], arr[5] & m.arr[5], arr[6] & m.arr[6], arr[7] & m.arr[7], arr[8] & m.arr[8]);
		}
		//! Component-wise matrix XOR
		mat<3, 3, T> operator ^ (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] ^ m.arr[0], arr[1] ^ m.arr[1], arr[2] ^ m.arr[2], arr[3] ^ m.arr[3], arr[4] ^ m.arr[4], arr[5] ^ m.arr[5], arr[6] ^ m.arr[6], arr[7] ^ m.arr[7], arr[8] ^ m.arr[8]);
		}
		//! Component-wise matrix modulus
		mat<3, 3, T> operator % (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] % m.arr[0], arr[1] % m.arr[1], arr[2] % m.arr[2], arr[3] % m.arr[3], arr[4] % m.arr[4], arr[5] % m.arr[5], arr[6] % m.arr[6], arr[7] % m.arr[7], arr[8] % m.arr[8]);
		}
		//! Component-wise matrix shift left
		mat<3, 3, T> operator << (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] << m.arr[0], arr[1] << m.arr[1], arr[2] << m.arr[2], arr[3] << m.arr[3], arr[4] << m.arr[4], arr[5] << m.arr[5], arr[6] << m.arr[6], arr[7] << m.arr[7], arr[8] << m.arr[8]);
		}
		//! Component-wise matrix shift right
		mat<3, 3, T> operator >> (const mat<3, 3, T> &m) const
		{
			return mat<3, 3, T>(arr[0] >> m.arr[0], arr[1] >> m.arr[1], arr[2] >> m.arr[2], arr[3] >> m.arr[3], arr[4] >> m.arr[4], arr[5] >> m.arr[5], arr[6] >> m.arr[6], arr[7] >> m.arr[7], arr[8] >> m.arr[8]);
		}

		//! Component-wise scalar multiplication
		mat<3, 3, T> operator * (const T &v) const
		{
			return mat<3, 3, T>(arr[0] * v, arr[1] * v, arr[2] * v, arr[3] * v, arr[4] * v, arr[5] * v, arr[6] * v, arr[7] * v, arr[8] * v);
		}
		//! Component-wise scalar division
		mat<3, 3, T> operator / (const T &v) const
		{
			return mat<3, 3, T>(arr[0] / v, arr[1] / v, arr[2] / v, arr[3] / v, arr[4] / v, arr[5] / v, arr[6] / v, arr[7] / v, arr[8] / v);
		}
		//! Component-wise scalar addition
		mat<3, 3, T> operator + (const T &v) const
		{
			return mat<3, 3, T>(arr[0] + v, arr[1] + v, arr[2] + v, arr[3] + v, arr[4] + v, arr[5] + v, arr[6] + v, arr[7] + v, arr[8] + v);
		}
		//! Component-wise scalar subtraction
		mat<3, 3, T> operator - (const T &v) const
		{
			return mat<3, 3, T>(arr[0] - v, arr[1] - v, arr[2] - v, arr[3] - v, arr[4] - v, arr[5] - v, arr[6] - v, arr[7] - v, arr[8] - v);
		}
		//! Component-wise scalar OR
		mat<3, 3, T> operator | (const T &v) const
		{
			return mat<3, 3, T>(arr[0] | v, arr[1] | v, arr[2] | v, arr[3] | v, arr[4] | v, arr[5] | v, arr[6] | v, arr[7] | v, arr[8] | v);
		}
		//! Component-wise scalar AND
		mat<3, 3, T> operator & (const T &v) const
		{
			return mat<3, 3, T>(arr[0] & v, arr[1] & v, arr[2] & v, arr[3] & v, arr[4] & v, arr[5] & v, arr[6] & v, arr[7] & v, arr[8] & v);
		}
		//! Component-wise scalar XOR
		mat<3, 3, T> operator ^ (const T &v) const
		{
			return mat<3, 3, T>(arr[0] ^ v, arr[1] ^ v, arr[2] ^ v, arr[3] ^ v, arr[4] ^ v, arr[5] ^ v, arr[6] ^ v, arr[7] ^ v, arr[8] ^ v);
		}
		//! Component-wise scalar modulus
		mat<3, 3, T> operator % (const T &v) const
		{
			return mat<3, 3, T>(arr[0] % v, arr[1] % v, arr[2] % v, arr[3] % v, arr[4] % v, arr[5] % v, arr[6] % v, arr[7] % v, arr[8] % v);
		}
		//! Component-wise scalar shift left
		mat<3, 3, T> operator << (const T &v) const
		{
			return mat<3, 3, T>(arr[0] << v, arr[1] << v, arr[2] << v, arr[3] << v, arr[4] << v, arr[5] << v, arr[6] << v, arr[7] << v, arr[8] << v);
		}
		//! Component-wise scalar shift right
		mat<3, 3, T> operator >> (const T &v) const
		{
			return mat<3, 3, T>(arr[0] >> v, arr[1] >> v, arr[2] >> v, arr[3] >> v, arr[4] >> v, arr[5] >> v, arr[6] >> v, arr[7] >> v, arr[8] >> v);
		}

		//! Component-wise matrix reference addition
		mat<3, 3, T> &operator += (const mat<3, 3, T> &m)
		{
			arr[0] += m.arr[0];
			arr[1] += m.arr[1];
			arr[2] += m.arr[2];
			arr[3] += m.arr[3];
			arr[4] += m.arr[4];
			arr[5] += m.arr[5];
			arr[6] += m.arr[6];
			arr[7] += m.arr[7];
			arr[8] += m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference subtraction
		mat<3, 3, T> &operator -= (const mat<3, 3, T> &m)
		{
			arr[0] -= m.arr[0];
			arr[1] -= m.arr[1];
			arr[2] -= m.arr[2];
			arr[3] -= m.arr[3];
			arr[4] -= m.arr[4];
			arr[5] -= m.arr[5];
			arr[6] -= m.arr[6];
			arr[7] -= m.arr[7];
			arr[8] -= m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference OR
		mat<3, 3, T> &operator |= (const mat<3, 3, T> &m)
		{
			arr[0] |= m.arr[0];
			arr[1] |= m.arr[1];
			arr[2] |= m.arr[2];
			arr[3] |= m.arr[3];
			arr[4] |= m.arr[4];
			arr[5] |= m.arr[5];
			arr[6] |= m.arr[6];
			arr[7] |= m.arr[7];
			arr[8] |= m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference AND
		mat<3, 3, T> &operator &= (const mat<3, 3, T> &m)
		{
			arr[0] &= m.arr[0];
			arr[1] &= m.arr[1];
			arr[2] &= m.arr[2];
			arr[3] &= m.arr[3];
			arr[4] &= m.arr[4];
			arr[5] &= m.arr[5];
			arr[6] &= m.arr[6];
			arr[7] &= m.arr[7];
			arr[8] &= m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference XOR
		mat<3, 3, T> &operator ^= (const mat<3, 3, T> &m)
		{
			arr[0] ^= m.arr[0];
			arr[1] ^= m.arr[1];
			arr[2] ^= m.arr[2];
			arr[3] ^= m.arr[3];
			arr[4] ^= m.arr[4];
			arr[5] ^= m.arr[5];
			arr[6] ^= m.arr[6];
			arr[7] ^= m.arr[7];
			arr[8] ^= m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference modulus
		mat<3, 3, T> &operator %= (const mat<3, 3, T> &m)
		{
			arr[0] %= m.arr[0];
			arr[1] %= m.arr[1];
			arr[2] %= m.arr[2];
			arr[3] %= m.arr[3];
			arr[4] %= m.arr[4];
			arr[5] %= m.arr[5];
			arr[6] %= m.arr[6];
			arr[7] %= m.arr[7];
			arr[8] %= m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference shift left
		mat<3, 3, T> &operator <<= (const mat<3, 3, T> &m)
		{
			arr[0] <<= m.arr[0];
			arr[1] <<= m.arr[1];
			arr[2] <<= m.arr[2];
			arr[3] <<= m.arr[3];
			arr[4] <<= m.arr[4];
			arr[5] <<= m.arr[5];
			arr[6] <<= m.arr[6];
			arr[7] <<= m.arr[7];
			arr[8] <<= m.arr[8];
			return *this;
		}
		//! Component-wise matrix reference shift right
		mat<3, 3, T> &operator >>= (const mat<3, 3, T> &m)
		{
			arr[0] >>= m.arr[0];
			arr[1] >>= m.arr[1];
			arr[2] >>= m.arr[2];
			arr[3] >>= m.arr[3];
			arr[4] >>= m.arr[4];
			arr[5] >>= m.arr[5];
			arr[6] >>= m.arr[6];
			arr[7] >>= m.arr[7];
			arr[8] >>= m.arr[8];
			return *this;
		}

		//! Component-wise scalar reference multiplication
		mat<3, 3, T> &operator *= (const T &v)
		{
			arr[0] *= v;
			arr[1] *= v;
			arr[2] *= v;
			arr[3] *= v;
			arr[4] *= v;
			arr[5] *= v;
			arr[6] *= v;
			arr[7] *= v;
			arr[8] *= v;
			return *this;
		}
		//! Component-wise scalar reference division
		mat<3, 3, T> &operator /= (const T &v)
		{
			arr[0] /= v;
			arr[1] /= v;
			arr[2] /= v;
			arr[3] /= v;
			arr[4] /= v;
			arr[5] /= v;
			arr[6] /= v;
			arr[7] /= v;
			arr[8] /= v;
			return *this;
		}
		//! Component-wise scalar reference addition
		mat<3, 3, T> &operator += (const T &v)
		{
			arr[0] += v;
			arr[1] += v;
			arr[2] += v;
			arr[3] += v;
			arr[4] += v;
			arr[5] += v;
			arr[6] += v;
			arr[7] += v;
			arr[8] += v;
			return *this;
		}
		//! Component-wise scalar reference subtraction
		mat<3, 3, T> &operator -= (const T &v)
		{
			arr[0] -= v;
			arr[1] -= v;
			arr[2] -= v;
			arr[3] -= v;
			arr[4] -= v;
			arr[5] -= v;
			arr[6] -= v;
			arr[7] -= v;
			arr[8] -= v;
			return *this;
		}
		//! Component-wise scalar reference OR
		mat<3, 3, T> &operator |= (const T &v)
		{
			arr[0] |= v;
			arr[1] |= v;
			arr[2] |= v;
			arr[3] |= v;
			arr[4] |= v;
			arr[5] |= v;
			arr[6] |= v;
			arr[7] |= v;
			arr[8] |= v;
			return *this;
		}
		//! Component-wise scalar reference AND
		mat<3, 3, T> &operator &= (const T &v)
		{
			arr[0] &= v;
			arr[1] &= v;
			arr[2] &= v;
			arr[3] &= v;
			arr[4] &= v;
			arr[5] &= v;
			arr[6] &= v;
			arr[7] &= v;
			arr[8] &= v;
			return *this;
		}
		//! Component-wise scalar reference XOR
		mat<3, 3, T> &operator ^= (const T &v)
		{
			arr[0] ^= v;
			arr[1] ^= v;
			arr[2] ^= v;
			arr[3] ^= v;
			arr[4] ^= v;
			arr[5] ^= v;
			arr[6] ^= v;
			arr[7] ^= v;
			arr[8] ^= v;
			return *this;
		}
		//! Component-wise scalar reference modulus
		mat<3, 3, T> &operator %= (const T &v)
		{
			arr[0] %= v;
			arr[1] %= v;
			arr[2] %= v;
			arr[3] %= v;
			arr[4] %= v;
			arr[5] %= v;
			arr[6] %= v;
			arr[7] %= v;
			arr[8] %= v;
			return *this;
		}
		//! Component-wise scalar reference shift left
		mat<3, 3, T> &operator <<= (const T &v)
		{
			arr[0] <<= v;
			arr[1] <<= v;
			arr[2] <<= v;
			arr[3] <<= v;
			arr[4] <<= v;
			arr[5] <<= v;
			arr[6] <<= v;
			arr[7] <<= v;
			arr[8] <<= v;
			return *this;
		}
		//! Component-wise scalar reference shift right
		mat<3, 3, T> &operator >>= (const T &v)
		{
			arr[0] >>= v;
			arr[1] >>= v;
			arr[2] >>= v;
			arr[3] >>= v;
			arr[4] >>= v;
			arr[5] >>= v;
			arr[6] >>= v;
			arr[7] >>= v;
			arr[8] >>= v;
			return *this;
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Returns an identity matrix
		static constexpr mat<3, 3, T> identity()
		{
			return mat<3, 3, T>(1, 0, 0, 0, 1, 0, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		static mat<3, 3, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8)
		{
			return mat<3, 3, T>
				(s0, s3, s6,
					s1, s4, s7,
					s2, s5, s8);
		}

		//! Creates a 3x3 matrix using 3 row vectors
		static mat<3, 3, T> fromrows(vec<3, T> r0, vec<3, T> r1, vec<3, T> r2)
		{
			return mat<3, 3, T>
				(r0.x, r1.x, r2.x,
					r0.y, r1.y, r2.y,
					r0.z, r1.z, r2.z);
		}

		//! Creates a 3x3 matrix using 3 column vectors
		static mat<3, 3, T> fromcols(vec<3, T> c0, vec<3, T> c1, vec<3, T> c2)
		{
			return mat<3, 3, T>
				(c0.x, c0.y, c0.z,
					c1.x, c1.y, c1.z,
					c2.x, c2.y, c2.z);
		}

		//! Rotate an axis about a given angle
		static mat<3, 3, T> rotate(const ang<T> &an, const vec<3, T> &ax)
		{
			T c = cos(an.radians());
			T s = sin(an.radians());
			T t = 1 - c;
			return mat<3, 3, T>
				((t * ax.x * ax.x) + c, (t * ax.x * ax.y) + ax.z * s, (t * ax.x * ax.z) - ax.y * s,
					(t * ax.x * ax.y) - ax.z * s, (t * ax.y * ax.y) + c, (t * ax.y * ax.z) + ax.x * s,
					(t * ax.x * ax.z) + ax.y * s, (t * ax.y * ax.z) - ax.x * s, (t * ax.z * ax.z) + c);
		}

		//! Rotate axis x about a given angle
		static mat<3, 3, T> rotatex(const ang<T> &x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<3, 3, T>
				(1, 0, 0,
					0, c, s,
					0, -s, c);
		}

		//! Rotate axis y about a given angle
		static mat<3, 3, T> rotatey(const ang<T> &x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<3, 3, T>
				(c, 0, -s,
					0, 1, 0,
					s, 0, c);
		}

		//! Rotate axis z about a given angle
		static mat<3, 3, T> rotatez(const ang<T> &x)
		{
			T c = cos(x.radians());
			T s = sin(x.radians());
			return mat<3, 3, T>
				(c, s, 0,
					-s, c, 0,
					0, 0, 1);
		}

		static mat<3, 3, T> scale(const T &s)
		{
			return mat<3, 3, T>(s, 0, 0, 0, s, 0, 0, 0, s);
		}

		static mat<3, 3, T> scale(const T &x, const T &y, const T &z)
		{
			return mat<3, 3, T>(x, 0, 0, 0, y, 0, 0, 0, z);
		}

		static mat<3, 3, T> scale(const vec<3, T> &v)
		{
			return mat<3, 3, T>(v.x, 0, 0, 0, v.y, 0, 0, 0, v.z);
		}

		static mat<3, 3, T> translate(const T &x, const T &y)
		{
			return mat<3, 3, T>(1, 0, 0, 0, 1, 0, x, y, 1);
		}

		static mat<3, 3, T> translate(const vec<3, T> &v)
		{
			return translate(v.x, v.y, v.z);
		}

		static mat<4, 4, T> translate_affine(const T &x, const T &y, const T &z)
		{
			mat<4, 4, T> res = mat<4, 4, T>::identity();
			res[3] = vec<4, T>(x, y, z, 1);
			return res;
		}

		static mat<4, 4, T> translate_affine(const vec<3, T> &v)
		{
			return translate(v.x, v.y, v.z);
		}

	}; //! struct mat

	template <typename T>
	static mat<3, 3, T> operator*(const mat<3, 3, T> &m, const mat<3, 3, T> &n)
	{
		return mat<3, 3, T>
			(m.arr[0] * n.arr[0] + m.arr[3] * n.arr[1] + m.arr[6] * n.arr[2],
				m.arr[1] * n.arr[0] + m.arr[4] * n.arr[1] + m.arr[7] * n.arr[2],
				m.arr[2] * n.arr[0] + m.arr[5] * n.arr[1] + m.arr[8] * n.arr[2],
				m.arr[0] * n.arr[3] + m.arr[3] * n.arr[4] + m.arr[6] * n.arr[5],
				m.arr[1] * n.arr[3] + m.arr[4] * n.arr[4] + m.arr[7] * n.arr[5],
				m.arr[2] * n.arr[3] + m.arr[5] * n.arr[4] + m.arr[8] * n.arr[5],
				m.arr[0] * n.arr[6] + m.arr[3] * n.arr[7] + m.arr[6] * n.arr[8],
				m.arr[1] * n.arr[6] + m.arr[4] * n.arr[7] + m.arr[7] * n.arr[8],
				m.arr[2] * n.arr[6] + m.arr[5] * n.arr[7] + m.arr[8] * n.arr[8]);
	}
	
	//! Matrix determinant
	template<typename T>
	static T det(const mat<3, 3, T> &m)
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
	static mat<3, 3, T> inverse(const mat<3, 3, T> &m)
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

#pragma warning(pop)

//

#endif//_DYM_MAT3_H_