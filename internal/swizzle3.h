#ifndef _GMTK_SWIZZLE3_H_
#define _GMTK_SWIZZLE3_H_

#include "../util.h"
#include "vec.h"

#define GMTK_SWZ3_UOP(op)																				\
	V operator op () const																				\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = op ((const T*)this)[a];																\
		res[1] = op ((const T*)this)[b];																\
		res[2] = op ((const T*)this)[c];																\
		return res;																						\
	}

#define GMTK_SWZ3_OP(op)																				\
	V operator op (const swizzle3<a, b, c, V, T> &s) const												\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a];												\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b];												\
		res[2] = ((const T*)this)[c] op ((const T*)&s)[c];												\
		return res;																						\
	}																									\
																										\
	template<int a2, int b2, int c2, typename V, typename T>											\
	V operator op (const swizzle3<a2, b2, c2, V, T> &s) const											\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a2];												\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b2];												\
		res[2] = ((const T*)this)[c] op ((const T*)&s)[c2];												\
		return res;																						\
	}																									\
																										\
	V operator op (const T &v) const																	\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = ((const T*)this)[a] op v;																\
		res[1] = ((const T*)this)[b] op v;																\
		res[2] = ((const T*)this)[c] op v;																\
		return res;																						\
	}																									\
																										\
	friend V operator op (const T &l, const swizzle3<a, b, c, V, T> &r)									\
	{																									\
		V res(static_cast<T>(0));																		\
		res[0] = l op ((const T*)r)[a];																	\
		res[1] = l op ((const T*)r)[b];																	\
		res[2] = l op ((const T*)r)[c];																	\
		return res;																						\
	}

#define GMTK_SWZ3_ROP(op)																				\
	writable_type& operator op (const swizzle3<a, b, c, V, T> &s)										\
	{																									\
		const T va = ((const T*)&s)[a];																	\
		const T vb = ((const T*)&s)[b];																	\
		const T vc = ((const T*)&s)[c];																	\
		((T*)this)[a] op va; 																			\
		((T*)this)[b] op vb;																			\
		((T*)this)[c] op vc;																			\
		return *this;																					\
	}																									\
																										\
	template<int a2, int b2, int c2, typename T>														\
	writable_type& operator op (const swizzle3<a2, b2, c2, V, T> &s)									\
	{																									\
		const T va2 = ((const T*)&s)[a2];																\
		const T vb2 = ((const T*)&s)[b2];																\
		const T vc2 = ((const T*)&s)[c2];																\
		((T*)this)[a] op va2; 																			\
		((T*)this)[b] op vb2;																			\
		((T*)this)[c] op vc2;																			\
		return *this;																					\
	}																									\
																										\
	writable_type& operator op (const V &s)																\
	{																									\
		((T*)this)[a] op s.data[0]; 																	\
		((T*)this)[b] op s.data[1];																		\
		((T*)this)[c] op s.data[2];																		\
		return *this;																					\
	}																									\
																										\
	template<int a2, int b2, int c2, typename T> 														\
	writable_type& operator op (const T &s)																\
	{																									\
		((const T*)&s)[a] op s; 																		\
		((const T*)&s)[b] op s;																			\
		((const T*)&s)[c] op s;																			\
		return *this;																					\
	}

#define GMTK_SWZ3_BOP(op) 																				\
	template<int a, int b, int c, typename T> 															\
	static inline vec<3, T> operator op (const vec<3, T> &v, const swizzle3<a, b, c, vec<3, T>, T> &s)	\
	{ 																									\
		vec<3, T> res; 																					\
		res.data[0] = data[0] op s[a]; 																	\
		res.data[1] = data[1] op s[b]; 																	\
		res.data[2] = data[2] op s[c]; 																	\
		return res; 																					\
	}

#define GMTK_SWZ3_BROP(op) 																				\
	template<int a, int b, int c, typename T> 															\
	static inline vec<3, T>& operator op (vec<3, T> &v, const swizzle3<a, b, c, vec<3, T>, T> &s)		\
	{ 																									\
		v.data[0] op s[a]; 																				\
		v.data[1] op s[b]; 																				\
		v.data[2] op s[c]; 																				\
		return v; 																						\
	}

