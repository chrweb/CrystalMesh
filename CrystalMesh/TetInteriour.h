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
#include "Triangle.h"

namespace CrystalMesh{

    namespace Delaunay3{
    
        struct TetInteriour{
            
            typedef std::array<Delaunay3::Triangle,6> Triangles;

            Triangles mTriangles;
            
            
            Triangle const getTriangleAt(Index aIndex) const;
            
            Triangles const getTriangles() const;
            
            Subdiv3::FacetEdge* getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const;
	};
    
    }
} 


#endif	/* TETINTERIOUR_H */

