#ifndef DYM_SWIZZLE2_H_INCLUDED
#define DYM_SWIZZLE2_H_INCLUDED

#include "util.h"
#include "vec.h"
#include <cstddef>
#include <type_traits>

//

namespace dym
{ ////

  struct duplicate_components_swizzle;

  template <dim_t I0, dim_t I1, class T>
  class swizzle2
  {
  public:
    swizzle2() = default;
    ~swizzle2() = default;

    static constexpr bool is_writable = (I0 != I1);

    using writable_type = std::conditional_t<is_writable, swizzle2<I0, I1, T>, duplicate_components_swizzle>;

    T &operator[](const std::size_t i)
    {
      return raw_data()[i];
    }

    const T &operator[](const std::size_t i) const
    {
      return raw_data()[i];
    }

    vec<2, T> operator-() const
    {
      return vec<2, T>(-(raw_data())[I0], -(raw_data())[I1]);
    }
    vec<2, T> operator~() const
    {
      return vec<2, T>(~(raw_data())[I0], ~(raw_data())[I1]);
    }

    writable_type &operator=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] = va;
      raw_data()[I1] = vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] = va2;
      raw_data()[I1] = vb2;
      return *this;
    }

    writable_type &operator=(const vec<2, T> &s)
    {
      raw_data()[I0] = s.x;
      raw_data()[I1] = s.y;
      return *this;
    }

    writable_type &operator=(const T &s)
    {
      raw_data()[I0] = s;
      raw_data()[I1] = s;
      return *this;
    }

    vec<2, T> operator*(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] * s[I0], raw_data()[I1] * s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator*(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] * s[J0], raw_data()[I1] * s[J1]);
    }

    vec<2, T> operator*(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] * v, raw_data()[I1] * v);
    }

    friend vec<2, T> operator*(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l * r[I0], l * r[I1]);
    }

    vec<2, T> operator/(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] / s[I0], raw_data()[I1] / s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator/(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] / s[J0], raw_data()[I1] / s[J1]);
    }

    vec<2, T> operator/(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] / v, raw_data()[I1] / v);
    }

    friend vec<2, T> operator/(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l / r[I0], l / r[I1]);
    }

    vec<2, T> operator+(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] + s[I0], raw_data()[I1] + s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator+(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] + s[J0], raw_data()[I1] + s[J1]);
    }

    vec<2, T> operator+(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] + v, raw_data()[I1] + v);
    }

    friend vec<2, T> operator+(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l + r[I0], l + r[I1]);
    }

    vec<2, T> operator-(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] - s[I0], raw_data()[I1] - s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator-(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] - s[J0], raw_data()[I1] - s[J1]);
    }

    vec<2, T> operator-(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] - v, raw_data()[I1] - v);
    }

    friend vec<2, T> operator-(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l - r[I0], l - r[I1]);
    }

    vec<2, T> operator|(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] | s[I0], raw_data()[I1] | s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator|(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] | s[J0], raw_data()[I1] | s[J1]);
    }

    vec<2, T> operator|(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] | v, raw_data()[I1] | v);
    }

    friend vec<2, T> operator|(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l | r[I0], l | r[I1]);
    }

    vec<2, T> operator&(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] & s[I0], raw_data()[I1] & s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator&(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] & s[J0], raw_data()[I1] & s[J1]);
    }

    vec<2, T> operator&(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] & v, raw_data()[I1] & v);
    }

    friend vec<2, T> operator&(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l & r[I0], l & r[I1]);
    }

    vec<2, T> operator^(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] ^ s[I0], raw_data()[I1] ^ s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator^(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] ^ s[J0], raw_data()[I1] ^ s[J1]);
    }

    vec<2, T> operator^(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] ^ v, raw_data()[I1] ^ v);
    }

    friend vec<2, T> operator^(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l ^ r[I0], l ^ r[I1]);
    }

    vec<2, T> operator%(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] % s[I0], raw_data()[I1] % s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator%(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] % s[J0], raw_data()[I1] % s[J1]);
    }

    vec<2, T> operator%(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] % v, raw_data()[I1] % v);
    }

    friend vec<2, T> operator%(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l % r[I0], l % r[I1]);
    }

    vec<2, T> operator<<(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] << s[I0], raw_data()[I1] << s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator<<(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] << s[J0], raw_data()[I1] << s[J1]);
    }

    vec<2, T> operator<<(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] << v, raw_data()[I1] << v);
    }

    friend vec<2, T> operator<<(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l << r[I0], l << r[I1]);
    }

    vec<2, T> operator>>(const swizzle2<I0, I1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] >> s[I0], raw_data()[I1] >> s[I1]);
    }

    template <dim_t J0, dim_t J1>
    vec<2, T> operator>>(const swizzle2<J0, J1, T> &s) const
    {
      return vec<2, T>(raw_data()[I0] >> s[J0], raw_data()[I1] >> s[J1]);
    }

    vec<2, T> operator>>(const T &v) const
    {
      return vec<2, T>(raw_data()[I0] >> v, raw_data()[I1] >> v);
    }

    friend vec<2, T> operator>>(const T &l, const swizzle2<I0, I1, T> &r)
    {
      return vec<2, T>(l >> r[I0], l >> r[I1]);
    }

    writable_type &operator*=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] *= va;
      raw_data()[I1] *= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator*=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] *= va2;
      raw_data()[I1] *= vb2;
      return *this;
    }

    writable_type &operator*=(const vec<2, T> &s)
    {
      raw_data()[I0] *= s.x;
      raw_data()[I1] *= s.y;
      return *this;
    }

    writable_type &operator*=(const T &s)
    {
      raw_data()[I0] *= s;
      raw_data()[I1] *= s;
      return *this;
    }

    writable_type &operator/=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] /= va;
      raw_data()[I1] /= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator/=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] /= va2;
      raw_data()[I1] /= vb2;
      return *this;
    }

    writable_type &operator/=(const vec<2, T> &s)
    {
      raw_data()[I0] /= s.x;
      raw_data()[I1] /= s.y;
      return *this;
    }

    writable_type &operator/=(const T &s)
    {
      raw_data()[I0] /= s;
      raw_data()[I1] /= s;
      return *this;
    }

    writable_type &operator+=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] += va;
      raw_data()[I1] += vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator+=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] += va2;
      raw_data()[I1] += vb2;
      return *this;
    }

    writable_type &operator+=(const vec<2, T> &s)
    {
      raw_data()[I0] += s.x;
      raw_data()[I1] += s.y;
      return *this;
    }

    writable_type &operator+=(const T &s)
    {
      raw_data()[I0] += s;
      raw_data()[I1] += s;
      return *this;
    }

    writable_type &operator-=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] -= va;
      raw_data()[I1] -= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator-=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] -= va2;
      raw_data()[I1] -= vb2;
      return *this;
    }

    writable_type &operator-=(const vec<2, T> &s)
    {
      raw_data()[I0] -= s.x;
      raw_data()[I1] -= s.y;
      return *this;
    }

    writable_type &operator-=(const T &s)
    {
      raw_data()[I0] -= s;
      raw_data()[I1] -= s;
      return *this;
    }

    writable_type &operator|=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] |= va;
      raw_data()[I1] |= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator|=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] |= va2;
      raw_data()[I1] |= vb2;
      return *this;
    }

    writable_type &operator|=(const vec<2, T> &s)
    {
      raw_data()[I0] |= s.x;
      raw_data()[I1] |= s.y;
      return *this;
    }

    writable_type &operator|=(const T &s)
    {
      raw_data()[I0] |= s;
      raw_data()[I1] |= s;
      return *this;
    }

    writable_type &operator&=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] &= va;
      raw_data()[I1] &= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator&=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] &= va2;
      raw_data()[I1] &= vb2;
      return *this;
    }

    writable_type &operator&=(const vec<2, T> &s)
    {
      raw_data()[I0] &= s.x;
      raw_data()[I1] &= s.y;
      return *this;
    }

    writable_type &operator&=(const T &s)
    {
      raw_data()[I0] &= s;
      raw_data()[I1] &= s;
      return *this;
    }

    writable_type &operator^=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] ^= va;
      raw_data()[I1] ^= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator^=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] ^= va2;
      raw_data()[I1] ^= vb2;
      return *this;
    }

    writable_type &operator^=(const vec<2, T> &s)
    {
      raw_data()[I0] ^= s.x;
      raw_data()[I1] ^= s.y;
      return *this;
    }

    writable_type &operator^=(const T &s)
    {
      raw_data()[I0] ^= s;
      raw_data()[I1] ^= s;
      return *this;
    }

    writable_type &operator%=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] %= va;
      raw_data()[I1] %= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator%=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] %= va2;
      raw_data()[I1] %= vb2;
      return *this;
    }

    writable_type &operator%=(const vec<2, T> &s)
    {
      raw_data()[I0] %= s.x;
      raw_data()[I1] %= s.y;
      return *this;
    }

    writable_type &operator%=(const T &s)
    {
      raw_data()[I0] %= s;
      raw_data()[I1] %= s;
      return *this;
    }

    writable_type &operator<<=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] <<= va;
      raw_data()[I1] <<= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator<<=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] <<= va2;
      raw_data()[I1] <<= vb2;
      return *this;
    }

    writable_type &operator<<=(const vec<2, T> &s)
    {
      raw_data()[I0] <<= s.x;
      raw_data()[I1] <<= s.y;
      return *this;
    }

    writable_type &operator<<=(const T &s)
    {
      raw_data()[I0] <<= s;
      raw_data()[I1] <<= s;
      return *this;
    }

    writable_type &operator>>=(const swizzle2<I0, I1, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      raw_data()[I0] >>= va;
      raw_data()[I1] >>= vb;
      return *this;
    }

    template <dim_t J0, dim_t J1>
    writable_type &operator>>=(const swizzle2<J0, J1, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      raw_data()[I0] >>= va2;
      raw_data()[I1] >>= vb2;
      return *this;
    }

    writable_type &operator>>=(const vec<2, T> &s)
    {
      raw_data()[I0] >>= s.x;
      raw_data()[I1] >>= s.y;
      return *this;
    }

    writable_type &operator>>=(const T &s)
    {
      raw_data()[I0] >>= s;
      raw_data()[I1] >>= s;
      return *this;
    }

  private:
    T *raw_data()
    {
      return reinterpret_cast<T *>(this);
    }

    const T *raw_data() const
    {
      return reinterpret_cast<const T *>(this);
    }

  }; //! class swizzle2

  //////////////////////
  //! OUTPUT OPERATOR //
  //////////////////////

  template <dim_t I0, dim_t I1, class T>
  std::ostream &operator<<(std::ostream &os, const swizzle2<I0, I1, T> &s)
  {
    os << vec<2, T>(s[I0], s[I1]);
    return os;
  }

  ///////////////////////
  //! BINARY OPERATORS //
  ///////////////////////

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator*(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x * s[I0], v.y * s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator/(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x / s[I0], v.y / s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator+(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x + s[I0], v.y + s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator-(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x - s[I0], v.y - s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator|(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x | s[I0], v.y | s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator&(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x & s[I0], v.y & s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator^(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x ^ s[I0], v.y ^ s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator%(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x % s[I0], v.y % s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator<<(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x << s[I0], v.y << s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> operator>>(const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    return vec<2, T>(v.x >> s[I0], v.y >> s[I1]);
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator*=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x *= s[I0];
    v.y *= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator/=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x /= s[I0];
    v.y /= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator+=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x += s[I0];
    v.y += s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator-=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x -= s[I0];
    v.y -= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator|=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x |= s[I0];
    v.y |= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator&=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x &= s[I0];
    v.y &= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator^=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x ^= s[I0];
    v.y ^= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator%=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x %= s[I0];
    v.y %= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator<<=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x <<= s[I0];
    v.y <<= s[I1];
    return v;
  }

  template <dim_t I0, dim_t I1, class T>
  static vec<2, T> &operator>>=(vec<2, T> &v, const swizzle2<I0, I1, T> &s)
  {
    v.x >>= s[I0];
    v.y >>= s[I1];
    return v;
  }

} ////

//

#endif //DYM_SWIZZLE2_H_INCLUDED
