#pragma once

#include "OpenML.h"

namespace OpenML
{

	template <typename T>
	class AlgorithmHorner
	{
	public:

		///<summary>
		///Divides a plynomial by a factor
		///x0 is the first value of coeficient values
		///x0 can be found using Newton, Secant, Bissection methods
		///Returns an array that contains the polynimal divided with 1 degree less
		///</summary>
		API_INTERFACE T* polynomialDivision(T x0, T* polynomial, int polynomialDegree);

		///<summary>
		///Find roots (zeros) from a plynomial P(x) = 0
		///x0 is the first value of coeficient values
		///x0 can be found using Newton, Secant, Bissection methods
		///Returns an array that contains the polynimal divided with 1 degree less
		///</summary>
		API_INTERFACE T* findRoots(T x0, T* polynomial, int polynomialDegree);

	};

}