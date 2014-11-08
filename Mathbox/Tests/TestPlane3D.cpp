/*
 * TestPlane3D.cpp
 *
 *  Created on: 05.10.2014
 *      Author: christoph
 */

#include "../TestIncludes.h"

using namespace Mathbox;
using namespace Geometry;



// construction by point and normal
TEST(Plane3D, construction0){
	double const eps = 1e-9;
	auto const point = pointFromXYZ(0.0, 0.0, 3.0);
	auto const normal = vectorFromXYZ(3.0, 0.0, 0.0);

	auto const plane = planeFromPointAndNormal(point, normal);

	Point3D exPoint = pointFromXYZ(0.0, 0.0, 3.0);
	Vector3D exNormal = vectorFromXYZ(1.0, 0.0, 0.0);

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


namespace{

	class PlaneProjection
	: public ::testing::Test{

	private:


	protected:

		Plane3D  plane0;
		Plane3D  plane1;

		virtual void SetUp(){
			auto const p0 = pointFromXYZ(1.0, 0.0, 0.0);
			auto const p1 = pointFromXYZ(1.0, 1.0, 0.0);
			auto const p2 = pointFromXYZ(1.0, 0.0, 1.0);

			plane0 = planeFromThreePoints(p0, p1, p2);
			plane1 = planeFromThreePoints(p0, p2, p1);
		}


	};
}


TEST_F(PlaneProjection, closestPoint){
	double const eps = 1e-6;

	// over plane
	auto const q0 = pointFromXYZ(1.2, 2.7, 3.14 );

	//under plane
	auto const q1 = pointFromXYZ(0.0, 2.7, 3.14);

	//on plane
	auto const q2 = pointFromXYZ(1.0, 2.0, 4.0);

	auto const c0 = closestPoint(plane0, q0);
	auto const c1 = closestPoint(plane0, q1);
	auto const c2 = closestPoint(plane0, q2);

	//expected:
	auto const ex0 = pointFromXYZ(1.0, 2.7, 3.14);
	auto const ex1 = ex0;
	auto const ex2 = q2;

	EXPECT_TRUE(almostEqual(ex0, c0, eps));
	EXPECT_TRUE(almostEqual(ex1, c1, eps));
	EXPECT_TRUE(almostEqual(ex2, c2, eps));
}

TEST_F(PlaneProjection, PointPlaneRelation){
	double const eps = 1e-6;

	// over plane
	auto const q0 = pointFromXYZ(1.2, 2.7, 3.14 );

	//on plane
	auto const q1 = pointFromXYZ(1.0, 2.0, 4.0);

	//under plane
	auto const q2 = pointFromXYZ(0.0, 2.7, 3.14);


	// signed dists:
	auto const posDist0 = signedDistanceBetween(plane0, q0);
	auto const negDist0 = signedDistanceBetween(plane0, q2);

	// expect
	double const exPosDist0 = 0.2;
	double const exNegDist0 = -1.0;

	EXPECT_TRUE(almostEqual(exPosDist0, posDist0, eps));
	EXPECT_TRUE(almostEqual(exNegDist0, negDist0, eps));

	// up side down:
	// signed dists:
	auto const posDist1 = signedDistanceBetween(plane1, q2);
	auto const negDist1 = signedDistanceBetween(plane1, q0);

	// expect
	double const exPosDist1 = 1.0;
	double const exNegDist1 = -0.2;

	EXPECT_TRUE(almostEqual(exPosDist1, posDist1, eps));
	EXPECT_TRUE(almostEqual(exNegDist1, negDist1, eps));

	//Predicates:
	auto const overPlane = pointPlaneProjection(plane0, q0, eps);
	auto const onPlane = pointPlaneProjection(plane0, q1, eps);
	auto const underPlane = pointPlaneProjection(plane0, q2, eps);

	EXPECT_EQ(PointToPlaneProjection::overPlane, overPlane);
	EXPECT_EQ(PointToPlaneProjection::onPlane, onPlane);
	EXPECT_EQ(PointToPlaneProjection::underPlane, underPlane);
}


