#ifndef DYM_UTIL_H_INCLUDED
#define DYM_UTIL_H_INCLUDED

//

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127; disable : 4244)
#endif

//

#include "constants.h"

#include <cstddef>
#include <cmath>
#include <cassert>
#include <random>
#include <ostream>
#include <concepts>
#include <type_traits>
#include <bit>
#include <cstdint>

//

namespace dym
{ ////

  //! Represents the dimensionality of vectors and matrices
  using dim_t = std::size_t;

  //! Relative equality for floats
  template <class T>
  static bool req(const T &l, const T &r, const T &tol = small_v<T>)
  {
    return std::abs(l - r) <= tol;
  }

  //! Square
  template <class T>
  static constexpr T sq(const T &v)
  {
    return v * v;
  }

  //! Cubic
  template <class T>
  static constexpr T cu(const T &v)
  {
    return v * v * v;
  }

  //! Generic power
  template <class T>
  static constexpr T pow(const T &v, const dim_t p)
  {
    T val = v;
    for (dim_t i = 0; i < p - 1; ++i)
    {
      val *= v;
    }
    return val;
  }

  //! Absolute value
  template <class T>
  static constexpr T abs(const T &v)
  {
    return (v > 0) ? v : -v;
  }

  //! Min
  template <class T>
  static constexpr T min(const T &l, const T &r)
  {
    return (l < r) ? l : r;
  }

  //! Max
  template <class T>
  static constexpr T max(const T &l, const T &r)
  {
    return (l > r) ? l : r;
  }

  //! Clamp
  template <class T>
  static constexpr T clamp(const T &v, const T &minv, const T &maxv)
  {
    return max(minv, min(v, maxv));
  }

  //! Clamp between 0 and 1
  template <class T>
  static constexpr T saturate(const T &v)
  {
    return max(0, min(v, 1));
  }

  
  //! Variation of the famous fast inverse square root
  //! Probably slower than the SSE rsqrtss instruction
  inline float fastinvsqrt(float v)
  {
    float vhalf = 0.5f * v;
    auto i = std::bit_cast<std::uint32_t>(v); //! reinterpret floating point as binary
    i = 0x5f375a7fu - (i >> 1);          //! get first best guess for invsqrt
    v = std::bit_cast<float>(i);         //! convert float binary back to float
    v = v * (1.5f - vhalf * v * v); //! use newton's approximation to determine better sqrt
    return v;
  }

  //! Slightly less fast variation of the famous fast inverse square root
  //! Probably slower than the SSE rsqrtss instruction
  inline float invsqrt(float v)
  {
    float vhalf = 0.5f * v;
    auto i = std::bit_cast<std::uint32_t>(v); //! reinterpret floating point as binary
    i = 0x5f375a7fu - (i >> 1);          //! get first best guess for invsqrt
    v = std::bit_cast<float>(i);         //! convert float binary back to float
    v = v * (1.5f - vhalf * v * v); //! use newton's approximation to determine better sqrt
    v = v * (1.5f - vhalf * v * v); //! do one more approximation to determine better result
    return v;
  }

  //! Linear interpolation
  template <class T, class D = float>
  static constexpr T lerp(const T& a, const T& b, D dv)
  {
    static_assert(std::is_floating_point_v<D>, "dv must be a floating-point type");
    return (a * (D{1} - dv)) + (b * dv);
  }
  
  //! Inverse linear interpolation
  template <class T, class D = float>
  static constexpr T invlerp(const T& a, const T& b, D dv)
  {
    static_assert(std::is_floating_point_v<D>, "dv must be a floating-point type");
    return (dv - a) / (b - a);
  }

  template <class T = float>
  static constexpr int sgn(T val)
  {
    return (T{0} < val) - (val < T{0});
  }

} ////

//

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//

#endif //DYM_UTIL_H_INCLUDED
