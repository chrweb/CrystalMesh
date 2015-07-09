#include <vector>
#include <stddef.h>
#include "Corner.h"
#include "Domain.h"
#include "ComplexTypes.h"
#include "../Toolbox/Checks.h"
namespace CrystalMesh{
    
    namespace Delaunay3{
    
        using namespace Subdiv3;
        
        Subdiv3::FacetEdge* Domain::getDualFacetEdge() const{
            return mDual->getFacetEdge(); 
        }
        
        Domain const domainFrom(Subdiv3::VertexPtr const & aVertex){
            SHOULD_BE(aVertex != nullptr);
            Domain result = {aVertex};
            return result;
        }
        
        bool const Domain::operator == (Domain const & rhs) const{
            return rhs.mDual == mDual;
        }
                
        bool const Domain::operator != (Domain const & rhs) const{
            return !operator ==(rhs);
        }
    }

}
