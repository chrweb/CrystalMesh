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

		    /**
		     * Other members in current OctoNode
		     */

		    FacetEdge const *	getDual() const;
		    FacetEdge * getDual();

		    //FacetEdge const &	getRev() const;
		    //FacetEdge &	getRev();

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

			Vertex* mpVertex;
			DirectedEdgeRing* mpDirectedEdgeRing;
			FacetEdge *mpNext;

			FieldIndex mIndex;
			FieldIndex  mDualIt;
			//FieldIndex  mRevsIt;
			FieldIndex  mClckIt;

		};

	}
}

