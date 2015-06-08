/* 
 * File:   TetInteriour.h
 * Author: christoph
 *
 * Created on 7. Juni 2015, 13:47
 */

#ifndef TETINTERIOUR_H
#define	TETINTERIOUR_H

#include <array>
#include "ComplexTypes.h" 
#include "DelaunayForwardDecs.h"
#include "../Mathbox/Mathbox.h"

namespace CrystalMesh{

    namespace Delaunay3{
    
        struct TetInteriour{

            std::array<Subdiv3::EdgeRing*,6> mpOuterEdgeRing;
            Subdiv3::Vertex * mpVertex[5];
            
            struct Vertices{
                //Boundary Vertices
                std::array<Subdiv3::Vertex *,4> mAtCorners;
                 //Inner Vertex
                Subdiv3::Vertex * mInTet;
            };

            Vertices const getVertices() const;
            
            Triangle const getTriangleAt(Index aIndex) const;
            
            Subdiv3::FacetEdge* getAdapterOf(Corner const & aCorner) const;
            
            Subdiv3::FacetEdge* getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const;
	};
    
    }
} 


#endif	/* TETINTERIOUR_H */

