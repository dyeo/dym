#ifndef _GMTK_SWIZZLE4_H_
#define _GMTK_SWIZZLE4_H_

#include "../util.h"
#include "vec.h"

#define GMTK_SWZ4_UOP(op)																					\
	V operator op () const																					\
	{																										\
		V res(static_cast<T>(0));																			\
		res[0] = op ((const T*)this)[a];																	\
		res[1] = op ((const T*)this)[b];																	\
		res[2] = op ((const T*)this)[c];																	\
		res[3] = op ((const T*)this)[d];																	\
		return res;																							\
	}

#define GMTK_SWZ4_OP(op)																					\
	V operator op (const swizzle4<a, b, c, d, V, T> &s) const												\
	{																										\
		V res(static_cast<T>(0));																			\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a];													\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b];													\
		res[2] = ((const T*)this)[c] op ((const T*)&s)[c];													\
		res[3] = ((const T*)this)[d] op ((const T*)&s)[d];													\
		return res;																							\
	}																										\
																											\
	template<int a2, int b2, int c2, int d2, typename V, typename T>										\
	V operator op (const swizzle4<a2, b2, c2, d2, V, T> &s) const											\
	{																										\
		V res(static_cast<T>(0));																			\
		res[0] = ((const T*)this)[a] op ((const T*)&s)[a2];													\
		res[1] = ((const T*)this)[b] op ((const T*)&s)[b2];													\
		res[2] = ((const T*)this)[c] op ((const T*)&s)[c2];													\
		res[3] = ((const T*)this)[d] op ((const T*)&s)[d2];													\
		return res;																							\
	}																										\
																											\
	V operator op (const T &v) const																		\
	{																										\
		V res(static_cast<T>(0));																			\
		res[0] = ((const T*)this)[a] op v;																	\
		res[1] = ((const T*)this)[b] op v;																	\
		res[2] = ((const T*)this)[c] op v;																	\
		res[3] = ((const T*)this)[d] op v;																	\
		return res;																							\
	}																										\
																											\
	friend V operator op (const T &l, const swizzle4<a, b, c, d, V, T> &r)									\
	{																										\
		V res(static_cast<T>(0));																			\
		res[0] = l op ((const T*)r)[a];																		\
		res[1] = l op ((const T*)r)[b];																		\
		res[2] = l op ((const T*)r)[c];																		\
		res[3] = l op ((const T*)r)[d];																		\
		return res;																							\
	}

#define GMTK_SWZ4_ROP(op)																					\
	writable_type& operator op (const swizzle4<a, b, c, d, V, T> &s)										\
	{																										\
		const T va = ((const T*)&s)[a];																		\
		const T vb = ((const T*)&s)[b];																		\
		const T vc = ((const T*)&s)[c];																		\
		const T vd = ((const T*)&s)[d];																		\
		((T*)this)[a] op va; 																				\
		((T*)this)[b] op vb;																				\
		((T*)this)[c] op vc;																				\
		((T*)this)[d] op vd;																				\
		return *this;																						\
	}																										\
																											\
	template<int a2, int b2, int c2, int d2, typename T>													\
	writable_type& operator op (const swizzle4<a2, b2, c2, d2, V, T> &s)									\
	{																										\
		const T va2 = ((const T*)&s)[a2];																	\
		const T vb2 = ((const T*)&s)[b2];																	\
		const T vc2 = ((const T*)&s)[c2];																	\
		const T vd2 = ((const T*)&s)[d2];																	\
		((T*)this)[a] op va2; 																				\
		((T*)this)[b] op vb2;																				\
		((T*)this)[c] op vc2;																				\
		((T*)this)[d] op vd2;																				\
		return *this;																						\
	}																										\
																											\
	writable_type& operator op (const V &s)																	\
	{																										\
		((T*)this)[a] op s.data[0]; 																		\
		((T*)this)[b] op s.data[1];																			\
		((T*)this)[c] op s.data[2];																			\
		((T*)this)[d] op s.data[3];																			\
		return *this;																						\
	}																										\
																											\
	template<int a2, int b2, int c2, int d2, typename T> 													\
	writable_type& operator op (const T &s)																	\
	{																										\
		((const T*)&s)[a] op s; 																			\
		((const T*)&s)[b] op s;																				\
		((const T*)&s)[c] op s;																				\
		((const T*)&s)[d] op s;																				\
		return *this;																						\
	}

