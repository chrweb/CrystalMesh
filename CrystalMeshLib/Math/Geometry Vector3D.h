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

			Vector3D const operator+ (Vector3D const & aLeftOp, Vector3D const & aRightOp);

			Vector3D const operator- (Vector3D const & aLeftOp, Vector3D const & aRightOp);

			Vector3D const vectorBetween(Point3D const & aP0, Point3D const & aP1);

			Vector3D const vectorFromXYZ( double const & aX, double const & aY, double const & aZ);

			Vector3D const vectorFromXY0( double const & aX, double const & aY);

			Vector3D const VectorFromXY0(Vector2D const & aVec);

			Vector3D const crossProductOf(Vector3D const & a0, Vector3D const & a1);

			double const dotProductOf(Vector3D const & a0, Vector3D const & a1);

		}


	}


}






#endif /* GEOMETRY_VECTOR3D_H_ */
