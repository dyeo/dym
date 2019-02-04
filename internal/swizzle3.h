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
swz2 <0, 0> xx, rr, ss; \
swz2 <0, 1> xy, rg, st; \
swz2 <0, 2> xz, rb, sp; \
swz2 <1, 0> yx, gr, ts; \
swz2 <1, 1> yy, gg, tt; \
swz2 <1, 2> yz, gb, tp; \
swz2 <2, 0> zx, br, ps; \
swz2 <2, 1> zy, bg, pt; \
swz2 <2, 2> zz, bb, pp; \
swz3 <0, 0, 0> xxx, rrr, sss; \
swz3 <0, 0, 1> xxy, rrg, sst; \
swz3 <0, 0, 2> xxz, rrb, ssp; \
swz3 <0, 1, 0> xyx, rgr, sts; \
swz3 <0, 1, 1> xyy, rgg, stt; \
swz3 <0, 1, 2> xyz, rgb, stp; \
swz3 <0, 2, 0> xzx, rbr, sps; \
swz3 <0, 2, 1> xzy, rbg, spt; \
swz3 <0, 2, 2> xzz, rbb, spp; \
swz3 <1, 0, 0> yxx, grr, tss; \
swz3 <1, 0, 1> yxy, grg, tst; \
swz3 <1, 0, 2> yxz, grb, tsp; \
swz3 <1, 1, 0> yyx, ggr, tts; \
swz3 <1, 1, 1> yyy, ggg, ttt; \
swz3 <1, 1, 2> yyz, ggb, ttp; \
swz3 <1, 2, 0> yzx, gbr, tps; \
swz3 <1, 2, 1> yzy, gbg, tpt; \
swz3 <1, 2, 2> yzz, gbb, tpp; \
swz3 <2, 0, 0> zxx, brr, pss; \
swz3 <2, 0, 1> zxy, brg, pst; \
swz3 <2, 0, 2> zxz, brb, psp; \
swz3 <2, 1, 0> zyx, bgr, pts; \
swz3 <2, 1, 1> zyy, bgg, ptt; \
swz3 <2, 1, 2> zyz, bgb, ptp; \
swz3 <2, 2, 0> zzx, bbr, pps; \
swz3 <2, 2, 1> zzy, bbg, ppt; \
swz3 <2, 2, 2> zzz, bbb, ppp; \
swz4 <0, 0, 0, 0> xxxx, rrrr, ssss; \
swz4 <0, 0, 0, 1> xxxy, rrrg, ssst; \
swz4 <0, 0, 0, 2> xxxz, rrrb, sssp; \
swz4 <0, 0, 1, 0> xxyx, rrgr, ssts; \
swz4 <0, 0, 1, 1> xxyy, rrgg, sstt; \
swz4 <0, 0, 1, 2> xxyz, rrgb, sstp; \
swz4 <0, 0, 2, 0> xxzx, rrbr, ssps; \
swz4 <0, 0, 2, 1> xxzy, rrbg, sspt; \
swz4 <0, 0, 2, 2> xxzz, rrbb, sspp; \
swz4 <0, 1, 0, 0> xyxx, rgrr, stss; \
swz4 <0, 1, 0, 1> xyxy, rgrg, stst; \
swz4 <0, 1, 0, 2> xyxz, rgrb, stsp; \
swz4 <0, 1, 1, 0> xyyx, rggr, stts; \
swz4 <0, 1, 1, 1> xyyy, rggg, sttt; \
swz4 <0, 1, 1, 2> xyyz, rggb, sttp; \
swz4 <0, 1, 2, 0> xyzx, rgbr, stps; \
swz4 <0, 1, 2, 1> xyzy, rgbg, stpt; \
swz4 <0, 1, 2, 2> xyzz, rgbb, stpp; \
swz4 <0, 2, 0, 0> xzxx, rbrr, spss; \
swz4 <0, 2, 0, 1> xzxy, rbrg, spst; \
swz4 <0, 2, 0, 2> xzxz, rbrb, spsp; \
swz4 <0, 2, 1, 0> xzyx, rbgr, spts; \
swz4 <0, 2, 1, 1> xzyy, rbgg, sptt; \
swz4 <0, 2, 1, 2> xzyz, rbgb, sptp; \
swz4 <0, 2, 2, 0> xzzx, rbbr, spps; \
swz4 <0, 2, 2, 1> xzzy, rbbg, sppt; \
swz4 <0, 2, 2, 2> xzzz, rbbb, sppp; \
swz4 <1, 0, 0, 0> yxxx, grrr, tsss; \
swz4 <1, 0, 0, 1> yxxy, grrg, tsst; \
swz4 <1, 0, 0, 2> yxxz, grrb, tssp; \
swz4 <1, 0, 1, 0> yxyx, grgr, tsts; \
swz4 <1, 0, 1, 1> yxyy, grgg, tstt; \
swz4 <1, 0, 1, 2> yxyz, grgb, tstp; \
swz4 <1, 0, 2, 0> yxzx, grbr, tsps; \
swz4 <1, 0, 2, 1> yxzy, grbg, tspt; \
swz4 <1, 0, 2, 2> yxzz, grbb, tspp; \
swz4 <1, 1, 0, 0> yyxx, ggrr, ttss; \
swz4 <1, 1, 0, 1> yyxy, ggrg, ttst; \
swz4 <1, 1, 0, 2> yyxz, ggrb, ttsp; \
swz4 <1, 1, 1, 0> yyyx, gggr, ttts; \
swz4 <1, 1, 1, 1> yyyy, gggg, tttt; \
swz4 <1, 1, 1, 2> yyyz, gggb, tttp; \
swz4 <1, 1, 2, 0> yyzx, ggbr, ttps; \
swz4 <1, 1, 2, 1> yyzy, ggbg, ttpt; \
swz4 <1, 1, 2, 2> yyzz, ggbb, ttpp; \
swz4 <1, 2, 0, 0> yzxx, gbrr, tpss; \
swz4 <1, 2, 0, 1> yzxy, gbrg, tpst; \
swz4 <1, 2, 0, 2> yzxz, gbrb, tpsp; \
swz4 <1, 2, 1, 0> yzyx, gbgr, tpts; \
swz4 <1, 2, 1, 1> yzyy, gbgg, tptt; \
swz4 <1, 2, 1, 2> yzyz, gbgb, tptp; \
swz4 <1, 2, 2, 0> yzzx, gbbr, tpps; \
swz4 <1, 2, 2, 1> yzzy, gbbg, tppt; \
swz4 <1, 2, 2, 2> yzzz, gbbb, tppp; \
swz4 <2, 0, 0, 0> zxxx, brrr, psss; \
swz4 <2, 0, 0, 1> zxxy, brrg, psst; \
swz4 <2, 0, 0, 2> zxxz, brrb, pssp; \
swz4 <2, 0, 1, 0> zxyx, brgr, psts; \
swz4 <2, 0, 1, 1> zxyy, brgg, pstt; \
swz4 <2, 0, 1, 2> zxyz, brgb, pstp; \
swz4 <2, 0, 2, 0> zxzx, brbr, psps; \
swz4 <2, 0, 2, 1> zxzy, brbg, pspt; \
swz4 <2, 0, 2, 2> zxzz, brbb, pspp; \
swz4 <2, 1, 0, 0> zyxx, bgrr, ptss; \
swz4 <2, 1, 0, 1> zyxy, bgrg, ptst; \
swz4 <2, 1, 0, 2> zyxz, bgrb, ptsp; \
swz4 <2, 1, 1, 0> zyyx, bggr, ptts; \
swz4 <2, 1, 1, 1> zyyy, bggg, pttt; \
swz4 <2, 1, 1, 2> zyyz, bggb, pttp; \
swz4 <2, 1, 2, 0> zyzx, bgbr, ptps; \
swz4 <2, 1, 2, 1> zyzy, bgbg, ptpt; \
swz4 <2, 1, 2, 2> zyzz, bgbb, ptpp; \
swz4 <2, 2, 0, 0> zzxx, bbrr, ppss; \
swz4 <2, 2, 0, 1> zzxy, bbrg, ppst; \
swz4 <2, 2, 0, 2> zzxz, bbrb, ppsp; \
swz4 <2, 2, 1, 0> zzyx, bbgr, ppts; \
swz4 <2, 2, 1, 1> zzyy, bbgg, pptt; \
swz4 <2, 2, 1, 2> zzyz, bbgb, pptp; \
swz4 <2, 2, 2, 0> zzzx, bbbr, ppps; \
swz4 <2, 2, 2, 1> zzzy, bbbg, pppt; \
swz4 <2, 2, 2, 2> zzzz, bbbb, pppp; \

//

#endif //_GMTK_SWIZZLE3_H_
