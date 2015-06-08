/* 
 * File:   Crater.h
 * Author: christoph
 *
 * Created on 25. Mai 2015, 22:55
 */

#ifndef CRATER_H
#define	CRATER_H

#include "ComplexTypes.h"
#include "Triangle.h"
#include <vector>
namespace CrystalMesh{
    
    namespace Delaunay3{
        
        struct Crater{
            
            Subdiv3::VertexPtr  mVertex;
            
            typedef std::vector<Triangle> Triangles;
            
            Triangles getTriangles() const;
            
            Subdiv3::RingMembers getOnextRingOfCenter() const;
            
            Domain const getDomain() const;
            
        };
        
        Crater const craterOf(Subdiv3::VertexPtr aVertex);
   
    }
}

#endif	/* CRATER_H */

