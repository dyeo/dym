#ifndef DYM_PERCENT_H_INCLUDED
#define DYM_PERCENT_H_INCLUDED

//

#include <ostream>

//

namespace dym
{ ////

  template <class T = float>
  struct perc
  { ////

    ///////////////////
    //! CONSTRUCTORS //
    ///////////////////

    //! Default constructor
    constexpr perc()
    {
      _val = T{0};
    }

    ~perc() = default;

    //! Copy constructor
    constexpr perc(const perc<T> &a)
    {
      _val = a._val;
    }

    //! Type conversion copy constructor
    template <class U>
    constexpr perc(const perc<U> &a)
    {
      _val = static_cast<T>(a._val);
    }

    //! Value constructor
    constexpr perc(const T &val) : _val(val)
    {
    }

    ///////////////////////////
    //! RIGHT-HAND OPERATORS //
    ///////////////////////////

    //! Unary negative percentage
    constexpr perc<T> operator-() const
    {
      return perc<T>(-_val);
    }

    //! Percent addition
    constexpr perc<T> operator+(const perc<T> &a) const
    {
      return perc<T>(_val + a._val);
    }

    //! Percent subtraction
    constexpr perc<T> operator-(const perc<T> &a) const
    {
      return perc<T>(_val - a._val);
    }

    //! Percent multiplication
    constexpr perc<T> operator*(const T &s) const
    {
      return perc<T>(_val * s);
    }

    //! Percent division
    constexpr perc<T> operator/(const T &s)
    {
      return perc<T>(_val / s);
    }

    //! Percent reference addition
    constexpr perc<T> &operator+=(const perc<T> &a)
    {
      _val += a._val;
      return *this;
    }

    //! Percent reference subtraction
    constexpr perc<T> &operator-=(const perc<T> &a)
    {
      _val -= a._val;
      return *this;
    }

    //! Percent reference multiplication
    constexpr perc<T> &operator*=(const T &s)
    {
      _val *= s;
      return *this;
    }

    //! Percent reference division
    constexpr perc<T> &operator/=(const T &s)
    {
      _val /= s;
      return *this;
    }

    ///////////////////////
    //! ACCESS FUNCTIONS //
    ///////////////////////

    constexpr T percent() const
    {
      return _val * static_cast<T>(100);
    }

    constexpr T value() const
    {
      return _val;
    }

  private:
    T _val = 0;

  }; ////

  //////////////////////////
  //! GENERATOR FUNCTIONS //
  //////////////////////////

  //! Creates an percentage from a value [0..1]
  template <class T = float>
  constexpr static perc<T> value(const T &val)
  {
    return perc<T>(val);
  }

  //! Creates an percentage from a percentage [0..100]
  template <class T = float>
  constexpr static perc<T> percent(const T &per)
  {
    return perc<T>(per / static_cast<T>(100));
  }

  ///////////////////////
  //! TYPE DEFINITIONS //
  ///////////////////////

  using percf = perc<float>;

  using percd = perc<double>;

  using perci = perc<int>;

  //////////////////////
  //! MISC. OPERATORS //
  //////////////////////

  inline std::ostream &operator<<(std::ostream &os, const perc<> &a)
  {
    os << a.percent() << "%";
    return os;
  }

} ////

///////////////
//! LITERALS //
///////////////

#ifndef DYM_DISABLE_LITERALS

constexpr inline dym::perc<float> operator"" _per(unsigned long long value)
{
  return dym::percent<float>(static_cast<float>(value));
}

constexpr inline dym::perc<float> operator"" _per(long double value)
{
  return dym::percent(static_cast<float>(value));
}

constexpr inline dym::perc<float> operator"" _val(unsigned long long value)
{
  return dym::value<float>(static_cast<float>(value));
}

constexpr inline dym::perc<float> operator"" _val(long double value)
{
  return dym::value<float>(static_cast<float>(value));
}

#endif

//

#endif
