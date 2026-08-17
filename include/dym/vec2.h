#ifndef DYM_VEC2_H_INCLUDED
#define DYM_VEC2_H_INCLUDED

//

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127)
#endif

//

#include "vec.h"

#ifndef DYM_DISABLE_SWIZZLING
#include "swizzle2.h"
#include "swizzle3.h"
#include "swizzle4.h"
#include <initializer_list>
#include <cstddef>
#endif

//

namespace dym
{ ////

  template <class T>
  struct vec<2, T>
  {
    using type = T;
    static constexpr dim_t dim = 2;
    static constexpr dim_t size = 2;

    ///////////////////
    //! DATA MEMBERS //
    ///////////////////

    union
    {
      struct
      {
        T data[size];
      };
      struct
      {
        T x, y;
      };
      struct
      {
        T r, g;
      };
      struct
      {
        T s, t;
      };
#ifndef DYM_DISABLE_SWIZZLING
      swizzle2<0, 0, T> xx, rr, ss;
      swizzle2<0, 1, T> xy, rg, st;
      swizzle2<1, 0, T> yx, gr, ts;
      swizzle2<1, 1, T> yy, gg, tt;
      swizzle3<0, 0, 0, T> xxx, rrr, sss;
      swizzle3<0, 0, 1, T> xxy, rrg, sst;
      swizzle3<0, 1, 0, T> xyx, rgr, sts;
      swizzle3<0, 1, 1, T> xyy, rgg, stt;
      swizzle3<1, 0, 0, T> yxx, grr, tss;
      swizzle3<1, 0, 1, T> yxy, grg, tst;
      swizzle3<1, 1, 0, T> yyx, ggr, tts;
      swizzle3<1, 1, 1, T> yyy, ggg, ttt;
      swizzle4<0, 0, 0, 0, T> xxxx, rrrr, ssss;
      swizzle4<0, 0, 0, 1, T> xxxy, rrrg, ssst;
      swizzle4<0, 0, 1, 0, T> xxyx, rrgr, ssts;
      swizzle4<0, 0, 1, 1, T> xxyy, rrgg, sstt;
      swizzle4<0, 1, 0, 0, T> xyxx, rgrr, stss;
      swizzle4<0, 1, 0, 1, T> xyxy, rgrg, stst;
      swizzle4<0, 1, 1, 0, T> xyyx, rggr, stts;
      swizzle4<0, 1, 1, 1, T> xyyy, rggg, sttt;
      swizzle4<1, 0, 0, 0, T> yxxx, grrr, tsss;
      swizzle4<1, 0, 0, 1, T> yxxy, grrg, tsst;
      swizzle4<1, 0, 1, 0, T> yxyx, grgr, tsts;
      swizzle4<1, 0, 1, 1, T> yxyy, grgg, tstt;
      swizzle4<1, 1, 0, 0, T> yyxx, ggrr, ttss;
      swizzle4<1, 1, 0, 1, T> yyxy, ggrg, ttst;
      swizzle4<1, 1, 1, 0, T> yyyx, gggr, ttts;
      swizzle4<1, 1, 1, 1, T> yyyy, gggg, tttt;
#endif
    };

    ///////////////////
    //! CONSTRUCTORS //
    ///////////////////

    //! Default constructor
    constexpr vec()
      : x(T{0}), y(T{0})
    {
    }

    ~vec() = default;

    //! Initialize vec2 with two values
    constexpr vec(const T &s0, const T &s1)
      : x(s0), y(s1)
    {
    }

#ifndef DYM_DISABLE_SWIZZLING
    //! Swizzle constructor
    template <dim_t a, dim_t b>
    constexpr vec(const swizzle2<a, b, T> &s)
      : x(s[a]), y(s[b])
    {
    }
#endif

    //! Copy constructor
    constexpr vec(const vec<2, T> &v)
      : x(v.x), y(v.y)
    {
    }

    //! Explicit type-conversion copy constructor
    template <class U>
    explicit constexpr vec(const vec<2, U> &v)
      : x(static_cast<T>(v.x)), y(static_cast<T>(v.y))
    {
    }

    //! Fill constructor
    explicit constexpr vec(const T &s)
      : x(s), y(s)
    {
    }

    //! Array initializer
    explicit constexpr vec(const T *a)
      : x(a[0]), y(a[1])
    {
    }

    //! Initializer list constructor
    constexpr vec(std::initializer_list<T> l)
      : x(*(l.begin())), y(*(l.begin() + 1))
    {
    }

