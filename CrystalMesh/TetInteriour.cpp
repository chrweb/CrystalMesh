#include <stddef.h>
#include "ComplexTypes.h"
#include "Corner.h"
#include "Triangle.h"
#include "TetInteriour.h"
#include "../Toolbox/Checks.h"
#include "DelaunayVertex.h"

namespace CrystalMesh{

    namespace Delaunay3{
        
        using namespace Subdiv3;
        using namespace Mathbox;
        using namespace Geometry;
      /*  
        TetInteriour::Vertices const TetInteriour::getVertices() const{
            Vertices result; 
            result.mInTet = mpVertex[0];
        
            for (Index i = 0; i < 4; i++ ){
		result.mAtCorners[i] = mpVertex[i+1];
            }

            return result;
	}
                
        Triangle const TetInteriour::getTriangleAt(Index aIndex) const{
            MUST_BE(aIndex < 6);
            Triangle result;
            result.mpDualEdgeRing = mpOuterEdgeRing[aIndex]->getItem(0).getRingMember()->getDual()->getDirectedEdgeRing();
            return result;
        }
                
        Subdiv3::FacetEdge* TetInteriour::getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const{
                    
            return facetEdgeWithEndPoints(org, dest, mpOuterEdgeRing);
        }
                
        Subdiv3::FacetEdge* TetInteriour::getAdapterOf(Corner const & aCorner) const{
            return getAdapterOf(
                            originPointOf(aCorner.mRef),
                            destinationPointOf(aCorner.mRef));
        }
       * */
    
    
    }
}

