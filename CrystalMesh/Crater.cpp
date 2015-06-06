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
        using namespace Subdiv3;
        Crater const craterOf(Subdiv3::VertexPtr aVertex){
            Crater result = {aVertex};
            return result;
        }
        
        Crater::Triangles Crater::getTriangles() const{
            FacetEdge* fedge = mVertex->getFacetEdge();
            RingMembers onext= getOnextRingMembersOf(*fedge);
            Triangles result;
            result.reserve(onext.size());
            
            for (FacetEdge * current: onext){
                result.push_back(triangleOf(current->getDual()->getDirectedEdgeRing()));
            }
            
            return result;
        }
    
    }
    
}

