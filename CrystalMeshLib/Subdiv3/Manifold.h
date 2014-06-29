/*
 * Manifold.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"

namespace CrystalMesh{

	namespace Subdiv3{



		class Manifold{

		public:

			Manifold();

			Manifold(const Manifold & aSrc);

			FacetEdge * makeFacetEdge();

			Vertex * makePrimalVertex();

			Vertex * makeDualVertex();

			EdgeRing * makePrimalEdgeRing();

			EdgeRing * makeDualEdgeRing();

			void deleteQuaterNodeOf(FacetEdge & aRef);

			void deletePrimalVertex(Vertex & aRef);

			void deleteDualVertex(Vertex & aRef);

			void deletePrimalEdgeRing(EdgeRing & aRef);

			void deleteDualEdgeRing(EdgeRing & aRef);

			void spliceFacets(FacetEdge& aFe0, FacetEdge& aFe1);

			void spliceEdges(FacetEdge& aFe0, FacetEdge& aFe1);

			void linkEdgeRingAndFacetedges(EdgeRing& aEring, FacetEdge & aRingRep);

			void linkVertexEdgeRings(Vertex& aVertex, EdgeRing& aEdgeRingRep);

		private:

			VertexMaintener * mpPrimalVertexMaintener;
			VertexMaintener * mpDualVertexMaintener;
			QuaterNodeMaintener * mpQuaterNodeMaintener;
			EdgeRingMaintener * mpPrimalEdgeRingMaintener;
			EdgeRingMaintener * mpDualEdgeRingMaintener;
		};


	}
}
