#ifndef _GMTK_QUAT_H_
#define _GMTK_QUAT_H_

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

#define GMTK_QUAT_SLERP_THRESHOLD 0.99951171875

//

namespace GMTK_NAMESPACE
{////

	//! Quaternion class
	template< typename T = float >
	struct Quat
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
		Quat()
			: w(static_cast<T>(0)), x(static_cast<T>(0)), y(static_cast<T>(0)), z(static_cast<T>(0))
		{}

		//! initialize quat with one scalar (s) and three complex (i, j, k)
		Quat(const T &s, const T &i, const T &j, const T &k)
			: w(s), x(i), y(j), z(k)
		{}

		//! initialize quat with one scalar (s) and a vec3 of complex (ijk)
		Quat(const T &s, const vec<3, T> &ijk)
			: w(s), x(ijk.data[0]), y(ijk.data[1]), z(ijk.data[2])
		{}

		//! initialize quat with vec4 of complex(3)scalar(1)
		//! NOTE: w becomes first element!
		Quat(const vec<4, T> &xyzw)
			: w(xyzw.data[3]), x(xyzw.data[0]), y(xyzw.data[1]), z(xyzw.data[2])
		{}

		//! Copy constructor
		template< typename U >
		Quat(const Quat<U> &q)
			: w(static_cast<T>(q.data[0])), x(static_cast<T>(q.data[1])), y(static_cast<T>(q.data[2])), z(static_cast<T>(q.data[3]))
		{}

		//! Array initializer
		explicit Quat(const T *a)
			: w(a[0]), x(a[1]), y(a[2]), z(a[3])
		{}

		//! Initializer list constructor
		Quat(std::initializer_list<T> l)
			: w(*(l.begin())), x(*(l.begin() + 1)), y(*(l.begin() + 2)), z(*(l.begin() + 3))
		{}

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! returns reference to an element of the given quat, in the order w,x,y,z
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
		Quat<T> operator +(const Quat<T> &q) const
		{
			return Quat<T>(w + q.w, x + q.x, y + q.y, z + q.z);
		}

		//! Quaternion subtraction
		Quat<T> operator -(const Quat<T> &q) const
		{
			return Quat<T>(w - q.w, x - q.x, y - q.y, z - q.z);
		}

		//! Quaternion multiplication
		Quat<T> operator*(const Quat &q)
		{
			Quat<T> res;
			res.x = x * q.w + y * q.z - z * q.y + w * q.x;
			res.y = -x * q.z + y * q.w + z * q.x + w * q.y;
			res.z = x * q.y - y * q.x + z * q.w + w * q.z;
			res.w = -x * q.x - y * q.y - z * q.z + w * q.w;
			return res;
		}

		//! Quaternion division (multiplication by conjugate)
		Quat<T> operator/(const Quat &q)
		{
			Quat<T> res;
			res = (*this) * conjugate(q);
			return res;
		}

		//! Quaternion reference addition
		Quat<T> &operator += (const Quat<T> &q)
		{
			w += q.w; x += q.x; y += q.y; z += q.z; return *this;
		}

		//! Quaternion reference subtraction
		Quat<T> &operator -= (const Quat<T> &q)
		{
			w -= q.w; x -= q.x; y -= q.y; z -= q.z; return *this;
		}

		//! Quaternion reference multiplication
		vec<3, T> operator*(const vec<3, T> &v)
		{
			Quat<T> vp = (*this) * Quat<T>(0, v.x, v.y, v.z) * conj(*this);
			return vec<3, T>(vp.x, vp.y, vp.z);
		}

		//! Quaternion reference division (multiplication by conjugate)
		vec<3, T> operator/(const vec<3, T> &v)
		{
			Quat<T> vp = (*this) * Quat<T>(0, -v.x, -v.y, -v.z) * conj(*this);
			return vec<3, T>(vp.x, vp.y, vp.z);
		}

		//! Quaternion scalar addition
		Quat<T> operator + (const T &v) const
		{
			return Quat<T>(w + v, x + v, y + v, z + v);
		}

		//! Quaternion scalar subtraction
		Quat<T> operator - (const T &v) const
		{
			return Quat<T>(w - v, x - v, y - v, z - v);
		}

