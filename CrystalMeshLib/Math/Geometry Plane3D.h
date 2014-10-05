/*
 * Geometry Plane3D.h
 *
 *  Created on: Oct 4, 2014
 *      Author: christoph
 */
#pragma once


namespace CrystalMesh{

	namespace Math{

		namespace Geometry {

			struct Plane3D;
			struct Point3D;
			struct Vector3D;

			enum struct PointToPlaneProjection{
							onPlane,
							overPlane,
							underPlane
						};

			// Determines, if Point above, under or on plane. Eps defines a distance delta to evaluate on-plane-situation
			PointToPlaneProjection const pointPlaneProjection(Plane3D const & aPlane, Point3D const & aPoint, double const aEps);

			double const signedDistanceBetween(Plane3D const & aPlane, Point3D const & aPoint);

			double const distanceBetween(Plane3D const & aPlane, Point3D const & aPoint);

			Plane3D const planeFromPointAndNormal(Point3D const & aPoint, Vector3D const & aNormal);

			Plane3D const planeFromThreePoints(Point3D const & a0, Point3D const & a1, Point3D const a2);

			// Returns closed (i.e projected) point on plane.
			Point3D const closestPoint(Plane3D const & aPlane, Point3D const & aPoint);

			Point3D const pointOnPlaneOf(Plane3D const & aPlane);

			Vector3D const normalOf(Plane3D const & aPlane);

		}  // namespace Geometry
	}

}
