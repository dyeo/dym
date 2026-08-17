#ifndef DYM_VEC_H_INCLUDED
#define DYM_VEC_H_INCLUDED

//

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127)
#endif

//

#include "util.h"
#include "angle.h"
#include <cmath>
#include <ostream>
#include <concepts>

//

namespace dym
{ ////

  //! A d-length vector of type T
  template <dim_t D, class T = float>
  struct vec
  {
    using type = T;
    static constexpr dim_t dim = D;
    static constexpr dim_t size = D;

    ///////////////////
    //! DATA MEMBERS //
    ///////////////////

    //! Array containing vector data
    T data[size];

    ///////////////////
    //! CONSTRUCTORS //
    ///////////////////

    //! Default constructor
    constexpr vec()
    {
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = type{0};
      }
    }

    ~vec() = default;

    //! Component constructor
    template <class... U>
      requires (sizeof...(U) == size && (std::convertible_to<U, T> && ...))
    constexpr vec(const U &...values)
      : data{static_cast<T>(values)...}
    {
    }

    //! Copy constructor
    constexpr vec(const vec<D, T> &v)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = v.data[i];
      }
    }

    //! Copy constructor for arbitrarily larger vector
    template <dim_t D1>
    constexpr vec(const vec<D1, T> &v)
    {
      static_assert(D1 >= size, "Input vector must be larger than constructed vector");
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = v.data[i];
      }
    }

    //! Explicit type-conversion copy constructor
    template <class U>
    explicit constexpr vec(const vec<D, U> &v)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = static_cast<T>(v[i]);
      }
    }

    //! Fill constructor
    explicit constexpr vec(const T &s)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = s;
      }
    }

    //! Array initializer
    explicit constexpr vec(const T *a)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = a[i];
      }
    }

    ///////////////////////
    //! ACCESS OPERATORS //
    ///////////////////////

    //! Vector index operator
    constexpr T &operator[](const int i)
    {
      return data[i];
    }

    //! Vector const index operator
    constexpr const T &operator[](const int i) const
    {
      return data[i];
    }

    ///////////////////////////
    //! ARITHMETIC OPERATORS //
    ///////////////////////////

    //! Component-wise unary negation
    constexpr vec<D, T> operator-() const
    {
      return unary_transform([](const auto &value) { return -value; });
    }
    //! Component-wise unary negation
    constexpr vec<D, T> operator~() const
    {
      return unary_transform([](const auto &value) { return ~value; });
    }
    //! Vector assignment
    constexpr vec<D, T> &operator=(const vec<D, T> &v)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        data[i] = v.data[i];
      }
      return *this;
    }

    //! Component-wise vector multiplication
    constexpr vec<D, T> operator*(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left * right; });
    }
    //! Component-wise vector division
    constexpr vec<D, T> operator/(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left / right; });
    }
    //! Component-wise vector addition
    constexpr vec<D, T> operator+(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left + right; });
    }
    //! Component-wise vector subtraction
    constexpr vec<D, T> operator-(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left - right; });
    }
    //! Component-wise vector OR
    constexpr vec<D, T> operator|(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left | right; });
    }
    //! Component-wise vector AND
    constexpr vec<D, T> operator&(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left & right; });
    }
    //! Component-wise vector XOR
    constexpr vec<D, T> operator^(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left ^ right; });
    }
    //! Component-wise vector modulus
    constexpr vec<D, T> operator%(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left % right; });
    }
    //! Component-wise vector shift left
    constexpr vec<D, T> operator<<(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left << right; });
    }
    //! Component-wise vector shift right
    constexpr vec<D, T> operator>>(const vec<D, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left >> right; });
    }

    //! Component-wise scalar multiplication
    constexpr vec<D, T> operator*(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left * right; });
    }
    //! Component-wise scalar division
    constexpr vec<D, T> operator/(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left / right; });
    }
    //! Component-wise scalar addition
    constexpr vec<D, T> operator+(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left + right; });
    }
    //! Component-wise scalar subtraction
    constexpr vec<D, T> operator-(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left - right; });
    }
    //! Component-wise scalar OR
    constexpr vec<D, T> operator|(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left | right; });
    }
    //! Component-wise scalar AND
    constexpr vec<D, T> operator&(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left & right; });
    }
    //! Component-wise scalar XOR
    constexpr vec<D, T> operator^(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left ^ right; });
    }
    //! Component-wise scalar modulus
    constexpr vec<D, T> operator%(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left % right; });
    }
    //! Component-wise scalar shift left
    constexpr vec<D, T> operator<<(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left << right; });
    }
    //! Component-wise scalar shift right
    constexpr vec<D, T> operator>>(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left >> right; });
    }

    //! Component-wise vector reference multiplication
    constexpr vec<D, T> &operator*=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left *= right; });
    }
    //! Component-wise vector reference division
    constexpr vec<D, T> &operator/=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left /= right; });
    }
    //! Component-wise vector reference addition
    constexpr vec<D, T> &operator+=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left += right; });
    }
    //! Component-wise vector reference subtraction
    constexpr vec<D, T> &operator-=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left -= right; });
    }
    //! Component-wise vector reference OR
    constexpr vec<D, T> &operator|=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left |= right; });
    }
    //! Component-wise vector reference AND
    constexpr vec<D, T> &operator&=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left &= right; });
    }
    //! Component-wise vector reference XOR
    constexpr vec<D, T> &operator^=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left ^= right; });
    }
    //! Component-wise vector reference modulus
    constexpr vec<D, T> &operator%=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left %= right; });
    }
    //! Component-wise vector reference shift left
    constexpr vec<D, T> &operator<<=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left <<= right; });
    }
    //! Component-wise vector reference shift right
    constexpr vec<D, T> &operator>>=(const vec<D, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left >>= right; });
    }

    //! Component-wise scalar reference multiplication
    constexpr vec<D, T> &operator*=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left *= right; });
    }
    //! Component-wise scalar reference division
    constexpr vec<D, T> &operator/=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left /= right; });
    }
    //! Component-wise scalar reference addition
    constexpr vec<D, T> &operator+=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left += right; });
    }
    //! Component-wise scalar reference subtraction
    constexpr vec<D, T> &operator-=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left -= right; });
    }
    //! Component-wise scalar reference OR
    constexpr vec<D, T> &operator|=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left |= right; });
    }
    //! Component-wise scalar reference AND
    constexpr vec<D, T> &operator&=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left &= right; });
    }
    //! Component-wise scalar reference XOR
    constexpr vec<D, T> &operator^=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left ^= right; });
    }
    //! Component-wise scalar reference modulus
    constexpr vec<D, T> &operator%=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left %= right; });
    }
    //! Component-wise scalar reference shift left
    constexpr vec<D, T> &operator<<=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left <<= right; });
    }
    //! Component-wise scalar reference shift right
    constexpr vec<D, T> &operator>>=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left >>= right; });
    }

    //! Component-wise equality comparison
    constexpr bool operator==(const vec<D, T> &v) const
    {
      bool r = true;
      for (dim_t i = 0; i < size; ++i)
      {
        r &= data[i] == v.data[i];
      }
      return r;
    }
    //! Component-wise inequality comparison
    constexpr bool operator!=(const vec<D, T> &v) const
    {
      bool r = true;
      for (dim_t i = 0; i < size; ++i)
      {
        r |= data[i] != v.data[i];
      }
      return r;
    }

    //! Zero vector
    static constexpr vec<D, T> zero()
    {
      return vec<D, T>{T{0}};
    }

    //! Unit vector
    static constexpr vec<D, T> one()
    {
      return vec<D, T>{T{1}};
    }


  private:
    template <class F>
    constexpr vec<D, T> unary_transform(F operation) const
    {
      vec<D, T> res;
      for (dim_t i = 0; i < size; ++i)
      {
        res.data[i] = operation(data[i]);
      }
      return res;
    }

    template <class F>
    constexpr vec<D, T> binary_transform(const vec<D, T> &v, F operation) const
    {
      vec<D, T> res;
      for (dim_t i = 0; i < size; ++i)
      {
        res.data[i] = operation(data[i], v.data[i]);
      }
      return res;
    }

    template <class F>
    constexpr vec<D, T> scalar_transform(const T &v, F operation) const
    {
      vec<D, T> res;
      for (dim_t i = 0; i < size; ++i)
      {
        res.data[i] = operation(data[i], v);
      }
      return res;
    }

    template <class F>
    constexpr vec<D, T> &binary_assign(const vec<D, T> &v, F operation)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        operation(data[i], v.data[i]);
      }
      return *this;
    }

    template <class F>
    constexpr vec<D, T> &scalar_assign(const T &v, F operation)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        operation(data[i], v);
      }
      return *this;
    }

  }; //! struct vec

  //////////////////////
  //! MISC. OPERATORS //
  //////////////////////

  template <dim_t D, class T = float>
  static std::ostream &operator<<(std::ostream &os, const vec<D, T> &v)
  {
    os << "| ";
    for (dim_t i = 0; i < D; ++i)
    {
      os << v.data[i] << ' ';
    }
    os << "|";
    return os;
  }

  //! Scalar-Vector multiplication
  template <dim_t D, class T = float>
  static constexpr vec<D, T> operator*(const T &l, const vec<D, T> &r)
  {
    vec<D, T> res;
    for (dim_t i = 0; i < D; ++i)
    {
      res.data[i] = l * r[i];
    }
    return res;
  }

  /////////////////////
  //! FREE FUNCTIONS //
  /////////////////////

  //! Calculates the dot or scalar product of two vectors
  template <dim_t D, class T = float>
  static constexpr T dot(const vec<D, T> &l, const vec<D, T> &r)
  {
    T res = 0;
    for (dim_t i = 0; i < D; ++i)
    {
      res += l[i] * r[i];
    }
    return res;
  }

  //! Calculates the angle between two vectors
  template <dim_t D, class T = float>
  static ang<T> angle(const vec<D, T> &l, const vec<D, T> &r)
  {
    T dp = dot(l, r) / (magnitude(l) * magnitude(r));
    return radians(acos(dp));
  }

  //! Rotates the source vector around the ais vector by the specified angle
  template <dim_t D, class T = float>
  static vec<D, T> rotatearound(const vec<D, T> &src, const vec<D, T> &axs, const ang<T> &dlt)
  {
    T ct = cos(dlt.radians());
    T st = sin(dlt.radians());
    return (src * ct) + (cross(axs, src) * st) + (axs * dot(axs, src)) * (1 - ct);
  }

  //! Projects a vector onto another vector
  template <dim_t D, class T = float>
  static vec<D, T> project(const vec<D, T> &l, const vec<D, T> &r)
  {
    vec<D, T> normal = normalize(r);
    return normal * dot(l, normal);
  }

  //! Calculates the cross product of two vectors
  template <class T = float>
  static constexpr T cross(const vec<2, T> &l, const vec<2, T> &r)
  {
    return (l.data[0] * r.data[1]) - (l.data[0] * r.data[1]);
  }

  //! Calculates the cross product of two vectors
  template <class T = float>
  static constexpr vec<3, T> cross(const vec<3, T> &l, const vec<3, T> &r)
  {
    return vec<3, T>{
        (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]),
        (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]),
        (l.data[0] * r.data[1]) - (l.data[1] * r.data[0])};
  }

  //! Calculates the cross product of two vectors
  template <class T = float>
  static constexpr vec<4, T> cross(const vec<4, T> &l, const vec<4, T> &r)
  {
    return vec<4, T>{
        (l.data[1] * r.data[2]) - (l.data[2] * r.data[1]),
        (l.data[2] * r.data[0]) - (l.data[0] * r.data[2]),
        (l.data[0] * r.data[1]) - (l.data[1] * r.data[0]),
        T{0}};
  }

  //! Returns length squared of vector
  template <dim_t D, class T = float>
  static constexpr T lengthsq(const vec<D, T> &v)
  {
    T res = 0;
    for (dim_t i = 0; i < D; ++i)
    {
      res += sq(v.data[i]);
    }
    return res;
  }

  //! Returns length of vector, or sqrt(lengthsq)
  template <dim_t D, class T = float>
  static T length(const vec<D, T> &v)
  {
    T res = 0;
    for (dim_t i = 0; i < D; ++i)
    {
      res += sq(v.data[i]);
    }
    return sqrt(res);
  }

  //! Returns magnitude of vector, or length
  template <dim_t D, class T = float>
  static T magnitude(const vec<D, T> &v)
  {
    return length(v);
  }

  //! Normalizes vector so it is a unit vector
  template <dim_t D, class T = float>
  static vec<D, T> normalize(const vec<D, T> &v)
  {
    return v / length(v);
  }

  //! Returns a component-wise minimum of two vectors
  template <dim_t D, class T = float>
  static constexpr vec<D, T> min(const vec<D, T> &l, const vec<D, T> &r)
  {
    vec<D, T> res;
    for (dim_t i = 0; i < D; ++i)
    {
      res.data[i] = min((l[i], r[i]));
    }
    return res;
  }

  //! Returns a component-wise minimum of a vector and a scalar
  template <dim_t D, class T = float>
  static constexpr vec<D, T> min(const vec<D, T> &l, const T &r)
  {
    vec<D, T> res;
    for (dim_t i = 0; i < D; ++i)
    {
      res.data[i] = min((l[i], r));
    }
    return res;
  }

  //! Returns a component-wise maximum of two vectors
  template <dim_t D, class T = float>
  static constexpr vec<D, T> max(const vec<D, T> &l, const vec<D, T> &r)
  {
    vec<D, T> res;
    for (dim_t i = 0; i < D; ++i)
    {
      res.data[i] = max(l[i], r[i]);
    }
    return res;
  }

  //! Returns a component-wise maximum of a vector and a scalar
  template <dim_t D, class T = float>
  static constexpr vec<D, T> max(const vec<D, T> &l, const T &r)
  {
    vec<D, T> res;
    for (dim_t i = 0; i < D; ++i)
    {
      res.data[i] = max(l[i], r);
    }
    return res;
  }

  //! Clamps the value of a vector between a min and max vector
  template <dim_t D, class T = float>
  static constexpr vec<D, T> clamp(const vec<D, T> &v, const vec<D, T> &minV, const vec<D, T> &maxV)
  {
    return min(max(v, minV), maxV);
  }

  //! Clamps the value of a vector between a min and max scalar
  template <dim_t D, class T = float>
  static constexpr vec<D, T> clamp(const vec<D, T> &v, const T &minV, const T &maxV)
  {
    return min(max(v, minV), maxV);
  }

  //! Computes the distance between two vectors
  template <dim_t D, class T = float>
  static T distance(const vec<D, T> &l, const vec<D, T> &r)
  {
    return length(l - r);
  }

  //! Computes the distance squared between two vectors
  template <dim_t D, class T = float>
  static constexpr T distancesq(const vec<D, T> &l, const vec<D, T> &r)
  {
    return lengthsq(l - r);
  }

  //! Faces a normal forward according to the dot product of nRef and i
  template <dim_t D, class T = float>
  static constexpr vec<D, T> faceforward(const vec<D, T> &n, const vec<D, T> &i, const vec<D, T> &nRef)
  {
    return (dot(nRef, i) < 0) ? n : -n;
  }

  //! Computes the reflection of vector v acording to the plane of normal vector 'n'
  template <dim_t D, class T = float>
  static constexpr vec<D, T> reflect(const vec<D, T> &v, const vec<D, T> &n)
  {
    return v - 2.0f * dot(n, v) * n;
  }

  //! GLSL refraction function
  template <dim_t D, class T = float>
  static vec<D, T> refract(const vec<D, T> &v, const vec<D, T> &n, float r)
  {
    float dir = static_cast<T>(1.0) - r * r * (static_cast<T>(1.0) - dot(n, v) * dot(n, v));
    if (dir < static_cast<T>(0.0))
      return vec<D, T>{static_cast<T>(0.0)}; //! total internal reflection
    return r * v - (r * dot(n, v) + sqrt(dir)) * n;
  }

  //! Generates a vector one-dimension larger than the input vector, with the added dimension set to 1. useful for affine transfomrations
  template <dim_t D, class T = float>
  static constexpr vec<D + 1, T> affine(const vec<D, T> &v)
  {
    vec<D + 1, T> res;
    for (dim_t i = 0; i < D; ++i)
    {
      res[i] = v[i];
    }
    res[D] = T{1};
    return res;
  }

  //! Point vector constructor (xyz,1)
  template <class T = float>
  static constexpr vec<4, T> point(const vec<3, T> &xyz)
  {
    return vec<4, T>{xyz.data[0], xyz.data[1], xyz.data[2], T{1}};
  }

  //! Point vector constructor (x,y,z,1)
  template <class T = float>
  static constexpr vec<4, T> point(const T &x, const T &y, const T &z)
  {
    return vec<4, T>{x, y, z, T{1}};
  }

  //! Returns whether vector is NaN
  template <dim_t D, class T = float>
  static bool isnan(const vec<D, T> &v)
  {
    bool r = true;
    for (dim_t i = 0; i < D; ++i)
    {
      r &= std::isnan(v[i]);
    }
    return r;
  }

  //! Returns whether vector is inf
  template <dim_t D, class T = float>
  static bool isinf(const vec<D, T> &v)
  {
    bool r = true;
    for (dim_t i = 0; i < D; ++i)
    {
      r &= std::isinf(v[i]);
    }
    return r;
  }

  //! Relative equality (for floating-point vectors)
  template <dim_t D, class T = float>
  static bool req(const vec<D, T> &a, const vec<D, T> &b, const T& tol = small_v<T>)
  {
    bool r = true;
    for (dim_t i = 0; i < D; ++i)
    {
      r &= req(a[i], b[i], tol);
    }
    return r;
  }

  //! Component-wise saturation (clamp01)
  template <dim_t D, class T = float>
  static constexpr vec<D, T> saturate(const vec<D, T> &v)
  {
    return max(vec<D, T>::zero(), min(v, vec<D, T>::one()));
  }

} ////

//

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//

#endif //_DYM_VEC
