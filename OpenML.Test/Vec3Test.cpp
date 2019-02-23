#pragma once

#include "CppUnitTest.h"
#include <Vec3.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Vec3Test)
	{
	public:

		TEST_METHOD(Vec3_x_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			float expected = 2.0f;

			float result = vector.x();

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
		TEST_METHOD(Vec3_y_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			float expected = 5.0f;

			float result = vector.y();

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
		TEST_METHOD(Vec3_z_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			float expected = -9.0f;

			float result = vector.z();

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_getValues_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			float expected[3] = { 2.0f, 5.0f, -9.0f };

			float* result = vector.getValues();

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_length_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };

			float expected = sqrt(110.0f);

			float result = vector.length();

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}	

		TEST_METHOD(Vec3_squared_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			float expected = 4.0f + 25.0f + 81.0f;

			float result = vector.squaredLength();

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_add_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			Vec3f vector2 = { 1.0f, 2.0f, 3.0f };
			float expected[3] = { 3.0f, 7.0f, -6.0f };

			vector.add(vector2);

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_subtract_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			Vec3f vector2 = { 1.0f, 2.0f, 3.0f };
			float expected[3] = { 1.0f, 3.0f, -12.0f };

			vector.subtract(vector2);

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_multiplyVector_Test)
		{
			Vec3f vector = { 2.0f, 3.0f, 4.0f };
			Vec3f vector2 = { 5.0f, 6.0f, -7.0f };
			Vec3f expected = { 10.0f, 18.0f, -28.0f };

			Vec3f result = vector.multiply(vector2);

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_scale_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			float expected[3] = { 6.0f, 15.0f, -27.0f };

			vector.scale(3.0f);

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_cross_Test)
		{
			Vec3f vector = { 2.0f, 3.0f, 4.0f };
			Vec3f vector2 = { 5.0f, 6.0f, 7.0f };
			Vec3f expected = { -3.0f, 6.0f, -3.0f };

			Vec3f result = vector.cross(vector2);

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_dot_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			Vec3f vector2 = { 4.0f, -2.0f, 3.0f };
			float expected = -29.0f;

			float result = vector.dot(vector2);

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_tripleProduct_Test)
		{
			Vec3f vector1 = { 10.0f, 0.0f, 0.0f };
			Vec3f vector2 = { 0.0f, 0.0f, 10.0f };
			Vec3f vector3 = { 0.0f, 10.0f, 0.0f };
			float expected = -1000.0f;

			float result = vector1.tripleProduct(vector2, vector3);

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_angle_Test)
		{
			Vec3f vector = { 3.0f, 4.0f, 0.0f };
			Vec3f vector2 = { 4.0f, 4.0f, 2.0f };
			
			float expected = 28.0f / 30.0f;

			float result = vector.angle(vector2);

			Assert::AreEqual(expected, result, L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_normalize_Test)
		{
			Vec3f vector = { 3.0f, 1.0f, 2.0f };
			Vec3f expected = { 0.801783681f, 0.267261237f, 0.534522474f };
			
			Vec3f result = vector.normalize();

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_transformToUnit_Test)
		{
			Vec3f vector = { 3.0f, 1.0f, 2.0f };
			Vec3f expected = { 0.801783681f, 0.267261237f, 0.534522474f };

			vector.transformToUnit();

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_distance_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };
			Vec3f vector2 = { 1.0f, 2.0f, 3.0f };
			float expected = 12.4096737f;

			float result = vector.distance(vector2);

			Assert::AreEqual(expected, result, L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec3_clone_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };

			Vec3f result = vector.clone();

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(vector[i], result[i], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorMultiplyScalar_Test)
		{
			Vec3f vector = { 2.0f, 5.0f, -9.0f };

			Vec3f expected = { 4.0f, 10.0f, -18.0f };

			Vec3f result = vector * 2;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorMultiplyVector_Test)
		{
			Vec3f vector = { 2.0f, 3.0f, 4.0f };
			Vec3f vector2 = { 5.0f, 6.0f, -7.0f };
			Vec3f expected = { 10.0f, 18.0f, -28.0f };

			Vec3f result = vector * vector2;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorPlusVector_Test)
		{
			Vec3f vector = { 2.0f, 3.0f, 4.0f };
			Vec3f vector2 = { 5.0f, 6.0f, -7.0f };
			Vec3f expected = { 7.0f, 9.0f, -3.0f };

			Vec3f result = vector + vector2;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorPlusScalar_Test)
		{
			Vec3f vector = { 2.0f, -3.0f, 4.0f };
			Vec3f expected = { 4.0f, -1.0f, 6.0f };

			Vec3f result = vector + 2.0f;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorMinus_vector_Test)
		{
			Vec3f vector = { 2.0f, 3.0f, 4.0f };
			Vec3f vector2 = { 5.0f, 6.0f, -7.0f };
			Vec3f expected = { -3.0f, -3.0f, 11.0f };

			Vec3f result = vector - vector2;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorMinus_prefix_Test)
		{
			Vec3f vector = { -2.0f, 3.0f, 4.0f };
			Vec3f expected = { 2.0f, -3.0f, -4.0f };

			Vec3f result = -vector;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorMinusScalar_Test)
		{
			Vec3f vector = { 2.0f, -3.0f, 4.0f };
			Vec3f expected = { 0.0f, -5.0f, 2.0f };

			Vec3f result = vector - 2.0f;

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorEqualVector_Test)
		{
			Vec3f vector = { 2.0f, -3.0f, 4.0f };

			Vec3f vectorEqual = { 2.0f, -3.0f, 4.0f };

			Vec3f vectorNotEqual_X = { 0.0f, -3.0f, 4.0f };
			Vec3f vectorNotEqual_Y = { 2.0f, 3.0f, 4.0f };
			Vec3f vectorNotEqual_Z = { 2.0f, -3.0f, 5.0f };
			
			Assert::IsTrue(vector == vectorEqual, L"Vectors should be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_X, L"Vectors should not be equal.", LINE_INFO());
			
			Assert::IsFalse(vector == vectorNotEqual_Y, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_Z, L"Vectors should not be equal.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorEqualScalar_Test)
		{
			Vec3f vector = { 0.0f, 0.0f, 0.0f };
			Assert::IsTrue(vector == 0, L"Vectors should be equal 0.", LINE_INFO());

			vector = { 1.0f, 0.0f, 0.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());

			vector = { 0.0f, 1.0f, 0.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());

			vector = { 0.0f, 0.0f, 1.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorNotEqual_Test)
		{
			Vec3f vector = { 2.0f, -3.0f, 4.0f };

			Vec3f vectorEqual = { 2.0f, -3.0f, 4.0f };

			Vec3f vectorNotEqual_X = { 0.0f, -3.0f, 4.0f };
			Vec3f vectorNotEqual_Y = { 2.0f, 3.0f, 4.0f };
			Vec3f vectorNotEqual_Z = { 2.0f, -3.0f, 5.0f };

			Assert::IsFalse(vector != vectorEqual, L"Vectors should be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_X, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_Y, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_Z, L"Vectors should not be equal.", LINE_INFO());
		}

		TEST_METHOD(Vec3_operatorIndex_Test)
		{
			Vec3f vector = { 2.0f, -3.0f, 4.0f };

			Assert::AreEqual(2.0f, vector[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(-3.0f, vector[1], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(4.0f, vector[2], L"Wrong value.", LINE_INFO());

			vector[0] = 5.0f;
			vector[1] = 6.0f;
			vector[2] = 7.0f;

			Assert::AreEqual(5.0f, vector[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(6.0f, vector[1], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(7.0f, vector[2], L"Wrong value.", LINE_INFO());
		}
		
	};
}