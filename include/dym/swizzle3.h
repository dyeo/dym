#ifndef _DYM_SWIZZLE3_H_
#define _DYM_SWIZZLE3_H_

#include "util.h"
#include "vec.h"

//

namespace dym
{ ////

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  class swizzle3
  {
  public:
    swizzle3() = default;
    ~swizzle3() = default;

    static constexpr bool is_writable = (I0 != I1 && I0 != I2 && I1 != I2);

    typedef class std::conditional<is_writable, swizzle3<I0, I1, I2, T>, struct duplicate_components_swizzle>::type writable_type;

    T &operator[](const size_t i)
    {
      return raw_data()[i];
    }

    const T &operator[](const size_t i) const
    {
      return raw_data()[i];
    }

    vec<3, T> operator-() const
    {
      return vec<3, T>(-raw_data()[I0], -raw_data()[I1], -raw_data()[I2]);
    }

    vec<3, T> operator~() const
    {
      return vec<3, T>(~raw_data()[I0], ~raw_data()[I1], ~raw_data()[I2]);
    }

    writable_type &operator=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] = va;
      raw_data()[I1] = vb;
      raw_data()[I2] = vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] = va2;
      raw_data()[I1] = vb2;
      raw_data()[I2] = vc2;
      return *this;
    }

    writable_type &operator=(const vec<3, T> &s)
    {
      raw_data()[I0] = s.x;
      raw_data()[I1] = s.y;
      raw_data()[I2] = s.z;
      return *this;
    }

    writable_type &operator=(const T &s)
    {
      raw_data()[I0] = s;
      raw_data()[I1] = s;
      raw_data()[I2] = s;
      return *this;
    }

    vec<3, T> operator*(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] * s[I0], raw_data()[I1] * s[I1], raw_data()[I2] * s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator*(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] * s[J0], raw_data()[I1] * s[J1], raw_data()[I2] * s[J2]);
    }

    vec<3, T> operator*(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] * v, raw_data()[I1] * v, raw_data()[I2] * v);
    }

    friend vec<3, T> operator*(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l * r[I0], l * r[I1], l * r[I2]);
    }

    vec<3, T> operator/(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] / s[I0], raw_data()[I1] / s[I1], raw_data()[I2] / s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator/(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] / s[J0], raw_data()[I1] / s[J1], raw_data()[I2] / s[J2]);
    }

    vec<3, T> operator/(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] / v, raw_data()[I1] / v, raw_data()[I2] / v);
    }

    friend vec<3, T> operator/(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l / r[I0], l / r[I1], l / r[I2]);
    }

    vec<3, T> operator+(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] + s[I0], raw_data()[I1] + s[I1], raw_data()[I2] + s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator+(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] + s[J0], raw_data()[I1] + s[J1], raw_data()[I2] + s[J2]);
    }

    vec<3, T> operator+(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] + v, raw_data()[I1] + v, raw_data()[I2] + v);
    }

    friend vec<3, T> operator+(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l + r[I0], l + r[I1], l + r[I2]);
    }

    vec<3, T> operator-(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] - s[I0], raw_data()[I1] - s[I1], raw_data()[I2] - s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator-(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] - s[J0], raw_data()[I1] - s[J1], raw_data()[I2] - s[J2]);
    }

    vec<3, T> operator-(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] - v, raw_data()[I1] - v, raw_data()[I2] - v);
    }

    friend vec<3, T> operator-(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l - r[I0], l - r[I1], l - r[I2]);
    }

    vec<3, T> operator|(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] | s[I0], raw_data()[I1] | s[I1], raw_data()[I2] | s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator|(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] | s[J0], raw_data()[I1] | s[J1], raw_data()[I2] | s[J2]);
    }

    vec<3, T> operator|(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] | v, raw_data()[I1] | v, raw_data()[I2] | v);
    }

    friend vec<3, T> operator|(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l | r[I0], l | r[I1], l | r[I2]);
    }

    vec<3, T> operator&(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] & s[I0], raw_data()[I1] & s[I1], raw_data()[I2] & s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator&(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] & s[J0], raw_data()[I1] & s[J1], raw_data()[I2] & s[J2]);
    }

    vec<3, T> operator&(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] & v, raw_data()[I1] & v, raw_data()[I2] & v);
    }

    friend vec<3, T> operator&(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l & r[I0], l & r[I1], l & r[I2]);
    }

    vec<3, T> operator^(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] ^ s[I0], raw_data()[I1] ^ s[I1], raw_data()[I2] ^ s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator^(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] ^ s[J0], raw_data()[I1] ^ s[J1], raw_data()[I2] ^ s[J2]);
    }

    vec<3, T> operator^(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] ^ v, raw_data()[I1] ^ v, raw_data()[I2] ^ v);
    }

    friend vec<3, T> operator^(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l ^ r[I0], l ^ r[I1], l ^ r[I2]);
    }

    vec<3, T> operator%(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] % s[I0], raw_data()[I1] % s[I1], raw_data()[I2] % s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator%(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] % s[J0], raw_data()[I1] % s[J1], raw_data()[I2] % s[J2]);
    }

    vec<3, T> operator%(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] % v, raw_data()[I1] % v, raw_data()[I2] % v);
    }

    friend vec<3, T> operator%(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l % r[I0], l % r[I1], l % r[I2]);
    }

    vec<3, T> operator<<(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] << s[I0], raw_data()[I1] << s[I1], raw_data()[I2] << s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator<<(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] << s[J0], raw_data()[I1] << s[J1], raw_data()[I2] << s[J2]);
    }

    vec<3, T> operator<<(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] << v, raw_data()[I1] << v, raw_data()[I2] << v);
    }

    friend vec<3, T> operator<<(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l << r[I0], l << r[I1], l << r[I2]);
    }

    vec<3, T> operator>>(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] >> s[I0], raw_data()[I1] >> s[I1], raw_data()[I2] >> s[I2]);
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    vec<3, T> operator>>(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(raw_data()[I0] >> s[J0], raw_data()[I1] >> s[J1], raw_data()[I2] >> s[J2]);
    }

    vec<3, T> operator>>(const T &v) const
    {
      return vec<3, T>(raw_data()[I0] >> v, raw_data()[I1] >> v, raw_data()[I2] >> v);
    }

    friend vec<3, T> operator>>(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l >> r[I0], l >> r[I1], l >> r[I2]);
    }

    writable_type &operator*=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] *= va;
      raw_data()[I1] *= vb;
      raw_data()[I2] *= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator*=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] *= va2;
      raw_data()[I1] *= vb2;
      raw_data()[I2] *= vc2;
      return *this;
    }

    writable_type &operator*=(const vec<3, T> &s)
    {
      raw_data()[I0] *= s.x;
      raw_data()[I1] *= s.y;
      raw_data()[I2] *= s.z;
      return *this;
    }

    writable_type &operator*=(const T &s)
    {
      raw_data()[I0] *= s;
      raw_data()[I1] *= s;
      raw_data()[I2] *= s;
      return *this;
    }

    writable_type &operator/=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] /= va;
      raw_data()[I1] /= vb;
      raw_data()[I2] /= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator/=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] /= va2;
      raw_data()[I1] /= vb2;
      raw_data()[I2] /= vc2;
      return *this;
    }

    writable_type &operator/=(const vec<3, T> &s)
    {
      raw_data()[I0] /= s.x;
      raw_data()[I1] /= s.y;
      raw_data()[I2] /= s.z;
      return *this;
    }

    writable_type &operator/=(const T &s)
    {
      raw_data()[I0] /= s;
      raw_data()[I1] /= s;
      raw_data()[I2] /= s;
      return *this;
    }

    writable_type &operator+=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] += va;
      raw_data()[I1] += vb;
      raw_data()[I2] += vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator+=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] += va2;
      raw_data()[I1] += vb2;
      raw_data()[I2] += vc2;
      return *this;
    }

    writable_type &operator+=(const vec<3, T> &s)
    {
      raw_data()[I0] += s.x;
      raw_data()[I1] += s.y;
      raw_data()[I2] += s.z;
      return *this;
    }

    writable_type &operator+=(const T &s)
    {
      raw_data()[I0] += s;
      raw_data()[I1] += s;
      raw_data()[I2] += s;
      return *this;
    }

    writable_type &operator-=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] -= va;
      raw_data()[I1] -= vb;
      raw_data()[I2] -= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator-=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] -= va2;
      raw_data()[I1] -= vb2;
      raw_data()[I2] -= vc2;
      return *this;
    }

    writable_type &operator-=(const vec<3, T> &s)
    {
      raw_data()[I0] -= s.x;
      raw_data()[I1] -= s.y;
      raw_data()[I2] -= s.z;
      return *this;
    }

    writable_type &operator-=(const T &s)
    {
      raw_data()[I0] -= s;
      raw_data()[I1] -= s;
      raw_data()[I2] -= s;
      return *this;
    }

    writable_type &operator|=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] |= va;
      raw_data()[I1] |= vb;
      raw_data()[I2] |= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator|=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] |= va2;
      raw_data()[I1] |= vb2;
      raw_data()[I2] |= vc2;
      return *this;
    }

    writable_type &operator|=(const vec<3, T> &s)
    {
      raw_data()[I0] |= s.x;
      raw_data()[I1] |= s.y;
      raw_data()[I2] |= s.z;
      return *this;
    }

    writable_type &operator|=(const T &s)
    {
      raw_data()[I0] |= s;
      raw_data()[I1] |= s;
      raw_data()[I2] |= s;
      return *this;
    }

    writable_type &operator&=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] &= va;
      raw_data()[I1] &= vb;
      raw_data()[I2] &= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator&=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] &= va2;
      raw_data()[I1] &= vb2;
      raw_data()[I2] &= vc2;
      return *this;
    }

    writable_type &operator&=(const vec<3, T> &s)
    {
      raw_data()[I0] &= s.x;
      raw_data()[I1] &= s.y;
      raw_data()[I2] &= s.z;
      return *this;
    }

    writable_type &operator&=(const T &s)
    {
      raw_data()[I0] &= s;
      raw_data()[I1] &= s;
      raw_data()[I2] &= s;
      return *this;
    }

    writable_type &operator^=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] ^= va;
      raw_data()[I1] ^= vb;
      raw_data()[I2] ^= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator^=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] ^= va2;
      raw_data()[I1] ^= vb2;
      raw_data()[I2] ^= vc2;
      return *this;
    }

    writable_type &operator^=(const vec<3, T> &s)
    {
      raw_data()[I0] ^= s.x;
      raw_data()[I1] ^= s.y;
      raw_data()[I2] ^= s.z;
      return *this;
    }

    writable_type &operator^=(const T &s)
    {
      raw_data()[I0] ^= s;
      raw_data()[I1] ^= s;
      raw_data()[I2] ^= s;
      return *this;
    }

    writable_type &operator%=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] %= va;
      raw_data()[I1] %= vb;
      raw_data()[I2] %= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator%=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] %= va2;
      raw_data()[I1] %= vb2;
      raw_data()[I2] %= vc2;
      return *this;
    }

    writable_type &operator%=(const vec<3, T> &s)
    {
      raw_data()[I0] %= s.x;
      raw_data()[I1] %= s.y;
      raw_data()[I2] %= s.z;
      return *this;
    }

    writable_type &operator%=(const T &s)
    {
      raw_data()[I0] %= s;
      raw_data()[I1] %= s;
      raw_data()[I2] %= s;
      return *this;
    }

    writable_type &operator<<=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] <<= va;
      raw_data()[I1] <<= vb;
      raw_data()[I2] <<= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator<<=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] <<= va2;
      raw_data()[I1] <<= vb2;
      raw_data()[I2] <<= vc2;
      return *this;
    }

    writable_type &operator<<=(const vec<3, T> &s)
    {
      raw_data()[I0] <<= s.x;
      raw_data()[I1] <<= s.y;
      raw_data()[I2] <<= s.z;
      return *this;
    }

    writable_type &operator<<=(const T &s)
    {
      raw_data()[I0] <<= s;
      raw_data()[I1] <<= s;
      raw_data()[I2] <<= s;
      return *this;
    }

    writable_type &operator>>=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      raw_data()[I0] >>= va;
      raw_data()[I1] >>= vb;
      raw_data()[I2] >>= vc;
      return *this;
    }

    template <dim_t J0, dim_t J1, dim_t J2>
    writable_type &operator>>=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      raw_data()[I0] >>= va2;
      raw_data()[I1] >>= vb2;
      raw_data()[I2] >>= vc2;
      return *this;
    }

    writable_type &operator>>=(const vec<3, T> &s)
    {
      raw_data()[I0] >>= s.x;
      raw_data()[I1] >>= s.y;
      raw_data()[I2] >>= s.z;
      return *this;
    }

    writable_type &operator>>=(const T &s)
    {
      raw_data()[I0] >>= s;
      raw_data()[I1] >>= s;
      raw_data()[I2] >>= s;
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

  }; //! class swizzle3

  //////////////////////
  //! OUTPUT OPERATOR //
  //////////////////////

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  std::ostream &operator<<(std::ostream &os, const swizzle3<I0, I1, I2, T> &s)
  {
    os << vec<3, T>(s[I0], s[I1], s[I2]);
    return os;
  }

  ///////////////////////
  //! BINARY OPERATORS //
  ///////////////////////

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator*(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x * s[I0], v.y * s[I1], v.z * s[I2], v.z * s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator/(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x / s[I0], v.y / s[I1], v.z / s[I2], v.z / s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator+(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x + s[I0], v.y + s[I1], v.z + s[I2], v.z + s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator-(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x - s[I0], v.y - s[I1], v.z - s[I2], v.z - s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator|(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x | s[I0], v.y | s[I1], v.z | s[I2], v.z | s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator&(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x & s[I0], v.y & s[I1], v.z & s[I2], v.z & s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator^(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x ^ s[I0], v.y ^ s[I1], v.z ^ s[I2], v.z ^ s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator%(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x % s[I0], v.y % s[I1], v.z % s[I2], v.z % s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator<<(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x << s[I0], v.y << s[I1], v.z << s[I2], v.z << s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> operator>>(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x >> s[I0], v.y >> s[I1], v.z >> s[I2], v.z >> s[I2]);
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator*=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x *= s[I0];
    v.y *= s[I1];
    v.z *= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator/=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x /= s[I0];
    v.y /= s[I1];
    v.z /= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator+=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x += s[I0];
    v.y += s[I1];
    v.z += s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator-=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x -= s[I0];
    v.y -= s[I1];
    v.z -= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator|=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x |= s[I0];
    v.y |= s[I1];
    v.z |= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator&=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x &= s[I0];
    v.y &= s[I1];
    v.z &= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator^=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x ^= s[I0];
    v.y ^= s[I1];
    v.z ^= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator%=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x %= s[I0];
    v.y %= s[I1];
    v.z %= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator<<=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x <<= s[I0];
    v.y <<= s[I1];
    v.z <<= s[I2];
    return v;
  }

  template <dim_t I0, dim_t I1, dim_t I2, class T>
  static vec<3, T> &operator>>=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x >>= s[I0];
    v.y >>= s[I1];
    v.z >>= s[I2];
    return v;
  }

} ////

//

#endif //_DYM_SWIZZLE3_H_