    //! Copy constructor for differently-sized vector
    template <dim_t d2>
    vec(const vec<d2, T> &v)
    {
      if (d2 < 2)
      {
        for (dim_t i = 0; i < d2; ++i)
        {
          data[i] = v.data[i];
        }
      }
      else
      {
        for (dim_t i = 0; i < 2; ++i)
        {
          data[i] = v.data[i];
        }
      }
    }

    ///////////////////////
    //! ACCESS OPERATORS //
    ///////////////////////

    //! Vector index operator
    constexpr T &operator[](const std::size_t i)
    {
      return data[i];
    }

    //! Vector const index operator
    constexpr const T &operator[](const std::size_t i) const
    {
      return data[i];
    }

    ///////////////////////////
    //! ARITHMETIC OPERATORS //
    ///////////////////////////

    //! Component-wise unary negation
    constexpr vec<2, T> operator-() const
    {
      return vec<2, T>(-x, -y);
    }
    //! Component-wise unary negation
    constexpr vec<2, T> operator~() const
    {
      return vec<2, T>(~x, ~y);
    }
    //! Vector assignment
    constexpr vec<2, T> &operator=(const vec<2, T> &v)
    {
      x = v.x;
      y = v.y;
      return *this;
    }

    //! Component-wise vector multiplication
    constexpr vec<2, T> operator*(const vec<2, T> &v) const
    {
      return vec<2, T>(x * v.x, y * v.y);
    }
    //! Component-wise vector division
    constexpr vec<2, T> operator/(const vec<2, T> &v) const
    {
      return vec<2, T>(x / v.x, y / v.y);
    }
    //! Component-wise vector addition
    constexpr vec<2, T> operator+(const vec<2, T> &v) const
    {
      return vec<2, T>(x + v.x, y + v.y);
    }
    //! Component-wise vector subtraction
    constexpr vec<2, T> operator-(const vec<2, T> &v) const
    {
      return vec<2, T>(x - v.x, y - v.y);
    }
    //! Component-wise vector OR
    constexpr vec<2, T> operator|(const vec<2, T> &v) const
    {
      return vec<2, T>(x | v.x, y | v.y);
    }
    //! Component-wise vector AND
    constexpr vec<2, T> operator&(const vec<2, T> &v) const
    {
      return vec<2, T>(x & v.x, y & v.y);
    }
    //! Component-wise vector XOR
    constexpr vec<2, T> operator^(const vec<2, T> &v) const
    {
      return vec<2, T>(x ^ v.x, y ^ v.y);
    }
    //! Component-wise vector modulus
    constexpr vec<2, T> operator%(const vec<2, T> &v) const
    {
      return vec<2, T>(x % v.x, y % v.y);
    }
    //! Component-wise vector shift left
    constexpr vec<2, T> operator<<(const vec<2, T> &v) const
    {
      return vec<2, T>(x << v.x, y << v.y);
    }
    //! Component-wise vector shift right
    constexpr vec<2, T> operator>>(const vec<2, T> &v) const
    {
      return vec<2, T>(x >> v.x, y >> v.y);
    }

    //! Component-wise scalar multiplication
    constexpr vec<2, T> operator*(const T &v) const
    {
      return vec<2, T>(x * v, y * v);
    }
    //! Component-wise scalar division
    constexpr vec<2, T> operator/(const T &v) const
    {
      return vec<2, T>(x / v, y / v);
    }
    //! Component-wise scalar addition
    constexpr vec<2, T> operator+(const T &v) const
    {
      return vec<2, T>(x + v, y + v);
    }
    //! Component-wise scalar subtraction
    constexpr vec<2, T> operator-(const T &v) const
    {
      return vec<2, T>(x - v, y - v);
    }
    //! Component-wise scalar OR
    constexpr vec<2, T> operator|(const T &v) const
    {
      return vec<2, T>(x | v, y | v);
    }
    //! Component-wise scalar AND
    constexpr vec<2, T> operator&(const T &v) const
    {
      return vec<2, T>(x & v, y & v);
    }
    //! Component-wise scalar XOR
    constexpr vec<2, T> operator^(const T &v) const
    {
      return vec<2, T>(x ^ v, y ^ v);
    }
    //! Component-wise scalar modulus
    constexpr vec<2, T> operator%(const T &v) const
    {
      return vec<2, T>(x % v, y % v);
    }
    //! Component-wise scalar shift left
    constexpr vec<2, T> operator<<(const T &v) const
    {
      return vec<2, T>(x << v, y << v);
    }
    //! Component-wise scalar shift right
    constexpr vec<2, T> operator>>(const T &v) const
    {
      return vec<2, T>(x >> v, y >> v);
    }

