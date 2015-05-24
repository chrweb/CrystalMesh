/*
 * Vertex.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{

		struct Vertex{

			bool const isPrimal() const;

			bool const isDual() const;

			DirectedEdgeRing * getDirectedEdgeRing();

			DirectedEdgeRing const * getDirectedEdgeRing() const;


			DirectedEdgeRing * mpOut;
			void * mpData;


		};
                
                typedef Vertex* VertexPtr;


	}


}

