#ifndef _GMTK_VEC3_H_
#define _GMTK_VEC3_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"

#ifndef GMTK_DISABLE_SWIZZLING
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"
#endif

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <3, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct
			{
				T data[3];
			};
			struct
			{
				T x, y, z;
			};
			struct
			{
				T r, g, b;
			};
			struct
			{
				T s, t, p;
			};
			#ifndef GMTK_DISABLE_SWIZZLING
			swizzle2 <0, 0, T> xx, rr, ss;
			swizzle2 <0, 1, T> xy, rg, st;
			swizzle2 <0, 2, T> xz, rb, sp;
			swizzle2 <1, 0, T> yx, gr, ts;
			swizzle2 <1, 1, T> yy, gg, tt;
			swizzle2 <1, 2, T> yz, gb, tp;
			swizzle2 <2, 0, T> zx, br, ps;
			swizzle2 <2, 1, T> zy, bg, pt;
			swizzle2 <2, 2, T> zz, bb, pp;
			swizzle3 <0, 0, 0, T> xxx, rrr, sss;
			swizzle3 <0, 0, 1, T> xxy, rrg, sst;
			swizzle3 <0, 0, 2, T> xxz, rrb, ssp;
			swizzle3 <0, 1, 0, T> xyx, rgr, sts;
			swizzle3 <0, 1, 1, T> xyy, rgg, stt;
			swizzle3 <0, 1, 2, T> xyz, rgb, stp;
			swizzle3 <0, 2, 0, T> xzx, rbr, sps;
			swizzle3 <0, 2, 1, T> xzy, rbg, spt;
			swizzle3 <0, 2, 2, T> xzz, rbb, spp;
			swizzle3 <1, 0, 0, T> yxx, grr, tss;
			swizzle3 <1, 0, 1, T> yxy, grg, tst;
			swizzle3 <1, 0, 2, T> yxz, grb, tsp;
			swizzle3 <1, 1, 0, T> yyx, ggr, tts;
			swizzle3 <1, 1, 1, T> yyy, ggg, ttt;
			swizzle3 <1, 1, 2, T> yyz, ggb, ttp;
			swizzle3 <1, 2, 0, T> yzx, gbr, tps;
			swizzle3 <1, 2, 1, T> yzy, gbg, tpt;
			swizzle3 <1, 2, 2, T> yzz, gbb, tpp;
			swizzle3 <2, 0, 0, T> zxx, brr, pss;
			swizzle3 <2, 0, 1, T> zxy, brg, pst;
			swizzle3 <2, 0, 2, T> zxz, brb, psp;
			swizzle3 <2, 1, 0, T> zyx, bgr, pts;
			swizzle3 <2, 1, 1, T> zyy, bgg, ptt;
			swizzle3 <2, 1, 2, T> zyz, bgb, ptp;
			swizzle3 <2, 2, 0, T> zzx, bbr, pps;
			swizzle3 <2, 2, 1, T> zzy, bbg, ppt;
			swizzle3 <2, 2, 2, T> zzz, bbb, ppp;
			swizzle4 <0, 0, 0, 0, T> xxxx, rrrr, ssss;
			swizzle4 <0, 0, 0, 1, T> xxxy, rrrg, ssst;
			swizzle4 <0, 0, 0, 2, T> xxxz, rrrb, sssp;
			swizzle4 <0, 0, 1, 0, T> xxyx, rrgr, ssts;
			swizzle4 <0, 0, 1, 1, T> xxyy, rrgg, sstt;
			swizzle4 <0, 0, 1, 2, T> xxyz, rrgb, sstp;
			swizzle4 <0, 0, 2, 0, T> xxzx, rrbr, ssps;
			swizzle4 <0, 0, 2, 1, T> xxzy, rrbg, sspt;
			swizzle4 <0, 0, 2, 2, T> xxzz, rrbb, sspp;
			swizzle4 <0, 1, 0, 0, T> xyxx, rgrr, stss;
			swizzle4 <0, 1, 0, 1, T> xyxy, rgrg, stst;
			swizzle4 <0, 1, 0, 2, T> xyxz, rgrb, stsp;
			swizzle4 <0, 1, 1, 0, T> xyyx, rggr, stts;
			swizzle4 <0, 1, 1, 1, T> xyyy, rggg, sttt;
			swizzle4 <0, 1, 1, 2, T> xyyz, rggb, sttp;
			swizzle4 <0, 1, 2, 0, T> xyzx, rgbr, stps;
			swizzle4 <0, 1, 2, 1, T> xyzy, rgbg, stpt;
			swizzle4 <0, 1, 2, 2, T> xyzz, rgbb, stpp;
			swizzle4 <0, 2, 0, 0, T> xzxx, rbrr, spss;
			swizzle4 <0, 2, 0, 1, T> xzxy, rbrg, spst;
			swizzle4 <0, 2, 0, 2, T> xzxz, rbrb, spsp;
			swizzle4 <0, 2, 1, 0, T> xzyx, rbgr, spts;
			swizzle4 <0, 2, 1, 1, T> xzyy, rbgg, sptt;
			swizzle4 <0, 2, 1, 2, T> xzyz, rbgb, sptp;
			swizzle4 <0, 2, 2, 0, T> xzzx, rbbr, spps;
			swizzle4 <0, 2, 2, 1, T> xzzy, rbbg, sppt;
			swizzle4 <0, 2, 2, 2, T> xzzz, rbbb, sppp;
			swizzle4 <1, 0, 0, 0, T> yxxx, grrr, tsss;
			swizzle4 <1, 0, 0, 1, T> yxxy, grrg, tsst;
			swizzle4 <1, 0, 0, 2, T> yxxz, grrb, tssp;
			swizzle4 <1, 0, 1, 0, T> yxyx, grgr, tsts;
			swizzle4 <1, 0, 1, 1, T> yxyy, grgg, tstt;
			swizzle4 <1, 0, 1, 2, T> yxyz, grgb, tstp;
			swizzle4 <1, 0, 2, 0, T> yxzx, grbr, tsps;
			swizzle4 <1, 0, 2, 1, T> yxzy, grbg, tspt;
			swizzle4 <1, 0, 2, 2, T> yxzz, grbb, tspp;
			swizzle4 <1, 1, 0, 0, T> yyxx, ggrr, ttss;
			swizzle4 <1, 1, 0, 1, T> yyxy, ggrg, ttst;
			swizzle4 <1, 1, 0, 2, T> yyxz, ggrb, ttsp;
			swizzle4 <1, 1, 1, 0, T> yyyx, gggr, ttts;
			swizzle4 <1, 1, 1, 1, T> yyyy, gggg, tttt;
			swizzle4 <1, 1, 1, 2, T> yyyz, gggb, tttp;
			swizzle4 <1, 1, 2, 0, T> yyzx, ggbr, ttps;
			swizzle4 <1, 1, 2, 1, T> yyzy, ggbg, ttpt;
			swizzle4 <1, 1, 2, 2, T> yyzz, ggbb, ttpp;
			swizzle4 <1, 2, 0, 0, T> yzxx, gbrr, tpss;
			swizzle4 <1, 2, 0, 1, T> yzxy, gbrg, tpst;
			swizzle4 <1, 2, 0, 2, T> yzxz, gbrb, tpsp;
			swizzle4 <1, 2, 1, 0, T> yzyx, gbgr, tpts;
			swizzle4 <1, 2, 1, 1, T> yzyy, gbgg, tptt;
			swizzle4 <1, 2, 1, 2, T> yzyz, gbgb, tptp;
			swizzle4 <1, 2, 2, 0, T> yzzx, gbbr, tpps;
			swizzle4 <1, 2, 2, 1, T> yzzy, gbbg, tppt;
			swizzle4 <1, 2, 2, 2, T> yzzz, gbbb, tppp;
			swizzle4 <2, 0, 0, 0, T> zxxx, brrr, psss;
			swizzle4 <2, 0, 0, 1, T> zxxy, brrg, psst;
			swizzle4 <2, 0, 0, 2, T> zxxz, brrb, pssp;
			swizzle4 <2, 0, 1, 0, T> zxyx, brgr, psts;
			swizzle4 <2, 0, 1, 1, T> zxyy, brgg, pstt;
			swizzle4 <2, 0, 1, 2, T> zxyz, brgb, pstp;
			swizzle4 <2, 0, 2, 0, T> zxzx, brbr, psps;
			swizzle4 <2, 0, 2, 1, T> zxzy, brbg, pspt;
			swizzle4 <2, 0, 2, 2, T> zxzz, brbb, pspp;
			swizzle4 <2, 1, 0, 0, T> zyxx, bgrr, ptss;
			swizzle4 <2, 1, 0, 1, T> zyxy, bgrg, ptst;
			swizzle4 <2, 1, 0, 2, T> zyxz, bgrb, ptsp;
			swizzle4 <2, 1, 1, 0, T> zyyx, bggr, ptts;
			swizzle4 <2, 1, 1, 1, T> zyyy, bggg, pttt;
			swizzle4 <2, 1, 1, 2, T> zyyz, bggb, pttp;
			swizzle4 <2, 1, 2, 0, T> zyzx, bgbr, ptps;
			swizzle4 <2, 1, 2, 1, T> zyzy, bgbg, ptpt;
			swizzle4 <2, 1, 2, 2, T> zyzz, bgbb, ptpp;
			swizzle4 <2, 2, 0, 0, T> zzxx, bbrr, ppss;
			swizzle4 <2, 2, 0, 1, T> zzxy, bbrg, ppst;
			swizzle4 <2, 2, 0, 2, T> zzxz, bbrb, ppsp;
			swizzle4 <2, 2, 1, 0, T> zzyx, bbgr, ppts;
			swizzle4 <2, 2, 1, 1, T> zzyy, bbgg, pptt;
			swizzle4 <2, 2, 1, 2, T> zzyz, bbgb, pptp;
			swizzle4 <2, 2, 2, 0, T> zzzx, bbbr, ppps;
			swizzle4 <2, 2, 2, 1, T> zzzy, bbbg, pppt;
			swizzle4 <2, 2, 2, 2, T> zzzz, bbbb, pppp;
			#endif
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline vec()
			: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
		{}

		//! Initialize vec3 with three scalar values
		inline vec(const T &s0, const T &s1, const T &s2)
			: x(s0), y(s1), z(s2)
		{}

		//! Initialize vec3 with a vec2 and a scalar value
		inline vec(const vec<2, T> &v01, const T &s2)
			: x(v01.x), y(v01.y), z(s2)
		{}

		//! Initialize vec3 with a scalar value and a vec2
		inline vec(const T &s0, const vec<2, T> &v12)
			: x(s0), y(v12.x), z(v12.y)
		{}

		#ifndef GMTK_DISABLE_SWIZZLING
		//! Swizzle constructor
		template<int a, int b, int c>
		inline vec(const swizzle3 < a, b, c, T > &s)
			: x(s[a]), y(s[b]), z(s[c])
		{}
		#endif

		//! Copy constructor
		inline vec(const vec<3, T> &v)
			: x(v.x), y(v.y), z(v.z)
		{}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit inline vec(const vec<3, U> &v)
			: x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z))
		{}

		//! Fill constructor
		explicit inline vec(const T &s)
			: x(s), y(s), z(s)
		{}

		//! Array initializer
		explicit inline vec(const T *a)
			: x(a[0]), y(a[1]), z(a[2])
		{}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> l)
			: x(*(l.begin())), y(*(l.begin() + 1)), z(*(l.begin() + 2))
		{}

		//! Copy constructor for differently-sized vector
		template<int d2>
		inline vec(const vec<d2, T> &v)
		{
			if (d2 < 3)
			{
				GMTK_UNROLL_LOOP(i, d2, data[i] = v.data[i]);
			}
			else
			{
				GMTK_UNROLL_LOOP(i, 3, data[i] = v.data[i]);
			}
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		inline T &operator[](const int i)
		{
			return data[i];
		}

		//! Vector const index operator
		inline const T &operator[](const int i) const
		{
			return data[i];
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		inline vec<3, T> operator - () const
		{
			return vec<3, T>(-x, -y, -z);
		}
		//! Component-wise unary negation
		inline vec<3, T> operator ~ () const
		{
			return vec<3, T>(~x, ~y, ~z);
		}
		//! Vector assignment
		inline vec<3, T> &operator = (const vec<3, T> &v)
		{
			x = v.x; y = v.y; z = v.z; return *this;
		}

		//! Component-wise vector multiplication
		inline vec<3, T> operator * (const vec<3, T> &v) const
		{
			return vec<3, T>(x * v.x, y * v.y, z * v.z);
		}
		//! Component-wise vector division
		inline vec<3, T> operator / (const vec<3, T> &v) const
		{
			return vec<3, T>(x / v.x, y / v.y, z / v.z);
		}
		//! Component-wise vector addition
		inline vec<3, T> operator + (const vec<3, T> &v) const
		{
			return vec<3, T>(x + v.x, y + v.y, z + v.z);
		}
		//! Component-wise vector subtraction
		inline vec<3, T> operator - (const vec<3, T> &v) const
		{
			return vec<3, T>(x - v.x, y - v.y, z - v.z);
		}
		//! Component-wise vector OR
		inline vec<3, T> operator | (const vec<3, T> &v) const
		{
			return vec<3, T>(x | v.x, y | v.y, z | v.z);
		}
		//! Component-wise vector AND
		inline vec<3, T> operator & (const vec<3, T> &v) const
		{
			return vec<3, T>(x & v.x, y & v.y, z & v.z);
		}
		//! Component-wise vector XOR
		inline vec<3, T> operator ^ (const vec<3, T> &v) const
		{
			return vec<3, T>(x ^ v.x, y ^ v.y, z ^ v.z);
		}
		//! Component-wise vector modulus
		inline vec<3, T> operator % (const vec<3, T> &v) const
		{
			return vec<3, T>(x % v.x, y % v.y, z % v.z);
		}
		//! Component-wise vector shift left
		inline vec<3, T> operator << (const vec<3, T> &v) const
		{
			return vec<3, T>(x << v.x, y << v.y, z << v.z);
		}
		//! Component-wise vector shift right
		inline vec<3, T> operator >> (const vec<3, T> &v) const
		{
			return vec<3, T>(x >> v.x, y >> v.y, z >> v.z);
		}

		//! Component-wise scalar multiplication
		inline vec<3, T> operator * (const T &v) const
		{
			return vec<3, T>(x * v, y * v, z * v);
		}
		//! Component-wise scalar division
		inline vec<3, T> operator / (const T &v) const
		{
			return vec<3, T>(x / v, y / v, z / v);
		}
		//! Component-wise scalar addition
		inline vec<3, T> operator + (const T &v) const
		{
			return vec<3, T>(x + v, y + v, z + v);
		}
		//! Component-wise scalar subtraction
		inline vec<3, T> operator - (const T &v) const
		{
			return vec<3, T>(x - v, y - v, z - v);
		}
		//! Component-wise scalar OR
		inline vec<3, T> operator | (const T &v) const
		{
			return vec<3, T>(x | v, y | v, z | v);
		}
		//! Component-wise scalar AND
		inline vec<3, T> operator & (const T &v) const
		{
			return vec<3, T>(x & v, y & v, z & v);
		}
		//! Component-wise scalar XOR
		inline vec<3, T> operator ^ (const T &v) const
		{
			return vec<3, T>(x ^ v, y ^ v, z ^ v);
		}
		//! Component-wise scalar modulus
		inline vec<3, T> operator % (const T &v) const
		{
			return vec<3, T>(x % v, y % v, z % v);
		}
		//! Component-wise scalar shift left
		inline vec<3, T> operator << (const T &v) const
		{
			return vec<3, T>(x << v, y << v, z << v);
		}
		//! Component-wise scalar shift right
		inline vec<3, T> operator >> (const T &v) const
		{
			return vec<3, T>(x >> v, y >> v, z >> v);
		}

		//! Component-wise vector reference multiplication
		inline vec<3, T> &operator *= (const vec<3, T> &v)
		{
			x *= v.x; y *= v.y; z *= v.z; return *this;
		}
		//! Component-wise vector reference division
		inline vec<3, T> &operator /= (const vec<3, T> &v)
		{
			x /= v.x; y /= v.y; z /= v.z; return *this;
		}
		//! Component-wise vector reference addition
		inline vec<3, T> &operator += (const vec<3, T> &v)
		{
			x += v.x; y += v.y; z += v.z; return *this;
		}
		//! Component-wise vector reference subtraction
		inline vec<3, T> &operator -= (const vec<3, T> &v)
		{
			x -= v.x; y -= v.y; z -= v.z; return *this;
		}
		//! Component-wise vector reference OR
		inline vec<3, T> &operator |= (const vec<3, T> &v)
		{
			x |= v.x; y |= v.y; z |= v.z; return *this;
		}
		//! Component-wise vector reference AND
		inline vec<3, T> &operator &= (const vec<3, T> &v)
		{
			x &= v.x; y &= v.y; z &= v.z; return *this;
		}
		//! Component-wise vector reference XOR
		inline vec<3, T> &operator ^= (const vec<3, T> &v)
		{
			x ^= v.x; y ^= v.y; z ^= v.z; return *this;
		}
		//! Component-wise vector reference modulus
		inline vec<3, T> &operator %= (const vec<3, T> &v)
		{
			x %= v.x; y %= v.y; z %= v.z; return *this;
		}
		//! Component-wise vector reference shift left
		inline vec<3, T> &operator <<= (const vec<3, T> &v)
		{
			x <<= v.x; y <<= v.y; z <<= v.z; return *this;
		}
		//! Component-wise vector reference shift right
		inline vec<3, T> &operator >>= (const vec<3, T> &v)
		{
			x >>= v.x; y >>= v.y; z >>= v.z; return *this;
		}

		//! Component-wise scalar reference multiplication
		inline vec<3, T> &operator *= (const T &v)
		{
			x *= v; y *= v; z *= v; return *this;
		}
		//! Component-wise scalar reference division
		inline vec<3, T> &operator /= (const T &v)
		{
			x /= v; y /= v; z /= v; return *this;
		}
		//! Component-wise scalar reference addition
		inline vec<3, T> &operator += (const T &v)
		{
			x += v; y += v; z += v; return *this;
		}
		//! Component-wise scalar reference subtraction
		inline vec<3, T> &operator -= (const T &v)
		{
			x -= v; y -= v; z -= v; return *this;
		}
		//! Component-wise scalar reference OR
		inline vec<3, T> &operator |= (const T &v)
		{
			x |= v; y |= v; z |= v; return *this;
		}
		//! Component-wise scalar reference AND
		inline vec<3, T> &operator &= (const T &v)
		{
			x &= v; y &= v; z &= v; return *this;
		}
		//! Component-wise scalar reference XOR
		inline vec<3, T> &operator ^= (const T &v)
		{
			x ^= v; y ^= v; z ^= v; return *this;
		}
		//! Component-wise scalar reference modulus
		inline vec<3, T> &operator %= (const T &v)
		{
			x %= v; y %= v; z %= v; return *this;
		}
		//! Component-wise scalar reference shift left
		inline vec<3, T> &operator <<= (const T &v)
		{
			x <<= v; y <<= v; z <<= v; return *this;
		}
		//! Component-wise scalar reference shift right
		inline vec<3, T> &operator >>= (const T &v)
		{
			x >>= v; y >>= v; z >>= v; return *this;
		}

		//! Component-wise equality comparison
		inline bool operator == (const vec<3, T> &v) const
		{
			return x == v.x && y == v.y && z == v.z;
		}
		//! Component-wise inequality comparison
		inline bool operator != (const vec<3, T> &v) const
		{
			return x != v.x && y != v.y && z != v.z;
		}
		//! Component-wise less-than comparison
		inline bool operator < (const vec<3, T> &v) const
		{
			return x < v.x &&y < v.y &&z < v.z;
		}
		//! Component-wise greater-than comparison
		inline bool operator > (const vec<3, T> &v) const
		{
			return x > v.x && y > v.y && z > v.z;
		}
		//! Component-wise less-than-equals comparison
		inline bool operator <= (const vec<3, T> &v) const
		{
			return x <= v.x && y <= v.y && z <= v.z;
		}
		//! Component-wise greater-than-equals comparison
		inline bool operator >= (const vec<3, T> &v) const
		{
			return x >= v.x && y >= v.y && z >= v.z;
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! NaN vector (NaN, NaN, NaN)
		static inline constexpr vec<3, T> nan()
		{
			return vec<3, T>(NAN, NAN, NAN);
		}

		//! Infinity vector (inf, inf, inf)
		static inline constexpr vec<3, T> inf()
		{
			return vec<3, T>(INFINITY, INFINITY, INFINITY);
		}

		//! Zero vector (0,0,0)
		static inline constexpr vec<3, T> zero()
		{
			return vec<3, T>(0, 0, 0);
		}

		//! One vector (1,1,1)
		static inline constexpr vec<3, T> one()
		{
			return vec<3, T>(1, 1, 1);
		}

		//! Up vector (0,1,0)
		static inline constexpr vec<3, T> up()
		{
			return vec<3, T>(0, 1, 0);
		}

		//! Down vector (0,-1,0)
		static inline constexpr vec<3, T> down()
		{
			return vec<3, T>(0, -1, 0);
		}

		//! Right vector (1,0,0)
		static inline constexpr vec<3, T> right()
		{
			return vec<3, T>(1, 0, 0);
		}

		//! Left vector (-1,0,0)
		static inline constexpr vec<3, T> left()
		{
			return vec<3, T>(-1, 0, 0);
		}

		//! Forward vector (0,0,1)
		static inline constexpr vec<3, T> forward()
		{
			return vec<3, T>(0, 0, 1);
		}

		//! Back vector (0,0,-1)
		static inline constexpr vec<3, T> back()
		{
			return vec<3, T>(0, 0, -1);
		}

	}; //! struct vec3

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef vec<3, float>			vec3, vec3f;
	typedef vec<3, double>			vec3d;
	typedef vec<3, unsigned char>	vec3uc;
	typedef vec<3, char>			vec3c;
	typedef vec<3, unsigned short>	vec3us;
	typedef vec<3, short>			vec3s;
	typedef vec<3, unsigned int>	vec3ui;
	typedef vec<3, int>				vec3i;
	typedef vec<3, unsigned long>	vec3ul;
	typedef vec<3, long>			vec3l;

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <typename T = float>
	inline std::ostream &operator<<(std::ostream &os, const vec<3, T> &v)
	{
		os << "| " << v.x << ' ' << v.y << ' ' << v.z << " |";
		return os;
	}

	//! Scalar-Vector multiplication
	template <typename T = float>
	inline vec<3, T> operator*(const T &l, const vec<3, T> &r)
	{
		return vec<3, T>(l * r.x, l * r.y, l & r.z);
	}


	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Calculates the dot or scalar product of two vectors
	template < typename T = float>
	inline T dot(const vec<3, T> &l, const vec<3, T> &r)
	{
		return (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	//! Returns length squared of vector
	template <typename T = float>
	inline T lengthsq(const vec<3, T> &v)
	{
		return sq(v.x) + sq(v.y) + sq(v.z);
	}

	//! Returns length of vector, or sqrt(lengthsq)
	template <typename T = float>
	inline T length(const vec<3, T> &v)
	{
		return sqrt(sq(v.x) + sq(v.y) + sq(v.z));
	}

	//! Returns a component-wise minimum of two vectors
	template < typename T = float>
	inline vec<3, T> min(const vec<3, T> &l, const vec<3, T> &r)
	{
		return vec<3, T>(min(l.x, r.x), min(l.y, r.y), min(l.z, r.z));
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template < typename T = float>
	inline vec<3, T> min(const vec<3, T> &l, const T &r)
	{
		return vec<3, T>(min(l.x, r), min(l.y, r), min(l.z, r));
	}

	//! Returns a component-wise minimum of two vectors
	template <typename T = float>
	inline vec<3, T> max(const vec<3, T> &l, const vec<3, T> &r)
	{
		return vec<3, T>(max(l.x, r.x), max(l.y, r.y), max(l.z, r.z));
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template <typename T = float>
	inline vec<3, T> max(const vec<3, T> &l, const T &r)
	{
		return vec<3, T>(max(l.x, r), max(l.y, r), max(l.z, r));
	}

	//! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
	template<typename T = float>
	inline vec<4, T> affine(const vec<3, T> &v)
	{
		return vec<4, T>(v.x, v.y, v.z, static_cast<T>(1));
	}

	//! Returns whether vector is NaN
	template<typename T = float>
	inline bool isnan(const vec<3, T> &v)
	{
		return std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z);
	}

	//! Returns whether vector is inf
	template<typename T = float>
	inline bool isinf(const vec<3, T> &v)
	{
		return std::isinf(v.x) || std::isinf(v.y) || std::isinf(v.z);
	}

	//! Relative equality (for floating-point vectors)
	template<typename T = float>
	inline bool req(const vec<3, T> &l, const vec<3, T> &r, T rng = 1e-8)
	{
		return req(l.x, r.x, rng) && req(l.y, r.y, rng) && req(l.z, r.z, rng);
	}

}////

//

#undef GMTK_SWZ3_BOP
#undef GMTK_SWZ3_BROP

//

#pragma warning(pop)

//

#endif