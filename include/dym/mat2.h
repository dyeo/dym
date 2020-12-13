#ifndef _DYM_MAT2_H_
#define _DYM_MAT2_H_

//

#pragma warning(push)
#pragma warning(disable:4456;disable:4127)

//

#include "mat.h"
#include "angle.h"

//

namespace dym
{////

	//! A column-major matrix spanning r rows and c columns
	template <typename T> struct mat <2, 2, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		constexpr int rows() const
		{
			return 2;
		}

		constexpr int cols() const
		{
			return 2;
		}

		constexpr int dim() const
		{
			return 2;
		}

		//! Unioned data members
		union
		{
			struct
			{
				vec<2, T> data[2];
			};
			struct
			{
				T arr[4];
			};
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		constexpr mat()
			: arr{ static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1) }
		{}

		~mat() = default;

		//! Initializer list constructor
		//! Columns span left-to-right in initialization, and rows span top-to-bottom
		//! This is because matrices are stored column-major
		constexpr mat(std::initializer_list<T> l)
			: arr{ *(l.begin()), *(l.begin() + 1), *(l.begin() + 2), *(l.begin() + 3) }
		{}

		//! Copy constructor
		constexpr mat(const mat<2, 2, T> &v)
			: arr{ v.arr[0], v.arr[1], v.arr[2], v.arr[3] }
		{}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit constexpr mat(const mat<2, 2, U> &v)
			: arr{ static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]), static_cast<T>(v.arr[3]) }
		{}

		//! Fill constructor
		explicit constexpr mat(const T &s)
			: arr{ s, s, s, s }
		{}

		//! Array initializer
		explicit constexpr mat(const T *a)
			: arr{ a[0], a[1], a[2], a[3] }
		{}

		//! Value constructor
		constexpr mat(const T &s0, const T &s1, const T &s2, const T &s3)
			: arr{ s0, s1, s2, s3 }
		{}

		//! Explicit type-conversionm value constructor
		template<typename U>
		explicit constexpr mat(const U &s0, const U &s1, const U &s2, const U &s3)
			: arr{ static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(s3) }
		{}

		//! Constructs a 2x2 matrix using the top-left portion of a 3x3 matrix;
		constexpr mat(const mat<3, 3, T> &m)
			: arr{ m.arr[0], m.arr[1], m.arr[3], m.arr[4] }
		{}

		//! Constructs a 2x2 matrix using the top-left portion of a 4x4 matrix;
		constexpr mat(const mat<4, 4, T> &m)
			: arr{ m.arr[0], m.arr[1], m.arr[4], m.arr[5] }
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
		vec<2, T> col(const std::size_t i)
		{
			return data[i];
		}

		//! Row function - returns row as vector of T
		vec<2, T> row(const std::size_t i)
		{
			vec<2, T> v = vec<2, T>(arr[i], arr[i + 2]);
			return v;
		}

		//! Matrix index operator - returns column
		vec<2, T> &operator[](const std::size_t i)
		{
			return data[i];
		}

		//! Matrix const index operator - returns column
		const vec<2, T> &operator[](const std::size_t i) const
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
		mat<2, 2, T> operator - () const
		{
			return mat<2, 2, T>(-arr[0], -arr[1], -arr[2], -arr[3]);
		}
		//! Component-wise unary negation
		mat<2, 2, T> operator ~ () const
		{
			return mat<2, 2, T>(~arr[0], ~arr[1], ~arr[2], ~arr[3]);
		}
		//! Vector assignment
		mat<2, 2, T> &operator = (const mat<2, 2, T> &m)
		{
			arr[0] = m.arr[0];
			arr[1] = m.arr[1];
			arr[2] = m.arr[2];
			arr[3] = m.arr[3];
			return *this;
		}

		//! Component-wise matrix addition
		mat<2, 2, T> operator + (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] + m.arr[0], arr[1] + m.arr[1], arr[2] + m.arr[2], arr[3] + m.arr[3]);
		}
		//! Component-wise matrix subtraction
		mat<2, 2, T> operator - (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] - m.arr[0], arr[1] - m.arr[1], arr[2] - m.arr[2], arr[3] - m.arr[3]);
		}
		//! Component-wise matrix OR
		mat<2, 2, T> operator | (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] | m.arr[0], arr[1] | m.arr[1], arr[2] | m.arr[2], arr[3] | m.arr[3]);
		}
		//! Component-wise matrix AND
		mat<2, 2, T> operator & (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] & m.arr[0], arr[1] & m.arr[1], arr[2] & m.arr[2], arr[3] & m.arr[3]);
		}
		//! Component-wise matrix XOR
		mat<2, 2, T> operator ^ (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] ^ m.arr[0], arr[1] ^ m.arr[1], arr[2] ^ m.arr[2], arr[3] ^ m.arr[3]);
		}
		//! Component-wise matrix modulus
		mat<2, 2, T> operator % (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] % m.arr[0], arr[1] % m.arr[1], arr[2] % m.arr[2], arr[3] % m.arr[3]);
		}
		//! Component-wise matrix shift left
		mat<2, 2, T> operator << (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] << m.arr[0], arr[1] << m.arr[1], arr[2] << m.arr[2], arr[3] << m.arr[3]);
		}
		//! Component-wise matrix shift right
		mat<2, 2, T> operator >> (const mat<2, 2, T> &m) const
		{
			return mat<2, 2, T>(arr[0] >> m.arr[0], arr[1] >> m.arr[1], arr[2] >> m.arr[2], arr[3] >> m.arr[3]);
		}

		//! Component-wise scalar multiplication
		mat<2, 2, T> operator * (const T &v) const
		{
			return mat<2, 2, T>(arr[0] * v, arr[1] * v, arr[2] * v, arr[3] * v);
		}
		//! Component-wise scalar division
		mat<2, 2, T> operator / (const T &v) const
		{
			return mat<2, 2, T>(arr[0] / v, arr[1] / v, arr[2] / v, arr[3] / v);
		}
		//! Component-wise scalar addition
		mat<2, 2, T> operator + (const T &v) const
		{
			return mat<2, 2, T>(arr[0] + v, arr[1] + v, arr[2] + v, arr[3] + v);
		}
		//! Component-wise scalar subtraction
		mat<2, 2, T> operator - (const T &v) const
		{
			return mat<2, 2, T>(arr[0] - v, arr[1] - v, arr[2] - v, arr[3] - v);
		}
		//! Component-wise scalar OR
		mat<2, 2, T> operator | (const T &v) const
		{
			return mat<2, 2, T>(arr[0] | v, arr[1] | v, arr[2] | v, arr[3] | v);
		}
		//! Component-wise scalar AND
		mat<2, 2, T> operator & (const T &v) const
		{
			return mat<2, 2, T>(arr[0] & v, arr[1] & v, arr[2] & v, arr[3] & v);
		}
		//! Component-wise scalar XOR
		mat<2, 2, T> operator ^ (const T &v) const
		{
			return mat<2, 2, T>(arr[0] ^ v, arr[1] ^ v, arr[2] ^ v, arr[3] ^ v);
		}
		//! Component-wise scalar modulus
		mat<2, 2, T> operator % (const T &v) const
		{
			return mat<2, 2, T>(arr[0] % v, arr[1] % v, arr[2] % v, arr[3] % v);
		}
		//! Component-wise scalar shift left
		mat<2, 2, T> operator << (const T &v) const
		{
			return mat<2, 2, T>(arr[0] << v, arr[1] << v, arr[2] << v, arr[3] << v);
		}
		//! Component-wise scalar shift right
		mat<2, 2, T> operator >> (const T &v) const
		{
			return mat<2, 2, T>(arr[0] >> v, arr[1] >> v, arr[2] >> v, arr[3] >> v);
		}

		//! Component-wise matrix reference addition
		mat<2, 2, T> &operator += (const mat<2, 2, T> &m)
		{
			arr[0] += m.arr[0];
			arr[1] += m.arr[1];
			arr[2] += m.arr[2];
			arr[3] += m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference subtraction
		mat<2, 2, T> &operator -= (const mat<2, 2, T> &m)
		{
			arr[0] -= m.arr[0];
			arr[1] -= m.arr[1];
			arr[2] -= m.arr[2];
			arr[3] -= m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference OR
		mat<2, 2, T> &operator |= (const mat<2, 2, T> &m)
		{
			arr[0] |= m.arr[0];
			arr[1] |= m.arr[1];
			arr[2] |= m.arr[2];
			arr[3] |= m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference AND
		mat<2, 2, T> &operator &= (const mat<2, 2, T> &m)
		{
			arr[0] &= m.arr[0];
			arr[1] &= m.arr[1];
			arr[2] &= m.arr[2];
			arr[3] &= m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference XOR
		mat<2, 2, T> &operator ^= (const mat<2, 2, T> &m)
		{
			arr[0] ^= m.arr[0];
			arr[1] ^= m.arr[1];
			arr[2] ^= m.arr[2];
			arr[3] ^= m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference modulus
		mat<2, 2, T> &operator %= (const mat<2, 2, T> &m)
		{
			arr[0] %= m.arr[0];
			arr[1] %= m.arr[1];
			arr[2] %= m.arr[2];
			arr[3] %= m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference shift left
		mat<2, 2, T> &operator <<= (const mat<2, 2, T> &m)
		{
			arr[0] <<= m.arr[0];
			arr[1] <<= m.arr[1];
			arr[2] <<= m.arr[2];
			arr[3] <<= m.arr[3];
			return *this;
		}
		//! Component-wise matrix reference shift right
		mat<2, 2, T> &operator >>= (const mat<2, 2, T> &m)
		{
			arr[0] >>= m.arr[0];
			arr[1] >>= m.arr[1];
			arr[2] >>= m.arr[2];
			arr[3] >>= m.arr[3];
			return *this;
		}

		//! Component-wise scalar reference multiplication
		mat<2, 2, T> &operator *= (const T &v)
		{
			arr[0] *= v;
			arr[1] *= v;
			arr[2] *= v;
			arr[3] *= v;
			return *this;
		}
		//! Component-wise scalar reference division
		mat<2, 2, T> &operator /= (const T &v)
		{
			arr[0] /= v;
			arr[1] /= v;
			arr[2] /= v;
			arr[3] /= v;
			return *this;
		}
		//! Component-wise scalar reference addition
		mat<2, 2, T> &operator += (const T &v)
		{
			arr[0] += v;
			arr[1] += v;
			arr[2] += v;
			arr[3] += v;
			return *this;
		}
		//! Component-wise scalar reference subtraction
		mat<2, 2, T> &operator -= (const T &v)
		{
			arr[0] -= v;
			arr[1] -= v;
			arr[2] -= v;
			arr[3] -= v;
			return *this;
		}
		//! Component-wise scalar reference OR
		mat<2, 2, T> &operator |= (const T &v)
		{
			arr[0] |= v;
			arr[1] |= v;
			arr[2] |= v;
			arr[3] |= v;
			return *this;
		}
		//! Component-wise scalar reference AND
		mat<2, 2, T> &operator &= (const T &v)
		{
			arr[0] &= v;
			arr[1] &= v;
			arr[2] &= v;
			arr[3] &= v;
			return *this;
		}
		//! Component-wise scalar reference XOR
		mat<2, 2, T> &operator ^= (const T &v)
		{
			arr[0] ^= v;
			arr[1] ^= v;
			arr[2] ^= v;
			arr[3] ^= v;
			return *this;
		}
		//! Component-wise scalar reference modulus
		mat<2, 2, T> &operator %= (const T &v)
		{
			arr[0] %= v;
			arr[1] %= v;
			arr[2] %= v;
			arr[3] %= v;
			return *this;
		}
		//! Component-wise scalar reference shift left
		mat<2, 2, T> &operator <<= (const T &v)
		{
			arr[0] <<= v;
			arr[1] <<= v;
			arr[2] <<= v;
			arr[3] <<= v;
			return *this;
		}
		//! Component-wise scalar reference shift right
		mat<2, 2, T> &operator >>= (const T &v)
		{
			arr[0] >>= v;
			arr[1] >>= v;
			arr[2] >>= v;
			arr[3] >>= v;
			return *this;
		}

		/////////////////////////////////
		//! MATRIX GENERATOR FUNCTIONS //
		/////////////////////////////////

		//! Generates a 2x2 identity matrix
		static constexpr mat<2, 2, T> identity()
		{
			return mat<2, 2, T>(1, 0, 0, 1);
		}

		//! Creates a row-order matrix using individual elements
		static mat<2, 2, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3)
		{
			return mat<2, 2, T>
				(s0, s2,
					s1, s3);
		}

		//! Creates a 2x2 matrix using 2 row vectors
		static mat<2, 2, T> fromrows(vec<2, T> r0, vec<2, T> r1)
		{
			return mat<2, 2, T>
				(r0.x, r1.x,
					r0.y, r1.y);
		}

		//! Creates a 2x2 matrix using 2 column vectors
		static mat<2, 2, T> fromcols(vec<2, T> c0, vec<2, T> c1)
		{
			return mat<2, 2, T>
				(c0.x, c0.y,
					c1.x, c1.y);
		}

		//! Generates a clockwise rotation matrix using an angle
		static mat<2, 2, T> rotate(const ang<T> &a)
		{
			const T ca = cos(a.radians());
			const T sa = sin(a.radians());
			return mat<2, 2, T>(ca, sa, -sa, ca);
		}

		//! Generates a clockwise rotation matrix using an angle
		static mat<2, 2, T> rotatecw(const ang<T> &a)
		{
			return rotate(a);
		}

		//! Generates a counter-clockwise rotation matrix using an angle
		static mat<2, 2, T> rotateccw(const ang<T> &a)
		{
			float ca = cos(a.radians());
			float sa = sin(a.radians());
			return mat<2, 2, T>(ca, -sa, sa, ca);
		}

		//! Generates a scaling matrix using a single scaling value
		static mat<2, 2, T> scale(const T &s)
		{
			return mat<2, 2, T>(s, 0, 0, s);
		}

		//! Generates a scaling matrix using an x and y scaling value
		static mat<2, 2, T> scale(const T &x, const T &y)
		{
			return mat<2, 2, T>(x, 0, 0, y);
		}

		//! Shears along the x axis
		static mat<2, 2, T> shearx(const T &k)
		{
			return mat<2, 2, T>(1, 0, k, 1);
		}

		//! Shears along the y axis
		static mat<2, 2, T> sheary(const T &k)
		{
			return mat<2, 2, T>(1, k, 0, 1);
		}

		static mat<3, 3, T> translate_affine(const T &x, const T &y)
		{
			mat<3, 3, T> res = mat<3, 3, T>::identity();
			res[2] = vec<3, T>(x, y, 1);
		}

		static mat<3, 3, T> translate_affine(const vec<2, T> &t)
		{
			return translate_affine(t.x, t.y);
		}

	}; //! struct mat

	template <typename T>
	static mat<2, 2, T> operator*(const mat<2, 2, T> &m, const mat<2, 2, T> &n)
	{
		return mat<2, 2, T>
			(m.arr[0] * n.arr[0] + m.arr[2] * n.arr[1], m.arr[1] * n.arr[0] + m.arr[3] * n.arr[1],
				m.arr[0] * n.arr[2] + m.arr[2] * n.arr[3], m.arr[1] * n.arr[2] + m.arr[3] * n.arr[3]);
	}

	//! Matrix determinant
	template<typename T>
	static T det(const mat<2, 2, T> &m)
	{
		return (m.arr[0] * m.arr[3])
			- (m.arr[1] * m.arr[2]);
	}

	//! Inverts the matrix, such that m * inverse(m) = the identity
	template<typename T>
	static mat<2, 2, T> inverse(const mat<2, 2, T> &m)
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

#pragma warning(pop)

//

#endif//_DYM_MAT2_H_