/*
 * AdjacentDirectedEdgeRings.cpp
 *
 *  Created on: 23.07.2014
 *      Author: christoph
 */

#include "AdjacentDirectedEdgeRings.h"
#include "DirectedEdgeRing.h"
#include "FacetEdge.h"
#include <queue>
#include <set>

namespace CrystalMesh {

	namespace Subdiv3 {

			/**
		     * Implementation of functions to collect adjacent directed edge rings
		     */
		    namespace{

		    AdjacentFacetEdges const otherIncidentFnextRingsOf(FacetEdge * apFe){
		    	AdjacentFacetEdges result;

		    	auto collector = [&result](FacetEdge & aFe){
		    		FacetEdge * transition = aFe.getInvEnext()->getClock();
		    		result.push_back(transition);
		    	};

		    	forEachElementInFnextRing(*apFe, collector);
		    	return result;
		    }

		    AdjacentRings const incidentEdgeRingsFrom(DirectedEdgeRing * apRing){
		    		AdjacentRings result;

		    		auto collector = [&result](FacetEdge & aFe){
		    			FacetEdge * transition = aFe.getInvEnext()->getClock();
		    			result.push_back(transition->getDirectedEdgeRing());
		    		};

		    		forEachElementInFnextRing(*apRing->mpRingMember, collector);
		    		return result;
		    	}
		    }


		    // All incident rings to a vertex may be extracted by a BFS:
		    // http://en.wikipedia.org/wiki/Breadth-first_search
		    AdjacentRings const getAdjacentRingsOf( DirectedEdgeRing const & aDring){

		    	typedef std::queue<DirectedEdgeRing*> NodeQueue;
		    	std::set<DirectedEdgeRing*> visitedNodes;

		    	NodeQueue nodeQueue;

		    	// initial node:
		    	DirectedEdgeRing * initialNode = const_cast<DirectedEdgeRing*>(&aDring);
		    	nodeQueue.push(initialNode);
		    	visitedNodes.insert(initialNode);

		    	while(!nodeQueue.empty()){
					auto current = nodeQueue.front();
					nodeQueue.pop();

					auto const nextNodes = incidentEdgeRingsFrom(current);

					for(auto current: nextNodes){
						// the node was not visited yet:
						if (visitedNodes.insert(current).second){
							// add this node into queue to get neighbored nodes:
							nodeQueue.push(current);
						}
					}
		    	}

		    	AdjacentRings result(visitedNodes.begin(), visitedNodes.end());
		    	return result;
		    }


		    AdjacentRings const getAdjacentRingsOf( Vertex const & aVert){
		    	return getAdjacentRingsOf(*aVert.getDirectedEdgeRing());
            }

		    AdjacentFacetEdges const getAdjacentFacetEdges( FacetEdge const & aStart){

		    	typedef std::queue<FacetEdge*> Fifo;
		    	std::set<FacetEdge*> visitedNodes;

		    	Fifo fifo;

		    	// initial node:
		    	FacetEdge* initialNode = const_cast<FacetEdge*>(&aStart);
		    	fifo.push(initialNode);
		    	visitedNodes.insert(initialNode);

		    	while(!fifo.empty()){
					auto current = fifo.front();
					fifo.pop();

					auto const nextNodes = otherIncidentFnextRingsOf(current);

					for(auto current: nextNodes){
						// the node was not visited yet:
						if (visitedNodes.insert(current).second){
							// add this node into queue to get ne
							nodeQueue.push(current);
						}
					}
		    	}

		    	AdjacentRings result(visitedNodes.begin(), visite
		    	return result;


		    }



	}  // namespace Subdiv3

}  // namespace CrystalMesh




