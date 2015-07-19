/*
 * FacetEdge.h
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{

		struct FacetEdge{

                    bool isPrimal() const;

                    bool isDual() const;
                    /**
                     * Access to origin/ destination
                     */
                    Vertex const * getOrg() const;
                    Vertex * getOrg();

                    Vertex const * getDest() const;
		    Vertex * getDest();

		    DirectedEdgeRing const * getDirectedEdgeRing() const;
		    DirectedEdgeRing * getDirectedEdgeRing();
                    
                    EdgeRing const * getEdgeRing() const;
		    EdgeRing * getEdgeRing();

		    /**
		     * Other members in current QuaterNode
		     */

		    FacetEdge const *	getDual() const;
		    FacetEdge * getDual();


		    FacetEdge const * getClock() const;
		    FacetEdge* 	getClock();

		    /**
		     * Switch to another ring member
		     */
		    FacetEdge const * getFnext() const;
		    FacetEdge * getFnext();

		    FacetEdge const * getInvFnext() const;
		    FacetEdge * getInvFnext();

		    FacetEdge const * getEnext() const;
		    FacetEdge * getEnext();

		    FacetEdge const * getInvEnext() const;
		    FacetEdge * getInvEnext();

		    /**
		     *  Access to QuaterNode
		     */
		    QuaterNode const * getQuaterNode() const;
		    QuaterNode * getQuaterNode();

		    /**
		     * Navigation on Surface
		     */

		    /**
		     * Returns the Onext FacetEdge, that is, in ccw-Direction the next FacetEdge with the same body 'under' it and the same origin  vertex
		     * than this instance.
		     */
		    FacetEdge const * getOnext() const;
		    FacetEdge * getOnext();

		    FacetEdge const * getInvOnext() const;
		    FacetEdge * getInvOnext();
                    
                    FacetEdge const * getSym() const;
                    FacetEdge * getSym();


                    DirectedEdgeRing* mpDirectedEdgeRing;
                    FacetEdge *mpNext;
                    Vertex * mpOrg;

                    FieldIndex mIndex;
                    FieldIndex  mDualIt;
                    FieldIndex  mClckIt;

		};

		template<typename Functor>
		void forEachElementInFnextRing(FacetEdge  & aStart, Functor const &aFunct){
			auto  pCurrent = &aStart;
			auto  pEnd = pCurrent;
			do{
				aFunct.operator()(*pCurrent);
				pCurrent = pCurrent->getFnext();
			}while(pCurrent != pEnd);

			return;
		}

		template<typename Functor>
		void forEachElementInFnextRing(FacetEdge const  & aStart, Functor const &aFunct){
			auto & nonConstRef = const_cast<FacetEdge&>(aStart);
			forEachElementInFnextRing(nonConstRef, aFunct);
		}


		}
}

