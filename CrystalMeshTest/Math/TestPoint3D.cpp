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

			p0 = point3DFromXYZ(0.0, 0.0, 0.0);
			p1 = point3DFromXYZ(0.3, -1.7, 2.1);
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

	auto const q0 = point3DFromXYZ(1.0, 1.0, 1.0);
	auto const p0 = Point3D::zero;
	auto const p1 = point3DFromXYZ(1.0, 0.0, 0.0);
	auto const p2 = point3DFromXYZ(-1.0, 1.0, 1.0);

	EXPECT_DOUBLE_EQ(squareRootOf(3) ,distanceBetween(q0, p0));
	EXPECT_DOUBLE_EQ(squareRootOf(2) ,distanceBetween(q0, p1));
	EXPECT_DOUBLE_EQ(2.0 ,distanceBetween(q0, p2));

}

TEST(POINT, vectorBetween){

	auto const p0 = point3DFromXYZ(1.0, 1.0, 1.0);
	auto const p1 = point3DFromXYZ(1.0, 0.0, 0.0);
	auto const p2 = point3DFromXYZ(-1.0, 1.0, 1.0);

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








