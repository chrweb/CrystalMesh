/* 
 * File:   Crater.cpp
 * Author: christoph
 * 
 * Created on 25. Mai 2015, 22:55
 */
#include <stddef.h>
#include "Crater.h"


namespace CrystalMesh{

    namespace Delaunay3{
        
        Crater const craterOf(Subdiv3::VertexPtr aVertex){
            Crater result = {aVertex};
            return result;
        }
    
    }
    
}

