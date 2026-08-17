#ifndef DYM_ANGLE_H_INCLUDED
#define DYM_ANGLE_H_INCLUDED

//

#include "constants.h"
#include <ostream>

//

namespace dym
{ ////

  template <class T = float>
  struct ang
  { ////

    ///////////////////
    //! CONSTRUCTORS //
    ///////////////////

    //! Default constructor
    constexpr ang()
    {
      _rads = T{0};
    }

    ~ang() = default;

    //! Copy constructor
    constexpr ang(const ang<T> &a)
    {
      _rads = a._rads;
    }

    //! Type conversion copy constructor
    template <class U>
    constexpr ang(const ang<U> &a)
    {
      _rads = static_cast<T>(a._rads);
    }

    //! Radian constructor
    constexpr ang(const T &rads) : _rads(rads)
    {
    }

    ///////////////////////////
    //! RIGHT-HAND OPERATORS //
    ///////////////////////////

    //! Unary negative angle
    constexpr ang<T> operator-() const
    {
      return ang<T>(-_rads);
    }

    //! Angle addition
    constexpr ang<T> operator+(const ang<T> &a) const
    {
      return ang<T>(_rads + a._rads);
    }

    //! Angle subtraction
    constexpr ang<T> operator-(const ang<T> &a) const
    {
      return ang<T>(_rads - a._rads);
    }

    //! Angle multiplication
    constexpr ang<T> operator*(const T &s) const
    {
      return ang<T>(_rads * s);
    }

    //! Angle division
    constexpr ang<T> operator/(const T &s) const
    {
      return ang<T>(_rads / s);
    }

    //! Angle reference addition
    constexpr ang<T> &operator+=(const ang<T> &a)
    {
      _rads += a._rads;
      return *this;
    }

    //! Angle reference subtraction
    constexpr ang<T> &operator-=(const ang<T> &a)
    {
      _rads -= a._rads;
      return *this;
    }

    //! Angle reference multiplication
    constexpr ang<T> &operator*=(const T &s)
    {
      _rads *= s;
      return *this;
    }

    //! Angle reference division
    constexpr ang<T> &operator/=(const T &s)
    {
      _rads /= s;
      return *this;
    }

    ///////////////////////
    //! ACCESS FUNCTIONS //
    ///////////////////////

    constexpr T degrees() const
    {
      return _rads * rad2deg_v<T>;
    }

    constexpr T radians() const
    {
      return _rads;
    }

  private:
    //! Private constructor.
    T _rads = 0;

  }; ////

  //////////////////////////
  //! GENERATOR FUNCTIONS //
  //////////////////////////

  //! Creates an angle in degrees
  template <class T = float>
  static constexpr ang<T> degrees(const T &deg)
  {
    return ang<float>(deg * deg2rad_v<T>);
  }

  //! Creates an angle in radians
  template <class T = float>
  static constexpr ang<> radians(const T &rad)
  {
    return ang<float>(rad);
  }

  ///////////////////////
  //! TYPE DEFINITIONS //
  ///////////////////////

  using angf = ang<float>;

  using angd = ang<double>;

  using angi = ang<int>;

  //////////////////////
  //! MISC. OPERATORS //
  //////////////////////

  template <class T = float>
  static std::ostream &operator<<(std::ostream &os, const ang<T> &a)
  {
    os << a.degrees() << "deg";
    return os;
  }

} ////

///////////////
//! LITERALS //
///////////////

#ifndef DYM_DISABLE_LITERALS

static constexpr dym::ang<float> operator"" _deg(unsigned long long value)
{
  return dym::degrees<float>(static_cast<float>(value));
}

static constexpr dym::ang<float> operator"" _deg(long double value)
{
  return dym::degrees<float>(static_cast<float>(value));
}

static constexpr dym::ang<float> operator"" _rad(unsigned long long value)
{
  return dym::radians<float>(static_cast<float>(value));
}

static constexpr dym::ang<float> operator"" _rad(long double value)
{
  return dym::radians<float>(static_cast<float>(value));
}

#endif

//

#endif
