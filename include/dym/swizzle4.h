#ifndef _DYM_SWIZZLE4_H_
#define _DYM_SWIZZLE4_H_

#include "util.h"
#include "vec.h"

//

namespace dym
{////

	template<int I0, int I1, int I2, int I3, typename T>
	class swizzle4
	{
	public:

		swizzle4() = default;
		~swizzle4() = default;
		
		static constexpr bool is_writable = (I0 != I1 && I0 != I2 && I0 != I3 && I1 != I2 && I1 != I3 && I2 != I3);
		typedef typename std::conditional<is_writable, swizzle4<I0, I1, I2, I3, T>, struct duplicate_components_swizzle>::type writable_type;
		
		T &operator[](const size_t i)
		{
			return static_cast<T *const>(this)[i];
		}

		const T &operator[](const size_t i) const
		{
			return static_cast<T *const>(this)[i];
		}

		vec<4, T> operator - () const
		{
			return vec<4, T>(-static_cast<const T *>(this)[I0], -static_cast<const T *>(this)[I1], -static_cast<const T *>(this)[I2], -static_cast<const T *>(this)[I3]);
		}

		vec<4, T> operator ~ () const
		{
			return vec<4, T>(~static_cast<const T *>(this)[I0], ~static_cast<const T *>(this)[I1], ~static_cast<const T *>(this)[I2], ~static_cast<const T *>(this)[I3]);
		}

		writable_type &operator = (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] = va;
			static_cast<T *>(this)[I1] = vb;
			static_cast<T *>(this)[I2] = vc;
			static_cast<T *>(this)[I3] = vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator = (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] = va2;
			static_cast<T *>(this)[I1] = vb2;
			static_cast<T *>(this)[I2] = vc2;
			static_cast<T *>(this)[I3] = vd2;
			return *this;
		}

		writable_type &operator = (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] = s.x;
			static_cast<T *>(this)[I1] = s.y;
			static_cast<T *>(this)[I2] = s.z;
			static_cast<T *>(this)[I3] = s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator = (const T &s)
		{
			static_cast<const T *>(&s)[I0] = s;
			static_cast<const T *>(&s)[I1] = s;
			static_cast<const T *>(&s)[I2] = s;
			static_cast<const T *>(&s)[I3] = s;
			return *this;
		}

