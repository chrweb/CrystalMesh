/*
 * VertexMaintener.h
 *
 *  Created on: 19.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"
#include <set>

namespace CrystalMesh{

	namespace Subdiv3{

		class VertexMaintener{

		public:

			VertexMaintener();

			Vertex * constructVertex();

			void deleteVertex(Vertex *apVert);

		private:

			std::set<Vertex*> mVertexContainer;

		};


	}
}

