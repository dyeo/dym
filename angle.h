#ifndef _GMATH_ANGLE_H_
#define _GMATH_ANGLE_H_

//

#define DEG2RAD 0.0174532925199432957692369076848861271344
#define RAD2DEG 57.2957795130823208767981548141051703324

namespace gmath
{////

	template<typename T = float>
	class Angle
	{
	public:

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
				ang = amount * DEG2RAD;
				break;
			}
		};

		template<typename U>
		// Type conversion copy constructor
		inline Angle(const Angle<U>& a)
		{
			ang = static_cast<T>(a.ang);
		}

		inline float degrees() const
		{
			return ang * RAD2DEG;
		}

		inline float radians() const
		{
			return ang;
		}

	private:

		T ang = 0;

	};

	// Creates an angle with degrees
	inline Angle<float> Degrees(float deg)
	{
		return Angle<float>(deg, Angle<float>::Degrees);
	}

	// Creates an angle with radians
	inline Angle<float> Radians(float rad)
	{
		return Angle<float>(rad, Angle<float>::Radians);
	}

}////

//

#endif