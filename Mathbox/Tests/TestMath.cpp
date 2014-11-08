/*
 * TestMath.cpp
 *
 *  Created on: 05.10.2014
 *      Author: christoph
 *
 *      Testing of some basic math functions
 */


#include "../TestIncludes.h"

using namespace Mathbox;


TEST(Math, SquareRoot){

	//rational >0
	EXPECT_EQ(2.0, squareRootOf(4.0));

	//irrational
	EXPECT_DOUBLE_EQ(1.4142135623730951, squareRootOf(2.0));

	//<0
	auto const img = squareRootOf(-4.0);
	EXPECT_FALSE(isFiniteNumber(img));
}


