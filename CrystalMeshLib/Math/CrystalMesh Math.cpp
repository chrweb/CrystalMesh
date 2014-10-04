/*
 * CrystalMesh Math.cpp
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#include "CrystalMesh Math.h"
#include "Geometry.h"
#include <math.h>

namespace CrystalMesh{

	namespace Math{


		 double const NaN =  NAN;
		 double const PositivInf = INFINITY;
		 double const NegativInf = -INFINITY;

		 double const squareRootOf( double const aSkalar){
			 return sqrt(aSkalar);
		 }

		 double const reciprocalOf(double const aScalar){
			 return 1/aScalar;
		 }

		double const squared(double const aSkalar){
			return aSkalar*aSkalar;
		}



	}



}





