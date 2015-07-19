/*
 * Vertex.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"
#include "FacetEdge.h"

namespace CrystalMesh{

	namespace Subdiv3{

		struct Vertex{

			bool const isPrimal() const;

			bool const isDual() const;

			DirectedEdgeRing * getDirectedEdgeRing();

			DirectedEdgeRing const * getDirectedEdgeRing() const;
                        
                        FacetEdge * getFacetEdge();
                        
                        FacetEdge const * getFacetEdge() const;

			FacetEdge * mpOut;
			void * mpData;


		};
                
                typedef Vertex* VertexPtr;
                
                extern VertexPtr const invalidVertex;


	}


}

