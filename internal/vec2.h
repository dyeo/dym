#ifndef _GMTK_VEC2_H_
#define _GMTK_VEC2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"

//

#define GMTK_VEC2_LOOP(oper) GMTK_STATIC_LOOP(i,2,oper)

//

#define GMTK_VEC2_INIT(a, b) : x( a ), y( b ) { }

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

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <2, T>
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
			struct { T data[2]; };
			struct { T x, y; };
			struct { T r, g; };
			GMTK_VEC2_SWIZZLES
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Initialize vec2 with two values
		inline vec(const T& s0, const T& s1) 
			GMTK_VEC2_INIT(s0, s1)

		//! Default constructor
		inline vec() 
			GMTK_VEC2_INIT(static_cast<T>(0), static_cast<T>(0))

		//! Swizzle constructor
		template<int a, int b>
		inline vec(const swz2<a, b>&s) 
			GMTK_VEC2_INIT(s[a], s[b])

		//! Copy constructor
		inline vec(const vec<2, T>& v) 
			GMTK_VEC2_INIT(v.x, v.y)

		//! Explicit type-conversion copy constructor
		template<typename U> 
		explicit inline vec(const vec<2, U>& v) 
			GMTK_VEC2_INIT(static_cast<T>(v.x), static_cast<T>(v.y))

		//! Fill constructor
		explicit inline vec(const T& s) 
			GMTK_VEC2_INIT(s, s)

		//! Array initializer
		explicit inline vec(const T* a) 
			GMTK_VEC2_INIT(a[0], a[1])

		//! Initializer list constructor
		inline vec(std::initializer_list<T> l)
			GMTK_VEC2_INIT(*(l.begin()), *(l.begin() + 1))

		//! Copy constructor for arbitrarily larger vector
		template<int d2>
		inline vec(const vec<d2, T> &v) {
			GMTK_STATIC_ASSERT(d2 >= 2);
			GMTK_VEC2_LOOP(data[i] = v.data[i]);
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
		
		//! Component-wise unary negation
		GMTK_VEC2_UN_OP(-)
		//! Component-wise unary negation
		GMTK_VEC2_UN_OP(~)
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
		//! Component-wise vector OR
		GMTK_VEC2_VEC_OP(|)
		//! Component-wise vector AND
		GMTK_VEC2_VEC_OP(&)
		//! Component-wise vector XOR
		GMTK_VEC2_VEC_OP(^)
		//! Component-wise vector modulus
		GMTK_VEC2_VEC_OP(%)
		//! Component-wise vector shift left
		GMTK_VEC2_VEC_OP(<<)
		//! Component-wise vector shift right
		GMTK_VEC2_VEC_OP(>>)	

		//! Component-wise scalar multiplication
		GMTK_VEC2_SCL_OP(*)		
		//! Component-wise scalar division
		GMTK_VEC2_SCL_OP(/)		
		//! Component-wise scalar addition
		GMTK_VEC2_SCL_OP(+)		
		//! Component-wise scalar subtraction
		GMTK_VEC2_SCL_OP(-)		
		//! Component-wise scalar OR
		GMTK_VEC2_SCL_OP(|)
		//! Component-wise scalar AND
		GMTK_VEC2_SCL_OP(&)
		//! Component-wise scalar XOR
		GMTK_VEC2_SCL_OP(^)
		//! Component-wise scalar modulus
		GMTK_VEC2_SCL_OP(%)
		//! Component-wise scalar shift left
		GMTK_VEC2_SCL_OP(<<)
		//! Component-wise scalar shift right
		GMTK_VEC2_SCL_OP(>>)
						
		//! Component-wise vector reference multiplication
		GMTK_VEC2_VEC_ROP(*=)		
		//! Component-wise vector reference division
		GMTK_VEC2_VEC_ROP(/=)		
		//! Component-wise vector reference addition
		GMTK_VEC2_VEC_ROP(+=)		
		//! Component-wise vector reference subtraction
		GMTK_VEC2_VEC_ROP(-=)
		//! Component-wise vector reference OR
		GMTK_VEC2_VEC_ROP(|=)
		//! Component-wise vector reference AND
		GMTK_VEC2_VEC_ROP(&=)
		//! Component-wise vector reference XOR
		GMTK_VEC2_VEC_ROP(^=)
		//! Component-wise vector reference modulus
		GMTK_VEC2_VEC_ROP(%=)
		//! Component-wise vector reference shift left
		GMTK_VEC2_VEC_ROP(<<=)
		//! Component-wise vector reference shift right
		GMTK_VEC2_VEC_ROP(>>=)

		//! Component-wise scalar reference multiplication
		GMTK_VEC2_SCL_ROP(*=)	
		//! Component-wise scalar reference division
		GMTK_VEC2_SCL_ROP(/=)		
		//! Component-wise scalar reference addition
		GMTK_VEC2_SCL_ROP(+=)		
		//! Component-wise scalar reference subtraction
		GMTK_VEC2_SCL_ROP(-=)
		//! Component-wise scalar reference OR
		GMTK_VEC2_SCL_ROP(|=)
		//! Component-wise scalar reference AND
		GMTK_VEC2_SCL_ROP(&=)
		//! Component-wise scalar reference XOR
		GMTK_VEC2_SCL_ROP(^=)
		//! Component-wise scalar reference modulus
		GMTK_VEC2_SCL_ROP(%=)
		//! Component-wise scalar reference shift left
		GMTK_VEC2_SCL_ROP(<<=)
		//! Component-wise scalar reference shift right
		GMTK_VEC2_SCL_ROP(>>=)

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

#undef GMTK_VEC2_INIT
#undef GMTK_VEC2_UN_OP
#undef GMTK_VEC2_VEC_OP
#undef GMTK_VEC2_SCL_OP
#undef GMTK_VEC2_VEC_ROP
#undef GMTK_VEC2_SCL_ROP

#undef GMTK_SWZ2_BOP
#undef GMTK_SWZ2_BROP

//

#pragma warning(pop)

//

#endif