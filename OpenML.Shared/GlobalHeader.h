#pragma once

#ifdef WINDOWS
	#ifdef API_IMPORT
		#define API_INTERFACE __declspec(dllimport)		
	#else
		#ifdef API_EXPORT
			#define API_INTERFACE __declspec(dllexport)
		#else
			#define API_INTERFACE
		#endif
	#endif	
#else
	#ifdef API_IMPORT
		#define API_INTERFACE __attribute__((visibility("hidden")))
	#else
		#ifdef API_EXPORT
			#define API_INTERFACE __attribute__((visibility("default")))
		#else
			#define API_INTERFACE
		#endif
	#endif	
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
	class Vec2List;
	template <typename T>
	class Vec3List;
	
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
	class BinaryTree;
	template <typename T>
	class BinaryTreeNode;

	template <typename T>
	class Line2D;
	template <typename T>
	class Line3D;
	template <typename T>
	class Plane3D;
	template <typename T>
	class Triangle2D;
	template <typename T>
	class Circle2D;
	template <typename T>
	class AABB;
	template <typename T>
	class Sphere;
	template <typename T>
	class Rectangle2D;

}