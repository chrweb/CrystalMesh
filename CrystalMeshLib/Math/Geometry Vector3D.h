/*
 * Geometry Vector3D.h
 *
 *  Created on: 14.06.2014
 *      Author: christoph
 */

#ifndef GEOMETRY_VECTOR3D_H_
#define GEOMETRY_VECTOR3D_H_

namespace CrystalMesh{

	namespace Math{

		namespace Geometry{

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
			bool const almostEqual(Vector3D const & a0, Vector3D const & a1, double const aDelta);

			double const absoluteOf(Vector3D const & aVec);

			double const squaredOf(Vector3D const & aVec);

			Vector3D const operator+ (Vector3D const & aLeftOp, Vector3D const & aRightOp);

			Vector3D const operator- (Vector3D const & aLeftOp, Vector3D const & aRightOp);

			Vector3D const operator* (double const aScalar, Vector3D const & aVec);

			Vector3D const operator* (Vector3D const & aVec, double const aScalar);




			/**
			 * length may differ by length DeltaL
			 */
			//bool const almostEqual(Vector3D const & a0, Vector3D const & a1, double const aDeltaL);

			Vector3D const normalized(Vector3D const & aVec);

			Vector3D const vectorTo(Point3D const & aPoint);

			// return a vector from origin to destination
			Vector3D const vectorBetween(Point3D const & aPdest, Point3D const & aPorg);

			Vector3D const vectorFromXYZ( double const & aX, double const & aY, double const & aZ);

			Vector3D const vectorFromXY0( double const & aX, double const & aY);

			Vector3D const VectorFromXY0(Vector2D const & aVec);

			Vector3D const crossProductOf(Vector3D const & a0, Vector3D const & a1);

			double const dotProductOf(Vector3D const & a0, Vector3D const & a1);

			Vector3D const transformed(Matrix4x3 const & aTrafo, Vector3D const & aVec);




		}


	}


}






#endif /* GEOMETRY_VECTOR3D_H_ */
