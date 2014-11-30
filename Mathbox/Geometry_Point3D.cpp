/*
 * Geometry Point.cpp
 *
 *  Created on: 20.06.2014
 *      Author: christoph
 */

#include  "Geometry.h"
#include  "Mathbox.h"

namespace Mathbox {

	namespace Geometry {

		Point3D const Point3D::zero = {0.0, 0.0, 0.0};

		// May different platforms have different descriptions fir NaN?
                #include <math.h>
		#define CM_NAN NAN

		Point3D const Point3D::NaN = {CM_NAN, CM_NAN, CM_NAN};

		bool const exactEqual(Point3D const & a0, Point3D const & a1){
			return exactEqual(vectorTo(a0), vectorTo(a1));
		}

		bool const almostEqual(Point3D const & a0, Point3D const & a1, uint64_t aDiffFromZeroInULP){
			return Mathbox::almostEqual(distanceBetween(a0, a1), 0.0, aDiffFromZeroInULP);
		}
                
                bool const inLexicographicalOrder(Point3D const & aPoint0, Point3D const & aPoint1){
                    if (aPoint0.mX < aPoint1.mX)
                        return true;
                    
                    if (aPoint0.mY < aPoint1.mY)
                        return true;
                    
                    if (aPoint0.mZ < aPoint1.mZ)
                        return true;
                    
                    return false;
                }


		Point3D const pointAt(Vector3D const & aVec){
			return reinterpret_cast<Point3D const&>(aVec);
		}

		Point3D const pointFromXYZ( double aX, double aY, double aZ){
			Point3D const  result = {aX, aY, aZ};
			return result;
		}

		double const distanceBetween(Point3D const & a0, Point3D const & a1){
			return absoluteOf(vectorBetween(a0, a1));
		}

		double const squaredDistanceBetween(Point3D const & a0, Point3D const & a1){
			return squaredOf(vectorBetween(a0, a1));
		}

		Point3D const operator + (Point3D const & aPoint, Vector3D const & aVec){
			return pointFromXYZ(
					aPoint.mX + aVec.mX,
					aPoint.mY + aVec.mY,
					aPoint.mZ + aVec.mZ);
		}


		Point3D const operator - (Point3D const & aPoint, Vector3D const & aVec){
			return pointFromXYZ(
									aPoint.mX - aVec.mX,
									aPoint.mY - aVec.mY,
									aPoint.mZ - aVec.mZ);
		}


		Point3D const pointFromXY0(double aX, double aY){
			return pointFromXYZ(aX, aY, 0.0);
		}



	}  // namespace Geometry
}  // namespace CrystalMesh

