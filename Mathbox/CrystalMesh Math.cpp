/*
 * CrystalMesh Math.cpp
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#include "CrystalMesh Math.h"
#include "Geometry.h"
#include <math.h>
#include "../Misc/Checks.h"

namespace CrystalMesh{

	namespace Math{


		 double const NaN =  NAN;
		 double const PositivInf = INFINITY;
		 double const NegativInf = -INFINITY;

		 bool const almostEqual(double a0, double a1, double eps){
			 SHOULD_BE(eps>=0);
			 return absoluteOf(a0-a1)<=eps;
		 }

		 double const squareRootOf( double const aScalar){
			 SHOULD_BE(aScalar>=0.0);
			 return sqrt(aScalar);
		 }

		 double const reciprocalOf(double const aScalar){
			 return 1/aScalar;
		 }

		double const squared(double const aSkalar){
			return aSkalar*aSkalar;
		}


		bool const isFiniteNumber(double const aScalar)
		{
			return NegativInf	 < aScalar && aScalar < PositivInf;
		}

		double const absoluteOf(double const aScalar){
			return fabs(aScalar);
		}



	}



}





