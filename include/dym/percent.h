#ifndef _DYM_PERCENT_H_
#define _DYM_PERCENT_H_

//

#include <ostream>

//

namespace dym
{////

	template<typename T = float>
	struct perc
	{////

		///////////////////
		//! CONSTRUCTORS //
		///////////////////

		//! Default constructor
		constexpr perc()
		{
			_val = static_cast<T>(0);
		}

		~perc() = default;
		
		//! Copy constructor
		constexpr perc(const perc<T> &a)
		{
			_val = a._val;
		}

		//! Type conversion copy constructor
		template<typename U>
		constexpr perc(const perc<U> &a)
		{
			_val = static_cast<T>(a._val);
		}

		//! Value constructor
		constexpr perc(const T &val) : _val(val)
		{}

		///////////////////////////
		//! RIGHT-HAND OPERATORS //
		///////////////////////////

		//! Unary negative percentage
		perc<T> operator-() const
		{
			return perc<T>(-_val);
		}

		//! Percent addition
		perc<T> operator+(const perc<T> &a) const
		{
			return perc<T>(_val + a._val);
		}

		//! Percent subtraction
		perc<T> operator-(const perc<T> &a) const
		{
			return perc<T>(_val - a._val);
		}

		//! Percent multiplication
		perc<T> operator*(const T &s) const
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
			return _val * static_cast<T>(100);
		}

		T value() const
		{
			return _val;
		}

	private:

		T _val = 0;

	};////

	//////////////////////////
	//! GENERATOR FUNCTIONS //
	//////////////////////////

	//! Creates an percentage from a value [0..1]
	template <typename  T = float>
	static perc<T> value(const T &val)
	{
		return perc<T>(val);
	}

	//! Creates an percentage from a percentage [0..100]
	template <typename  T = float>
	static perc<T> percent(const T &per)
	{
		return perc<T>(per / static_cast<T>(100));
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

inline dym::perc<float> operator "" _per(unsigned long long value)
{
	return dym::percent<float>(static_cast<float>(value));
}

inline dym::perc<float> operator "" _per(long double value)
{
	return dym::percent(static_cast<float>(value));
}

inline dym::perc<float> operator "" _val(unsigned long long value)
{
	return dym::value<float>(static_cast<float>(value));
}

inline dym::perc<float> operator "" _val(long double value)
{
	return dym::value<float>(static_cast<float>(value));
}

#endif

//

#endif