    //! Component-wise vector reference multiplication
    constexpr vec<2, T> &operator*=(const vec<2, T> &v)
    {
      x *= v.x;
      y *= v.y;
      return *this;
    }
    //! Component-wise vector reference division
    constexpr vec<2, T> &operator/=(const vec<2, T> &v)
    {
      x /= v.x;
      y /= v.y;
      return *this;
    }
    //! Component-wise vector reference addition
    constexpr vec<2, T> &operator+=(const vec<2, T> &v)
    {
      x += v.x;
      y += v.y;
      return *this;
    }
    //! Component-wise vector reference subtraction
    constexpr vec<2, T> &operator-=(const vec<2, T> &v)
    {
      x -= v.x;
      y -= v.y;
      return *this;
    }
    //! Component-wise vector reference OR
    constexpr vec<2, T> &operator|=(const vec<2, T> &v)
    {
      x |= v.x;
      y |= v.y;
      return *this;
    }
    //! Component-wise vector reference AND
    constexpr vec<2, T> &operator&=(const vec<2, T> &v)
    {
      x &= v.x;
      y &= v.y;
      return *this;
    }
    //! Component-wise vector reference XOR
    constexpr vec<2, T> &operator^=(const vec<2, T> &v)
    {
      x ^= v.x;
      y ^= v.y;
      return *this;
    }
    //! Component-wise vector reference modulus
    constexpr vec<2, T> &operator%=(const vec<2, T> &v)
    {
      x %= v.x;
      y %= v.y;
      return *this;
    }
    //! Component-wise vector reference shift left
    constexpr vec<2, T> &operator<<=(const vec<2, T> &v)
    {
      x <<= v.x;
      y <<= v.y;
      return *this;
    }
    //! Component-wise vector reference shift right
    constexpr vec<2, T> &operator>>=(const vec<2, T> &v)
    {
      x >>= v.x;
      y >>= v.y;
      return *this;
    }

    //! Component-wise scalar reference multiplication
    constexpr vec<2, T> &operator*=(const T &v)
    {
      x *= v;
      y *= v;
      return *this;
    }
    //! Component-wise scalar reference division
    constexpr vec<2, T> &operator/=(const T &v)
    {
      x /= v;
      y /= v;
      return *this;
    }
    //! Component-wise scalar reference addition
    constexpr vec<2, T> &operator+=(const T &v)
    {
      x += v;
      y += v;
      return *this;
    }
    //! Component-wise scalar reference subtraction
    constexpr vec<2, T> &operator-=(const T &v)
    {
      x -= v;
      y -= v;
      return *this;
    }
    //! Component-wise scalar reference OR
    constexpr vec<2, T> &operator|=(const T &v)
    {
      x |= v;
      y |= v;
      return *this;
    }
    //! Component-wise scalar reference AND
    constexpr vec<2, T> &operator&=(const T &v)
    {
      x &= v;
      y &= v;
      return *this;
    }
    //! Component-wise scalar reference XOR
    constexpr vec<2, T> &operator^=(const T &v)
    {
      x ^= v;
      y ^= v;
      return *this;
    }
    //! Component-wise scalar reference modulus
    constexpr vec<2, T> &operator%=(const T &v)
    {
      x %= v;
      y %= v;
      return *this;
    }
    //! Component-wise scalar reference shift left
    constexpr vec<2, T> &operator<<=(const T &v)
    {
      x <<= v;
      y <<= v;
      return *this;
    }
    //! Component-wise scalar reference shift right
    constexpr vec<2, T> &operator>>=(const T &v)
    {
      x >>= v;
      y >>= v;
      return *this;
    }

    //! Component-wise equality comparison
    constexpr bool operator==(const vec<2, T> &v) const
    {
      return x == v.x && y == v.y;
    }
    //! Component-wise inequality comparison
    constexpr bool operator!=(const vec<2, T> &v) const
    {
      return x != v.x || y != v.y;
    }

    //////////////////////////
    //! GENERATOR FUNCTIONS //
    //////////////////////////

    //! NaN vector (NaN, NaN)
    static constexpr vec<2, T> nan()
    {
      return vec<2, T>(NAN, NAN);
    }

