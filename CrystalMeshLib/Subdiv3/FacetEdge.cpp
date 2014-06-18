/*
 * FacetEdge.cpp
 *
 *  Created on: 18.06.2014
 *      Author: christoph
 */
#include "FacetEdge.h"
#include "Vertex.h"
#include "EdgeRing.h"
#include "../Misc/Checks.h"

namespace CrystalMesh{

	namespace Subdiv3{

		namespace{

			template<typename T>
			void checkValidPtr(T const * ptr){
				MUST_BE(notNullptr(ptr));
			}
		}

		Vertex const & FacetEdge::getOrg() const{
			checkValidPtr(mpVertex);
			return *mpVertex;
		}

		Vertex & FacetEdge::getOrg(){
			checkValidPtr(mpVertex);
			return *mpVertex;
		};

		Vertex const & FacetEdge::getDest() const{
			return getClock().getOrg();
		};

		Vertex & FacetEdge::getDest(){
			return getClock().getOrg();
		}

		EdgeRing const & FacetEdge::getEdgeRing() const{
			checkValidPtr(mpEdgeRing);
			return *mpEdgeRing;
		}

		EdgeRing & FacetEdge::getEdgeRing() {
			checkValidPtr(mpEdgeRing);
			return *mpEdgeRing;
		}






	}
}