		//!  Quaternion scalar multiplication
		Quat<T> operator * (const T &v) const
		{
			return Quat<T>(w * v, x * v, y * v, z * v);
		}

		//! Quaternion scalar division
		Quat<T> operator / (const T &v) const
		{
			return Quat<T>(w / v, x / v, y / v, z / v);
		}

		//! Quaternion scalar reference addition
		Quat<T> &operator += (const T &v)
		{
			w += v; x += v; y += v; z += v; return *this;
		}

		//! Quaternion scalar reference subtraction
		Quat<T> &operator -= (const T &v)
		{
			w -= v; x -= v; y -= v; z -= v; return *this;
		}

		//! Quaternion scalar reference multiplication
		Quat<T> &operator *= (const T &v)
		{
			w *= v; x *= v; y *= v; z *= v; return *this;
		}

		//! Quaternion scalar reference division
		Quat<T> &operator /= (const T &v)
		{
			w /= v; x /= v; y /= v; z /= v; return *this;
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
		static Quat<T> axisangle(const vec<3, T> &axis, const ang<T> &angle)
		{
			float a2 = angle.radians() / 2;
			float sa2 = sin(a2);
			Quat<T> q;
			q.w = cos(a2);
			q.x = axis.x * sa2;
			q.y = axis.y * sa2;
			q.z = axis.z * sa2;
			return q;
		}

		// MISC. STATIC FUNCTIONS

		static Quat<T> identity()
		{
			return Quat<T>(1, 0, 0, 0);
		}

	};

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	//! Quaternion output operator
	template <typename T>
	static std::ostream &operator<<(std::ostream &os, const Quat<T> &q)
	{
		os << "< " << std::showpos << q.w << ' ' << q.x << "i " << q.y << "j " << q.z << std::noshowpos << "k >";
		return os;
	}

	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////

	//! Returns length squared of quaternion
	template <typename T>
	static T lengthsq(const Quat<T> &v)
	{
		return sq(v.w) + sq(v.x) + sq(v.y) + sq(v.z);
	}

	//! Returns length of quaternion, or sqrt(lengthsq)
	template <typename T>
	static T length(const Quat<T> &v)
	{
		return sqrt(sq(v.w) + sq(v.x) + sq(v.y) + sq(v.z));
	}

	template <typename T>
	static T norm(const Quat<T> &q)
	{
		return length(q);
	}

	//! Normalizes quaternion so it is a unit quaternion
	template <typename T>
	static Quat<T> normalize(const Quat<T> &q)
	{
		return q / length(q);
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T>
	static Quat<T> conjugate(const Quat<T> &q)
	{
		return Quat<T>(-q.x,-q.y,-q.z,q.w);
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T>
	static Quat<T> conj(const Quat<T> &q)
	{
		return conjugate(q);
	}

	//! Returns the quaternion inverse
	template <typename T>
	static Quat<T> inverse(const Quat<T> &q)
	{
		return q / lengthsq(q);
	}

	//! Calculates the dot or hamiltonian product of two quaternions
	template <typename T>
	static T dot(const Quat<T> &l, const Quat<T> &r)
	{
		return (l.w * r.w) + (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	//! Calculates the spherical linear interpolation of two quaternions using a t-value
	template <typename T>
	static Quat<T> slerp(const Quat<T> &l, const Quat<T> &r, const double &t)
	{
		T dotProduct = dot(l, r);

		if (dotProduct > GMTK_QUAT_SLERP_THRESHOLD) return normalize(l + t * (r - l));

		dot = clamp(dot, -1, 1);

		const double tht0 = acos(dot);
		const double tht = tht0 * t;

		Quat<T> v = r - l * dot;
		v = normalize(v);

		return l * cos(tht) + v * sin(tht);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef Quat<float> quat, quatf;
	typedef Quat<double> quatd;
	typedef Quat<int> quati;
	typedef Quat<unsigned> quatui;

}////

//

#undef GMTK_QUAT_SLERP_THRESHOLD

//

#pragma warning(pop)

//

#endif//_GMTK_QUAT_H_