		vec<4, T> operator * (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] * static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] * static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] * static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] * static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator * (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] * static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] * static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] * static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] * static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator * (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] * v, static_cast<const T *>(this)[I1] * v, static_cast<const T *>(this)[I2] * v, static_cast<const T *>(this)[I3] * v);
		}

		friend vec<4, T> operator * (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l * static_cast<const T *>(r)[I0], l * static_cast<const T *>(r)[I1], l * static_cast<const T *>(r)[I2], l * static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator / (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] / static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] / static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] / static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] / static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator / (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] / static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] / static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] / static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] / static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator / (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] / v, static_cast<const T *>(this)[I1] / v, static_cast<const T *>(this)[I2] / v, static_cast<const T *>(this)[I3] / v);
		}

		friend vec<4, T> operator / (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l / static_cast<const T *>(r)[I0], l / static_cast<const T *>(r)[I1], l / static_cast<const T *>(r)[I2], l / static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator + (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] + static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] + static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] + static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] + static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator + (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] + static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] + static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] + static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] + static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator + (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] + v, static_cast<const T *>(this)[I1] + v, static_cast<const T *>(this)[I2] + v, static_cast<const T *>(this)[I3] + v);
		}

		friend vec<4, T> operator + (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l + static_cast<const T *>(r)[I0], l + static_cast<const T *>(r)[I1], l + static_cast<const T *>(r)[I2], l + static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator - (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] - static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] - static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] - static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] - static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator - (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] - static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] - static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] - static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] - static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator - (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] - v, static_cast<const T *>(this)[I1] - v, static_cast<const T *>(this)[I2] - v, static_cast<const T *>(this)[I3] - v);
		}

		friend vec<4, T> operator - (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l - static_cast<const T *>(r)[I0], l - static_cast<const T *>(r)[I1], l - static_cast<const T *>(r)[I2], l - static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator | (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] | static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] | static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] | static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] | static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator | (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] | static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] | static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] | static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] | static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator | (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] | v, static_cast<const T *>(this)[I1] | v, static_cast<const T *>(this)[I2] | v, static_cast<const T *>(this)[I3] | v);
		}

		friend vec<4, T> operator | (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l | static_cast<const T *>(r)[I0], l | static_cast<const T *>(r)[I1], l | static_cast<const T *>(r)[I2], l | static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator & (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] & static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] & static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] & static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] & static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator & (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] & static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] & static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] & static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] & static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator & (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] & v, static_cast<const T *>(this)[I1] & v, static_cast<const T *>(this)[I2] & v, static_cast<const T *>(this)[I3] & v);
		}

		friend vec<4, T> operator & (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l & static_cast<const T *>(r)[I0], l & static_cast<const T *>(r)[I1], l & static_cast<const T *>(r)[I2], l & static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator ^ (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] ^ static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] ^ static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] ^ static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] ^ static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator ^ (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] ^ static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] ^ static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] ^ static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] ^ static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator ^ (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] ^ v, static_cast<const T *>(this)[I1] ^ v, static_cast<const T *>(this)[I2] ^ v, static_cast<const T *>(this)[I3] ^ v);
		}

		friend vec<4, T> operator ^ (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l ^ static_cast<const T *>(r)[I0], l ^ static_cast<const T *>(r)[I1], l ^ static_cast<const T *>(r)[I2], l ^ static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator % (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] % static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] % static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] % static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] % static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator % (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] % static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] % static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] % static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] % static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator % (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] % v, static_cast<const T *>(this)[I1] % v, static_cast<const T *>(this)[I2] % v, static_cast<const T *>(this)[I3] % v);
		}

		friend vec<4, T> operator % (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l % static_cast<const T *>(r)[I0], l % static_cast<const T *>(r)[I1], l % static_cast<const T *>(r)[I2], l % static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator << (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] << static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] << static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] << static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] << static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator << (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] << static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] << static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] << static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] << static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator << (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] << v, static_cast<const T *>(this)[I1] << v, static_cast<const T *>(this)[I2] << v, static_cast<const T *>(this)[I3] << v);
		}

		friend vec<4, T> operator << (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l << static_cast<const T *>(r)[I0], l << static_cast<const T *>(r)[I1], l << static_cast<const T *>(r)[I2], l << static_cast<const T *>(r)[I3]);
		}

		vec<4, T> operator >> (const swizzle4<I0, I1, I2, I3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] >> static_cast<const T *>(&s)[I0], static_cast<const T *>(this)[I1] >> static_cast<const T *>(&s)[I1], static_cast<const T *>(this)[I2] >> static_cast<const T *>(&s)[I2], static_cast<const T *>(this)[I3] >> static_cast<const T *>(&s)[I3]);
		}

		template<int J0, int J1, int J2, int J3>
		vec<4, T> operator >> (const swizzle4<J0, J1, J2, J3, T> &s) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] >> static_cast<const T *>(&s)[J0], static_cast<const T *>(this)[I1] >> static_cast<const T *>(&s)[J1], static_cast<const T *>(this)[I2] >> static_cast<const T *>(&s)[J2], static_cast<const T *>(this)[I3] >> static_cast<const T *>(&s)[J3]);
		}

		vec<4, T> operator >> (const T &v) const
		{
			return vec<4, T>(static_cast<const T *>(this)[I0] >> v, static_cast<const T *>(this)[I1] >> v, static_cast<const T *>(this)[I2] >> v, static_cast<const T *>(this)[I3] >> v);
		}

		friend vec<4, T> operator >> (const T &l, const swizzle4<I0, I1, I2, I3, T> &r)
		{
			return vec<4, T>(l >> static_cast<const T *>(r)[I0], l >> static_cast<const T *>(r)[I1], l >> static_cast<const T *>(r)[I2], l >> static_cast<const T *>(r)[I3]);
		}

		writable_type &operator *= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] *= va;
			static_cast<T *>(this)[I1] *= vb;
			static_cast<T *>(this)[I2] *= vc;
			static_cast<T *>(this)[I3] *= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator *= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] *= va2;
			static_cast<T *>(this)[I1] *= vb2;
			static_cast<T *>(this)[I2] *= vc2;
			static_cast<T *>(this)[I3] *= vd2;
			return *this;
		}

		writable_type &operator *= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] *= s.x;
			static_cast<T *>(this)[I1] *= s.y;
			static_cast<T *>(this)[I2] *= s.z;
			static_cast<T *>(this)[I3] *= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator *= (const T &s)
		{
			static_cast<const T *>(&s)[I0] *= s;
			static_cast<const T *>(&s)[I1] *= s;
			static_cast<const T *>(&s)[I2] *= s;
			static_cast<const T *>(&s)[I3] *= s;
			return *this;
		}

		writable_type &operator /= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] /= va;
			static_cast<T *>(this)[I1] /= vb;
			static_cast<T *>(this)[I2] /= vc;
			static_cast<T *>(this)[I3] /= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator /= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] /= va2;
			static_cast<T *>(this)[I1] /= vb2;
			static_cast<T *>(this)[I2] /= vc2;
			static_cast<T *>(this)[I3] /= vd2;
			return *this;
		}

		writable_type &operator /= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] /= s.x;
			static_cast<T *>(this)[I1] /= s.y;
			static_cast<T *>(this)[I2] /= s.z;
			static_cast<T *>(this)[I3] /= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator /= (const T &s)
		{
			static_cast<const T *>(&s)[I0] /= s;
			static_cast<const T *>(&s)[I1] /= s;
			static_cast<const T *>(&s)[I2] /= s;
			static_cast<const T *>(&s)[I3] /= s;
			return *this;
		}

		writable_type &operator += (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] += va;
			static_cast<T *>(this)[I1] += vb;
			static_cast<T *>(this)[I2] += vc;
			static_cast<T *>(this)[I3] += vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator += (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] += va2;
			static_cast<T *>(this)[I1] += vb2;
			static_cast<T *>(this)[I2] += vc2;
			static_cast<T *>(this)[I3] += vd2;
			return *this;
		}

		writable_type &operator += (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] += s.x;
			static_cast<T *>(this)[I1] += s.y;
			static_cast<T *>(this)[I2] += s.z;
			static_cast<T *>(this)[I3] += s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator += (const T &s)
		{
			static_cast<const T *>(&s)[I0] += s;
			static_cast<const T *>(&s)[I1] += s;
			static_cast<const T *>(&s)[I2] += s;
			static_cast<const T *>(&s)[I3] += s;
			return *this;
		}

		writable_type &operator -= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] -= va;
			static_cast<T *>(this)[I1] -= vb;
			static_cast<T *>(this)[I2] -= vc;
			static_cast<T *>(this)[I3] -= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator -= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] -= va2;
			static_cast<T *>(this)[I1] -= vb2;
			static_cast<T *>(this)[I2] -= vc2;
			static_cast<T *>(this)[I3] -= vd2;
			return *this;
		}

		writable_type &operator -= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] -= s.x;
			static_cast<T *>(this)[I1] -= s.y;
			static_cast<T *>(this)[I2] -= s.z;
			static_cast<T *>(this)[I3] -= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator -= (const T &s)
		{
			static_cast<const T *>(&s)[I0] -= s;
			static_cast<const T *>(&s)[I1] -= s;
			static_cast<const T *>(&s)[I2] -= s;
			static_cast<const T *>(&s)[I3] -= s;
			return *this;
		}

		writable_type &operator |= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] |= va;
			static_cast<T *>(this)[I1] |= vb;
			static_cast<T *>(this)[I2] |= vc;
			static_cast<T *>(this)[I3] |= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator |= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] |= va2;
			static_cast<T *>(this)[I1] |= vb2;
			static_cast<T *>(this)[I2] |= vc2;
			static_cast<T *>(this)[I3] |= vd2;
			return *this;
		}

		writable_type &operator |= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] |= s.x;
			static_cast<T *>(this)[I1] |= s.y;
			static_cast<T *>(this)[I2] |= s.z;
			static_cast<T *>(this)[I3] |= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator |= (const T &s)
		{
			static_cast<const T *>(&s)[I0] |= s;
			static_cast<const T *>(&s)[I1] |= s;
			static_cast<const T *>(&s)[I2] |= s;
			static_cast<const T *>(&s)[I3] |= s;
			return *this;
		}

		writable_type &operator &= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] &= va;
			static_cast<T *>(this)[I1] &= vb;
			static_cast<T *>(this)[I2] &= vc;
			static_cast<T *>(this)[I3] &= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator &= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] &= va2;
			static_cast<T *>(this)[I1] &= vb2;
			static_cast<T *>(this)[I2] &= vc2;
			static_cast<T *>(this)[I3] &= vd2;
			return *this;
		}

		writable_type &operator &= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] &= s.x;
			static_cast<T *>(this)[I1] &= s.y;
			static_cast<T *>(this)[I2] &= s.z;
			static_cast<T *>(this)[I3] &= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator &= (const T &s)
		{
			static_cast<const T *>(&s)[I0] &= s;
			static_cast<const T *>(&s)[I1] &= s;
			static_cast<const T *>(&s)[I2] &= s;
			static_cast<const T *>(&s)[I3] &= s;
			return *this;
		}

		writable_type &operator ^= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] ^= va;
			static_cast<T *>(this)[I1] ^= vb;
			static_cast<T *>(this)[I2] ^= vc;
			static_cast<T *>(this)[I3] ^= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator ^= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] ^= va2;
			static_cast<T *>(this)[I1] ^= vb2;
			static_cast<T *>(this)[I2] ^= vc2;
			static_cast<T *>(this)[I3] ^= vd2;
			return *this;
		}

		writable_type &operator ^= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] ^= s.x;
			static_cast<T *>(this)[I1] ^= s.y;
			static_cast<T *>(this)[I2] ^= s.z;
			static_cast<T *>(this)[I3] ^= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator ^= (const T &s)
		{
			static_cast<const T *>(&s)[I0] ^= s;
			static_cast<const T *>(&s)[I1] ^= s;
			static_cast<const T *>(&s)[I2] ^= s;
			static_cast<const T *>(&s)[I3] ^= s;
			return *this;
		}

		writable_type &operator %= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] %= va;
			static_cast<T *>(this)[I1] %= vb;
			static_cast<T *>(this)[I2] %= vc;
			static_cast<T *>(this)[I3] %= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator %= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] %= va2;
			static_cast<T *>(this)[I1] %= vb2;
			static_cast<T *>(this)[I2] %= vc2;
			static_cast<T *>(this)[I3] %= vd2;
			return *this;
		}

		writable_type &operator %= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] %= s.x;
			static_cast<T *>(this)[I1] %= s.y;
			static_cast<T *>(this)[I2] %= s.z;
			static_cast<T *>(this)[I3] %= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator %= (const T &s)
		{
			static_cast<const T *>(&s)[I0] %= s;
			static_cast<const T *>(&s)[I1] %= s;
			static_cast<const T *>(&s)[I2] %= s;
			static_cast<const T *>(&s)[I3] %= s;
			return *this;
		}

		writable_type &operator <<= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] <<= va;
			static_cast<T *>(this)[I1] <<= vb;
			static_cast<T *>(this)[I2] <<= vc;
			static_cast<T *>(this)[I3] <<= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator <<= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] <<= va2;
			static_cast<T *>(this)[I1] <<= vb2;
			static_cast<T *>(this)[I2] <<= vc2;
			static_cast<T *>(this)[I3] <<= vd2;
			return *this;
		}

		writable_type &operator <<= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] <<= s.x;
			static_cast<T *>(this)[I1] <<= s.y;
			static_cast<T *>(this)[I2] <<= s.z;
			static_cast<T *>(this)[I3] <<= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator <<= (const T &s)
		{
			static_cast<const T *>(&s)[I0] <<= s;
			static_cast<const T *>(&s)[I1] <<= s;
			static_cast<const T *>(&s)[I2] <<= s;
			static_cast<const T *>(&s)[I3] <<= s;
			return *this;
		}

		writable_type &operator >>= (const swizzle4<I0, I1, I2, I3, T> &s)
		{
			const T va = static_cast<const T *>(&s)[I0];
			const T vb = static_cast<const T *>(&s)[I1];
			const T vc = static_cast<const T *>(&s)[I2];
			const T vd = static_cast<const T *>(&s)[I3];
			static_cast<T *>(this)[I0] >>= va;
			static_cast<T *>(this)[I1] >>= vb;
			static_cast<T *>(this)[I2] >>= vc;
			static_cast<T *>(this)[I3] >>= vd;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator >>= (const swizzle4<J0, J1, J2, J3, T> &s)
		{
			const T va2 = static_cast<const T *>(&s)[J0];
			const T vb2 = static_cast<const T *>(&s)[J1];
			const T vc2 = static_cast<const T *>(&s)[J2];
			const T vd2 = static_cast<const T *>(&s)[J3];
			static_cast<T *>(this)[I0] >>= va2;
			static_cast<T *>(this)[I1] >>= vb2;
			static_cast<T *>(this)[I2] >>= vc2;
			static_cast<T *>(this)[I3] >>= vd2;
			return *this;
		}

		writable_type &operator >>= (const vec<4, T> &s)
		{
			static_cast<T *>(this)[I0] >>= s.x;
			static_cast<T *>(this)[I1] >>= s.y;
			static_cast<T *>(this)[I2] >>= s.z;
			static_cast<T *>(this)[I3] >>= s.w;
			return *this;
		}

		template<int J0, int J1, int J2, int J3>
		writable_type &operator >>= (const T &s)
		{
			static_cast<const T *>(&s)[I0] >>= s;
			static_cast<const T *>(&s)[I1] >>= s;
			static_cast<const T *>(&s)[I2] >>= s;
			static_cast<const T *>(&s)[I3] >>= s;
			return *this;
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

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator * (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x * s[I0], v.y * s[I1], v.z * s[I2], v.w * s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator / (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x / s[I0], v.y / s[I1], v.z / s[I2], v.w / s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator + (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x + s[I0], v.y + s[I1], v.z + s[I2], v.w + s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator - (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x - s[I0], v.y - s[I1], v.z - s[I2], v.w - s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator | (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x | s[I0], v.y | s[I1], v.z | s[I2], v.w | s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator & (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x & s[I0], v.y & s[I1], v.z & s[I2], v.w & s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator ^ (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x ^ s[I0], v.y ^ s[I1], v.z ^ s[I2], v.w ^ s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator % (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x % s[I0], v.y % s[I1], v.z % s[I2], v.w % s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator << (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x << s[I0], v.y << s[I1], v.z << s[I2], v.w << s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> operator >> (const vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		return vec<4, T>(v.x >> s[I0], v.y >> s[I1], v.z >> s[I2], v.w >> s[I3]);
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator *= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x *= s[I0];
		v.y *= s[I1];
		v.z *= s[I2];
		v.w *= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator /= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x /= s[I0];
		v.y /= s[I1];
		v.z /= s[I2];
		v.w /= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator += (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x += s[I0];
		v.y += s[I1];
		v.z += s[I2];
		v.w += s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator -= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x -= s[I0];
		v.y -= s[I1];
		v.z -= s[I2];
		v.w -= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator |= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x |= s[I0];
		v.y |= s[I1];
		v.z |= s[I2];
		v.w |= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator &= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x &= s[I0];
		v.y &= s[I1];
		v.z &= s[I2];
		v.w &= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator ^= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x ^= s[I0];
		v.y ^= s[I1];
		v.z ^= s[I2];
		v.w ^= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator %= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x %= s[I0];
		v.y %= s[I1];
		v.z %= s[I2];
		v.w %= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator <<= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x <<= s[I0];
		v.y <<= s[I1];
		v.z <<= s[I2];
		v.w <<= s[I3];
		return v;
	}

	template<int I0, int I1, int I2, int I3, typename T>
	static vec<4, T> &operator >>= (vec<4, T> &v, const swizzle4<I0, I1, I2, I3, T> &s)
	{
		v.x >>= s[I0];
		v.y >>= s[I1];
		v.z >>= s[I2];
		v.w >>= s[I3];
		return v;
	}

}////

//

#endif //_DYM_SWIZZLE4_H_
