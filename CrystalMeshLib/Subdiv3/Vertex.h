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

			bool isPrimal() const;

			bool isDual() const;


			FacetEdge * mpOut;
			void * mpData;


		};


	}


}

