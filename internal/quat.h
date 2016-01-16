#ifndef _GMTK_QUAT_H_
#define _GMTK_QUAT_H_

//

#include "..\util.h"
#include <math.h>
#include <ostream>

//

//! Unrolls a component-wise vector manipulation for generic implementation
#define GMTK_QUAT_LOOP(oper) GMTK_UNROLL_LOOP(i,4,oper)

//

#define GMTK_QUAT_OPERATOR(oper) { Quat<T> res; GMTK_QUAT_LOOP(res[i] = oper); return res; }

//

#define GMTK_QUAT_REF_OPERATOR(oper) { GMTK_QUAT_LOOP(oper); return *this; }

//

namespace GMTK_NAMESPACE
{
	//! quaternion class
	template< typename T = float >
	struct Quat
	{////

		// DATA

		union
		{
			struct { T data[4]; };
			struct { T w, x, y, z; };
		};

		// CONSTRUCTORS

		// ! default constructor
		inline Quat()
		{
			w = 0;
			x = 0;
			y = 0;
			z = 0;
		}

		// ! initialize quat with one scalar (w) and three complex (i, j, k)
		inline Quat(const T &s, const T &i, const T &j, const T &k)
		{
			w = s;
			x = i;
			y = j;
			z = k;
		}

		// ! initialize quat with one scalar and a vec3 of complex
		inline Quat(const T &s, const vec<T, 3> &ijk)
		{
			w = s;
			x = ijk.data[0];
			y = ijk.data[1];
			z = ijk.data[2];
		}

		// ! initialize quat with vec4 of complex(3)scalar(1)
		// ! NOTE: w becomes first element!
		inline Quat(const vec<T, 4> &xyzw)
		{
			w = xyzw.data[3];
			x = xyzw.data[0];
			y = xyzw.data[1];
			z = xyzw.data[2];
		}

		// GENERATORS

		// ! creates a rotation quaternion rotated about an axis according to a specified angle
		inline static Quat<T> axisangle(const vec<T, 3> &axis, const Angle<T> &angle)
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

	};////

	template <typename T>
	inline std::ostream& operator<<(std::ostream& os, const Quat<T>& q)
	{
		os << "< " << std::showpos << q.w << ' ' << q.x << "i " << q.y << "j " << q.z << std::noshowpos << "k >";
		return os;
	}

	typedef Quat<float> quat;
	typedef Quat<double> quatd;
	typedef Quat<int> quati;
	typedef Quat<unsigned> quatui;

}

#endif//_GMTK_QUAT_H_