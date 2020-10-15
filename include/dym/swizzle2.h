#ifndef _DYM_SWIZZLE2_H_
#define _DYM_SWIZZLE2_H_

#include "util.h"
#include "vec.h"

//

namespace dym
{////

	template<int I0, int I1, typename T>
	class swizzle2
	{
	public:

		static constexpr bool is_writable = (I0 != I1);

		typedef typename std::conditional<is_writable, swizzle2<I0, I1, T>, struct duplicate_components_swizzle>::type writable_type;

		T &operator[](const std::size_t i)
		{
			return static_cast<T *const>(this)[i];
		}

		const T &operator[](const std::size_t i) const
		{
			return static_cast<T *const>(this)[i];
		}

		vec<2, T> operator - () const
		{
			return vec<2, T>(-(static_cast<const T *>(this))[I0], -(static_cast<const T *>(this))[I1]);
		}
		vec<2, T> operator ~ () const
		{
			return vec<2, T>(~(static_cast<const T *>(this))[I0], ~(static_cast<const T *>(this))[I1]);
		}

		writable_type &operator = (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] = va;
			static_cast<T *>(this)[I1] = vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator = (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] = va2;
			static_cast<T *>(this)[I1] = vb2;
			return *this;
		}

		writable_type &operator = (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] = s.x;
			static_cast<T *>(this)[I1] = s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator = (const T &s)
		{
			static_cast<const T *>(&s)[I0] = s;
			static_cast<const T *>(&s)[I1] = s;
			return *this;
		}

