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
			/**
			 * Access to origin/ destination
			 */

			Vertex const & getOrg() const;
			Vertex & getOrg();

			Vertex const & getDest() const;
		    Vertex & getDest();

		    EdgeRing const & getEdgeRing() const;
		    EdgeRing & getEdgeRing();

		    FacetEdge const &	getDual() const;
		    FacetEdge &	getDual();

		    FacetEdge const &	getRev() const;
		    FacetEdge &	getRev();

		    FacetEdge const & getClock() const;
		    FacetEdge& 	getClock();

		    FacetEdge const & getFnext() const;
		    FacetEdge & getFnext();

		    FacetEdge const & getInvFnext() const;
		    FacetEdge & getInvFnext();

		    FacetEdge const & getEnext() const;
		    FacetEdge & getEnext();

		    FacetEdge const & getInvEnext() const;
		    FacetEdge & getInvEnext();

			Vertex* mpVertex;
			EdgeRing* mpEdgeRing;

			FieldIndex mIndex;
			FieldIndex  dualIt;
			FieldIndex  revsIt;
		    FieldIndex  clckIt;

		};

	}
}

