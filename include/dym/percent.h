#ifndef _DYM_PERCENT_H_
#define _DYM_PERCENT_H_

//

#include "util.h"
#include <ostream>

//

namespace dym
{////

	template<typename T = float>
	struct perc
	{////

		///////////////////
		//! DATA MEMBERS //
		///////////////////

		enum PercentUnits
		{
			Value = 0,
			Percent = 1
		};


		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		perc()
		{
			_val = static_cast<T>(0);
		}

		~perc() = default;
		
		//! Copy constructor
		perc(const perc<T> &a)
		{
			_val = a._val;
		}

		//! Type conversion copy constructor
		template<typename U>
		perc(const perc<U> &a)
		{
			_val = static_cast<T>(a._val);
		}

		//! Selectable constructor
		perc(T amount, PercentUnits units)
		{
			switch (units)
			{
				case Value:
				_val = amount;
				break;
				case Percent:
				_val = amount * static_cast<T>(0.01f);
				break;
			}
		};

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Unary negative percentage
		perc<T> operator-()
		{
			return perc<T>(-_val);
		}

		//! Percent addition
		perc<T> operator+(const perc<T> &a)
		{
			return perc<T>(_val + a._val);
		}

		//! Percent subtraction
		perc<T> operator-(const perc<T> &a)
		{
			return perc<T>(_val - a._val);
		}

		//! Percent multiplication
		perc<T> operator*(const T &s)
		{
			return perc<T>(_val * s);
		}

		//! Percent division
		perc<T> operator/(const T &s)
		{
			return perc<T>(_val - s);
		}

		//! Percent reference addition
		perc<T> &operator+=(const perc<T> &a)
		{
			_val += a._val;
			return *this;
		}

		//! Percent reference subtraction
		perc<T> &operator-=(const perc<T> &a)
		{
			_val -= a._val;
			return *this;
		}

		//! Percent reference multiplication
		perc<T> &operator*=(const T &s)
		{
			_val *= s;
			return *this;
		}

		//! Percent reference division
		perc<T> &operator/=(const T &s)
		{
			_val /= s;
			return *this;
		}

		///////////////////////
		//! ACCESS FUNCTIONS //
		///////////////////////

		T percent() const
		{
			return _val * static_cast<T>(100.0f);
		}

		T value() const
		{
			return _val;
		}

	private:

		//! Private inline constructor.
		perc(const T &v) : _val(v)
		{}

		T _val = 0;

	};////

	//////////////////////////
	//! GENERATOR FUNCTIONS //
	//////////////////////////

	//! Creates an percentage from a value (0..1)
	inline perc<> value(float val)
	{
		return perc<float>(val, perc<float>::Value);
	}

	//! Creates an percentage from a percentage (0..100)
	inline perc<> percent(float per)
	{
		return perc<float>(per, perc<float>::Percent);
	}

	///////////////////////
	//! TYPE DEFINITIONS //
	///////////////////////

	typedef perc<float> percf;

	typedef perc<double> percd;

	typedef perc<int> perci;

	//////////////////////
	//! MISC. OPERATORS //
	//////////////////////

	inline std::ostream &operator<<(std::ostream &os, const perc<> &a)
	{
		os << a.percent() << "%";
		return os;
	}

}////

///////////////
//! LITERALS //
///////////////

#ifndef DYM_DISABLE_LITERALS

inline dym::perc<> operator "" _per(unsigned long long value)
{
	return dym::percent(static_cast<float>(value));
}

inline dym::perc<> operator "" _per(long double value)
{
	return dym::percent(static_cast<float>(value));
}

inline dym::perc<> operator "" _val(unsigned long long value)
{
	return dym::value(static_cast<float>(value));
}

inline dym::perc<> operator "" _val(long double value)
{
	return dym::value(static_cast<float>(value));
}

#endif

//

#endif