#pragma once

#include <OpenML.h>
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace OpenML;

class Asserts 
{
public:

	template<typename T>
	static void isCloseEnough(T value, T compare, T epsilon, std::string message, const __LineInfo* lineInfo = nullptr)
	{
		const wchar_t* messageAswchar = std::wstring(message.begin(), message.end()).c_str();

		bool result = OpenML::isCloseEnough(value, compare, epsilon);

		Assert::IsTrue(result, messageAswchar, lineInfo);
	}

};