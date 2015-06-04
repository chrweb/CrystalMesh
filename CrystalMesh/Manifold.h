/*
 * Manifold.h
 *
 *  Created on: 17.06.2014
 *      Author: christoph
 */
#pragma once

#include "Subdiv3ForwardDecs.h"
#include "Vertex.h"
#include <vector>


namespace CrystalMesh{

	namespace Subdiv3{

            typedef std::vector<Vertex*>  VertexBuffer;
            typedef std::vector<EdgeRing*> EdgeRingBuffer;


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

			void linkEdgeRingAndFacetEdges(EdgeRing& aEring, FacetEdge & aRingRep) const;

			/**
			 * All ring members directed edge ring set to nullptr,
			 * all aEring's directed edge rings's facet edges set to nullptr
			 */
			void dislinkEdgeRing(EdgeRing & aEring) const;
                        
                        /**
                         * Links the vertex to all adjacent directed edge ring and vice versa
                         * @param aVertex
                         * @param aRingRep
                         */
			void linkVertexFacetEdge(Vertex& aVertex, FacetEdge& aFedge);

			/**
			 * aVertex's DirectedEdgeRing is set to nullptr,
			 * all vertex-adjacent DirectedEdgeRing's vertex pointer set to nullptr
			 */
			void dislinkVertexFacetEdges(Vertex & aVertex);

			bool const isMyPrimalVertex(Vertex const & aVert) const;

			bool const isMyDualVertex(Vertex const & aVert) const;

			bool const isMyFacetEdge(FacetEdge const & aFe) const;

			bool const isMyPrimalEdgeRing(EdgeRing const & aRing) const;

			bool const isMyDualEdgeRing(EdgeRing const & aRing) const;
                        
                        void exportPrimalVerts(VertexBuffer& aBuffer) const;
                        
                        void exportDualVerts(VertexBuffer& aBuffer) const;
                        
                        void exportPrimalEdgeRings(EdgeRingBuffer& aBuffer) const;
                        
                        void exportDualEdgeRings(EdgeRingBuffer& aBuffer) const;
                        
                        size_t primalVertexSize() const;
                        
                        size_t dualVertexSize() const;
                        
                        size_t primalEdgeRingSize() const;
                        
                        size_t dualEdgeRingSize() const;
                        
		private:

			VertexMaintener * mpPrimalVertexMaintener;
			VertexMaintener * mpDualVertexMaintener;
			QuaterNodeMaintener * mpQuaterNodeMaintener;
			EdgeRingMaintener * mpPrimalEdgeRingMaintener;
			EdgeRingMaintener * mpDualEdgeRingMaintener;



		};


	}
}
