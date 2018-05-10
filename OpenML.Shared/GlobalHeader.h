#pragma once

#ifdef WINDOWS
	#ifdef API_IMPORT
		#define API_INTERFACE __declspec(dllimport)		
	#else
		#ifdef API_EXPORT
			#define API_INTERFACE __declspec(dllexport)
		#endif
	#endif	
#else
	#define API_INTERFACE __attribute__((visibility("default")))
#endif 

#include <cmath>
#include <iostream>
#include <sstream>
#include <cassert>

namespace OpenML 
{
	template <typename T>
	class Vec2;
	template <typename T>
	class Vec3;
	template <typename T>
	class Vec4;

	template <typename T>
	class Mat;
	template <typename T>
	class Mat2;
	template <typename T>
	class Mat3;
	template <typename T>
	class Mat4;

	template <typename T>
	class Quat;

	template <typename T>
	class Point2D;
	template <typename T>
	class Point3D;
}

using namespace std;