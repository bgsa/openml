#pragma once

#include "GlobalHeader.h"

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "Mat.h"
#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"

#include "Quat.h"

#include "Point2D.h"
#include "Point3D.h"

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

	template <typename T>
	inline bool API_INTERFACE isEven(T value)
	{
		return (value % 2) == 0;
	}

	template <typename T>
	inline bool API_INTERFACE isOdd(T value)
	{
		return ! isEven(value);
	}

	template <typename T>
	inline unsigned int API_INTERFACE isPow2(T value)
	{
		T nPow2 = T(1);

		while (value > nPow2)
			nPow2 = (nPow2 << 1);

		return nPow2;
	}

	inline unsigned int API_INTERFACE nextPowOf2(int value)
	{
		int rval = 1;

		while (rval < value) 
			rval *= 2;

		return rval;
	}
		
	template<typename T>		
	inline T API_INTERFACE round(T number, int decimals)
	{
		double m = (number < 0.0) ? -1.0 : 1.0;   // check if input is negative
		double power = pow(10, decimals);

		return T((floor(number * m * power + 0.5) / power) * m);
	}

	inline float API_INTERFACE roundf(float number, int decimals)
	{
		return OpenML::round<float>(number, decimals);
	}

	
	inline double API_INTERFACE roundd(double number, int decimals)
	{
		return OpenML::round<double>(number, decimals);
	}

	template<typename T>
	inline bool API_INTERFACE isCloseEnough(const T value, const T compare, const T epsilon)
	{
		return T(abs(value - compare) < epsilon);
	}

	template<typename T>
	inline bool API_INTERFACE isCloseEnough(const T value, const T compare)
	{
		return isCloseEnough(value, compare, DefaultErrorMargin);
	}
	
}

