#ifndef OPENML_HEADER
#define OPENML_HEADER

#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdarg.h>

#include <apollo.h>

#define EULER_NUMBER (2.71828f)   // e^1 = 2.71828

#define MAX_DIGITS_EXPOENT  (5)
#define MAX_DIGITS_MANTISSA (4)

namespace OpenML
{
	const float DefaultErrorMargin = 0.0001f;

	template <typename T>
	class Vec2;
	template <typename T>
	class Vec3;
	template <typename T>
	class Vec4;

	template <typename T>
	class Vec2List;
	template <typename T>
	class Vec3List;

	template <typename T>
	class Mat;
	template <typename T>
	class Mat2;
	template <typename T>
	class Mat3;
	template <typename T>
	class Mat4;

	template <typename T>
	class Quat;

	template <class T>
	class BoundingVolume;

	template <typename T>
	class BinaryTree;
	template <typename T>
	class BinaryTreeNode;

	template <typename T>
	class Line2D;
	class Line3D;
	class Plane3D;
	template <typename T>
	class Triangle2D;
	template <typename T>
	class Circle2D;

	class AABB;
	class OBB;
	class Sphere;
	class DOP18;

	template <typename T>
	class Rectangle2D;

	///<summary>
	///Fast multiplication by 2
	///</summary>
	template <typename T>
	inline T API_INTERFACE multiplyBy2(T value)
	{
		return (value << SHIFT_BIT);
	}
	///<summary>
	///Fast multiplication by 10
	///</summary>
	inline size_t API_INTERFACE multiplyBy10(size_t value)
	{
		return ((value << 3) + (value << 1));
	}

	///<summary>
	///Fast division by 2
	///</summary>
	template <typename T>
	inline T API_INTERFACE divideBy2(T value)
	{
		return (value >> SHIFT_BIT);
	}

	///<summary>
	///Check the number is even or not
	///</summary>
	template <typename T>
	inline bool API_INTERFACE isEven(T value)
	{
		return (value % 2) == 0;
	}
	template <>
	inline bool API_INTERFACE isEven<int>(int value)
	{
		return !(value & 1);
	}
	template <>
	inline bool API_INTERFACE isEven<size_t>(size_t value)
	{
		return !(value & 1);
	}
		
	///<summary>
	///Check the number is odd or not
	///</summary>
	template <typename T>
	inline bool API_INTERFACE isOdd(T value)
	{
		return ! isEven(value);
	}
	template <>
	inline bool API_INTERFACE isOdd<int>(int value)
	{
		return value & 1;
	}
	template <>
	inline bool API_INTERFACE isOdd<size_t>(size_t value)
	{
		return value & 1;
	}

	///<summary>
	///Modify a bit of a integer value, given a index bit
	///</summary>
	inline int API_INTERFACE modifyBit(int value, int index, int bit)
	{
		return (value & ~(SHIFT_BIT << index)) | ((bit << index) & (SHIFT_BIT << index));
	}

	///<summary>
	///Set a bit to ZERO of a integer value, given a index bit
	///</summary>
	inline int API_INTERFACE clearBit(int value, int index)
	{
		return modifyBit(value, index, 0);
	}

	///<summary>
	///Set a bit to ONE of a integer value, given a index bit
	///</summary>
	inline int API_INTERFACE setBit(int value, int index)
	{
		return modifyBit(value, index, 1);
	}

	///<summary>
	///GFet a bit of a integer value, given a index bit
	///</summary>
	inline int API_INTERFACE getBit(int value, int index)
	{
		return (value & (SHIFT_BIT << index)) >> index;
	}
	///<summary>
	///GFet a bit of a integer value, given a index bit
	///</summary>
	inline int API_INTERFACE getBit(size_t value, int index)
	{
		return (value & (SHIFT_BIT << index)) >> index;
	}

	///<summary>
	///Get the parts of float (expoent and mantissa)
	///The mantissa just returns the 4th numbers
	///</summary>
	inline size_t API_INTERFACE floatParts(float value, size_t* expoent)
	{
		*expoent = (size_t)value;
		return size_t(std::fabsf(*expoent - value) * 10000.0f);
	}

	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	inline int API_INTERFACE digit(int value, int index)
	{
		int result = int(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE;

		assert(result >= 0 && result < 10);
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	inline size_t API_INTERFACE digit(size_t value, size_t index)
	{
		size_t result = size_t(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE;

		assert(result >= 0 && result < 10);
		return result;
	}
	///<summary>
	///Get a digit of the number given by value parameter and the index
	///</summary>
	inline int API_INTERFACE digit(float value, int index)
	{
		int result = int(value / std::pow(DECIMAL_BASE, index)) % DECIMAL_BASE;

		assert(result >= 0 && result < 10);
		return result;
	}

	///<summary>
	///Check the numbers have the same sign
	///</summary>
	inline bool API_INTERFACE sameSign(int value1, int value2)
	{
		return (value1 ^ value2) >= 0;
	}

	///<summary>
	///Return -1 if value <  0
	///Return  0 if value == 0
	///Return  1 if value >  0
	///</summary>
	template <typename T> 
	inline int API_INTERFACE sign(T value) 
	{
		return (T(0) < value) - (value < T(0));
	}

	///<summary>
	///Check the number is power of 2
	///</summary>
	inline bool API_INTERFACE isPowerOf2(size_t value)
	{
		return value && !(value & (value - 1));
	}

	///<summary>
	///Get the next number power of 2
	///</summary>
	inline unsigned int API_INTERFACE nextPowOf2(int value)
	{
		int rval = 1;

		while (rval < value) 
			rval = rval << 1; // multiply by 2

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

		return T((floor(m * number * power + 0.5) / power) * m);
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
	///
	///</summary>
	template <typename T>
	inline T API_INTERFACE clamp(T value, T minValue, T maxValue)
	{
		if (value < minValue)
			value = minValue;
		else
			if (value > maxValue)
				value = maxValue;

		return value;
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

	///<summary>
	///Get the count of digits of the number given by value parameter
	///</summary>
	inline size_t API_INTERFACE digitCount(int value)
	{
		size_t len = 1;

		if (value < 0)
			value *= -1;

		for (len = 0; value > 0; len++)
			value = value / 10;

		return len;
	}
	///<summary>
	///Get the count of digits of the number given by value parameter
	///</summary>
	inline size_t API_INTERFACE digitCount(size_t value)
	{
		size_t len = 1;

		for (len = 0; value > 0; len++)
			value = value / 10;

		return len;
	}
	///<summary>
	///Get the count of digits of the number given by value parameter
	///</summary>
	inline size_t API_INTERFACE digitMantissaCount(float value)
	{
		float temp;
		float d = std::modff(value, &temp);
		size_t counter = 0;

		while (d > 0 && !isCloseEnough(d, 0.0f)) {
			d *= 10;
			d = d - ((size_t)d);
			counter++;
		}

		return counter;
	}

}

#include "CollisionStatus.h"

#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#include "Vec2List.h"
#include "Vec3List.h"

#include "Mat.h"
#include "Mat2.h"
#include "Mat3.h"
#include "Mat4.h"

#include "Quat.h"

#include "Line2D.h"
#include "Circle2D.h"

#include "Rectangle2D.h"

#endif // !OPENML_HEADER