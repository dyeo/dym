#ifndef _GMTK_SWIZZLE2_H_
#define _GMTK_SWIZZLE2_H_

#include "../util.h"
#include "vec.h"

#define GMTK_SWZ2_UOP(op)																				\
	V operator op () const																				\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = op ((const T*)this)[a];																\
		res[1] = op ((const T*)this)[b];																\
		return res;																						\
	}

#define GMTK_SWZ2_OP(op)																				\
	inline V operator op (const swizzle2<a, b, V, T> &s) const											\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a];												\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b];												\
		return res;																						\
	}																									\
																										\
	template<int a2, int b2, typename V, typename T>													\
	inline V operator op (const swizzle2<a2, b2, V, T> &s) const										\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a2];												\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b2];												\
		return res;																						\
	}																									\
																										\
	inline V operator op (const T &v) const																\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = ((const T*)this)[a] op v;																\
		res[1] = ((const T*)this)[b] op v;																\
		return res;																						\
	}																									\
																										\
	inline friend V operator op (const T &l, const swizzle2<a, b, V, T> &r)								\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = l op ((const T*)r)[a];																	\
		res[1] = l op ((const T*)r)[b];																	\
		return res;																						\
	}

#define GMTK_SWZ2_ROP(op)																				\
	inline writable_type& operator op (const swizzle2<a, b, V, T> &s)									\
	{																									\
		const T va = ((const T*)&s)[a];																	\
		const T vb = ((const T*)&s)[b];																	\
		((T*)this)[a] op va; 																			\
		((T*)this)[b] op vb;																			\
		return *this;																					\
	}																									\
																										\
	template<int a2, int b2, typename T>																\
	inline writable_type& operator op (const swizzle2<a2, b2, V, T> &s)									\
	{																									\
		const T va2 = ((const T*)&s)[a2];																\
		const T vb2 = ((const T*)&s)[b2];																\
		((T*)this)[a] op va2; 																			\
		((T*)this)[b] op vb2;																			\
		return *this;																					\
	}																									\
																										\
	inline writable_type& operator op (const V &s)														\
	{																									\
		((T*)this)[a] op s.data[0]; 																	\
		((T*)this)[b] op s.data[1];																		\
		return *this;																					\
	}																									\
																										\
	template<int a2, int b2, typename T> 																\
	inline writable_type& operator op (const T &s)														\
	{																									\
		((const T*)&s)[a] op s; 																		\
		((const T*)&s)[b] op s;																			\
		return *this;																					\
	}

#define GMTK_SWZ2_BOP(op)																				\
	template<int a, int b, typename T>																	\
	static inline vec<2, T> operator op (const vec<2, T> &v, const swizzle2<a, b, vec<2, T>, T> &s)		\
	{ 																									\
		vec<2, T> res; 																					\
		res.data[0] = data[0] op s[a]; 																	\
		res.data[1] = data[1] op s[b]; 																	\
		return res;																						\
	}																								

#define GMTK_SWZ2_BROP(op)																				\
	template<int a, int b, typename T>																	\
	static inline vec<2, T>& operator op (vec<2, T> &v, const swizzle2<a, b, vec<2, T>, T> &s)			\
	{ 																									\
		v.data[0] op s[a]; 																				\
		v.data[1] op s[b]; 																				\
		return v; 																						\
	} 																						   

//

#define GMTK_SWZ2_TYPE \
	template<int a, int b> using swz2 = swizzle2<a, b, vec<2, T>, T>;

//

namespace GMTK_NAMESPACE
{////

	template<int a, int b, typename V, typename T>
	class swizzle2
	{
	public:
		
		static constexpr bool is_writable = (a != b);

		typedef typename std::conditional<is_writable, swizzle2<a, b, V, T>, struct duplicate_components_swizzle>::type writable_type;

		inline T& operator[](const int i) {
			return ((T* const)this)[i];
		}

		inline const T& operator[](const int i) const {
			return ((T* const)this)[i];
		}

		GMTK_SWZ2_UOP(-)
		GMTK_SWZ2_UOP(~)
		GMTK_SWZ2_ROP(=)					  
		
		GMTK_SWZ2_OP(*)
		GMTK_SWZ2_OP(/)
		GMTK_SWZ2_OP(+)
		GMTK_SWZ2_OP(-)
		GMTK_SWZ2_OP(|)
		GMTK_SWZ2_OP(&)
		GMTK_SWZ2_OP(^)
		GMTK_SWZ2_OP(%)
		GMTK_SWZ2_OP(<<)
		GMTK_SWZ2_OP(>>)

