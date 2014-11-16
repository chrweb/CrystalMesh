/*
 * TestTopologicalOperations.cpp
 *
 *  Created on: 17.07.2014
 *      Author: christoph
 *
 *      I'll test some extensive topological operation here.
 */

#include "TestInclude.h"
#include <cstdlib>
#include <algorithm>


using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Toolbox;

namespace{
	typedef std::vector<FacetEdge*> AdjancentFacetEdges;



}

/**
 * Since always a manifold has to constructed, I'll try a test fixture
 */
class TopOps
: public ::testing::Test{

private:


protected:

	CrystalMesh::Subdiv3::Manifold mf;
	// some utilities to form a tet
	CrystalMesh::Subdiv3::EdgeRing* fac[4];
	CrystalMesh::Subdiv3::EdgeRing* corner[6];
	CrystalMesh::Subdiv3::Vertex* vertex[4];
	CrystalMesh::Subdiv3::Vertex* body[2];


	virtual void SetUp(){
		for (int i = 0; i<4; i++){
			fac[i] = makeTriangle();
		}

		for (int i = 0; i<6; i++){
			corner[i] = mf.makePrimalEdgeRing();
		}

		for (int i = 0; i<4; i++){
			vertex[i] = mf.makePrimalVertex();
		}

		for (int i = 0; i<2; i++){
			body[i] = mf.makeDualVertex();
		}
	}



private:

	EdgeRing * makeTriangle(){

		FacetEdge* fe[3];
		for (int i = 0; i<3; i++){
			fe[i] = mf.makeFacetEdge();
		}

		EdgeRing * er = mf.makeDualEdgeRing();

		mf.spliceEdges(*fe[0], *fe[1]);
		mf.spliceEdges(*fe[1], *fe[2]);

		mf.linkEdgeRingAndFacetEdges(*er, *fe[0]->getDual());

		return er;
	}
};

// let's test edge ring links...
TEST_F(TopOps, EdgeRingLinking)
{
	for(int i = 0; i<4; i++){
		auto const & ring = *fac[i];
		// expect a triangle topology
		EXPECT_EQ(ring.computeEdgeRingSize(), 3u);
		// expect to be dual
		EXPECT_TRUE(ring.isDual());
		EXPECT_FALSE(ring.isPrimal());
	}
}


TEST_F(TopOps, DislinkingEdgeRing){
	EdgeRing * testRing = fac[0];

	// keep refs to linked ring pointers
	FacetEdge const * fe0 = testRing->operator[](0).mpRingMember;
	FacetEdge const * fe1 = testRing->operator[](1).mpRingMember;

	// dislink
	mf.dislinkEdgeRing(*testRing);

	// directed edge ring dislinked?
	for (int i = 0 ; i<2; i++)
	{
		DirectedEdgeRing const & dRing= testRing->operator[](i);
		EXPECT_TRUE(isNullptr(dRing.mpRingMember));
	}

	// all Facetedges dislinkt?
	auto nullptrCheck = [](FacetEdge const & aFe){
		EXPECT_TRUE(isNullptr(aFe.mpDirectedEdgeRing));
	};

	forEachElementInFnextRing( *fe0, nullptrCheck);
	forEachElementInFnextRing( *fe1, nullptrCheck);
}

//Let's link a Vertex to several adjancent DirectedEdgeRings
// see
// https://github.com/chrweb/CrystalMesh/wiki/Documentation-for-test-setups#test-the-correctness-of-vertex-edgering-links-1
// for what is going on
TEST_F(TopOps, VertexLinking0){

	auto pFe0 = fac[0]->operator[](0).getRingMember()->getDual();
	auto pFe1 = fac[1]->operator[](0).getRingMember()->getDual();
	auto pFe2 = fac[2]->operator[](0).getRingMember()->getDual();

	mf.spliceFacets(*pFe0, *pFe1);
	mf.spliceFacets(*pFe1, *pFe2);

	// let's link the corners:
	mf.linkEdgeRingAndFacetEdges(*corner[0], *pFe0->getInvEnext() );
	mf.linkEdgeRingAndFacetEdges(*corner[1], *pFe1->getInvEnext() );
	mf.linkEdgeRingAndFacetEdges(*corner[2], *pFe2->getInvEnext() );
	mf.linkEdgeRingAndFacetEdges(*corner[3], *pFe0 );

	//let's check the corner ring sizes to fulfill our expectations:
	EXPECT_EQ(corner[0]->computeEdgeRingSize(), 1u);
	EXPECT_EQ(corner[1]->computeEdgeRingSize(), 1u);
	EXPECT_EQ(corner[2]->computeEdgeRingSize(), 1u);
	EXPECT_EQ(corner[3]->computeEdgeRingSize(), 3u);

	// all transitions from corner3 to oher corners well-linked?
	auto t0 = pFe0->getInvEnext()->getClock();
	auto t1 = pFe1->getInvEnext()->getClock();
	auto t2 = pFe2->getInvEnext()->getClock();

	EXPECT_TRUE(notNullptr(t0->mpDirectedEdgeRing));
	EXPECT_TRUE(notNullptr(t1->mpDirectedEdgeRing));
	EXPECT_TRUE(notNullptr(t2->mpDirectedEdgeRing));


	// link a vertex
	Vertex & vertexRef = *vertex[0];
	mf.linkVertexDirectedEdgeRings(vertexRef, corner[3]->operator[](0));

	// now 4 directed edge ring are expected to be adjacent to the vertex:
	auto const adjRings = getAdjacentRingsOf(vertexRef);
	EXPECT_EQ(adjRings.size(), 4u);

	// try dislinking:xsa
	mf.dislinkVertexDirectedEdgeRings(vertexRef);

	for(EdgeRing const* ring: corner){
		auto const & ref = *ring;
		for (int i = 0; i<2; i++){
			EXPECT_TRUE(isNullptr(ref[i].mpOrg));
		}
	}

	EXPECT_TRUE(isNullptr(vertexRef.mpOut));
}


