#ifndef _DYM_UTIL_H_
#define _DYM_UTIL_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127; disable:4244)

//

#include "constants.h"

#include <cmath>
#include <cassert>
#include <random>

//

template<bool> struct static_assert_util;
template<> struct static_assert_util < true >
{};
#define DYM_STATIC_ASSERT(cond) static_assert_util<(cond)>()

//

#define DYM_MIN_OF(a, b) ( a < b ? a : b )

//

namespace dym
{////

	template <typename T>
	static bool req(const T &l, const T &r, const T &rng = small_v<T>)
	{
		return std::abs(l - r) <= rng;
	}

	template <typename T>
	static T sq(const T &v)
	{
		return v * v;
	}

	template <typename T>
	static T cu(const T &v)
	{
		return v * v * v;
	}

	template <typename T>
	static T pow(const T &v, const int p)
	{
		T val = v;
		for (std::size_t i = 0; i < p - 1; ++i)
		{
			val *= v;
		}
		return val;
	}

	template <typename T>
	static constexpr T abs(const T &v)
	{
		return (v > 0) ? v : -v;
	}

	template<typename T>
	static constexpr T min(const T &l, const T &r)
	{
		return (l < r) ? l : r;
	}

	template <typename T>
	static constexpr T max(const T &l, const T &r)
	{
		return (l > r) ? l : r;
	}

	template <typename T>
	static constexpr T clamp(const T &v, const T &minv, const T &maxv)
	{
		return max(minv, min(v, maxv));
	}

	template <typename T>
	static constexpr T saturate(const T &v)
	{
		return max(0, min(v, 1));
	}

	// the following functions are probably slower than the SSE rsqrtss instruction

	//! variation of the famous fast inverse square root
	inline float fastinvsqrt(float v)
	{
		float vhalf = 0.5f * v;
		int i = *(int *)&v; //! reinterpret floating point as binary, stored in int
		i = 0x5f375a7f - (i >> 1); //! get first best guess for invsqrt
		v = *(float *)&i; //! convert float binary back to float
		v = v * (1.5f - vhalf * v * v); //! use newton's approximation to determine better sqrt
		return v;
	}

	//! inverse square root
	inline float invsqrt(float v)
	{
		float vhalf = 0.5f * v;
		int i = *(int *)&v; //! reinterpret floating point as binary, stored in int
		i = 0x5f375a7f - (i >> 1); //! get first best guess for invsqrt
		v = *(float *)&i; //! convert float binary back to float
		v = v * (1.5f - vhalf * v * v); //! use newton's approximation to determine better sqrt
		v = v * (1.5f - vhalf * v * v); //! do one more approximation to determine better result
		return v;
	}

	template <typename T = long double>
	static T lerp(const T &src, const T &dst, const long double delta)
	{
		return (src * (1.0 - delta)) + (dst * delta);
	}

	template <typename T = double>
	static T lerp(const T &src, const T &dst, const double delta)
	{
		return (src * (1.0 - delta)) + (dst * delta);
	}

	template <typename T = float>
	static T lerp(const T &src, const T &dst, const float delta)
	{
		return (src * (1.f - delta)) + (dst * delta);
	}

	template <typename T = float>
	static int sgn(T val)
	{
		return (T(0) < val) - (val < T(0));
	}

}////

//

#pragma warning(pop)

//

#endif //_DYM_UTIL_H_