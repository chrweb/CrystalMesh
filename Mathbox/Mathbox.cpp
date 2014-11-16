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
            
            uint64_t diffUlpsUnion(double const a, double const b){
                Double A = genDouble(a);
                Double B = genDouble(b);
                
                auto const diff = A.mInt - B.mInt;
                
                if (diff < 0) return -diff;
                return diff;
            }
            
            
        
        
        }
        
        
         uint64_t diffInUlps(
			double const & a,
			double const & b
		) {
             auto const result = diffUlpsUnion(a, b);
             return result;
         }
          
//        uint64_t diffInUlps(
//			double const & a,
//			double const & b
//		) {
//			// Nach dem IEEE754-Standard lassen sich die Bitmuster aller Gleitkommazahlen sortieren, indem man sie als
//			//	Ganzzahlen in Einerkomplementschreibweise interpretiert. Dadurch lässt sich bestimmen, wie viele mögliche
//			//	Gleitkommazustände zwischen den Zahlen liegen.
//
//			// Die 'double's zu 64-Bit-Integern im Einerkomplement konvertieren. Da Visual C++ nicht so strenge Aliasing-Regeln
//			//	wie GCC hat, ist dies via 'reinterpret_cast<>()' am schnellsten.
//			auto aAsInt = reinterpret_cast<int64_t const &>(a);
//			if(aAsInt < 0) 
//                        {
//				aAsInt = 0x8000000000000000ull - aAsInt;
//			}
//			auto bAsInt = reinterpret_cast<int64_t const &>(b);
//			if(bAsInt < 0) 
//                        //{
//			//	bAsInt = 0x8000000000000000ull - bAsInt;
//			//}
//
//			// Absolutwert berechnen.
//			auto const differenceInULPs = bAsInt - aAsInt;
//			return (0 > differenceInULPs) ? -differenceInULPs : differenceInULPs;
//		}
          
         
//         uint64_t const diffInUlps(double a0, double a1){
//             MUST_BE(sizeof(double)== sizeof(uint64_t));
//             
//             auto  a0AsInt = *reinterpret_cast<int64_t const *>(&a0);
//             
//             //int64_t  a0AsInt = *(int64_t*)(&a0);
//             
//             
//             if(a0AsInt < 0) 
//             {
//		a0AsInt = 0x8000000000000000ull - a0AsInt;
//             }
//             
//             auto a1AsInt = *reinterpret_cast<int64_t const *>(&a1);
//             //int64_t a1AsInt = *(int64_t*)(&a1);
//             
//	     
//             if(a1AsInt < 0) 
//             {
//                a1AsInt = 0x8000000000000000ull - a1AsInt;
//             }
//             
//
//             // determine absolute
//	     auto const diffInInts = a1AsInt - a0AsInt;
//             
//             if (diffInInts < 0){
//                 return -diffInInts;
//             }
//             
//             return diffInInts;
//         }
         
#include<assert.h>
        int diffInUlps(float A, float B)
        {

            assert(sizeof(float) == sizeof(int));

           
            int intDiff = abs(*(int*)&A - *(int*)&B);

            return intDiff;

        }
        
         int diffInUlpsD(double A, double B){
             int intDiff = abs(*(int*)&A - *(int*)&B);

            return intDiff;
         }
                        
}





