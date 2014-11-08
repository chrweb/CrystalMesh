/*
 * Geometry Plane3D.cpp
 *
 *  Created on: 05.10.2014
 *      Author: christoph
 */

#include "Mathbox.h.h"
#include "Geometry.h"
namespace Mathbox{

	namespace Geometry{

		Plane3D const planeFromPointAndNormal(Point3D const & aPoint, Vector3D const & aNormal){
			Plane3D result;
			result.mPoint = aPoint;
			result.mNormal = normalized(aNormal);
			return result;
		}


		Plane3D const planeFromThreePoints(Point3D const & a0, Point3D const & a1, Point3D const a2){
			auto const v0 = vectorBetween(a1, a0);
			auto const v1 = vectorBetween(a2, a1);
			return planeFromPointAndNormal(a0, crossProductOf(v0, v1));
		}

		Point3D const pointOnPlaneOf(Plane3D const & aPlane){
			return aPlane.mPoint;
		}

		Vector3D const normalOf(Plane3D const & aPlane){
			return aPlane.mNormal;
		}

		Point3D const closestPoint(Plane3D const & aPlane, Point3D const & aPoint){
			return aPoint- signedDistanceBetween(aPlane, aPoint)*aPlane.mNormal;
		}

		// Determines, if Point above, under or on plane.
		PointToPlaneProjection const pointPlaneProjection(Plane3D const & aPlane, Point3D const & aPoint, double const aEps){
			auto const dist = signedDistanceBetween(aPlane, aPoint);
			if (Mathbox::almostEqual(0.0, dist, aEps)){
				return PointToPlaneProjection::onPlane;
			}

			if (dist>0)
				return PointToPlaneProjection::overPlane;

			return PointToPlaneProjection::underPlane;
		}

		double const signedDistanceBetween(Plane3D const & aPlane, Point3D const & aPoint){
			return dotProductOf(vectorBetween(aPoint, aPlane.mPoint), aPlane.mNormal);
		}

		double const distanceBetween(Plane3D const & aPlane, Point3D const & aPoint){
			return Mathbox::absoluteOf(signedDistanceBetween(aPlane, aPoint));
		}
	}	
}


