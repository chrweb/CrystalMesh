#include <vector>
#include <stddef.h>
#include "Corner.h"
#include "Domain.h"
#include "ComplexTypes.h"

namespace CrystalMesh{
    
    namespace Delaunay3{
    
        using namespace Subdiv3;
        
        Subdiv3::FacetEdge* Domain::getDualFacetEdge() const{
            return mDual->getFacetEdge(); 
        }
        
        Domain const domainFrom(Subdiv3::VertexPtr const & aVertex){
            Domain result = {aVertex};
            return result;
        }
    }

}
