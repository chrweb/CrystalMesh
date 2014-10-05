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




	}



}





