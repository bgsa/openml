#pragma once

namespace OpenML 
{

	enum class VerticalOrientation
	{
		LEFT = -1,
		NONE = 0,
		RIGHT = 1
	};

	enum class HorizontalOrientation
	{
		UP = -1,
		NONE = 0,
		DOWN = 1
	};

	class Orientation
	{
	public:
		HorizontalOrientation horizontalOrientation;
		VerticalOrientation verticalOrientation;
	};

}