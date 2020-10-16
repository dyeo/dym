#ifndef _DYM_MAT4_H_
#define _DYM_MAT4_H_

//

#pragma warning(push)
#pragma warning(disable:4456;disable:4127)

//

#include "mat.h"

//

namespace dym
{////

	//! A column-major matrix spanning r rows and c columns
	template <typename T> struct mat <4, 4, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		constexpr int rows() const
		{
			return 4;
		}

		constexpr int cols() const
		{
			return 4;
		}

		constexpr int dim() const
		{
			return 4;
		}

		//! Unioned data members
		union
		{
			struct
			{
				vec<4, T> data[4];
			};
			struct
			{
				T arr[16];
			};
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		mat()
			: arr{ static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) }
		{}

		~mat() = default;

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		mat(std::initializer_list<T> l)
			: arr{ *(l.begin()), *(l.begin() + 1), *(l.begin() + 2), *(l.begin() + 3), *(l.begin() + 4), *(l.begin() + 5), *(l.begin() + 6), *(l.begin() + 7), *(l.begin() + 8), *(l.begin() + 9), *(l.begin() + 10), *(l.begin() + 11), *(l.begin() + 12), *(l.begin() + 13), *(l.begin() + 14), *(l.begin() + 15) }
		{}

		//! Copy constructor
		mat(const mat<4, 4, T> &v)
			: arr{ v.arr[0], v.arr[1], v.arr[2], v.arr[3], v.arr[4], v.arr[5], v.arr[6], v.arr[7], v.arr[8], v.arr[9], v.arr[10], v.arr[11], v.arr[12], v.arr[13], v.arr[14], v.arr[15] }
		{}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit mat(const mat<4, 4, U> &v)
			: arr{ static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]), static_cast<T>(v.arr[3]), static_cast<T>(v.arr[4]), static_cast<T>(v.arr[5]), static_cast<T>(v.arr[6]), static_cast<T>(v.arr[7]), static_cast<T>(v.arr[8]), static_cast<T>(v.arr[9]), static_cast<T>(v.arr[10]), static_cast<T>(v.arr[11]), static_cast<T>(v.arr[12]), static_cast<T>(v.arr[13]), static_cast<T>(v.arr[14]), static_cast<T>(v.arr[15]) }
		{}

		//! Fill constructor
		explicit mat(const T &s)
			: arr{ s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s }
		{}

		//! Array initializer
		explicit mat(const T *a)
			: arr{ a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15] }
		{}

		//! Value constructor
		mat(const T &s0, const T &s1, const T &s2, const T &s3,
			const T &s4, const T &s5, const T &s6, const T &s7,
			const T &s8, const T &s9, const T &s10, const T &s11,
			const T &s12, const T &s13, const T &s14, const T &s15)
			: arr{ s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11, s12, s13, s14, s15 }
		{}

		//! Explicit type-conversionm value constructor
		template<typename U>
		explicit mat(const U &s0, const U &s1, const U &s2, const U &s3,
			const U &s4, const U &s5, const U &s6, const U &s7,
			const U &s8, const U &s9, const U &s10, const U &s11,
			const U &s12, const U &s13, const U &s14, const U &s15)
			: arr{ static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(s3), static_cast<T>(s4), static_cast<T>(s5), static_cast<T>(s6), static_cast<T>(s7), static_cast<T>(s8), static_cast<T>(s9), static_cast<T>(s10), static_cast<T>(s11), static_cast<T>(s12), static_cast<T>(s13), static_cast<T>(s14), static_cast<T>(s15) }
		{}

		//! Inserts a 2x2 matrix into the top-left portion of a 4x4 identity matrix
		//! ident adjusts the identity value
		mat(const mat<2, 2, T> &m, const T &ident = static_cast<T>(1))
			: arr{ m.arr[0], m.arr[1], 0, 0, m.arr[2], m.arr[3], 0, 0, 0, 0, ident, 0, 0, 0, 0, ident }
		{}

		//! Inserts a 3x3 matrix into the top-left portion of a 4x4 identity matrix
		//! ident adjusts the identity value
		mat(const mat<3, 3, T> &m, const T &ident = static_cast<T>(1))
			: arr{ m.arr[0], m.arr[1], m.arr[2], 0, m.arr[3], m.arr[4], m.arr[5], 0, m.arr[6], m.arr[7], m.arr[8], 0, 0, 0, 0, ident }
		{}

		//! Creates a homogeneous transformation matrix out of a rotation matrix and a displacement vector
		mat(const mat<3, 3, T> &r, const vec<3, T> &d)
			: arr{ r.arr[0], r.arr[1], r.arr[2], 0, r.arr[3], r.arr[4], r.arr[5], 0, r.arr[6], r.arr[7], r.arr[8], 0, d.data[0], d.data[1], d.data[2], static_cast<T>(1) }
		{}

		//! Minor matrix constructor
		template<int cm, int rm>
		mat(const mat<cm, rm, T> &m)
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
		vec<4, T> col(const int i) const
		{
			return data[i];
		}

		//! Row function - returns row as vector of T
		vec<4, T> row(const int i) const
		{
			vec<4, T> v = vec4(arr[i], arr[i + 4], arr[i + 8], arr[i + 12]);
			return v;
		}

		//! Matrix index operator - returns column as vector of T
		vec<4, T> &operator[](const int i)
		{
			return data[i];
		}

		//! Matrix const index operator - returns column as vector of T
		const vec<4, T> &operator[](const int i) const
		{
			return data[i];
		}

		//! Matrix linear array index operator - returns element as T
		T &operator()(const int i)
		{
			return arr[i];
		}

		//! Matrix linear array const index operator - returns element as T
		const T &operator()(const int i) const
		{
			return arr[i];
		}

		///////////////////////
		//! ACCESS FUNCTIONS //
		///////////////////////

		//! right
		vec<3, T> right() const
		{
			return data[0];
		}

		//! up
		vec<3, T> up() const
		{
			return data[1];
		}

		//! forward
		vec<3, T> forward() const
		{
			return data[2];
		}

		//! translation
		vec<3, T> translation() const
		{
			return data[3];
		}

		////////////////
		//! OPERATORS //
		////////////////

		//! Component-wise unary negation
		mat<4, 4, T> operator - () const
		{
			return mat<4, 4, T>(-arr[0], -arr[1], -arr[2], -arr[3], -arr[4], -arr[5], -arr[6], -arr[7], -arr[8], -arr[9], -arr[10], -arr[11], -arr[12], -arr[13], -arr[14], -arr[15]);
		}
		//! Component-wise unary negation
		mat<4, 4, T> operator ~ () const
		{
			return mat<4, 4, T>(~arr[0], ~arr[1], ~arr[2], ~arr[3], ~arr[4], ~arr[5], ~arr[6], ~arr[7], ~arr[8], ~arr[9], ~arr[10], ~arr[11], ~arr[12], ~arr[13], ~arr[14], ~arr[15]);
		}
		//! Vector assignment
		mat<4, 4, T> &operator = (const mat<4, 4, T> &m)
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
			arr[9] = m.arr[9];
			arr[10] = m.arr[10];
			arr[11] = m.arr[11];
			arr[12] = m.arr[12];
			arr[13] = m.arr[13];
			arr[14] = m.arr[14];
			arr[15] = m.arr[15];
			return *this;
		}

		//! Component-wise matrix addition
		mat<4, 4, T> operator + (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] + m.arr[0], arr[1] + m.arr[1], arr[2] + m.arr[2], arr[3] + m.arr[3], arr[4] + m.arr[4], arr[5] + m.arr[5], arr[6] + m.arr[6], arr[7] + m.arr[7], arr[8] + m.arr[8], arr[9] + m.arr[9], arr[10] + m.arr[10], arr[11] + m.arr[11], arr[12] + m.arr[12], arr[13] + m.arr[13], arr[14] + m.arr[14], arr[15] + m.arr[15]);
		}
		//! Component-wise matrix subtraction
		mat<4, 4, T> operator - (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] - m.arr[0], arr[1] - m.arr[1], arr[2] - m.arr[2], arr[3] - m.arr[3], arr[4] - m.arr[4], arr[5] - m.arr[5], arr[6] - m.arr[6], arr[7] - m.arr[7], arr[8] - m.arr[8], arr[9] - m.arr[9], arr[10] - m.arr[10], arr[11] - m.arr[11], arr[12] - m.arr[12], arr[13] - m.arr[13], arr[14] - m.arr[14], arr[15] - m.arr[15]);
		}
		//! Component-wise matrix OR
		mat<4, 4, T> operator | (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] | m.arr[0], arr[1] | m.arr[1], arr[2] | m.arr[2], arr[3] | m.arr[3], arr[4] | m.arr[4], arr[5] | m.arr[5], arr[6] | m.arr[6], arr[7] | m.arr[7], arr[8] | m.arr[8], arr[9] | m.arr[9], arr[10] | m.arr[10], arr[11] | m.arr[11], arr[12] | m.arr[12], arr[13] | m.arr[13], arr[14] | m.arr[14], arr[15] | m.arr[15]);
		}
		//! Component-wise matrix AND
		mat<4, 4, T> operator & (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] & m.arr[0], arr[1] & m.arr[1], arr[2] & m.arr[2], arr[3] & m.arr[3], arr[4] & m.arr[4], arr[5] & m.arr[5], arr[6] & m.arr[6], arr[7] & m.arr[7], arr[8] & m.arr[8], arr[9] & m.arr[9], arr[10] & m.arr[10], arr[11] & m.arr[11], arr[12] & m.arr[12], arr[13] & m.arr[13], arr[14] & m.arr[14], arr[15] & m.arr[15]);
		}
		//! Component-wise matrix XOR
		mat<4, 4, T> operator ^ (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] ^ m.arr[0], arr[1] ^ m.arr[1], arr[2] ^ m.arr[2], arr[3] ^ m.arr[3], arr[4] ^ m.arr[4], arr[5] ^ m.arr[5], arr[6] ^ m.arr[6], arr[7] ^ m.arr[7], arr[8] ^ m.arr[8], arr[9] ^ m.arr[9], arr[10] ^ m.arr[10], arr[11] ^ m.arr[11], arr[12] ^ m.arr[12], arr[13] ^ m.arr[13], arr[14] ^ m.arr[14], arr[15] ^ m.arr[15]);
		}
		//! Component-wise matrix modulus
		mat<4, 4, T> operator % (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] % m.arr[0], arr[1] % m.arr[1], arr[2] % m.arr[2], arr[3] % m.arr[3], arr[4] % m.arr[4], arr[5] % m.arr[5], arr[6] % m.arr[6], arr[7] % m.arr[7], arr[8] % m.arr[8], arr[9] % m.arr[9], arr[10] % m.arr[10], arr[11] % m.arr[11], arr[12] % m.arr[12], arr[13] % m.arr[13], arr[14] % m.arr[14], arr[15] % m.arr[15]);
		}
		//! Component-wise matrix shift left
		mat<4, 4, T> operator << (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] << m.arr[0], arr[1] << m.arr[1], arr[2] << m.arr[2], arr[3] << m.arr[3], arr[4] << m.arr[4], arr[5] << m.arr[5], arr[6] << m.arr[6], arr[7] << m.arr[7], arr[8] << m.arr[8], arr[9] << m.arr[9], arr[10] << m.arr[10], arr[11] << m.arr[11], arr[12] << m.arr[12], arr[13] << m.arr[13], arr[14] << m.arr[14], arr[15] << m.arr[15]);
		}
		//! Component-wise matrix shift right
		mat<4, 4, T> operator >> (const mat<4, 4, T> &m) const
		{
			return mat<4, 4, T>(arr[0] >> m.arr[0], arr[1] >> m.arr[1], arr[2] >> m.arr[2], arr[3] >> m.arr[3], arr[4] >> m.arr[4], arr[5] >> m.arr[5], arr[6] >> m.arr[6], arr[7] >> m.arr[7], arr[8] >> m.arr[8], arr[9] >> m.arr[9], arr[10] >> m.arr[10], arr[11] >> m.arr[11], arr[12] >> m.arr[12], arr[13] >> m.arr[13], arr[14] >> m.arr[14], arr[15] >> m.arr[15]);
		}

		//! Component-wise scalar multiplication
		mat<4, 4, T> operator * (const T &v) const
		{
			return mat<4, 4, T>(arr[0] * v, arr[1] * v, arr[2] * v, arr[3] * v, arr[4] * v, arr[5] * v, arr[6] * v, arr[7] * v, arr[8] * v, arr[9] * v, arr[10] * v, arr[11] * v, arr[12] * v, arr[13] * v, arr[14] * v, arr[15] * v);
		}
		//! Component-wise scalar division
		mat<4, 4, T> operator / (const T &v) const
		{
			return mat<4, 4, T>(arr[0] / v, arr[1] / v, arr[2] / v, arr[3] / v, arr[4] / v, arr[5] / v, arr[6] / v, arr[7] / v, arr[8] / v, arr[9] / v, arr[10] / v, arr[11] / v, arr[12] / v, arr[13] / v, arr[14] / v, arr[15] / v);
		}
		//! Component-wise scalar addition
		mat<4, 4, T> operator + (const T &v) const
		{
			return mat<4, 4, T>(arr[0] + v, arr[1] + v, arr[2] + v, arr[3] + v, arr[4] + v, arr[5] + v, arr[6] + v, arr[7] + v, arr[8] + v, arr[9] + v, arr[10] + v, arr[11] + v, arr[12] + v, arr[13] + v, arr[14] + v, arr[15] + v);
		}
		//! Component-wise scalar subtraction
		mat<4, 4, T> operator - (const T &v) const
		{
			return mat<4, 4, T>(arr[0] - v, arr[1] - v, arr[2] - v, arr[3] - v, arr[4] - v, arr[5] - v, arr[6] - v, arr[7] - v, arr[8] - v, arr[9] - v, arr[10] - v, arr[11] - v, arr[12] - v, arr[13] - v, arr[14] - v, arr[15] - v);
		}
		//! Component-wise scalar OR
		mat<4, 4, T> operator | (const T &v) const
		{
			return mat<4, 4, T>(arr[0] | v, arr[1] | v, arr[2] | v, arr[3] | v, arr[4] | v, arr[5] | v, arr[6] | v, arr[7] | v, arr[8] | v, arr[9] | v, arr[10] | v, arr[11] | v, arr[12] | v, arr[13] | v, arr[14] | v, arr[15] | v);
		}
		//! Component-wise scalar AND
		mat<4, 4, T> operator & (const T &v) const
		{
			return mat<4, 4, T>(arr[0] & v, arr[1] & v, arr[2] & v, arr[3] & v, arr[4] & v, arr[5] & v, arr[6] & v, arr[7] & v, arr[8] & v, arr[9] & v, arr[10] & v, arr[11] & v, arr[12] & v, arr[13] & v, arr[14] & v, arr[15] & v);
		}
		//! Component-wise scalar XOR
		mat<4, 4, T> operator ^ (const T &v) const
		{
			return mat<4, 4, T>(arr[0] ^ v, arr[1] ^ v, arr[2] ^ v, arr[3] ^ v, arr[4] ^ v, arr[5] ^ v, arr[6] ^ v, arr[7] ^ v, arr[8] ^ v, arr[9] ^ v, arr[10] ^ v, arr[11] ^ v, arr[12] ^ v, arr[13] ^ v, arr[14] ^ v, arr[15] ^ v);
		}
		//! Component-wise scalar modulus
		mat<4, 4, T> operator % (const T &v) const
		{
			return mat<4, 4, T>(arr[0] % v, arr[1] % v, arr[2] % v, arr[3] % v, arr[4] % v, arr[5] % v, arr[6] % v, arr[7] % v, arr[8] % v, arr[9] % v, arr[10] % v, arr[11] % v, arr[12] % v, arr[13] % v, arr[14] % v, arr[15] % v);
		}
		//! Component-wise scalar shift left
		mat<4, 4, T> operator << (const T &v) const
		{
			return mat<4, 4, T>(arr[0] << v, arr[1] << v, arr[2] << v, arr[3] << v, arr[4] << v, arr[5] << v, arr[6] << v, arr[7] << v, arr[8] << v, arr[9] << v, arr[10] << v, arr[11] << v, arr[12] << v, arr[13] << v, arr[14] << v, arr[15] << v);
		}
		//! Component-wise scalar shift right
		mat<4, 4, T> operator >> (const T &v) const
		{
			return mat<4, 4, T>(arr[0] >> v, arr[1] >> v, arr[2] >> v, arr[3] >> v, arr[4] >> v, arr[5] >> v, arr[6] >> v, arr[7] >> v, arr[8] >> v, arr[9] >> v, arr[10] >> v, arr[11] >> v, arr[12] >> v, arr[13] >> v, arr[14] >> v, arr[15] >> v);
		}

		//! Component-wise matrix reference addition
		mat<4, 4, T> &operator += (const mat<4, 4, T> &m)
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
			arr[9] += m.arr[9];
			arr[10] += m.arr[10];
			arr[11] += m.arr[11];
			arr[12] += m.arr[12];
			arr[13] += m.arr[13];
			arr[14] += m.arr[14];
			arr[15] += m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference subtraction
		mat<4, 4, T> &operator -= (const mat<4, 4, T> &m)
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
			arr[9] -= m.arr[9];
			arr[10] -= m.arr[10];
			arr[11] -= m.arr[11];
			arr[12] -= m.arr[12];
			arr[13] -= m.arr[13];
			arr[14] -= m.arr[14];
			arr[15] -= m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference OR
		mat<4, 4, T> &operator |= (const mat<4, 4, T> &m)
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
			arr[9] |= m.arr[9];
			arr[10] |= m.arr[10];
			arr[11] |= m.arr[11];
			arr[12] |= m.arr[12];
			arr[13] |= m.arr[13];
			arr[14] |= m.arr[14];
			arr[15] |= m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference AND
		mat<4, 4, T> &operator &= (const mat<4, 4, T> &m)
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
			arr[9] &= m.arr[9];
			arr[10] &= m.arr[10];
			arr[11] &= m.arr[11];
			arr[12] &= m.arr[12];
			arr[13] &= m.arr[13];
			arr[14] &= m.arr[14];
			arr[15] &= m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference XOR
		mat<4, 4, T> &operator ^= (const mat<4, 4, T> &m)
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
			arr[9] ^= m.arr[9];
			arr[10] ^= m.arr[10];
			arr[11] ^= m.arr[11];
			arr[12] ^= m.arr[12];
			arr[13] ^= m.arr[13];
			arr[14] ^= m.arr[14];
			arr[15] ^= m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference modulus
		mat<4, 4, T> &operator %= (const mat<4, 4, T> &m)
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
			arr[9] %= m.arr[9];
			arr[10] %= m.arr[10];
			arr[11] %= m.arr[11];
			arr[12] %= m.arr[12];
			arr[13] %= m.arr[13];
			arr[14] %= m.arr[14];
			arr[15] %= m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference shift left
		mat<4, 4, T> &operator <<= (const mat<4, 4, T> &m)
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
			arr[9] <<= m.arr[9];
			arr[10] <<= m.arr[10];
			arr[11] <<= m.arr[11];
			arr[12] <<= m.arr[12];
			arr[13] <<= m.arr[13];
			arr[14] <<= m.arr[14];
			arr[15] <<= m.arr[15];
			return *this;
		}
		//! Component-wise matrix reference shift right
		mat<4, 4, T> &operator >>= (const mat<4, 4, T> &m)
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
			arr[9] >>= m.arr[9];
			arr[10] >>= m.arr[10];
			arr[11] >>= m.arr[11];
			arr[12] >>= m.arr[12];
			arr[13] >>= m.arr[13];
			arr[14] >>= m.arr[14];
			arr[15] >>= m.arr[15];
			return *this;
		}

		//! Component-wise scalar reference multiplication
		mat<4, 4, T> &operator *= (const T &v)
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
			arr[9] *= v;
			arr[10] *= v;
			arr[11] *= v;
			arr[12] *= v;
			arr[13] *= v;
			arr[14] *= v;
			arr[15] *= v;
			return *this;
		}
		//! Component-wise scalar reference division
		mat<4, 4, T> &operator /= (const T &v)
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
			arr[9] /= v;
			arr[10] /= v;
			arr[11] /= v;
			arr[12] /= v;
			arr[13] /= v;
			arr[14] /= v;
			arr[15] /= v;
			return *this;
		}
		//! Component-wise scalar reference addition
		mat<4, 4, T> &operator += (const T &v)
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
			arr[9] += v;
			arr[10] += v;
			arr[11] += v;
			arr[12] += v;
			arr[13] += v;
			arr[14] += v;
			arr[15] += v;
			return *this;
		}
		//! Component-wise scalar reference subtraction
		mat<4, 4, T> &operator -= (const T &v)
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
			arr[9] -= v;
			arr[10] -= v;
			arr[11] -= v;
			arr[12] -= v;
			arr[13] -= v;
			arr[14] -= v;
			arr[15] -= v;
			return *this;
		}
		//! Component-wise scalar reference OR
		mat<4, 4, T> &operator |= (const T &v)
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
			arr[9] |= v;
			arr[10] |= v;
			arr[11] |= v;
			arr[12] |= v;
			arr[13] |= v;
			arr[14] |= v;
			arr[15] |= v;
			return *this;
		}
		//! Component-wise scalar reference AND
		mat<4, 4, T> &operator &= (const T &v)
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
			arr[9] &= v;
			arr[10] &= v;
			arr[11] &= v;
			arr[12] &= v;
			arr[13] &= v;
			arr[14] &= v;
			arr[15] &= v;
			return *this;
		}
		//! Component-wise scalar reference XOR
		mat<4, 4, T> &operator ^= (const T &v)
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
			arr[9] ^= v;
			arr[10] ^= v;
			arr[11] ^= v;
			arr[12] ^= v;
			arr[13] ^= v;
			arr[14] ^= v;
			arr[15] ^= v;
			return *this;
		}
		//! Component-wise scalar reference modulus
		mat<4, 4, T> &operator %= (const T &v)
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
			arr[9] %= v;
			arr[10] %= v;
			arr[11] %= v;
			arr[12] %= v;
			arr[13] %= v;
			arr[14] %= v;
			arr[15] %= v;
			return *this;
		}
		//! Component-wise scalar reference shift left
		mat<4, 4, T> &operator <<= (const T &v)
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
			arr[9] <<= v;
			arr[10] <<= v;
			arr[11] <<= v;
			arr[12] <<= v;
			arr[13] <<= v;
			arr[14] <<= v;
			arr[15] <<= v;
			return *this;
		}
		//! Component-wise scalar reference shift right
		mat<4, 4, T> &operator >>= (const T &v)
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
			arr[9] >>= v;
			arr[10] >>= v;
			arr[11] >>= v;
			arr[12] >>= v;
			arr[13] >>= v;
			arr[14] >>= v;
			arr[15] >>= v;
			return *this;
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! returns an identity matrix
		static constexpr mat<4, 4, T> identity()
		{
			return mat<4, 4, T>
				(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		static mat<4, 4, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8, const T &s9, const T &s10, const T &s11, const T &s12, const T &s13, const T &s14, const T &s15)
		{
			return mat<4, 4, T>
				(s0, s4, s8, s12,
					s1, s5, s9, s13,
					s2, s6, s10, s14,
					s3, s7, s11, s15);
		}

		//! Creates a 4x4 matrix using 4 row vectors
		static mat<4, 4, T> fromrows(vec<4, T> r0, vec<4, T> r1, vec<4, T> r2, vec<4, T> r3)
		{
			return mat<4, 4, T>
				(r0.x, r1.x, r2.x, r3.x,
					r0.y, r1.y, r2.y, r3.y,
					r0.z, r1.z, r2.z, r3.z,
					r0.w, r1.w, r2.w, r3.w);
		}

		//! Creates a 4x4 matrix using 4 column vectors
		static mat<4, 4, T> fromcols(vec<4, T> c0, vec<4, T> c1, vec<4, T> c2, vec<4, T> c3)
		{
			return mat<4, 4, T>
				(c0.x, c0.y, c0.z, c0.w,
					c1.x, c1.y, c1.z, c1.w,
					c2.x, c2.y, c2.z, c2.w,
					c3.x, c3.y, c3.z, c3.w);
		}

		static mat<4, 4, T> rotate(const ang<T> &an, const vec<3, T> &ax)
		{
			const T c = cos(an.radians());
			const T s = sin(an.radians());
			const T t = 1 - c;
			return mat<4, 4, T>
				((t * ax.x * ax.x) + c, (t * ax.x * ax.y) + ax.z * s, (t * ax.x * ax.z) - ax.y * s, 0,
					(t * ax.x * ax.y) - ax.z * s, (t * ax.y * ax.y) + c, (t * ax.y * ax.z) + ax.x * s, 0,
					(t * ax.x * ax.z) + ax.y * s, (t * ax.y * ax.z) - ax.x * s, (t * ax.z * ax.z) + c, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> rotatex(const ang<T> &x)
		{
			const T c = cos(x.radians());
			const T s = sin(x.radians());
			return mat<4, 4, T>
				(1, 0, 0, 0,
					0, c, s, 0,
					0, -s, c, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> rotatey(const ang<T> &x)
		{
			const T c = cos(x.radians());
			const T s = sin(x.radians());
			return mat<4, 4, T>
				(c, 0, -s, 0,
					0, 1, 0, 0,
					s, 0, c, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> rotatez(const ang<T> &x)
		{
			const T c = cos(x.radians());
			const T s = sin(x.radians());
			return mat<4, 4, T>
				(c, s, 0, 0,
					-s, c, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> scale(const T &s)
		{
			return mat<4, 4, T>
				(s, 0, 0, 0,
					0, s, 0, 0,
					0, 0, s, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> scale(const T &x, const T &y, const T &z)
		{
			return mat<4, 4, T>
				(x, 0, 0, 0,
					0, y, 0, 0,
					0, 0, z, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> scale(const vec<3, T> &v)
		{
			return mat<4, 4, T>
				(v.x, 0, 0, 0,
					0, v.y, 0, 0,
					0, 0, v.z, 0,
					0, 0, 0, 1);
		}

		static mat<4, 4, T> translate(const T &x, const T &y, const T &z)
		{
			return mat<4, 4, T>
				(1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					x, y, z, 1);
		}

		static mat<4, 4, T> translate(const vec<3, T> &v)
		{
			return translate(v.x, v.y, v.z);
		}

		//! generates a generic frustum transformation
		static mat<4, 4, T> frustum(const T &left, const T &right, const T &bottom, const T &top, const T &near, const T &far)
		{
			const T n2 = 2 * near;
			const T rml = right - left;
			const T tmb = top - bottom;
			const T nmf = near - far;
			return mat<4, 4, T>
				(n2 / rml, 0.f, 0.f, 0.f,
					0.f, n2 / tmb, 0.f, 0.f,
					(right + left) / rml, (top + bottom) / tmb, (near + far) / nmf, -1.f,
					0.f, 0.f, (n2 * far) / nmf, 0.f);
		}

		//! generates a 3d-perspective frustum transformation
		static mat<4, 4, T> perspective(const ang<T> &fovy, const T &aspect, const T &near, const T &far)
		{
			const T ys = static_cast<T>(1.0) / tan(fovy.radians() * static_cast<T>(0.5));
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
		static mat<4, 4, T> ortho(const T &left, const T &right, const T &bottom, const T &top, const T &near, const T &far)
		{
			return mat<4, 4, T>
				(static_cast<T>(2.0) / (right - left), 0, 0, 0,
					0, static_cast<T>(2.0) / (top - bottom), 0, 0,
					0, 0, static_cast<T>(2.0) / (near - far), 0,
					(left + right) / (left - right), (bottom + top) / (bottom - top), (near + far) / (far - near), 1);
		}

		//! generates a catmull-rom identity transformation
		static constexpr mat<4, 4, T> catmull()
		{
			return mat<4, 4, T>::roworder(
				-0.5f, 1.5f, -1.5f, 0.5f,
				1.0f, -2.5f, 2.0f, -0.5f,
				-0.5f, 0.0f, 0.5f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f);
		}

		//! generates a bezier identity transformation
		static constexpr mat<4, 4, T> bezier()
		{
			return mat<4, 4, T>::roworder(
				-1.0f, 3.0f, -3.0f, 1.0f,
				3.0f, -6.0f, 3.0f, 0.0f,
				-3.0f, 3.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 0.0f);
		}

		//! converts clipspace matrix to screenspace matrix
		static constexpr mat<4, 4, T> cliptoscreen()
		{
			return mat<4, 4, T>(
				0.5f, 0.0f, 0.0f, 0.0f,
				0.0f, 0.5f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.5f, 0.0f,
				0.5f, 0.5f, 0.5f, 1.0f);
		}

		//! converts screenspace to clipspace
		static constexpr mat<4, 4, T> screentoclip()
		{
			return mat<4, 4, T>(
				2.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 2.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 2.0f, 0.0f,
				-1.0f, -1.0f, -1.0f, 1.0f);
		}

	}; //! struct mat

	//! Matrix determinant
	template<typename T>
	static T det(const mat<4, 4, T> &m)
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
	static mat<4, 4, T> inverse(const mat<4, 4, T> &m)
	{
		return adjoint(m) / det(m);
	}

	template<typename T>
	static mat<4, 4, T> fastinverse(const mat<4, 4, T> &m)
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

#pragma warning(pop)

//

#endif//_DYM_MAT4_H_