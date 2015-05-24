#include <stddef.h>
#include "ComplexTypes.h"
#include "../Mathbox/Mathbox.h"
#include "DelaunayVertex.h"


namespace CrystalMesh{
    namespace Delaunay3{
        
        using namespace Mathbox::Geometry;
        using namespace Subdiv3;
        
        Index const VertexData::invalidID = Index(-1);
        
        VertexData const vertexDataFrom(Mathbox::Geometry::Point3D const & aPoint, void const * apPropPtr){
            VertexData result{ aPoint, apPropPtr, VertexData::invalidID};
            return result;
	}
        
        VertexData const vertexDataFrom(VertexData const& aOther){
            VertexData const result = aOther;
            return result;
        }
        
        VertexData const vertexDataOf(Subdiv3::VertexPtr const & pVertex){
            VertexData const  data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
            return data;
        }
        
        Point3D const pointOf(Subdiv3::Vertex const *pVertex){
            VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
            return data.mPoint;
	}
        
        Index idOf(Subdiv3::Vertex const *pVertex){
            VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
            return data.mId;
        }
        
        void const * propertyPtrOf(Subdiv3::Vertex const * pVertex){
             VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
            return data.mpPropPtr;
        }
        
        VertexData * vertexDataPtrOf(Subdiv3::Vertex const * pVertex){
            VertexData * data = reinterpret_cast<VertexData*>(pVertex->mpData);
            return data;
        }
   
	
         Point3D const originPointOf(Subdiv3::FacetEdge const * pFacetEdge){
             return pointOf(pFacetEdge->getOrg());
         }
         
         Point3D const destinationPointOf(Subdiv3::FacetEdge const * pFacetEdge){
             return pointOf(pFacetEdge->getDest());
         }
         
         Point3D const originPointOf(Subdiv3::DirectedEdgeRing const * pRing){
             return originPointOf(pRing->getRingMember());
         }
         
         Point3D const destinationPointOf(Subdiv3::DirectedEdgeRing const * pRing){
             return destinationPointOf(pRing->getRingMember());
         }
         
        Index const originIndexOf(Subdiv3::FacetEdge const *pFedge){
            return originIndexOf(pFedge->getDirectedEdgeRing());
        }
        
        Index const destinationIndexOf(Subdiv3::FacetEdge const *pFedge){
            return destinationIndexOf(pFedge->getDirectedEdgeRing());
        }
         
        Index const originIndexOf(Subdiv3::DirectedEdgeRing const *pRing){
            Index result =  idOf(pRing->getOrg());
            return result;
        }
        
        Index const destinationIndexOf(Subdiv3::DirectedEdgeRing const * pRing){
            Index result =  idOf(pRing->getSym()->getOrg());
            return result;
        }
         
         void setVertexPointTo(Mathbox::Geometry::Point3D const & aPoint, Subdiv3::Vertex * pVertex){
            VertexData * data = reinterpret_cast<VertexData*>(pVertex->mpData);
            data->mPoint = aPoint;
         }
         
        void setVertexIdTo(Index aIndex, Subdiv3::Vertex* pVertex){
            VertexData * data = reinterpret_cast<VertexData*>(pVertex->mpData);
            data->mId = aIndex;
            return;
        }
         
         
    }
}