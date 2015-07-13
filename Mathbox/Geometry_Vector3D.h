/*
 * Geometry Vector3D.h
 *
 *  Created on: 14.06.2014
 *      Author: christoph
 */

#ifndef GEOMETRY_VECTOR3D_H_
#define GEOMETRY_VECTOR3D_H_

#include "Geometry.h"


namespace Mathbox{

	namespace Geometry{

		struct Vector3D;
		struct Vector3D;	
                struct Point3D;
		struct Vector2D;
		struct Matrix4x3;

		/**
		* all components bitwise identical
		*/
		bool const exactEqual(Vector3D const & a0, Vector3D const & a1);

		/**
		 * Vector my differ by delta componentwise
		 */
		bool const almostEqual(Vector3D const & a0, Vector3D const & a1, uint64_t aDiffInUlp);
                
                bool isValidDirection(Vector3D const & aVector);

		double const absoluteOf(Vector3D const & aVec);

		double const squaredOf(Vector3D const & aVec);
                
                double const dotProductOf(Vector3D const & a0, Vector3D const & a1);
                
		Vector3D const operator+ (Vector3D const & aLeftOp, Vector3D const & aRightOp);

		Vector3D const operator- (Vector3D const & aLeftOp, Vector3D const & aRightOp);
                
                Vector3D const operator- (Vector3D const & aRhs);

		Vector3D const operator* (double const aScalar, Vector3D const & aVec);

		Vector3D const operator* (Vector3D const & aVec, double const aScalar);

		Vector3D const normalized(Vector3D const & aVec);

		Vector3D const vectorTo(Point3D const & aPoint);

		// return a vector from origin to destination
		Vector3D const vectorBetween(Point3D const & aPdest, Point3D const & aPorg);

		Vector3D const vectorFromXYZ( double const & aX, double const & aY, double const & aZ);

		Vector3D const vectorFromXY0( double const & aX, double const & aY);

		Vector3D const VectorFromXY0(Vector2D const & aVec);

		Vector3D const crossProductOf(Vector3D const & a0, Vector3D const & a1);
                
                Vector3D const normalizedCrossProductOf(Vector3D const & a0, Vector3D const & a1);

		

		Vector3D const transformed(Matrix4x3 const & aTrafo, Vector3D const & aVec);
                

                
                double const tripleProductOf(Vector3D const & aV0, Vector3D const & aV1, Vector3D const & aV2);

	}
}






#endif /* GEOMETRY_VECTOR3D_H_ */
