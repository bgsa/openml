#pragma once

#include "CppUnitTest.h"
#include <Point2D.h>

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
			static wstring ToString<Point2Df>(const Point2Df& coord) 
			{
				return L"Some string representing Point2D.";
			}

		}
	}
}
