#pragma once

#include "CppUnitTest.h"
#include <Vec2.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace OpenMLTest
{
	TEST_CLASS(Vec2Test)
	{
	public:

		TEST_METHOD(Vec2_x_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			float expected = 2.0f;

			float result = vector.x;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_y_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			float expected = -9.0f;

			float result = vector.y;

			Assert::AreEqual(expected, result, L"Wrong value.", LINE_INFO());
		}
	
		TEST_METHOD(Vec2_getValues_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			float expected[VEC2_SIZE] = { 2.0f, -9.0f };

			float* result = vector.getValues();

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_length_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			float expected = sqrt(85.0f);

			float result = vector.length();

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_squared_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			float expected = 85.0f;

			float result = vector.squared();

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_add_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			Vec2f vector2 = { 1.0f, 3.0f };
			float expected[VEC2_SIZE] = { 3.0f, -6.0f };

			vector.add(vector2);

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_subtract_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			Vec2f vector2 = { 1.0f, 3.0f };
			float expected[VEC2_SIZE] = { 1.0f, -12.0f };

			vector.subtract(vector2);

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_scale_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			float expected[VEC2_SIZE] = { 6.0f, -27.0f };

			vector.scale(3.0f);

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Length value wrong.", LINE_INFO());
		}
		
		TEST_METHOD(Vec2_dot_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			Vec2f vector2 = { 4.0f, 3.0f };
			float expected = -19.0f;

			float result = vector.dot(vector2);

			Assert::AreEqual(expected, result, L"Length value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_angle_Test)
		{
			Vec2f vector = { 3.0f, 0.0f };
			Vec2f vector2 = { 4.0f, 2.0f };

			float expected = 0.894427121f;

			float result = vector.angle(vector2);

			Assert::AreEqual(expected, result, L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_normalize_Test)
		{
			Vec2f vector = { 3.0f, 2.0f };
			Vec2f expected = { 0.832050323f, 0.554700196f };

			Vec2f result = vector.normalize();

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_transformToUnit_Test)
		{
			Vec2f vector = { 3.0f, 2.0f };
			Vec2f expected = { 0.832050323f, 0.554700196f };

			vector.transformToUnit();

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], vector[i], L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_distance_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };
			Vec2f vector2 = { 1.0f, 3.0f };
			float expected = 12.0415945f;

			float result = vector.distance(vector2);

			Assert::AreEqual(expected, result, L"Value wrong.", LINE_INFO());
		}

		TEST_METHOD(Vec2_clone_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };

			Vec2f result = vector.clone();

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(vector[i], result[i], L"Wrong value", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorMultiplyScalar_Test)
		{
			Vec2f vector = { 2.0f, -9.0f };

			Vec2f expected = { 4.0f, -18.0f };

			Vec2f result = vector * 2;

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value", LINE_INFO());
		}
		
		TEST_METHOD(Vec2_operatorPlusVector_Test)
		{
			Vec2f vector = { 2.0f, 4.0f };
			Vec2f vector2 = { 5.0f, -7.0f };
			Vec2f expected = { 7.0f, -3.0f };

			Vec2f result = vector + vector2;

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorPlusScalar_Test)
		{
			Vec2f vector = { 2.0f, 4.0f };
			Vec2f expected = { 4.0f, 6.0f };

			Vec2f result = vector + 2.0f;

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorMinusVector_Test)
		{
			Vec2f vector = { 2.0f, 4.0f };
			Vec2f vector2 = { 5.0f, -7.0f };
			Vec2f expected = { -3.0f, 11.0f };

			Vec2f result = vector - vector2;

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorMinus_prefix_Test)
		{
			Vec2f vector = { -2.0f, 3.0f };
			Vec2f expected = { 2.0f, -3.0f };

			Vec2f result = -vector;

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorMinusScalar_Test)
		{
			Vec2f vector = { 2.0f, 4.0f };
			Vec2f expected = { 0.0f, 2.0f };

			Vec2f result = vector - 2.0f;

			for (size_t i = 0; i < VEC2_SIZE; i++)
				Assert::AreEqual(expected[i], result[i], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorEqualVector_Test)
		{
			Vec2f vector = { 2.0f, 4.0f };

			Vec2f vectorEqual = { 2.0f, 4.0f };

			Vec2f vectorNotEqual_X = { 0.0f, 4.0f };
			Vec2f vectorNotEqual_Y = { 2.0, 0.0f };

			Assert::IsTrue(vector == vectorEqual, L"Vectors should be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_X, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsFalse(vector == vectorNotEqual_Y, L"Vectors should not be equal.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorEqualScalar_Test)
		{
			Vec2f vector = { 0.0f, 0.0f };
			Assert::IsTrue(vector == 0, L"Vectors should be equal 0.", LINE_INFO());

			vector = { 1.0f, 0.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());

			vector = { 0.0f, 1.0f };
			Assert::IsFalse(vector == 0, L"Vectors should not be equal 0.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorNotEqual_Test)
		{
			Vec2f vector = { 2.0f, 4.0f };

			Vec2f vectorEqual = { 2.0f, 4.0f };

			Vec2f vectorNotEqual_X = { 0.0f, 4.0f };
			Vec2f vectorNotEqual_Y = { 2.0f, 3.0f };

			Assert::IsFalse(vector != vectorEqual, L"Vectors should be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_X, L"Vectors should not be equal.", LINE_INFO());

			Assert::IsTrue(vector != vectorNotEqual_Y, L"Vectors should not be equal.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorIndex_Test)
		{
			Vec2f vector = { 2.0f, -3.0f };

			Assert::AreEqual(2.0f, vector[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(-3.0f, vector[1], L"Wrong value.", LINE_INFO());

			vector[0] = 5.0f;
			vector[1] = 6.0f;

			Assert::AreEqual(5.0f, vector[0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(6.0f, vector[1], L"Wrong value.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operatorDireferent_value_Test)
		{
			Vec2f vector = { 0.0f, 0.0f };
			bool result = vector != 0.0f;
			Assert::IsFalse(result, L"vector should not be diferente of Zero", LINE_INFO());

			vector = { 0.0f, 1.0f };
			result = vector != 0.0f;
			Assert::IsTrue(result, L"vector should be diferente of Zero", LINE_INFO());

			vector = { 1.0f, 0.0f };
			result = vector != 0.0f;
			Assert::IsTrue(result, L"vector should be diferente of Zero", LINE_INFO());
		}

		TEST_METHOD(Vec2_orthogonalProjection_Test)
		{
			Vec2f u = { 4.0f, 3.0f };
			Vec2f v = { 1.0f, 2.0f };

			Vec2f* result = v.orthogonalProjection(u);
			Vec2f proof = result[0] + result[1];
			bool areEqual = u == proof;

			Assert::AreEqual(1.6f, result[0][0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(1.2f, result[0][1], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(2.4f, result[1][0], L"Wrong value.", LINE_INFO());
			Assert::AreEqual(1.8f, result[1][1], L"Wrong value.", LINE_INFO());

			Assert::IsTrue(areEqual, L"Vectors are not equal.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operator_Serialize)
		{
			Vec2f vector = { 4.0f, 3.0f };
			std::string expected("4,3");

			std::stringstream sstream;
			vector.serialize(sstream);
			std::string result = sstream.str();

			Assert::AreEqual(expected, result, L"Wrong Serialization.", LINE_INFO());
		}

		TEST_METHOD(Vec2_operator_Deserialize)
		{
			Vec2f vector = { 4.0f, 3.0f };

			std::stringstream sstream;
			vector.serialize(sstream);

			Vec2f result;
			result.deserialize(sstream);

			Assert::IsTrue(vector == result, L"Wrong Serialization.", LINE_INFO());
		}

	};
}