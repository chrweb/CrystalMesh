#include <stddef.h>
#include "Corner.h"
#include "../Toolbox/Checks.h"
#include "Tet.h"
#include "DelaunayVertex.h"

namespace CrystalMesh{

    namespace Delaunay3{
        using namespace Subdiv3;
        using namespace Mathbox;
        using namespace Geometry;
        
        Triangle const Tet::getTriangleAt(Index aIndex) const{
            SHOULD_BE(aIndex<5);
            return mTri[aIndex];
        }
        
        Tet::Vertices const Tet::getVertices() const{
            
            //to tris hold all vertices
            auto triverts0 = getTriangleAt(0).getBoundaryVertices();
            auto triverts1 = getTriangleAt(1).getBoundaryVertices();
            std::array<VertexPtr, 6> vertices = {
                triverts0[0], 
                triverts0[1], 
                triverts0[2], 
                triverts1[0], 
                triverts1[1], 
                triverts1[2]
            };
            
            //remove doublettes
            std::sort(vertices.begin(), vertices.end());
            auto uniqueEnd = std::unique(vertices.begin(), vertices.end());
            
            SHOULD_BE(uniqueEnd- vertices.begin() == 4);
            
            Tet::Vertices result = {
                vertices[0],
                vertices[1],
                vertices[2],
                vertices[3]
            };
            
            return result;
        
        }
        
        Tet::Points const Tet::getPoints() const{
            auto vertices = getVertices();
            Points result = {
                pointOf(vertices[0]),
                pointOf(vertices[1]),
                pointOf(vertices[2]),
                pointOf(vertices[3]),
            };
            
            return result;
        }
        
        Tet::Triangles const Tet::getTriangles() const{
            return mTri;
        }
        
        
        
        Tet::Corners const Tet::getCorners() const{
                   
            std::vector<EdgeRing*> edgeRings;

            for (auto const & triangle : mTri){
                auto bound = triangle.getBoundaryEdges();

                for (auto const fe: bound){
                    edgeRings.push_back(fe->getDirectedEdgeRing()->getEdgeRing());
                }

            }

            std::sort(edgeRings.begin(), edgeRings.end());
            auto toUniqueEnd = std::unique(edgeRings.begin(), edgeRings.end());

            SHOULD_BE((toUniqueEnd-edgeRings.begin()) == 6 );
            std::array<EdgeRing*, 6> uniqueEdgeRings;
            std::copy(edgeRings.begin(), toUniqueEnd, uniqueEdgeRings.begin());


            Corners result;
            Domain inner = getTriangleAt(0).getDomainUnder();
            
            for (Index i = 0; i<6; i++){
                Corner current = cornerFrom(uniqueEdgeRings[i], inner);
                result[i] = current;
            }

            return result;
        }

    }
}