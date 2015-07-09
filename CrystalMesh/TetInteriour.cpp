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
        
        Triangle const TetInteriour::getTriangleAt(Index aIndex) const{
            SHOULD_BE(aIndex < 6);
            return mTriangles[aIndex];
        }
        
        TetInteriour::Triangles const TetInteriour::getTriangles() const{
            return mTriangles;
        }
        
        Subdiv3::FacetEdge* TetInteriour::getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const{
            for (auto const& current : mTriangles){
                FacetEdge* bnd = current.boundaryWith(org, dest);
                if (bnd != nullptr){
                    return bnd;
                }
            }
            
            return nullptr;
        
        }
      /*  
        TetInteriour::Vertices const TetInteriour::getVertices() const{
            Vertices result; 
            result.mInTet = mpVertex[0];
        
            for (Index i = 0; i < 4; i++ ){
		result.mAtCorners[i] = mpVertex[i+1];
            }

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

