/*
 * TestComplexConstruction.cpp
 *
 *  Created on: 26.07.2014
 *      Author: christoph
 */


#include "TestInclude.h"
#include <cstdlib>
#include <algorithm>

using namespace CrystalMesh;
using namespace Mathbox;
using namespace Geometry;
using namespace Toolbox;

namespace{

	using namespace Subdiv3;

	class ComplexTester
	: public ::testing::Test{

	private:


	protected:

		CrystalMesh::Subdiv3::Manifold mf;


	};
}

// First, test trigangles.
TEST_F(ComplexTester, Triangle){

	using namespace Delaunay3;

	auto trig0 = constructTriangleInComplex(mf);

	// exepect a well annotated directed edge ring
	auto dRing0 = trig0.mpDualEdgeRing;
	EXPECT_TRUE(notNullptr(dRing0));

	// clocking returns a triangle with sym edge ring
	auto trig1 = getCounterOrientedOf(trig0);
	EXPECT_EQ(dRing0->getSym(), trig1.mpDualEdgeRing);

	//well defined bounds:
	auto bnds = trig0.getBoundary();
	EXPECT_EQ(bnds.f0->getEnext(), bnds.f1);
	EXPECT_EQ(bnds.f1->getEnext(), bnds.f2);
	EXPECT_EQ(bnds.f2->getEnext(), bnds.f0);
}


namespace{

	uint32_t const computeRingMemberCount(Subdiv3::FacetEdge const * apRef){
		uint32_t c= 0;
		auto counter = [&](FacetEdge const & aFe){
			c++;
		};

		forEachElementInFnextRing(*apRef, counter);
		return c;
	}

	bool const checkBlossomAdapterSituation(FacetEdge const * ap0, FacetEdge const *ap1){
		return ap0->getInvEnext()->getFnext()->getClock() == ap1;
	}



}

// Test Blossom (3 spliced triangles)
// see
// https://github.com/chrweb/CrystalMesh/wiki/Cell-complexes-in-Delaunay3#blossom
//
TEST_F(ComplexTester, Blossom){
	using namespace Delaunay3;

	auto const blossom = constructBlossomInComplex(mf);

	auto const fanAdapter = blossom.getFanAdapter();

	// adapters are facetedges with fnext ring size 2
	EXPECT_EQ(computeRingMemberCount(fanAdapter.f0), 2u);
	EXPECT_EQ(computeRingMemberCount(fanAdapter.f1), 2u);
	EXPECT_EQ(computeRingMemberCount(fanAdapter.f2), 2u);

	EXPECT_TRUE(checkBlossomAdapterSituation(fanAdapter.f0, fanAdapter.f1));
	EXPECT_TRUE(checkBlossomAdapterSituation(fanAdapter.f1, fanAdapter.f2));
	EXPECT_TRUE(checkBlossomAdapterSituation(fanAdapter.f2, fanAdapter.f0));

}

// Test fan construction
TEST_F(ComplexTester, Fan){

	using namespace Delaunay3;

	auto const fan = constructFanInComplex(mf);

	auto const pDring = fan.mpCorner;


	// well-defined directed edge ring
	EXPECT_TRUE(notNullptr(pDring));

	// edge ring size ==3
	EXPECT_EQ(pDring->computeEdgeRingSize(), 3u);

	// relations of the blossom adapter
	auto const blossomAdapter = fan.getBlossomAdapter();

	EXPECT_EQ(blossomAdapter.f0->getInvEnext()->getClock()->getDirectedEdgeRing(), pDring);
	EXPECT_EQ(blossomAdapter.f1->getInvEnext()->getClock()->getDirectedEdgeRing(), pDring);
	EXPECT_EQ(blossomAdapter.f2->getInvEnext()->getClock()->getDirectedEdgeRing(), pDring);
}




TEST_F(ComplexTester, TetInterior){

	using namespace Delaunay3;

	auto const tetint = constructTetInteriourInComplex(mf);

	//well linked edge rings
	for (Index i = 0; i<6; i++){
		auto const currentRing = tetint.mpOuterEdgeRing[i];
		EXPECT_EQ(currentRing->computeEdgeRingSize(),1u);
		EXPECT_TRUE(notNullptr(currentRing->getItem(0).getRingMember()));
		EXPECT_TRUE(notNullptr(currentRing->getItem(1).getRingMember()));
	}

	//all vertex incident to 4 edge rings,
	for (auto const currentVertex : tetint.mpVertex){
		auto incEdgeRings = getAdjacentRingsOf(*currentVertex);
		EXPECT_EQ(incEdgeRings.size(), 4u);
	}
        
        //have a closer look to the vertices:
        TetInteriour::Vertices const vertices = tetint.getVertices();
        
        //outer ones:
        auto const & outer = vertices.mAtCorners;
        
        for (Vertex* currentVertex: outer){
            //adjancent Edgerings
            auto const adjRings = getAdjacentRingsOf(*currentVertex);
            
            MUST_BE(adjRings.size() == 4);
           
             //get their edge ring size:
            auto getSize = [](DirectedEdgeRing* ring) -> Counter{
                return ring->computeEdgeRingSize();
            };
            
            std::array<Counter,4>  sizes;
            
            std::transform(adjRings.begin(), adjRings.end(), sizes.begin(), getSize);
            
            //expected pattern
            std::array<Counter,4> pattern = {1, 1, 1, 3}; 
           
            
            EXPECT_TRUE(std::is_permutation(sizes.begin(), sizes.end(), pattern.begin()));
        }
        
        //inner one:
        auto const innerAdjRings = getAdjacentRingsOf(*vertices.mInTet);
        
        MUST_BE(innerAdjRings.size() == 4);
        
        for (auto currentRing: innerAdjRings){
            EXPECT_EQ(3u, currentRing->computeEdgeRingSize());
        }
        
        
}


TEST_F(ComplexTester, Tet){
	using namespace Delaunay3;

	// tet
	auto const tet = constructTetInComplex(mf);
	auto const verts = tet.getVertices();

	// visit each vertex
	for (auto const pVert: verts){
		// incident directed edge rings
		auto const incRings = getAdjacentRingsOf(*pVert);

		EXPECT_EQ(incRings.size(), 3u);

		// check for well def props
		for (auto const pDirEdge: incRings){
			EXPECT_EQ(pDirEdge->computeEdgeRingSize(), 2u);
		}
	}

	// dual:
	auto const incDualDirRings = getAdjacentRingsOf(*tet.mpDualVertex);

	// 4 incindent rings
	EXPECT_EQ(incDualDirRings.size(), 4u);

	for (auto const pDirEdge: incDualDirRings){
		// each represents a tri..
		EXPECT_EQ(pDirEdge->computeEdgeRingSize(), 3u);
	}

	// other (outside):
	auto const pDualVertex = incDualDirRings.front()->getSym()->getOrg();
	auto const itsIncRings = getAdjacentRingsOf(*pDualVertex);

	// 4 incident rings
	EXPECT_EQ(itsIncRings.size(), 4u);

	for (auto const pCurrentRing: itsIncRings){
		// each one represents a triangle
		EXPECT_EQ(pCurrentRing->computeEdgeRingSize(), 3u);
	}


}





