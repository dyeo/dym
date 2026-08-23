#ifndef DYM_MAT2_H_INCLUDED
#define DYM_MAT2_H_INCLUDED

//

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127)
#endif

//

#include "mat.h"
#include "angle.h"
#include <cstddef>

//

namespace dym
{ ////

  //! A specialized 2x2 square matrix
  template <class T>
  struct mat<2, 2, T>
  {
    using type = T;
    static constexpr dim_t cols = 2;
    static constexpr dim_t rows = 2;
    static constexpr dim_t dim = 2;
    static constexpr dim_t size = 4;

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
      : arr{T{1}, T{0}, T{0}, T{1}}
    {
    }

    ~mat() = default;


    //! Copy constructor
    constexpr mat(const mat<2, 2, T> &v)
      : arr{v.arr[0], v.arr[1], v.arr[2], v.arr[3]}
    {
    }

    //! Explicit type-conversion copy constructor
    template <class U>
    explicit constexpr mat(const mat<2, 2, U> &v)
      : arr{static_cast<T>(v.arr[0]), static_cast<T>(v.arr[1]), static_cast<T>(v.arr[2]), static_cast<T>(v.arr[3])}
    {
    }

    //! Fill constructor
    explicit constexpr mat(const T &s)
      : arr{s, s, s, s}
    {
    }

    //! Array initializer
    explicit constexpr mat(const T *a)
      : arr{a[0], a[1], a[2], a[3]}
    {
    }

    //! Value constructor
    constexpr mat(const T &s0, const T &s1, const T &s2, const T &s3)
      : arr{s0, s1, s2, s3}
    {
    }

    //! Explicit type-conversionm value constructor
    template <class U>
    explicit constexpr mat(const U &s0, const U &s1, const U &s2, const U &s3)
      : arr{static_cast<T>(s0), static_cast<T>(s1), static_cast<T>(s2), static_cast<T>(s3)}
    {
    }

    //! Constructs a 2x2 matrix using the top-left portion of a 3x3 matrix;
    constexpr mat(const mat<3, 3, T> &m)
      : arr{m.arr[0], m.arr[1], m.arr[3], m.arr[4]}
    {
    }

    //! Constructs a 2x2 matrix using the top-left portion of a 4x4 matrix;
    constexpr mat(const mat<4, 4, T> &m)
      : arr{m.arr[0], m.arr[1], m.arr[4], m.arr[5]}
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
    constexpr vec<2, T> col(const dim_t i)
    {
      return data[i];
    }

    //! Row function - returns row as vector of T
    constexpr vec<2, T> row(const dim_t i)
    {
      vec<2, T> v{arr[i], arr[i + 2]};
      return v;
    }

    //! Matrix index operator - returns column
    constexpr vec<2, T> &operator[](const dim_t i)
    {
      return data[i];
    }

    //! Matrix const index operator - returns column
    constexpr const vec<2, T> &operator[](const dim_t i) const
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
    constexpr mat<2, 2, T> operator-() const
    {
      return mat<2, 2, T>(-arr[0], -arr[1], -arr[2], -arr[3]);
    }
    //! Component-wise unary negation
    constexpr mat<2, 2, T> operator~() const
    {
      return mat<2, 2, T>(~arr[0], ~arr[1], ~arr[2], ~arr[3]);
    }
    //! Vector assignment
    constexpr mat<2, 2, T> &operator=(const mat<2, 2, T> &m)
    {
      arr[0] = m.arr[0];
      arr[1] = m.arr[1];
      arr[2] = m.arr[2];
      arr[3] = m.arr[3];
      return *this;
    }

