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

			~Manifold();

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

			void linkEdgeRingAndFacetEdges(EdgeRing& aEring, FacetEdge & aRingRep);

			void linkVertexEdgeRings(Vertex& aVertex, EdgeRing& aEdgeRingRep);

			bool const isMyPrimalVertex(Vertex const & aVert) const;

			bool const isMyDualVertex(Vertex const & aVert) const;

			bool const isMyFacetEdge(FacetEdge const & aFe) const;

			bool const isMyPrimalEdgeRing(EdgeRing const & aRing) const;

			bool const isMyDualEdgeRing(EdgeRing const & aRing) const;



		private:

			VertexMaintener * mpPrimalVertexMaintener;
			VertexMaintener * mpDualVertexMaintener;
			QuaterNodeMaintener * mpQuaterNodeMaintener;
			EdgeRingMaintener * mpPrimalEdgeRingMaintener;
			EdgeRingMaintener * mpDualEdgeRingMaintener;



		};


	}
}
