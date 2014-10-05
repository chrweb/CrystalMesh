/*
 * TestVector3D.cpp
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#include "../TestInclude.h"
#include <cstdlib>

using namespace CrystalMesh;
using namespace Math;
using namespace Geometry;



TEST(Vector3D, equality){
	Vector3D v00 = Vector3D::zero;
	Vector3D v01 = Vector3D::zero;

	Vector3D v10 = Vector3D::xAxis;

	EXPECT_TRUE(exactEqual(v00, v01));
	EXPECT_FALSE(exactEqual(v00, v10));

}


TEST(Vector3D, zero){
	Vector3D const & ref = Vector3D::zero;
	EXPECT_EQ(ref.mX, 0.0);
	EXPECT_EQ(ref.mY, 0.0);
	EXPECT_EQ(ref.mZ, 0.0);
}


TEST(Vector3D, xAxis){
	Vector3D const & ref = Vector3D::xAxis;
	EXPECT_EQ(ref.mX, 1.0);
	EXPECT_EQ(ref.mY, 0.0);
	EXPECT_EQ(ref.mZ, 0.0);
}


TEST(Vector3D, yAxis){
	Vector3D const & ref = Vector3D::yAxis;
	EXPECT_EQ(ref.mX, 0.0);
	EXPECT_EQ(ref.mY, 1.0);
	EXPECT_EQ(ref.mZ, 0.0);
}

TEST(Vector3D, zAxis){
	Vector3D const & ref = Vector3D::zAxis;
	EXPECT_EQ(ref.mX, 0.0);
	EXPECT_EQ(ref.mY, 0.0);
	EXPECT_EQ(ref.mZ, 1.0);
}

TEST(Vector3D, addition){
	auto const first = vectorFromXYZ(1.0, 2.0, 3.0);

	auto const sec = vectorFromXYZ(1.0, 2.0, 3.0);

	auto const res = first + sec;

	EXPECT_EQ(res.mX, 2.0);
	EXPECT_EQ(res.mY, 4.0);
	EXPECT_EQ(res.mZ, 6.0);
}
/**
 * Test a chained addition
 */
TEST(Vector3D, multAddition){
	auto const res = Vector3D::zero + Vector3D::xAxis + Vector3D::yAxis + Vector3D::zAxis;
	EXPECT_EQ(res.mX, 1.0);
	EXPECT_EQ(res.mY, 1.0);
	EXPECT_EQ(res.mZ, 1.0);

}


TEST(Vector3D, subtraction){
	auto const first = vectorFromXYZ(1.0, 2.0, 3.0);

	auto const sec = vectorFromXYZ(1.0, 2.0, 0.0);

	auto const res = first - sec;

	EXPECT_EQ(res.mX, 0.0);
	EXPECT_EQ(res.mY, 0.0);
	EXPECT_EQ(res.mZ, 3.0);
}

TEST(Vector3D,dotProd){
	auto const v0 = vectorFromXYZ(1.0, 2.0, 3.0);
	auto const v1 = vectorFromXYZ(4.0, 5.0, -1.0);
	double const result = dotProductOf(v0, v1);
	EXPECT_EQ(11.0, result);

}

TEST(Vector3D, xProd0){
	auto const res = crossProductOf(Vector3D::xAxis, Vector3D::yAxis);
	EXPECT_EQ(res.mX, 0.0);
    EXPECT_EQ(res.mY, 0.0);
    EXPECT_EQ(res.mZ, 1.0);
}

TEST(Vector3D, squaredAbs){
	// squared
	auto const vec = vectorFromXYZ(1.0, 2.0, 3.0);
	double const sq = 14.0;

	EXPECT_EQ(sq, squaredOf(vec));

	// abs
	EXPECT_DOUBLE_EQ(squareRootOf(sq), absoluteOf(vec));

}


