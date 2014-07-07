/*
 * Geometry Vector3D.cpp
 *
 *  Created on: 14.06.2014
 *      Author: christoph
 */

#include "Geometry.h"


namespace CrystalMesh{

	namespace Math{

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

		}
	}
}