// a more extensive example
//  see
// https://github.com/chrweb/CrystalMesh/wiki/Documentation-for-test-setups#test-the-correctness-of-vertex-edgering-links-2
// for the expected complex.
TEST_F(TopOps, VertexLinking1){

	auto pFe0 = fac[0]->operator[](0).getRingMember()->getDual();
	auto pFe1 = fac[1]->operator[](0).getRingMember()->getDual();
	auto pFe2 = fac[2]->operator[](0).getRingMember()->getDual();
	auto pFe3 = fac[3]->operator[](0).getRingMember()->getDual();


	mf.spliceFacets(*pFe0, *pFe1);
	mf.spliceFacets(*pFe1, *pFe2);
	mf.spliceFacets(*pFe0->getInvEnext(), *pFe3);

	// let's link the corners:
	mf.linkEdgeRingAndFacetEdges(*corner[0], *pFe0->getInvEnext() );
	mf.linkEdgeRingAndFacetEdges(*corner[1], *pFe1->getInvEnext() );
	mf.linkEdgeRingAndFacetEdges(*corner[2], *pFe2->getInvEnext() );
	mf.linkEdgeRingAndFacetEdges(*corner[3], *pFe0 );
	mf.linkEdgeRingAndFacetEdges(*corner[4], *pFe3->getEnext() );

	//let's check the corner ring sizes to fulfill our expectations:
	EXPECT_EQ(corner[0]->computeEdgeRingSize(), 2u);
	EXPECT_EQ(corner[1]->computeEdgeRingSize(), 1u);
	EXPECT_EQ(corner[2]->computeEdgeRingSize(), 1u);
	EXPECT_EQ(corner[3]->computeEdgeRingSize(), 3u);
	EXPECT_EQ(corner[4]->computeEdgeRingSize(), 1u);

	// all transitions from corner3 to oher corners well-linked?
	auto t0 = pFe0->getInvEnext()->getClock();
	auto t1 = pFe1->getInvEnext()->getClock();
	auto t2 = pFe2->getInvEnext()->getClock();

	EXPECT_TRUE(notNullptr(t0->mpDirectedEdgeRing));
	EXPECT_TRUE(notNullptr(t1->mpDirectedEdgeRing));
	EXPECT_TRUE(notNullptr(t2->mpDirectedEdgeRing));

	// collect all vertex-adjacent FacetEdges
	auto adjacentFacetEdges = getAdjacentFacetEdges(*pFe0);

	// expect 8 FacetEdge-Instances
	EXPECT_EQ(adjacentFacetEdges.size(), 8u);

	// extract directed edge rings:
	std::vector<DirectedEdgeRing *> dirRings;

	for (FacetEdge *  fe : adjacentFacetEdges){
		dirRings.push_back(fe->getDirectedEdgeRing());
	}

	auto const& toBegin = dirRings.begin();
	auto const& toEnd = dirRings.end();

	// sorting
	std::sort(toBegin, toEnd);

	//count occourrences
	auto const count0 = std::count(toBegin, toEnd, & corner[0]->getItem(1));
	auto const count1 = std::count(toBegin, toEnd, & corner[1]->getItem(1));
	auto const count2 = std::count(toBegin, toEnd, & corner[2]->getItem(1));
	auto const count3 = std::count(toBegin, toEnd, & corner[3]->getItem(0));
	auto const count4 = std::count(toBegin, toEnd, & corner[4]->getItem(0));

	EXPECT_EQ(count0, 2);
	EXPECT_EQ(count1, 1);
	EXPECT_EQ(count2, 1);
	EXPECT_EQ(count3, 3);
	EXPECT_EQ(count4, 1);

	auto &vertexRef = *vertex[0];
	mf.linkVertexDirectedEdgeRings(vertexRef, corner[3]->getItem(0));
	// now 4 directed edge ring are expected to be adjacent to the vertex:
	auto const adjRings = getAdjacentRingsOf(vertexRef);
	EXPECT_EQ(adjRings.size(), 5u);

	// try dislinking:
	mf.dislinkVertexDirectedEdgeRings(vertexRef);

	for(EdgeRing const* ring: corner){
		auto const & ref = *ring;
		for (int i = 0; i<2; i++){
			EXPECT_TRUE(isNullptr(ref[i].mpOrg));
		}
	}

	EXPECT_TRUE(isNullptr(vertexRef.mpOut));
}




