#ifndef _DYM_VEC_H_
#define _DYM_VEC_H_

//

#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127)

//

#include "util.h"
#include "angle.h"
#include <cmath>
#include <ostream>

//

namespace dym
{ ////

  //! A d-length vector of type T
  template <int D, typename T = float>
  struct vec
  {
    ///////////////////
    //! DATA MEMBERS //
    ///////////////////

    //! Array containing vector data
    T data[D];

    ///////////////////
    //! CONSTRUCTORS //
    ///////////////////

    //! Default constructor
    constexpr vec()
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = static_cast<T>(0);
      }
    }

    ~vec() = default;

    //! Initializer list constructor
    constexpr vec(std::initializer_list<T> list)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = *(list.begin() + i);
      }
    }

    //! Copy constructor
    constexpr vec(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = v.data[i];
      }
    }

    //! Copy constructor for arbitrarily larger vector
    template <int D1>
    constexpr vec(const vec<D1, T> &v)
    {
      DYM_STATIC_ASSERT(D1 >= D);
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = v.data[i];
      }
    }

    //! Explicit type-conversion copy constructor
    template <typename U>
    explicit constexpr vec(const vec<D, U> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = static_cast<T>(v[i]);
      }
    }

    //! Fill constructor
    explicit constexpr vec(const T &s)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = s;
      }
    }

    //! Array initializer
    explicit constexpr vec(const T *a)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = a[i];
      }
    }

    ///////////////////////
    //! ACCESS OPERATORS //
    ///////////////////////

    //! Vector index operator
    T &operator[](const int i)
    {
      return data[i];
    }

    //! Vector const index operator
    const T &operator[](const int i) const
    {
      return data[i];
    }

    ///////////////////////////
    //! ARITHMETIC OPERATORS //
    ///////////////////////////

    //! Component-wise unary negation
    vec<D, T> operator-() const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = -data[i];
      }
      return res;
    }
    //! Component-wise unary negation
    vec<D, T> operator~() const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = ~data[i];
      }
      return res;
    }
    //! Vector assignment
    vec<D, T> &operator=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] = v.data[i];
      }
      return *this;
    }

    //! Component-wise vector multiplication
    vec<D, T> operator*(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] * v.data[i];
      }
      return res;
    }
    //! Component-wise vector division
    vec<D, T> operator/(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] / v.data[i];
      }
      return res;
    }
    //! Component-wise vector addition
    vec<D, T> operator+(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] + v.data[i];
      }
      return res;
    }
    //! Component-wise vector subtraction
    vec<D, T> operator-(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] - v.data[i];
      }
      return res;
    }
    //! Component-wise vector OR
    vec<D, T> operator|(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] | v.data[i];
      }
      return res;
    }
    //! Component-wise vector AND
    vec<D, T> operator&(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] & v.data[i];
      }
      return res;
    }
    //! Component-wise vector XOR
    vec<D, T> operator^(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] ^ v.data[i];
      }
      return res;
    }
    //! Component-wise vector modulus
    vec<D, T> operator%(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] % v.data[i];
      }
      return res;
    }
    //! Component-wise vector shift left
    vec<D, T> operator<<(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] << v.data[i];
      }
      return res;
    }
    //! Component-wise vector shift right
    vec<D, T> operator>>(const vec<D, T> &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] >> v.data[i];
      }
      return res;
    }

    //! Component-wise scalar multiplication
    vec<D, T> operator*(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] * v;
      }
      return res;
    }
    //! Component-wise scalar division
    vec<D, T> operator/(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] / v;
      }
      return res;
    }
    //! Component-wise scalar addition
    vec<D, T> operator+(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] + v;
      }
      return res;
    }
    //! Component-wise scalar subtraction
    vec<D, T> operator-(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] - v;
      }
      return res;
    }
    //! Component-wise scalar OR
    vec<D, T> operator|(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] | v;
      }
      return res;
    }
    //! Component-wise scalar AND
    vec<D, T> operator&(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] & v;
      }
      return res;
    }
    //! Component-wise scalar XOR
    vec<D, T> operator^(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] ^ v;
      }
      return res;
    }
    //! Component-wise scalar modulus
    vec<D, T> operator%(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] % v;
      }
      return res;
    }
    //! Component-wise scalar shift left
    vec<D, T> operator<<(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] << v;
      }
      return res;
    }
    //! Component-wise scalar shift right
    vec<D, T> operator>>(const T &v) const
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res.data[i] = data[i] >> v;
      }
      return res;
    }

    //! Component-wise vector reference multiplication
    vec<D, T> &operator*=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] *= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference division
    vec<D, T> &operator/=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] /= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference addition
    vec<D, T> &operator+=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] += v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference subtraction
    vec<D, T> &operator-=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] -= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference OR
    vec<D, T> &operator|=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] |= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference AND
    vec<D, T> &operator&=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] &= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference XOR
    vec<D, T> &operator^=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] ^= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference modulus
    vec<D, T> &operator%=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] %= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference shift left
    vec<D, T> &operator<<=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] <<= v.data[i];
      }
      return *this;
    }
    //! Component-wise vector reference shift right
    vec<D, T> &operator>>=(const vec<D, T> &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] >>= v.data[i];
      }
      return *this;
    }

    //! Component-wise scalar reference multiplication
    vec<D, T> &operator*=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] *= v;
      }
      return *this;
    }
    //! Component-wise scalar reference division
    vec<D, T> &operator/=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] /= v;
      }
      return *this;
    }
    //! Component-wise scalar reference addition
    vec<D, T> &operator+=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] += v;
      }
      return *this;
    }
    //! Component-wise scalar reference subtraction
    vec<D, T> &operator-=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] -= v;
      }
      return *this;
    }
    //! Component-wise scalar reference OR
    vec<D, T> &operator|=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] |= v;
      }
      return *this;
    }
    //! Component-wise scalar reference AND
    vec<D, T> &operator&=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] &= v;
      }
      return *this;
    }
    //! Component-wise scalar reference XOR
    vec<D, T> &operator^=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] ^= v;
      }
      return *this;
    }
    //! Component-wise scalar reference modulus
    vec<D, T> &operator%=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] %= v;
      }
      return *this;
    }
    //! Component-wise scalar reference shift left
    vec<D, T> &operator<<=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] <<= v;
      }
      return *this;
    }
    //! Component-wise scalar reference shift right
    vec<D, T> &operator>>=(const T &v)
    {
      for (size_t i = 0; i < D; ++i)
      {
        data[i] >>= v;
      }
      return *this;
    }

    //! Component-wise equality comparison
    bool operator==(const vec<D, T> &v) const
    {
      bool r = true;
      for (size_t i = 0; i < D; ++i)
      {
        r &= data[i] == v.data[i];
      }
      return r;
    }
    //! Component-wise inequality comparison
    bool operator!=(const vec<D, T> &v) const
    {
      bool r = true;
      for (size_t i = 0; i < D; ++i)
      {
        r |= data[i] != v.data[i];
      }
      return r;
    }

    //! Zero vector
    static constexpr vec<D, T> zero()
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res[i] = static_cast<T>(0);
      }
      return res;
    }

    //! Unit vector
    static constexpr vec<D, T> one()
    {
      vec<D, T> res;
      for (size_t i = 0; i < D; ++i)
      {
        res[i] = static_cast<T>(1);
      }
      return res;
    }

  }; //! struct vec

  //////////////////////
  //! MISC. OPERATORS //
  //////////////////////

  template <int D, typename T = float>
  static std::ostream &operator<<(std::ostream &os, const vec<D, T> &v)
  {
    os << "| ";
    for (size_t i = 0; i < D; ++i)
    {
      os << v.data[i] << ' ';
    }
    os << "|";
    return os;
  }

  //! Scalar-Vector multiplication
  template <int D, typename T = float>
  static vec<D, T> operator*(const T &l, const vec<D, T> &r)
  {
    vec<D, T> res;
    for (size_t i = 0; i < D; ++i)
    {
      res.data[i] = l * r[i];
    }
    return res;
  }

  /////////////////////
  //! FREE FUNCTIONS //
  /////////////////////

  //! Calculates the dot or scalar product of two vectors
  template <int D, typename T = float>
  static T dot(const vec<D, T> &l, const vec<D, T> &r)
  {
    T res = 0;
    for (size_t i = 0; i < D; ++i)
    {
      res += l[i] * r[i];
    }
    return res;
  }

  //! Calculates the angle between two vectors
  template <int D, typename T = float>
  static ang<T> angle(const vec<D, T> &l, const vec<D, T> &r)
  {
    T dp = dot(l, r) / (magnitude(l) * magnitude(r));
    return radians(acos(dp));
  }

  //! Rotates the source vector around the ais vector by the specified angle
  template <int D, typename T = float>
  static vec<D, T> rotatearound(const vec<D, T> &src, const vec<D, T> &axs, const ang<T> &dlt)
  {
    T ct = cos(dlt.radians());
    T st = sin(dlt.radians());
    return (src * ct) + (cross(axs, src) * st) + (axs * dot(axs, src)) * (1 - ct);
  }

  //! Projects a vector onto another vector
  template <int D, typename T = float>
  static vec<D, T> project(const vec<D, T> &l, const vec<D, T> &r)
  {
    vec<D, T> normal = normalize(r);
    return normal * dot(l, normal);
  }

  //! Calculates the cross product of two vectors
  template <typename T = float>
  static T cross(const vec<2, T> &l, const vec<2, T> &r)
  {
    return (l.data[0] * r.data[1]) - (l.data[0] * r.data[1]);
  }

  //! Calculates the cross product of two vectors
  template <typename T = float>
  static vec<3, T> cross(const vec<3, T> &l, const vec<3, T> &r)
  {
    vec<3, T> res;
    res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
    res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
    res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
    return res;
  }

  //! Calculates the cross product of two vectors
  template <typename T = float>
  static vec<4, T> cross(const vec<4, T> &l, const vec<4, T> &r)
  {
    vec<4, T> res;
    res.data[0] = (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]);
    res.data[1] = (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]);
    res.data[2] = (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]);
    res.data[3] = static_cast<T>(0);
    return res;
  }

  //! Returns length squared of vector
  template <int D, typename T = float>
  static T lengthsq(const vec<D, T> &v)
  {
    T res = 0;
    for (size_t i = 0; i < D; ++i)
    {
      res += sq(v.data[i]);
    }
    return res;
  }

  //! Returns length of vector, or sqrt(lengthsq)
  template <int D, typename T = float>
  static T length(const vec<D, T> &v)
  {
    T res = 0;
    for (size_t i = 0; i < D; ++i)
    {
      res += sq(v.data[i]);
    }
    return sqrt(res);
  }

  //! Returns magnitude of vector, or length
  template <int D, typename T = float>
  static T magnitude(const vec<D, T> &v)
  {
    return length(v);
  }

  //! Normalizes vector so it is a unit vector
  template <int D, typename T = float>
  static vec<D, T> normalize(const vec<D, T> &v)
  {
    return v / length(v);
  }

  //! Returns a component-wise minimum of two vectors
  template <int D, typename T = float>
  static vec<D, T> min(const vec<D, T> &l, const vec<D, T> &r)
  {
    vec<D, T> res;
    for (size_t i = 0; i < D; ++i)
    {
      res.data[i] = (l[i] < r[i]) ? l[i] : r[i];
    }
    return res;
  }

  //! Returns a component-wise maximum of a vector and a scalar
  template <int D, typename T = float>
  static vec<D, T> min(const vec<D, T> &l, const T &r)
  {
    vec<D, T> res;
    for (size_t i = 0; i < D; ++i)
    {
      res.data[i] = (l[i] < r) ? l[i] : r;
    }
    return res;
  }

  //! Returns a component-wise minimum of two vectors
  template <int D, typename T = float>
  static vec<D, T> max(const vec<D, T> &l, const vec<D, T> &r)
  {
    vec<D, T> res;
    for (size_t i = 0; i < D; ++i)
    {
      res.data[i] = (l[i] > r[i]) ? l[i] : r[i];
    }
    return res;
  }

  //! Returns a component-wise maximum of a vector and a scalar
  template <int D, typename T = float>
  static vec<D, T> max(const vec<D, T> &l, const T &r)
  {
    vec<D, T> res;
    for (size_t i = 0; i < D; ++i)
    {
      res.data[i] = (l[i] > r) ? l[i] : r;
    }
    return res;
  }

  //! Clamps the value of a vector between a min and max vector
  template <int D, typename T = float>
  static vec<D, T> clamp(const vec<D, T> &v, const vec<D, T> &minV, const vec<D, T> &maxV)
  {
    return min(max(v, minV), maxV);
  }

  //! Clamps the value of a vector between a min and max scalar
  template <int D, typename T = float>
  static vec<D, T> clamp(const vec<D, T> &v, const T &minV, const T &maxV)
  {
    return min(max(v, minV), maxV);
  }

  //! Computes the distance between two vectors
  template <int D, typename T = float>
  static T distance(const vec<D, T> &l, const vec<D, T> &r)
  {
    return length(l - r);
  }

  //! Computes the distance squared between two vectors
  template <int D, typename T = float>
  static T distancesq(const vec<D, T> &l, const vec<D, T> &r)
  {
    return lengthsq(l - r);
  }

  //! Faces a normal forward according to the dot product of nRef and i
  template <int D, typename T = float>
  static vec<D, T> faceforward(const vec<D, T> &n, const vec<D, T> &i, const vec<D, T> &nRef)
  {
    return (dot(nRef, i) < 0) ? n : -n;
  }

  //! Computes the reflection of vector v acording to the plane of normal vector 'n'
  template <int D, typename T = float>
  static vec<D, T> reflect(const vec<D, T> &v, const vec<D, T> &n)
  {
    return v - 2.0f * dot(n, v) * n;
  }

  //! GLSL refraction function
  template <int D, typename T = float>
  static vec<D, T> refract(const vec<D, T> &v, const vec<D, T> &n, float r)
  {
    float dir = static_cast<T>(1.0) - r * r * (static_cast<T>(1.0) - dot(n, v) * dot(n, v));
    if (dir < static_cast<T>(0.0))
      return vec<D, T>(static_cast<T>(0.0)); //! total internal reflection
    return r * v - (r * dot(n, v) + sqrt(dir)) * n;
  }

  //! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
  template <int D, typename T = float>
  static vec<D + 1, T> affine(const vec<D, T> &v)
  {
    vec<D + 1, T> res;
    for (size_t i = 0; i < D; ++i)
    {
      res[i] = v[i];
    }
    res[D] = static_cast<T>(1);
    return res;
  }

  //! Point vector constructor (xyz,1)
  template <typename T = float>
  static vec<4, T> point(const vec<3, T> &xyz)
  {
    return vec<4, T>(xyz.data[0], xyz.data[1], xyz.data[2], static_cast<T>(1));
  }

  //! Point vector constructor (x,y,z,1)
  template <typename T = float>
  static vec<4, T> point(const T &x, const T &y, const T &z)
  {
    return vec<4, T>(x, y, z, static_cast<T>(1));
  }

  //! Returns whether vector is NaN
  template <int D, typename T = float>
  static bool isnan(const vec<D, T> &v)
  {
    bool r = true;
    for (size_t i = 0; i < D; ++i)
    {
      r &= std::isnan(v[i]);
    }
    return r;
  }

  //! Returns whether vector is inf
  template <int D, typename T = float>
  static bool isinf(const vec<D, T> &v)
  {
    bool r = true;
    for (size_t i = 0; i < D; ++i)
    {
      r &= std::isinf(v[i]);
    }
    return r;
  }

  //! Relative equality (for floating-point vectors)
  template <int D, typename T = float>
  static bool req(const vec<D, T> &a, const vec<D, T> &b, T rng = small_v<T>)
  {
    bool r = true;
    for (size_t i = 0; i < D; ++i)
    {
      r &= req(a[i], b[i], rng);
    }
    return r;
  }

  //! Component-wise saturation (clamp01)
  template <int D, typename T = float>
  static vec<D, T> saturate(const vec<D, T> &v)
  {
    return max(vec<D, T>::zero(), min(v, vec<D, T>::one()));
  }

} ////

//

#pragma warning(pop)

//

#endif //_DYM_VEC