/* 
 * File:   Domain.h
 * Author: christoph
 *
 * Created on 12. April 2015, 22:21
 */

#ifndef DOMAIN_H
#define	DOMAIN_H
#include "DelaunayForwardDecs.h"

namespace CrystalMesh{
    
    namespace Delaunay3{

        /*A general domain with triangles as boundary faces*/
        struct Domain{
            typedef std::vector<Corner> Corners;
            typedef std::vector<Subdiv3::Vertex*> Vertices;
            typedef std::vector<Triangle> Triangles;
            Subdiv3::Vertex* mpDual;
            
            bool const operator == (Domain const & rhs) const;
                
            bool const operator != (Domain const & rhs) const;
            
            Corners const getCorners() const;
        
            Vertices const getVertices() const;
            
            Triangles const getTriangles() const;
        };
    
    }
}

#endif	/* DOMAIN_H */

