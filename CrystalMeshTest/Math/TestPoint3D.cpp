/*
 * TestPoint3D.cpp
 *
 *  Created on: 06.08.2014
 *      Author: christoph
 */



#include "../TestInclude.h"

using namespace CrystalMesh;
using namespace Math;
using namespace Geometry;

namespace{

	class PointTester
	: public ::testing::Test
	{
	protected:

		Point3D p0;
		Point3D p1;
		Vector3D v1;
		double delta;

	public:

		virtual void SetUp(){

			p0 = pointFromXYZ(0.0, 0.0, 0.0);
			p1 = pointFromXYZ(0.3, -1.7, 2.1);
			v1 = vectorFromXYZ(0.3, -1.7, 2.1);
			delta = 0.1;

		}
	};

}



TEST_F(PointTester, zero){
	EXPECT_TRUE(exactEqual(p0, Point3D::zero));
}

TEST_F(PointTester, exactEqual){
	EXPECT_TRUE(exactEqual(p1, p1));
	auto differ = p1;
	differ.mX+=delta;
	EXPECT_FALSE(exactEqual(differ, p1));
}

TEST_F(PointTester, toVector){
	auto const point = pointAt(v1);
	EXPECT_TRUE(exactEqual(point, p1));
}

TEST(Point, distance){

	auto const q0 = pointFromXYZ(1.0, 1.0, 1.0);
	auto const p0 = Point3D::zero;
	auto const p1 = pointFromXYZ(1.0, 0.0, 0.0);
	auto const p2 = pointFromXYZ(-1.0, 1.0, 1.0);

	EXPECT_DOUBLE_EQ(squareRootOf(3) ,distanceBetween(q0, p0));
	EXPECT_DOUBLE_EQ(squareRootOf(2) ,distanceBetween(q0, p1));
	EXPECT_DOUBLE_EQ(2.0 ,distanceBetween(q0, p2));

}

TEST(POINT, vectorBetween){

	auto const p0 = pointFromXYZ(1.0, 1.0, 1.0);
	auto const p1 = pointFromXYZ(1.0, 0.0, 0.0);
	auto const p2 = pointFromXYZ(-1.0, 1.0, 1.0);

	auto const vec0 = vectorBetween(p1, p0);

	EXPECT_EQ(0.0, vec0.mX);
	EXPECT_EQ(-1.0, vec0.mY);
	EXPECT_EQ(-1.0, vec0.mZ);

	auto const vec1 = vectorBetween(p2, p1);

	EXPECT_EQ(-2.0, vec1.mX);
	EXPECT_EQ(1.0, vec1.mY);
	EXPECT_EQ(1.0, vec1.mZ);

	// backwards:
	auto const vec2 = vectorBetween(p1, p2);
	EXPECT_TRUE(exactEqual(vec2, -1*vec1));
}

// Test point - vector - addition and - substraction
TEST(Point, addition){
	double const eps = 1e-6;
	Point3D const p = pointFromXYZ(1.3, 1.2, 1.1);
	Vector3D const v0 = vectorFromXYZ(0.3, 0.2, 0.1);

	Point3D const result0 = p + v0;

	// expected result
	Point3D const ex0 = pointFromXYZ(1.6, 1.4, 1.2);
	EXPECT_TRUE(almostEqual(result0, ex0, eps));

	Vector3D const v1 = vectorFromXYZ(0.6, 0.4, 0.2);
	Point3D const result1 = result0 - v1;

	// expected result:
	Point3D const ex1 = pointFromXYZ(1.0, 1.0, 1.0);
	EXPECT_TRUE(almostEqual(result1, ex1, eps));

	// chained:
	Point3D const result2 = result1 - Vector3D::xAxis - Vector3D::yAxis + Vector3D::zAxis;
	Point3D const ex2 = pointFromXYZ(0.0, 0.0, 2.0);
	EXPECT_TRUE(almostEqual(ex2, result2, eps));
}











