#ifndef _DYM_SWIZZLE4_H_
#define _DYM_SWIZZLE4_H_

#include "util.h"
#include "vec.h"

//

namespace dym
{ ////

  template <int I0, int I1, int I2, int I3, typename T>
  class swizzle4
  {
  public:
    swizzle4() = default;
    ~swizzle4() = default;

    static constexpr bool is_writable = (I0 != I1 && I0 != I2 && I0 != I3 && I1 != I2 && I1 != I3 && I2 != I3);
    typedef typename std::conditional<is_writable, swizzle4<I0, I1, I2, I3, T>, struct duplicate_components_swizzle>::type writable_type;

    T &operator[](const size_t i)
    {
      return raw_data()[i];
    }

    const T &operator[](const size_t i) const
    {
      return raw_data()[i];
    }

    vec<4, T> operator-() const
    {
      return vec<4, T>(-raw_data()[I0], -raw_data()[I1], -raw_data()[I2], -raw_data()[I3]);
    }

    vec<4, T> operator~() const
    {
      return vec<4, T>(~raw_data()[I0], ~raw_data()[I1], ~raw_data()[I2], ~raw_data()[I3]);
    }

    writable_type &operator=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] = va;
      raw_data()[I1] = vb;
      raw_data()[I2] = vc;
      raw_data()[I3] = vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] = va2;
      raw_data()[I1] = vb2;
      raw_data()[I2] = vc2;
      raw_data()[I3] = vd2;
      return *this;
    }

    writable_type &operator=(const vec<4, T> &s)
    {
      raw_data()[I0] = s.x;
      raw_data()[I1] = s.y;
      raw_data()[I2] = s.z;
      raw_data()[I3] = s.w;
      return *this;
    }

    writable_type &operator=(const T &s)
    {
      raw_data()[I0] = s;
      raw_data()[I1] = s;
      raw_data()[I2] = s;
      raw_data()[I3] = s;
      return *this;
    }

    vec<4, T> operator*(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] * s[I0], raw_data()[I1] * s[I1], raw_data()[I2] * s[I2], raw_data()[I3] * s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator*(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] * s[J0], raw_data()[I1] * s[J1], raw_data()[I2] * s[J2], raw_data()[I3] * s[J3]);
    }

    vec<4, T> operator*(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] * v, raw_data()[I1] * v, raw_data()[I2] * v, raw_data()[I3] * v);
    }

    friend vec<4, T> operator*(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l * r[I0], l * r[I1], l * r[I2], l * r[I3]);
    }

    vec<4, T> operator/(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] / s[I0], raw_data()[I1] / s[I1], raw_data()[I2] / s[I2], raw_data()[I3] / s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator/(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] / s[J0], raw_data()[I1] / s[J1], raw_data()[I2] / s[J2], raw_data()[I3] / s[J3]);
    }

    vec<4, T> operator/(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] / v, raw_data()[I1] / v, raw_data()[I2] / v, raw_data()[I3] / v);
    }

    friend vec<4, T> operator/(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l / r[I0], l / r[I1], l / r[I2], l / r[I3]);
    }

    vec<4, T> operator+(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] + s[I0], raw_data()[I1] + s[I1], raw_data()[I2] + s[I2], raw_data()[I3] + s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator+(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] + s[J0], raw_data()[I1] + s[J1], raw_data()[I2] + s[J2], raw_data()[I3] + s[J3]);
    }

    vec<4, T> operator+(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] + v, raw_data()[I1] + v, raw_data()[I2] + v, raw_data()[I3] + v);
    }

    friend vec<4, T> operator+(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l + r[I0], l + r[I1], l + r[I2], l + r[I3]);
    }

    vec<4, T> operator-(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] - s[I0], raw_data()[I1] - s[I1], raw_data()[I2] - s[I2], raw_data()[I3] - s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator-(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] - s[J0], raw_data()[I1] - s[J1], raw_data()[I2] - s[J2], raw_data()[I3] - s[J3]);
    }

    vec<4, T> operator-(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] - v, raw_data()[I1] - v, raw_data()[I2] - v, raw_data()[I3] - v);
    }

    friend vec<4, T> operator-(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l - r[I0], l - r[I1], l - r[I2], l - r[I3]);
    }

    vec<4, T> operator|(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] | s[I0], raw_data()[I1] | s[I1], raw_data()[I2] | s[I2], raw_data()[I3] | s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator|(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] | s[J0], raw_data()[I1] | s[J1], raw_data()[I2] | s[J2], raw_data()[I3] | s[J3]);
    }

    vec<4, T> operator|(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] | v, raw_data()[I1] | v, raw_data()[I2] | v, raw_data()[I3] | v);
    }

    friend vec<4, T> operator|(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l | r[I0], l | r[I1], l | r[I2], l | r[I3]);
    }

    vec<4, T> operator&(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] & s[I0], raw_data()[I1] & s[I1], raw_data()[I2] & s[I2], raw_data()[I3] & s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator&(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] & s[J0], raw_data()[I1] & s[J1], raw_data()[I2] & s[J2], raw_data()[I3] & s[J3]);
    }

    vec<4, T> operator&(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] & v, raw_data()[I1] & v, raw_data()[I2] & v, raw_data()[I3] & v);
    }

    friend vec<4, T> operator&(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l & r[I0], l & r[I1], l & r[I2], l & r[I3]);
    }

    vec<4, T> operator^(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] ^ s[I0], raw_data()[I1] ^ s[I1], raw_data()[I2] ^ s[I2], raw_data()[I3] ^ s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator^(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] ^ s[J0], raw_data()[I1] ^ s[J1], raw_data()[I2] ^ s[J2], raw_data()[I3] ^ s[J3]);
    }

    vec<4, T> operator^(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] ^ v, raw_data()[I1] ^ v, raw_data()[I2] ^ v, raw_data()[I3] ^ v);
    }

    friend vec<4, T> operator^(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l ^ r[I0], l ^ r[I1], l ^ r[I2], l ^ r[I3]);
    }

    vec<4, T> operator%(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] % s[I0], raw_data()[I1] % s[I1], raw_data()[I2] % s[I2], raw_data()[I3] % s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator%(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] % s[J0], raw_data()[I1] % s[J1], raw_data()[I2] % s[J2], raw_data()[I3] % s[J3]);
    }

    vec<4, T> operator%(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] % v, raw_data()[I1] % v, raw_data()[I2] % v, raw_data()[I3] % v);
    }

    friend vec<4, T> operator%(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l % r[I0], l % r[I1], l % r[I2], l % r[I3]);
    }

    vec<4, T> operator<<(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] << s[I0], raw_data()[I1] << s[I1], raw_data()[I2] << s[I2], raw_data()[I3] << s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator<<(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] << s[J0], raw_data()[I1] << s[J1], raw_data()[I2] << s[J2], raw_data()[I3] << s[J3]);
    }

    vec<4, T> operator<<(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] << v, raw_data()[I1] << v, raw_data()[I2] << v, raw_data()[I3] << v);
    }

    friend vec<4, T> operator<<(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l << r[I0], l << r[I1], l << r[I2], l << r[I3]);
    }

    vec<4, T> operator>>(const swizzle4<I0, I1, I2, I3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] >> s[I0], raw_data()[I1] >> s[I1], raw_data()[I2] >> s[I2], raw_data()[I3] >> s[I3]);
    }

    template <int J0, int J1, int J2, int J3>
    vec<4, T> operator>>(const swizzle4<J0, J1, J2, J3, T> &s) const
    {
      return vec<4, T>(raw_data()[I0] >> s[J0], raw_data()[I1] >> s[J1], raw_data()[I2] >> s[J2], raw_data()[I3] >> s[J3]);
    }

    vec<4, T> operator>>(const T &v) const
    {
      return vec<4, T>(raw_data()[I0] >> v, raw_data()[I1] >> v, raw_data()[I2] >> v, raw_data()[I3] >> v);
    }

    friend vec<4, T> operator>>(const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
    {
      return vec<4, T>(l >> r[I0], l >> r[I1], l >> r[I2], l >> r[I3]);
    }

    writable_type &operator*=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] *= va;
      raw_data()[I1] *= vb;
      raw_data()[I2] *= vc;
      raw_data()[I3] *= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator*=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] *= va2;
      raw_data()[I1] *= vb2;
      raw_data()[I2] *= vc2;
      raw_data()[I3] *= vd2;
      return *this;
    }

    writable_type &operator*=(const vec<4, T> &s)
    {
      raw_data()[I0] *= s.x;
      raw_data()[I1] *= s.y;
      raw_data()[I2] *= s.z;
      raw_data()[I3] *= s.w;
      return *this;
    }

    writable_type &operator*=(const T &s)
    {
      raw_data()[I0] *= s;
      raw_data()[I1] *= s;
      raw_data()[I2] *= s;
      raw_data()[I3] *= s;
      return *this;
    }

    writable_type &operator/=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] /= va;
      raw_data()[I1] /= vb;
      raw_data()[I2] /= vc;
      raw_data()[I3] /= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator/=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] /= va2;
      raw_data()[I1] /= vb2;
      raw_data()[I2] /= vc2;
      raw_data()[I3] /= vd2;
      return *this;
    }

    writable_type &operator/=(const vec<4, T> &s)
    {
      raw_data()[I0] /= s.x;
      raw_data()[I1] /= s.y;
      raw_data()[I2] /= s.z;
      raw_data()[I3] /= s.w;
      return *this;
    }

    writable_type &operator/=(const T &s)
    {
      raw_data()[I0] /= s;
      raw_data()[I1] /= s;
      raw_data()[I2] /= s;
      raw_data()[I3] /= s;
      return *this;
    }

    writable_type &operator+=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] += va;
      raw_data()[I1] += vb;
      raw_data()[I2] += vc;
      raw_data()[I3] += vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator+=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] += va2;
      raw_data()[I1] += vb2;
      raw_data()[I2] += vc2;
      raw_data()[I3] += vd2;
      return *this;
    }

    writable_type &operator+=(const vec<4, T> &s)
    {
      raw_data()[I0] += s.x;
      raw_data()[I1] += s.y;
      raw_data()[I2] += s.z;
      raw_data()[I3] += s.w;
      return *this;
    }

    writable_type &operator+=(const T &s)
    {
      raw_data()[I0] += s;
      raw_data()[I1] += s;
      raw_data()[I2] += s;
      raw_data()[I3] += s;
      return *this;
    }

    writable_type &operator-=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] -= va;
      raw_data()[I1] -= vb;
      raw_data()[I2] -= vc;
      raw_data()[I3] -= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator-=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] -= va2;
      raw_data()[I1] -= vb2;
      raw_data()[I2] -= vc2;
      raw_data()[I3] -= vd2;
      return *this;
    }

    writable_type &operator-=(const vec<4, T> &s)
    {
      raw_data()[I0] -= s.x;
      raw_data()[I1] -= s.y;
      raw_data()[I2] -= s.z;
      raw_data()[I3] -= s.w;
      return *this;
    }

    writable_type &operator-=(const T &s)
    {
      raw_data()[I0] -= s;
      raw_data()[I1] -= s;
      raw_data()[I2] -= s;
      raw_data()[I3] -= s;
      return *this;
    }

    writable_type &operator|=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] |= va;
      raw_data()[I1] |= vb;
      raw_data()[I2] |= vc;
      raw_data()[I3] |= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator|=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] |= va2;
      raw_data()[I1] |= vb2;
      raw_data()[I2] |= vc2;
      raw_data()[I3] |= vd2;
      return *this;
    }

    writable_type &operator|=(const vec<4, T> &s)
    {
      raw_data()[I0] |= s.x;
      raw_data()[I1] |= s.y;
      raw_data()[I2] |= s.z;
      raw_data()[I3] |= s.w;
      return *this;
    }

    writable_type &operator|=(const T &s)
    {
      raw_data()[I0] |= s;
      raw_data()[I1] |= s;
      raw_data()[I2] |= s;
      raw_data()[I3] |= s;
      return *this;
    }

    writable_type &operator&=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] &= va;
      raw_data()[I1] &= vb;
      raw_data()[I2] &= vc;
      raw_data()[I3] &= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator&=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] &= va2;
      raw_data()[I1] &= vb2;
      raw_data()[I2] &= vc2;
      raw_data()[I3] &= vd2;
      return *this;
    }

    writable_type &operator&=(const vec<4, T> &s)
    {
      raw_data()[I0] &= s.x;
      raw_data()[I1] &= s.y;
      raw_data()[I2] &= s.z;
      raw_data()[I3] &= s.w;
      return *this;
    }

    writable_type &operator&=(const T &s)
    {
      raw_data()[I0] &= s;
      raw_data()[I1] &= s;
      raw_data()[I2] &= s;
      raw_data()[I3] &= s;
      return *this;
    }

    writable_type &operator^=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] ^= va;
      raw_data()[I1] ^= vb;
      raw_data()[I2] ^= vc;
      raw_data()[I3] ^= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator^=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] ^= va2;
      raw_data()[I1] ^= vb2;
      raw_data()[I2] ^= vc2;
      raw_data()[I3] ^= vd2;
      return *this;
    }

    writable_type &operator^=(const vec<4, T> &s)
    {
      raw_data()[I0] ^= s.x;
      raw_data()[I1] ^= s.y;
      raw_data()[I2] ^= s.z;
      raw_data()[I3] ^= s.w;
      return *this;
    }

    writable_type &operator^=(const T &s)
    {
      raw_data()[I0] ^= s;
      raw_data()[I1] ^= s;
      raw_data()[I2] ^= s;
      raw_data()[I3] ^= s;
      return *this;
    }

    writable_type &operator%=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] %= va;
      raw_data()[I1] %= vb;
      raw_data()[I2] %= vc;
      raw_data()[I3] %= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator%=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] %= va2;
      raw_data()[I1] %= vb2;
      raw_data()[I2] %= vc2;
      raw_data()[I3] %= vd2;
      return *this;
    }

    writable_type &operator%=(const vec<4, T> &s)
    {
      raw_data()[I0] %= s.x;
      raw_data()[I1] %= s.y;
      raw_data()[I2] %= s.z;
      raw_data()[I3] %= s.w;
      return *this;
    }

    writable_type &operator%=(const T &s)
    {
      raw_data()[I0] %= s;
      raw_data()[I1] %= s;
      raw_data()[I2] %= s;
      raw_data()[I3] %= s;
      return *this;
    }

    writable_type &operator<<=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] <<= va;
      raw_data()[I1] <<= vb;
      raw_data()[I2] <<= vc;
      raw_data()[I3] <<= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator<<=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] <<= va2;
      raw_data()[I1] <<= vb2;
      raw_data()[I2] <<= vc2;
      raw_data()[I3] <<= vd2;
      return *this;
    }

    writable_type &operator<<=(const vec<4, T> &s)
    {
      raw_data()[I0] <<= s.x;
      raw_data()[I1] <<= s.y;
      raw_data()[I2] <<= s.z;
      raw_data()[I3] <<= s.w;
      return *this;
    }

    writable_type &operator<<=(const T &s)
    {
      raw_data()[I0] <<= s;
      raw_data()[I1] <<= s;
      raw_data()[I2] <<= s;
      raw_data()[I3] <<= s;
      return *this;
    }

    writable_type &operator>>=(const swizzle4<I0, I1, I2, I3, T> &s)
    {
      const T va = s[I0];
      const T vb = s[I1];
      const T vc = s[I2];
      const T vd = s[I3];
      raw_data()[I0] >>= va;
      raw_data()[I1] >>= vb;
      raw_data()[I2] >>= vc;
      raw_data()[I3] >>= vd;
      return *this;
    }

    template <int J0, int J1, int J2, int J3>
    writable_type &operator>>=(const swizzle4<J0, J1, J2, J3, T> &s)
    {
      const T va2 = s[J0];
      const T vb2 = s[J1];
      const T vc2 = s[J2];
      const T vd2 = s[J3];
      raw_data()[I0] >>= va2;
      raw_data()[I1] >>= vb2;
      raw_data()[I2] >>= vc2;
      raw_data()[I3] >>= vd2;
      return *this;
    }

    writable_type &operator>>=(const vec<4, T> &s)
    {
      raw_data()[I0] >>= s.x;
      raw_data()[I1] >>= s.y;
      raw_data()[I2] >>= s.z;
      raw_data()[I3] >>= s.w;
      return *this;
    }

    writable_type &operator>>=(const T &s)
    {
      raw_data()[I0] >>= s;
      raw_data()[I1] >>= s;
      raw_data()[I2] >>= s;
      raw_data()[I3] >>= s;
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

  }; //! class swizzle4

  //////////////////////
  //! OUTPUT OPERATOR //
  //////////////////////

  template <int I0, int I1, int I2, int I3, typename T>
  std::ostream &operator<<(std::ostream &os, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    os << vec<4, T>(s[I0], s[I1], s[I2], s[I3]);
    return os;
  }

  ///////////////////////
  //! BINARY OPERATORS //
  ///////////////////////

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator*(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x * s[I0], v.y * s[I1], v.z * s[I2], v.w * s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator/(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x / s[I0], v.y / s[I1], v.z / s[I2], v.w / s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator+(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x + s[I0], v.y + s[I1], v.z + s[I2], v.w + s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator-(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x - s[I0], v.y - s[I1], v.z - s[I2], v.w - s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator|(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x | s[I0], v.y | s[I1], v.z | s[I2], v.w | s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator&(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x & s[I0], v.y & s[I1], v.z & s[I2], v.w & s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator^(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x ^ s[I0], v.y ^ s[I1], v.z ^ s[I2], v.w ^ s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator%(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x % s[I0], v.y % s[I1], v.z % s[I2], v.w % s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator<<(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x << s[I0], v.y << s[I1], v.z << s[I2], v.w << s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> operator>>(const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    return vec<4, T>(v.x >> s[I0], v.y >> s[I1], v.z >> s[I2], v.w >> s[I3]);
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator*=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x *= s[I0];
    v.y *= s[I1];
    v.z *= s[I2];
    v.w *= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator/=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x /= s[I0];
    v.y /= s[I1];
    v.z /= s[I2];
    v.w /= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator+=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x += s[I0];
    v.y += s[I1];
    v.z += s[I2];
    v.w += s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator-=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x -= s[I0];
    v.y -= s[I1];
    v.z -= s[I2];
    v.w -= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator|=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x |= s[I0];
    v.y |= s[I1];
    v.z |= s[I2];
    v.w |= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator&=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x &= s[I0];
    v.y &= s[I1];
    v.z &= s[I2];
    v.w &= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator^=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x ^= s[I0];
    v.y ^= s[I1];
    v.z ^= s[I2];
    v.w ^= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator%=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x %= s[I0];
    v.y %= s[I1];
    v.z %= s[I2];
    v.w %= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator<<=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x <<= s[I0];
    v.y <<= s[I1];
    v.z <<= s[I2];
    v.w <<= s[I3];
    return v;
  }

  template <int I0, int I1, int I2, int I3, typename T>
  static vec<4, T> &operator>>=(vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
  {
    v.x >>= s[I0];
    v.y >>= s[I1];
    v.z >>= s[I2];
    v.w >>= s[I3];
    return v;
  }

} ////

//

#endif //_DYM_SWIZZLE4_H_
