#ifndef _GMTK_VEC4_H_
#define _GMTK_VEC4_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"

//

#define GMTK_VEC4_LOOP(oper) GMTK_UNROLL_LOOP(i,4,oper)

//

#define GMTK_VEC4_UN_OP(op) \
	inline vec<4, T> operator op () const \
	{ vec<4, T> res; GMTK_VEC4_LOOP(res.data[i] = op data[i]); return res; }

#define GMTK_VEC4_VEC_OP(op) \
	inline vec<4, T> operator op (const vec<4, T>& v) const \
	{ vec<4, T> res; GMTK_VEC4_LOOP(res.data[i] = data[i] op v.data[i]); return res; }

#define GMTK_VEC4_SCL_OP(op) \
	inline vec<4, T> operator op (const T& v) const \
	{ vec<4, T> res; GMTK_VEC4_LOOP(res.data[i] = data[i] op v); return res; }

#define GMTK_VEC4_VEC_ROP(op) \
	inline vec<4, T>& operator op (const vec<4, T>& v) \
	{ GMTK_VEC4_LOOP(data[i] op v.data[i]); return *this; }

#define GMTK_VEC4_SCL_ROP(op) \
	inline vec<4, T>& operator op (const T& v) \
	{ GMTK_VEC4_LOOP(data[i] op v); return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <4, T>
	{
		////////////
		//! TYPES //
		////////////
		
		GMTK_SWZ2_TYPE
		GMTK_SWZ3_TYPE
		GMTK_SWZ4_TYPE

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[4]; };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			GMTK_VEC4_SWIZZLES
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec4 with four values
		inline vec(const T& s0, const T& s1, const T& s2, const T& s3)
		{
			data[0] = s0;
			data[1] = s1;
			data[2] = s2;
			data[3] = s3;
		}

		//! Initialize vec4 with a vec3 and a fourth value
		inline vec(const vec<3, T>& v012, const T& s3)
		{
			data[0] = v012.data[0];
			data[1] = v012.data[1];
			data[2] = v012.data[2];
			data[3] = s3;
		}

		//! Initialize vec4 with two vec2s
		inline vec(const vec<2, T>& v01, const vec<2, T>& v23)
		{
			data[0] = v01.data[0];
			data[1] = v01.data[1];
			data[2] = v23.data[0];
			data[2] = v23.data[1];
		}

		//! Default constructor
		inline vec() {
			GMTK_VEC4_LOOP(data[i] = static_cast<T>(0));
		}

		//! Swizzle4 constructor
		template<int a, int b, int c, int d>
		inline vec(const swz4<a, b, c, d>&s) {
			data[0] = s[a];
			data[1] = s[b];
			data[2] = s[c];
			data[3] = s[d];
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC4_LOOP(data[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline vec(const vec<4, T>& v) {
			GMTK_VEC4_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 4);
			GMTK_VEC4_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<4, U>& v) {
			GMTK_VEC4_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC4_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC4_LOOP(data[i] = a[i]);
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		inline T& operator[](const int i) {
			return data[i];
		}

		//! Vector const index operator
		inline const T& operator[](const int i) const {
			return data[i];
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		GMTK_VEC4_UN_OP(-)

		//! Component-wise vector multiplication
		GMTK_VEC4_VEC_OP(*)

		//! Component-wise vector division
		GMTK_VEC4_VEC_OP(/ )

		//! Component-wise vector addition
		GMTK_VEC4_VEC_OP(+)

		//! Component-wise vector subtraction
		GMTK_VEC4_VEC_OP(-)

		//! Component-wise scalar multiplication
		GMTK_VEC4_SCL_OP(*)

		//! Component-wise scalar division
		GMTK_VEC4_SCL_OP(/)

		//! Component-wise scalar addition
		GMTK_VEC4_SCL_OP(+)

		//! Component-wise scalar subtraction
		GMTK_VEC4_SCL_OP(-)

		//! Component-wise scalar reference multiplication
		GMTK_VEC4_SCL_ROP(*=)

		//! Component-wise vector reference multiplication
		GMTK_VEC4_VEC_ROP(*=)

		//! Component-wise vector reference division
		GMTK_VEC4_VEC_ROP(/=)

		//! Component-wise vector reference addition
		GMTK_VEC4_VEC_ROP(+=)

		//! Component-wise vector reference subtraction
		GMTK_VEC4_VEC_ROP(-=)

		//! Component-wise scalar reference division
		GMTK_VEC4_SCL_ROP(/=)

		//! Component-wise scalar reference addition
		GMTK_VEC4_SCL_ROP(+=)

		//! Component-wise scalar reference subtraction
		GMTK_VEC4_SCL_ROP(-=)

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Zero vector (0,0,0,0)
		static inline constexpr vec<4, T> zero() { return vec<4, T>(0, 0, 0, 0); }

		//! One vector (1,1,1,1)
		static inline constexpr vec<4, T> one() { return vec<4, T>(1, 1, 1, 1); }

		//! Up vector (0,1,0,0)
		static inline constexpr vec<4, T> up() { return vec<4, T>(0, 1, 0, 0); }

		//! Down vector (0,-1,0,0)
		static inline constexpr vec<4, T> down() { return vec<4, T>(0, -1, 0, 0); }

		//! Right vector (1,0,0,0)
		static inline constexpr vec<4, T> right() { return vec<4, T>(1, 0, 0, 0); }

		//! Left vector (-1,0,0,0)
		static inline constexpr vec<4, T> left() { return vec<4, T>(-1, 0, 0, 0); }

		//! Forward vector (0,0,1,0)
		static inline constexpr vec<4, T> forward() { return vec<4, T>(0, 0, 1, 0); }

		//! Back vector (0,0,-1,0)
		static inline constexpr vec<4, T> back() { return vec<4, T>(0, 0, -1, 0); }

	}; //! struct vec4

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////
	
	typedef vec<4, float>			vec4, vec4f;
	typedef vec<4, double>			vec4d;
	typedef vec<4, unsigned char>	vec4uc;
	typedef vec<4, char>			vec4c;
	typedef vec<4, unsigned short>	vec4us;
	typedef vec<4, short>			vec4s;
	typedef vec<4, unsigned int>	vec4ui;
	typedef vec<4, int>				vec4i;
	typedef vec<4, unsigned long>	vec4ul;
	typedef vec<4, long>			vec4l;

}////

//

#undef GMTK_VEC4_LOOP
#undef GMTK_VEC4_OPERATOR
#undef GMTK_VEC4_UN_OP
#undef GMTK_VEC4_VEC_OP
#undef GMTK_VEC4_SCL_OP
#undef GMTK_VEC4_VEC_ROP
#undef GMTK_VEC4_SCL_ROP

#undef GMTK_SWZ4_BOP
#undef GMTK_SWZ4_BROP

//

#pragma warning(pop)

//

#endif