/*
 * TestPlane3D.cpp
 *
 *  Created on: 05.10.2014
 *      Author: christoph
 */

#include "../TestInclude.h"

using namespace CrystalMesh;
using namespace Math;
using namespace Geometry;



// construction by point and normal
TEST(Plane3D, construction0){
	double const eps = 1e-9;
	auto const point = pointFromXYZ(0.0, 0.0, 3.0);
	auto const normal = vectorFromXYZ(3.0, 0.0, 0.0);

	auto const plane = planeFromPointAndNormal(point, normal);

	Vector3D exNormal = vectorFromXYZ(1.0, 0.0, 0.0);
	Point3D exPoint = pointFromXYZ(0.0, 0.0, 3.0);



	EXPECT_TRUE(almostEqual(exPoint, pointOnPlaneOf(plane), eps));
	EXPECT_TRUE(almostEqual(exNormal, normalOf(plane), eps));
}

// Define a plane by three points:
TEST(Plane3D, construction1){
	double const eps = 1e-6;
	auto const p0 = pointFromXYZ(1.0, 0.0, 0.0);
	auto const p1 = pointFromXYZ(1.0, 1.0, 0.0);
	auto const p2 = pointFromXYZ(1.0, 0.0, 1.0);

	auto const plane0 = planeFromThreePoints(p0, p1, p2);
	auto const exNormal = vectorFromXYZ(1.0, 0.0, 0.0);

	EXPECT_TRUE(almostEqual(exNormal, normalOf(plane0), eps));

	// opposide:
	EXPECT_TRUE(almostEqual(exNormal, normalOf(plane0), eps));
	auto const plane1 = planeFromThreePoints(p0, p2, p1);

	EXPECT_TRUE(almostEqual(-1*exNormal, normalOf(plane1), eps));

}


