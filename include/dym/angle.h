#ifndef _DYM_ANGLE_H_
#define _DYM_ANGLE_H_

//

#include "util.h"

#include <ostream>

//

#define DEG2RAD 0.0174532925199432957692369076848861271344
#define RAD2DEG 57.2957795130823208767981548141051703324

namespace dym
{////

	template<typename T = float>
	struct ang
	{////

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		enum AngleUnits
		{
			Radians = 0,
			Degrees = 1
		};


		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		ang()
		{
			_rads = static_cast<T>(0);
		}

		~ang() = default;

		//! Copy constructor
		ang(const ang<T> &a)
		{
			_rads = a._rads;
		}

		//! Type conversion copy constructor
		template<typename U>
		ang(const ang<U> &a)
		{
			_rads = static_cast<T>(a._rads);
		}

		//! Selectable constructor
		ang(T amount, AngleUnits units)
		{
			switch (units)
			{
				case Radians:
				_rads = amount;
				break;
				case Degrees:
				_rads = amount * static_cast<T>(DEG2RAD);
				break;
			}
		};

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Unary negative angle
		ang<T> operator-()
		{
			return ang<T>(-_rads);
		}

		//! Angle addition
		ang<T> operator+(const ang<T> &a)
		{
			return ang<T>(_rads + a._rads);
		}

		//! Angle subtraction
		ang<T> operator-(const ang<T> &a)
		{
			return ang<T>(_rads - a._rads);
		}

		//! Angle multiplication
		ang<T> operator*(const T &s)
		{
			return ang<T>(_rads * s);
		}

		//! Angle division
		ang<T> operator/(const T &s)
		{
			return ang<T>(_rads - s);
		}

		//! Angle reference addition
		ang<T> &operator+=(const ang<T> &a)
		{
			_rads += a._rads;
			return *this;
		}

		//! Angle reference subtraction
		ang<T> &operator-=(const ang<T> &a)
		{
			_rads -= a._rads;
			return *this;
		}

		//! Angle reference multiplication
		ang<T> &operator*=(const T &s)
		{
			_rads *= s;
			return *this;
		}

		//! Angle reference division
		ang<T> &operator/=(const T &s)
		{
			_rads /= s;
			return *this;
		}

		///////////////////////
		//! ACCESS FUNCTIONS //
		///////////////////////

		T degrees() const
		{
			return _rads * static_cast<T>(RAD2DEG);
		}

		T radians() const
		{
			return _rads;
		}

	private:

		//! Private constructor.
		ang(const T &v) : _rads(v)
		{}

		T _rads = 0;

	};////

	//////////////////////////
	//! GENERATOR FUNCTIONS //
	//////////////////////////

	//! Creates an angle in degrees
	template<typename T = float>
	static ang<T> degrees(const T &deg)
	{
		return ang<float>(deg, ang<T>::Degrees);
	}

	//! Creates an angle in radians
	template<typename T = float>
	static ang<> radians(const float &rad)
	{
		return ang<float>(rad, ang<T>::Radians);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef ang<float> angf;

	typedef ang<double> angd;

	typedef ang<int> angi;

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	template<typename T = float>
	static std::ostream &operator<<(std::ostream &os, const ang<T> &a)
	{
		os << a.degrees() << "deg";
		return os;
	}

}////

///////////////
//! LITERALS //
///////////////

#ifndef DYM_DISABLE_LITERALS

inline dym::ang<> operator "" _deg(unsigned long long value)
{
	return dym::degrees(static_cast<float>(value));
}

inline dym::ang<> operator "" _deg(long double value)
{
	return dym::degrees(static_cast<float>(value));
}

inline dym::ang<> operator "" _rad(unsigned long long value)
{
	return dym::radians(static_cast<float>(value));
}

inline dym::ang<> operator "" _rad(long double value)
{
	return dym::radians(static_cast<float>(value));
}

#endif

//

#endif