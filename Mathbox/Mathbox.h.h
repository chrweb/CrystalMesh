/*
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#ifndef CRYSTALMESH_MATH_H_
#define CRYSTALMESH_MATH_H_


namespace Mathbox{

	extern double const PositivInf;
	extern double const NegativInf;
	extern double const NaN;

	// ToDo: ULP-issue
	bool const almostEqual(double a0, double a1, double eps);

	bool const isFiniteNumber( double aNumber);

	double const squared(double const aScalar);

	double const squareRootOf( double const aScalar);

	double const reciprocalOf(double const aScalar);

	double const absoluteOf(double const aScalar);
}



#endif /* CRYSTALMESH_MATH_H_ */
