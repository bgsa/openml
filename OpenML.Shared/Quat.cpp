#include "Quat.h"

template <typename T>
Quat<T>::Quat()
{
	static T emptyQuaternion[QUAT_SIZE] = { T(0), T(0), T(0), T(0) };

	memcpy(&values, emptyQuaternion, sizeof(values));
}

template <typename T>
Quat<T>::Quat(T* values)
{
	memcpy(&this->values, values, sizeof(this->values));
}

template <typename T>
Quat<T>::Quat(T value1, T value2, T value3, T value4)
{
	values[0] = value1;
	values[1] = value2;
	values[2] = value3;
	values[3] = value4;
}

template <typename T>
Quat<T>::Quat(Vec3<T> vector)
{
	values[0] = vector[0];
	values[1] = vector[1];
	values[2] = vector[2];
	values[3] = T(0);
}

template <typename T>
T* Quat<T>::getValues()
{
	return values;
}

template <typename T>
T Quat<T>::x()
{
	return values[0];
}

template <typename T>
T Quat<T>::y()
{
	return values[1];
}

template <typename T>
T Quat<T>::z()
{
	return values[2];
}

template <typename T>
T Quat<T>::w()
{
	return values[3];
}

template <typename T>
Quat<T> Quat<T>::add(Quat<T> quatB)
{
	Quat<T> result;

	result[0] = values[0] + quatB[0];
	result[1] = values[1] + quatB[1];
	result[2] = values[2] + quatB[2];
	result[3] = values[3] + quatB[3];

	return result;
}

template <typename T>
Quat<T> Quat<T>::subtract(Quat<T> quatB)
{
	Quat<T> result;

	result[0] = values[0] - quatB[0];
	result[1] = values[1] - quatB[1];
	result[2] = values[2] - quatB[2];
	result[3] = values[3] - quatB[3];

	return result;
}

template <typename T>
void Quat<T>::scale(T value)
{
	values[0] *= value;
	values[1] *= value;
	values[2] *= value;
	values[3] *= value;
}

template <typename T>
Quat<T> Quat<T>::createScale(T value)
{
	Quat<T> result;

	result[0] = values[0] * value;
	result[1] = values[1] * value;
	result[2] = values[2] * value;
	result[3] = values[3] * value;

	return result;
}

template <typename T>
Quat<T> Quat<T>::multiply(Quat<T> quat)
{
	Quat<T> result;

	result[0] = values[0] * quat[3] + values[1] * quat[2] - values[2] * quat[1] + values[3] * quat[0];
	result[1] = -values[0] * quat[2] + values[1] * quat[3] + values[2] * quat[0] + values[3] * quat[1];
	result[2] = values[0] * quat[1] - values[1] * quat[0] + values[2] * quat[3] + values[3] * quat[2];
	result[3] = -values[0] * quat[0] - values[1] * quat[1] - values[2] * quat[2] + values[3] * quat[3];

	return result;
}

template <typename T>
T Quat<T>::length()
{
	double value = sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2] + values[3] * values[3]);

	return T(value);
}

template <typename T>
Quat<T> Quat<T>::normalize()
{
	Quat<T> quat;

	T magnitude = length();

	quat[0] = values[0] / magnitude;
	quat[1] = values[1] / magnitude;
	quat[2] = values[2] / magnitude;
	quat[3] = values[3] / magnitude;

	return quat;
}

template <typename T>
Quat<T> Quat<T>::conjugate()
{
	Quat<T> quat;

	quat[0] = -values[0];
	quat[1] = -values[1];
	quat[2] = -values[2];
	quat[3] = values[3];

	return quat;
}

template <typename T>
T Quat<T>::dot(Quat<T> quatB)
{
	T result = T(sqrt(values[3] * quatB[3] + values[0] * quatB[0] + values[1] * quatB[1] + values[2] * quatB[2]));

	return result;
}

template <typename T>
Quat<T> Quat<T>::inverse()
{
	Quat<T> result(
		values[0],
		values[1],
		values[2],
		values[3]
	);

	T magnitude = length();

	if (magnitude == T(0))
		return result;

	result.scale(1 / (magnitude * magnitude));

	return result;
}

template <typename T>
Quat<T> Quat<T>::rotate(Quat<T> r)
{
	return r * (*this * r.conjugate());
}

template <typename T>
Quat<T> Quat<T>::rotate(double angleInRadians, Vec3<T> vector)
{
	Quat<T> rotationalQuaternion = Quat<T>::createRotate(angleInRadians, vector);

	return rotate(rotationalQuaternion);
}

template <typename T>
Quat<T> Quat<T>::linearInterpolate(Quat<T> quatB, T t)
{
	return createScale(T(1) - t) + quatB.createScale(t);
}

template <typename T>
Quat<T> Quat<T>::linearInterpolateNormalized(Quat<T> quatB, T t)
{
	return linearInterpolate(quatB, t).normalize();
}

template <typename T>
size_t Quat<T>::sizeInBytes()
{
	return QUAT_SIZE * sizeof(T);
}

template <typename T>
Vec3<T> Quat<T>::toVec3()
{
	return Vec3<T>(values[0], values[1], values[2]);
}

template <typename T>
T& Quat<T>::operator[](int index)
{
	assert(index >= 0 && index < QUAT_SIZE);

	return values[index];
}

template <typename T>
Quat<T> Quat<T>::operator+(Quat<T> quatB)
{
	return add(quatB);
}

template <typename T>
Quat<T> Quat<T>::operator-(Quat<T> quatB)
{
	return subtract(quatB);
}

template <typename T>
Quat<T> Quat<T>::operator*(Quat<T> quat)
{
	return multiply(quat);
}

template <typename T>
Quat<T> Quat<T>::operator*(T value)
{
	return createScale(value);
}

template <typename T>
Quat<T>::operator Vec3<T>()
{
	return toVec3();
}

template <typename T>
Quat<T>::operator void*() const
{
	return (void*)values;
}

template class Quat<int>;
template class Quat<float>;
template class Quat<double>;