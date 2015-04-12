#include "ComplexTypes.h"
#include "../Mathbox/Mathbox.h"
#include "DelaunayVertex.h"


namespace CrystalMesh{
    namespace Delaunay3{
        
        using namespace Mathbox::Geometry;
        using namespace Subdiv3;
        
        VertexData const vertexDataOf(Mathbox::Geometry::Point3D const & aPoint, void const * apPropPtr){
            VertexData result{ aPoint, apPropPtr};
            return result;
	}
        
        Point3D const pointOf(Subdiv3::Vertex const *pVertex){
            VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
            return data.mPoint;
	}
        
        void const * propertyPtrOf(Subdiv3::Vertex const * pVertex){
             VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
            return data.mpPropPtr;
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
         
         void setVertexPointTo(Mathbox::Geometry::Point3D const & aPoint, Subdiv3::Vertex * pVertex){
             VertexData * data = reinterpret_cast<VertexData*>(pVertex->mpData);
             data->mPoint = aPoint;
         }
         
         
    }
}