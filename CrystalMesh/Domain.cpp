#include <vector>
#include <stddef.h>
#include <algorithm>
#include "Corner.h"
#include "Domain.h"
#include "ComplexTypes.h"
#include "../Toolbox/Checks.h"
#include "AdjacentDirectedEdgeRings.h"

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
        
       Corner const Domain::cornerWith(Mathbox::Geometry::Point3D const & aOrg, Mathbox::Geometry::Point3D const & aDest) const{
           auto triangles = getTriangles();
           for (Triangle const& triangle: triangles){
               FacetEdge* edgeOfInterest = triangle.boundaryWith(aOrg, aDest);
               
               if (edgeOfInterest != nullptr){
                   Corner result = cornerFrom(edgeOfInterest->getEdgeRing(), *this);
                   return result;
               }
           }
           
           return Corner::invalid;
        }
       
       
        Domain::Triangles const Domain::getTriangles() const{
           auto adjEdgeRings = getAdjacentRingsOf(*mDual);
           Triangles result(adjEdgeRings.size(), Triangle::invalid);
           
           std::transform(adjEdgeRings.begin(), adjEdgeRings.end(), result.begin(), triangleOf);
           return result;
       }
       
    }
    
}
