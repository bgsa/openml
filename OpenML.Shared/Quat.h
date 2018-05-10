#pragma once

#include "OpenML.h"

#define QUAT_SIZE 4

template <typename T>
class Quat
{
private:
	T values[QUAT_SIZE];

public:

	/// <summary>
	/// Default constructor
	/// Load a empty quaternion = 0
	/// </summary>
	API_INTERFACE Quat();

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Quat(T* values);

	/// <summary>
	/// Constructor with initialized values
	/// </summary>
	API_INTERFACE Quat(T value1, T value2, T value3, T value4);

	/// <summary>
	/// Constructor with a 3D vector
	/// </summary>
	API_INTERFACE Quat(Vec3<T> vector);

	/// <summary>
	/// Get the values from current quaternion
	/// </summary>
	API_INTERFACE T* getValues();
	
	/// <summary>
	/// Get the x value
	/// </summary>
	API_INTERFACE T x();

	/// <summary>
	/// Get the y value
	/// </summary>
	API_INTERFACE T y();

	/// <summary>
	/// Get the z value
	/// </summary>
	API_INTERFACE T z();

	/// <summary>
	/// Get the w value
	/// </summary>
	API_INTERFACE T w();

	/// <summary>
	/// Add/Sum two quaternions
	/// </summary>
	API_INTERFACE Quat<T> add(Quat<T> quatB);

	/// <summary>
	/// Subtract two quaternions
	/// </summary>
	API_INTERFACE Quat<T> subtract(Quat<T> quatB);

	/// <summary>
	/// Scale a quaternion
	/// </summary>
	API_INTERFACE void scale(T value);

	/// <summary>
	/// Create a new quaternion scaled
	/// </summary>
	API_INTERFACE Quat<T> createScale(T value);

	/// <summary>
	/// Scale a quaternion
	/// </summary>
	API_INTERFACE Quat<T> multiply(Quat<T> quat);

	/// <summary>
	/// Length/Magnitude of quaternion
	/// </summary>
	API_INTERFACE T length();

	/// <summary>
	/// Craete a new Quaternion Normalized
	/// </summary>
	API_INTERFACE Quat<T> normalize();

	/// <summary>
	/// Craete a new Quaternion Conjugated
	/// </summary>
	API_INTERFACE Quat<T> conjugate();

	/// <summary>
	/// Product Scalar of two quaternion
	/// </summary>
	API_INTERFACE T dot(Quat<T> quatB);

	/// <summary>
	/// Craete a Inversed Quaternion
	/// Return a quaternion that if multiplied by current quaternion results in value 1 ot the current quternion ifs length/norm is zero
	/// </summary>
	API_INTERFACE Quat<T> inverse();

	/// <summary>
	/// Craete a rotation unit quaternion bases on angle (in radians) and directional vector provided
	/// </summary>
	API_INTERFACE static Quat<T> createRotate(double angleInRadians, Vec3<T> position)
	{
		double halfAngle = angleInRadians / 2;
		double sinHalfAngle = sin(halfAngle);
		double cosineHalfAngle = cos(halfAngle);

		Vec3<T> positionNomralized = position.normalize();

		Quat<T> result(
			T(sinHalfAngle * positionNomralized[0]),
			T(sinHalfAngle * positionNomralized[1]),
			T(sinHalfAngle * positionNomralized[2]),
			T(cosineHalfAngle)
		);

		return result;
	}

	/// <summary>
	/// Return a quaternion rotated bases on rotation quaternion provided in parameter
	/// The parameter can/must be used with createRotation static method
	/// </summary>
	API_INTERFACE Quat<T> rotate(Quat<T> r);

	/// <summary>
	/// Return a quaternion rotated bases on angle and a directional vector
	/// </summary>
	API_INTERFACE Quat<T> rotate(double angleInRadians, Vec3<T> vector);

	/// <summary>
	/// Quaternion lerp. Linear quaternion interpolation method. This method is the quickest, but is also least accurate. The method does not always generate normalized output.
	/// t parameter is [0,1]
	/// </summary>
	API_INTERFACE Quat<T> linearInterpolate(Quat<T> quatB, T t);

	/// <summary>
	/// Quaternion nlerp. Linear quaternion interpolation method. This method is the quickest, but is also least accurate.
	/// This method normalize the result
	/// t parameter is [0,1]
	/// </summary>
	API_INTERFACE Quat<T> linearInterpolateNormalized(Quat<T> quatB, T t);

	/// <summary>
	/// Get the size in Bytes of Quaternion
	/// </summary>
	API_INTERFACE size_t sizeInBytes();

	/// <summary>
	/// Convertion to Vec3
	/// </summary>
	API_INTERFACE Vec3<T> toVec3();

	/// <summary>
	/// Get a index from the quaternion
	/// </summary>
	API_INTERFACE T& operator[](int index);

	/// <summary>
	/// Add/Sum two quaternions
	/// </summary>
	API_INTERFACE Quat<T> operator+(Quat<T> quatB);

	/// <summary>
	/// Add/Sum two quaternions
	/// </summary>
	API_INTERFACE Quat<T> operator-(Quat<T> quatB);
	
	/// <summary>
	/// Multiply the quaternion to another one
	/// </summary>
	API_INTERFACE Quat<T> operator*(Quat<T> quat);

	/// <summary>
	/// Multiply the quaternion to a scalar
	/// Return a new quaternion scaled
	/// </summary>
	API_INTERFACE Quat<T> operator*(T value);

	/// <summary>
	/// Auto convertion to Vec3
	/// </summary>
	API_INTERFACE operator Vec3<T>();

	/// <summary>
	/// Auto convertion to void *
	/// </summary>
	API_INTERFACE operator void*() const;

};

typedef Quat<int>	 Quati;
typedef Quat<float>  Quatf;
typedef Quat<double> Quatd;
