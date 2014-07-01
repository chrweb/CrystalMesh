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

TEST(Manifold, Quaternode){
	Manifold mf;
	auto const  eRef =  mf.makeFacetEdge();

	auto const pQn = eRef->getQuaterNode();

	for (int i = 0; i<3; i++){
		auto const & current = pQn->mNodeArray[i];
		EXPECT_TRUE(isNullptr(current.mpVertex));
		EXPECT_TRUE(isNullptr(current.mpDirectedEdgeRing));
		EXPECT_TRUE(notNullptr(current.mpNext));

	}

}


namespace{

/**
	 * Tests the edge algebra after spliceFacets due to spliced references immediately
	 * after this operation
	 */
	void checkSpliceFacetsEdgeAlgebra(
			FacetEdge const & aFe0,
			FacetEdge const & aFormerFnext0,
			FacetEdge const & aFe1,
			FacetEdge const & aFormerFnext1)
	{
		EXPECT_EQ(aFe0.getFnext() , & aFormerFnext1);
		EXPECT_EQ(aFe1.getFnext() , & aFormerFnext0);
	}

	/**
	 * Tests the edge algebra after spliceEdges due to spliced references immediately
	 * after this operation
	 */
	void checkSpliceEdgesEdgeAlgebra(
			FacetEdge const & aFe0,
		    FacetEdge const & aFormerEnext0,
			FacetEdge const & aFe1,
			FacetEdge const & aFormerEnext1)
			{
				EXPECT_EQ(aFe0.getEnext() , & aFormerEnext1);
				EXPECT_EQ(aFe1.getEnext() , & aFormerEnext0);
			}

}


TEST(Manifold, SpliceFacets){

	Manifold mf;

	auto e0 = mf.makeFacetEdge();
	auto e1 = mf.makeFacetEdge();

	auto fnext0 = e0->getFnext();
	auto fnext1 = e1->getFnext();

	mf.spliceFacets(*e0, *e1);

	SCOPED_TRACE("Elementary spliceFacets operation");
	checkSpliceFacetsEdgeAlgebra(*e0, *fnext0, *e1, *fnext1);
}

TEST(Manifold, SpliceEdges){
	Manifold mf;

	auto e0 = mf.makeFacetEdge();
	auto e1 = mf.makeFacetEdge();

	auto enext0 = e0->getEnext();
	auto enext1 = e1->getEnext();

	mf.spliceEdges(*e0, *e1);

	SCOPED_TRACE("Elementary spliceFacets operation");
	checkSpliceEdgesEdgeAlgebra(*e0, *enext0, *e1, *enext1);
}

TEST(Manifold, EdgeRingLinking){

	Manifold mf;

	auto e0 = mf.makeFacetEdge();
	auto e1 = mf.makeFacetEdge();
	auto e2 = mf.makeFacetEdge();

	mf.spliceFacets(*e0, *e1);
	mf.spliceFacets(*e1, *e2);
	mf.spliceFacets(*e2, *e0);

	auto ring = mf.makePrimalEdgeRing();

	mf.linkEdgeRingAndFacetEdges(*ring, *e0);

	EXPECT_EQ(ring->computeEdgeRingSize(), 3);





}



