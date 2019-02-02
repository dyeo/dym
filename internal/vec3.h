#ifndef _GMTK_VEC3_H_
#define _GMTK_VEC3_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"

//

#define GMTK_VEC3_LOOP(oper) GMTK_UNROLL_LOOP(i,3,oper)

//

#define GMTK_VEC3_UN_OP(op) \
	inline vec<3, T> operator op () const \
	{ vec<3, T> res; GMTK_VEC3_LOOP(res.data[i] = op data[i]); return res; }

#define GMTK_VEC3_VEC_OP(op) \
	inline vec<3, T> operator op (const vec<3, T>& v) const \
	{ vec<3, T> res; GMTK_VEC3_LOOP(res.data[i] = data[i] op v.data[i]); return res; }

#define GMTK_VEC3_SCL_OP(op) \
	inline vec<3, T> operator op (const T& v) const \
	{ vec<3, T> res; GMTK_VEC3_LOOP(res.data[i] = data[i] op v); return res; }

#define GMTK_VEC3_VEC_ROP(op) \
	inline vec<3, T>& operator op (const vec<3, T>& v) \
	{ GMTK_VEC3_LOOP(data[i] op v.data[i]); return *this; }

#define GMTK_VEC3_SCL_ROP(op) \
	inline vec<3, T>& operator op (const T& v) \
	{ GMTK_VEC3_LOOP(data[i] op v); return *this; }

#define GMTK_VEC3_SWZ_BOP(op) \
	template<int a, int b, int c, typename T> \
	static inline vec<3, T> operator op (const vec<3, T> &v, const swizzle3<a, b, c, vec<3, T>, T> &s) \
	{ vec<3, T> res; res.data[0] = data[0] op s[a]; res.data[1] = data[1] op s[b]; res.data[2] = data[2] op s[c]; return res; } \
	template<int a, int b, int c, typename T> \
	static inline vec<3, T> operator op (const swizzle3<a, b, c, vec<3, T>, T> &s, const vec<3, T> &v) \
	{ vec<3, T> res; res.data[0] = s[a] op data[0]; res.data[1] = s[b] op data[1]; res.data[2] = s[c] op data[2]; return res; } \
	template<int a1, int b1, int c1, int a2, int b2, int c2, typename T> \
	static inline vec<3, T> operator op (const swizzle3<a1, b1, c1, vec<3, T>, T> &s, const swizzle3<a2, b2, c2, vec<3, T>, T> &t) \
	{ vec<3, T> res; res.data[0] = s[a1] op t[a2]; res.data[1] = s[b1] op t[b2]; res.data[2] = s[c1] op t[c2]; return res; }

