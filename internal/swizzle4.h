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

		GMTK_SWZ4_ROP(=)

		GMTK_SWZ4_OP(*)
		GMTK_SWZ4_OP(/)
		GMTK_SWZ4_OP(+)
		GMTK_SWZ4_OP(-)

		GMTK_SWZ4_ROP(*=)
		GMTK_SWZ4_ROP(/=)
		GMTK_SWZ4_ROP(+=)
		GMTK_SWZ4_ROP(-=)

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

	GMTK_SWZ4_BROP(*=)
	GMTK_SWZ4_BROP(/=)
	GMTK_SWZ4_BROP(+=)
	GMTK_SWZ4_BROP(-=)

}////

//

#undef GMTK_SWZ4_UOP
#undef GMTK_SWZ4_OP
#undef GMTK_SWZ4_ROP

//

#define GMTK_VEC4_SWIZZLES \
swz2 <0, 0> xx, rr, uu; \
swz2 <0, 1> xy, rg, uv; \
swz2 <0, 2> xz, rb, us; \
swz2 <0, 3> xw, ra, ut; \
swz2 <1, 0> yx, gr, vu; \
swz2 <1, 1> yy, gg, vv; \
swz2 <1, 2> yz, gb, vs; \
swz2 <1, 3> yw, ga, vt; \
swz2 <2, 0> zx, br, su; \
swz2 <2, 1> zy, bg, sv; \
swz2 <2, 2> zz, bb, ss; \
swz2 <2, 3> zw, ba, st; \
swz2 <3, 0> wx, ar, tu; \
swz2 <3, 1> wy, ag, tv; \
swz2 <3, 2> wz, ab, ts; \
swz2 <3, 3> ww, aa, tt; \
swz3 <0, 0, 0> xxx, rrr, uuu; \
swz3 <0, 0, 1> xxy, rrg, uuv; \
swz3 <0, 0, 2> xxz, rrb, uus; \
swz3 <0, 0, 3> xxw, rra, uut; \
swz3 <0, 1, 0> xyx, rgr, uvu; \
swz3 <0, 1, 1> xyy, rgg, uvv; \
swz3 <0, 1, 2> xyz, rgb, uvs; \
swz3 <0, 1, 3> xyw, rga, uvt; \
swz3 <0, 2, 0> xzx, rbr, usu; \
swz3 <0, 2, 1> xzy, rbg, usv; \
swz3 <0, 2, 2> xzz, rbb, uss; \
swz3 <0, 2, 3> xzw, rba, ust; \
swz3 <0, 3, 0> xwx, rar, utu; \
swz3 <0, 3, 1> xwy, rag, utv; \
swz3 <0, 3, 2> xwz, rab, uts; \
swz3 <0, 3, 3> xww, raa, utt; \
swz3 <1, 0, 0> yxx, grr, vuu; \
swz3 <1, 0, 1> yxy, grg, vuv; \
swz3 <1, 0, 2> yxz, grb, vus; \
swz3 <1, 0, 3> yxw, gra, vut; \
swz3 <1, 1, 0> yyx, ggr, vvu; \
swz3 <1, 1, 1> yyy, ggg, vvv; \
swz3 <1, 1, 2> yyz, ggb, vvs; \
swz3 <1, 1, 3> yyw, gga, vvt; \
swz3 <1, 2, 0> yzx, gbr, vsu; \
swz3 <1, 2, 1> yzy, gbg, vsv; \
swz3 <1, 2, 2> yzz, gbb, vss; \
swz3 <1, 2, 3> yzw, gba, vst; \
swz3 <1, 3, 0> ywx, gar, vtu; \
swz3 <1, 3, 1> ywy, gag, vtv; \
swz3 <1, 3, 2> ywz, gab, vts; \
swz3 <1, 3, 3> yww, gaa, vtt; \
swz3 <2, 0, 0> zxx, brr, suu; \
swz3 <2, 0, 1> zxy, brg, suv; \
swz3 <2, 0, 2> zxz, brb, sus; \
swz3 <2, 0, 3> zxw, bra, sut; \
swz3 <2, 1, 0> zyx, bgr, svu; \
swz3 <2, 1, 1> zyy, bgg, svv; \
swz3 <2, 1, 2> zyz, bgb, svs; \
swz3 <2, 1, 3> zyw, bga, svt; \
swz3 <2, 2, 0> zzx, bbr, ssu; \
swz3 <2, 2, 1> zzy, bbg, ssv; \
swz3 <2, 2, 2> zzz, bbb, sss; \
swz3 <2, 2, 3> zzw, bba, sst; \
swz3 <2, 3, 0> zwx, bar, stu; \
swz3 <2, 3, 1> zwy, bag, stv; \
swz3 <2, 3, 2> zwz, bab, sts; \
swz3 <2, 3, 3> zww, baa, stt; \
swz3 <3, 0, 0> wxx, arr, tuu; \
swz3 <3, 0, 1> wxy, arg, tuv; \
swz3 <3, 0, 2> wxz, arb, tus; \
swz3 <3, 0, 3> wxw, ara, tut; \
swz3 <3, 1, 0> wyx, agr, tvu; \
swz3 <3, 1, 1> wyy, agg, tvv; \
swz3 <3, 1, 2> wyz, agb, tvs; \
swz3 <3, 1, 3> wyw, aga, tvt; \
swz3 <3, 2, 0> wzx, abr, tsu; \
swz3 <3, 2, 1> wzy, abg, tsv; \
swz3 <3, 2, 2> wzz, abb, tss; \
swz3 <3, 2, 3> wzw, aba, tst; \
swz3 <3, 3, 0> wwx, aar, ttu; \
swz3 <3, 3, 1> wwy, aag, ttv; \
swz3 <3, 3, 2> wwz, aab, tts; \
swz3 <3, 3, 3> www, aaa, ttt; \
swz4 <0, 0, 0, 0> xxxx, rrrr, uuuu; \
swz4 <0, 0, 0, 1> xxxy, rrrg, uuuv; \
swz4 <0, 0, 0, 2> xxxz, rrrb, uuus; \
swz4 <0, 0, 0, 3> xxxw, rrra, uuut; \
swz4 <0, 0, 1, 0> xxyx, rrgr, uuvu; \
swz4 <0, 0, 1, 1> xxyy, rrgg, uuvv; \
swz4 <0, 0, 1, 2> xxyz, rrgb, uuvs; \
swz4 <0, 0, 1, 3> xxyw, rrga, uuvt; \
swz4 <0, 0, 2, 0> xxzx, rrbr, uusu; \
swz4 <0, 0, 2, 1> xxzy, rrbg, uusv; \
swz4 <0, 0, 2, 2> xxzz, rrbb, uuss; \
swz4 <0, 0, 2, 3> xxzw, rrba, uust; \
swz4 <0, 0, 3, 0> xxwx, rrar, uutu; \
swz4 <0, 0, 3, 1> xxwy, rrag, uutv; \
swz4 <0, 0, 3, 2> xxwz, rrab, uuts; \
swz4 <0, 0, 3, 3> xxww, rraa, uutt; \
swz4 <0, 1, 0, 0> xyxx, rgrr, uvuu; \
swz4 <0, 1, 0, 1> xyxy, rgrg, uvuv; \
swz4 <0, 1, 0, 2> xyxz, rgrb, uvus; \
swz4 <0, 1, 0, 3> xyxw, rgra, uvut; \
swz4 <0, 1, 1, 0> xyyx, rggr, uvvu; \
swz4 <0, 1, 1, 1> xyyy, rggg, uvvv; \
swz4 <0, 1, 1, 2> xyyz, rggb, uvvs; \
swz4 <0, 1, 1, 3> xyyw, rgga, uvvt; \
swz4 <0, 1, 2, 0> xyzx, rgbr, uvsu; \
swz4 <0, 1, 2, 1> xyzy, rgbg, uvsv; \
swz4 <0, 1, 2, 2> xyzz, rgbb, uvss; \
swz4 <0, 1, 2, 3> xyzw, rgba, uvst; \
swz4 <0, 1, 3, 0> xywx, rgar, uvtu; \
swz4 <0, 1, 3, 1> xywy, rgag, uvtv; \
swz4 <0, 1, 3, 2> xywz, rgab, uvts; \
swz4 <0, 1, 3, 3> xyww, rgaa, uvtt; \
swz4 <0, 2, 0, 0> xzxx, rbrr, usuu; \
swz4 <0, 2, 0, 1> xzxy, rbrg, usuv; \
swz4 <0, 2, 0, 2> xzxz, rbrb, usus; \
swz4 <0, 2, 0, 3> xzxw, rbra, usut; \
swz4 <0, 2, 1, 0> xzyx, rbgr, usvu; \
swz4 <0, 2, 1, 1> xzyy, rbgg, usvv; \
swz4 <0, 2, 1, 2> xzyz, rbgb, usvs; \
swz4 <0, 2, 1, 3> xzyw, rbga, usvt; \
swz4 <0, 2, 2, 0> xzzx, rbbr, ussu; \
swz4 <0, 2, 2, 1> xzzy, rbbg, ussv; \
swz4 <0, 2, 2, 2> xzzz, rbbb, usss; \
swz4 <0, 2, 2, 3> xzzw, rbba, usst; \
swz4 <0, 2, 3, 0> xzwx, rbar, ustu; \
swz4 <0, 2, 3, 1> xzwy, rbag, ustv; \
swz4 <0, 2, 3, 2> xzwz, rbab, usts; \
swz4 <0, 2, 3, 3> xzww, rbaa, ustt; \
swz4 <0, 3, 0, 0> xwxx, rarr, utuu; \
swz4 <0, 3, 0, 1> xwxy, rarg, utuv; \
swz4 <0, 3, 0, 2> xwxz, rarb, utus; \
swz4 <0, 3, 0, 3> xwxw, rara, utut; \
swz4 <0, 3, 1, 0> xwyx, ragr, utvu; \
swz4 <0, 3, 1, 1> xwyy, ragg, utvv; \
swz4 <0, 3, 1, 2> xwyz, ragb, utvs; \
swz4 <0, 3, 1, 3> xwyw, raga, utvt; \
swz4 <0, 3, 2, 0> xwzx, rabr, utsu; \
swz4 <0, 3, 2, 1> xwzy, rabg, utsv; \
swz4 <0, 3, 2, 2> xwzz, rabb, utss; \
swz4 <0, 3, 2, 3> xwzw, raba, utst; \
swz4 <0, 3, 3, 0> xwwx, raar, uttu; \
swz4 <0, 3, 3, 1> xwwy, raag, uttv; \
swz4 <0, 3, 3, 2> xwwz, raab, utts; \
swz4 <0, 3, 3, 3> xwww, raaa, uttt; \
swz4 <1, 0, 0, 0> yxxx, grrr, vuuu; \
swz4 <1, 0, 0, 1> yxxy, grrg, vuuv; \
swz4 <1, 0, 0, 2> yxxz, grrb, vuus; \
swz4 <1, 0, 0, 3> yxxw, grra, vuut; \
swz4 <1, 0, 1, 0> yxyx, grgr, vuvu; \
swz4 <1, 0, 1, 1> yxyy, grgg, vuvv; \
swz4 <1, 0, 1, 2> yxyz, grgb, vuvs; \
swz4 <1, 0, 1, 3> yxyw, grga, vuvt; \
swz4 <1, 0, 2, 0> yxzx, grbr, vusu; \
swz4 <1, 0, 2, 1> yxzy, grbg, vusv; \
swz4 <1, 0, 2, 2> yxzz, grbb, vuss; \
swz4 <1, 0, 2, 3> yxzw, grba, vust; \
swz4 <1, 0, 3, 0> yxwx, grar, vutu; \
swz4 <1, 0, 3, 1> yxwy, grag, vutv; \
swz4 <1, 0, 3, 2> yxwz, grab, vuts; \
swz4 <1, 0, 3, 3> yxww, graa, vutt; \
swz4 <1, 1, 0, 0> yyxx, ggrr, vvuu; \
swz4 <1, 1, 0, 1> yyxy, ggrg, vvuv; \
swz4 <1, 1, 0, 2> yyxz, ggrb, vvus; \
swz4 <1, 1, 0, 3> yyxw, ggra, vvut; \
swz4 <1, 1, 1, 0> yyyx, gggr, vvvu; \
swz4 <1, 1, 1, 1> yyyy, gggg, vvvv; \
swz4 <1, 1, 1, 2> yyyz, gggb, vvvs; \
swz4 <1, 1, 1, 3> yyyw, ggga, vvvt; \
swz4 <1, 1, 2, 0> yyzx, ggbr, vvsu; \
swz4 <1, 1, 2, 1> yyzy, ggbg, vvsv; \
swz4 <1, 1, 2, 2> yyzz, ggbb, vvss; \
swz4 <1, 1, 2, 3> yyzw, ggba, vvst; \
swz4 <1, 1, 3, 0> yywx, ggar, vvtu; \
swz4 <1, 1, 3, 1> yywy, ggag, vvtv; \
swz4 <1, 1, 3, 2> yywz, ggab, vvts; \
swz4 <1, 1, 3, 3> yyww, ggaa, vvtt; \
swz4 <1, 2, 0, 0> yzxx, gbrr, vsuu; \
swz4 <1, 2, 0, 1> yzxy, gbrg, vsuv; \
swz4 <1, 2, 0, 2> yzxz, gbrb, vsus; \
swz4 <1, 2, 0, 3> yzxw, gbra, vsut; \
swz4 <1, 2, 1, 0> yzyx, gbgr, vsvu; \
swz4 <1, 2, 1, 1> yzyy, gbgg, vsvv; \
swz4 <1, 2, 1, 2> yzyz, gbgb, vsvs; \
swz4 <1, 2, 1, 3> yzyw, gbga, vsvt; \
swz4 <1, 2, 2, 0> yzzx, gbbr, vssu; \
swz4 <1, 2, 2, 1> yzzy, gbbg, vssv; \
swz4 <1, 2, 2, 2> yzzz, gbbb, vsss; \
swz4 <1, 2, 2, 3> yzzw, gbba, vsst; \
swz4 <1, 2, 3, 0> yzwx, gbar, vstu; \
swz4 <1, 2, 3, 1> yzwy, gbag, vstv; \
swz4 <1, 2, 3, 2> yzwz, gbab, vsts; \
swz4 <1, 2, 3, 3> yzww, gbaa, vstt; \
swz4 <1, 3, 0, 0> ywxx, garr, vtuu; \
swz4 <1, 3, 0, 1> ywxy, garg, vtuv; \
swz4 <1, 3, 0, 2> ywxz, garb, vtus; \
swz4 <1, 3, 0, 3> ywxw, gara, vtut; \
swz4 <1, 3, 1, 0> ywyx, gagr, vtvu; \
swz4 <1, 3, 1, 1> ywyy, gagg, vtvv; \
swz4 <1, 3, 1, 2> ywyz, gagb, vtvs; \
swz4 <1, 3, 1, 3> ywyw, gaga, vtvt; \
swz4 <1, 3, 2, 0> ywzx, gabr, vtsu; \
swz4 <1, 3, 2, 1> ywzy, gabg, vtsv; \
swz4 <1, 3, 2, 2> ywzz, gabb, vtss; \
swz4 <1, 3, 2, 3> ywzw, gaba, vtst; \
swz4 <1, 3, 3, 0> ywwx, gaar, vttu; \
swz4 <1, 3, 3, 1> ywwy, gaag, vttv; \
swz4 <1, 3, 3, 2> ywwz, gaab, vtts; \
swz4 <1, 3, 3, 3> ywww, gaaa, vttt; \
swz4 <2, 0, 0, 0> zxxx, brrr, suuu; \
swz4 <2, 0, 0, 1> zxxy, brrg, suuv; \
swz4 <2, 0, 0, 2> zxxz, brrb, suus; \
swz4 <2, 0, 0, 3> zxxw, brra, suut; \
swz4 <2, 0, 1, 0> zxyx, brgr, suvu; \
swz4 <2, 0, 1, 1> zxyy, brgg, suvv; \
swz4 <2, 0, 1, 2> zxyz, brgb, suvs; \
swz4 <2, 0, 1, 3> zxyw, brga, suvt; \
swz4 <2, 0, 2, 0> zxzx, brbr, susu; \
swz4 <2, 0, 2, 1> zxzy, brbg, susv; \
swz4 <2, 0, 2, 2> zxzz, brbb, suss; \
swz4 <2, 0, 2, 3> zxzw, brba, sust; \
swz4 <2, 0, 3, 0> zxwx, brar, sutu; \
swz4 <2, 0, 3, 1> zxwy, brag, sutv; \
swz4 <2, 0, 3, 2> zxwz, brab, suts; \
swz4 <2, 0, 3, 3> zxww, braa, sutt; \
swz4 <2, 1, 0, 0> zyxx, bgrr, svuu; \
swz4 <2, 1, 0, 1> zyxy, bgrg, svuv; \
swz4 <2, 1, 0, 2> zyxz, bgrb, svus; \
swz4 <2, 1, 0, 3> zyxw, bgra, svut; \
swz4 <2, 1, 1, 0> zyyx, bggr, svvu; \
swz4 <2, 1, 1, 1> zyyy, bggg, svvv; \
swz4 <2, 1, 1, 2> zyyz, bggb, svvs; \
swz4 <2, 1, 1, 3> zyyw, bgga, svvt; \
swz4 <2, 1, 2, 0> zyzx, bgbr, svsu; \
swz4 <2, 1, 2, 1> zyzy, bgbg, svsv; \
swz4 <2, 1, 2, 2> zyzz, bgbb, svss; \
swz4 <2, 1, 2, 3> zyzw, bgba, svst; \
swz4 <2, 1, 3, 0> zywx, bgar, svtu; \
swz4 <2, 1, 3, 1> zywy, bgag, svtv; \
swz4 <2, 1, 3, 2> zywz, bgab, svts; \
swz4 <2, 1, 3, 3> zyww, bgaa, svtt; \
swz4 <2, 2, 0, 0> zzxx, bbrr, ssuu; \
swz4 <2, 2, 0, 1> zzxy, bbrg, ssuv; \
swz4 <2, 2, 0, 2> zzxz, bbrb, ssus; \
swz4 <2, 2, 0, 3> zzxw, bbra, ssut; \
swz4 <2, 2, 1, 0> zzyx, bbgr, ssvu; \
swz4 <2, 2, 1, 1> zzyy, bbgg, ssvv; \
swz4 <2, 2, 1, 2> zzyz, bbgb, ssvs; \
swz4 <2, 2, 1, 3> zzyw, bbga, ssvt; \
swz4 <2, 2, 2, 0> zzzx, bbbr, sssu; \
swz4 <2, 2, 2, 1> zzzy, bbbg, sssv; \
swz4 <2, 2, 2, 2> zzzz, bbbb, ssss; \
swz4 <2, 2, 2, 3> zzzw, bbba, ssst; \
swz4 <2, 2, 3, 0> zzwx, bbar, sstu; \
swz4 <2, 2, 3, 1> zzwy, bbag, sstv; \
swz4 <2, 2, 3, 2> zzwz, bbab, ssts; \
swz4 <2, 2, 3, 3> zzww, bbaa, sstt; \
swz4 <2, 3, 0, 0> zwxx, barr, stuu; \
swz4 <2, 3, 0, 1> zwxy, barg, stuv; \
swz4 <2, 3, 0, 2> zwxz, barb, stus; \
swz4 <2, 3, 0, 3> zwxw, bara, stut; \
swz4 <2, 3, 1, 0> zwyx, bagr, stvu; \
swz4 <2, 3, 1, 1> zwyy, bagg, stvv; \
swz4 <2, 3, 1, 2> zwyz, bagb, stvs; \
swz4 <2, 3, 1, 3> zwyw, baga, stvt; \
swz4 <2, 3, 2, 0> zwzx, babr, stsu; \
swz4 <2, 3, 2, 1> zwzy, babg, stsv; \
swz4 <2, 3, 2, 2> zwzz, babb, stss; \
swz4 <2, 3, 2, 3> zwzw, baba, stst; \
swz4 <2, 3, 3, 0> zwwx, baar, sttu; \
swz4 <2, 3, 3, 1> zwwy, baag, sttv; \
swz4 <2, 3, 3, 2> zwwz, baab, stts; \
swz4 <2, 3, 3, 3> zwww, baaa, sttt; \
swz4 <3, 0, 0, 0> wxxx, arrr, tuuu; \
swz4 <3, 0, 0, 1> wxxy, arrg, tuuv; \
swz4 <3, 0, 0, 2> wxxz, arrb, tuus; \
swz4 <3, 0, 0, 3> wxxw, arra, tuut; \
swz4 <3, 0, 1, 0> wxyx, argr, tuvu; \
swz4 <3, 0, 1, 1> wxyy, argg, tuvv; \
swz4 <3, 0, 1, 2> wxyz, argb, tuvs; \
swz4 <3, 0, 1, 3> wxyw, arga, tuvt; \
swz4 <3, 0, 2, 0> wxzx, arbr, tusu; \
swz4 <3, 0, 2, 1> wxzy, arbg, tusv; \
swz4 <3, 0, 2, 2> wxzz, arbb, tuss; \
swz4 <3, 0, 2, 3> wxzw, arba, tust; \
swz4 <3, 0, 3, 0> wxwx, arar, tutu; \
swz4 <3, 0, 3, 1> wxwy, arag, tutv; \
swz4 <3, 0, 3, 2> wxwz, arab, tuts; \
swz4 <3, 0, 3, 3> wxww, araa, tutt; \
swz4 <3, 1, 0, 0> wyxx, agrr, tvuu; \
swz4 <3, 1, 0, 1> wyxy, agrg, tvuv; \
swz4 <3, 1, 0, 2> wyxz, agrb, tvus; \
swz4 <3, 1, 0, 3> wyxw, agra, tvut; \
swz4 <3, 1, 1, 0> wyyx, aggr, tvvu; \
swz4 <3, 1, 1, 1> wyyy, aggg, tvvv; \
swz4 <3, 1, 1, 2> wyyz, aggb, tvvs; \
swz4 <3, 1, 1, 3> wyyw, agga, tvvt; \
swz4 <3, 1, 2, 0> wyzx, agbr, tvsu; \
swz4 <3, 1, 2, 1> wyzy, agbg, tvsv; \
swz4 <3, 1, 2, 2> wyzz, agbb, tvss; \
swz4 <3, 1, 2, 3> wyzw, agba, tvst; \
swz4 <3, 1, 3, 0> wywx, agar, tvtu; \
swz4 <3, 1, 3, 1> wywy, agag, tvtv; \
swz4 <3, 1, 3, 2> wywz, agab, tvts; \
swz4 <3, 1, 3, 3> wyww, agaa, tvtt; \
swz4 <3, 2, 0, 0> wzxx, abrr, tsuu; \
swz4 <3, 2, 0, 1> wzxy, abrg, tsuv; \
swz4 <3, 2, 0, 2> wzxz, abrb, tsus; \
swz4 <3, 2, 0, 3> wzxw, abra, tsut; \
swz4 <3, 2, 1, 0> wzyx, abgr, tsvu; \
swz4 <3, 2, 1, 1> wzyy, abgg, tsvv; \
swz4 <3, 2, 1, 2> wzyz, abgb, tsvs; \
swz4 <3, 2, 1, 3> wzyw, abga, tsvt; \
swz4 <3, 2, 2, 0> wzzx, abbr, tssu; \
swz4 <3, 2, 2, 1> wzzy, abbg, tssv; \
swz4 <3, 2, 2, 2> wzzz, abbb, tsss; \
swz4 <3, 2, 2, 3> wzzw, abba, tsst; \
swz4 <3, 2, 3, 0> wzwx, abar, tstu; \
swz4 <3, 2, 3, 1> wzwy, abag, tstv; \
swz4 <3, 2, 3, 2> wzwz, abab, tsts; \
swz4 <3, 2, 3, 3> wzww, abaa, tstt; \
swz4 <3, 3, 0, 0> wwxx, aarr, ttuu; \
swz4 <3, 3, 0, 1> wwxy, aarg, ttuv; \
swz4 <3, 3, 0, 2> wwxz, aarb, ttus; \
swz4 <3, 3, 0, 3> wwxw, aara, ttut; \
swz4 <3, 3, 1, 0> wwyx, aagr, ttvu; \
swz4 <3, 3, 1, 1> wwyy, aagg, ttvv; \
swz4 <3, 3, 1, 2> wwyz, aagb, ttvs; \
swz4 <3, 3, 1, 3> wwyw, aaga, ttvt; \
swz4 <3, 3, 2, 0> wwzx, aabr, ttsu; \
swz4 <3, 3, 2, 1> wwzy, aabg, ttsv; \
swz4 <3, 3, 2, 2> wwzz, aabb, ttss; \
swz4 <3, 3, 2, 3> wwzw, aaba, ttst; \
swz4 <3, 3, 3, 0> wwwx, aaar, tttu; \
swz4 <3, 3, 3, 1> wwwy, aaag, tttv; \
swz4 <3, 3, 3, 2> wwwz, aaab, ttts; \
swz4 <3, 3, 3, 3> wwww, aaaa, tttt; \

//

#endif //_GMTK_SWIZZLE4_H_