//

#define GMTK_SWZ3_TYPE \
	template<int a, int b, int c> using swz3 = swizzle3<a, b, c, vec<3, T>, T>;

//

namespace GMTK_NAMESPACE
{////

	template<int a, int b, int c, typename V, typename T>
	class swizzle3
	{
	public:

		static constexpr bool is_writable = (a != b && a != c && b != c);

		typedef typename std::conditional<is_writable, swizzle3<a, b, c, V, T>, struct duplicate_components_swizzle>::type writable_type;

		inline T& operator[](const int i) {
			return ((T* const)this)[i];
		}

		inline const T& operator[](const int i) const {
			return ((T* const)this)[i];
		}

		GMTK_SWZ3_UOP(-)
		GMTK_SWZ3_UOP(~)
		GMTK_SWZ3_ROP(=)
			
		GMTK_SWZ3_OP(*)
		GMTK_SWZ3_OP(/)
		GMTK_SWZ3_OP(+)
		GMTK_SWZ3_OP(-)
		GMTK_SWZ3_OP(|)
		GMTK_SWZ3_OP(&)
		GMTK_SWZ3_OP(^)
		GMTK_SWZ3_OP(%)
		GMTK_SWZ3_OP(<<)
		GMTK_SWZ3_OP(>>)

		GMTK_SWZ3_ROP(*=)
		GMTK_SWZ3_ROP(/=)
		GMTK_SWZ3_ROP(+=)
		GMTK_SWZ3_ROP(-=)
		GMTK_SWZ3_ROP(|=)
		GMTK_SWZ3_ROP(&=)
		GMTK_SWZ3_ROP(^=)
		GMTK_SWZ3_ROP(%=)
		GMTK_SWZ3_ROP(<<=)
		GMTK_SWZ3_ROP(>>=)

	}; //! class swizzle3

	//////////////////////
	//! OUTPUT OPERATOR //
	//////////////////////

	template <int a, int b, int c, typename V, typename T>
	inline std::ostream& operator<<(std::ostream& os, const swizzle3<a, b, c, V, T>& s)
	{
		os << vec<3, T>(s[a], s[b], s[c]);
		return os;
	}
	
	///////////////////////
	//! BINARY OPERATORS //
	///////////////////////
	
	GMTK_SWZ3_BOP(*)
	GMTK_SWZ3_BOP(/)
	GMTK_SWZ3_BOP(+)
	GMTK_SWZ3_BOP(-)
	GMTK_SWZ3_BOP(|)
	GMTK_SWZ3_BOP(&)
	GMTK_SWZ3_BOP(^)
	GMTK_SWZ3_BOP(%)
	GMTK_SWZ3_BOP(<<)
	GMTK_SWZ3_BOP(>>)

	GMTK_SWZ3_BROP(*=)
	GMTK_SWZ3_BROP(/=)
	GMTK_SWZ3_BROP(+=)
	GMTK_SWZ3_BROP(-=)
	GMTK_SWZ3_BROP(|=)
    GMTK_SWZ3_BROP(&=)
    GMTK_SWZ3_BROP(^=)
    GMTK_SWZ3_BROP(%=)
    GMTK_SWZ3_BROP(<<=)
    GMTK_SWZ3_BROP(>>=)

}////

//

#undef GMTK_SWZ3_UOP
#undef GMTK_SWZ3_OP
#undef GMTK_SWZ3_ROP

//

