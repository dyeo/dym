#ifndef _GMTK_ANGLE_H_
#define _GMTK_ANGLE_H_

//

#include "util.h"

//

#define DEG2RAD 0.0174532925199432957692369076848861271344
#define RAD2DEG 57.2957795130823208767981548141051703324

namespace GMTK_NAMESPACE
{////

	template<typename T = float>
	struct Angle
	{////

		enum AngleUnits
		{
			Radians = 0,
			Degrees
		};

		inline Angle(T amount, AngleUnits units)
		{
			switch (units)
			{
			case Radians:
				ang = amount;
				break;
			case Degrees:
				ang = amount * static_cast<T>(DEG2RAD);
				break;
			}
		};

		inline Angle()
		{
			ang = static_cast<T>(0);
		}

		template<typename U>
		//! Type conversion copy constructor
		inline Angle(const Angle<U>& a)
		{
			ang = static_cast<T>(a.ang);
		}

		inline float degrees() const
		{
			return ang * static_cast<T>(RAD2DEG);
		}

		inline float radians() const
		{
			return ang;
		}

	private:

		T ang = 0;

	};////

	//! Creates an angle in degrees
	inline Angle<> degrees(float deg)
	{
		return Angle<float>(deg, Angle<float>::Degrees);
	}

	//! Creates an angle in radians
	inline Angle<> radians(float rad)
	{
		return Angle<float>(rad, Angle<float>::Radians);
	}

	//! Default angle specifier
	typedef Angle<float> angf;

	typedef Angle<double> angd;
	typedef Angle<int> angi;
	
	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	inline std::ostream& operator<<(std::ostream& os, const Angle<> &a)
	{
		os << a.degrees() << "deg";
		return os;
	}

}////

//

inline GMTK_NAMESPACE::Angle<> operator "" _deg(unsigned long long value)
{
	return GMTK_NAMESPACE::degrees(static_cast<float>(value));
}

inline GMTK_NAMESPACE::Angle<> operator "" _deg(long double value)
{
	return GMTK_NAMESPACE::degrees(static_cast<float>(value));
}

inline GMTK_NAMESPACE::Angle<> operator "" _rad(unsigned long long value)
{
	return GMTK_NAMESPACE::radians(static_cast<float>(value));
}

inline GMTK_NAMESPACE::Angle<> operator "" _rad(long double value)
{
	return GMTK_NAMESPACE::radians(static_cast<float>(value));
}

//

#endif