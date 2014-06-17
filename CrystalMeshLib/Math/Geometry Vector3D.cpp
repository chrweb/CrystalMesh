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

		}
	}
}






