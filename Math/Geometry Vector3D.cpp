/*
 * Geometry Vector3D.cpp
 *
 *  Created on: 14.06.2014
 *      Author: christoph
 */

#include "Geometry.h"

using namespace CrystalMesh::Math::Geometry;

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