		GMTK_SWZ2_ROP(*=)
		GMTK_SWZ2_ROP(/=)
		GMTK_SWZ2_ROP(+=)
		GMTK_SWZ2_ROP(-=)
		GMTK_SWZ2_ROP(|=)
		GMTK_SWZ2_ROP(&=)
		GMTK_SWZ2_ROP(^=)
		GMTK_SWZ2_ROP(%=)
		GMTK_SWZ2_ROP(<<=)
		GMTK_SWZ2_ROP(>>=)

	}; //! class swizzle2

	//////////////////////
	//! OUTPUT OPERATOR //
	//////////////////////

	template <int a, int b, typename V, typename T>
	inline std::ostream& operator<<(std::ostream& os, const swizzle2<a, b, V, T>& s)
	{
		os << vec<2, T>(s[a], s[b]);
		return os;
	}

	///////////////////////
	//! BINARY OPERATORS //
	///////////////////////
		
	GMTK_SWZ2_BOP(*)
	GMTK_SWZ2_BOP(/)
	GMTK_SWZ2_BOP(+)
	GMTK_SWZ2_BOP(-)
	GMTK_SWZ2_BOP(|)
	GMTK_SWZ2_BOP(&)
	GMTK_SWZ2_BOP(^)
	GMTK_SWZ2_BOP(%)
	GMTK_SWZ2_BOP(<<)
	GMTK_SWZ2_BOP(>>)

	GMTK_SWZ2_BROP(*=)
	GMTK_SWZ2_BROP(/=)
	GMTK_SWZ2_BROP(+=)
	GMTK_SWZ2_BROP(-=)
	GMTK_SWZ2_BROP(|=)
    GMTK_SWZ2_BROP(&=)
    GMTK_SWZ2_BROP(^=)
    GMTK_SWZ2_BROP(%=)
    GMTK_SWZ2_BROP(<<=)
    GMTK_SWZ2_BROP(>>=)

}////

//

#undef GMTK_SWZ2_UOP
#undef GMTK_SWZ2_OP
#undef GMTK_SWZ2_ROP

//

#define GMTK_VEC2_SWIZZLES \
swz2 <0, 0> xx, rr, ss; \
swz2 <0, 1> xy, rg, st; \
swz2 <1, 0> yx, gr, ts; \
swz2 <1, 1> yy, gg, tt; \
swz3 <0, 0, 0> xxx, rrr, sss; \
swz3 <0, 0, 1> xxy, rrg, sst; \
swz3 <0, 1, 0> xyx, rgr, sts; \
swz3 <0, 1, 1> xyy, rgg, stt; \
swz3 <1, 0, 0> yxx, grr, tss; \
swz3 <1, 0, 1> yxy, grg, tst; \
swz3 <1, 1, 0> yyx, ggr, tts; \
swz3 <1, 1, 1> yyy, ggg, ttt; \
swz4 <0, 0, 0, 0> xxxx, rrrr, ssss; \
swz4 <0, 0, 0, 1> xxxy, rrrg, ssst; \
swz4 <0, 0, 1, 0> xxyx, rrgr, ssts; \
swz4 <0, 0, 1, 1> xxyy, rrgg, sstt; \
swz4 <0, 1, 0, 0> xyxx, rgrr, stss; \
swz4 <0, 1, 0, 1> xyxy, rgrg, stst; \
swz4 <0, 1, 1, 0> xyyx, rggr, stts; \
swz4 <0, 1, 1, 1> xyyy, rggg, sttt; \
swz4 <1, 0, 0, 0> yxxx, grrr, tsss; \
swz4 <1, 0, 0, 1> yxxy, grrg, tsst; \
swz4 <1, 0, 1, 0> yxyx, grgr, tsts; \
swz4 <1, 0, 1, 1> yxyy, grgg, tstt; \
swz4 <1, 1, 0, 0> yyxx, ggrr, ttss; \
swz4 <1, 1, 0, 1> yyxy, ggrg, ttst; \
swz4 <1, 1, 1, 0> yyyx, gggr, ttts; \
swz4 <1, 1, 1, 1> yyyy, gggg, tttt; \

//

#endif //_GMTK_SWIZZLE2_H_
