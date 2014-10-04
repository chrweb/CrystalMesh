/*
 * Geometry Plane3D.h
 *
 *  Created on: Oct 4, 2014
 *      Author: christoph
 */
#pragma once


namespace CystalMesh{

	namespace Math{

		namespace Geometry {

			struct Plane3D;
			struct Point3D;
			struct Vector3D;

			Plane3D const plane3DFromPointAndNormal(Point3D const & aPoint, Vector3D const & aNormal);

			Plane3D const plane3DFromThreePoints(Point3D const & a0, Point3D const & a1, Point3D const a2);

			// Returns closed (i.e projected) point on plane.
			Point3D const closestPoint(Plane3D const & aPlane, Point3D const & aPoint);

		}  // namespace Geometry
	}

}
