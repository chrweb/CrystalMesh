/*
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#ifndef CRYSTALMESH_MATH_H_
#define CRYSTALMESH_MATH_H_
#include <stdint.h>

namespace Mathbox{

	extern double const PositivInf;
	extern double const NegativInf;
	extern double const NaN;
        
        /**
         * Double comparism by units in the last place,
         * see http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
         * @param a0
         * @param a1
         * @param aULP
         * @return 
         */
        bool const almostEqual(double a0, double a1, uint64_t aULP);
        
        uint64_t const diffInUlps(double const a, double const b);
        
	bool const isFiniteNumber( double aNumber);

	double const squared(double const aScalar);

	double const squareRootOf( double const aScalar);

	double const reciprocalOf(double const aScalar);

	double const absoluteOf(double const aScalar);
       
        /**
         * 
         * @param aScalar: a nonzero number
         * @return 0 if argument is 0, -1 if argument < 0, 1 if argument >0
         */
        double const signumOf(double const aScalar);
        
        bool const isWithin(double const aLower, double const value,  double const aUpper);
        
        double const minimumOf(double const a0, double const a1);
}

#include "Geometry.h"


#endif /* CRYSTALMESH_MATH_H_ */
