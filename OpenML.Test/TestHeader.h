#pragma once

#include "CppUnitTest.h"
#include <OpenML.h>
#include <MemoryAllocatorManager.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

namespace Microsoft 
{
	namespace VisualStudio 
	{
		namespace CppUnitTestFramework 
		{

			template<>
			static std::wstring ToString<Vec2f>(const Vec2f& vector)
			{
				return L"Some string representing Vector2D.";
			}

			template<>
			static std::wstring ToString<Vec3f>(const Vec3f& vector)
			{
				return L"Some string representing Vector3D.";
			}

			template<>
			static std::wstring ToString<Vec4f>(const Vec4f& vector)
			{
				return L"Some string representing Vector4D.";
			}

			template<>
			static std::wstring ToString<Mat2f>(const Mat2f& matrix)
			{
				return L"Some string representing Matrix2D.";
			}

			template<>
			static std::wstring ToString<Mat3f>(const Mat3f& matrix)
			{
				return L"Some string representing Matrix3D.";
			}

			template<>
			static std::wstring ToString<Mat4f>(const Mat4f& matrix)
			{
				return L"Some string representing Matrix4D.";
			}

			template<>
			static std::wstring ToString<Rectangle2Df>(const Rectangle2Df& rectangle)
			{
				return L"Some string representing Rectangle2D.";
			}

		}
	}
}
