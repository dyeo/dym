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
		inline ang()
		{
			_rads = static_cast<T>(0);
		}

		//! Copy constructor
		inline ang(const ang<T>& a)
		{
			_rads = a._rads;
		}

		//! Type conversion copy constructor
		template<typename U>
		inline ang(const ang<U>& a)
		{
			_rads = static_cast<T>(a._rads);
		}

		//! Selectable constructor
		inline ang(T amount, AngleUnits units)
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
		inline ang<T> operator-() {
			return ang<T>(-_rads);
		}
		
		//! Angle addition
		inline ang<T> operator+(const ang<T>& a) {
			return ang<T>(_rads + a.ang);
		}

		//! Angle subtraction
		inline ang<T> operator-(const ang<T>& a) {
			return ang<T>(_rads - a.ang);
		}

		//! Angle multiplication
		inline ang<T> operator*(const T& s) {
			return ang<T>(_rads * s);
		}

		//! Angle division
		inline ang<T> operator/(const T& s) {
			return ang<T>(_rads - s);
		}

		//! Angle reference addition
		inline ang<T>& operator+=(const ang<T>& a) {
			_rads += a.ang;
			return *this;
		}

		//! Angle reference subtraction
		inline ang<T>& operator-=(const ang<T>& a) {
			_rads -= a.ang;
			return *this;
		}

		//! Angle reference multiplication
		inline ang<T>& operator*=(const T& s) {
			_rads *= s;
			return *this;
		}

		//! Angle reference division
		inline ang<T>& operator/=(const T& s) {
			_rads /= s;
			return *this;
		}

		///////////////////////
		//! ACCESS FUNCTIONS //
		///////////////////////

		inline T degrees() const
		{
			return _rads * static_cast<T>(RAD2DEG);
		}

		inline T radians() const
		{
			return _rads;
		}

	private:

		//! Private inline constructor.
		inline ang(const T& v) : _rads(v) { }

		T _rads = 0;

	};////

	//////////////////////////
	//! GENERATOR FUNCTIONS //
	//////////////////////////

	//! Creates an angle in degrees
	inline ang<> degrees(float deg)
	{
		return ang<float>(deg, ang<float>::Degrees);
	}

	//! Creates an angle in radians
	inline ang<> radians(float rad)
	{
		return ang<float>(rad, ang<float>::Radians);
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

	inline std::ostream& operator<<(std::ostream& os, const ang<> &a)
	{
		os << a.degrees() << "deg";
		return os;
	}

}////

///////////////
//! LITERALS //
///////////////

#ifndef GMTK_DISABLE_LITERALS

inline GMTK_NAMESPACE::ang<> operator "" _deg(unsigned long long value)
{
	return GMTK_NAMESPACE::degrees(static_cast<float>(value));
}

inline GMTK_NAMESPACE::ang<> operator "" _deg(long double value)
{
	return GMTK_NAMESPACE::degrees(static_cast<float>(value));
}

inline GMTK_NAMESPACE::ang<> operator "" _rad(unsigned long long value)
{
	return GMTK_NAMESPACE::radians(static_cast<float>(value));
}

inline GMTK_NAMESPACE::ang<> operator "" _rad(long double value)
{
	return GMTK_NAMESPACE::radians(static_cast<float>(value));
}

#endif

//

#endif