    //! Component-wise matrix addition
    constexpr mat<2, 2, T> operator+(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] + m.arr[0], arr[1] + m.arr[1], arr[2] + m.arr[2], arr[3] + m.arr[3]);
    }
    //! Component-wise matrix subtraction
    constexpr mat<2, 2, T> operator-(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] - m.arr[0], arr[1] - m.arr[1], arr[2] - m.arr[2], arr[3] - m.arr[3]);
    }
    //! Component-wise matrix OR
    constexpr mat<2, 2, T> operator|(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] | m.arr[0], arr[1] | m.arr[1], arr[2] | m.arr[2], arr[3] | m.arr[3]);
    }
    //! Component-wise matrix AND
    constexpr mat<2, 2, T> operator&(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] & m.arr[0], arr[1] & m.arr[1], arr[2] & m.arr[2], arr[3] & m.arr[3]);
    }
    //! Component-wise matrix XOR
    constexpr mat<2, 2, T> operator^(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] ^ m.arr[0], arr[1] ^ m.arr[1], arr[2] ^ m.arr[2], arr[3] ^ m.arr[3]);
    }
    //! Component-wise matrix modulus
    constexpr mat<2, 2, T> operator%(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] % m.arr[0], arr[1] % m.arr[1], arr[2] % m.arr[2], arr[3] % m.arr[3]);
    }
    //! Component-wise matrix shift left
    constexpr mat<2, 2, T> operator<<(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] << m.arr[0], arr[1] << m.arr[1], arr[2] << m.arr[2], arr[3] << m.arr[3]);
    }
    //! Component-wise matrix shift right
    constexpr mat<2, 2, T> operator>>(const mat<2, 2, T> &m) const
    {
      return mat<2, 2, T>(arr[0] >> m.arr[0], arr[1] >> m.arr[1], arr[2] >> m.arr[2], arr[3] >> m.arr[3]);
    }

    //! Component-wise scalar multiplication
    constexpr mat<2, 2, T> operator*(const T &v) const
    {
      return mat<2, 2, T>(arr[0] * v, arr[1] * v, arr[2] * v, arr[3] * v);
    }
    //! Component-wise scalar division
    constexpr mat<2, 2, T> operator/(const T &v) const
    {
      return mat<2, 2, T>(arr[0] / v, arr[1] / v, arr[2] / v, arr[3] / v);
    }
    //! Component-wise scalar addition
    constexpr mat<2, 2, T> operator+(const T &v) const
    {
      return mat<2, 2, T>(arr[0] + v, arr[1] + v, arr[2] + v, arr[3] + v);
    }
    //! Component-wise scalar subtraction
    constexpr mat<2, 2, T> operator-(const T &v) const
    {
      return mat<2, 2, T>(arr[0] - v, arr[1] - v, arr[2] - v, arr[3] - v);
    }
    //! Component-wise scalar OR
    constexpr mat<2, 2, T> operator|(const T &v) const
    {
      return mat<2, 2, T>(arr[0] | v, arr[1] | v, arr[2] | v, arr[3] | v);
    }
    //! Component-wise scalar AND
    constexpr mat<2, 2, T> operator&(const T &v) const
    {
      return mat<2, 2, T>(arr[0] & v, arr[1] & v, arr[2] & v, arr[3] & v);
    }
    //! Component-wise scalar XOR
    constexpr mat<2, 2, T> operator^(const T &v) const
    {
      return mat<2, 2, T>(arr[0] ^ v, arr[1] ^ v, arr[2] ^ v, arr[3] ^ v);
    }
    //! Component-wise scalar modulus
    constexpr mat<2, 2, T> operator%(const T &v) const
    {
      return mat<2, 2, T>(arr[0] % v, arr[1] % v, arr[2] % v, arr[3] % v);
    }
    //! Component-wise scalar shift left
    constexpr mat<2, 2, T> operator<<(const T &v) const
    {
      return mat<2, 2, T>(arr[0] << v, arr[1] << v, arr[2] << v, arr[3] << v);
    }
    //! Component-wise scalar shift right
    constexpr mat<2, 2, T> operator>>(const T &v) const
    {
      return mat<2, 2, T>(arr[0] >> v, arr[1] >> v, arr[2] >> v, arr[3] >> v);
    }

    //! Component-wise matrix reference addition
    constexpr mat<2, 2, T> &operator+=(const mat<2, 2, T> &m)
    {
      arr[0] += m.arr[0];
      arr[1] += m.arr[1];
      arr[2] += m.arr[2];
      arr[3] += m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference subtraction
    constexpr mat<2, 2, T> &operator-=(const mat<2, 2, T> &m)
    {
      arr[0] -= m.arr[0];
      arr[1] -= m.arr[1];
      arr[2] -= m.arr[2];
      arr[3] -= m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference OR
    constexpr mat<2, 2, T> &operator|=(const mat<2, 2, T> &m)
    {
      arr[0] |= m.arr[0];
      arr[1] |= m.arr[1];
      arr[2] |= m.arr[2];
      arr[3] |= m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference AND
    constexpr mat<2, 2, T> &operator&=(const mat<2, 2, T> &m)
    {
      arr[0] &= m.arr[0];
      arr[1] &= m.arr[1];
      arr[2] &= m.arr[2];
      arr[3] &= m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference XOR
    constexpr mat<2, 2, T> &operator^=(const mat<2, 2, T> &m)
    {
      arr[0] ^= m.arr[0];
      arr[1] ^= m.arr[1];
      arr[2] ^= m.arr[2];
      arr[3] ^= m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference modulus
    constexpr mat<2, 2, T> &operator%=(const mat<2, 2, T> &m)
    {
      arr[0] %= m.arr[0];
      arr[1] %= m.arr[1];
      arr[2] %= m.arr[2];
      arr[3] %= m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference shift left
    constexpr mat<2, 2, T> &operator<<=(const mat<2, 2, T> &m)
    {
      arr[0] <<= m.arr[0];
      arr[1] <<= m.arr[1];
      arr[2] <<= m.arr[2];
      arr[3] <<= m.arr[3];
      return *this;
    }
    //! Component-wise matrix reference shift right
    constexpr mat<2, 2, T> &operator>>=(const mat<2, 2, T> &m)
    {
      arr[0] >>= m.arr[0];
      arr[1] >>= m.arr[1];
      arr[2] >>= m.arr[2];
      arr[3] >>= m.arr[3];
      return *this;
    }

    //! Component-wise scalar reference multiplication
    constexpr mat<2, 2, T> &operator*=(const T &v)
    {
      arr[0] *= v;
      arr[1] *= v;
      arr[2] *= v;
      arr[3] *= v;
      return *this;
    }
    //! Component-wise scalar reference division
    constexpr mat<2, 2, T> &operator/=(const T &v)
    {
      arr[0] /= v;
      arr[1] /= v;
      arr[2] /= v;
      arr[3] /= v;
      return *this;
    }
    //! Component-wise scalar reference addition
    constexpr mat<2, 2, T> &operator+=(const T &v)
    {
      arr[0] += v;
      arr[1] += v;
      arr[2] += v;
      arr[3] += v;
      return *this;
    }
    //! Component-wise scalar reference subtraction
    constexpr mat<2, 2, T> &operator-=(const T &v)
    {
      arr[0] -= v;
      arr[1] -= v;
      arr[2] -= v;
      arr[3] -= v;
      return *this;
    }
    //! Component-wise scalar reference OR
    constexpr mat<2, 2, T> &operator|=(const T &v)
    {
      arr[0] |= v;
      arr[1] |= v;
      arr[2] |= v;
      arr[3] |= v;
      return *this;
    }
    //! Component-wise scalar reference AND
    constexpr mat<2, 2, T> &operator&=(const T &v)
    {
      arr[0] &= v;
      arr[1] &= v;
      arr[2] &= v;
      arr[3] &= v;
      return *this;
    }
    //! Component-wise scalar reference XOR
    constexpr mat<2, 2, T> &operator^=(const T &v)
    {
      arr[0] ^= v;
      arr[1] ^= v;
      arr[2] ^= v;
      arr[3] ^= v;
      return *this;
    }
    //! Component-wise scalar reference modulus
    constexpr mat<2, 2, T> &operator%=(const T &v)
    {
      arr[0] %= v;
      arr[1] %= v;
      arr[2] %= v;
      arr[3] %= v;
      return *this;
    }
    //! Component-wise scalar reference shift left
    constexpr mat<2, 2, T> &operator<<=(const T &v)
    {
      arr[0] <<= v;
      arr[1] <<= v;
      arr[2] <<= v;
      arr[3] <<= v;
      return *this;
    }
    //! Component-wise scalar reference shift right
    constexpr mat<2, 2, T> &operator>>=(const T &v)
    {
      arr[0] >>= v;
      arr[1] >>= v;
      arr[2] >>= v;
      arr[3] >>= v;
      return *this;
    }

    /////////////////////////////////
    //! MATRIX GENERATOR FUNCTIONS //
    /////////////////////////////////

    //! Generates a 2x2 identity matrix
    static constexpr mat<2, 2, T> identity()
    {
      return mat<2, 2, T>{T{1}, T{0}, T{0}, T{1}};
    }

    //! Creates a row-order matrix using individual elements
    static constexpr mat<2, 2, T> roworder(const T &s0, const T &s1, const T &s2, const T &s3)
    {
      return mat<2, 2, T>{s0, s2,
                          s1, s3};
    }

    //! Creates a 2x2 matrix using 2 row vectors
    static constexpr mat<2, 2, T> fromrows(vec<2, T> r0, vec<2, T> r1)
    {
      return mat<2, 2, T>{r0.x, r1.x,
                          r0.y, r1.y};
    }

    //! Creates a 2x2 matrix using 2 column vectors
    static constexpr mat<2, 2, T> fromcols(vec<2, T> c0, vec<2, T> c1)
    {
      return mat<2, 2, T>{c0.x, c0.y,
                          c1.x, c1.y};
    }

    //! Generates a clockwise rotation matrix using an angle
    static mat<2, 2, T> rotate(const ang<T> &a)
    {
      const T ca = cos(a.radians());
      const T sa = sin(a.radians());
      return mat<2, 2, T>{ca, sa, -sa, ca};
    }

    //! Generates a clockwise rotation matrix using an angle
    static mat<2, 2, T> rotatecw(const ang<T> &a)
    {
      return rotate(a);
    }

    //! Generates a counter-clockwise rotation matrix using an angle
    static mat<2, 2, T> rotateccw(const ang<T> &a)
    {
      float ca = cos(a.radians());
      float sa = sin(a.radians());
      return mat<2, 2, T>{static_cast<T>(ca), static_cast<T>(-sa), static_cast<T>(sa), static_cast<T>(ca)};
    }

    //! Generates a scaling matrix using a single scaling value
    static constexpr mat<2, 2, T> scale(const T &s)
    {
      return mat<2, 2, T>{s, T{0}, T{0}, s};
    }

    //! Generates a scaling matrix using an x and y scaling value
    static constexpr mat<2, 2, T> scale(const T &x, const T &y)
    {
      return mat<2, 2, T>{x, T{0}, T{0}, y};
    }

    //! Shears along the x axis
    static constexpr mat<2, 2, T> shearx(const T &k)
    {
      return mat<2, 2, T>{T{1}, T{0}, k, T{1}};
    }

    //! Shears along the y axis
    static constexpr mat<2, 2, T> sheary(const T &k)
    {
      return mat<2, 2, T>{T{1}, k, T{0}, T{1}};
    }

    static mat<3, 3, T> translate_affine(const T &x, const T &y)
    {
      mat<3, 3, T> res{mat<3, 3, T>::identity()};
      res[2] = vec<3, T>{x, y, T{1}};
    }

    static mat<3, 3, T> translate_affine(const vec<2, T> &t)
    {
      return translate_affine(t.x, t.y);
    }

  }; //! struct mat

  template <class T>
  static constexpr mat<2, 2, T> operator*(const mat<2, 2, T> &m, const mat<2, 2, T> &n)
  {
    return mat<2, 2, T>{m.arr[0] * n.arr[0] + m.arr[2] * n.arr[1], m.arr[1] * n.arr[0] + m.arr[3] * n.arr[1],
                        m.arr[0] * n.arr[2] + m.arr[2] * n.arr[3], m.arr[1] * n.arr[2] + m.arr[3] * n.arr[3]};
  }

  //! Matrix determinant
  template <class T>
  static constexpr T det(const mat<2, 2, T> &m)
  {
    return (m.arr[0] * m.arr[3]) - (m.arr[1] * m.arr[2]);
  }

  //! Inverts the matrix, such that m * inverse(m) = the identity
  template <class T>
  static constexpr mat<2, 2, T> inverse(const mat<2, 2, T> &m)
  {
    return mat<2, 2, T>{m.arr[3], -m.arr[1], -m.arr[2], m.arr[0]} / det(m);
  }

  ///////////////////////
  //! TYPE DEFINITIONS //
  ///////////////////////
  using mat2 = mat<2, 2, float>;
  using mat2f = mat2;
  using mat2d = mat<2, 2, double>;
  using mat2uc = mat<2, 2, unsigned char>;
  using mat2c = mat<2, 2, char>;
  using mat2us = mat<2, 2, unsigned short>;
  using mat2s = mat<2, 2, short>;
  using mat2ui = mat<2, 2, unsigned int>;
  using mat2i = mat<2, 2, int>;
  using mat2ul = mat<2, 2, unsigned long>;
  using mat2l = mat<2, 2, long>;

} ////

//


#ifdef _MSC_VER
#pragma warning(pop)
#endif

//

#endif //DYM_MAT2_H_INCLUDED
