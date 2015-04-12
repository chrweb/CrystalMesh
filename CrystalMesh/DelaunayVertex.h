/* 
 * File:   DelaunayVertex.h
 * Author: christoph
 *
 * Created on 11. April 2015, 21:30
 */

#ifndef DELAUNAYVERTEX_H
#define	DELAUNAYVERTEX_H

#include "DelaunayForwardDecs.h"
#include "Vertex.h"
#include <algorithm>
namespace CrystalMesh{
    
    namespace Delaunay3{
        
        struct VertexData{
            Mathbox::Geometry::Point3D  mPoint;
            void const * mpPropPtr;
	};
        
        VertexData const vertexDataOf(Mathbox::Geometry::Point3D const & aPoint, void const * aPropPtr = nullptr);
        
        Mathbox::Geometry::Point3D const pointOf(Subdiv3::Vertex const *pVertex);

        void const * propertyPtrOf(Subdiv3::Vertex const * pVertex);
        
        Mathbox::Geometry::Point3D const originPointOf(Subdiv3::FacetEdge const * pFacetEdge);

        Mathbox::Geometry::Point3D const destinationPointOf(Subdiv3::FacetEdge const * pFacetEdge);

        Mathbox::Geometry::Point3D const originPointOf(Subdiv3::DirectedEdgeRing const * pFacetEdge);

        Mathbox::Geometry::Point3D const destinationPointOf(Subdiv3::DirectedEdgeRing const * pFacetEdge);

        void setVertexPointTo(Mathbox::Geometry::Point3D const & aPoint, Subdiv3::Vertex * pVertex);
        
            /**
        * Tries to find a FacetEdge with given start/endpoints in an Edgering container.
        * @param org
        * @param dest
        * @param container
        * @return nullptr, if nothing found, else the annotated FacetEdge
        */
        template<class TEdgeRingContainer>
        Subdiv3::FacetEdge* facetEdgeWithEndPoints(Mathbox::Geometry::Point3D const& org, Mathbox::Geometry::Point3D const & dest, TEdgeRingContainer const &container){
            using namespace Subdiv3;
            using namespace Mathbox;
            using namespace Geometry;

            auto finder0 = [&dest, &org](EdgeRing const * ring)->bool{

                 DirectedEdgeRing const * dring = &ring->getItem(0);            
                 Point3D ringOrg = originPointOf(dring);
                 Point3D ringDest= destinationPointOf(dring);

                 if ( exactEqual(ringOrg, org) && exactEqual(ringDest, dest))
                     return true; 

                 return false;
             };

             auto finder1 = [&dest, &org](EdgeRing const * ring)->bool{

                 DirectedEdgeRing const * dring = &ring->getItem(1);            
                 Point3D ringOrg = originPointOf(dring);
                 Point3D ringDest= destinationPointOf(dring);

                 if ( exactEqual(ringOrg, org) && exactEqual(ringDest, dest))
                     return true;                       

                 return false;
            };


             auto const result0 = std::find_if(container.begin(), container.end(), finder0);

             if (result0!= container.end()){
                 return (*result0)->getItem(0).getRingMember();
             }

             auto const result1 = std::find_if(container.begin(), container.end(), finder1);

             if (result1 != container.end())
                 return (*result1)->getItem(1).getRingMember();

             return nullptr;
        }
    
    
    }
}
                


#endif	/* DELAUNAYVERTEX_H */
