/*
 * TestManifold.cpp
 *
 *  Created on: 24.06.2014
 *      Author: christoph
 */




#include "../TestInclude.h"
#include <cstdlib>


using namespace CrystalMesh;
using namespace Subdiv3;


namespace{

//	void basicEdgeArithmTest(FacetEdge const & aRef){
//
//	}

}


TEST(Manifold, EdgeAlgebra){

	Manifold mf;

	auto const  eRef =  mf.makeFacetEdge();

	auto const  clock = eRef->getClock();

	auto const  dual = eRef->getDual();

	auto const  clockDual = eRef->getClock()->getDual();

	EXPECT_EQ(eRef, eRef->getFnext());
	EXPECT_EQ(clock, clock->getFnext());
	EXPECT_EQ(dual, dual->getFnext());
	EXPECT_EQ(clockDual, clockDual->getFnext());

	EXPECT_EQ(eRef, eRef->getEnext());
	EXPECT_EQ(clock, clock->getEnext());
	EXPECT_EQ(dual, dual->getEnext());
	EXPECT_EQ(clockDual, clockDual->getEnext());
}

//TEST(Manifold, SpliceFacets){
//
//	Manifold mf;
//
//	auto e0 = mf.makeFacetEdge();
//	auto e1 = mf.makeFacetEdge();
//
//	auto e0D = e0->getDual();
//	auto e1D = e2->getDual();
//
//	mf.spliceFacets(*e0, e1);
//
//	EXPECT_EQ(e0->getFnext(), e1);
//	EXPECT_EQ(e1->getFnext(), e0);
//
//
//
//
//
//}



