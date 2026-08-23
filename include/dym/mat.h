#ifndef DYM_MAT_H_INCLUDED
#define DYM_MAT_H_INCLUDED

//

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4456; disable : 4127)
#endif

//

#include "util.h"
#include "vec.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

//

#include <cmath>
#include <ostream>
#include <concepts>

//

namespace dym
{ ////

  //! A column-major matrix spanning C columns and R rows
  template <dim_t C, dim_t R = C, class T = float>
  struct mat
  {
    using type = T;
    static constexpr dim_t cols = C;
    static constexpr dim_t rows = R;
    static constexpr dim_t dim = min(C, R);
    static constexpr dim_t size = C * R;

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
    {
      for (dim_t i = 0; i < size; ++i)
      {
        arr[i] = T{0};
      }
    }

    ~mat() = default;

    //! Component constructor
    //! Columns span left-to-right in initialization, and rows span top-to-bottom
    //! This is because matrices are stored column-major
    template <class... U>
      requires (sizeof...(U) == size && (std::convertible_to<U, T> && ...))
    constexpr mat(const U &...values)
      : arr{static_cast<T>(values)...}
    {
    }

    //! Copy constructor
    constexpr mat(const mat<C, R, T> &v)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        arr[i] = v.arr[i];
      }
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

    //! Explicit type-conversion copy constructor
    template <class U>
    explicit constexpr mat(const mat<C, R, U> &v)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        arr[i] = static_cast<T>(v.arr[i]);
      }
    }

    //! Fill constructor
    explicit constexpr mat(const T &s)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        arr[i] = s;
      }
    }

    //! Array initializer
    explicit constexpr mat(const T *a)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        arr[i] = a[i];
      }
    }

    ///////////////////////
    //! ACCESS OPERATORS //
    ///////////////////////

    //! Column function - returns column as vector of T
    constexpr vec<R, T> &col(const dim_t i)
    {
      return data[i];
    }

    //! Column function - returns column as vector of T
    constexpr const vec<R, T> &col(const dim_t i) const
    {
      return data[i];
    }

    //! Row function - returns row as vector of T
    constexpr const vec<C, T> row(const dim_t i) const
    {
      vec<C, T> v{static_cast<T>(0)};
      for (dim_t i = 0; i < C; ++i)
      {
        v[i] = arr[i * C];
      }
      return v;
    }

    //! Matrix index operator - returns column
    constexpr vec<R, T> &operator[](const dim_t i)
    {
      return data[i];
    }

    //! Matrix const index operator - returns column
    constexpr const vec<R, T> &operator[](const dim_t i) const
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

    ///////////////////////////
    //! ARITHMETIC OPERATORS //
    ///////////////////////////

    //! Component-wise unary negation
    constexpr mat<C, R, T> operator-() const
    {
      return unary_transform([](const auto &value) { return -value; });
    }
    //! Component-wise unary negation
    constexpr mat<C, R, T> operator~() const
    {
      return unary_transform([](const auto &value) { return ~value; });
    }
    //! Vector assignment
    constexpr mat<C, R, T> &operator=(const mat<C, R, T> &v)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        arr[i] = v.arr[i];
      }
      return *this;
    }

    //! Component-wise matrix addition
    constexpr mat<C, R, T> operator+(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left + right; });
    }
    //! Component-wise matrix subtraction
    constexpr mat<C, R, T> operator-(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left - right; });
    }
    //! Component-wise matrix OR
    constexpr mat<C, R, T> operator|(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left | right; });
    }
    //! Component-wise matrix AND
    constexpr mat<C, R, T> operator&(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left & right; });
    }
    //! Component-wise matrix XOR
    constexpr mat<C, R, T> operator^(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left ^ right; });
    }
    //! Component-wise matrix modulus
    constexpr mat<C, R, T> operator%(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left % right; });
    }
    //! Component-wise matrix shift left
    constexpr mat<C, R, T> operator<<(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left << right; });
    }
    //! Component-wise matrix shift right
    constexpr mat<C, R, T> operator>>(const mat<C, R, T> &v) const
    {
      return binary_transform(v, [](const auto &left, const auto &right) { return left >> right; });
    }

    //! Component-wise scalar multiplication
    constexpr mat<C, R, T> operator*(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left * right; });
    }
    //! Component-wise scalar division
    constexpr mat<C, R, T> operator/(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left / right; });
    }
    //! Component-wise scalar addition
    constexpr mat<C, R, T> operator+(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left + right; });
    }
    //! Component-wise scalar subtraction
    constexpr mat<C, R, T> operator-(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left - right; });
    }
    //! Component-wise scalar OR
    constexpr mat<C, R, T> operator|(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left | right; });
    }
    //! Component-wise scalar AND
    constexpr mat<C, R, T> operator&(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left & right; });
    }
    //! Component-wise scalar XOR
    constexpr mat<C, R, T> operator^(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left ^ right; });
    }
    //! Component-wise scalar modulus
    constexpr mat<C, R, T> operator%(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left % right; });
    }
    //! Component-wise scalar shift left
    constexpr mat<C, R, T> operator<<(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left << right; });
    }
    //! Component-wise scalar shift right
    constexpr mat<C, R, T> operator>>(const T &v) const
    {
      return scalar_transform(v, [](const auto &left, const auto &right) { return left >> right; });
    }

    //! Component-wise matrix reference addition
    constexpr mat<C, R, T> &operator+=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left += right; });
    }
    //! Component-wise matrix reference subtraction
    constexpr mat<C, R, T> &operator-=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left -= right; });
    }
    //! Component-wise matrix reference OR
    constexpr mat<C, R, T> &operator|=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left |= right; });
    }
    //! Component-wise matrix reference AND
    constexpr mat<C, R, T> &operator&=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left &= right; });
    }
    //! Component-wise matrix reference XOR
    constexpr mat<C, R, T> &operator^=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left ^= right; });
    }
    //! Component-wise matrix reference modulus
    constexpr mat<C, R, T> &operator%=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left %= right; });
    }
    //! Component-wise matrix reference shift left
    constexpr mat<C, R, T> &operator<<=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left <<= right; });
    }
    //! Component-wise matrix reference shift right
    constexpr mat<C, R, T> &operator>>=(const mat<C, R, T> &v)
    {
      return binary_assign(v, [](auto &left, const auto &right) { left >>= right; });
    }

    //! Component-wise scalar reference multiplication
    constexpr mat<C, R, T> &operator*=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left *= right; });
    }
    //! Component-wise scalar reference division
    constexpr mat<C, R, T> &operator/=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left /= right; });
    }
    //! Component-wise scalar reference addition
    constexpr mat<C, R, T> &operator+=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left += right; });
    }
    //! Component-wise scalar reference subtraction
    constexpr mat<C, R, T> &operator-=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left -= right; });
    }
    //! Component-wise scalar reference OR
    constexpr mat<C, R, T> &operator|=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left |= right; });
    }
    //! Component-wise scalar reference AND
    constexpr mat<C, R, T> &operator&=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left &= right; });
    }
    //! Component-wise scalar reference XOR
    constexpr mat<C, R, T> &operator^=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left ^= right; });
    }
    //! Component-wise scalar reference modulus
    constexpr mat<C, R, T> &operator%=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left %= right; });
    }
    //! Component-wise scalar reference shift left
    constexpr mat<C, R, T> &operator<<=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left <<= right; });
    }
    //! Component-wise scalar reference shift right
    constexpr mat<C, R, T> &operator>>=(const T &v)
    {
      return scalar_assign(v, [](auto &left, const auto &right) { left >>= right; });
    }

    //! Matrix identity
    static constexpr mat<C, R, T> identity()
    {
      mat<C, R, T> res{T{0}};
      for (dim_t i = 0; i < dim; ++i)
      {
        res.data[i][i] = T{1};
      }
      return res;
    }

    //! Zero matrix
    static constexpr mat<C, R, T> zero()
    {
      return mat<C, R, T>{T{0}};
    }

    //! Unit matrix
    static constexpr mat<C, R, T> one()
    {
      return mat<C, R, T>{T{1}};
    }


  private:
    template <class F>
    constexpr mat<C, R, T> unary_transform(F operation) const
    {
      mat<C, R, T> res;
      for (dim_t i = 0; i < size; ++i)
      {
        res.arr[i] = operation(arr[i]);
      }
      return res;
    }

    template <class F>
    constexpr mat<C, R, T> binary_transform(const mat<C, R, T> &v, F operation) const
    {
      mat<C, R, T> res;
      for (dim_t i = 0; i < size; ++i)
      {
        res.arr[i] = operation(arr[i], v.arr[i]);
      }
      return res;
    }

    template <class F>
    constexpr mat<C, R, T> scalar_transform(const T &v, F operation) const
    {
      mat<C, R, T> res;
      for (dim_t i = 0; i < size; ++i)
      {
        res.arr[i] = operation(arr[i], v);
      }
      return res;
    }

    template <class F>
    constexpr mat<C, R, T> &binary_assign(const mat<C, R, T> &v, F operation)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        operation(arr[i], v.arr[i]);
      }
      return *this;
    }

    template <class F>
    constexpr mat<C, R, T> &scalar_assign(const T &v, F operation)
    {
      for (dim_t i = 0; i < size; ++i)
      {
        operation(arr[i], v);
      }
      return *this;
    }

  }; //! struct mat

  //////////////////////
  //! MISC. OPERATORS //
  //////////////////////

  template <dim_t C, dim_t R, class T>
  static std::ostream &operator<<(std::ostream &os, const mat<C, R, T> &v)
  {
#ifdef DYM_OUTPUT_ROW_MAJOR
    const mat<C, R, T> &t = transpose(v);
    for (dim_t i = 0; i < C; ++i)
    {
      os << "| ";
      for (dim_t j = 0; j < R; ++j)
      {
        os << t[i][j] << ' ';
      }
      os << "|\n";
    };
#else
    for (dim_t i = 0; i < C; ++i)
    {
      os << v.data[i];
      (i < C - 1) ? os << '\n' : os << ' ';
    }
#endif
    return os;
  }

  ///////////////////////////////////
  //! MATRIX&MATRIX MULTIPLICATION //
  ///////////////////////////////////

  template <dim_t N, class T>
  static mat<N, N, T> strassen(const mat<N, N, T> &l, const mat<N, N, T> &r)
  {
    if (N == 1)
    {
      mat<1, 1, T> r;
      r[0][0] = l[0][0] * r[0][0];
      return r;
    }

    mat<N / 2, N / 2, T> l11, l12, l21, l22;
    mat<N / 2, N / 2, T> r11, r12, r21, r22;
    split(l, l11, l12, l21, l22);
    split(r, r11, r12, r21, r22);

    mat<N / 2, N / 2, T> P1 = strassen(l11 + l22, r11 + r22);
    mat<N / 2, N / 2, T> P2 = strassen(l11 + l22, r11);
    mat<N / 2, N / 2, T> P3 = strassen(l11, r12 - r22);
    mat<N / 2, N / 2, T> P4 = strassen(l11, r21 - r11);
    mat<N / 2, N / 2, T> P5 = strassen(l11 + l12, r22);
    mat<N / 2, N / 2, T> P6 = strassen(l21 - l11, r11 + r12);
    mat<N / 2, N / 2, T> P7 = strassen(l12 - l22, r21 + r22);

    mat<N / 2, N / 2, T> C11 = P1 + P4 - P5 + P7;
    mat<N / 2, N / 2, T> C12 = P3 + P5;
    mat<N / 2, N / 2, T> C21 = P2 + P4;
    mat<N / 2, N / 2, T> C22 = P1 - P2 + P3 + P6;

    mat<N, N, T> C;
    join(C11, C12, C21, C22, C);
    return C;
  }

  template <dim_t N, class T>
  static void split(const mat<N, N, T> &M, mat<N / 2, N / 2, T> &M11, mat<N / 2, N / 2, T> &M12, mat<N / 2, N / 2, T> &M21, mat<N / 2, N / 2, T> &M22)
  {
    for (dim_t i = 0; i < N / 2; ++i)
    {
      for (dim_t j = 0; j < N / 2; ++j)
      {
        M11(i, j) = M(i, j);
        M12(i, j) = M(i, j + N / 2);
        M21(i, j) = M(i + N / 2, j);
        M22(i, j) = M(i + N / 2, j + N / 2);
      }
    }
  }

  template <dim_t N, class T>
  static void join(const mat<N / 2, N / 2, T> &M11, const mat<N / 2, N / 2, T> &M12, const mat<N / 2, N / 2, T> &M21, const mat<N / 2, N / 2, T> &M22, mat<N, N, T> &M)
  {
    for (dim_t i = 0; i < N / 2; ++i)
    {
      for (dim_t j = 0; j < N / 2; ++j)
      {
        M(i, j) = M11(i, j);
        M(i, j + N / 2) = M12(i, j);
        M(i + N / 2, j) = M21(i, j);
        M(i + N / 2, j + N / 2) = M22(i, j);
      }
    }
  }

  //! Matrix product
  //! Accepts a R1 x C1 matrix and a R2 x C2 matrix where C1 and R2 are equal
  //! Returns a R1 x C2 matrix that is the product of the two original matrices
  //! Is not commutative
  template <dim_t C1, dim_t R1, dim_t C2, dim_t R2, class T>
  static constexpr mat<C2, R1, T> operator*(const mat<C1, R1, T> &m, const mat<C2, R2, T> &n)
  {
    static_assert(C1 == R2, "Number of columns in m must equal number of rows in n");
    mat<C2, R1, T> res{T{0}};
    for (dim_t i = 0; i < R1; ++i)
    {
      for (dim_t j = 0; j < C2; ++j)
      {
        for (dim_t k = 0; k < R2; ++k)
        {
          res[j][i] += m.data[k][i] * n.data[j][k];
        }
      }
    }
    return res;
  }

  //! Matrix product (reference)
  //! Accepts two matrices where cols and rows are equal
  //! Is not commutative
  template <dim_t C, dim_t R, class T>
  static constexpr mat<C, R, T> &operator*=(mat<C, R, T> &m, const mat<C, R, T> &n)
  {
    mat<C, R, T> res{T{0}};
    for (dim_t i = 0; i < R; ++i)
    {
      for (dim_t j = 0; j < C; ++j)
      {
        for (dim_t k = 0; k < R; ++k)
        {
          res[j][i] += m.data[k][i] * n.data[j][k];
        }
      }
    }
    return m = res;
  }

  ///////////////////////////////////
  //! MATRIX&VECTOR MULTIPLICATION //
  ///////////////////////////////////

  //! Matrix-vector multiplication: column vector (matrix row)
  template <dim_t C, dim_t R, class T>
  static constexpr vec<R, T> operator*(const mat<C, R, T> &m, const vec<R, T> &v)
  {
    vec<R, T> res{T{0}};
    for (dim_t i = 0; i < R; ++i)
    {
      for (dim_t j = 0; j < C; ++j)
      {
        res[i] += m.data[j][i] * v[j];
      }
    }
    return res;
  }

  //! Matrix-vector multiplication: row vector (matrix column)
  template <dim_t C, dim_t R, class T>
  static constexpr vec<C, T> operator*(const vec<C, T> &v, const mat<C, R, T> &m)
  {
    vec<C, T> res{T{0}};
    for (dim_t i = 0; i < C; ++i)
    {
      for (dim_t j = 0; j < R; ++j)
      {
        res[i] += m.data[i][j] * v[j];
      }
    }
    return res;
  }

  //! Matrix-vector multiplication: row vector (matrix column, reference)
  template <dim_t C, dim_t R, class T>
  static constexpr vec<C, T> &operator*=(vec<C, T> &v, const mat<C, R, T> &m)
  {
    vec<C, T> res{T{0}};
    for (dim_t i = 0; i < C; ++i)
    {
      for (dim_t j = 0; j < R; ++j)
      {
        res[i] += m.data[i][j] * v[j];
      }
    }
    return v = res;
  }

  ///////////////////////////////////
  //! MATRIX&SCALAR MULTIPLICATION //
  ///////////////////////////////////

  //! Matrix-scalar multiplication
  template <dim_t C, dim_t R, class T>
  static constexpr mat<C, R, T> operator*(const T &v, const mat<C, R, T> &m)
  {
    mat<C, R, T> res;
    for (dim_t i = 0; i < C * R; ++i)
    {
      res.arr[i] = v * m.arr[i];
    }
    return res;
  }

  //! Matrix-scalar multiplication (odd-typed)
  template <dim_t C, dim_t R, class T, class U>
  static constexpr mat<C, R, T> operator*(const U &v, const mat<C, R, T> &m)
  {
    mat<C, R, T> res;
    for (dim_t i = 0; i < C * R; ++i)
    {
      res.arr[i] = static_cast<T>(v) * m.arr[i];
    }
    return res;
  }

  /////////////////////
  //! FREE-FUNCTIONS //
  /////////////////////

  //! Component-wise matrix multiplication
  template <dim_t C, dim_t R, class T>
  static constexpr mat<C, R, T> mult(const mat<C, R, T> &m, const mat<C, R, T> &n)
  {
    mat<C, R, T> res;
    for (dim_t i = 0; i < C * R; ++i)
    {
      res.arr[i] = m.arr[i] * n.arr[i];
    }
    return res;
  }

  //! Returns sum of the matrix diagonal
  template <dim_t C, dim_t R, class T>
  static constexpr T trace(const mat<C, R, T> &m)
  {
    T res = 0;
    for (dim_t i = 0; i < min(C, R); ++i)
    {
      res += m.data[i][i];
    }
    return res;
  }

  //! Returns minor matrix of the current matrix, "crossing out" the specified row and column
  template <dim_t C, dim_t R, class T>
  static constexpr mat<C - 1, R - 1, T> minor(const mat<C, R, T> &m, int rx, int cx)
  {
    mat<C - 1, R - 1, T> res{T{0}};

    int mini = 0;
    int minj = 0;

    for (dim_t i = 0; i < R; ++i)
    {
      if (i != rx)
      {
        minj = 0;
        for (dim_t j = 0; j < C; ++j)
        {
          if (j != cx)
          {
            res.data[minj][mini] = m.data[j][i];
            minj++;
          }
        }
        mini++;
      }
    }
    return res;
  }

  //! Calculates the determinant of a matrix
  template <dim_t D, class T>
  static T det(const mat<D, D, T> &m)
  {
    if (D == 1)
      return m[0][0];

    mat<D, D, T> l;
    mat<D, D, T> u;

    int sign = ludecompose(m, l, u);

    if (sign == 0)
      return T{0};

    T res = static_cast<T>(sign);

    for (dim_t i = 0; i < D; ++i)
    {
      res *= u[i][i];
    }

    return res;
  }

  //! Decomposes a matrix into lower and upper traingular cofactor matrices
  template <dim_t D, class T>
  static int ludecompose(const mat<D, D, T> &m, mat<D, D, T> &l, mat<D, D, T> &u)
  {
    l = mat<D, D, T>::identity();
    u = m;

    int sign = 1;

    for (dim_t k = 0; k < D; ++k)
    {
      // Find pivot row in column k
      int pivot = k;
      T maxval = std::abs(u[k][k]);

      for (dim_t i = k + 1; i < D; ++i)
      {
        T v = std::abs(u[k][i]);
        if (v > maxval)
        {
          maxval = v;
          pivot = i;
        }
      }

      // Singular matrix
      if (maxval == T{0})
        return 0;

      // Swap rows k and pivot
      if (pivot != k)
      {
        // Swap rows of U.
        for (dim_t col = 0; col < D; ++col)
        {
          T tmp = u[col][k];
          u[col][k] = u[col][pivot];
          u[col][pivot] = tmp;
        }

        // Swap already-computed portion of L
        for (dim_t col = 0; col < k; ++col)
        {
          T tmp = l[col][k];
          l[col][k] = l[col][pivot];
          l[col][pivot] = tmp;
        }

        sign = -sign;
      }

      // Eliminate entries below pivot
      for (dim_t row = k + 1; row < D; ++row)
      {
        T factor = u[k][row] / u[k][k];

        l[k][row] = factor;

        for (dim_t col = k; col < D; ++col)
        {
          u[col][row] -= factor * u[col][k];
        }
      }
    }
    return sign;
  }

  //! Flips the matrix along its diagonal (rows become columns, columns become rows)
  template <dim_t R, dim_t C, class T>
  static constexpr mat<R, C, T> transpose(const mat<C, R, T> &m)
  {
    mat<R, C, T> res{T{0}};
    for (dim_t i = 0; i < C; ++i)
    {
      for (dim_t j = 0; j < R; ++j)
      {
        res[j][i] = m[i][j];
      }
    }
    return res;
  }

  //! Generates a matrix one dimension larger that is a composition of the target matrix and an identity matrix
  template <dim_t R, dim_t C, class T>
  static constexpr mat<C + 1, R + 1, T> affine(const mat<C, R, T> &m)
  {
    mat<C + 1, R + 1, T> res{m};
    res[C][R] = T{1};
    return res;
  }

  template <dim_t D, class T>
  static constexpr mat<D, D, T> cofactor(const mat<D, D, T> &m)
  {
    mat<D, D, T> res{T{0}};
    for (dim_t j = 0; j < D; ++j)
    {
      for (dim_t i = 0; i < D; ++i)
      {
        res[i][j] = pow(-1, (i + 1) + (j + 1)) * det(minor(m, j, i));
      }
    }
    return res;
  }

  //! Returns true if the matrix has no inverse, false otherwise
  template <dim_t D, class T>
  static constexpr bool issingular(const mat<D, D, T> &m)
  {
    return det(m) == T{0};
  }

  //! Returns an adjoint of matrix m
  template <dim_t D, class T>
  static constexpr mat<D, D, T> adjoint(const mat<D, D, T> &m)
  {
    return transpose(cofactor(m));
  }

  //! Inverts the matrix, such that m * inverse(m) = the identity
  template <dim_t D, class T>
  static constexpr mat<D, D, T> inverse(const mat<D, D, T> &m)
  {
    return adjoint(m) / det(m);
  }

  //! Component-wise saturation (clamp01)
  template <dim_t C, dim_t R, class T = float>
  static constexpr mat<C, R, T> saturate(const mat<C, R, T> &m)
  {
    return max(mat<C, R, T>::zero(), min(m, mat<C, R, T>::one()));
  }

} ////

//

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//

#endif //DYM_MAT_H_INCLUDED
