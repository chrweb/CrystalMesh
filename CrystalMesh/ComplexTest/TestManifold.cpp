/*
 * TestManifold.cpp
 *
 *  Created on: 24.06.2014
 *      Author: christoph
 */




#include "TestInclude.h"
#include <cstdlib>


using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Toolbox;




namespace{
	void testVertexProperties(Vertex const & aVert){
		EXPECT_EQ(aVert.mpOut, nullptr);
		EXPECT_EQ(aVert.mpData, nullptr);
	}
}

// Test some properties of a primal vertex, constructed in a manifold:
TEST(Manifold, PrimalVertex){
	Manifold mf;
	// Primal vertex is here in context of the manifold:
	auto const primVert = mf.makePrimalVertex();

	//this will cause an abortion..
	//EXPECT_TRUE(primVert->isPrimal();

	// But we can ask the manifold about this property...
	EXPECT_TRUE(mf.isMyPrimalVertex(*primVert));
	//... and verify, its members are as expected:
	SCOPED_TRACE("Primal vertex properties");
	testVertexProperties(*primVert);
}

// same with dual vertex
TEST(Manifold, DualVertex){
	Manifold mf;
	auto const vert = mf.makeDualVertex();
	EXPECT_TRUE(mf.isMyDualVertex(*vert));
	//... and verify, its members are as expected:
	SCOPED_TRACE("Dual  vertex properties");
	testVertexProperties(*vert);
}

namespace{
	void testEdgeRingProps(EdgeRing const & aRing){
		for (FieldIndex i = 0; i<2; i++){
			auto const & currentDirectedRing = aRing.mRings[i];
			EXPECT_EQ(currentDirectedRing.mIndex, i);
			EXPECT_EQ(currentDirectedRing.mpOrg, nullptr);
			EXPECT_EQ(currentDirectedRing.mpRingMember, nullptr);
		}
	}
}

// Test EdgeRing construction
TEST(Manifold, PrimalEdgeRing){
	Manifold mf;
	auto const ring = mf.makePrimalEdgeRing();
	EXPECT_TRUE(mf.isMyPrimalEdgeRing(*ring));
	SCOPED_TRACE("Primal edge ring");
	testEdgeRingProps(*ring);
}

// And Dual
TEST(Manifold, DualEdgeRing){
	Manifold mf;
	auto const ring = mf.makeDualEdgeRing();
	EXPECT_TRUE(mf.isMyDualEdgeRing(*ring));
	SCOPED_TRACE("Dual edge ring");
	testEdgeRingProps(*ring);
}


TEST(Manifold, FacetEdgePrimalDual){
	Manifold mf;

	auto const  eRef =  mf.makeFacetEdge();
	auto const  clock = eRef->getClock();
	auto const  dual = eRef->getDual();
	auto const  clockDual = eRef->getClock()->getDual();

	EXPECT_TRUE(eRef->isPrimal());
	EXPECT_TRUE(clock->isPrimal());
	EXPECT_TRUE(dual->isDual());
	EXPECT_TRUE(clockDual->isDual());
}



TEST(Manifold, EdgeAlgebra){

	Manifold mf;

	auto const  eRef =  mf.makeFacetEdge();

	auto const  clock = eRef->getClock();

	auto const  dual = eRef->getDual();

	auto const  clockDual = eRef->getClock()->getDual();

	auto const dualClock = eRef->getDual()->getClock();

	EXPECT_EQ(eRef, eRef->getFnext());
	EXPECT_EQ(clock, clock->getFnext());
	EXPECT_EQ(dual, dual->getFnext());
	EXPECT_EQ(clockDual, clockDual->getFnext());

	EXPECT_EQ(eRef, eRef->getEnext());
	EXPECT_EQ(clock, clock->getEnext());
	EXPECT_EQ(dual, dual->getEnext());
	EXPECT_EQ(clockDual, clockDual->getEnext());

	EXPECT_EQ(clockDual, dualClock);

	// arg->clock->clock leads to arg
	EXPECT_EQ(clock->getClock(), eRef);
	EXPECT_EQ(dualClock->getClock(), dual);

	// arg->dual->dual lead to arg
	EXPECT_EQ(dual->getDual(), eRef);
	EXPECT_EQ(dualClock->getDual(), clock);
}

TEST(Manifold, Quaternode){
	Manifold mf;
	auto const  eRef =  mf.makeFacetEdge();

	auto const pQn = eRef->getQuaterNode();

	for (int i = 0; i<3; i++){
		auto const & current = pQn->mNodeArray[i];
		//EXPECT_TRUE(isNullptr(current.mpVertex));
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

TEST(Manifold, triangleEdgeAlgebra){

	Manifold mf;

	auto e0 = mf.makeFacetEdge();
	auto e1 = mf.makeFacetEdge();
	auto e2 = mf.makeFacetEdge();

	mf.spliceEdges(*e0, *e1);
	mf.spliceEdges(*e1, *e2);

	EXPECT_EQ(e0->getInvEnext(), e2);
	EXPECT_EQ(e0->getInvEnext()->getInvEnext(), e1);
	EXPECT_EQ(e0->getInvEnext()->getInvEnext()->getInvEnext(), e0);

	EXPECT_EQ(e0->getEnext(), e1);
	EXPECT_EQ(e0->getEnext()->getEnext(), e2);
	EXPECT_EQ(e0->getEnext()->getEnext()->getEnext(), e0);

	EXPECT_EQ(e0->getEnext()->getClock(), e0->getClock()->getInvEnext());
	EXPECT_EQ(e0->getInvEnext()->getClock(), e0->getClock()->getEnext());

}

TEST(Manifold, EdgeRingLinking){

	Manifold mf;

	FacetEdge* fes[2];
	EdgeRing* rings[2];

	for (int i = 0; i < 2; i++){
		fes[i] = mf.makeFacetEdge();
		rings[i] = mf.makePrimalEdgeRing();
	}

	mf.spliceEdges(*fes[0], *fes[1]);

	for (int i = 0; i<2; i++){
		auto fe = fes[i];
		auto clocked = fe->getClock();

		auto ring = rings[i];

		mf.linkEdgeRingAndFacetEdges(*ring, *fe);

		//annotations as expected?
		auto const dirRing0 = &ring->operator[](0);
		auto const dirRing1 = &ring->operator[](1);

		EXPECT_EQ(dirRing0->getRingMember(), fe);
		EXPECT_EQ(dirRing1->getRingMember(), clocked);

		// annotations removed correctly?
		mf.dislinkEdgeRing(*ring);

		EXPECT_TRUE(isNullptr(dirRing0->mpRingMember));
		EXPECT_TRUE(isNullptr(dirRing1->mpRingMember));

		EXPECT_TRUE(isNullptr(fe->mpDirectedEdgeRing));
		EXPECT_TRUE(isNullptr(clocked->mpDirectedEdgeRing));
	}

}





