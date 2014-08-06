/*
 * CrystalMesh Math.h
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#ifndef CRYSTALMESH_MATH_H_
#define CRYSTALMESH_MATH_H_


namespace CrystalMesh{

	namespace Math{

		extern double const PositivInf;
		extern double const NegativInf;
		extern double const NaN;

		bool const isFiniteNumber( double aNumber);

		double const squared(double const aSkalar);

		double const squareRootOf( double const aSkalar);

	}


}



#endif /* CRYSTALMESH_MATH_H_ */
