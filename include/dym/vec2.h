#ifndef _DYM_VEC2_H_
#define _DYM_VEC2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"

#ifndef DYM_DISABLE_SWIZZLING
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"
#endif

//

namespace dym
{////

	template <typename T> struct vec <2, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct
			{
				T data[2];
			};
			struct
			{
				T x, y;
			};
			struct
			{
				T r, g;
			};
			struct
			{
				T s, t;
			};
			#ifndef DYM_DISABLE_SWIZZLING
			swizzle2 <0, 0, T> xx, rr, ss;
			swizzle2 <0, 1, T> xy, rg, st;
			swizzle2 <1, 0, T> yx, gr, ts;
			swizzle2 <1, 1, T> yy, gg, tt;
			swizzle3 <0, 0, 0, T> xxx, rrr, sss;
			swizzle3 <0, 0, 1, T> xxy, rrg, sst;
			swizzle3 <0, 1, 0, T> xyx, rgr, sts;
			swizzle3 <0, 1, 1, T> xyy, rgg, stt;
			swizzle3 <1, 0, 0, T> yxx, grr, tss;
			swizzle3 <1, 0, 1, T> yxy, grg, tst;
			swizzle3 <1, 1, 0, T> yyx, ggr, tts;
			swizzle3 <1, 1, 1, T> yyy, ggg, ttt;
			swizzle4 <0, 0, 0, 0, T> xxxx, rrrr, ssss;
			swizzle4 <0, 0, 0, 1, T> xxxy, rrrg, ssst;
			swizzle4 <0, 0, 1, 0, T> xxyx, rrgr, ssts;
			swizzle4 <0, 0, 1, 1, T> xxyy, rrgg, sstt;
			swizzle4 <0, 1, 0, 0, T> xyxx, rgrr, stss;
			swizzle4 <0, 1, 0, 1, T> xyxy, rgrg, stst;
			swizzle4 <0, 1, 1, 0, T> xyyx, rggr, stts;
			swizzle4 <0, 1, 1, 1, T> xyyy, rggg, sttt;
			swizzle4 <1, 0, 0, 0, T> yxxx, grrr, tsss;
			swizzle4 <1, 0, 0, 1, T> yxxy, grrg, tsst;
			swizzle4 <1, 0, 1, 0, T> yxyx, grgr, tsts;
			swizzle4 <1, 0, 1, 1, T> yxyy, grgg, tstt;
			swizzle4 <1, 1, 0, 0, T> yyxx, ggrr, ttss;
			swizzle4 <1, 1, 0, 1, T> yyxy, ggrg, ttst;
			swizzle4 <1, 1, 1, 0, T> yyyx, gggr, ttts;
			swizzle4 <1, 1, 1, 1, T> yyyy, gggg, tttt;
			#endif
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		vec()
			: x(static_cast<T>(0)), y(static_cast<T>(0))
		{}

		//! Initialize vec2 with two values
		vec(const T &s0, const T &s1)
			: x(s0), y(s1)
		{}

		#ifndef DYM_DISABLE_SWIZZLING
		//! Swizzle constructor
		template<int a, int b>
		vec(const swizzle2<a, b, T> &s)
			: x(s[a]), y(s[b])
		{}
		#endif

		//! Copy constructor
		vec(const vec<2, T> &v)
			: x(v.x), y(v.y)
		{}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit  vec(const vec<2, U> &v)
			: x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
		{}

		//! Fill constructor
		explicit  vec(const T &s)
			: x(s), y(s)
		{}

		//! Array initializer
		explicit  vec(const T *a)
			: x(a[0]), y(a[1])
		{}

		//! Initializer list constructor
		vec(std::initializer_list<T> l)
			: x(*(l.begin())), y(*(l.begin() + 1))
		{}

