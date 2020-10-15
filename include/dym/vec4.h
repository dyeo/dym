#ifndef _DYM_VEC4_H_
#define _DYM_VEC4_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "vec.h"			

#ifndef DYM_DISABLE_SWIZZLING
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"
#endif

//

namespace dym
{////

	template <typename T> struct vec <4, T>
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct
			{
				T data[4];
			};
			struct
			{
				T x, y, z, w;
			};
			struct
			{
				T r, g, b, a;
			};
			struct
			{
				T s, t, p, q;
			};
			#ifndef DYM_DISABLE_SWIZZLING
			swizzle2 <0, 0, T> xx, rr, ss;
			swizzle2 <0, 1, T> xy, rg, st;
			swizzle2 <0, 2, T> xz, rb, sp;
			swizzle2 <0, 3, T> xw, ra, sq;
			swizzle2 <1, 0, T> yx, gr, ts;
			swizzle2 <1, 1, T> yy, gg, tt;
			swizzle2 <1, 2, T> yz, gb, tp;
			swizzle2 <1, 3, T> yw, ga, tq;
			swizzle2 <2, 0, T> zx, br, ps;
			swizzle2 <2, 1, T> zy, bg, pt;
			swizzle2 <2, 2, T> zz, bb, pp;
			swizzle2 <2, 3, T> zw, ba, pq;
			swizzle2 <3, 0, T> wx, ar, qs;
			swizzle2 <3, 1, T> wy, ag, qt;
			swizzle2 <3, 2, T> wz, ab, qp;
			swizzle2 <3, 3, T> ww, aa, qq;
			swizzle3 <0, 0, 0, T> xxx, rrr, sss;
			swizzle3 <0, 0, 1, T> xxy, rrg, sst;
			swizzle3 <0, 0, 2, T> xxz, rrb, ssp;
			swizzle3 <0, 0, 3, T> xxw, rra, ssq;
			swizzle3 <0, 1, 0, T> xyx, rgr, sts;
			swizzle3 <0, 1, 1, T> xyy, rgg, stt;
			swizzle3 <0, 1, 2, T> xyz, rgb, stp;
			swizzle3 <0, 1, 3, T> xyw, rga, stq;
			swizzle3 <0, 2, 0, T> xzx, rbr, sps;
			swizzle3 <0, 2, 1, T> xzy, rbg, spt;
			swizzle3 <0, 2, 2, T> xzz, rbb, spp;
			swizzle3 <0, 2, 3, T> xzw, rba, spq;
			swizzle3 <0, 3, 0, T> xwx, rar, sqs;
			swizzle3 <0, 3, 1, T> xwy, rag, sqt;
			swizzle3 <0, 3, 2, T> xwz, rab, sqp;
			swizzle3 <0, 3, 3, T> xww, raa, sqq;
			swizzle3 <1, 0, 0, T> yxx, grr, tss;
			swizzle3 <1, 0, 1, T> yxy, grg, tst;
			swizzle3 <1, 0, 2, T> yxz, grb, tsp;
			swizzle3 <1, 0, 3, T> yxw, gra, tsq;
			swizzle3 <1, 1, 0, T> yyx, ggr, tts;
			swizzle3 <1, 1, 1, T> yyy, ggg, ttt;
			swizzle3 <1, 1, 2, T> yyz, ggb, ttp;
			swizzle3 <1, 1, 3, T> yyw, gga, ttq;
			swizzle3 <1, 2, 0, T> yzx, gbr, tps;
			swizzle3 <1, 2, 1, T> yzy, gbg, tpt;
			swizzle3 <1, 2, 2, T> yzz, gbb, tpp;
			swizzle3 <1, 2, 3, T> yzw, gba, tpq;
			swizzle3 <1, 3, 0, T> ywx, gar, tqs;
			swizzle3 <1, 3, 1, T> ywy, gag, tqt;
			swizzle3 <1, 3, 2, T> ywz, gab, tqp;
			swizzle3 <1, 3, 3, T> yww, gaa, tqq;
			swizzle3 <2, 0, 0, T> zxx, brr, pss;
			swizzle3 <2, 0, 1, T> zxy, brg, pst;
			swizzle3 <2, 0, 2, T> zxz, brb, psp;
			swizzle3 <2, 0, 3, T> zxw, bra, psq;
			swizzle3 <2, 1, 0, T> zyx, bgr, pts;
			swizzle3 <2, 1, 1, T> zyy, bgg, ptt;
			swizzle3 <2, 1, 2, T> zyz, bgb, ptp;
			swizzle3 <2, 1, 3, T> zyw, bga, ptq;
			swizzle3 <2, 2, 0, T> zzx, bbr, pps;
			swizzle3 <2, 2, 1, T> zzy, bbg, ppt;
			swizzle3 <2, 2, 2, T> zzz, bbb, ppp;
			swizzle3 <2, 2, 3, T> zzw, bba, ppq;
			swizzle3 <2, 3, 0, T> zwx, bar, pqs;
			swizzle3 <2, 3, 1, T> zwy, bag, pqt;
			swizzle3 <2, 3, 2, T> zwz, bab, pqp;
			swizzle3 <2, 3, 3, T> zww, baa, pqq;
			swizzle3 <3, 0, 0, T> wxx, arr, qss;
			swizzle3 <3, 0, 1, T> wxy, arg, qst;
			swizzle3 <3, 0, 2, T> wxz, arb, qsp;
			swizzle3 <3, 0, 3, T> wxw, ara, qsq;
			swizzle3 <3, 1, 0, T> wyx, agr, qts;
			swizzle3 <3, 1, 1, T> wyy, agg, qtt;
			swizzle3 <3, 1, 2, T> wyz, agb, qtp;
			swizzle3 <3, 1, 3, T> wyw, aga, qtq;
			swizzle3 <3, 2, 0, T> wzx, abr, qps;
			swizzle3 <3, 2, 1, T> wzy, abg, qpt;
			swizzle3 <3, 2, 2, T> wzz, abb, qpp;
			swizzle3 <3, 2, 3, T> wzw, aba, qpq;
			swizzle3 <3, 3, 0, T> wwx, aar, qqs;
			swizzle3 <3, 3, 1, T> wwy, aag, qqt;
			swizzle3 <3, 3, 2, T> wwz, aab, qqp;
			swizzle3 <3, 3, 3, T> www, aaa, qqq;
			swizzle4 <0, 0, 0, 0, T> xxxx, rrrr, ssss;
			swizzle4 <0, 0, 0, 1, T> xxxy, rrrg, ssst;
			swizzle4 <0, 0, 0, 2, T> xxxz, rrrb, sssp;
			swizzle4 <0, 0, 0, 3, T> xxxw, rrra, sssq;
			swizzle4 <0, 0, 1, 0, T> xxyx, rrgr, ssts;
			swizzle4 <0, 0, 1, 1, T> xxyy, rrgg, sstt;
			swizzle4 <0, 0, 1, 2, T> xxyz, rrgb, sstp;
			swizzle4 <0, 0, 1, 3, T> xxyw, rrga, sstq;
			swizzle4 <0, 0, 2, 0, T> xxzx, rrbr, ssps;
			swizzle4 <0, 0, 2, 1, T> xxzy, rrbg, sspt;
			swizzle4 <0, 0, 2, 2, T> xxzz, rrbb, sspp;
			swizzle4 <0, 0, 2, 3, T> xxzw, rrba, sspq;
			swizzle4 <0, 0, 3, 0, T> xxwx, rrar, ssqs;
			swizzle4 <0, 0, 3, 1, T> xxwy, rrag, ssqt;
			swizzle4 <0, 0, 3, 2, T> xxwz, rrab, ssqp;
			swizzle4 <0, 0, 3, 3, T> xxww, rraa, ssqq;
			swizzle4 <0, 1, 0, 0, T> xyxx, rgrr, stss;
			swizzle4 <0, 1, 0, 1, T> xyxy, rgrg, stst;
			swizzle4 <0, 1, 0, 2, T> xyxz, rgrb, stsp;
			swizzle4 <0, 1, 0, 3, T> xyxw, rgra, stsq;
			swizzle4 <0, 1, 1, 0, T> xyyx, rggr, stts;
			swizzle4 <0, 1, 1, 1, T> xyyy, rggg, sttt;
			swizzle4 <0, 1, 1, 2, T> xyyz, rggb, sttp;
			swizzle4 <0, 1, 1, 3, T> xyyw, rgga, sttq;
			swizzle4 <0, 1, 2, 0, T> xyzx, rgbr, stps;
			swizzle4 <0, 1, 2, 1, T> xyzy, rgbg, stpt;
			swizzle4 <0, 1, 2, 2, T> xyzz, rgbb, stpp;
			swizzle4 <0, 1, 2, 3, T> xyzw, rgba, stpq;
			swizzle4 <0, 1, 3, 0, T> xywx, rgar, stqs;
			swizzle4 <0, 1, 3, 1, T> xywy, rgag, stqt;
			swizzle4 <0, 1, 3, 2, T> xywz, rgab, stqp;
			swizzle4 <0, 1, 3, 3, T> xyww, rgaa, stqq;
			swizzle4 <0, 2, 0, 0, T> xzxx, rbrr, spss;
			swizzle4 <0, 2, 0, 1, T> xzxy, rbrg, spst;
			swizzle4 <0, 2, 0, 2, T> xzxz, rbrb, spsp;
			swizzle4 <0, 2, 0, 3, T> xzxw, rbra, spsq;
			swizzle4 <0, 2, 1, 0, T> xzyx, rbgr, spts;
			swizzle4 <0, 2, 1, 1, T> xzyy, rbgg, sptt;
			swizzle4 <0, 2, 1, 2, T> xzyz, rbgb, sptp;
			swizzle4 <0, 2, 1, 3, T> xzyw, rbga, sptq;
			swizzle4 <0, 2, 2, 0, T> xzzx, rbbr, spps;
			swizzle4 <0, 2, 2, 1, T> xzzy, rbbg, sppt;
			swizzle4 <0, 2, 2, 2, T> xzzz, rbbb, sppp;
			swizzle4 <0, 2, 2, 3, T> xzzw, rbba, sppq;
			swizzle4 <0, 2, 3, 0, T> xzwx, rbar, spqs;
			swizzle4 <0, 2, 3, 1, T> xzwy, rbag, spqt;
			swizzle4 <0, 2, 3, 2, T> xzwz, rbab, spqp;
			swizzle4 <0, 2, 3, 3, T> xzww, rbaa, spqq;
			swizzle4 <0, 3, 0, 0, T> xwxx, rarr, sqss;
			swizzle4 <0, 3, 0, 1, T> xwxy, rarg, sqst;
			swizzle4 <0, 3, 0, 2, T> xwxz, rarb, sqsp;
			swizzle4 <0, 3, 0, 3, T> xwxw, rara, sqsq;
			swizzle4 <0, 3, 1, 0, T> xwyx, ragr, sqts;
			swizzle4 <0, 3, 1, 1, T> xwyy, ragg, sqtt;
			swizzle4 <0, 3, 1, 2, T> xwyz, ragb, sqtp;
			swizzle4 <0, 3, 1, 3, T> xwyw, raga, sqtq;
			swizzle4 <0, 3, 2, 0, T> xwzx, rabr, sqps;
			swizzle4 <0, 3, 2, 1, T> xwzy, rabg, sqpt;
			swizzle4 <0, 3, 2, 2, T> xwzz, rabb, sqpp;
			swizzle4 <0, 3, 2, 3, T> xwzw, raba, sqpq;
			swizzle4 <0, 3, 3, 0, T> xwwx, raar, sqqs;
			swizzle4 <0, 3, 3, 1, T> xwwy, raag, sqqt;
			swizzle4 <0, 3, 3, 2, T> xwwz, raab, sqqp;
			swizzle4 <0, 3, 3, 3, T> xwww, raaa, sqqq;
			swizzle4 <1, 0, 0, 0, T> yxxx, grrr, tsss;
			swizzle4 <1, 0, 0, 1, T> yxxy, grrg, tsst;
			swizzle4 <1, 0, 0, 2, T> yxxz, grrb, tssp;
			swizzle4 <1, 0, 0, 3, T> yxxw, grra, tssq;
			swizzle4 <1, 0, 1, 0, T> yxyx, grgr, tsts;
			swizzle4 <1, 0, 1, 1, T> yxyy, grgg, tstt;
			swizzle4 <1, 0, 1, 2, T> yxyz, grgb, tstp;
			swizzle4 <1, 0, 1, 3, T> yxyw, grga, tstq;
			swizzle4 <1, 0, 2, 0, T> yxzx, grbr, tsps;
			swizzle4 <1, 0, 2, 1, T> yxzy, grbg, tspt;
			swizzle4 <1, 0, 2, 2, T> yxzz, grbb, tspp;
			swizzle4 <1, 0, 2, 3, T> yxzw, grba, tspq;
			swizzle4 <1, 0, 3, 0, T> yxwx, grar, tsqs;
			swizzle4 <1, 0, 3, 1, T> yxwy, grag, tsqt;
			swizzle4 <1, 0, 3, 2, T> yxwz, grab, tsqp;
			swizzle4 <1, 0, 3, 3, T> yxww, graa, tsqq;
			swizzle4 <1, 1, 0, 0, T> yyxx, ggrr, ttss;
			swizzle4 <1, 1, 0, 1, T> yyxy, ggrg, ttst;
			swizzle4 <1, 1, 0, 2, T> yyxz, ggrb, ttsp;
			swizzle4 <1, 1, 0, 3, T> yyxw, ggra, ttsq;
			swizzle4 <1, 1, 1, 0, T> yyyx, gggr, ttts;
			swizzle4 <1, 1, 1, 1, T> yyyy, gggg, tttt;
			swizzle4 <1, 1, 1, 2, T> yyyz, gggb, tttp;
			swizzle4 <1, 1, 1, 3, T> yyyw, ggga, tttq;
			swizzle4 <1, 1, 2, 0, T> yyzx, ggbr, ttps;
			swizzle4 <1, 1, 2, 1, T> yyzy, ggbg, ttpt;
			swizzle4 <1, 1, 2, 2, T> yyzz, ggbb, ttpp;
			swizzle4 <1, 1, 2, 3, T> yyzw, ggba, ttpq;
			swizzle4 <1, 1, 3, 0, T> yywx, ggar, ttqs;
			swizzle4 <1, 1, 3, 1, T> yywy, ggag, ttqt;
			swizzle4 <1, 1, 3, 2, T> yywz, ggab, ttqp;
			swizzle4 <1, 1, 3, 3, T> yyww, ggaa, ttqq;
			swizzle4 <1, 2, 0, 0, T> yzxx, gbrr, tpss;
			swizzle4 <1, 2, 0, 1, T> yzxy, gbrg, tpst;
			swizzle4 <1, 2, 0, 2, T> yzxz, gbrb, tpsp;
			swizzle4 <1, 2, 0, 3, T> yzxw, gbra, tpsq;
			swizzle4 <1, 2, 1, 0, T> yzyx, gbgr, tpts;
			swizzle4 <1, 2, 1, 1, T> yzyy, gbgg, tptt;
			swizzle4 <1, 2, 1, 2, T> yzyz, gbgb, tptp;
			swizzle4 <1, 2, 1, 3, T> yzyw, gbga, tptq;
			swizzle4 <1, 2, 2, 0, T> yzzx, gbbr, tpps;
			swizzle4 <1, 2, 2, 1, T> yzzy, gbbg, tppt;
			swizzle4 <1, 2, 2, 2, T> yzzz, gbbb, tppp;
			swizzle4 <1, 2, 2, 3, T> yzzw, gbba, tppq;
			swizzle4 <1, 2, 3, 0, T> yzwx, gbar, tpqs;
			swizzle4 <1, 2, 3, 1, T> yzwy, gbag, tpqt;
			swizzle4 <1, 2, 3, 2, T> yzwz, gbab, tpqp;
			swizzle4 <1, 2, 3, 3, T> yzww, gbaa, tpqq;
			swizzle4 <1, 3, 0, 0, T> ywxx, garr, tqss;
			swizzle4 <1, 3, 0, 1, T> ywxy, garg, tqst;
			swizzle4 <1, 3, 0, 2, T> ywxz, garb, tqsp;
			swizzle4 <1, 3, 0, 3, T> ywxw, gara, tqsq;
			swizzle4 <1, 3, 1, 0, T> ywyx, gagr, tqts;
			swizzle4 <1, 3, 1, 1, T> ywyy, gagg, tqtt;
			swizzle4 <1, 3, 1, 2, T> ywyz, gagb, tqtp;
			swizzle4 <1, 3, 1, 3, T> ywyw, gaga, tqtq;
			swizzle4 <1, 3, 2, 0, T> ywzx, gabr, tqps;
			swizzle4 <1, 3, 2, 1, T> ywzy, gabg, tqpt;
			swizzle4 <1, 3, 2, 2, T> ywzz, gabb, tqpp;
			swizzle4 <1, 3, 2, 3, T> ywzw, gaba, tqpq;
			swizzle4 <1, 3, 3, 0, T> ywwx, gaar, tqqs;
			swizzle4 <1, 3, 3, 1, T> ywwy, gaag, tqqt;
			swizzle4 <1, 3, 3, 2, T> ywwz, gaab, tqqp;
			swizzle4 <1, 3, 3, 3, T> ywww, gaaa, tqqq;
			swizzle4 <2, 0, 0, 0, T> zxxx, brrr, psss;
			swizzle4 <2, 0, 0, 1, T> zxxy, brrg, psst;
			swizzle4 <2, 0, 0, 2, T> zxxz, brrb, pssp;
			swizzle4 <2, 0, 0, 3, T> zxxw, brra, pssq;
			swizzle4 <2, 0, 1, 0, T> zxyx, brgr, psts;
			swizzle4 <2, 0, 1, 1, T> zxyy, brgg, pstt;
			swizzle4 <2, 0, 1, 2, T> zxyz, brgb, pstp;
			swizzle4 <2, 0, 1, 3, T> zxyw, brga, pstq;
			swizzle4 <2, 0, 2, 0, T> zxzx, brbr, psps;
			swizzle4 <2, 0, 2, 1, T> zxzy, brbg, pspt;
			swizzle4 <2, 0, 2, 2, T> zxzz, brbb, pspp;
			swizzle4 <2, 0, 2, 3, T> zxzw, brba, pspq;
			swizzle4 <2, 0, 3, 0, T> zxwx, brar, psqs;
			swizzle4 <2, 0, 3, 1, T> zxwy, brag, psqt;
			swizzle4 <2, 0, 3, 2, T> zxwz, brab, psqp;
			swizzle4 <2, 0, 3, 3, T> zxww, braa, psqq;
			swizzle4 <2, 1, 0, 0, T> zyxx, bgrr, ptss;
			swizzle4 <2, 1, 0, 1, T> zyxy, bgrg, ptst;
			swizzle4 <2, 1, 0, 2, T> zyxz, bgrb, ptsp;
			swizzle4 <2, 1, 0, 3, T> zyxw, bgra, ptsq;
			swizzle4 <2, 1, 1, 0, T> zyyx, bggr, ptts;
			swizzle4 <2, 1, 1, 1, T> zyyy, bggg, pttt;
			swizzle4 <2, 1, 1, 2, T> zyyz, bggb, pttp;
			swizzle4 <2, 1, 1, 3, T> zyyw, bgga, pttq;
			swizzle4 <2, 1, 2, 0, T> zyzx, bgbr, ptps;
			swizzle4 <2, 1, 2, 1, T> zyzy, bgbg, ptpt;
			swizzle4 <2, 1, 2, 2, T> zyzz, bgbb, ptpp;
			swizzle4 <2, 1, 2, 3, T> zyzw, bgba, ptpq;
			swizzle4 <2, 1, 3, 0, T> zywx, bgar, ptqs;
			swizzle4 <2, 1, 3, 1, T> zywy, bgag, ptqt;
			swizzle4 <2, 1, 3, 2, T> zywz, bgab, ptqp;
			swizzle4 <2, 1, 3, 3, T> zyww, bgaa, ptqq;
			swizzle4 <2, 2, 0, 0, T> zzxx, bbrr, ppss;
			swizzle4 <2, 2, 0, 1, T> zzxy, bbrg, ppst;
			swizzle4 <2, 2, 0, 2, T> zzxz, bbrb, ppsp;
			swizzle4 <2, 2, 0, 3, T> zzxw, bbra, ppsq;
			swizzle4 <2, 2, 1, 0, T> zzyx, bbgr, ppts;
			swizzle4 <2, 2, 1, 1, T> zzyy, bbgg, pptt;
			swizzle4 <2, 2, 1, 2, T> zzyz, bbgb, pptp;
			swizzle4 <2, 2, 1, 3, T> zzyw, bbga, pptq;
			swizzle4 <2, 2, 2, 0, T> zzzx, bbbr, ppps;
			swizzle4 <2, 2, 2, 1, T> zzzy, bbbg, pppt;
			swizzle4 <2, 2, 2, 2, T> zzzz, bbbb, pppp;
			swizzle4 <2, 2, 2, 3, T> zzzw, bbba, pppq;
			swizzle4 <2, 2, 3, 0, T> zzwx, bbar, ppqs;
			swizzle4 <2, 2, 3, 1, T> zzwy, bbag, ppqt;
			swizzle4 <2, 2, 3, 2, T> zzwz, bbab, ppqp;
			swizzle4 <2, 2, 3, 3, T> zzww, bbaa, ppqq;
			swizzle4 <2, 3, 0, 0, T> zwxx, barr, pqss;
			swizzle4 <2, 3, 0, 1, T> zwxy, barg, pqst;
			swizzle4 <2, 3, 0, 2, T> zwxz, barb, pqsp;
			swizzle4 <2, 3, 0, 3, T> zwxw, bara, pqsq;
			swizzle4 <2, 3, 1, 0, T> zwyx, bagr, pqts;
			swizzle4 <2, 3, 1, 1, T> zwyy, bagg, pqtt;
			swizzle4 <2, 3, 1, 2, T> zwyz, bagb, pqtp;
			swizzle4 <2, 3, 1, 3, T> zwyw, baga, pqtq;
			swizzle4 <2, 3, 2, 0, T> zwzx, babr, pqps;
			swizzle4 <2, 3, 2, 1, T> zwzy, babg, pqpt;
			swizzle4 <2, 3, 2, 2, T> zwzz, babb, pqpp;
			swizzle4 <2, 3, 2, 3, T> zwzw, baba, pqpq;
			swizzle4 <2, 3, 3, 0, T> zwwx, baar, pqqs;
			swizzle4 <2, 3, 3, 1, T> zwwy, baag, pqqt;
			swizzle4 <2, 3, 3, 2, T> zwwz, baab, pqqp;
			swizzle4 <2, 3, 3, 3, T> zwww, baaa, pqqq;
			swizzle4 <3, 0, 0, 0, T> wxxx, arrr, qsss;
			swizzle4 <3, 0, 0, 1, T> wxxy, arrg, qsst;
			swizzle4 <3, 0, 0, 2, T> wxxz, arrb, qssp;
			swizzle4 <3, 0, 0, 3, T> wxxw, arra, qssq;
			swizzle4 <3, 0, 1, 0, T> wxyx, argr, qsts;
			swizzle4 <3, 0, 1, 1, T> wxyy, argg, qstt;
			swizzle4 <3, 0, 1, 2, T> wxyz, argb, qstp;
			swizzle4 <3, 0, 1, 3, T> wxyw, arga, qstq;
			swizzle4 <3, 0, 2, 0, T> wxzx, arbr, qsps;
			swizzle4 <3, 0, 2, 1, T> wxzy, arbg, qspt;
			swizzle4 <3, 0, 2, 2, T> wxzz, arbb, qspp;
			swizzle4 <3, 0, 2, 3, T> wxzw, arba, qspq;
			swizzle4 <3, 0, 3, 0, T> wxwx, arar, qsqs;
			swizzle4 <3, 0, 3, 1, T> wxwy, arag, qsqt;
			swizzle4 <3, 0, 3, 2, T> wxwz, arab, qsqp;
			swizzle4 <3, 0, 3, 3, T> wxww, araa, qsqq;
			swizzle4 <3, 1, 0, 0, T> wyxx, agrr, qtss;
			swizzle4 <3, 1, 0, 1, T> wyxy, agrg, qtst;
			swizzle4 <3, 1, 0, 2, T> wyxz, agrb, qtsp;
			swizzle4 <3, 1, 0, 3, T> wyxw, agra, qtsq;
			swizzle4 <3, 1, 1, 0, T> wyyx, aggr, qtts;
			swizzle4 <3, 1, 1, 1, T> wyyy, aggg, qttt;
			swizzle4 <3, 1, 1, 2, T> wyyz, aggb, qttp;
			swizzle4 <3, 1, 1, 3, T> wyyw, agga, qttq;
			swizzle4 <3, 1, 2, 0, T> wyzx, agbr, qtps;
			swizzle4 <3, 1, 2, 1, T> wyzy, agbg, qtpt;
			swizzle4 <3, 1, 2, 2, T> wyzz, agbb, qtpp;
			swizzle4 <3, 1, 2, 3, T> wyzw, agba, qtpq;
			swizzle4 <3, 1, 3, 0, T> wywx, agar, qtqs;
			swizzle4 <3, 1, 3, 1, T> wywy, agag, qtqt;
			swizzle4 <3, 1, 3, 2, T> wywz, agab, qtqp;
			swizzle4 <3, 1, 3, 3, T> wyww, agaa, qtqq;
			swizzle4 <3, 2, 0, 0, T> wzxx, abrr, qpss;
			swizzle4 <3, 2, 0, 1, T> wzxy, abrg, qpst;
			swizzle4 <3, 2, 0, 2, T> wzxz, abrb, qpsp;
			swizzle4 <3, 2, 0, 3, T> wzxw, abra, qpsq;
			swizzle4 <3, 2, 1, 0, T> wzyx, abgr, qpts;
			swizzle4 <3, 2, 1, 1, T> wzyy, abgg, qptt;
			swizzle4 <3, 2, 1, 2, T> wzyz, abgb, qptp;
			swizzle4 <3, 2, 1, 3, T> wzyw, abga, qptq;
			swizzle4 <3, 2, 2, 0, T> wzzx, abbr, qpps;
			swizzle4 <3, 2, 2, 1, T> wzzy, abbg, qppt;
			swizzle4 <3, 2, 2, 2, T> wzzz, abbb, qppp;
			swizzle4 <3, 2, 2, 3, T> wzzw, abba, qppq;
			swizzle4 <3, 2, 3, 0, T> wzwx, abar, qpqs;
			swizzle4 <3, 2, 3, 1, T> wzwy, abag, qpqt;
			swizzle4 <3, 2, 3, 2, T> wzwz, abab, qpqp;
			swizzle4 <3, 2, 3, 3, T> wzww, abaa, qpqq;
			swizzle4 <3, 3, 0, 0, T> wwxx, aarr, qqss;
			swizzle4 <3, 3, 0, 1, T> wwxy, aarg, qqst;
			swizzle4 <3, 3, 0, 2, T> wwxz, aarb, qqsp;
			swizzle4 <3, 3, 0, 3, T> wwxw, aara, qqsq;
			swizzle4 <3, 3, 1, 0, T> wwyx, aagr, qqts;
			swizzle4 <3, 3, 1, 1, T> wwyy, aagg, qqtt;
			swizzle4 <3, 3, 1, 2, T> wwyz, aagb, qqtp;
			swizzle4 <3, 3, 1, 3, T> wwyw, aaga, qqtq;
			swizzle4 <3, 3, 2, 0, T> wwzx, aabr, qqps;
			swizzle4 <3, 3, 2, 1, T> wwzy, aabg, qqpt;
			swizzle4 <3, 3, 2, 2, T> wwzz, aabb, qqpp;
			swizzle4 <3, 3, 2, 3, T> wwzw, aaba, qqpq;
			swizzle4 <3, 3, 3, 0, T> wwwx, aaar, qqqs;
			swizzle4 <3, 3, 3, 1, T> wwwy, aaag, qqqt;
			swizzle4 <3, 3, 3, 2, T> wwwz, aaab, qqqp;
			swizzle4 <3, 3, 3, 3, T> wwww, aaaa, qqqq;
			#endif
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline vec()
			: x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0)), w(static_cast<T>(0))
		{}

		//! Initialize vec4 with four scalar values
		inline vec(const T &s0, const T &s1, const T &s2, const T &s3)
			: x(s0), y(s1), z(s2), w(s3)
		{}

		//! Initialize vec4 with two vec2s
		inline vec(const vec<2, T> &v01, const vec<2, T> &v23)
			: x(v01.x), y(v01.y), z(v23.x), w(v23.y)
		{}

		//! Initialize vec4 with a vec2 and two scalar values
		inline vec(const vec<2, T> &v01, const T &s2, const T &s3)
			: x(v01.x), y(v01.y), z(s2), w(s3)
		{}

		//! Initialize vec4 with a scalar value, a vec2, and another scalar value
		inline vec(const T &s0, const vec<2, T> &v12, const T &s3)
			: x(s0), y(v12.x), z(v12.y), w(s3)
		{}

		//! Initialize vec4 with two scalar values and a vec2
		inline vec(const T &s0, const T &s1, const vec<2, T> &v23)
			: x(s0), y(s1), z(v23.x), w(v23.y)
		{}

		//! Initialize vec4 with a vec3 and a scalar value
		inline vec(const vec<3, T> &v012, const T &s3)
			: x(v012.x), y(v012.y), z(v012.z), w(s3)
		{}

		//! Initialize vec4 with a scalar value and a vec3
		inline vec(const T &s0, const vec<3, T> &v123)
			: x(s0), y(v123.x), z(v123.y), w(v123.z)
		{}

		#ifndef DYM_DISABLE_SWIZZLING
		//! Swizzle4 constructor
		template<int a, int b, int c, int d>
		inline vec(const swizzle4 <a, b, c, d, T> &s)
			: x(s[a]), y(s[b]), z(s[c]), w(s[d])
		{}
		#endif

		//! Copy constructor
		inline vec(const vec<4, T> &v)
			: x(v.x), y(v.y), z(v.z), w(v.w)
		{}

		//! Explicit type-conversion copy constructor
		template<typename U>
		explicit inline vec(const vec<4, U> &v)
			: x(static_cast<T>(v.x)), y(static_cast<T>(v.y)), z(static_cast<T>(v.z)), w(static_cast<T>(v.w))
		{}

		//! Fill constructor
		explicit inline vec(const T &s)
			: x(s), y(s), z(s), w(s)
		{}

		//! Array initializer
		explicit inline vec(const T *a)
			: x(a[0]), y(a[1]), z(a[2]), w(a[3])
		{}

		//! Initializer list constructor
		inline vec(std::initializer_list<T> l)
			: x(*(l.begin())), y(*(l.begin() + 1)), z(*(l.begin() + 2)), w(*(l.begin() + 3))
		{}

		//! Copy constructor for differently-sized vector
		template<int d2>
		inline vec(const vec<d2, T> &v)
		{
			if (d2 < 4)
			{
				for (std::size_t i = 0; i < d2; ++i)
				{
					data[i] = v.data[i];
				}
			}
			else
			{
				for (std::size_t i = 0; i < 4; ++i)
				{
					data[i] = v.data[i];
				}
			}
		}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! Vector index operator
		inline T &operator[](const std::size_t i)
		{
			return data[i];
		}

		//! Vector const index operator
		inline const T &operator[](const std::size_t i) const
		{
			return data[i];
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Component-wise unary negation
		inline vec<4, T> operator - () const
		{
			return vec<4, T>(-x, -y, -z, -w);
		}
		//! Component-wise unary negation
		inline vec<4, T> operator ~ () const
		{
			return vec<4, T>(~x, ~y, ~z, ~w);
		}
		//! Vector assignment
		inline vec<4, T> &operator = (const vec<4, T> &v)
		{
			x = v.x; y = v.y; z = v.z; w = v.w; return *this;
		}

		//! Component-wise vector multiplication
		inline vec<4, T> operator * (const vec<4, T> &v) const
		{
			return vec<4, T>(x * v.x, y * v.y, z * v.z, w * v.w);
		}
		//! Component-wise vector division
		inline vec<4, T> operator / (const vec<4, T> &v) const
		{
			return vec<4, T>(x / v.x, y / v.y, z / v.z, w / v.w);
		}
		//! Component-wise vector addition
		inline vec<4, T> operator + (const vec<4, T> &v) const
		{
			return vec<4, T>(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		//! Component-wise vector subtraction
		inline vec<4, T> operator - (const vec<4, T> &v) const
		{
			return vec<4, T>(x - v.x, y - v.y, z - v.z, w - v.w);
		}
		//! Component-wise vector OR
		inline vec<4, T> operator | (const vec<4, T> &v) const
		{
			return vec<4, T>(x | v.x, y | v.y, z | v.z, w | v.w);
		}
		//! Component-wise vector AND
		inline vec<4, T> operator & (const vec<4, T> &v) const
		{
			return vec<4, T>(x & v.x, y & v.y, z & v.z, w & v.w);
		}
		//! Component-wise vector XOR
		inline vec<4, T> operator ^ (const vec<4, T> &v) const
		{
			return vec<4, T>(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w);
		}
		//! Component-wise vector modulus
		inline vec<4, T> operator % (const vec<4, T> &v) const
		{
			return vec<4, T>(x % v.x, y % v.y, z % v.z, w % v.w);
		}
		//! Component-wise vector shift left
		inline vec<4, T> operator << (const vec<4, T> &v) const
		{
			return vec<4, T>(x << v.x, y << v.y, z << v.z, w << v.w);
		}
		//! Component-wise vector shift right
		inline vec<4, T> operator >> (const vec<4, T> &v) const
		{
			return vec<4, T>(x >> v.x, y >> v.y, z >> v.z, w >> v.w);
		}

		//! Component-wise scalar multiplication
		inline vec<4, T> operator * (const T &v) const
		{
			return vec<4, T>(x * v, y * v, z * v, w * v);
		}
		//! Component-wise scalar division
		inline vec<4, T> operator / (const T &v) const
		{
			return vec<4, T>(x / v, y / v, z / v, w / v);
		}
		//! Component-wise scalar addition
		inline vec<4, T> operator + (const T &v) const
		{
			return vec<4, T>(x + v, y + v, z + v, w + v);
		}
		//! Component-wise scalar subtraction
		inline vec<4, T> operator - (const T &v) const
		{
			return vec<4, T>(x - v, y - v, z - v, w - v);
		}
		//! Component-wise scalar OR
		inline vec<4, T> operator | (const T &v) const
		{
			return vec<4, T>(x | v, y | v, z | v, w | v);
		}
		//! Component-wise scalar AND
		inline vec<4, T> operator & (const T &v) const
		{
			return vec<4, T>(x & v, y & v, z & v, w & v);
		}
		//! Component-wise scalar XOR
		inline vec<4, T> operator ^ (const T &v) const
		{
			return vec<4, T>(x ^ v, y ^ v, z ^ v, w ^ v);
		}
		//! Component-wise scalar modulus
		inline vec<4, T> operator % (const T &v) const
		{
			return vec<4, T>(x % v, y % v, z % v, w % v);
		}
		//! Component-wise scalar shift left
		inline vec<4, T> operator << (const T &v) const
		{
			return vec<4, T>(x << v, y << v, z << v, w << v);
		}
		//! Component-wise scalar shift right
		inline vec<4, T> operator >> (const T &v) const
		{
			return vec<4, T>(x >> v, y >> v, z >> v, w >> v);
		}

		//! Component-wise vector reference multiplication
		inline vec<4, T> &operator *= (const vec<4, T> &v)
		{
			x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this;
		}
		//! Component-wise vector reference division
		inline vec<4, T> &operator /= (const vec<4, T> &v)
		{
			x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this;
		}
		//! Component-wise vector reference addition
		inline vec<4, T> &operator += (const vec<4, T> &v)
		{
			x += v.x; y += v.y; z += v.z; w += v.w; return *this;
		}
		//! Component-wise vector reference subtraction
		inline vec<4, T> &operator -= (const vec<4, T> &v)
		{
			x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this;
		}
		//! Component-wise vector reference OR
		inline vec<4, T> &operator |= (const vec<4, T> &v)
		{
			x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this;
		}
		//! Component-wise vector reference AND
		inline vec<4, T> &operator &= (const vec<4, T> &v)
		{
			x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this;
		}
		//! Component-wise vector reference XOR
		inline vec<4, T> &operator ^= (const vec<4, T> &v)
		{
			x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this;
		}
		//! Component-wise vector reference modulus
		inline vec<4, T> &operator %= (const vec<4, T> &v)
		{
			x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this;
		}
		//! Component-wise vector reference shift left
		inline vec<4, T> &operator <<= (const vec<4, T> &v)
		{
			x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this;
		}
		//! Component-wise vector reference shift right
		inline vec<4, T> &operator >>= (const vec<4, T> &v)
		{
			x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this;
		}

		//! Component-wise scalar reference multiplication
		inline vec<4, T> &operator *= (const T &v)
		{
			x *= v; y *= v; z *= v; w *= v; return *this;
		}
		//! Component-wise scalar reference division
		inline vec<4, T> &operator /= (const T &v)
		{
			x /= v; y /= v; z /= v; w /= v; return *this;
		}
		//! Component-wise scalar reference addition
		inline vec<4, T> &operator += (const T &v)
		{
			x += v; y += v; z += v; w += v; return *this;
		}
		//! Component-wise scalar reference subtraction
		inline vec<4, T> &operator -= (const T &v)
		{
			x -= v; y -= v; z -= v; w -= v; return *this;
		}
		//! Component-wise scalar reference OR
		inline vec<4, T> &operator |= (const T &v)
		{
			x |= v; y |= v; z |= v; w |= v; return *this;
		}
		//! Component-wise scalar reference AND
		inline vec<4, T> &operator &= (const T &v)
		{
			x &= v; y &= v; z &= v; w &= v; return *this;
		}
		//! Component-wise scalar reference XOR
		inline vec<4, T> &operator ^= (const T &v)
		{
			x ^= v; y ^= v; z ^= v; w ^= v; return *this;
		}
		//! Component-wise scalar reference modulus
		inline vec<4, T> &operator %= (const T &v)
		{
			x %= v; y %= v; z %= v; w %= v; return *this;
		}
		//! Component-wise scalar reference shift left
		inline vec<4, T> &operator <<= (const T &v)
		{
			x <<= v; y <<= v; z <<= v; w <<= v; return *this;
		}
		//! Component-wise scalar reference shift right
		inline vec<4, T> &operator >>= (const T &v)
		{
			x >>= v; y >>= v; z >>= v; w >>= v; return *this;
		}

		//! Component-wise equality comparison
		inline bool operator == (const vec<4, T> &v) const
		{
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}
		//! Component-wise inequality comparison
		inline bool operator != (const vec<4, T> &v) const
		{
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! NaN vector (NaN, NaN, NaN, NaN)
		static inline constexpr vec<4, T> nan()
		{
			return vec<4, T>(NAN, NAN, NAN, NAN);
		}

		//! Infinity vector (inf, inf, inf, inf)
		static inline constexpr vec<4, T> inf()
		{
			return vec<4, T>(INFINITY, INFINITY, INFINITY, INFINITY);
		}

		//! Zero vector (0,0,0,0)
		static inline constexpr vec<4, T> zero()
		{
			return vec<4, T>(0, 0, 0, 0);
		}

		//! One vector (1,1,1,1)
		static inline constexpr vec<4, T> one()
		{
			return vec<4, T>(1, 1, 1, 1);
		}

		//! Up vector (0,1,0,0)
		static inline constexpr vec<4, T> up()
		{
			return vec<4, T>(0, 1, 0, 0);
		}

		//! Down vector (0,-1,0,0)
		static inline constexpr vec<4, T> down()
		{
			return vec<4, T>(0, -1, 0, 0);
		}

		//! Right vector (1,0,0,0)
		static inline constexpr vec<4, T> right()
		{
			return vec<4, T>(1, 0, 0, 0);
		}

		//! Left vector (-1,0,0,0)
		static inline constexpr vec<4, T> left()
		{
			return vec<4, T>(-1, 0, 0, 0);
		}

		//! Forward vector (0,0,1,0)
		static inline constexpr vec<4, T> forward()
		{
			return vec<4, T>(0, 0, 1, 0);
		}

		//! Back vector (0,0,-1,0)
		static inline constexpr vec<4, T> back()
		{
			return vec<4, T>(0, 0, -1, 0);
		}

	}; //! struct vec4

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef vec<4, float>			vec4, vec4f;
	typedef vec<4, double>			vec4d;
	typedef vec<4, unsigned char>	vec4uc;
	typedef vec<4, char>			vec4c;
	typedef vec<4, unsigned short>	vec4us;
	typedef vec<4, short>			vec4s;
	typedef vec<4, unsigned int>	vec4ui;
	typedef vec<4, int>				vec4i;
	typedef vec<4, unsigned long>	vec4ul;
	typedef vec<4, long>			vec4l;

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template <typename T = float>
	inline std::ostream &operator<<(std::ostream &os, const vec<4, T> &v)
	{
		os << "| " << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w << " |";
		return os;
	}

	//! Scalar-Vector multiplication
	template <typename T = float>
	inline vec<4, T> operator*(const T &l, const vec<4, T> &r)
	{
		return vec<4, T>(l * r.x, l * r.y, l * r.z, l * r.w);
	}

	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Calculates the dot or scalar product of two vectors
	template < typename T = float>
	inline T dot(const vec<4, T> &l, const vec<4, T> &r)
	{
		return (l.x * r.x) + (l.y * r.y) + (l.z * r.z) + (l.w * r.w);
	}

	//! Returns length squared of vector
	template <typename T = float>
	inline T lengthsq(const vec<4, T> &v)
	{
		return sq(v.x) + sq(v.y) + sq(v.z) + sq(v.w);
	}

	//! Returns length of vector, or sqrt(lengthsq)
	template <typename T = float>
	inline T length(const vec<4, T> &v)
	{
		return sqrt(sq(v.x) + sq(v.y) + sq(v.z) + sq(v.w));
	}

	//! Returns a component-wise minimum of two vectors
	template < typename T = float>
	inline vec<4, T> min(const vec<4, T> &l, const vec<4, T> &r)
	{
		return vec<4, T>(min(l.x, r.x), min(l.y, r.y), min(l.z, r.z), min(l.w, r.w));
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template < typename T = float>
	inline vec<4, T> min(const vec<4, T> &l, const T &r)
	{
		return vec<4, T>(min(l.x, r), min(l.y, r), min(l.z, r), min(l.w, r));
	}

	//! Returns a component-wise minimum of two vectors
	template <typename T = float>
	inline vec<4, T> max(const vec<4, T> &l, const vec<4, T> &r)
	{
		return vec<4, T>(max(l.x, r.x), max(l.y, r.y), max(l.z, r.z), max(l.w, r.w));
	}

	//! Returns a component-wise maximum of a vector and a scalar
	template <typename T = float>
	inline vec<4, T> max(const vec<4, T> &l, const T &r)
	{
		return vec<4, T>(max(l.x, r), max(l.y, r), max(l.z, r), max(l.w, r));
	}

	//! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
	template<typename T = float>
	inline vec<5, T> affine(const vec<4, T> &v)
	{
		return vec<5, T>(v.x, v.y, v.z, v.w, static_cast<T>(1));
	}

	//! Returns whether vector is NaN
	template<typename T = float>
	inline bool isnan(const vec<4, T> &v)
	{
		return std::isnan(v.x) || std::isnan(v.y) || std::isnan(v.z) || std::isnan(v.w);
	}

	//! Returns whether vector is inf
	template<typename T = float>
	inline bool isinf(const vec<4, T> &v)
	{
		return std::isinf(v.x) || std::isinf(v.y) || std::isinf(v.z) || std::isinf(v.w);
	}

	//! Relative equality (for floating-point vectors)
	template<typename T = float>
	inline bool req(const vec<4, T> &a, const vec<4, T> &b, T rng = 1e-8)
	{
		return req(l.x, r.x, rng) && req(l.y, r.y, rng) && req(l.z, r.z, rng) && req(l.w, r.w, rng);
	}

}////

//

#pragma warning(pop)

//

#endif