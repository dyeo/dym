#ifndef DYM_MAT3_H_INCLUDED
#define DYM_MAT3_H_INCLUDED

//

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127)
#endif

//

#include "mat.h"
#include <cstddef>

//

namespace dym
{ ////

  //! A specialized 3x3 square matrix
  template <class T>
  struct mat<3, 3, T>
  {
    using type = T;
    static constexpr dim_t cols = 3;
    static constexpr dim_t rows = 3;
    static constexpr dim_t dim = 3;
    static constexpr dim_t size = 9;

    ///////////////////
    //! DATA MEMBERS //
    ///////////////////

    //! Unioned data members
    union
    {
      struct
      {
        vec<cols, T> data[rows];
      };
      struct
      {
        T arr[size];
      };
    };

    ///////////////////
    //! CONSTRUCTORS //
    ///////////////////

    //! Default constructor
    constexpr mat()
        : arr{T{1}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{1}}
    {
    }

    ~mat() = default;


    //! Copy constructor
    constexpr mat(const mat<3, 3, T> &v)
        : arr{v.arr[0], v.arr[1], v.arr[2], v.arr[3], v.arr[4], v.arr[5], v.arr[6], v.arr[7], v.arr[8]}
    {
    }

    //! Explicit type-conversion copy constructor
    template <class U>
    explicit constexpr mat(const mat<3, 3, U> &v)
        : arr{static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]), static_cast<T>(v.arr[3]), static_cast<T>(v.arr[4]), static_cast<T>(v.arr[5]), static_cast<T>(v.arr[6]), static_cast<T>(v.arr[7]), static_cast<T>(v.arr[8])}
    {
    }

    //! Fill constructor
    explicit constexpr mat(const T &s)
        : arr{s, s, s, s, s, s, s, s, s}
    {
    }

    //! Array initializer
    explicit constexpr mat(const T *a)
        : arr{a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]}
    {
    }

    //! Value constructor
    constexpr mat(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8)
        : arr{s0, s1, s2, s3, s4, s5, s6, s7, s8}
    {
    }

    //! Explicit type-conversionm value constructor
    template <class U>
    explicit constexpr mat(const U &s0, const U &s1, const U &s2, const U &s3, const U &s4, const U &s5, const U &s6, const U &s7, const U &s8)
        : arr{static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(s3), static_cast<T>(s4), static_cast<T>(s5), static_cast<T>(s6), static_cast<T>(s7), static_cast<T>(s8)}
    {
    }

    //! Inserts a 2x2 matrix into the top-left portion of a 3x3 identity matrix
    //! ident adjusts the identity value
    constexpr mat(const mat<2, 2, T> &m, const T &ident = T{1})
        : arr{m.arr[0], m.arr[1], 0, m.arr[2], m.arr[3], 0, 0, 0, ident}
    {
    }

    //! Constructs a 3x3 matrix using the top-left portion of a 4x4 matrix
    constexpr mat(const mat<4, 4, T> &m)
        : arr{m.arr[0], m.arr[1], m.arr[2], m.arr[4], m.arr[5], m.arr[6], m.arr[8], m.arr[9], m.arr[10]}
    {
    }

    //! Minor matrix constructor
    template <dim_t C1, dim_t R1>
    constexpr mat(const mat<C1, R1, T> &m)
    {
      static_assert((C1 < cols) && (R1 < rows), "Minor matrix must be smaller than original matrix");
      for (dim_t i = 0; i < C1; ++i)
      {
        for (dim_t j = 0; j < R1; ++j)
        {
          data[i][j] = m.data[i][j];
        }
      }
    }

    ///////////////////////
    //! ACCESS OPERATORS //
    ///////////////////////

    //! Column function - returns column as vector of T
    constexpr vec<3, T> col(const dim_t i) const
    {
      return data[i];
    }

    //! Row function - returns row as vector of T
    constexpr vec<3, T> row(const dim_t i) const
    {
      vec<3, T> v{arr[i], arr[i + 3], arr[i + 6]};
      return v;
    }

    //! Matrix index operator - returns column
    constexpr vec<3, T> &operator[](const dim_t i)
    {
      return data[i];
    }

    //! Matrix const index operator - returns column
    constexpr const vec<3, T> &operator[](const dim_t i) const
    {
      return data[i];
    }

    //! Matrix linear array index operator - returns element
    constexpr T &operator()(const dim_t i)
    {
      return arr[i];
    }

    //! Matrix linear array const index operator - returns element
    constexpr const T &operator()(const dim_t i) const
    {
      return arr[i];
    }

    ////////////////
    //! OPERATORS //
    ////////////////

    //! Component-wise unary negation
    constexpr mat<3, 3, T> operator-() const
    {
      return mat<3, 3, T>(-arr[0], -arr[1], -arr[2], -arr[3], -arr[4], -arr[5], -arr[6], -arr[7], -arr[8]);
    }
    //! Component-wise unary negation
    constexpr mat<3, 3, T> operator~() const
    {
      return mat<3, 3, T>(~arr[0], ~arr[1], ~arr[2], ~arr[3], ~arr[4], ~arr[5], ~arr[6], ~arr[7], ~arr[8]);
    }
    //! Vector assignment
    constexpr mat<3, 3, T> &operator=(const mat<3, 3, T> &m)
    {
      arr[0] = m.arr[0];
      arr[1] = m.arr[1];
      arr[2] = m.arr[2];
      arr[3] = m.arr[3];
      arr[4] = m.arr[4];
      arr[5] = m.arr[5];
      arr[6] = m.arr[6];
      arr[7] = m.arr[7];
      arr[8] = m.arr[8];
      return *this;
    }

    //! Component-wise matrix addition
    constexpr mat<3, 3, T> operator+(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] + m.arr[0], arr[1] + m.arr[1], arr[2] + m.arr[2], arr[3] + m.arr[3], arr[4] + m.arr[4], arr[5] + m.arr[5], arr[6] + m.arr[6], arr[7] + m.arr[7], arr[8] + m.arr[8]);
    }
    //! Component-wise matrix subtraction
    constexpr mat<3, 3, T> operator-(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] - m.arr[0], arr[1] - m.arr[1], arr[2] - m.arr[2], arr[3] - m.arr[3], arr[4] - m.arr[4], arr[5] - m.arr[5], arr[6] - m.arr[6], arr[7] - m.arr[7], arr[8] - m.arr[8]);
    }
    //! Component-wise matrix OR
    constexpr mat<3, 3, T> operator|(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] | m.arr[0], arr[1] | m.arr[1], arr[2] | m.arr[2], arr[3] | m.arr[3], arr[4] | m.arr[4], arr[5] | m.arr[5], arr[6] | m.arr[6], arr[7] | m.arr[7], arr[8] | m.arr[8]);
    }
    //! Component-wise matrix AND
    constexpr mat<3, 3, T> operator&(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] & m.arr[0], arr[1] & m.arr[1], arr[2] & m.arr[2], arr[3] & m.arr[3], arr[4] & m.arr[4], arr[5] & m.arr[5], arr[6] & m.arr[6], arr[7] & m.arr[7], arr[8] & m.arr[8]);
    }
    //! Component-wise matrix XOR
    constexpr mat<3, 3, T> operator^(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] ^ m.arr[0], arr[1] ^ m.arr[1], arr[2] ^ m.arr[2], arr[3] ^ m.arr[3], arr[4] ^ m.arr[4], arr[5] ^ m.arr[5], arr[6] ^ m.arr[6], arr[7] ^ m.arr[7], arr[8] ^ m.arr[8]);
    }
    //! Component-wise matrix modulus
    constexpr mat<3, 3, T> operator%(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] % m.arr[0], arr[1] % m.arr[1], arr[2] % m.arr[2], arr[3] % m.arr[3], arr[4] % m.arr[4], arr[5] % m.arr[5], arr[6] % m.arr[6], arr[7] % m.arr[7], arr[8] % m.arr[8]);
    }
    //! Component-wise matrix shift left
    constexpr mat<3, 3, T> operator<<(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] << m.arr[0], arr[1] << m.arr[1], arr[2] << m.arr[2], arr[3] << m.arr[3], arr[4] << m.arr[4], arr[5] << m.arr[5], arr[6] << m.arr[6], arr[7] << m.arr[7], arr[8] << m.arr[8]);
    }
    //! Component-wise matrix shift right
    constexpr mat<3, 3, T> operator>>(const mat<3, 3, T> &m) const
    {
      return mat<3, 3, T>(arr[0] >> m.arr[0], arr[1] >> m.arr[1], arr[2] >> m.arr[2], arr[3] >> m.arr[3], arr[4] >> m.arr[4], arr[5] >> m.arr[5], arr[6] >> m.arr[6], arr[7] >> m.arr[7], arr[8] >> m.arr[8]);
    }

    //! Component-wise scalar multiplication
    constexpr mat<3, 3, T> operator*(const T &v) const
    {
      return mat<3, 3, T>(arr[0] * v, arr[1] * v, arr[2] * v, arr[3] * v, arr[4] * v, arr[5] * v, arr[6] * v, arr[7] * v, arr[8] * v);
    }
    //! Component-wise scalar division
    constexpr mat<3, 3, T> operator/(const T &v) const
    {
      return mat<3, 3, T>(arr[0] / v, arr[1] / v, arr[2] / v, arr[3] / v, arr[4] / v, arr[5] / v, arr[6] / v, arr[7] / v, arr[8] / v);
    }
    //! Component-wise scalar addition
    constexpr mat<3, 3, T> operator+(const T &v) const
    {
      return mat<3, 3, T>(arr[0] + v, arr[1] + v, arr[2] + v, arr[3] + v, arr[4] + v, arr[5] + v, arr[6] + v, arr[7] + v, arr[8] + v);
    }
    //! Component-wise scalar subtraction
    constexpr mat<3, 3, T> operator-(const T &v) const
    {
      return mat<3, 3, T>(arr[0] - v, arr[1] - v, arr[2] - v, arr[3] - v, arr[4] - v, arr[5] - v, arr[6] - v, arr[7] - v, arr[8] - v);
    }
    //! Component-wise scalar OR
    constexpr mat<3, 3, T> operator|(const T &v) const
    {
      return mat<3, 3, T>(arr[0] | v, arr[1] | v, arr[2] | v, arr[3] | v, arr[4] | v, arr[5] | v, arr[6] | v, arr[7] | v, arr[8] | v);
    }
    //! Component-wise scalar AND
    constexpr mat<3, 3, T> operator&(const T &v) const
    {
      return mat<3, 3, T>(arr[0] & v, arr[1] & v, arr[2] & v, arr[3] & v, arr[4] & v, arr[5] & v, arr[6] & v, arr[7] & v, arr[8] & v);
    }
    //! Component-wise scalar XOR
    constexpr mat<3, 3, T> operator^(const T &v) const
    {
      return mat<3, 3, T>(arr[0] ^ v, arr[1] ^ v, arr[2] ^ v, arr[3] ^ v, arr[4] ^ v, arr[5] ^ v, arr[6] ^ v, arr[7] ^ v, arr[8] ^ v);
    }
    //! Component-wise scalar modulus
    constexpr mat<3, 3, T> operator%(const T &v) const
    {
      return mat<3, 3, T>(arr[0] % v, arr[1] % v, arr[2] % v, arr[3] % v, arr[4] % v, arr[5] % v, arr[6] % v, arr[7] % v, arr[8] % v);
    }
    //! Component-wise scalar shift left
    constexpr mat<3, 3, T> operator<<(const T &v) const
    {
      return mat<3, 3, T>(arr[0] << v, arr[1] << v, arr[2] << v, arr[3] << v, arr[4] << v, arr[5] << v, arr[6] << v, arr[7] << v, arr[8] << v);
    }
    //! Component-wise scalar shift right
    constexpr mat<3, 3, T> operator>>(const T &v) const
    {
      return mat<3, 3, T>(arr[0] >> v, arr[1] >> v, arr[2] >> v, arr[3] >> v, arr[4] >> v, arr[5] >> v, arr[6] >> v, arr[7] >> v, arr[8] >> v);
    }

    //! Component-wise matrix reference addition
    constexpr mat<3, 3, T> &operator+=(const mat<3, 3, T> &m)
    {
      arr[0] += m.arr[0];
      arr[1] += m.arr[1];
      arr[2] += m.arr[2];
      arr[3] += m.arr[3];
      arr[4] += m.arr[4];
      arr[5] += m.arr[5];
      arr[6] += m.arr[6];
      arr[7] += m.arr[7];
      arr[8] += m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference subtraction
    constexpr mat<3, 3, T> &operator-=(const mat<3, 3, T> &m)
    {
      arr[0] -= m.arr[0];
      arr[1] -= m.arr[1];
      arr[2] -= m.arr[2];
      arr[3] -= m.arr[3];
      arr[4] -= m.arr[4];
      arr[5] -= m.arr[5];
      arr[6] -= m.arr[6];
      arr[7] -= m.arr[7];
      arr[8] -= m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference OR
    constexpr mat<3, 3, T> &operator|=(const mat<3, 3, T> &m)
    {
      arr[0] |= m.arr[0];
      arr[1] |= m.arr[1];
      arr[2] |= m.arr[2];
      arr[3] |= m.arr[3];
      arr[4] |= m.arr[4];
      arr[5] |= m.arr[5];
      arr[6] |= m.arr[6];
      arr[7] |= m.arr[7];
      arr[8] |= m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference AND
    constexpr mat<3, 3, T> &operator&=(const mat<3, 3, T> &m)
    {
      arr[0] &= m.arr[0];
      arr[1] &= m.arr[1];
      arr[2] &= m.arr[2];
      arr[3] &= m.arr[3];
      arr[4] &= m.arr[4];
      arr[5] &= m.arr[5];
      arr[6] &= m.arr[6];
      arr[7] &= m.arr[7];
      arr[8] &= m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference XOR
    constexpr mat<3, 3, T> &operator^=(const mat<3, 3, T> &m)
    {
      arr[0] ^= m.arr[0];
      arr[1] ^= m.arr[1];
      arr[2] ^= m.arr[2];
      arr[3] ^= m.arr[3];
      arr[4] ^= m.arr[4];
      arr[5] ^= m.arr[5];
      arr[6] ^= m.arr[6];
      arr[7] ^= m.arr[7];
      arr[8] ^= m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference modulus
    constexpr mat<3, 3, T> &operator%=(const mat<3, 3, T> &m)
    {
      arr[0] %= m.arr[0];
      arr[1] %= m.arr[1];
      arr[2] %= m.arr[2];
      arr[3] %= m.arr[3];
      arr[4] %= m.arr[4];
      arr[5] %= m.arr[5];
      arr[6] %= m.arr[6];
      arr[7] %= m.arr[7];
      arr[8] %= m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference shift left
    constexpr mat<3, 3, T> &operator<<=(const mat<3, 3, T> &m)
    {
      arr[0] <<= m.arr[0];
      arr[1] <<= m.arr[1];
      arr[2] <<= m.arr[2];
      arr[3] <<= m.arr[3];
      arr[4] <<= m.arr[4];
      arr[5] <<= m.arr[5];
      arr[6] <<= m.arr[6];
      arr[7] <<= m.arr[7];
      arr[8] <<= m.arr[8];
      return *this;
    }
    //! Component-wise matrix reference shift right
    constexpr mat<3, 3, T> &operator>>=(const mat<3, 3, T> &m)
    {
      arr[0] >>= m.arr[0];
      arr[1] >>= m.arr[1];
      arr[2] >>= m.arr[2];
      arr[3] >>= m.arr[3];
      arr[4] >>= m.arr[4];
      arr[5] >>= m.arr[5];
      arr[6] >>= m.arr[6];
      arr[7] >>= m.arr[7];
      arr[8] >>= m.arr[8];
      return *this;
    }

    //! Component-wise scalar reference multiplication
    constexpr mat<3, 3, T> &operator*=(const T &v)
    {
      arr[0] *= v;
      arr[1] *= v;
      arr[2] *= v;
      arr[3] *= v;
      arr[4] *= v;
      arr[5] *= v;
      arr[6] *= v;
      arr[7] *= v;
      arr[8] *= v;
      return *this;
    }
    //! Component-wise scalar reference division
    constexpr mat<3, 3, T> &operator/=(const T &v)
    {
      arr[0] /= v;
      arr[1] /= v;
      arr[2] /= v;
      arr[3] /= v;
      arr[4] /= v;
      arr[5] /= v;
      arr[6] /= v;
      arr[7] /= v;
      arr[8] /= v;
      return *this;
    }
    //! Component-wise scalar reference addition
    constexpr mat<3, 3, T> &operator+=(const T &v)
    {
      arr[0] += v;
      arr[1] += v;
      arr[2] += v;
      arr[3] += v;
      arr[4] += v;
      arr[5] += v;
      arr[6] += v;
      arr[7] += v;
      arr[8] += v;
      return *this;
    }
    //! Component-wise scalar reference subtraction
    constexpr mat<3, 3, T> &operator-=(const T &v)
    {
      arr[0] -= v;
      arr[1] -= v;
      arr[2] -= v;
      arr[3] -= v;
      arr[4] -= v;
      arr[5] -= v;
      arr[6] -= v;
      arr[7] -= v;
      arr[8] -= v;
      return *this;
    }
    //! Component-wise scalar reference OR
    constexpr mat<3, 3, T> &operator|=(const T &v)
    {
      arr[0] |= v;
      arr[1] |= v;
      arr[2] |= v;
      arr[3] |= v;
      arr[4] |= v;
      arr[5] |= v;
      arr[6] |= v;
      arr[7] |= v;
      arr[8] |= v;
      return *this;
    }
    //! Component-wise scalar reference AND
    constexpr mat<3, 3, T> &operator&=(const T &v)
    {
      arr[0] &= v;
      arr[1] &= v;
      arr[2] &= v;
      arr[3] &= v;
      arr[4] &= v;
      arr[5] &= v;
      arr[6] &= v;
      arr[7] &= v;
      arr[8] &= v;
      return *this;
    }
    //! Component-wise scalar reference XOR
    constexpr mat<3, 3, T> &operator^=(const T &v)
    {
      arr[0] ^= v;
      arr[1] ^= v;
      arr[2] ^= v;
      arr[3] ^= v;
      arr[4] ^= v;
      arr[5] ^= v;
      arr[6] ^= v;
      arr[7] ^= v;
      arr[8] ^= v;
      return *this;
    }
    //! Component-wise scalar reference modulus
    constexpr mat<3, 3, T> &operator%=(const T &v)
    {
      arr[0] %= v;
      arr[1] %= v;
      arr[2] %= v;
      arr[3] %= v;
      arr[4] %= v;
      arr[5] %= v;
      arr[6] %= v;
      arr[7] %= v;
      arr[8] %= v;
      return *this;
    }
    //! Component-wise scalar reference shift left
    constexpr mat<3, 3, T> &operator<<=(const T &v)
    {
      arr[0] <<= v;
      arr[1] <<= v;
      arr[2] <<= v;
      arr[3] <<= v;
      arr[4] <<= v;
      arr[5] <<= v;
      arr[6] <<= v;
      arr[7] <<= v;
      arr[8] <<= v;
      return *this;
    }
    //! Component-wise scalar reference shift right
    constexpr mat<3, 3, T> &operator>>=(const T &v)
    {
      arr[0] >>= v;
      arr[1] >>= v;
      arr[2] >>= v;
      arr[3] >>= v;
      arr[4] >>= v;
      arr[5] >>= v;
      arr[6] >>= v;
      arr[7] >>= v;
      arr[8] >>= v;
      return *this;
    }

    //////////////////////////
    //! GENERATOR FUNCTIONS //
    //////////////////////////

    //! Returns an identity matrix
    static constexpr mat<3, 3, T> identity()
    {
      return mat<3, 3, T>{T{1}, T{0}, T{0}, T{0}, T{1}, T{0}, T{0}, T{0}, T{1}};
    }

    //! Creates a row-order matrix using individual elements
    static constexpr mat<3, 3, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3, const T &s4, const T &s5, const T &s6, const T &s7, const T &s8)
    {
      return mat<3, 3, T>{s0, s3, s6,
                          s1, s4, s7,
                          s2, s5, s8};
    }

    //! Creates a 3x3 matrix using 3 row vectors
    static constexpr mat<3, 3, T> fromrows(vec<3, T> r0, vec<3, T> r1, vec<3, T> r2)
    {
      return mat<3, 3, T>{r0.x, r1.x, r2.x,
                          r0.y, r1.y, r2.y,
                          r0.z, r1.z, r2.z};
    }

    //! Creates a 3x3 matrix using 3 column vectors
    static constexpr mat<3, 3, T> fromcols(vec<3, T> c0, vec<3, T> c1, vec<3, T> c2)
    {
      return mat<3, 3, T>{c0.x, c0.y, c0.z,
                          c1.x, c1.y, c1.z,
                          c2.x, c2.y, c2.z};
    }

    //! Rotate an axis about a given angle
    static mat<3, 3, T> rotate(const ang<T> &an, const vec<3, T> &ax)
    {
      T c = cos(an.radians());
      T s = sin(an.radians());
      T t = 1 - c;
      return mat<3, 3, T>{(t * ax.x * ax.x) + c, (t * ax.x * ax.y) + ax.z * s, (t * ax.x * ax.z) - ax.y * s,
                          (t * ax.x * ax.y) - ax.z * s, (t * ax.y * ax.y) + c, (t * ax.y * ax.z) + ax.x * s,
                          (t * ax.x * ax.z) + ax.y * s, (t * ax.y * ax.z) - ax.x * s, (t * ax.z * ax.z) + c};
    }

    //! Rotate axis x about a given angle
    static mat<3, 3, T> rotatex(const ang<T> &x)
    {
      T c = cos(x.radians());
      T s = sin(x.radians());
      return mat<3, 3, T>{T{1}, T{0}, T{0},
                          T{0}, c, s,
                          T{0}, -s, c};
    }

    //! Rotate axis y about a given angle
    static mat<3, 3, T> rotatey(const ang<T> &x)
    {
      T c = cos(x.radians());
      T s = sin(x.radians());
      return mat<3, 3, T>{c, T{0}, -s,
                          T{0}, T{1}, T{0},
                          s, T{0}, c};
    }

    //! Rotate axis z about a given angle
    static mat<3, 3, T> rotatez(const ang<T> &x)
    {
      T c = cos(x.radians());
      T s = sin(x.radians());
      return mat<3, 3, T>{c, s, T{0},
                          -s, c, T{0},
                          T{0}, T{0}, T{1}};
    }

    static constexpr mat<3, 3, T> scale(const T &s)
    {
      return mat<3, 3, T>{s, T{0}, T{0}, T{0}, s, T{0}, T{0}, T{0}, s};
    }

    static constexpr mat<3, 3, T> scale(const T &x, const T &y, const T &z)
    {
      return mat<3, 3, T>{x, T{0}, T{0}, T{0}, y, T{0}, T{0}, T{0}, z};
    }

    static constexpr mat<3, 3, T> scale(const vec<3, T> &v)
    {
      return mat<3, 3, T>{v.x, T{0}, T{0}, T{0}, v.y, T{0}, T{0}, T{0}, v.z};
    }

    static constexpr mat<3, 3, T> translate(const T &x, const T &y)
    {
      return mat<3, 3, T>{T{1}, T{0}, T{0}, T{0}, T{1}, T{0}, x, y, T{1}};
    }

    static mat<3, 3, T> translate(const vec<3, T> &v)
    {
      return translate(v.x, v.y, v.z);
    }

    static constexpr mat<4, 4, T> translate_affine(const T &x, const T &y, const T &z)
    {
      return mat<4, 4, T>{
          T{1}, T{0}, T{0}, T{0},
          T{0}, T{1}, T{0}, T{0},
          T{0}, T{0}, T{1}, T{0},
          x, y, z, T{1}};
    }

    static mat<4, 4, T> translate_affine(const vec<3, T> &v)
    {
      return translate(v.x, v.y, v.z);
    }

  }; //! struct mat

  template <class T>
  static constexpr mat<3, 3, T> operator*(const mat<3, 3, T> &m, const mat<3, 3, T> &n)
  {
    return mat<3, 3, T>{m.arr[0] * n.arr[0] + m.arr[3] * n.arr[1] + m.arr[6] * n.arr[2],
                        m.arr[1] * n.arr[0] + m.arr[4] * n.arr[1] + m.arr[7] * n.arr[2],
                        m.arr[2] * n.arr[0] + m.arr[5] * n.arr[1] + m.arr[8] * n.arr[2],
                        m.arr[0] * n.arr[3] + m.arr[3] * n.arr[4] + m.arr[6] * n.arr[5],
                        m.arr[1] * n.arr[3] + m.arr[4] * n.arr[4] + m.arr[7] * n.arr[5],
                        m.arr[2] * n.arr[3] + m.arr[5] * n.arr[4] + m.arr[8] * n.arr[5],
                        m.arr[0] * n.arr[6] + m.arr[3] * n.arr[7] + m.arr[6] * n.arr[8],
                        m.arr[1] * n.arr[6] + m.arr[4] * n.arr[7] + m.arr[7] * n.arr[8],
                        m.arr[2] * n.arr[6] + m.arr[5] * n.arr[7] + m.arr[8] * n.arr[8]};
  }

  //! Matrix determinant
  template <class T>
  static constexpr T det(const mat<3, 3, T> &m)
  {
    return (m.arr[0] * m.arr[4] * m.arr[8]) - (m.arr[0] * m.arr[5] * m.arr[7]) - (m.arr[1] * m.arr[3] * m.arr[8]) + (m.arr[1] * m.arr[5] * m.arr[6]) + (m.arr[2] * m.arr[3] * m.arr[7]) - (m.arr[2] * m.arr[4] * m.arr[6]);
  }

  //! Inverts the matrix, such that m * inverse(m) = the identity
  template <class T>
  static mat<3, 3, T> inverse(const mat<3, 3, T> &m)
  {
    return adjoint(m) / det(m);
  }

  ///////////////////////
  //! TYPE DEFINITIONS //
  ///////////////////////
  using mat3 = mat<3, 3, float>;
  using mat3f = mat3;
  using mat3d = mat<3, 3, double>;
  using mat3uc = mat<3, 3, unsigned char>;
  using mat3c = mat<3, 3, char>;
  using mat3us = mat<3, 3, unsigned short>;
  using mat3s = mat<3, 3, short>;
  using mat3ui = mat<3, 3, unsigned int>;
  using mat3i = mat<3, 3, int>;
  using mat3ul = mat<3, 3, unsigned long>;
  using mat3l = mat<3, 3, long>;

} ////

//

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//

#endif //DYM_MAT3_H_INCLUDED
