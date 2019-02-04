#ifndef _GMTK_QUAT_H_
#define _GMTK_QUAT_H_

//

#pragma warning(push)
#pragma warning(disable:4456; disable:4127)

//

#include "..\util.h"
#include <math.h>
#include <ostream>

//

#define GMTK_QUAT_LOOP(oper) GMTK_STATIC_LOOP(i,4,oper)

#define GMTK_QUAT_INIT(a, b, c, d) : w( a ), x( b ), y( c ), z( d ) { }

#define GMTK_QUAT_QUAT_OP(op) \
	inline Quat<T> operator op(const Quat<T> &q) const \
	{ Quat<T> res; GMTK_QUAT_LOOP(res.data[i] = data[i] op q.data[i]); return res; }

#define GMTK_QUAT_SCL_OP(op) \
	inline Quat<T> operator op (const T& v) const \
	{ Quat<T> res; GMTK_QUAT_LOOP(res.data[i] = data[i] op v); return res; }

#define GMTK_QUAT_QUAT_ROP(op) \
	inline Quat<T>& operator op (const Quat<T>&  q) \
	{ GMTK_QUAT_LOOP(data[i] op v.data[i]); return *this; }

#define GMTK_QUAT_SCL_ROP(op) \
	inline Quat<T>& operator op (const T& v) \
	{ GMTK_QUAT_LOOP(data[i] op v); return *this; }

//

#define GMTK_QUAT_SLERP_THRESHOLD 0.99951171875

//

namespace GMTK_NAMESPACE
{////

	//! quaternion class
	template< typename T = float >
	struct Quat
	{
		///////////////////
		//! DATA MEMBERS //
		///////////////////

		union
		{
			struct { T data[4]; };
			struct { T w, x, y, z; };
			struct { T w, i, j, k; };
		};

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! default constructor
		inline Quat()
			GMTK_QUAT_INIT(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0))

		//! initialize quat with one scalar (s) and three complex (i, j, k)
		inline Quat(const T &s, const T &i, const T &j, const T &k)
			GMTK_QUAT_INIT(s, i, j, k)

		//! initialize quat with one scalar (s) and a vec3 of complex (ijk)
		inline Quat(const T &s, const vec<3, T> &ijk)
			GMTK_QUAT_INIT(s, ijk.data[0], ijk.data[1], ijk.data[2])

		//! initialize quat with vec4 of complex(3)scalar(1)
		//! NOTE: w becomes first element!
		inline Quat(const vec<4, T> &xyzw)
			GMTK_QUAT_INIT(xyzw.data[3], xyzw.data[0], xyzw.data[1], xyzw.data[2])

		//! Copy constructor
		template< typename U >
		inline Quat(const Quat<U> &q)
			GMTK_QUAT_INIT( static_cast<T>(q.data[0]), static_cast<T>(q.data[1]), static_cast<T>(q.data[2]), static_cast<T>(q.data[3]) ) 
					
		//! Array initializer
		explicit inline Quat(const T* a)
			GMTK_QUAT_INIT(a[0], a[1], a[2], a[3])

		//! Initializer list constructor
		inline Quat(std::initializer_list<T> l)
			GMTK_QUAT_INIT(*(l.begin()), *(l.begin() + 1), *(l.begin() + 2), *(l.begin() + 3))

		///////////////////////
		//! ACCESS OPERATORS //
		///////////////////////

		//! returns reference to an element of the given quat, in the order w,x,y,z
		inline T& operator[](const int i) {
			return data[i];
		}