		//! Copy constructor for differently-sized vector
		template<int d2>
		vec(const vec<d2, T> &v)
		{
			if (d2 < 2)
			{
				for (std::size_t i = 0; i < d2; ++i)
				{
					data[i] = v.data[i];
				}
			}
			else
			{
				for (std::size_t i = 0; i < 2; ++i)
				{
					data[i] = v.data[i];
				}
			}
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		T &operator[](const std::size_t i)
		{
			return data[i];
		}

		//! Vector const index operator
		const T &operator[](const std::size_t i) const
		{
			return data[i];
		}

		///////////////////////////
		//! ARITHMETIC OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		vec<2, T> operator - () const
		{
			return vec<2, T>(-x, -y);
		}
		//! Component-wise unary negation
		vec<2, T> operator ~ () const
		{
			return vec<2, T>(~x, ~y);
		}
		//! Vector assignment
		vec<2, T> &operator = (const vec<2, T> &v)
		{
			x = v.x; y = v.y; return *this;
		}

		//! Component-wise vector multiplication
		vec<2, T> operator * (const vec<2, T> &v) const
		{
			return vec<2, T>(x * v.x, y * v.y);
		}
		//! Component-wise vector division
		vec<2, T> operator / (const vec<2, T> &v) const
		{
			return vec<2, T>(x / v.x, y / v.y);
		}
		//! Component-wise vector addition
		vec<2, T> operator + (const vec<2, T> &v) const
		{
			return vec<2, T>(x + v.x, y + v.y);
		}
		//! Component-wise vector subtraction
		vec<2, T> operator - (const vec<2, T> &v) const
		{
			return vec<2, T>(x - v.x, y - v.y);
		}
		//! Component-wise vector OR
		vec<2, T> operator | (const vec<2, T> &v) const
		{
			return vec<2, T>(x | v.x, y | v.y);
		}
		//! Component-wise vector AND
		vec<2, T> operator & (const vec<2, T> &v) const
		{
			return vec<2, T>(x & v.x, y & v.y);
		}
		//! Component-wise vector XOR
		vec<2, T> operator ^ (const vec<2, T> &v) const
		{
			return vec<2, T>(x ^ v.x, y ^ v.y);
		}
		//! Component-wise vector modulus
		vec<2, T> operator % (const vec<2, T> &v) const
		{
			return vec<2, T>(x % v.x, y % v.y);
		}
		//! Component-wise vector shift left
		vec<2, T> operator << (const vec<2, T> &v) const
		{
			return vec<2, T>(x << v.x, y << v.y);
		}
		//! Component-wise vector shift right
		vec<2, T> operator >> (const vec<2, T> &v) const
		{
			return vec<2, T>(x >> v.x, y >> v.y);
		}

		//! Component-wise scalar multiplication
		vec<2, T> operator * (const T &v) const
		{
			return vec<2, T>(x * v, y * v);
		}
		//! Component-wise scalar division
		vec<2, T> operator / (const T &v) const
		{
			return vec<2, T>(x / v, y / v);
		}
		//! Component-wise scalar addition
		vec<2, T> operator + (const T &v) const
		{
			return vec<2, T>(x + v, y + v);
		}
		//! Component-wise scalar subtraction
		vec<2, T> operator - (const T &v) const
		{
			return vec<2, T>(x - v, y - v);
		}
		//! Component-wise scalar OR
		vec<2, T> operator | (const T &v) const
		{
			return vec<2, T>(x | v, y | v);
		}
		//! Component-wise scalar AND
		vec<2, T> operator & (const T &v) const
		{
			return vec<2, T>(x & v, y & v);
		}
		//! Component-wise scalar XOR
		vec<2, T> operator ^ (const T &v) const
		{
			return vec<2, T>(x ^ v, y ^ v);
		}
		//! Component-wise scalar modulus
		vec<2, T> operator % (const T &v) const
		{
			return vec<2, T>(x % v, y % v);
		}
		//! Component-wise scalar shift left
		vec<2, T> operator << (const T &v) const
		{
			return vec<2, T>(x << v, y << v);
		}
		//! Component-wise scalar shift right
		vec<2, T> operator >> (const T &v) const
		{
			return vec<2, T>(x >> v, y >> v);
		}

		//! Component-wise vector reference multiplication
		vec<2, T> &operator *= (const vec<2, T> &v)
		{
			x *= v.x; y *= v.y; return *this;
		}
		//! Component-wise vector reference division
		vec<2, T> &operator /= (const vec<2, T> &v)
		{
			x /= v.x; y /= v.y; return *this;
		}
		//! Component-wise vector reference addition
		vec<2, T> &operator += (const vec<2, T> &v)
		{
			x += v.x; y += v.y; return *this;
		}
		//! Component-wise vector reference subtraction
		vec<2, T> &operator -= (const vec<2, T> &v)
		{
			x -= v.x; y -= v.y; return *this;
		}
		//! Component-wise vector reference OR
		vec<2, T> &operator |= (const vec<2, T> &v)
		{
			x |= v.x; y |= v.y; return *this;
		}
		//! Component-wise vector reference AND
		vec<2, T> &operator &= (const vec<2, T> &v)
		{
			x &= v.x; y &= v.y; return *this;
		}
		//! Component-wise vector reference XOR
		vec<2, T> &operator ^= (const vec<2, T> &v)
		{
			x ^= v.x; y ^= v.y; return *this;
		}
		//! Component-wise vector reference modulus
		vec<2, T> &operator %= (const vec<2, T> &v)
		{
			x %= v.x; y %= v.y; return *this;
		}
		//! Component-wise vector reference shift left
		vec<2, T> &operator <<= (const vec<2, T> &v)
		{
			x <<= v.x; y <<= v.y; return *this;
		}
		//! Component-wise vector reference shift right
		vec<2, T> &operator >>= (const vec<2, T> &v)
		{
			x >>= v.x; y >>= v.y; return *this;
		}

		//! Component-wise scalar reference multiplication
		vec<2, T> &operator *= (const T &v)
		{
			x *= v; y *= v; return *this;
		}
		//! Component-wise scalar reference division
		vec<2, T> &operator /= (const T &v)
		{
			x /= v; y /= v; return *this;
		}
		//! Component-wise scalar reference addition
		vec<2, T> &operator += (const T &v)
		{
			x += v; y += v; return *this;
		}
		//! Component-wise scalar reference subtraction
		vec<2, T> &operator -= (const T &v)
		{
			x -= v; y -= v; return *this;
		}
		//! Component-wise scalar reference OR
		vec<2, T> &operator |= (const T &v)
		{
			x |= v; y |= v; return *this;
		}
		//! Component-wise scalar reference AND
		vec<2, T> &operator &= (const T &v)
		{
			x &= v; y &= v; return *this;
		}
		//! Component-wise scalar reference XOR
		vec<2, T> &operator ^= (const T &v)
		{
			x ^= v; y ^= v; return *this;
		}
		//! Component-wise scalar reference modulus
		vec<2, T> &operator %= (const T &v)
		{
			x %= v; y %= v; return *this;
		}
		//! Component-wise scalar reference shift left
		vec<2, T> &operator <<= (const T &v)
		{
			x <<= v; y <<= v; return *this;
		}
		//! Component-wise scalar reference shift right
		vec<2, T> &operator >>= (const T &v)
		{
			x >>= v; y >>= v; return *this;
		}

		//! Component-wise equality comparison
		bool operator == (const vec<2, T> &v) const
		{
			return x == v.x && y == v.y;
		}
		//! Component-wise inequality comparison
		bool operator != (const vec<2, T> &v) const
		{
			return x != v.x || y != v.y;
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! NaN vector (NaN, NaN)
		static constexpr vec<2, T> nan()
		{
			return vec<2, T>(NAN, NAN);
		}

		//! Infinity vector (inf, inf)
		static constexpr vec<2, T> inf()
		{
			return vec<2, T>(INFINITY, INFINITY);
		}

		//! Zero vector (0,0)
		static constexpr vec<2, T> zero()
		{
			return vec<2, T>(0, 0);
		}

		//! One vector (1,1)
		static constexpr vec<2, T> one()
		{
			return vec<2, T>(1, 1);
		}

		//! Up vector (0,1)
		static constexpr vec<2, T> up()
		{
			return vec<2, T>(0, 1);
		}

		//! Down vector (0,-1)
		static constexpr vec<2, T> down()
		{
			return vec<2, T>(0, -1);
		}

		//! Right vector (1,0)
		static constexpr vec<2, T> right()
		{
			return vec<2, T>(1, 0);
		}

		//! Left vector (-1,0)
		static constexpr vec<2, T> left()
		{
			return vec<2, T>(-1, 0);
		}

	}; //! struct vec2

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef vec<2, float>			vec2, vec2f;
	typedef vec<2, double>			vec2d;
	typedef vec<2, unsigned char>	vec2uc;
	typedef vec<2, char>			vec2c;
	typedef vec<2, unsigned short>	vec2us;
	typedef vec<2, short>			vec2s;
	typedef vec<2, unsigned int>	vec2ui;
	typedef vec<2, int>				vec2i;
	typedef vec<2, unsigned long>	vec2ul;
	typedef vec<2, long>			vec2l;

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <typename T = float>
	static std::ostream &operator<<(std::ostream &os, const vec<2, T> &v)
	{
		os << "| " << v.x << ' ' << v.y << " |";
		return os;
	}

	//! Scalar-Vector multiplication
	template <typename T = float>
	static vec<2, T> operator*(const T &l, const vec<2, T> &r)
	{
		return vec<2, T>(l * r.x, l * r.y);
	}


	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Calculates the dot or scalar product of two vectors
	template <typename T = float>
	static T dot(const vec<2, T> &l, const vec<2, T> &r)
	{
		return (l.x * r.x) + (l.y * r.y);
	}

	//! Returns length squared of vector
	template <typename T = float>
	static T lengthsq(const vec<2, T> &v)
	{
		return sq(v.x) + sq(v.y);
	}

	//! Returns length of vector, or sqrt(lengthsq)
	template <typename T = float>
	static T length(const vec<2, T> &v)
	{
		return sqrt(sq(v.x) + sq(v.y));
	}

	//! Returns a component-wise minimum of two vectors
	template <typename T = float>
	static vec<2, T> min(const vec<2, T> &l, const vec<2, T> &r)
	{
		return vec<2, T>(min(l.x, r.x), min(l.y, r.y));
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template <typename T = float>
	static vec<2, T> min(const vec<2, T> &l, const T &r)
	{
		return vec<2, T>(min(l.x, r), min(l.y, r));
	}

	//! Returns a component-wise minimum of two vectors
	template <typename T = float>
	static vec<2, T> max(const vec<2, T> &l, const vec<2, T> &r)
	{
		return vec<2, T>(max(l.x, r.x), max(l.y, r.y));
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template <typename T = float>
	static vec<2, T> max(const vec<2, T> &l, const T &r)
	{
		return vec<2, T>(max(l.x, r), max(l.y, r));
	}

	//! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
	template<typename T = float>
	static vec<3, T> affine(const vec<2, T> &v)
	{
		return vec<3, T>(v.x, v.y, static_cast<T>(1));
	}

	//! Returns whether vector is NaN
	template<typename T = float>
	static bool isnan(const vec<2, T> &v)
	{
		return std::isnan(v.x) || std::isnan(v.y);
	}

	//! Returns whether vector is inf
	template<typename T = float>
	static bool isinf(const vec<2, T> &v)
	{
		return std::isinf(v.x) || std::isinf(v.y);
	}

	//! Relative equality (for floating-point vectors)
	template<typename T = float>
	static bool req(const vec<2, T> &l, const vec<2, T> &r, T rng = 1e-8)
	{
		return req(l.x, r.x, rng) && req(l.y, r.y, rng);
	}

}////

//

#pragma warning(pop)

//

#endif