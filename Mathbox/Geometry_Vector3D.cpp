/*
 * Geometry Vector3D.cpp
 *
 *  Created on: 14.06.2014
 *      Author: christoph
 */

#include "Geometry.h"
#include "Mathbox.h"


namespace Mathbox{


	namespace Geometry{

		/**
		 * statics
		 */


		// May different platforms have different descriptions fir NaN?
		#include <math.h>
		#define CM_NAN NAN

		Vector3D const Vector3D::NaN = {CM_NAN, CM_NAN, CM_NAN};
		Vector3D const Vector3D::zero = { 0.0, 0.0, 0.0};
		Vector3D const Vector3D::xAxis = {1.0, 0.0, 0.0};
		Vector3D const Vector3D::yAxis = {0.0, 1.0, 0.0};
		Vector3D const Vector3D::zAxis = {0.0, 0.0, 1.0};

		Vector3D const operator+ (Vector3D const & aLeftOp, Vector3D const & aRightOp){

			Vector3D result = {
					aLeftOp.mX + aRightOp.mX,
					aLeftOp.mY + aRightOp.mY,
					aLeftOp.mZ + aRightOp.mZ};

			return result;
		}


		Vector3D const operator- (Vector3D const & aLeftOp, Vector3D const & aRightOp){

			Vector3D result = {
					aLeftOp.mX - aRightOp.mX,
					aLeftOp.mY - aRightOp.mY,
					aLeftOp.mZ - aRightOp.mZ};

			return result;
		}
                
                Vector3D const operator- (Vector3D const & aRhs){
                    Vector3D result = vectorFromXYZ(-aRhs.mX, -aRhs.mY, -aRhs.mZ);
                    return result;
                }
                
		Vector3D const vectorFromXYZ( double const & aX, double const & aY, double const & aZ){

			Vector3D result = {
			aX,
			aY,
			aZ
			};

			return result;
		}

		Vector3D const VectorFromXY0(Vector2D const & aVec){

			Vector3D result = { aVec.mX, aVec.mY, 0.0 };
			return result;
		}

		Vector3D const crossProductOf(Vector3D const & a0, Vector3D const & a1){
			Vector3D result = {
					a0.mY*a1.mZ - a0.mZ * a1.mY,
					a0.mZ*a1.mX - a0.mX * a1.mZ,
					a0.mX*a1.mY - a0.mY * a1.mX,
			};

			return result;
		}


		double const dotProductOf(Vector3D const & a0, Vector3D const & a1){
			return a0.mX*a1.mX + a0.mY * a1.mY + a0.mZ * a1.mZ;
		}

		bool const exactEqual(Vector3D const & a0, Vector3D const & a1){
			return a0.mX == a1.mX && a0.mY == a1.mY && a0.mZ == a1.mZ;
		}

		Vector3D const vectorTo(Point3D const & aPoint){
			return reinterpret_cast<Vector3D  const &>(aPoint);
		}

		Vector3D const normalized(Vector3D const & aVec){
			auto const abs = absoluteOf(aVec);
			return reciprocalOf(abs)*aVec;
		}

		double const absoluteOf(Vector3D const & aVec){
			return squareRootOf(squaredOf(aVec));
		}


		double const squaredOf(Vector3D const & aVec){
			return dotProductOf(aVec, aVec);
		}

		Vector3D const operator* (double const aScalar, Vector3D const & aVec){
			return vectorFromXYZ(
					aScalar*aVec.mX,
					aScalar*aVec.mY,
					aScalar*aVec.mZ);
		}

		Vector3D const operator* (Vector3D const & aVec, double const aScalar){
			return aScalar*aVec;
		}

		Vector3D const vectorBetween(Point3D const & aPdest, Point3D const & aPorg){
			return vectorFromXYZ(
					aPdest.mX- aPorg.mX,
					aPdest.mY- aPorg.mY,
					aPdest.mZ- aPorg.mZ
					);
		}


		bool const almostEqual(Vector3D const & a0, Vector3D const & a1, uint64_t aDiffInUlp){
			return
					Mathbox::almostEqual(a0.mX, a1.mX, aDiffInUlp) &&
					Mathbox::almostEqual(a0.mY, a1.mY, aDiffInUlp) &&
					Mathbox::almostEqual(a0.mZ, a1.mZ, aDiffInUlp);
		}
                
                double const tripleProductOf(Vector3D const & aV0, Vector3D const & aV1, Vector3D const & aV2){
                    auto const cross = crossProductOf(aV0, aV1);
                    auto const dotProd =  dotProductOf(cross, aV2);
                    return dotProd;
                }
                
                Vector3D const normalizedCrossProductOf(Vector3D const & a0, Vector3D const & a1){
                    auto const cross = crossProductOf(a0, a1);
                    return normalized(cross);
                }
                
                bool isValidDirection(Vector3D const & aVector){
                    return isWithin(
				1.11875110968003096e-154 * 1.11875110968003096e-154,
				squaredOf(aVector),
				1.3407807929942598e154 * 1.3407807929942598e154
			);
                
                }


	}
}