#define GMTK_VEC3_SWZ_BROP(op) \
	template<int a, int b, int c, typename T> \
	static inline vec<3, T>& operator op (vec<3, T> &v, const swizzle3<a, b, c, vec<3, T>, T> &s) \
	{ v.data[0] op s[a]; v.data[1] op s[b]; v.data[2] op s[c]; return v; } \
	template<int a, int b, int c, typename T> \
	static inline swizzle3<a, b, c, vec<3, T>, T>& operator op (swizzle3<a, b, c, vec<3, T>, T> &s, const vec<3, T> &v) \
	{ s[a] op v.data[0]; s[b] op v.data[1]; s[c] op v.data[2]; return s; } \
	template<int a1, int b1, int c1, int a2, int b2, int c2, typename T> \
	static inline swizzle3<a1, b1, c1, vec<3, T>, T>& operator op (swizzle3<a1, b1, c1, vec<3, T>, T> &s, const swizzle3<a2, b2, c2, vec<3, T>, T> &t) \
	{ s[a1] op t[a2]; s[b1] op t[b2]; s[c1] op t[c2]; return s; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <3, T>
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
			struct { T data[3]; };
			struct { T x, y, z; };
			#pragma region swizzle
			swz2 <0, 0>	   xx;
			swz2 <0, 1>	   xy;
			swz2 <0, 2>	   xz;
			swz2 <1, 0>	   yx;
			swz2 <1, 1>	   yy;
			swz2 <1, 2>	   yz;
			swz2 <2, 0>	   zx;
			swz2 <2, 1>	   zy;
			swz2 <2, 2>	   zz;
			swz3 <0, 0, 0> xxx;
			swz3 <0, 0, 1> xxy;
			swz3 <0, 0, 2> xxz;
			swz3 <0, 1, 0> xyx;
			swz3 <0, 1, 1> xyy;
			swz3 <0, 1, 2> xyz;
			swz3 <0, 2, 0> xzx;
			swz3 <0, 2, 1> xzy;
			swz3 <0, 2, 2> xzz;
			swz3 <1, 0, 0> yxx;
			swz3 <1, 0, 1> yxy;
			swz3 <1, 0, 2> yxz;
			swz3 <1, 1, 0> yyx;
			swz3 <1, 1, 1> yyy;
			swz3 <1, 1, 2> yyz;
			swz3 <1, 2, 0> yzx;
			swz3 <1, 2, 1> yzy;
			swz3 <1, 2, 2> yzz;
			swz3 <2, 0, 0> zxx;
			swz3 <2, 0, 1> zxy;
			swz3 <2, 0, 2> zxz;
			swz3 <2, 1, 0> zyx;
			swz3 <2, 1, 1> zyy;
			swz3 <2, 1, 2> zyz;
			swz3 <2, 2, 0> zzx;
			swz3 <2, 2, 1> zzy;
			swz3 <2, 2, 2> zzz;
			#pragma region swizzle
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec3 with three values
		inline vec(const T& s0, const T& s1, const T& s2)
		{
			data[0] = s0;
			data[1] = s1;
			data[2] = s2;
		}

		//! Initialize vec3 with a vec2 and a third value
		inline vec(const vec<2, T>& v01, const T& s2)
		{
			data[0] = v01.data[0];
			data[1] = v01.data[1];
			data[2] = s2;
		}

		//! Default constructor
		inline vec() {
			GMTK_VEC3_LOOP(data[i] = static_cast<T>(0));
		}

		//! Swizzle constructor
		template<int a, int b>
		inline vec(const swz2<a, b>&s) {
			data[0] = s[a];
			data[1] = s[b];
			data[2] = static_cast<T>(1);
		}

		//! Swizzle constructor
		template<int a, int b, int c>
		inline vec(const swz3<a, b, c>&s) {
			data[0] = s[a];
			data[1] = s[b];
			data[2] = s[c];
		}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> list)
		{
			GMTK_VEC3_LOOP(data[i] = *(list.begin() + i));
		}
		
		//! Copy constructor
		inline vec(const vec<3, T>& v) {
			GMTK_VEC3_LOOP(data[i] = v.data[i]);
		}

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 3);
			GMTK_VEC3_LOOP(data[i] = v.data[i]);
		}

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<3, U>& v) {
			GMTK_VEC3_LOOP(data[i] = static_cast<T>(v[i]));
		}

		//! Fill constructor
		explicit inline vec(const T& s) {
			GMTK_VEC3_LOOP(data[i] = s);
		}

		//! Array initializer
		explicit inline vec(const T* a) {
			GMTK_VEC3_LOOP(data[i] = a[i]);
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
		GMTK_VEC3_UN_OP(-)

		//! Vector assignment
		GMTK_VEC3_VEC_ROP(=)
		
		//! Component-wise vector multiplication
		GMTK_VEC3_VEC_OP(*)
		
		//! Component-wise vector division
		GMTK_VEC3_VEC_OP(/)
		
		//! Component-wise vector addition
		GMTK_VEC3_VEC_OP(+)
		
		//! Component-wise vector subtraction
		GMTK_VEC3_VEC_OP(-)
		
		//! Component-wise scalar multiplication
		GMTK_VEC3_SCL_OP(*)
		
		//! Component-wise scalar division
		GMTK_VEC3_SCL_OP(/)
		
		//! Component-wise scalar addition
		GMTK_VEC3_SCL_OP(+)
		
		//! Component-wise scalar subtraction
		GMTK_VEC3_SCL_OP(-)
		
		//! Component-wise scalar reference multiplication
		GMTK_VEC3_SCL_ROP(*=)
			
		//! Component-wise vector reference multiplication
		GMTK_VEC3_VEC_ROP(*=)
		
		//! Component-wise vector reference division
		GMTK_VEC3_VEC_ROP(/=)
		
		//! Component-wise vector reference addition
		GMTK_VEC3_VEC_ROP(+=)
		
		//! Component-wise vector reference subtraction
		GMTK_VEC3_VEC_ROP(-=)
		
		//! Component-wise scalar reference division
		GMTK_VEC3_SCL_ROP(/=)
		
		//! Component-wise scalar reference addition
		GMTK_VEC3_SCL_ROP(+=)
		
		//! Component-wise scalar reference subtraction
		GMTK_VEC3_SCL_ROP(-=)

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Zero vector (0,0,0)
		static inline constexpr vec<3, T> zero() { return vec<3, T>(0, 0, 0); }

		//! One vector (1,1,1)
		static inline constexpr vec<3, T> one() { return vec<3, T>(1, 1, 1); }

		//! Up vector (0,1,0)
		static inline constexpr vec<3, T> up() { return vec<3, T>(0, 1, 0); }

		//! Down vector (0,-1,0)
		static inline constexpr vec<3, T> down() { return vec<3, T>(0, -1, 0); }

		//! Right vector (1,0,0)
		static inline constexpr vec<3, T> right() { return vec<3, T>(1, 0, 0); }

		//! Left vector (-1,0,0)
		static inline constexpr vec<3, T> left() { return vec<3, T>(-1, 0, 0); }

		//! Forward vector (0,0,1)
		static inline constexpr vec<3, T> forward() { return vec<3, T>(0, 0, 1); }

		//! Back vector (0,0,-1)
		static inline constexpr vec<3, T> back() { return vec<3, T>(0, 0, -1); }

	}; //! struct vec3
	
	//////////////////////////
	//! SWIZZLING OPERATORS //
	//////////////////////////
	
	GMTK_VEC3_SWZ_BOP(*)
	GMTK_VEC3_SWZ_BOP(/)
	GMTK_VEC3_SWZ_BOP(+)
	GMTK_VEC3_SWZ_BOP(-)

	GMTK_VEC3_SWZ_BROP(*=)
	GMTK_VEC3_SWZ_BROP(/=)
	GMTK_VEC3_SWZ_BROP(+=)
	GMTK_VEC3_SWZ_BROP(-=)

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

}////

//

#undef GMTK_VEC3_LOOP
#undef GMTK_VEC3_OPERATOR
#undef GMTK_VEC3_UN_OP
#undef GMTK_VEC3_VEC_OP
#undef GMTK_VEC3_SCL_OP
#undef GMTK_VEC3_VEC_ROP
#undef GMTK_VEC3_SCL_ROP

#undef GMTK_VEC3_SWZ_BOP
#undef GMTK_VEC3_SWZ_BROP

//

#pragma warning(pop)

//

#endif