		vec<2, T> operator * (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] * static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] * static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator * (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] * static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] * static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator * (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] * v, static_cast<const T *>(this)[I1] * v);
		}

		friend vec<2, T> operator * (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l * static_cast<const T *>(r)[I0], l * static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator / (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] / static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] / static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator / (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] / static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] / static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator / (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] / v, static_cast<const T *>(this)[I1] / v);
		}

		friend vec<2, T> operator / (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l / static_cast<const T *>(r)[I0], l / static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator + (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] + static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] + static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator + (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] + static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] + static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator + (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] + v, static_cast<const T *>(this)[I1] + v);
		}

		friend vec<2, T> operator + (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l + static_cast<const T *>(r)[I0], l + static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator - (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] - static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] - static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator - (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] - static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] - static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator - (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] - v, static_cast<const T *>(this)[I1] - v);
		}

		friend vec<2, T> operator - (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l - static_cast<const T *>(r)[I0], l - static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator | (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] | static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] | static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator | (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] | static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] | static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator | (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] | v, static_cast<const T *>(this)[I1] | v);
		}

		friend vec<2, T> operator | (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l | static_cast<const T *>(r)[I0], l | static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator & (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] & static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] & static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator & (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] & static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] & static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator & (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] & v, static_cast<const T *>(this)[I1] & v);
		}

		friend vec<2, T> operator & (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l & static_cast<const T *>(r)[I0], l & static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator ^ (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] ^ static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] ^ static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator ^ (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] ^ static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] ^ static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator ^ (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] ^ v, static_cast<const T *>(this)[I1] ^ v);
		}

		friend vec<2, T> operator ^ (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l ^ static_cast<const T *>(r)[I0], l ^ static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator % (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] % static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] % static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator % (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] % static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] % static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator % (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] % v, static_cast<const T *>(this)[I1] % v);
		}

		friend vec<2, T> operator % (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l % static_cast<const T *>(r)[I0], l % static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator << (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] << static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] << static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator << (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] << static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] << static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator << (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] << v, static_cast<const T *>(this)[I1] << v);
		}

		friend vec<2, T> operator << (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l << static_cast<const T *>(r)[I0], l << static_cast<const T *>(r)[I1]);
		}

		vec<2, T> operator >> (const swizzle2<I0, I1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] >> static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] >> static_cast<const T *>(&s)[I1]);
		}

		template<int J0, int J1>
		vec<2, T> operator >> (const swizzle2<J0, J1, T> &s) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] >> static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] >> static_cast<const T *>(&s)[J1]);
		}

		vec<2, T> operator >> (const T &v) const
		{
			return vec<2, T>(static_cast<const T *>(this)[I0] >> v, static_cast<const T *>(this)[I1] >> v);
		}

		friend vec<2, T> operator >> (const T &l, const swizzle2<I0, I1, T> &r)
		{
			return vec<2, T>(l >> static_cast<const T *>(r)[I0], l >> static_cast<const T *>(r)[I1]);
		}

		writable_type &operator *= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] *= va;
			static_cast<T *>(this)[I1] *= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator *= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] *= va2;
			static_cast<T *>(this)[I1] *= vb2;
			return *this;
		}

		writable_type &operator *= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] *= s.x;
			static_cast<T *>(this)[I1] *= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator *= (const T &s)
		{
			static_cast<const T *>(&s)[I0] *= s;
			static_cast<const T *>(&s)[I1] *= s;
			return *this;
		}

		writable_type &operator /= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] /= va;
			static_cast<T *>(this)[I1] /= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator /= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] /= va2;
			static_cast<T *>(this)[I1] /= vb2;
			return *this;
		}

		writable_type &operator /= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] /= s.x;
			static_cast<T *>(this)[I1] /= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator /= (const T &s)
		{
			static_cast<const T *>(&s)[I0] /= s;
			static_cast<const T *>(&s)[I1] /= s;
			return *this;
		}

		writable_type &operator += (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] += va;
			static_cast<T *>(this)[I1] += vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator += (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] += va2;
			static_cast<T *>(this)[I1] += vb2;
			return *this;
		}

		writable_type &operator += (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] += s.x;
			static_cast<T *>(this)[I1] += s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator += (const T &s)
		{
			static_cast<const T *>(&s)[I0] += s;
			static_cast<const T *>(&s)[I1] += s;
			return *this;
		}

		writable_type &operator -= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] -= va;
			static_cast<T *>(this)[I1] -= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator -= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] -= va2;
			static_cast<T *>(this)[I1] -= vb2;
			return *this;
		}

		writable_type &operator -= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] -= s.x;
			static_cast<T *>(this)[I1] -= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator -= (const T &s)
		{
			static_cast<const T *>(&s)[I0] -= s;
			static_cast<const T *>(&s)[I1] -= s;
			return *this;
		}

		writable_type &operator |= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] |= va;
			static_cast<T *>(this)[I1] |= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator |= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] |= va2;
			static_cast<T *>(this)[I1] |= vb2;
			return *this;
		}

		writable_type &operator |= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] |= s.x;
			static_cast<T *>(this)[I1] |= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator |= (const T &s)
		{
			static_cast<const T *>(&s)[I0] |= s;
			static_cast<const T *>(&s)[I1] |= s;
			return *this;
		}

		writable_type &operator &= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] &= va;
			static_cast<T *>(this)[I1] &= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator &= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] &= va2;
			static_cast<T *>(this)[I1] &= vb2;
			return *this;
		}

		writable_type &operator &= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] &= s.x;
			static_cast<T *>(this)[I1] &= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator &= (const T &s)
		{
			static_cast<const T *>(&s)[I0] &= s;
			static_cast<const T *>(&s)[I1] &= s;
			return *this;
		}

		writable_type &operator ^= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] ^= va;
			static_cast<T *>(this)[I1] ^= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator ^= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] ^= va2;
			static_cast<T *>(this)[I1] ^= vb2;
			return *this;
		}

		writable_type &operator ^= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] ^= s.x;
			static_cast<T *>(this)[I1] ^= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator ^= (const T &s)
		{
			static_cast<const T *>(&s)[I0] ^= s;
			static_cast<const T *>(&s)[I1] ^= s;
			return *this;
		}

		writable_type &operator %= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] %= va;
			static_cast<T *>(this)[I1] %= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator %= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] %= va2;
			static_cast<T *>(this)[I1] %= vb2;
			return *this;
		}

		writable_type &operator %= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] %= s.x;
			static_cast<T *>(this)[I1] %= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator %= (const T &s)
		{
			static_cast<const T *>(&s)[I0] %= s;
			static_cast<const T *>(&s)[I1] %= s;
			return *this;
		}

		writable_type &operator <<= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] <<= va;
			static_cast<T *>(this)[I1] <<= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator <<= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] <<= va2;
			static_cast<T *>(this)[I1] <<= vb2;
			return *this;
		}

		writable_type &operator <<= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] <<= s.x;
			static_cast<T *>(this)[I1] <<= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator <<= (const T &s)
		{
			static_cast<const T *>(&s)[I0] <<= s;
			static_cast<const T *>(&s)[I1] <<= s;
			return *this;
		}

		writable_type &operator >>= (const swizzle2<I0, I1, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			static_cast<T *>(this)[I0] >>= va;
			static_cast<T *>(this)[I1] >>= vb;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator >>= (const swizzle2<J0, J1, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			static_cast<T *>(this)[I0] >>= va2;
			static_cast<T *>(this)[I1] >>= vb2;
			return *this;
		}

		writable_type &operator >>= (const vec<2, T> &s)
		{
			static_cast<T *>(this)[I0] >>= s.x;
			static_cast<T *>(this)[I1] >>= s.y;
			return *this;
		}

		template<int J0, int J1>
		writable_type &operator >>= (const T &s)
		{
			static_cast<const T *>(&s)[I0] >>= s;
			static_cast<const T *>(&s)[I1] >>= s;
			return *this;
		}

	}; //! class swizzle2

	//////////////////////
	//! OUTPUT OPERATOR //
	//////////////////////

	template <int I0, int I1, typename T>
	std::ostream &operator<<(std::ostream &os, const swizzle2<I0, I1, T> &s)
	{
		os << vec<2, T>(s[I0], s[I1]);
		return os;
	}

	///////////////////////
	//! BINARY OPERATORS //
	///////////////////////

	template<int I0, int I1, typename T>
	static vec<2, T> operator * (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x * s[I0], v.y * s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator / (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x / s[I0], v.y / s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator + (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x + s[I0], v.y + s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator - (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x - s[I0], v.y - s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator | (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x | s[I0], v.y | s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator & (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x & s[I0], v.y & s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator ^ (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x ^ s[I0], v.y ^ s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator % (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x % s[I0], v.y % s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator << (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x << s[I0], v.y << s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> operator >> (const vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		return vec<2, T>(v.x >> s[I0], v.y >> s[I1]);
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator *= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x *= s[I0];
		v.y *= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator /= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x /= s[I0];
		v.y /= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator += (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x += s[I0];
		v.y += s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator -= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x -= s[I0];
		v.y -= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator |= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x |= s[I0];
		v.y |= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator &= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x &= s[I0];
		v.y &= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator ^= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x ^= s[I0];
		v.y ^= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator %= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x %= s[I0];
		v.y %= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator <<= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x <<= s[I0];
		v.y <<= s[I1];
		return v;
	}

	template<int I0, int I1, typename T>
	static vec<2, T> &operator >>= (vec<2, T> &v, const swizzle2<I0, I1, T> &s)
	{
		v.x >>= s[I0];
		v.y >>= s[I1];
		return v;
	}

}////

//

#endif //_DYM_SWIZZLE2_H_
