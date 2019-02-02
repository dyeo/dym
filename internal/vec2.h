#ifndef _GMTK_VEC2_H_
#define _GMTK_VEC2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"
#include "swizzle2.h"
#include "swizzle3.h"

//

#define GMTK_VEC2_LOOP(oper) GMTK_UNROLL_LOOP(i,2,oper)

//

#define GMTK_VEC2_UN_OP(op) \
	inline vec<2, T> operator op () const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = op data[i]); return res; }

#define GMTK_VEC2_VEC_OP(op) \
	inline vec<2, T> operator op (const vec<2, T> &v) const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = data[i] op v.data[i]); return res; }

#define GMTK_VEC2_SCL_OP(op) \
	inline vec<2, T> operator op (const T& v) const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = data[i] op v); return res; } 

#define GMTK_VEC2_VEC_ROP(op) \
	inline vec<2, T>& operator op (const vec<2, T> &v) \
	{ GMTK_VEC2_LOOP(data[i] op v.data[i]); return *this; }

#define GMTK_VEC2_SCL_ROP(op) \
	inline vec<2, T>& operator op (const T &v) \
	{ GMTK_VEC2_LOOP(data[i] op v); return *this; }

#define GMTK_VEC2_SWZ_BOP(op) \
	template<int a, int b, typename T> \
	static inline vec<2, T> operator op (const vec<2, T> &v, const swizzle2<a, b, vec<2, T>, T> &s) \
	{ vec<2, T> res; res.data[0] = data[0] op s[a]; res.data[1] = data[1] op s[b]; return res; } \
	template<int a, int b, typename T> \
	static inline vec<2, T> operator op (const swizzle2<a, b, vec<2, T>, T> &s, const vec<2, T> &v) \
	{ vec<2, T> res; res.data[0] = s[a] op data[0]; res.data[1] = s[b] op data[1]; return res; } \
	template<int a1, int b1, int a2, int b2, typename T> \
	static inline vec<2, T> operator op (const swizzle2<a1, b1, vec<2, T>, T> &s, const swizzle2<a2, b2, vec<2, T>, T> &t) \
	{ vec<2, T> res; res.data[0] = s[a1] op t[a2]; res.data[1] = s[b1] op t[b2]; return res; }

#define GMTK_VEC2_SWZ_BROP(op) \
	template<int a, int b, typename T> \
	static inline vec<2, T>& operator op (vec<2, T> &v, const swizzle2<a, b, vec<2, T>, T> &s) \
	{ v.data[0] op s[a]; v.data[1] op s[b]; return v; } \
	template<int a, int b, typename T> \
	static inline swizzle2<a, b, vec<2, T>, T>& operator op (swizzle2<a, b, vec<2, T>, T> &s, const vec<2, T> &v) \
	{ s[a] op v.data[0]; s[b] op v.data[1]; return s; } \
	template<int a1, int b1, int a2, int b2, typename T> \
	static inline swizzle2<a1, b1, vec<2, T>, T>& operator op (swizzle2<a1, b1, vec<2, T>, T> &s, const swizzle2<a2, b2, vec<2, T>, T> &t) \
	{ s[a1] op t[a2]; s[b1] op t[b2]; return s; }
