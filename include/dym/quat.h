#ifndef _DYM_QUAT_H_
#define _DYM_QUAT_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "util.h"
#include "vec3.h"
#include "mat3.h"
#include <cmath>
#include <ostream>

//

#define DYM_QUAT_SLERP_THRESHOLD 0.99951171875

//

namespace dym
{////

	//! Quaternion class
	template< typename T = float >
	struct quat
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct
			{
				T data[4];
			};
			struct
			{
				T w, i, j, k;
			};
			struct
			{
				T w, x, y, z;
			};
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! default constructor
		quat()
			: w(static_cast<T>(0)), i(static_cast<T>(0)), j(static_cast<T>(0)), k(static_cast<T>(0))
		{}

		//! initialize quat with one scalar (s) and three complex (i, j, k)
		quat(const T &s, const T &i, const T &j, const T &k)
			: w(s), i(i), j(j), k(k)
		{}

		//! initialize quat with one scalar (s) and a vec3 of complex (ijk)
		quat(const T &s, const vec<3, T> &ijk)
			: w(s), i(ijk.data[0]), j(ijk.data[1]), k(ijk.data[2])
		{}

		//! initialize quat with vec4 of complex(3)scalar(1)
		//! NOTE: w becomes first element!
		quat(const vec<4, T> &xyzw)
			: w(xyzw.data[3]), i(xyzw.data[0]), j(xyzw.data[1]), k(xyzw.data[2])
		{}

		//! Copy constructor
		template< typename U >
		quat(const quat<U> &q)
			: w(static_cast<T>(q.data[0])), i(static_cast<T>(q.data[1])), j(static_cast<T>(q.data[2])), k(static_cast<T>(q.data[3]))
		{}

		//! Array initializer
		explicit quat(const T *a)
			: w(a[0]), i(a[1]), j(a[2]), k(a[3])
		{}

		//! Initializer list constructor
		quat(std::initializer_list<T> l)
			: w(*(l.begin())), i(*(l.begin() + 1)), j(*(l.begin() + 2)), k(*(l.begin() + 3))
		{}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! returns reference to an element of the given quat, in the order w,i,j,k
		T &operator[](const std::size_t i)
		{
			return data[i];
		}

