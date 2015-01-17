/*
 * AdjacentDirectedEdgeRings.cpp
 *
 *  Created on: 23.07.2014
 *      Author: christoph
 */

#include "AdjacentDirectedEdgeRings.h"
#include "DirectedEdgeRing.h"
#include "FacetEdge.h"
#include "Vertex.h"
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
					auto currentEdgeRing = nodeQueue.front();
					nodeQueue.pop();

					auto const transistions = incidentEdgeRingsFrom(currentEdgeRing);

					for(auto currentTransition: transistions){
						// the node was not visited yet:
						if (visitedNodes.insert(currentTransition).second){
							// add this node into queue to get neighbored nodes:
							nodeQueue.push(currentTransition);
						}
					}
		    	}

		    	AdjacentRings result(visitedNodes.begin(), visitedNodes.end());
		    	return result;
		    }


		    AdjacentRings const getAdjacentRingsOf( Vertex const & aVert){
		    	return getAdjacentRingsOf(*aVert.getDirectedEdgeRing());
            }
                    AdjacentFacetEdges const getAdjacentFacetEdges( Vertex const & aVert){
                        return getAdjacentFacetEdges(aVert->getDirectedEdgeRing()->getRingMember());
                    }
                    
		    AdjacentFacetEdges const getAdjacentFacetEdges( FacetEdge const & aStart){

		    	typedef std::queue<FacetEdge*> Fifo;
		    	std::set<FacetEdge*> collected;

		    	Fifo fifo;

		    	// initial node:
		    	FacetEdge* initialNode = const_cast<FacetEdge*>(&aStart);
		    	fifo.push(initialNode);
		    	collected.insert(initialNode);

		    	while(!fifo.empty()){
                            auto currentBorder = fifo.front();
                            fifo.pop();

                            // get adjancent fnext rings
                            auto const transistions = otherIncidentFnextRingsOf(currentBorder);

                            for(auto currentTransistion: transistions){

                                // extract all ring members:
                                auto const currentRing = getFnextRingMembersOf(*currentTransistion);

                                for (auto currentRingMember: currentRing){
                                    // the fnext ring was not visited yet:
                                    if (collected.insert(currentRingMember).second){
                                        // add this node into queue
                                        fifo.push(currentRingMember);
                                        // extract all ring members:}
                                        auto currentBorder = fifo.front();
                                    }
                                }
                            }
		    	}

		    	AdjacentFacetEdges result(collected.begin(), collected.end());
		    	return result;
		    }

			RingMembers const getFnextRingMembersOf(FacetEdge const & aRef){
				RingMembers result;
				auto collector = [&result](FacetEdge const & aArg){
					result.push_back(const_cast<FacetEdge*>(&aArg));
				};
				forEachElementInFnextRing(aRef, collector);
				return result;
			}

			RingMembers const getFnextRingMembersOf(DirectedEdgeRing const & aRef){
				return getFnextRingMembersOf(*aRef.getRingMember());
			}


			RingMembers const getEnextRingMembersOf(FacetEdge const & aRef){
				RingMembers result;
				auto const dual = aRef.getDual();

				auto collector = [&result](FacetEdge const & aArg){
					result.push_back(const_cast<FacetEdge*>(aArg.getDual()));
				};

				forEachElementInFnextRing(*dual, collector);
				return result;
			}




	}  // namespace Subdiv3

}  // namespace CrystalMesh