#define GMTK_VEC3_SWIZZLES \
swz2 <0, 0> xx, rr, uu; \
swz2 <0, 1> xy, rg, uv; \
swz2 <0, 2> xz, rb, us; \
swz2 <1, 0> yx, gr, vu; \
swz2 <1, 1> yy, gg, vv; \
swz2 <1, 2> yz, gb, vs; \
swz2 <2, 0> zx, br, su; \
swz2 <2, 1> zy, bg, sv; \
swz2 <2, 2> zz, bb, ss; \
swz3 <0, 0, 0> xxx, rrr, uuu; \
swz3 <0, 0, 1> xxy, rrg, uuv; \
swz3 <0, 0, 2> xxz, rrb, uus; \
swz3 <0, 1, 0> xyx, rgr, uvu; \
swz3 <0, 1, 1> xyy, rgg, uvv; \
swz3 <0, 1, 2> xyz, rgb, uvs; \
swz3 <0, 2, 0> xzx, rbr, usu; \
swz3 <0, 2, 1> xzy, rbg, usv; \
swz3 <0, 2, 2> xzz, rbb, uss; \
swz3 <1, 0, 0> yxx, grr, vuu; \
swz3 <1, 0, 1> yxy, grg, vuv; \
swz3 <1, 0, 2> yxz, grb, vus; \
swz3 <1, 1, 0> yyx, ggr, vvu; \
swz3 <1, 1, 1> yyy, ggg, vvv; \
swz3 <1, 1, 2> yyz, ggb, vvs; \
swz3 <1, 2, 0> yzx, gbr, vsu; \
swz3 <1, 2, 1> yzy, gbg, vsv; \
swz3 <1, 2, 2> yzz, gbb, vss; \
swz3 <2, 0, 0> zxx, brr, suu; \
swz3 <2, 0, 1> zxy, brg, suv; \
swz3 <2, 0, 2> zxz, brb, sus; \
swz3 <2, 1, 0> zyx, bgr, svu; \
swz3 <2, 1, 1> zyy, bgg, svv; \
swz3 <2, 1, 2> zyz, bgb, svs; \
swz3 <2, 2, 0> zzx, bbr, ssu; \
swz3 <2, 2, 1> zzy, bbg, ssv; \
swz3 <2, 2, 2> zzz, bbb, sss; \
swz4 <0, 0, 0, 0> xxxx, rrrr, uuuu; \
swz4 <0, 0, 0, 1> xxxy, rrrg, uuuv; \
swz4 <0, 0, 0, 2> xxxz, rrrb, uuus; \
swz4 <0, 0, 1, 0> xxyx, rrgr, uuvu; \
swz4 <0, 0, 1, 1> xxyy, rrgg, uuvv; \
swz4 <0, 0, 1, 2> xxyz, rrgb, uuvs; \
swz4 <0, 0, 2, 0> xxzx, rrbr, uusu; \
swz4 <0, 0, 2, 1> xxzy, rrbg, uusv; \
swz4 <0, 0, 2, 2> xxzz, rrbb, uuss; \
swz4 <0, 1, 0, 0> xyxx, rgrr, uvuu; \
swz4 <0, 1, 0, 1> xyxy, rgrg, uvuv; \
swz4 <0, 1, 0, 2> xyxz, rgrb, uvus; \
swz4 <0, 1, 1, 0> xyyx, rggr, uvvu; \
swz4 <0, 1, 1, 1> xyyy, rggg, uvvv; \
swz4 <0, 1, 1, 2> xyyz, rggb, uvvs; \
swz4 <0, 1, 2, 0> xyzx, rgbr, uvsu; \
swz4 <0, 1, 2, 1> xyzy, rgbg, uvsv; \
swz4 <0, 1, 2, 2> xyzz, rgbb, uvss; \
swz4 <0, 2, 0, 0> xzxx, rbrr, usuu; \
swz4 <0, 2, 0, 1> xzxy, rbrg, usuv; \
swz4 <0, 2, 0, 2> xzxz, rbrb, usus; \
swz4 <0, 2, 1, 0> xzyx, rbgr, usvu; \
swz4 <0, 2, 1, 1> xzyy, rbgg, usvv; \
swz4 <0, 2, 1, 2> xzyz, rbgb, usvs; \
swz4 <0, 2, 2, 0> xzzx, rbbr, ussu; \
swz4 <0, 2, 2, 1> xzzy, rbbg, ussv; \
swz4 <0, 2, 2, 2> xzzz, rbbb, usss; \
swz4 <1, 0, 0, 0> yxxx, grrr, vuuu; \
swz4 <1, 0, 0, 1> yxxy, grrg, vuuv; \
swz4 <1, 0, 0, 2> yxxz, grrb, vuus; \
swz4 <1, 0, 1, 0> yxyx, grgr, vuvu; \
swz4 <1, 0, 1, 1> yxyy, grgg, vuvv; \
swz4 <1, 0, 1, 2> yxyz, grgb, vuvs; \
swz4 <1, 0, 2, 0> yxzx, grbr, vusu; \
swz4 <1, 0, 2, 1> yxzy, grbg, vusv; \
swz4 <1, 0, 2, 2> yxzz, grbb, vuss; \
swz4 <1, 1, 0, 0> yyxx, ggrr, vvuu; \
swz4 <1, 1, 0, 1> yyxy, ggrg, vvuv; \
swz4 <1, 1, 0, 2> yyxz, ggrb, vvus; \
swz4 <1, 1, 1, 0> yyyx, gggr, vvvu; \
swz4 <1, 1, 1, 1> yyyy, gggg, vvvv; \
swz4 <1, 1, 1, 2> yyyz, gggb, vvvs; \
swz4 <1, 1, 2, 0> yyzx, ggbr, vvsu; \
swz4 <1, 1, 2, 1> yyzy, ggbg, vvsv; \
swz4 <1, 1, 2, 2> yyzz, ggbb, vvss; \
swz4 <1, 2, 0, 0> yzxx, gbrr, vsuu; \
swz4 <1, 2, 0, 1> yzxy, gbrg, vsuv; \
swz4 <1, 2, 0, 2> yzxz, gbrb, vsus; \
swz4 <1, 2, 1, 0> yzyx, gbgr, vsvu; \
swz4 <1, 2, 1, 1> yzyy, gbgg, vsvv; \
swz4 <1, 2, 1, 2> yzyz, gbgb, vsvs; \
swz4 <1, 2, 2, 0> yzzx, gbbr, vssu; \
swz4 <1, 2, 2, 1> yzzy, gbbg, vssv; \
swz4 <1, 2, 2, 2> yzzz, gbbb, vsss; \
swz4 <2, 0, 0, 0> zxxx, brrr, suuu; \
swz4 <2, 0, 0, 1> zxxy, brrg, suuv; \
swz4 <2, 0, 0, 2> zxxz, brrb, suus; \
swz4 <2, 0, 1, 0> zxyx, brgr, suvu; \
swz4 <2, 0, 1, 1> zxyy, brgg, suvv; \
swz4 <2, 0, 1, 2> zxyz, brgb, suvs; \
swz4 <2, 0, 2, 0> zxzx, brbr, susu; \
swz4 <2, 0, 2, 1> zxzy, brbg, susv; \
swz4 <2, 0, 2, 2> zxzz, brbb, suss; \
swz4 <2, 1, 0, 0> zyxx, bgrr, svuu; \
swz4 <2, 1, 0, 1> zyxy, bgrg, svuv; \
swz4 <2, 1, 0, 2> zyxz, bgrb, svus; \
swz4 <2, 1, 1, 0> zyyx, bggr, svvu; \
swz4 <2, 1, 1, 1> zyyy, bggg, svvv; \
swz4 <2, 1, 1, 2> zyyz, bggb, svvs; \
swz4 <2, 1, 2, 0> zyzx, bgbr, svsu; \
swz4 <2, 1, 2, 1> zyzy, bgbg, svsv; \
swz4 <2, 1, 2, 2> zyzz, bgbb, svss; \
swz4 <2, 2, 0, 0> zzxx, bbrr, ssuu; \
swz4 <2, 2, 0, 1> zzxy, bbrg, ssuv; \
swz4 <2, 2, 0, 2> zzxz, bbrb, ssus; \
swz4 <2, 2, 1, 0> zzyx, bbgr, ssvu; \
swz4 <2, 2, 1, 1> zzyy, bbgg, ssvv; \
swz4 <2, 2, 1, 2> zzyz, bbgb, ssvs; \
swz4 <2, 2, 2, 0> zzzx, bbbr, sssu; \
swz4 <2, 2, 2, 1> zzzy, bbbg, sssv; \
swz4 <2, 2, 2, 2> zzzz, bbbb, ssss; \

//

#endif //_GMTK_SWIZZLE3_H_
