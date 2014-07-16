/*
 * DirectedEdgeRing.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{

	    /**
		* An equivalence class for a ring of FacetEdges, forming a ring,
		*/
		struct DirectedEdgeRing{

			FacetEdge * mpRingMember;

			bool const isDual() const;

			bool const isPrimal() const;


			DirectedEdgeRing const *getSym() const;
			DirectedEdgeRing * getSym();

			Vertex const * getOrg() const;
			Vertex * getOrg();

			EdgeRing const * getEdgeRing() const;
			EdgeRing * getEdgeRing();

			Counter const computeEdgeRingSize() const;
		};
	}
}
