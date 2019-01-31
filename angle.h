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

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		enum AngleUnits
		{
			Radians = 0,
			Degrees = 1
		};

		inline Angle(T amount, AngleUnits units)
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

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		inline Angle()
		{
			_rads = static_cast<T>(0);
		}

		//! Copy constructor
		inline Angle(const Angle<T>& a)
		{
			_rads = a._rads;
		}

		//! Type conversion copy constructor
		template<typename U>
		inline Angle(const Angle<U>& a)
		{
			_rads = static_cast<T>(a._rads);
		}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Unary negative angle
		inline Angle<T> operator-() {
			return Angle<T>(-_rads);
		}
		
		//! Angle addition
		inline Angle<T> operator+(const Angle<T>& a) {
			return Angle<T>(_rads + a.ang);
		}

		//! Angle subtraction
		inline Angle<T> operator-(const Angle<T>& a) {
			return Angle<T>(_rads - a.ang);
		}

		//! Angle multiplication
		inline Angle<T> operator*(const T& s) {
			return Angle<T>(_rads * s);
		}

		//! Angle division
		inline Angle<T> operator/(const T& s) {
			return Angle<T>(_rads - s);
		}

		//! Angle reference addition
		inline Angle<T>& operator+=(const Angle<T>& a) {
			_rads += a.ang;
			return *this;
		}

		//! Angle reference subtraction
		inline Angle<T>& operator-=(const Angle<T>& a) {
			_rads -= a.ang;
			return *this;
		}

		//! Angle reference multiplication
		inline Angle<T>& operator*=(const T& s) {
			_rads *= s;
			return *this;
		}

		//! Angle reference division
		inline Angle<T>& operator/=(const T& s) {
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

		//! Efficient private inline constructor.
		inline Angle(const T& v)
		{
			_rads = v;
		}

		T _rads = 0;

	};////

	//////////////////////////
	//! GENERATOR FUNCTIONS //
	//////////////////////////

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

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef Angle<float> ang, angf;

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