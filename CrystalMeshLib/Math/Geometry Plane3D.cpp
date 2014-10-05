/*
 * Geometry Plane3D.cpp
 *
 *  Created on: 05.10.2014
 *      Author: christoph
 */

#include "CrystalMesh Math.h"
#include "Geometry.h"
namespace CrystalMesh{

	namespace Math{

		namespace Geometry{

			Plane3D const plane3DFromPointAndNormal(Point3D const & aPoint, Vector3D const & aNormal){
				Plane3D result;
				result.mOrgToPoint = distanceBetween(aPoint, Point3D::zero);
				result.mOrtho = normalized(aNormal);
				return result;
			}


			Plane3D const plane3DFromThreePoints(Point3D const & a0, Point3D const & a1, Point3D const a2){
				auto const v0 = vectorBetween(a1, a0);
				auto const v1 = vectorBetween(a2, a1);
				return plane3DFromPointAndNormal(a0, crossProductOf(v0, v1));
			}




		}
	}
}


