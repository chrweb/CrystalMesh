/*
 * VertexMaintener.cpp
 *
 *  Created on: 19.06.2014
 *      Author: christoph
 */

#include "VertexMaintener.h"
#include "Vertex.h"
#include "../Misc/Checks.h"
namespace CrystalMesh{

	namespace Subdiv3{

		VertexMaintener::VertexMaintener()
		: mVertexContainer()
		{

		}

		Vertex * VertexMaintener::constructVertex(){
			auto pVert = new Vertex;
			mVertexContainer.insert(pVert);
			return pVert;

		}

		void VertexMaintener::deleteVertex(Vertex *apVert){
			auto found = mVertexContainer.find(apVert);
			MUST_BE(found != mVertexContainer.end());
			delete *found;
			mVertexContainer.erase(found);
			return;
		}



	}
}



