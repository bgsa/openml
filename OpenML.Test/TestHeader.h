#pragma once

#include "CppUnitTest.h"
#include <OpenML.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace Microsoft 
{
	namespace VisualStudio 
	{
		namespace CppUnitTestFramework 
		{

			template<>
			static wstring ToString<Vec2f>(const Vec2f& coord)
			{
				return L"Some string representing Vector2D.";
			}

			template<>
			static wstring ToString<Vec3f>(const Vec3f& coord)
			{
				return L"Some string representing Vector3D.";
			}

			template<>
			static wstring ToString<Vec4f>(const Vec4f& coord)
			{
				return L"Some string representing Vector4D.";
			}

			template<>
			static wstring ToString<Mat2f>(const Mat2f& coord)
			{
				return L"Some string representing Matrix2D.";
			}

			template<>
			static wstring ToString<Mat3f>(const Mat3f& coord)
			{
				return L"Some string representing Matrix3D.";
			}

			template<>
			static wstring ToString<Mat4f>(const Mat4f& coord)
			{
				return L"Some string representing Matrix4D.";
			}

			template<>
			static wstring ToString<Point2Df>(const Point2Df& coord) 
			{
				return L"Some string representing Point2D.";
			}

			template<>
			static wstring ToString<Point3Df>(const Point3Df& coord)
			{
				return L"Some string representing Point3D.";
			}

		}
	}
}
