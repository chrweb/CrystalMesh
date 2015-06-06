/*
 * AdjacentDirectedEdgeRings.h
 *
 *  Created on: 21.07.2014
 *      Author: christoph
 */
#pragma once
#include <vector>
#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh {

	namespace Subdiv3 {

		typedef std::vector<DirectedEdgeRing*> AdjacentRings;

		/**
		 * Returns all DirectedEdgeRings, adjacent the the specified vertex,
		 * -aborts, if an annotation is nullptr
		 */
		AdjacentRings const getAdjacentRingsOf( Vertex const & aVert);

		/**
		 * Almost same as above, using the specified directed edge ring as initial start point
		 */
		AdjacentRings const getAdjacentRingsOf( DirectedEdgeRing const & aStart);



		typedef std::vector<FacetEdge*> AdjacentFacetEdges;

		/**
		 * Starting at aStart, all FacetEdges which should share the same origin are collected,
		 * -that is, each facet ring member is listed explicitly.
		 * -no abortion caused by nullptr annotation.
		 */
		AdjacentFacetEdges const getAdjacentFacetEdges( FacetEdge const & aStart);

		AdjacentFacetEdges const getAdjacentFacetEdges( Vertex const & aVert);

                
                typedef std::vector<FacetEdge*> RingMembers;

		RingMembers const getFnextRingMembersOf(FacetEdge const & aRef);

		RingMembers const getFnextRingMembersOf(DirectedEdgeRing const & aRef);

		RingMembers const getEnextRingMembersOf(FacetEdge const & aRef);
                
                RingMembers const getOnextRingMembersOf(FacetEdge const & aRef);
                


	}  // namespace Subdiv3

}  // namespace CrystalMesh

