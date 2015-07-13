/* 
 * File:   Triangle.h
 * Author: christoph
 *
 * Created on 11. April 2015, 14:02
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H
#include <array>
#include "ComplexTypes.h" 
#include "DelaunayForwardDecs.h"
#include "../Mathbox/Mathbox.h"

namespace CrystalMesh{
    
    namespace Delaunay3{
        

        struct Triangle
        {
            typedef std::array<Subdiv3::FacetEdge*, 3> BoundaryEdges;
            typedef std::array<Mathbox::Geometry::Point3D, 3> BoundaryPoints;
            typedef std::array<Subdiv3::Vertex*, 3> BoundaryVertices;
            
            BoundaryEdges const getBoundaryEdges() const;

            BoundaryPoints const getBoundaryPoints() const;
            
            BoundaryVertices const getBoundaryVertices() const;

            Mathbox::Geometry::OrientedPlane3D const getOrientedPlane() const;
            
            bool const pointBehind(Mathbox::Geometry::Point3D const& aPoint) const;
            
            Subdiv3::FacetEdge* boundaryWith(Mathbox::Geometry::Point3D const & aOrg, Mathbox::Geometry::Point3D const & aDest) const;
            
            bool const operator == (const Triangle& other) const;
            
            bool const operator != (const Triangle& other) const;
            
            Delaunay3::Domain const getDomainUnder() const;
           
            Delaunay3::Domain const getDomainOver() const;
            // Tet const upperTet() const;
            
           // Tet const lowerTet() const;

            Subdiv3::DirectedEdgeRing* mpDualEdgeRing;
            
            static Triangle const invalid;
            
            Triangle const getCounterOriented() const;

	};
        
        Triangle const triangleOf(Subdiv3::DirectedEdgeRing * apDring);
        
        Triangle const triangleLeftOf(Subdiv3::FacetEdge* aFacetEdge);

    }
}

#endif	/* TRIANGLE_H */

