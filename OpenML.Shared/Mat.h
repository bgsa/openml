#pragma once

#include "GlobalHeader.h"
#include <iomanip>

namespace OpenML
{
	template <typename T>
	class Mat
	{
	protected:

		string toString(T* values, int size, int precision = 4)
		{
			string content;
			size_t total = (int)(size * size);

			for (size_t i = 0; i < total; i++)
			{
				stringstream stream;
				stream << fixed << setprecision(precision) << values[i];
				string numberAsString = stream.str();

				bool isPositive = values[i] >= 0;

				if (isPositive)
					numberAsString = " " + numberAsString;

				content += " " + numberAsString + " ";

				if ((i + 1) % size == 0)
					content += '\n';
			}

			return content;
		}

	};

	template class Mat<int>;
	template class Mat<float>;
	template class Mat<double>;

}