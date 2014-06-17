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

