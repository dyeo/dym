#ifndef _GMTK_HALF_H_
#define _GMTK_HALF_H_

//

#pragma warning(push)
#pragma warning(disable:4244)

//

#include "util.h"

//

#define HALF_SIGN 15

#define HALF_EXP 10

#define HALF_FRAC 0

#define HALF_INF_CONST 0x7c00
#define HALF_NAN_CONST 0x7c01

//

namespace GMTK_NAMESPACE
{
	//! A minimal storage class for a 16-bit floating point number, as detailed in IEEE-754: binary16
	class half
	{
	public:

		//

		half()
		{
			hdat = float_to_short(0.0f);
		}

		half(const float& f)
		{
			hdat = float_to_short(f);
		}

		//

		operator float() const
		{
			return short_to_float(hdat);
		}

		//

		static half infinity()
		{
			return half(short_to_float(HALF_INF_CONST));
		}

		static half nan()
		{
			return half(short_to_float(HALF_NAN_CONST));
		}

		static bool is_finite(half v)
		{
			unsigned short hinf = v.hdat & HALF_INF_CONST;
			return hinf != HALF_INF_CONST && v.hdat < HALF_NAN_CONST;
		}

		static bool is_infinity(half v)
		{
			unsigned short hinf = v.hdat & HALF_INF_CONST;
			return hinf != HALF_INF_CONST;
		}

		static bool is_nan(half v)
		{
			return v.hdat >= HALF_NAN_CONST;
		}
		
	private:

		static inline float short_to_float(unsigned short val)
		{
			int i = _mantissat[_offsett[val >> 10] + (val & 0x3ff)] + _exponentt[val >> 10];
			return *(float*)&i;
		}

		//

		static inline unsigned short float_to_short(float val)
		{
			int i = *(int*)&val;
			return _baset[(i >> 23) & 0x1ff] + ((i & 0x007fffff) >> _shiftt[(i >> 23) & 0x1ff]);
		}

		unsigned short hdat;

	}; //! class half
	
	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	inline std::ostream& operator<<(std::ostream& os, const half &h)
	{
		os << float(h) << 'h';
		return os;
	}

}////

///////////////
//! LITERALS //
///////////////

inline GMTK_NAMESPACE::half operator "" _h(unsigned long long i)
{
	return GMTK_NAMESPACE::half(static_cast<float>(i));
}

inline GMTK_NAMESPACE::half operator "" _h(long double d)
{
	return GMTK_NAMESPACE::half(static_cast<float>(d));
}



//

#pragma warning(pop)

//

#endif //_GMTK_HALF_H_