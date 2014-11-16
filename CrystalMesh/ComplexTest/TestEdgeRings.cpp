/*
 * TestEdgeRings.cpp
 *
 *  Created on: 24.07.2014
 *      Author: christoph
 */

#include "TestInclude.h"
#include <cstdlib>
#include <algorithm>


using namespace CrystalMesh;
using namespace Subdiv3;

class EdgeRingTester
: public ::testing::Test{

private:


protected:

	CrystalMesh::Subdiv3::Manifold mf;

	FacetEdge * makeTriangle(){

			FacetEdge* fe[3];
			for (int i = 0; i<3; i++){
				fe[i] = mf.makeFacetEdge();
			}
			mf.spliceEdges(*fe[0], *fe[1]);
			mf.spliceEdges(*fe[1], *fe[2]);

			return fe[0];
	}

};

namespace{

	bool const wasFound(RingMembers const & aRingMembers, FacetEdge const * apFe){
		auto result = std::find(aRingMembers.begin(), aRingMembers.end(), apFe);
		return result != aRingMembers.end();
	}
}

TEST_F(EdgeRingTester, FNextRing){

	auto fe0 = makeTriangle();
	auto fe1 = makeTriangle();
	auto fe2 = makeTriangle();

	mf.spliceFacets(*fe0, *fe1);
	mf.spliceFacets(*fe1, *fe2);

	auto collected = getFnextRingMembersOf(*fe0);

	EXPECT_EQ(collected.size(), 3u);

	EXPECT_TRUE(wasFound(collected, fe0));
	EXPECT_TRUE(wasFound(collected, fe1));
	EXPECT_TRUE(wasFound(collected, fe2));

	// let's look for clocked versions:

	auto cl0 = fe0->getClock();
	auto cl1 = fe1->getClock();
	auto cl2 = fe2->getClock();

	collected = getFnextRingMembersOf(*cl1);

	EXPECT_EQ(collected.size(), 3u);

	EXPECT_TRUE(wasFound(collected, cl0));
	EXPECT_TRUE(wasFound(collected, cl1));
	EXPECT_TRUE(wasFound(collected, cl2));
}


TEST_F(EdgeRingTester, ENextRing){

	auto fe0 = makeTriangle();
	auto fe1 = fe0->getEnext();
	auto fe2 = fe1->getEnext();

	auto collected = getEnextRingMembersOf(*fe0);

	EXPECT_EQ(collected.size(), 3u);

	EXPECT_TRUE(wasFound(collected, fe0));
	EXPECT_TRUE(wasFound(collected, fe1));
	EXPECT_TRUE(wasFound(collected, fe2));

	// inspect clocked..
	auto cl0 = fe0->getClock();
	auto cl1 = fe1->getClock();
	auto cl2 = fe2->getClock();

	collected = getEnextRingMembersOf(*cl1);

	EXPECT_EQ(collected.size(), 3u);

	EXPECT_TRUE(wasFound(collected, cl0));
	EXPECT_TRUE(wasFound(collected, cl1));
	EXPECT_TRUE(wasFound(collected, cl2));
}

//TEST_F(EdgeRingTester, AdjancentCollection0){
//
//	auto fe0 = makeTriangle();
//	auto fe1 = makeTriangle();
//	auto fe2 = makeTriangle();
//	auto fe3 = makeTriangle();
//
//
//
//
//
//}






