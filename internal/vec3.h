#ifndef _GMTK_VEC3_H_
#define _GMTK_VEC3_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"

//

#define GMTK_VEC3_LOOP(oper) GMTK_STATIC_LOOP(i,3,oper)

//

#define GMTK_VEC3_INIT(a, b, c) : x( a ), y( b ), z( c ) { }

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

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <3, T>
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
			struct { T data[3]; };
			struct { T x, y, z; };
			struct { T r, g, b; };
			GMTK_VEC3_SWIZZLES
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec3 with three values
		inline vec(const T& s0, const T& s1, const T& s2)
			GMTK_VEC3_INIT(s0, s1, s2)

		//! Initialize vec3 with a vec2 and a third value
		inline vec(const vec<2, T>& v01, const T& s2)
			GMTK_VEC3_INIT(v0.x, v0.y, s2)

		//! Default constructor
		inline vec() 
			GMTK_VEC3_INIT(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0))

		//! Swizzle constructor
		template<int a, int b, int c>
		inline vec(const swz3<a, b, c>&s) 
			GMTK_VEC3_INIT(s[a], s[b], s[c])
		
		//! Copy constructor
		inline vec(const vec<3, T>& v) 
			GMTK_VEC3_INIT(v.x, v.y, v.z)

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<3, U>& v)
			GMTK_VEC3_INIT(static_cast<T>(v.x), static_cast<T>(v.y), static_cast<T>(v.z))

		//! Fill constructor
		explicit inline vec(const T& s)
			GMTK_VEC3_INIT(s, s, s)

		//! Array initializer
		explicit inline vec(const T* a)
			GMTK_VEC3_INIT(a[0], a[1], a[2])

		//! Initializer list constructor
		inline vec(std::initializer_list<T> l)
			GMTK_VEC3_INIT(*(l.begin()), *(l.begin() + 1), *(l.begin() + 2))

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 3);
			GMTK_VEC3_LOOP(data[i] = v.data[i]);
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
		//! Component-wise unary negation
		GMTK_VEC3_UN_OP(~)
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
		//! Component-wise vector OR
		GMTK_VEC3_VEC_OP(|)
		//! Component-wise vector AND
		GMTK_VEC3_VEC_OP(&)
		//! Component-wise vector XOR
		GMTK_VEC3_VEC_OP(^)
		//! Component-wise vector modulus
		GMTK_VEC3_VEC_OP(%)
		//! Component-wise vector shift left
		GMTK_VEC3_VEC_OP(<<)
		//! Component-wise vector shift right
		GMTK_VEC3_VEC_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_VEC3_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_VEC3_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_VEC3_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_VEC3_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_VEC3_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_VEC3_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_VEC3_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_VEC3_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_VEC3_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_VEC3_SCL_OP(>>)
						
		//! Component-wise vector reference multiplication
		GMTK_VEC3_VEC_ROP(*=)		
		//! Component-wise vector reference division
		GMTK_VEC3_VEC_ROP(/=)		
		//! Component-wise vector reference addition
		GMTK_VEC3_VEC_ROP(+=)		
		//! Component-wise vector reference subtraction
		GMTK_VEC3_VEC_ROP(-=)
		//! Component-wise vector reference OR
		GMTK_VEC3_VEC_ROP(|=)
		//! Component-wise vector reference AND
		GMTK_VEC3_VEC_ROP(&=)
		//! Component-wise vector reference XOR
		GMTK_VEC3_VEC_ROP(^=)
		//! Component-wise vector reference modulus
		GMTK_VEC3_VEC_ROP(%=)
		//! Component-wise vector reference shift left
		GMTK_VEC3_VEC_ROP(<<=)
		//! Component-wise vector reference shift right
		GMTK_VEC3_VEC_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_VEC3_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_VEC3_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_VEC3_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_VEC3_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_VEC3_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_VEC3_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_VEC3_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_VEC3_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_VEC3_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_VEC3_SCL_ROP(>>=)

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

#undef GMTK_VEC3_INIT
#undef GMTK_VEC3_UN_OP
#undef GMTK_VEC3_VEC_OP
#undef GMTK_VEC3_SCL_OP
#undef GMTK_VEC3_VEC_ROP
#undef GMTK_VEC3_SCL_ROP

#undef GMTK_SWZ3_BOP
#undef GMTK_SWZ3_BROP

//

#pragma warning(pop)

//

#endif