//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <2, T>
	{
		////////////
		//! TYPES //
		////////////

		template<int a, int b> using swz2 = swizzle2<a, b, vec<2, T>, T>;
		template<int a, int b, int c> using swz3 = swizzle3<a, b, c, vec<3, T>, T>;

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[2]; };
			struct { T x, y; };
			swz2 <0, 0>	   xx;
			swz2 <0, 1>	   xy;
			swz2 <1, 0>	   yx;
			swz2 <1, 1>	   yy;
			swz3 <0, 0, 0> xxx;
			swz3 <0, 0, 1> xxy;
			swz3 <0, 1, 0> xyx;
			swz3 <0, 1, 1> xyy;
			swz3 <1, 0, 0> yxx;
			swz3 <1, 0, 1> yxy;
			swz3 <1, 1, 0> yyx;
			swz3 <1, 1, 1> yyy;
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec2 with two values
		inline vec(const T& s0, const T& s1)
		{
			data[0] = s0;
			data[1] = s1;
		}

		//! Default constructor
		inline vec() {
			GMTK_VEC2_LOOP(data[i] = static_cast<T>(0));
		}

		//! Swizzle constructor
		template<int a, int b>
		inline vec(const swz2<a, b>&s) {
			data[0] = s[a];
			data[1] = s[b];
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC2_LOOP(data[i] = *(list.begin() + i));
		}

		//! Copy constructor
		inline vec(const vec<2, T>& v) {
			GMTK_VEC2_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 2);
			GMTK_VEC2_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<2, U>& v) {
			GMTK_VEC2_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC2_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC2_LOOP(data[i] = a[i]);
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
		//! ARITHMETIC OPERATORS //
		///////////////////////////

		//! Swizzle assignment
		template<int a, int b>
		vec<2, T>& operator=(const swz2<a, b> &s) {
			*this = vec<2, T>(s[a], s[b]);
			return *this;
		}

		//! Component-wise unary negation
		GMTK_VEC2_UN_OP(-)

		//! Vector assignment
		GMTK_VEC2_VEC_ROP(=)

		//! Component-wise vector multiplication
		GMTK_VEC2_VEC_OP(*)

		//! Component-wise vector division
		GMTK_VEC2_VEC_OP(/)

		//! Component-wise vector addition
		GMTK_VEC2_VEC_OP(+)

		//! Component-wise vector subtraction
		GMTK_VEC2_VEC_OP(-)

		//! Component-wise scalar multiplication
		GMTK_VEC2_SCL_OP(*)

		//! Component-wise scalar division
		GMTK_VEC2_SCL_OP(/)

		//! Component-wise scalar addition
		GMTK_VEC2_SCL_OP(+)

		//! Component-wise scalar subtraction
		GMTK_VEC2_SCL_OP(-)

		//! Component-wise scalar reference multiplication
		GMTK_VEC2_SCL_ROP(*=)
			
		//! Component-wise vector reference multiplication
		GMTK_VEC2_VEC_ROP(*=)

		//! Component-wise vector reference division
		GMTK_VEC2_VEC_ROP(/=)

		//! Component-wise vector reference addition
		GMTK_VEC2_VEC_ROP(+=)

		//! Component-wise vector reference subtraction
		GMTK_VEC2_VEC_ROP(-=)

		//! Component-wise scalar reference division
		GMTK_VEC2_SCL_ROP(/=)

		//! Component-wise scalar reference addition
		GMTK_VEC2_SCL_ROP(+=)

		//! Component-wise scalar reference subtraction
		GMTK_VEC2_SCL_ROP(-=)

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////
		
		//! Zero vector (0,0)
		static inline constexpr vec<2, T> zero() { return vec<2, T>(0, 0); }
		
		//! One vector (1,1)
		static inline constexpr vec<2, T> one() { return vec<2, T>(1, 1); }

		//! Up vector (0,1)
		static inline constexpr vec<2, T> up() { return vec<2, T>(0, 1); }

		//! Down vector (0,-1)
		static inline constexpr vec<2, T> down() { return vec<2, T>(0, -1); }

		//! Right vector (1,0)
		static inline constexpr vec<2, T> right() { return vec<2, T>(1, 0); }

		//! Left vector (-1,0)
		static inline constexpr vec<2, T> left() { return vec<2, T>(-1, 0); }

	}; //! struct vec2

	//////////////////////////
	//! SWIZZLING OPERATORS //
	//////////////////////////
	
	GMTK_VEC2_SWZ_BOP(*)
	GMTK_VEC2_SWZ_BOP(/)
	GMTK_VEC2_SWZ_BOP(+)
	GMTK_VEC2_SWZ_BOP(-)

	GMTK_VEC2_SWZ_BROP(*=)
	GMTK_VEC2_SWZ_BROP(/=)
	GMTK_VEC2_SWZ_BROP(+=)
	GMTK_VEC2_SWZ_BROP(-=)

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

}////

//

#undef GMTK_VEC2_LOOP
#undef GMTK_VEC2_OPERATOR
#undef GMTK_VEC2_UN_OP
#undef GMTK_VEC2_VEC_OP
#undef GMTK_VEC2_SCL_OP
#undef GMTK_VEC2_VEC_ROP
#undef GMTK_VEC2_SCL_ROP

#undef GMTK_VEC2_SWZ_BOP
#undef GMTK_VEC2_SWZ_BROP

//

#pragma warning(pop)

//

#endif