#define GMTK_SWZ4_BOP(op)																					\
	template<int a, int b, int c, int d, typename T>														\
	static inline vec<4, T> operator op (const vec<4, T> &v, const swizzle4<a, b, c, d, vec<4, T>, T> &s)	\
	{ 																										\
		vec<4, T> res; 																						\
		res.data[0] = data[0] op s[a]; 																		\
		res.data[1] = data[1] op s[b]; 																		\
		res.data[2] = data[2] op s[c];																		\
		res.data[3] = data[3] op s[d]; 																		\
		return res; 																						\
	}

#define GMTK_SWZ4_BROP(op)																					\
	template<int a, int b, int c, int d, typename T>														\
	static inline vec<4, T>& operator op (vec<4, T> &v, const swizzle4<a, b, c, d, vec<4, T>, T> &s)		\
	{ 																										\
		v.data[0] op s[a]; 																					\
		v.data[1] op s[b]; 																					\
		v.data[2] op s[c]; 																					\
		v.data[3] op s[d]; 																					\
		return v; 																							\
	}

//

#define GMTK_SWZ4_TYPE \
	template<int a, int b, int c, int d> using swz4 = swizzle4<a, b, c, d, vec<4, T>, T>;

//

namespace GMTK_NAMESPACE
{////

	template<int a, int b, int c, int d, typename V, typename T>
	class swizzle4
	{
	public:
		
		static constexpr bool is_writable = (a != b && a != c && a != d && b != c && b != d && c != d);

		typedef typename std::conditional<is_writable, swizzle4<a, b, c, d, V, T>, struct duplicate_components_swizzle>::type writable_type;

		inline T& operator[](const int i) {
			return ((T* const)this)[i];
		}

		inline const T& operator[](const int i) const {
			return ((T* const)this)[i];
		}

		GMTK_SWZ4_UOP(-)
		GMTK_SWZ4_UOP(~)
		GMTK_SWZ4_ROP(=)

		GMTK_SWZ4_OP(*)
		GMTK_SWZ4_OP(/)
		GMTK_SWZ4_OP(+)
		GMTK_SWZ4_OP(-)
		GMTK_SWZ4_OP(|)
		GMTK_SWZ4_OP(&)
		GMTK_SWZ4_OP(^)
		GMTK_SWZ4_OP(%)
		GMTK_SWZ4_OP(<<)
		GMTK_SWZ4_OP(>>)

		GMTK_SWZ4_ROP(*=)
		GMTK_SWZ4_ROP(/=)
		GMTK_SWZ4_ROP(+=)
		GMTK_SWZ4_ROP(-=)
		GMTK_SWZ4_ROP(|=)
		GMTK_SWZ4_ROP(&=)
		GMTK_SWZ4_ROP(^=)
		GMTK_SWZ4_ROP(%=)
		GMTK_SWZ4_ROP(<<=)
		GMTK_SWZ4_ROP(>>=)

	}; //! class swizzle3

	//////////////////////
	//! OUTPUT OPERATOR //
	//////////////////////

	template <int a, int b, int c, int d, typename V, typename T>
	inline std::ostream& operator<<(std::ostream& os, const swizzle4<a, b, c, d, V, T>& s)
	{
		os << vec<4, T>(s[a], s[b], s[c], s[d]);
		return os;
	}
	
	///////////////////////
	//! BINARY OPERATORS //
	///////////////////////
	
	GMTK_SWZ4_BOP(*)
	GMTK_SWZ4_BOP(/)
	GMTK_SWZ4_BOP(+)
	GMTK_SWZ4_BOP(-)
	GMTK_SWZ4_BOP(|)
	GMTK_SWZ4_BOP(&)
	GMTK_SWZ4_BOP(^)
	GMTK_SWZ4_BOP(%)
	GMTK_SWZ4_BOP(<<)
	GMTK_SWZ4_BOP(>>)

	GMTK_SWZ4_BROP(*=)
	GMTK_SWZ4_BROP(/=)
	GMTK_SWZ4_BROP(+=)
	GMTK_SWZ4_BROP(-=)
	GMTK_SWZ4_BROP( |= )
    GMTK_SWZ4_BROP( &= )
    GMTK_SWZ4_BROP( ^= )
    GMTK_SWZ4_BROP( %= )
    GMTK_SWZ4_BROP( <<= )
    GMTK_SWZ4_BROP( >>= )

}////

