#pragma once

#include "OpenML.h"

namespace OpenML
{

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
		API_INTERFACE inline Quat();

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE inline Quat(T* values);

		/// <summary>
		/// Constructor with initialized values
		/// </summary>
		API_INTERFACE inline Quat(T value1, T value2, T value3, T value4);

		/// <summary>
		/// Constructor with a 3D vector
		/// </summary>
		API_INTERFACE inline Quat(const Vec3<T>& vector);

		/// <summary>
		/// Get the values from current quaternion
		/// </summary>
		API_INTERFACE T* getValues();

		/// <summary>
		/// Get the x value
		/// </summary>
		API_INTERFACE inline T x() const;

		/// <summary>
		/// Get the y value
		/// </summary>
		API_INTERFACE inline T y() const;

		/// <summary>
		/// Get the z value
		/// </summary>
		API_INTERFACE inline T z() const;

		/// <summary>
		/// Get the w value
		/// </summary>
		API_INTERFACE inline T w() const;

		/// <summary>
		/// Add/Sum two quaternions
		/// </summary>
		API_INTERFACE inline Quat<T> add(const Quat<T>& quatB) const;

		/// <summary>
		/// Subtract two quaternions
		/// </summary>
		API_INTERFACE inline Quat<T> subtract(const Quat<T>& quatB) const;

		/// <summary>
		/// Scale a quaternion
		/// </summary>
		API_INTERFACE inline void scale(T value);

		/// <summary>
		/// Create a new quaternion scaled
		/// </summary>
		API_INTERFACE inline Quat<T> createScale(T value) const;

		/// <summary>
		/// Scale a quaternion
		/// </summary>
		API_INTERFACE inline Quat<T> multiply(const Quat<T>& quat) const;

		/// <summary>
		/// Length/Magnitude of quaternion
		/// </summary>
		API_INTERFACE inline T length() const;

		/// <summary>
		/// Craete a new Quaternion Normalized
		/// </summary>
		API_INTERFACE inline Quat<T> normalize() const;

		/// <summary>
		/// Craete a new Quaternion Conjugated
		/// </summary>
		API_INTERFACE inline Quat<T> conjugate() const;

		/// <summary>
		/// Product Scalar of two quaternion
		/// </summary>
		API_INTERFACE inline T dot(Quat<T> quatB) const;

		/// <summary>
		/// Craete a Inversed Quaternion
		/// Return a quaternion that if multiplied by current quaternion results in value 1 ot the current quternion ifs length/norm is zero
		/// </summary>
		API_INTERFACE Quat<T> inverse() const;

		/// <summary>
		/// Craete a rotation unit quaternion bases on angle (in radians) and directional vector provided
		/// </summary>
		API_INTERFACE static Quat<T> createRotate(double angleInRadians, Vec3<T> position);

		/// <summary>
		/// Return a quaternion rotated bases on rotation quaternion provided in parameter
		/// The parameter can/must be used with createRotation static method
		/// </summary>
		API_INTERFACE inline Quat<T> rotate(const Quat<T>& r) const;

		/// <summary>
		/// Return a quaternion rotated bases on angle and a directional vector
		/// </summary>
		API_INTERFACE inline Quat<T> rotate(double angleInRadians, const Vec3<T>& vector) const;

		/// <summary>
		/// Quaternion lerp. Linear quaternion interpolation method. This method is the quickest, but is also least accurate. The method does not always generate normalized output.
		/// t parameter is [0,1]
		/// </summary>
		API_INTERFACE inline Quat<T> linearInterpolate(const Quat<T>& quatB, T t) const;

		/// <summary>
		/// Quaternion nlerp. Linear quaternion interpolation method. This method is the quickest, but is also least accurate.
		/// This method normalize the result
		/// t parameter is [0,1]
		/// </summary>
		API_INTERFACE inline Quat<T> linearInterpolateNormalized(const Quat<T>& quatB, T t) const;

		/// <summary>
		/// Get the size in Bytes of Quaternion
		/// </summary>
		API_INTERFACE inline size_t sizeInBytes() const;

		/// <summary>
		/// Convertion to Vec3
		/// </summary>
		API_INTERFACE inline Vec3<T> toVec3() const;

		/// <summary>
		/// Get a index from the quaternion
		/// </summary>
		API_INTERFACE inline T& operator[](int index);

		/// <summary>
		/// Get a index from the quaternion
		/// </summary>
		API_INTERFACE inline T operator[](int index) const;

		/// <summary>
		/// Add/Sum two quaternions
		/// </summary>
		API_INTERFACE inline Quat<T> operator+(const Quat<T>& quatB) const;

		/// <summary>
		/// Add/Sum two quaternions
		/// </summary>
		API_INTERFACE inline Quat<T> operator-(const Quat<T>& quatB) const;

		/// <summary>
		/// Multiply the quaternion to another one
		/// </summary>
		API_INTERFACE inline Quat<T> operator*(const Quat<T>& quat) const;

		/// <summary>
		/// Multiply the quaternion to a scalar
		/// Return a new quaternion scaled
		/// </summary>
		API_INTERFACE inline Quat<T> operator*(T value) const;
		
		/// <summary>
		/// Auto convertion to void *
		/// </summary>
		API_INTERFACE inline operator void*() const;

		/// <summary>
		/// Auto convertion to Vec3
		/// </summary>
		API_INTERFACE inline operator Vec3<T>() const;
	};

	typedef Quat<int>	 Quati;
	typedef Quat<float>  Quatf;
	typedef Quat<double> Quatd;

}