    //! Infinity vector (inf, inf)
    static constexpr vec<2, T> inf()
    {
      return vec<2, T>(INFINITY, INFINITY);
    }

    //! Zero vector (0,0)
    static constexpr vec<2, T> zero()
    {
      return vec<2, T>(0, 0);
    }

    //! One vector (1,1)
    static constexpr vec<2, T> one()
    {
      return vec<2, T>(1, 1);
    }

    //! Up vector (0,1)
    static constexpr vec<2, T> up()
    {
      return vec<2, T>(0, 1);
    }

    //! Down vector (0,-1)
    static constexpr vec<2, T> down()
    {
      return vec<2, T>(0, -1);
    }

    //! Right vector (1,0)
    static constexpr vec<2, T> right()
    {
      return vec<2, T>(1, 0);
    }

    //! Left vector (-1,0)
    static constexpr vec<2, T> left()
    {
      return vec<2, T>(-1, 0);
    }

  }; //! struct vec2

  ///////////////////////
  //! TYPE DEFINITIONS //
  ///////////////////////
  using vec2 = vec<2, float>;
  using vec2f = vec2;
  using vec2d = vec<2, double>;
  using vec2uc = vec<2, unsigned char>;
  using vec2c = vec<2, char>;
  using vec2us = vec<2, unsigned short>;
  using vec2s = vec<2, short>;
  using vec2ui = vec<2, unsigned int>;
  using vec2i = vec<2, int>;
  using vec2ul = vec<2, unsigned long>;
  using vec2l = vec<2, long>;

  //////////////////////
  //! MISC. OPERATORS //
  //////////////////////

  template <class T = float>
  static std::ostream &operator<<(std::ostream &os, const vec<2, T> &v)
  {
    os << "| " << v.x << ' ' << v.y << " |";
    return os;
  }

  //! Scalar-Vector multiplication
  template <class T = float>
  static vec<2, T> operator*(const T &l, const vec<2, T> &r)
  {
    return vec<2, T>(l * r.x, l * r.y);
  }

  /////////////////////
  //! FREE FUNCTIONS //
  /////////////////////

  //! Calculates the dot or scalar product of two vectors
  template <class T = float>
  static T dot(const vec<2, T> &l, const vec<2, T> &r)
  {
    return (l.x * r.x) + (l.y * r.y);
  }

  //! Returns length squared of vector
  template <class T = float>
  static T lengthsq(const vec<2, T> &v)
  {
    return sq(v.x) + sq(v.y);
  }

  //! Returns length of vector, or sqrt(lengthsq)
  template <class T = float>
  static T length(const vec<2, T> &v)
  {
    return sqrt(sq(v.x) + sq(v.y));
  }

  //! Returns a component-wise minimum of two vectors
  template <class T = float>
  static vec<2, T> min(const vec<2, T> &l, const vec<2, T> &r)
  {
    return vec<2, T>(min(l.x, r.x), min(l.y, r.y));
  }

  //! Returns a component-wise maximum of a vector and a scalar
  template <class T = float>
  static vec<2, T> min(const vec<2, T> &l, const T &r)
  {
    return vec<2, T>(min(l.x, r), min(l.y, r));
  }

  //! Returns a component-wise minimum of two vectors
  template <class T = float>
  static vec<2, T> max(const vec<2, T> &l, const vec<2, T> &r)
  {
    return vec<2, T>(max(l.x, r.x), max(l.y, r.y));
  }

  //! Returns a component-wise maximum of a vector and a scalar
  template <class T = float>
  static vec<2, T> max(const vec<2, T> &l, const T &r)
  {
    return vec<2, T>(max(l.x, r), max(l.y, r));
  }

  //! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
  template <class T = float>
  static vec<3, T> affine(const vec<2, T> &v)
  {
    return vec<3, T>(v.x, v.y, T{1});
  }

  //! Returns whether vector is NaN
  template <class T = float>
  static bool isnan(const vec<2, T> &v)
  {
    return std::isnan(v.x) || std::isnan(v.y);
  }

  //! Returns whether vector is inf
  template <class T = float>
  static bool isinf(const vec<2, T> &v)
  {
    return std::isinf(v.x) || std::isinf(v.y);
  }

  //! Relative equality (for floating-point vectors)
  template <class T = float>
  static bool req(const vec<2, T> &l, const vec<2, T> &r, const T &tol = small_v<T>)
  {
    return req(l.x, r.x, tol) && req(l.y, r.y, tol);
  }

} ////

//

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//

#endif