//

#undef GMTK_SWZ4_UOP
#undef GMTK_SWZ4_OP
#undef GMTK_SWZ4_ROP

//

#define GMTK_VEC4_SWIZZLES \
swz2 <0, 0> xx, rr, ss; \
swz2 <0, 1> xy, rg, st; \
swz2 <0, 2> xz, rb, sp; \
swz2 <0, 3> xw, ra, sq; \
swz2 <1, 0> yx, gr, ts; \
swz2 <1, 1> yy, gg, tt; \
swz2 <1, 2> yz, gb, tp; \
swz2 <1, 3> yw, ga, tq; \
swz2 <2, 0> zx, br, ps; \
swz2 <2, 1> zy, bg, pt; \
swz2 <2, 2> zz, bb, pp; \
swz2 <2, 3> zw, ba, pq; \
swz2 <3, 0> wx, ar, qs; \
swz2 <3, 1> wy, ag, qt; \
swz2 <3, 2> wz, ab, qp; \
swz2 <3, 3> ww, aa, qq; \
swz3 <0, 0, 0> xxx, rrr, sss; \
swz3 <0, 0, 1> xxy, rrg, sst; \
swz3 <0, 0, 2> xxz, rrb, ssp; \
swz3 <0, 0, 3> xxw, rra, ssq; \
swz3 <0, 1, 0> xyx, rgr, sts; \
swz3 <0, 1, 1> xyy, rgg, stt; \
swz3 <0, 1, 2> xyz, rgb, stp; \
swz3 <0, 1, 3> xyw, rga, stq; \
swz3 <0, 2, 0> xzx, rbr, sps; \
swz3 <0, 2, 1> xzy, rbg, spt; \
swz3 <0, 2, 2> xzz, rbb, spp; \
swz3 <0, 2, 3> xzw, rba, spq; \
swz3 <0, 3, 0> xwx, rar, sqs; \
swz3 <0, 3, 1> xwy, rag, sqt; \
swz3 <0, 3, 2> xwz, rab, sqp; \
swz3 <0, 3, 3> xww, raa, sqq; \
swz3 <1, 0, 0> yxx, grr, tss; \
swz3 <1, 0, 1> yxy, grg, tst; \
swz3 <1, 0, 2> yxz, grb, tsp; \
swz3 <1, 0, 3> yxw, gra, tsq; \
swz3 <1, 1, 0> yyx, ggr, tts; \
swz3 <1, 1, 1> yyy, ggg, ttt; \
swz3 <1, 1, 2> yyz, ggb, ttp; \
swz3 <1, 1, 3> yyw, gga, ttq; \
swz3 <1, 2, 0> yzx, gbr, tps; \
swz3 <1, 2, 1> yzy, gbg, tpt; \
swz3 <1, 2, 2> yzz, gbb, tpp; \
swz3 <1, 2, 3> yzw, gba, tpq; \
swz3 <1, 3, 0> ywx, gar, tqs; \
swz3 <1, 3, 1> ywy, gag, tqt; \
swz3 <1, 3, 2> ywz, gab, tqp; \
swz3 <1, 3, 3> yww, gaa, tqq; \
swz3 <2, 0, 0> zxx, brr, pss; \
swz3 <2, 0, 1> zxy, brg, pst; \
swz3 <2, 0, 2> zxz, brb, psp; \
swz3 <2, 0, 3> zxw, bra, psq; \
swz3 <2, 1, 0> zyx, bgr, pts; \
swz3 <2, 1, 1> zyy, bgg, ptt; \
swz3 <2, 1, 2> zyz, bgb, ptp; \
swz3 <2, 1, 3> zyw, bga, ptq; \
swz3 <2, 2, 0> zzx, bbr, pps; \
swz3 <2, 2, 1> zzy, bbg, ppt; \
swz3 <2, 2, 2> zzz, bbb, ppp; \
swz3 <2, 2, 3> zzw, bba, ppq; \
swz3 <2, 3, 0> zwx, bar, pqs; \
swz3 <2, 3, 1> zwy, bag, pqt; \
swz3 <2, 3, 2> zwz, bab, pqp; \
swz3 <2, 3, 3> zww, baa, pqq; \
swz3 <3, 0, 0> wxx, arr, qss; \
swz3 <3, 0, 1> wxy, arg, qst; \
swz3 <3, 0, 2> wxz, arb, qsp; \
swz3 <3, 0, 3> wxw, ara, qsq; \
swz3 <3, 1, 0> wyx, agr, qts; \
swz3 <3, 1, 1> wyy, agg, qtt; \
swz3 <3, 1, 2> wyz, agb, qtp; \
swz3 <3, 1, 3> wyw, aga, qtq; \
swz3 <3, 2, 0> wzx, abr, qps; \
swz3 <3, 2, 1> wzy, abg, qpt; \
swz3 <3, 2, 2> wzz, abb, qpp; \
swz3 <3, 2, 3> wzw, aba, qpq; \
swz3 <3, 3, 0> wwx, aar, qqs; \
swz3 <3, 3, 1> wwy, aag, qqt; \
swz3 <3, 3, 2> wwz, aab, qqp; \
swz3 <3, 3, 3> www, aaa, qqq; \
swz4 <0, 0, 0, 0> xxxx, rrrr, ssss; \
swz4 <0, 0, 0, 1> xxxy, rrrg, ssst; \
swz4 <0, 0, 0, 2> xxxz, rrrb, sssp; \
swz4 <0, 0, 0, 3> xxxw, rrra, sssq; \
swz4 <0, 0, 1, 0> xxyx, rrgr, ssts; \
swz4 <0, 0, 1, 1> xxyy, rrgg, sstt; \
swz4 <0, 0, 1, 2> xxyz, rrgb, sstp; \
swz4 <0, 0, 1, 3> xxyw, rrga, sstq; \
swz4 <0, 0, 2, 0> xxzx, rrbr, ssps; \
swz4 <0, 0, 2, 1> xxzy, rrbg, sspt; \
swz4 <0, 0, 2, 2> xxzz, rrbb, sspp; \
swz4 <0, 0, 2, 3> xxzw, rrba, sspq; \
swz4 <0, 0, 3, 0> xxwx, rrar, ssqs; \
swz4 <0, 0, 3, 1> xxwy, rrag, ssqt; \
swz4 <0, 0, 3, 2> xxwz, rrab, ssqp; \
swz4 <0, 0, 3, 3> xxww, rraa, ssqq; \
swz4 <0, 1, 0, 0> xyxx, rgrr, stss; \
swz4 <0, 1, 0, 1> xyxy, rgrg, stst; \
swz4 <0, 1, 0, 2> xyxz, rgrb, stsp; \
swz4 <0, 1, 0, 3> xyxw, rgra, stsq; \
swz4 <0, 1, 1, 0> xyyx, rggr, stts; \
swz4 <0, 1, 1, 1> xyyy, rggg, sttt; \
swz4 <0, 1, 1, 2> xyyz, rggb, sttp; \
swz4 <0, 1, 1, 3> xyyw, rgga, sttq; \
swz4 <0, 1, 2, 0> xyzx, rgbr, stps; \
swz4 <0, 1, 2, 1> xyzy, rgbg, stpt; \
swz4 <0, 1, 2, 2> xyzz, rgbb, stpp; \
swz4 <0, 1, 2, 3> xyzw, rgba, stpq; \
swz4 <0, 1, 3, 0> xywx, rgar, stqs; \
swz4 <0, 1, 3, 1> xywy, rgag, stqt; \
swz4 <0, 1, 3, 2> xywz, rgab, stqp; \
swz4 <0, 1, 3, 3> xyww, rgaa, stqq; \
swz4 <0, 2, 0, 0> xzxx, rbrr, spss; \
swz4 <0, 2, 0, 1> xzxy, rbrg, spst; \
swz4 <0, 2, 0, 2> xzxz, rbrb, spsp; \
swz4 <0, 2, 0, 3> xzxw, rbra, spsq; \
swz4 <0, 2, 1, 0> xzyx, rbgr, spts; \
swz4 <0, 2, 1, 1> xzyy, rbgg, sptt; \
swz4 <0, 2, 1, 2> xzyz, rbgb, sptp; \
swz4 <0, 2, 1, 3> xzyw, rbga, sptq; \
swz4 <0, 2, 2, 0> xzzx, rbbr, spps; \
swz4 <0, 2, 2, 1> xzzy, rbbg, sppt; \
swz4 <0, 2, 2, 2> xzzz, rbbb, sppp; \
swz4 <0, 2, 2, 3> xzzw, rbba, sppq; \
swz4 <0, 2, 3, 0> xzwx, rbar, spqs; \
swz4 <0, 2, 3, 1> xzwy, rbag, spqt; \
swz4 <0, 2, 3, 2> xzwz, rbab, spqp; \
swz4 <0, 2, 3, 3> xzww, rbaa, spqq; \
swz4 <0, 3, 0, 0> xwxx, rarr, sqss; \
swz4 <0, 3, 0, 1> xwxy, rarg, sqst; \
swz4 <0, 3, 0, 2> xwxz, rarb, sqsp; \
swz4 <0, 3, 0, 3> xwxw, rara, sqsq; \
swz4 <0, 3, 1, 0> xwyx, ragr, sqts; \
swz4 <0, 3, 1, 1> xwyy, ragg, sqtt; \
swz4 <0, 3, 1, 2> xwyz, ragb, sqtp; \
swz4 <0, 3, 1, 3> xwyw, raga, sqtq; \
swz4 <0, 3, 2, 0> xwzx, rabr, sqps; \
swz4 <0, 3, 2, 1> xwzy, rabg, sqpt; \
swz4 <0, 3, 2, 2> xwzz, rabb, sqpp; \
swz4 <0, 3, 2, 3> xwzw, raba, sqpq; \
swz4 <0, 3, 3, 0> xwwx, raar, sqqs; \
swz4 <0, 3, 3, 1> xwwy, raag, sqqt; \
swz4 <0, 3, 3, 2> xwwz, raab, sqqp; \
swz4 <0, 3, 3, 3> xwww, raaa, sqqq; \
swz4 <1, 0, 0, 0> yxxx, grrr, tsss; \
swz4 <1, 0, 0, 1> yxxy, grrg, tsst; \
swz4 <1, 0, 0, 2> yxxz, grrb, tssp; \
swz4 <1, 0, 0, 3> yxxw, grra, tssq; \
swz4 <1, 0, 1, 0> yxyx, grgr, tsts; \
swz4 <1, 0, 1, 1> yxyy, grgg, tstt; \
swz4 <1, 0, 1, 2> yxyz, grgb, tstp; \
swz4 <1, 0, 1, 3> yxyw, grga, tstq; \
swz4 <1, 0, 2, 0> yxzx, grbr, tsps; \
swz4 <1, 0, 2, 1> yxzy, grbg, tspt; \
swz4 <1, 0, 2, 2> yxzz, grbb, tspp; \
swz4 <1, 0, 2, 3> yxzw, grba, tspq; \
swz4 <1, 0, 3, 0> yxwx, grar, tsqs; \
swz4 <1, 0, 3, 1> yxwy, grag, tsqt; \
swz4 <1, 0, 3, 2> yxwz, grab, tsqp; \
swz4 <1, 0, 3, 3> yxww, graa, tsqq; \
swz4 <1, 1, 0, 0> yyxx, ggrr, ttss; \
swz4 <1, 1, 0, 1> yyxy, ggrg, ttst; \
swz4 <1, 1, 0, 2> yyxz, ggrb, ttsp; \
swz4 <1, 1, 0, 3> yyxw, ggra, ttsq; \
swz4 <1, 1, 1, 0> yyyx, gggr, ttts; \
swz4 <1, 1, 1, 1> yyyy, gggg, tttt; \
swz4 <1, 1, 1, 2> yyyz, gggb, tttp; \
swz4 <1, 1, 1, 3> yyyw, ggga, tttq; \
swz4 <1, 1, 2, 0> yyzx, ggbr, ttps; \
swz4 <1, 1, 2, 1> yyzy, ggbg, ttpt; \
swz4 <1, 1, 2, 2> yyzz, ggbb, ttpp; \
swz4 <1, 1, 2, 3> yyzw, ggba, ttpq; \
swz4 <1, 1, 3, 0> yywx, ggar, ttqs; \
swz4 <1, 1, 3, 1> yywy, ggag, ttqt; \
swz4 <1, 1, 3, 2> yywz, ggab, ttqp; \
swz4 <1, 1, 3, 3> yyww, ggaa, ttqq; \
swz4 <1, 2, 0, 0> yzxx, gbrr, tpss; \
swz4 <1, 2, 0, 1> yzxy, gbrg, tpst; \
swz4 <1, 2, 0, 2> yzxz, gbrb, tpsp; \
swz4 <1, 2, 0, 3> yzxw, gbra, tpsq; \
swz4 <1, 2, 1, 0> yzyx, gbgr, tpts; \
swz4 <1, 2, 1, 1> yzyy, gbgg, tptt; \
swz4 <1, 2, 1, 2> yzyz, gbgb, tptp; \
swz4 <1, 2, 1, 3> yzyw, gbga, tptq; \
swz4 <1, 2, 2, 0> yzzx, gbbr, tpps; \
swz4 <1, 2, 2, 1> yzzy, gbbg, tppt; \
swz4 <1, 2, 2, 2> yzzz, gbbb, tppp; \
swz4 <1, 2, 2, 3> yzzw, gbba, tppq; \
swz4 <1, 2, 3, 0> yzwx, gbar, tpqs; \
swz4 <1, 2, 3, 1> yzwy, gbag, tpqt; \
swz4 <1, 2, 3, 2> yzwz, gbab, tpqp; \
swz4 <1, 2, 3, 3> yzww, gbaa, tpqq; \
swz4 <1, 3, 0, 0> ywxx, garr, tqss; \
swz4 <1, 3, 0, 1> ywxy, garg, tqst; \
swz4 <1, 3, 0, 2> ywxz, garb, tqsp; \
swz4 <1, 3, 0, 3> ywxw, gara, tqsq; \
swz4 <1, 3, 1, 0> ywyx, gagr, tqts; \
swz4 <1, 3, 1, 1> ywyy, gagg, tqtt; \
swz4 <1, 3, 1, 2> ywyz, gagb, tqtp; \
swz4 <1, 3, 1, 3> ywyw, gaga, tqtq; \
swz4 <1, 3, 2, 0> ywzx, gabr, tqps; \
swz4 <1, 3, 2, 1> ywzy, gabg, tqpt; \
swz4 <1, 3, 2, 2> ywzz, gabb, tqpp; \
swz4 <1, 3, 2, 3> ywzw, gaba, tqpq; \
swz4 <1, 3, 3, 0> ywwx, gaar, tqqs; \
swz4 <1, 3, 3, 1> ywwy, gaag, tqqt; \
swz4 <1, 3, 3, 2> ywwz, gaab, tqqp; \
swz4 <1, 3, 3, 3> ywww, gaaa, tqqq; \
swz4 <2, 0, 0, 0> zxxx, brrr, psss; \
swz4 <2, 0, 0, 1> zxxy, brrg, psst; \
swz4 <2, 0, 0, 2> zxxz, brrb, pssp; \
swz4 <2, 0, 0, 3> zxxw, brra, pssq; \
swz4 <2, 0, 1, 0> zxyx, brgr, psts; \
swz4 <2, 0, 1, 1> zxyy, brgg, pstt; \
swz4 <2, 0, 1, 2> zxyz, brgb, pstp; \
swz4 <2, 0, 1, 3> zxyw, brga, pstq; \
swz4 <2, 0, 2, 0> zxzx, brbr, psps; \
swz4 <2, 0, 2, 1> zxzy, brbg, pspt; \
swz4 <2, 0, 2, 2> zxzz, brbb, pspp; \
swz4 <2, 0, 2, 3> zxzw, brba, pspq; \
swz4 <2, 0, 3, 0> zxwx, brar, psqs; \
swz4 <2, 0, 3, 1> zxwy, brag, psqt; \
swz4 <2, 0, 3, 2> zxwz, brab, psqp; \
swz4 <2, 0, 3, 3> zxww, braa, psqq; \
swz4 <2, 1, 0, 0> zyxx, bgrr, ptss; \
swz4 <2, 1, 0, 1> zyxy, bgrg, ptst; \
swz4 <2, 1, 0, 2> zyxz, bgrb, ptsp; \
swz4 <2, 1, 0, 3> zyxw, bgra, ptsq; \
swz4 <2, 1, 1, 0> zyyx, bggr, ptts; \
swz4 <2, 1, 1, 1> zyyy, bggg, pttt; \
swz4 <2, 1, 1, 2> zyyz, bggb, pttp; \
swz4 <2, 1, 1, 3> zyyw, bgga, pttq; \
swz4 <2, 1, 2, 0> zyzx, bgbr, ptps; \
swz4 <2, 1, 2, 1> zyzy, bgbg, ptpt; \
swz4 <2, 1, 2, 2> zyzz, bgbb, ptpp; \
swz4 <2, 1, 2, 3> zyzw, bgba, ptpq; \
swz4 <2, 1, 3, 0> zywx, bgar, ptqs; \
swz4 <2, 1, 3, 1> zywy, bgag, ptqt; \
swz4 <2, 1, 3, 2> zywz, bgab, ptqp; \
swz4 <2, 1, 3, 3> zyww, bgaa, ptqq; \
swz4 <2, 2, 0, 0> zzxx, bbrr, ppss; \
swz4 <2, 2, 0, 1> zzxy, bbrg, ppst; \
swz4 <2, 2, 0, 2> zzxz, bbrb, ppsp; \
swz4 <2, 2, 0, 3> zzxw, bbra, ppsq; \
swz4 <2, 2, 1, 0> zzyx, bbgr, ppts; \
swz4 <2, 2, 1, 1> zzyy, bbgg, pptt; \
swz4 <2, 2, 1, 2> zzyz, bbgb, pptp; \
swz4 <2, 2, 1, 3> zzyw, bbga, pptq; \
swz4 <2, 2, 2, 0> zzzx, bbbr, ppps; \
swz4 <2, 2, 2, 1> zzzy, bbbg, pppt; \
swz4 <2, 2, 2, 2> zzzz, bbbb, pppp; \
swz4 <2, 2, 2, 3> zzzw, bbba, pppq; \
swz4 <2, 2, 3, 0> zzwx, bbar, ppqs; \
swz4 <2, 2, 3, 1> zzwy, bbag, ppqt; \
swz4 <2, 2, 3, 2> zzwz, bbab, ppqp; \
swz4 <2, 2, 3, 3> zzww, bbaa, ppqq; \
swz4 <2, 3, 0, 0> zwxx, barr, pqss; \
swz4 <2, 3, 0, 1> zwxy, barg, pqst; \
swz4 <2, 3, 0, 2> zwxz, barb, pqsp; \
swz4 <2, 3, 0, 3> zwxw, bara, pqsq; \
swz4 <2, 3, 1, 0> zwyx, bagr, pqts; \
swz4 <2, 3, 1, 1> zwyy, bagg, pqtt; \
swz4 <2, 3, 1, 2> zwyz, bagb, pqtp; \
swz4 <2, 3, 1, 3> zwyw, baga, pqtq; \
swz4 <2, 3, 2, 0> zwzx, babr, pqps; \
swz4 <2, 3, 2, 1> zwzy, babg, pqpt; \
swz4 <2, 3, 2, 2> zwzz, babb, pqpp; \
swz4 <2, 3, 2, 3> zwzw, baba, pqpq; \
swz4 <2, 3, 3, 0> zwwx, baar, pqqs; \
swz4 <2, 3, 3, 1> zwwy, baag, pqqt; \
swz4 <2, 3, 3, 2> zwwz, baab, pqqp; \
swz4 <2, 3, 3, 3> zwww, baaa, pqqq; \
swz4 <3, 0, 0, 0> wxxx, arrr, qsss; \
swz4 <3, 0, 0, 1> wxxy, arrg, qsst; \
swz4 <3, 0, 0, 2> wxxz, arrb, qssp; \
swz4 <3, 0, 0, 3> wxxw, arra, qssq; \
swz4 <3, 0, 1, 0> wxyx, argr, qsts; \
swz4 <3, 0, 1, 1> wxyy, argg, qstt; \
swz4 <3, 0, 1, 2> wxyz, argb, qstp; \
swz4 <3, 0, 1, 3> wxyw, arga, qstq; \
swz4 <3, 0, 2, 0> wxzx, arbr, qsps; \
swz4 <3, 0, 2, 1> wxzy, arbg, qspt; \
swz4 <3, 0, 2, 2> wxzz, arbb, qspp; \
swz4 <3, 0, 2, 3> wxzw, arba, qspq; \
swz4 <3, 0, 3, 0> wxwx, arar, qsqs; \
swz4 <3, 0, 3, 1> wxwy, arag, qsqt; \
swz4 <3, 0, 3, 2> wxwz, arab, qsqp; \
swz4 <3, 0, 3, 3> wxww, araa, qsqq; \
swz4 <3, 1, 0, 0> wyxx, agrr, qtss; \
swz4 <3, 1, 0, 1> wyxy, agrg, qtst; \
swz4 <3, 1, 0, 2> wyxz, agrb, qtsp; \
swz4 <3, 1, 0, 3> wyxw, agra, qtsq; \
swz4 <3, 1, 1, 0> wyyx, aggr, qtts; \
swz4 <3, 1, 1, 1> wyyy, aggg, qttt; \
swz4 <3, 1, 1, 2> wyyz, aggb, qttp; \
swz4 <3, 1, 1, 3> wyyw, agga, qttq; \
swz4 <3, 1, 2, 0> wyzx, agbr, qtps; \
swz4 <3, 1, 2, 1> wyzy, agbg, qtpt; \
swz4 <3, 1, 2, 2> wyzz, agbb, qtpp; \
swz4 <3, 1, 2, 3> wyzw, agba, qtpq; \
swz4 <3, 1, 3, 0> wywx, agar, qtqs; \
swz4 <3, 1, 3, 1> wywy, agag, qtqt; \
swz4 <3, 1, 3, 2> wywz, agab, qtqp; \
swz4 <3, 1, 3, 3> wyww, agaa, qtqq; \
swz4 <3, 2, 0, 0> wzxx, abrr, qpss; \
swz4 <3, 2, 0, 1> wzxy, abrg, qpst; \
swz4 <3, 2, 0, 2> wzxz, abrb, qpsp; \
swz4 <3, 2, 0, 3> wzxw, abra, qpsq; \
swz4 <3, 2, 1, 0> wzyx, abgr, qpts; \
swz4 <3, 2, 1, 1> wzyy, abgg, qptt; \
swz4 <3, 2, 1, 2> wzyz, abgb, qptp; \
swz4 <3, 2, 1, 3> wzyw, abga, qptq; \
swz4 <3, 2, 2, 0> wzzx, abbr, qpps; \
swz4 <3, 2, 2, 1> wzzy, abbg, qppt; \
swz4 <3, 2, 2, 2> wzzz, abbb, qppp; \
swz4 <3, 2, 2, 3> wzzw, abba, qppq; \
swz4 <3, 2, 3, 0> wzwx, abar, qpqs; \
swz4 <3, 2, 3, 1> wzwy, abag, qpqt; \
swz4 <3, 2, 3, 2> wzwz, abab, qpqp; \
swz4 <3, 2, 3, 3> wzww, abaa, qpqq; \
swz4 <3, 3, 0, 0> wwxx, aarr, qqss; \
swz4 <3, 3, 0, 1> wwxy, aarg, qqst; \
swz4 <3, 3, 0, 2> wwxz, aarb, qqsp; \
swz4 <3, 3, 0, 3> wwxw, aara, qqsq; \
swz4 <3, 3, 1, 0> wwyx, aagr, qqts; \
swz4 <3, 3, 1, 1> wwyy, aagg, qqtt; \
swz4 <3, 3, 1, 2> wwyz, aagb, qqtp; \
swz4 <3, 3, 1, 3> wwyw, aaga, qqtq; \
swz4 <3, 3, 2, 0> wwzx, aabr, qqps; \
swz4 <3, 3, 2, 1> wwzy, aabg, qqpt; \
swz4 <3, 3, 2, 2> wwzz, aabb, qqpp; \
swz4 <3, 3, 2, 3> wwzw, aaba, qqpq; \
swz4 <3, 3, 3, 0> wwwx, aaar, qqqs; \
swz4 <3, 3, 3, 1> wwwy, aaag, qqqt; \
swz4 <3, 3, 3, 2> wwwz, aaab, qqqp; \
swz4 <3, 3, 3, 3> wwww, aaaa, qqqq; \

//

#endif //_GMTK_SWIZZLE4_H_
