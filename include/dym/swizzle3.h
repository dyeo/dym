#ifndef _DYM_SWIZZLE3_H_
#define _DYM_SWIZZLE3_H_

#include "util.h"
#include "vec.h"

//

namespace dym
{ ////

  template <int I0, int I1, int I2, typename T>
  class swizzle3
  {
  public:
    swizzle3() = default;
    ~swizzle3() = default;

    static constexpr bool is_writable = (I0 != I1 && I0 != I2 && I1 != I2);

    typedef typename std::conditional<is_writable, swizzle3<I0, I1, I2, T>, struct duplicate_components_swizzle>::type writable_type;

    T &operator[](const size_t i)
    {
      return static_cast<T *const>(this)[i];
    }

    const T &operator[](const size_t i) const
    {
      return static_cast<T *const>(this)[i];
    }

    vec<3, T> operator-() const
    {
      return vec<3, T>(-static_cast<const T *>(this)[I0], -static_cast<const T *>(this)[I1], -static_cast<const T *>(this)[I2]);
    }

    vec<3, T> operator~() const
    {
      return vec<3, T>(~static_cast<const T *>(this)[I0], ~static_cast<const T *>(this)[I1], ~static_cast<const T *>(this)[I2]);
    }

    writable_type &operator=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] = va;
      static_cast<T *>(this)[I1] = vb;
      static_cast<T *>(this)[I2] = vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] = va2;
      static_cast<T *>(this)[I1] = vb2;
      static_cast<T *>(this)[I2] = vc2;
      return *this;
    }

    writable_type &operator=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] = s.x;
      static_cast<T *>(this)[I1] = s.y;
      static_cast<T *>(this)[I2] = s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator=(const T &s)
    {
      static_cast<const T *>(&s)[I0] = s;
      static_cast<const T *>(&s)[I1] = s;
      static_cast<const T *>(&s)[I2] = s;
      return *this;
    }

    vec<3, T> operator*(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] * static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] * static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] * static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator*(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] * static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] * static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] * static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator*(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] * v, static_cast<const T *>(this)[I1] * v, static_cast<const T *>(this)[I2] * v);
    }

    friend vec<3, T> operator*(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l * static_cast<const T *>(r)[I0], l * static_cast<const T *>(r)[I1], l * static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator/(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] / static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] / static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] / static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator/(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] / static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] / static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] / static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator/(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] / v, static_cast<const T *>(this)[I1] / v, static_cast<const T *>(this)[I2] / v);
    }

    friend vec<3, T> operator/(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l / static_cast<const T *>(r)[I0], l / static_cast<const T *>(r)[I1], l / static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator+(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] + static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] + static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] + static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator+(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] + static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] + static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] + static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator+(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] + v, static_cast<const T *>(this)[I1] + v, static_cast<const T *>(this)[I2] + v);
    }

    friend vec<3, T> operator+(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l + static_cast<const T *>(r)[I0], l + static_cast<const T *>(r)[I1], l + static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator-(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] - static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] - static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] - static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator-(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] - static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] - static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] - static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator-(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] - v, static_cast<const T *>(this)[I1] - v, static_cast<const T *>(this)[I2] - v);
    }

    friend vec<3, T> operator-(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l - static_cast<const T *>(r)[I0], l - static_cast<const T *>(r)[I1], l - static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator|(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] | static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] | static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] | static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator|(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] | static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] | static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] | static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator|(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] | v, static_cast<const T *>(this)[I1] | v, static_cast<const T *>(this)[I2] | v);
    }

    friend vec<3, T> operator|(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l | static_cast<const T *>(r)[I0], l | static_cast<const T *>(r)[I1], l | static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator&(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] & static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] & static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] & static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator&(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] & static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] & static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] & static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator&(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] & v, static_cast<const T *>(this)[I1] & v, static_cast<const T *>(this)[I2] & v);
    }

    friend vec<3, T> operator&(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l & static_cast<const T *>(r)[I0], l & static_cast<const T *>(r)[I1], l & static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator^(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] ^ static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] ^ static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] ^ static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator^(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] ^ static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] ^ static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] ^ static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator^(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] ^ v, static_cast<const T *>(this)[I1] ^ v, static_cast<const T *>(this)[I2] ^ v);
    }

    friend vec<3, T> operator^(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l ^ static_cast<const T *>(r)[I0], l ^ static_cast<const T *>(r)[I1], l ^ static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator%(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] % static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] % static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] % static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator%(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] % static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] % static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] % static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator%(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] % v, static_cast<const T *>(this)[I1] % v, static_cast<const T *>(this)[I2] % v);
    }

    friend vec<3, T> operator%(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l % static_cast<const T *>(r)[I0], l % static_cast<const T *>(r)[I1], l % static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator<<(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] << static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] << static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] << static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator<<(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] << static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] << static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] << static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator<<(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] << v, static_cast<const T *>(this)[I1] << v, static_cast<const T *>(this)[I2] << v);
    }

    friend vec<3, T> operator<<(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l << static_cast<const T *>(r)[I0], l << static_cast<const T *>(r)[I1], l << static_cast<const T *>(r)[I2]);
    }

    vec<3, T> operator>>(const swizzle3<I0, I1, I2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] >> static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] >> static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] >> static_cast<const T *>(&s)[I2]);
    }

    template <int J0, int J1, int J2>
    vec<3, T> operator>>(const swizzle3<J0, J1, J2, T> &s) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] >> static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] >> static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] >> static_cast<const T *>(&s)[J2]);
    }

    vec<3, T> operator>>(const T &v) const
    {
      return vec<3, T>(static_cast<const T *>(this)[I0] >> v, static_cast<const T *>(this)[I1] >> v, static_cast<const T *>(this)[I2] >> v);
    }

    friend vec<3, T> operator>>(const T &l, const swizzle3<I0, I1, I2, T> &r)
    {
      return vec<3, T>(l >> static_cast<const T *>(r)[I0], l >> static_cast<const T *>(r)[I1], l >> static_cast<const T *>(r)[I2]);
    }

    writable_type &operator*=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] *= va;
      static_cast<T *>(this)[I1] *= vb;
      static_cast<T *>(this)[I2] *= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator*=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] *= va2;
      static_cast<T *>(this)[I1] *= vb2;
      static_cast<T *>(this)[I2] *= vc2;
      return *this;
    }

    writable_type &operator*=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] *= s.x;
      static_cast<T *>(this)[I1] *= s.y;
      static_cast<T *>(this)[I2] *= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator*=(const T &s)
    {
      static_cast<const T *>(&s)[I0] *= s;
      static_cast<const T *>(&s)[I1] *= s;
      static_cast<const T *>(&s)[I2] *= s;
      return *this;
    }

    writable_type &operator/=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] /= va;
      static_cast<T *>(this)[I1] /= vb;
      static_cast<T *>(this)[I2] /= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator/=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] /= va2;
      static_cast<T *>(this)[I1] /= vb2;
      static_cast<T *>(this)[I2] /= vc2;
      return *this;
    }

    writable_type &operator/=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] /= s.x;
      static_cast<T *>(this)[I1] /= s.y;
      static_cast<T *>(this)[I2] /= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator/=(const T &s)
    {
      static_cast<const T *>(&s)[I0] /= s;
      static_cast<const T *>(&s)[I1] /= s;
      static_cast<const T *>(&s)[I2] /= s;
      return *this;
    }

    writable_type &operator+=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] += va;
      static_cast<T *>(this)[I1] += vb;
      static_cast<T *>(this)[I2] += vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator+=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] += va2;
      static_cast<T *>(this)[I1] += vb2;
      static_cast<T *>(this)[I2] += vc2;
      return *this;
    }

    writable_type &operator+=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] += s.x;
      static_cast<T *>(this)[I1] += s.y;
      static_cast<T *>(this)[I2] += s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator+=(const T &s)
    {
      static_cast<const T *>(&s)[I0] += s;
      static_cast<const T *>(&s)[I1] += s;
      static_cast<const T *>(&s)[I2] += s;
      return *this;
    }

    writable_type &operator-=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] -= va;
      static_cast<T *>(this)[I1] -= vb;
      static_cast<T *>(this)[I2] -= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator-=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] -= va2;
      static_cast<T *>(this)[I1] -= vb2;
      static_cast<T *>(this)[I2] -= vc2;
      return *this;
    }

    writable_type &operator-=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] -= s.x;
      static_cast<T *>(this)[I1] -= s.y;
      static_cast<T *>(this)[I2] -= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator-=(const T &s)
    {
      static_cast<const T *>(&s)[I0] -= s;
      static_cast<const T *>(&s)[I1] -= s;
      static_cast<const T *>(&s)[I2] -= s;
      return *this;
    }

    writable_type &operator|=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] |= va;
      static_cast<T *>(this)[I1] |= vb;
      static_cast<T *>(this)[I2] |= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator|=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] |= va2;
      static_cast<T *>(this)[I1] |= vb2;
      static_cast<T *>(this)[I2] |= vc2;
      return *this;
    }

    writable_type &operator|=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] |= s.x;
      static_cast<T *>(this)[I1] |= s.y;
      static_cast<T *>(this)[I2] |= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator|=(const T &s)
    {
      static_cast<const T *>(&s)[I0] |= s;
      static_cast<const T *>(&s)[I1] |= s;
      static_cast<const T *>(&s)[I2] |= s;
      return *this;
    }

    writable_type &operator&=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] &= va;
      static_cast<T *>(this)[I1] &= vb;
      static_cast<T *>(this)[I2] &= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator&=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] &= va2;
      static_cast<T *>(this)[I1] &= vb2;
      static_cast<T *>(this)[I2] &= vc2;
      return *this;
    }

    writable_type &operator&=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] &= s.x;
      static_cast<T *>(this)[I1] &= s.y;
      static_cast<T *>(this)[I2] &= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator&=(const T &s)
    {
      static_cast<const T *>(&s)[I0] &= s;
      static_cast<const T *>(&s)[I1] &= s;
      static_cast<const T *>(&s)[I2] &= s;
      return *this;
    }

    writable_type &operator^=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] ^= va;
      static_cast<T *>(this)[I1] ^= vb;
      static_cast<T *>(this)[I2] ^= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator^=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] ^= va2;
      static_cast<T *>(this)[I1] ^= vb2;
      static_cast<T *>(this)[I2] ^= vc2;
      return *this;
    }

    writable_type &operator^=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] ^= s.x;
      static_cast<T *>(this)[I1] ^= s.y;
      static_cast<T *>(this)[I2] ^= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator^=(const T &s)
    {
      static_cast<const T *>(&s)[I0] ^= s;
      static_cast<const T *>(&s)[I1] ^= s;
      static_cast<const T *>(&s)[I2] ^= s;
      return *this;
    }

    writable_type &operator%=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] %= va;
      static_cast<T *>(this)[I1] %= vb;
      static_cast<T *>(this)[I2] %= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator%=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] %= va2;
      static_cast<T *>(this)[I1] %= vb2;
      static_cast<T *>(this)[I2] %= vc2;
      return *this;
    }

    writable_type &operator%=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] %= s.x;
      static_cast<T *>(this)[I1] %= s.y;
      static_cast<T *>(this)[I2] %= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator%=(const T &s)
    {
      static_cast<const T *>(&s)[I0] %= s;
      static_cast<const T *>(&s)[I1] %= s;
      static_cast<const T *>(&s)[I2] %= s;
      return *this;
    }

    writable_type &operator<<=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] <<= va;
      static_cast<T *>(this)[I1] <<= vb;
      static_cast<T *>(this)[I2] <<= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator<<=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] <<= va2;
      static_cast<T *>(this)[I1] <<= vb2;
      static_cast<T *>(this)[I2] <<= vc2;
      return *this;
    }

    writable_type &operator<<=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] <<= s.x;
      static_cast<T *>(this)[I1] <<= s.y;
      static_cast<T *>(this)[I2] <<= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator<<=(const T &s)
    {
      static_cast<const T *>(&s)[I0] <<= s;
      static_cast<const T *>(&s)[I1] <<= s;
      static_cast<const T *>(&s)[I2] <<= s;
      return *this;
    }

    writable_type &operator>>=(const swizzle3<I0, I1, I2, T> &s)
    {
      const T va = static_cast<const T *>(&s)[I0];
      const T vb = static_cast<const T *>(&s)[I1];
      const T vc = static_cast<const T *>(&s)[I2];
      static_cast<T *>(this)[I0] >>= va;
      static_cast<T *>(this)[I1] >>= vb;
      static_cast<T *>(this)[I2] >>= vc;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator>>=(const swizzle3<J0, J1, J2, T> &s)
    {
      const T va2 = static_cast<const T *>(&s)[J0];
      const T vb2 = static_cast<const T *>(&s)[J1];
      const T vc2 = static_cast<const T *>(&s)[J2];
      static_cast<T *>(this)[I0] >>= va2;
      static_cast<T *>(this)[I1] >>= vb2;
      static_cast<T *>(this)[I2] >>= vc2;
      return *this;
    }

    writable_type &operator>>=(const vec<3, T> &s)
    {
      static_cast<T *>(this)[I0] >>= s.x;
      static_cast<T *>(this)[I1] >>= s.y;
      static_cast<T *>(this)[I2] >>= s.z;
      return *this;
    }

    template <int J0, int J1, int J2>
    writable_type &operator>>=(const T &s)
    {
      static_cast<const T *>(&s)[I0] >>= s;
      static_cast<const T *>(&s)[I1] >>= s;
      static_cast<const T *>(&s)[I2] >>= s;
      return *this;
    }

  }; //! class swizzle3

  //////////////////////
  //! OUTPUT OPERATOR //
  //////////////////////

  template <int I0, int I1, int I2, typename T>
  std::ostream &operator<<(std::ostream &os, const swizzle3<I0, I1, I2, T> &s)
  {
    os << vec<3, T>(s[I0], s[I1], s[I2]);
    return os;
  }

  ///////////////////////
  //! BINARY OPERATORS //
  ///////////////////////

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator*(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x * s[I0], v.y * s[I1], v.z * s[I2], v.z * s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator/(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x / s[I0], v.y / s[I1], v.z / s[I2], v.z / s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator+(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x + s[I0], v.y + s[I1], v.z + s[I2], v.z + s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator-(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x - s[I0], v.y - s[I1], v.z - s[I2], v.z - s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator|(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x | s[I0], v.y | s[I1], v.z | s[I2], v.z | s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator&(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x & s[I0], v.y & s[I1], v.z & s[I2], v.z & s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator^(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x ^ s[I0], v.y ^ s[I1], v.z ^ s[I2], v.z ^ s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator%(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x % s[I0], v.y % s[I1], v.z % s[I2], v.z % s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator<<(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x << s[I0], v.y << s[I1], v.z << s[I2], v.z << s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> operator>>(const vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    return vec<3, T>(v.x >> s[I0], v.y >> s[I1], v.z >> s[I2], v.z >> s[I2]);
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator*=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x *= s[I0];
    v.y *= s[I1];
    v.z *= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator/=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x /= s[I0];
    v.y /= s[I1];
    v.z /= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator+=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x += s[I0];
    v.y += s[I1];
    v.z += s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator-=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x -= s[I0];
    v.y -= s[I1];
    v.z -= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator|=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x |= s[I0];
    v.y |= s[I1];
    v.z |= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator&=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x &= s[I0];
    v.y &= s[I1];
    v.z &= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator^=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x ^= s[I0];
    v.y ^= s[I1];
    v.z ^= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator%=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x %= s[I0];
    v.y %= s[I1];
    v.z %= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
  static vec<3, T> &operator<<=(vec<3, T> &v, const swizzle3<I0, I1, I2, T> &s)
  {
    v.x <<= s[I0];
    v.y <<= s[I1];
    v.z <<= s[I2];
    return v;
  }

  template <int I0, int I1, int I2, typename T>
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
