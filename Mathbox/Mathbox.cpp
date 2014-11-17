/*
 * CrystalMesh Math.cpp
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#include "Mathbox.h"
#include "Geometry.h"
#include <math.h>
#include <stdint.h>
#include "../Toolbox/Checks.h"
#include <stdlib.h>

namespace Mathbox{

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

	double const absoluteOf(double const aScalar){
		return fabs(aScalar);
	}
        
        bool const almostEqual(double a0, double a1, uint64_t aULP){     
             if (a0 == a1)
                 return true;
             
             auto const diff = diffInUlps(a0, a1);
             
             if (diff<= aULP)
                 return true;
             
             return false;
         }
         
         
//          uint64_t const diffInUlps(double a0, double a1){
//             MUST_BE(sizeof(double)== sizeof(uint64_t));
//             
//             auto  a0AsInt = *reinterpret_cast<int64_t const *>(&a0);
//             
//             auto a1AsInt = *reinterpret_cast<int64_t const *>(&a1);
//             
//             // determine absolute
//	       auto const diffInInts = a1AsInt - a0AsInt;
//             
//             return diffInInts; 
//         }
        
        
        
        namespace{
            
            union Double{
                   double mD;
                   int64_t mInt;
                
            };
            
            Double const genDouble(double aNumber){
                Double result;
                result.mD = aNumber;
                return result;
            }
            
            // get integer representation by Union:
            // This implementation does not work!
            uint64_t diffUlpsUnion(double const a, double const b){
                
                Double A = genDouble(a);
                Double B = genDouble(b);
                
                if(A.mInt < 0) 
                {
                    A.mInt = 0x8000000000000000ull - A.mInt;
		}
		
		if(B.mInt < 0) 
                {
                    B.mInt = 0x8000000000000000ull - B.mInt;
		}

                // diff in ULPs
                auto const diff = A.mInt - B.mInt;
                // absolute of
                
                if (diff < 0) return -diff;
                return diff;
            } 
            
            //By reinterpret
            uint64_t diffUlpsReint(double  a, double  b){
                
                int64_t aAsInt = *reinterpret_cast<int64_t*>(&a);
                int64_t bAsInt = *reinterpret_cast<int64_t*>(&b);
                if(aAsInt < 0) 
                {
                    aAsInt = 0x8000000000000000ull - aAsInt;
		}
		
		if(bAsInt < 0) 
                {
                    bAsInt = 0x8000000000000000ull - bAsInt;
		}

                // diff in ULPs
                auto const diff = aAsInt - bAsInt;
                // absolute of
                
                if (diff < 0) 
                    return -diff;
                
                return diff;
            }           
        }
       
         
         /* Varius literature for ULP issues::
          *   http://web.mit.edu/hyperbook/Patrikalakis-Maekawa-Cho/node46.html
          *   http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
          */
         
        uint64_t const diffInUlps( double const  a, double const  b) 
        {
            //return diffUlpsReint(a, b);
            return diffUlpsUnion(a,b);
        }
          
         
                        
}





