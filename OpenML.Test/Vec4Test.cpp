#pragma once

#include "CppUnitTest.h"
#include <Vec4.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Vec4Test)
	{
	public:

		TEST_METHOD(Vec4_x_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected = 2.0f;

			float result = vector.x;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
		TEST_METHOD(Vec4_y_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected = 5.0f;

			float result = vector.y;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
		TEST_METHOD(Vec4_z_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected = -9.0f;

			float result = vector.z;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
		TEST_METHOD(Vec4_w_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected = 10.0f;

			float result = vector.w;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_getValues_Test)
		{
			Vec4<float> vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected[4] = { 2.0f, 5.0f, -9.0f, 10.0f };

			float* result = vector.getValues();

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_length_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected = sqrt(210.0f);

			float result = vector.length();

			Assert::AreEqual(expected, result, L"Length Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_squared_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			float expected = 210.0f;

			float result = vector.squared();

			Assert::AreEqual(expected, result, L"Length Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_add_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			Vec4f vector2 = { 1.0f, 2.0f, 3.0f, 10.0f };
			float expected[4] = { 3.0f, 7.0f, -6.0f, 20.0f };

			vector.add(vector2);

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_subtract_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.f };
			Vec4f vector2 = { 1.0f, 2.0f, 3.0f, 10.f };
			float expected[4] = { 1.0f, 3.0f, -12.0f, 0.0f };

			vector.subtract(vector2);

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_scale_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.f };
			float expected[4] = { 6.0f, 15.0f, -27.0f, 30.f };

			vector.scale(3.0f);

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_dot_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.f };
			Vec4f vector2 = { 4.0f, -2.0f, 3.0f, 10.f };

			float expected = 71.0f;

			float result = vector.dot(vector2);

			Assert::AreEqual(expected, result, L"Length Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_angle_Test)
		{
			Vec4f vector = { 3.0f, 4.0f, 0.0f, 10.f };
			Vec4f vector2 = { 4.0f, 4.0f, 2.0f, 10.f };

			float expected = 0.981715202f;

			float result = vector.angle(vector2);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_normalize_Test)
		{
			Vec4f vector = { 3.0f, 1.0f, 2.0f, 10.f };
			Vec4f expected = { 0.280975729f, 0.0936585814f, 0.187317163f, 0.936585784f };

			Vec4f result = vector.normalize();

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::IsTrue(isCloseEnough(expected[i], result[i], 0.000001f), L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_distance_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };
			Vec4f vector2 = { 1.0f, 2.0f, 3.0f, 10.0f };
			float expected = 12.4096737f;

			float result = vector.distance(vector2);

			Assert::AreEqual(expected, result, L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_clone_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };

			Vec4f result = vector.clone();

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(vector[i], result[i], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorMultiplyScalar_Test)
		{
			Vec4f vector = { 2.0f, 5.0f, -9.0f, 10.0f };

			Vec4f expected = { 4.0f, 10.0f, -18.0f, 20.0f };

			Vec4f result = vector * 2;

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value", LINE_INFO());
		}
		
		TEST_METHOD(Vec4_operatorPlusVector_Test)
		{
			Vec4f vector = { 2.0f, 3.0f, 4.0f, 10.0f };
			Vec4f vector2 = { 5.0f, 6.0f, -7.0f, 40.0f };
			Vec4f expected = { 7.0f, 9.0f, -3.0f, 50.0f };

			Vec4f result = vector + vector2;

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorPlusScalar_Test)
		{
			Vec4f vector = { 2.0f, -3.0f, 4.0f, 10.0f };
			Vec4f expected = { 4.0f, -1.0f, 6.0f, 12.0f };

			Vec4f result = vector + 2.0f;

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorMinusVector_Test)
		{
			Vec4f vector = { 2.0f, 3.0f, 4.0f, 10.0f };
			Vec4f vector2 = { 5.0f, 6.0f, -7.0f, 15.0f };
			Vec4f expected = { -3.0f, -3.0f, 11.0f, -5.0f };

			Vec4f result = vector - vector2;

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorMinusScalar_Test)
		{
			Vec4f vector = { 2.0f, -3.0f, 4.0f, 10.0f };
			Vec4f expected = { 0.0f, -5.0f, 2.0f, 8.0f };

			Vec4f result = vector - 2.0f;

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorMinus_Test)
		{
			Vec4f vector = { -2.0f, 3.0f, 4.0f, -5.0f };
			Vec4f expected = { 2.0f, -3.0f, -4.0f, 5.0f };

			Vec4f result = -vector;

			for (size_t i = 0; i < VEC4_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorEqualVector_Test)
		{
			Vec4f vector = { 2.0f, -3.0f, 4.0f, 10.0f };

			Vec4f vectorEqual = { 2.0f, -3.0f, 4.0f, 10.0f };

			Vec4f vectorNotEqual_X = { 0.0f, -3.0f, 4.0f, 10.0f };
			Vec4f vectorNotEqual_Y = { 2.0f, 3.0f, 4.0f, 10.0f };
			Vec4f vectorNotEqual_Z = { 2.0f, -3.0f, 5.0f, 10.0f };
			Vec4f vectorNotEqual_W = { 2.0f, -3.0f, 4.0f, 7.0f };

			Assert::IsTrue(vector == vectorEqual, L"Vectors should be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_X, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_Y, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_Z, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_W, L"Vectors should not be equal.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorEqualScalar_Test)
		{
			Vec4f vector = { 0.0f, 0.0f, 0.0f, 0.0f };
			Assert::IsTrue(vector == 0, L"Vectors should be equal 0.", LINE_INFO());

			vector = { 1.0f, 0.0f, 0.0f, 0.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());

			vector = { 0.0f, 1.0f, 0.0f, 0.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());

			vector = { 0.0f, 0.0f, 1.0f, 0.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());

			vector = { 0.0f, 0.0f, 0.0f, 1.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorNotEqual_Test)
		{
			Vec4f vector = { 2.0f, -3.0f, 4.0f, 10.0f };

			Vec4f vectorEqual = { 2.0f, -3.0f, 4.0f, 10.0f };

			Vec4f vectorNotEqual_X = { 0.0f, -3.0f, 4.0f, 10.0f };
			Vec4f vectorNotEqual_Y = { 2.0f, 3.0f, 4.0f, 10.0f };
			Vec4f vectorNotEqual_Z = { 2.0f, -3.0f, 5.0f, 10.0f };
			Vec4f vectorNotEqual_W = { 2.0f, -3.0f, 4.0f, 4.0f };

			Assert::IsFalse(vector != vectorEqual, L"Vectors should be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_X, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_Y, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_Z, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_W, L"Vectors should not be equal.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorIndex_Test)
		{
			Vec4f vector = { 2.0f, -3.0f, 4.0f, 10.0f };

			Assert::AreEqual(2.0f, vector[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(-3.0f, vector[1], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(4.0f, vector[2], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(10.0f, vector[3], L"Wrong value.", LINE_INFO());
			
			//vector = { 5.0f, 6.0f, 7.0f, 8.0f };
			vector[0] = 5.0f;
			vector[1] = 6.0f;
			vector[2] = 7.0f;
			vector[3] = 8.0f;

			Assert::AreEqual(5.0f, vector[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(6.0f, vector[1], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(7.0f, vector[2], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(8.0f, vector[3], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec4_operatorDireferent_value_Test)
		{
			Vec4f vector = { 0.0f, 0.0f, 0.0f, 0.0f };
			bool result = vector != 0.0f;
			Assert::IsFalse(result, L"vector should not be diferente of Zero", LINE_INFO());

			vector = { 0.0f, 0.0f, 0.0f, 1.0f };
			result = vector != 0.0f;
			Assert::IsTrue(result, L"vector should be diferente of Zero", LINE_INFO());

			vector = { 0.0f, 0.0f, 1.0f, 0.0f };
			result = vector != 0.0f;
			Assert::IsTrue(result, L"vector should be diferente of Zero", LINE_INFO());

			vector = { 0.0f, 1.0f, 0.0f, 0.0f };
			result = vector != 0.0f;
			Assert::IsTrue(result, L"vector should be diferente of Zero", LINE_INFO());

			vector = { 1.0f, 0.0f, 0.0f, 0.0f };
			result = vector != 0.0f;
			Assert::IsTrue(result, L"vector should be diferente of Zero", LINE_INFO());
		}

		TEST_METHOD(Vec4_toVec3_Test)
		{
			Vec4f vector = { 2.0f, -3.0f, 4.0f, 10.0f };
			Vec3f expected = { 2.0f, -3.0f, 4.0f };

			Vec3f result = vector.toVec3();

			for (size_t i = 0; i < VEC3_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Length Wrong value", LINE_INFO());
		}

	};
}