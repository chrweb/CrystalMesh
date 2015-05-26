/* 
 * File:   Crater.h
 * Author: christoph
 *
 * Created on 25. Mai 2015, 22:55
 */

#ifndef CRATER_H
#define	CRATER_H

#include "ComplexTypes.h"

namespace CrystalMesh{
    
    namespace Delaunay3{
        
        struct Crater{
            
            Subdiv3::VertexPtr  mVertex;
            
        };
        
        Crater const craterOf(Subdiv3::VertexPtr aVertex);
   
    }
}

#endif	/* CRATER_H */

