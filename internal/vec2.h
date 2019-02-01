#ifndef _GMTK_VEC2_H_
#define _GMTK_VEC2_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"
#include "swizzle.h"

//

#define GMTK_VEC2_LOOP(oper) GMTK_UNROLL_LOOP(i,2,oper)

//

#define GMTK_VEC2_UN_OP(op) \
	inline vec<2, T> operator op () const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = op data[i]); return res; }

#define GMTK_VEC2_VEC_OP(op) \
	inline vec<2, T> operator op (const vec<2, T>& v) const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = data[i] op v.data[i]); return res; } \
	template<int a, int b> \
	inline vec<2, T> operator op (const swizzle<a, b, vec<2, T>, T>& v) const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = data[i] op v[i]); return res; }

#define GMTK_VEC2_SCL_OP(op) \
	inline vec<2, T> operator op (const T& v) const \
	{ vec<2, T> res; GMTK_VEC2_LOOP(res.data[i] = data[i] op v); return res; } 

#define GMTK_VEC2_VEC_ROP(op) \
	inline vec<2, T>& operator op (const vec<2, T>& v) \
	{ GMTK_VEC2_LOOP(data[i] op v.data[i]); return *this; } \
	template<int a, int b> \
	inline vec<2, T> operator op (const swizzle<a, b, vec<2, T>, T>& v) \
	{ GMTK_VEC2_LOOP(data[i] op v[i]); return *this; }

#define GMTK_VEC2_SCL_ROP(op) \
	inline vec<2, T>& operator op (const T& v) \
	{ GMTK_VEC2_LOOP(data[i] op v); return *this; }

//

namespace GMTK_NAMESPACE
{////

	template <typename T> struct vec <2, T>
	{
		////////////
		//! TYPES //
		////////////

		template<int a, int b> using swz2 = swizzle<a, b, vec<2, T>, T>;

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[2]; };
			struct { T x, y; };
			swz2<0, 0> xx;
			swz2<0, 1> xy;
			swz2<1, 0> yx;
			swz2<1, 1> yy;
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
		inline vec(const swizzle<a, b, vec<2, T>, T>&s)
		{
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

//

#pragma warning(pop)

//

#endif