		inline const T& operator[](const int i) const {
			return data[i];
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//!
		GMTK_QUAT_QUAT_OP(+)

		//!
		GMTK_QUAT_QUAT_OP(-)

		//!
		inline Quat<T> operator*(const Quat &q) {
			Quat<T> res;
			res.x = x * q.w + y * q.z - z * q.y + w * q.x;
			res.y = -x * q.z + y * q.w + z * q.x + w * q.y;
			res.z = x * q.y - y * q.x + z * q.w + w * q.z;
			res.w = -x * q.x - y * q.y - z * q.z + w * q.w;
			return res;
		}

		//!
		inline Quat<T> operator/(const Quat &q) {
			Quat<T> res;
			res = (*this) * conjugate(q);
			return res;
		}
		
		//!
		GMTK_QUAT_QUAT_ROP(+=)

		//!
		GMTK_QUAT_QUAT_ROP(-=)

		//!
		inline vec<3, T> operator*(const vec<3, T> &v) {
			Quat<T> vp = (*this) * Quat<T>(0, v.x, v.y, v.z) * conj(*this);
			return vec<3, T>(vp.x, vp.y, vp.z);
		}
		
		//!
		inline vec<3, T> operator/(const vec<3, T> &v) {
			Quat<T> vp = (*this) * Quat<T>(0, -v.x, -v.y, -v.z) * conj(*this);
			return vec<3, T>(vp.x, vp.y, vp.z);
		}

		//!
		GMTK_QUAT_SCL_OP(+)

		//!
		GMTK_QUAT_SCL_OP(-)

		//!
		GMTK_QUAT_SCL_OP(*)

		//!
		GMTK_QUAT_SCL_OP(/)

		//!
		GMTK_QUAT_SCL_ROP(+=)

		//!
		GMTK_QUAT_SCL_ROP(-=)

		//!
		GMTK_QUAT_SCL_ROP(*=)

		//!
		GMTK_QUAT_SCL_ROP(/=)

		///////////////////////
		//! TYPE CONVERSIONS //
		///////////////////////

		//!
		inline mat<3, 3, T> tomat()
		{
			return mat<3, 3, T>
			{
				static_cast<T>(1) - static_cast<T>(2) * (sq(k) + sq(j)), 
				static_cast<T>(2) * (i * j + k * w),
				static_cast<T>(2) * (i * k - j * w),
					//
				static_cast<T>(2) * (i * j - k * w),
				static_cast<T>(1) - static_cast<T>(2) * (sq(i) + sq(k)),
				static_cast<T>(2) * (j * k + i * w),
					//
				static_cast<T>(2) * (j * w + i * k),
				static_cast<T>(2) * (j * k - i * w), 
				static_cast<T>(1) - static_cast<T>(2) * (sq(j) + sq(i))
			};
		}
		
		//////////////////////////
		//! GENERATOR FUNCTIONS //
		//////////////////////////

		//! creates a rotation quaternion rotated about an axis according to a specified angle
		inline static Quat<T> axisangle(const vec<3, T> &axis, const ang<T> &angle)
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

		inline static Quat<T> identity()
		{
			return Quat<T>(1, 0, 0, 0);
		}
				
	}; //! struct quat

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	//! Quaternion output operator
	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Quat<T>& q)
	{
		os << "< " << std::showpos << q.w << ' ' << q.x << "i " << q.y << "j " << q.z << std::noshowpos << "k >";
		return os;
	}

	/////////////////////
	//! FREE FUNCTIONS //
	/////////////////////
	
	//! Returns length squared of quaternion
	template <typename T>
	inline T lengthsq(const Quat<T>& v)
	{
		T res = 0;
		GMTK_QUAT_LOOP(res += sq(v.data[i]));
		return res;
	}

	//! Returns length of quaternion, or sqrt(lengthsq)
	template <typename T>
	inline T length(const Quat<T>& v)
	{
		T res = 0;
		GMTK_QUAT_LOOP(res += sq(v.data[i]));
		return sqrt(res);
	}

	template <typename T>
	inline T norm(const Quat<T> &q)
	{
		return length(q);
	}

	//! Normalizes quaternion so it is a unit quaternion
	template <typename T>
	inline Quat<T> normalize(const Quat<T> &q)
	{
		return q / length(q);
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T>
	inline Quat<T> conjugate(const Quat<T> &q)
	{
		Quat<T> res;
		res.x = -q.x;
		res.y = -q.y;
		res.z = -q.z;
		res.w =  q.w;
		return res;
	}

	//! Returns the quaternion conjugate. The "negative" of the quaternion.
	template <typename T>
	inline Quat<T> conj(const Quat<T> &q)
	{
		return conjugate(q);
	}

	//! Returns the quaternion inverse
	template <typename T>
	inline Quat<T> inverse(const Quat<T> &q)
	{
		return q / lengthsq(q);
	}

	//! Calculates the dot or hamiltonian product of two quaternions
	template <typename T>
	inline T dot(const Quat<T> &l, const Quat<T> &r)
	{
		return (l.w * r.w) + (l.x * r.x) + (l.y * r.y) + (l.z * r.z);
	}

	//! Calculates the spherical linear interpolation of two quaternions using a t-value
	template <typename T>
	inline Quat<T> slerp(const Quat<T> &l, const Quat<T> &r, const double &t)
	{
		T dotProduct = dot(l, r);

		if (dotProduct > GMTK_QUAT_SLERP_THRESHOLD) return normalize(l + t*(r - l));

		dot = clamp(dot, -1, 1);

		double tht0 = acos(dot);
		double tht = tht0*t;

		Quaternion v = r - l*dot;
		v = normalize(v);

		return l*cos(tht) + v*sin(tht);
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

#undef GMTK_QUAT_LOOP

#undef GMTK_QUAT_INIT
#undef GMTK_QUAT_QUAT_OP
#undef GMTK_QUAT_SCL_OP
#undef GMTK_QUAT_QUAT_ROP
#undef GMTK_QUAT_SCL_ROP

#undef GMTK_QUAT_SLERP_THRESHOLD

//

#pragma warning(pop)

//

#endif//_GMTK_QUAT_H_