		const T &operator[](const std::size_t i) const
		{
			return data[i];
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Quaternion addition
		quat<T> operator +(const quat<T> &q) const
		{
			return quat<T>(w + q.w, i + q.i, j + q.j, k + q.k);
		}

		//! Quaternion subtraction
		quat<T> operator -(const quat<T> &q) const
		{
			return quat<T>(w - q.w, i - q.i, j - q.j, k - q.k);
		}

		//! Quaternion multiplication
		quat<T> operator*(const quat &q)
		{
			quat<T> res;
			res.i = i * q.w + j * q.k - k * q.j + w * q.i;
			res.j = -i * q.k + j * q.w + k * q.i + w * q.j;
			res.k = i * q.j - j * q.i + k * q.w + w * q.k;
			res.w = -i * q.i - j * q.j - k * q.k + w * q.w;
			return res;
		}

		//! Quaternion division (multiplication by conjugate)
		quat<T> operator/(const quat &q)
		{
			quat<T> res;
			res = (*this) * conjugate(q);
			return res;
		}

		//! Quaternion reference addition
		quat<T> &operator += (const quat<T> &q)
		{
			w += q.w; i += q.i; j += q.j; k += q.k; return *this;
		}

		//! Quaternion reference subtraction
		quat<T> &operator -= (const quat<T> &q)
		{
			w -= q.w; i -= q.i; j -= q.j; k -= q.k; return *this;
		}

		//! Quaternion reference multiplication
		vec<3, T> operator*(const vec<3, T> &v)
		{
			quat<T> vp = (*this) * quat<T>(0, v.i, v.j, v.k) * conj(*this);
			return vec<3, T>(vp.i, vp.j, vp.k);
		}

		//! Quaternion reference division (multiplication by conjugate)
		vec<3, T> operator/(const vec<3, T> &v)
		{
			quat<T> vp = (*this) * quat<T>(0, -v.i, -v.j, -v.k) * conj(*this);
			return vec<3, T>(vp.i, vp.j, vp.k);
		}

		//! Quaternion scalar addition
		quat<T> operator + (const T &v) const
		{
			return quat<T>(w + v, i + v, j + v, k + v);
		}

		//! Quaternion scalar subtraction
		quat<T> operator - (const T &v) const
		{
			return quat<T>(w - v, i - v, j - v, k - v);
		}

		//!  Quaternion scalar multiplication
		quat<T> operator * (const T &v) const
		{
			return quat<T>(w * v, i * v, j * v, k * v);
		}

		//! Quaternion scalar division
		quat<T> operator / (const T &v) const
		{
			return quat<T>(w / v, i / v, j / v, k / v);
		}

		//! Quaternion scalar reference addition
		quat<T> &operator += (const T &v)
		{
			w += v; i += v; j += v; k += v; return *this;
		}

		//! Quaternion scalar reference subtraction
		quat<T> &operator -= (const T &v)
		{
			w -= v; i -= v; j -= v; k -= v; return *this;
		}

		//! Quaternion scalar reference multiplication
		quat<T> &operator *= (const T &v)
		{
			w *= v; i *= v; j *= v; k *= v; return *this;
		}

		//! Quaternion scalar reference division
		quat<T> &operator /= (const T &v)
		{
			w /= v; i /= v; j /= v; k /= v; return *this;
		}

		///////////////////////
		//! TYPE CONVERSIONS //
		///////////////////////

		//! Returns the quaternion represented as a 3-dimension column-order rotation matrix
		mat<3, 3, T> tomat()
		{
			return mat<3, 3, T>
			{
				static_cast<T>(1) - static_cast<T>(2) * (sq(k) + sq(j)),
					static_cast<T>(2) *(i *j + k * w),
					static_cast<T>(2) *(i *k - j * w),
					//
					static_cast<T>(2) *(i *j - k * w),
					static_cast<T>(1) - static_cast<T>(2) * (sq(i) + sq(k)),
					static_cast<T>(2) *(j *k + i * w),
					//
					static_cast<T>(2) *(j *w + i * k),
					static_cast<T>(2) *(j *k - i * w),
					static_cast<T>(1) - static_cast<T>(2) * (sq(j) + sq(i))
			};
		}

		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! Creates a rotation quaternion rotated about an axis according to a specified angle
		static quat<T> axisangle(const vec<3, T> &axis, const ang<T> &angle)
		{
			float a2 = angle.radians() / 2;
			float sa2 = sin(a2);
			quat<T> q;
			q.w = cos(a2);
			q.i = axis.i * sa2;
			q.j = axis.j * sa2;
			q.k = axis.k * sa2;
			return q;
		}

		// MISC. STATIC FUNCTIONS

		static quat<T> identity()
		{
			return quat<T>(1, 0, 0, 0);
		}

	};

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	//! Quaternion output operator
	template <typename T = float>
	static std::ostream &operator<<(std::ostream &os, const quat<T> &q)
	{
		os << "< " << std::showpos << q.w << ' ' << q.i << "i " << q.j << "j " << q.k << std::noshowpos << "k >";
		return os;
	}

	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Returns length squared of quaternion
	template <typename T = float>
	static T lengthsq(const quat<T> &v)
	{
		return sq(v.w) + sq(v.i) + sq(v.j) + sq(v.k);
	}

	//! Returns length of quaternion, or sqrt(lengthsq)
	template <typename T = float>
	static T length(const quat<T> &v)
	{
		return sqrt(sq(v.w) + sq(v.i) + sq(v.j) + sq(v.k));
	}

	template <typename T = float>
	static T norm(const quat<T> &q)
	{
		return length(q);
	}

	//! Normalizes quaternion so it is a unit quaternion
	template <typename T = float>
	static quat<T> normalize(const quat<T> &q)
	{
		return q / length(q);
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T = float>
	static quat<T> conjugate(const quat<T> &q)
	{
		return quat<T>(-q.i, -q.j, -q.k, q.w);
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T = float>
	static quat<T> conj(const quat<T> &q)
	{
		return conjugate(q);
	}

	//! Returns the quaternion inverse
	template <typename T = float>
	static quat<T> inverse(const quat<T> &q)
	{
		return q / lengthsq(q);
	}

	//! Calculates the dot or hamiltonian product of two quaternions
	template <typename T = float>
	static T dot(const quat<T> &l, const quat<T> &r)
	{
		return (l.w * r.w) + (l.i * r.i) + (l.j * r.j) + (l.k * r.k);
	}

	//! Calculates the spherical linear interpolation of two quaternions using a t-value
	template <typename T = float>
	static quat<T> slerp(const quat<T> &l, const quat<T> &r, const double &t)
	{
		T dotProduct = dot(l, r);

		if (dotProduct > DYM_QUAT_SLERP_THRESHOLD) return normalize(l + t * (r - l));

		dot = clamp(dot, -1, 1);

		const double tht0 = acos(dot);
		const double tht = tht0 * t;

		quat<T> v = r - l * dot;
		v = normalize(v);

		return l * cos(tht) + v * sin(tht);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef quat<float> quatf;
	typedef quat<double> quatd;
	typedef quat<int> quati;
	typedef quat<unsigned> quatui;

}////

//

#undef DYM_QUAT_SLERP_THRESHOLD

//

#pragma warning(pop)

//

#endif//_DYM_QUAT_H_