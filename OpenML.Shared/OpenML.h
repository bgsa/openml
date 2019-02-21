#pragma once

#include "GlobalHeader.h"

namespace OpenML 
{
	const float DefaultErrorMargin = 0.0009f;
	
#define PI (3.14159265358979323846)
#define TWO_PI (6.28318530717958647692)
#define HALF_PI (1.57079632679489661923)
#define PI_DIV_180 (0.017453292519943296)
#define INV_PI_DIV_180 (57.2957795130823229)
#define	PI_DIV_360 (0.008726646259971647)

#define degreesToRadians(x)	((x) * PI_DIV_180)
#define radiansToDegrees(x)	((x) * INV_PI_DIV_180)

#define hourToDegrees(x) ( x * (1.0 / 15.0) )
#define hourToRadians(x)	degreesToRadians(hourToDegrees(x))

#define degreesToHout(x)	((x) * 15.0))
#define radiansToHour(x)	degreesToHout(radiansToDegrees(x))

	///<summary>
	///Check the number is even or not
	///</summary>
	template <typename T>
	inline bool API_INTERFACE isEven(T value)
	{
		return (value % 2) == 0;
	}

	///<summary>
	///Check the number is odd or not
	///</summary>
	template <typename T>
	inline bool API_INTERFACE isOdd(T value)
	{
		return ! isEven(value);
	}

	///<summary>
	///Check the number is power of 2
	///</summary>
	template <typename T>
	inline unsigned int API_INTERFACE isPow2(T value)
	{
		T nPow2 = T(1);

		while (value > nPow2)
			nPow2 = (nPow2 << 1);

		return nPow2;
	}

	///<summary>
	///Get the next number power of 2
	///</summary>
	inline unsigned int API_INTERFACE nextPowOf2(int value)
	{
		int rval = 1;

		while (rval < value) 
			rval *= 2;

		return rval;
	}
		
	///<summary>
	///Round the number given a amount of decimals
	///</summary>
	template<typename T>		
	inline T API_INTERFACE round(T number, int decimals)
	{
		double m = (number < 0.0) ? -1.0 : 1.0;   // check if input is negative
		double power = pow(10, decimals);

		return T((floor(number * m * power + 0.5) / power) * m);
	}

	///<summary>
	///Round the number (in float) given a amount of decimals
	///</summary>
	inline float API_INTERFACE roundf(float number, int decimals)
	{
		return OpenML::round<float>(number, decimals);
	}
	
	///<summary>
	///Round the number (in double) given a amount of decimals
	///</summary>
	inline double API_INTERFACE roundd(double number, int decimals)
	{
		return OpenML::round<double>(number, decimals);
	}

	///<summary>
	///Check the number is close enough given a other number. It is used to check aproximation value and calculate the error measure.
	///Epsilon is the tolerated value
	///</summary>
	template<typename T>
	inline bool API_INTERFACE isCloseEnough(T value, T compare, T epsilon)
	{
		return abs(value - compare) < epsilon;
	}

	///<summary>
	///Check the number is close enough given a other number. It is used to check aproximation value and calculate the error measure.
	///</summary>
	template<typename T>
	inline bool API_INTERFACE isCloseEnough(T value, T compare)
	{
		return isCloseEnough(value, compare, T(DefaultErrorMargin));
	}
	
}

#include "ColisionStatus.h"

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "Mat.h"
#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"

#include "Quat.h"

#include "Line2D.h"
#include "Circle2D.h"

#include "Rectangle2D.h"