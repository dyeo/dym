#ifndef _GMTK_HALF_H_
#define _GMTK_HALF_H_

//

#pragma warning(push)
#pragma warning(disable:4244)

//

#include "util.h"

//

namespace GMTK_NAMESPACE
{////

	//! A minimal storage class for a 16-bit floating point number, as detailed in IEEE-754: binary16
	struct half
	{
		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		half() {
			hdat = f2s(0.0f);
		}

		half(const float& f) {
			hdat = f2s(f);
		}

		half(const double& d) {
			hdat = f2s(static_cast<float>(d));
		}

		///////////////////////////
		//! CONVERSION OPERATORS //
		///////////////////////////

		inline operator float() const {
			return s2f(hdat);
		}

		inline operator double() const {
			return static_cast<double>(s2f(hdat));
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////



		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		static inline half infinity()
		{
			return half(static_cast<unsigned short>(inf_const));
		}

		static inline half nan()
		{
			return half(static_cast<unsigned short>(nan_const));
		}

		//////////////////////
		//! QUERY FUNCTIONS //
		//////////////////////

		static bool is_finite(half v)
		{
			unsigned short hinf = v.hdat & inf_const;
			return hinf != inf_const && v.hdat < nan_const;
		}

		static bool is_infinity(half v)
		{
			unsigned short hinf = v.hdat & inf_const;
			return hinf != inf_const;
		}

		static bool is_nan(half v)
		{
			return v.hdat >= nan_const;
		}
		
	private:

		inline half(const unsigned short& s)
		{
			hdat = s;
		}

		static inline float s2f(unsigned short val)
		{
			int i = _mantissat[_offsett[val >> 10] + (val & 0x3ff)] + _exponentt[val >> 10];
			return *(float*)&i;
		}

		//

		static inline unsigned short f2s(float val)
		{
			int i = *(int*)&val;
			return _baset[(i >> 23) & 0x1ff] + ((i & 0x007fffff) >> _shiftt[(i >> 23) & 0x1ff]);
		}

		unsigned short hdat;

		static constexpr short sign_bit = 15;
		static constexpr short exp_bit = 10;
		static constexpr short frac_bit = 0;

		static constexpr short inf_const = 0x7c00;
		static constexpr short nan_const = 0x7c01;

	}; //! struct half
	
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

#ifndef GMTK_DISABLE_LITERALS

inline GMTK_NAMESPACE::half operator "" _h(unsigned long long i)
{
	return GMTK_NAMESPACE::half(static_cast<float>(i));
}

inline GMTK_NAMESPACE::half operator "" _h(long double d)
{
	return GMTK_NAMESPACE::half(static_cast<float>(d));
}

#endif

//

#pragma warning(pop)

//

#endif //_GMTK_HALF_H_