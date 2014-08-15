/*
 * Geometry Point.cpp
 *
 *  Created on: 20.06.2014
 *      Author: christoph
 */

#include  "Geometry.h"

namespace CrystalMesh {

	namespace Math {

		namespace Geometry {

			Point3D const Point3D::zero = {0.0, 0.0, 0.0};

			// May different platforms have different descriptions fir NaN?
            #include <math.h>
			#define CM_NAN NAN

			Point3D const Point3D::NaN = {CM_NAN, CM_NAN, CM_NAN};

			bool const exactEqual(Point3D const & a0, Point3D const & a1){
				return exactEqual(vectorTo(a0), vectorTo(a1));
			}

			Point3D const pointAt(Vector3D const & aVec){
				return reinterpret_cast<Point3D const&>(aVec);
			}

			Point3D const point3DFromXYZ( double aX, double aY, double aZ){
				Point3D const  result = {aX, aY, aZ};
				return result;
			}




		}  // namespace Geometry



	}  // namespace Math



}  // namespace CrystalMesh

