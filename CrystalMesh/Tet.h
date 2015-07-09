/* 
 * File:   Tet.h
 * Author: christoph
 *
 * Created on 11. April 2015, 14:10
 */

#ifndef TET_H
#define	TET_H
#include <array>
#include "Triangle.h"
#include "DelaunayForwardDecs.h"
namespace CrystalMesh{
    
    namespace Subdiv3{
        struct Vertex;
        struct DirectedEdgeRing;
    }
    
    
    namespace Delaunay3{
        
        
    
        struct Tet{
        
            typedef std::array<Triangle,4> Triangles;   
            typedef std::array<Subdiv3::Vertex*, 4> Vertices;
            typedef std::array<Corner, 6> Corners;
		
            //Subdiv3::Vertex* mpDualVertex;
            Triangles mTri;
        
            bool const operator == (Tet const & rhs) const;
        
            bool const operator != (Tet const & rhs) const;
        
            /**
             * True, if Vertex is part of this Tet
             * @param apVert
             * @return 
             */
            bool const isPartOf(Subdiv3::Vertex const *apVert) const;

            Triangle const getTriangleAt(Index aIndex) const;

            Tet const adjancentTetAt(Index aIndex) const;

            Triangle const commonBoundaryWith(Tet const & aOther) const;

            Vertices const getVertices() const;

            Triangles const getTriangles() const;

            Corners const getCorners() const;   
        };
    }
}



#endif	/* TET_H */

