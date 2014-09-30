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








