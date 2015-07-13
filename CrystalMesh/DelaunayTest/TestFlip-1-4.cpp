#include "TestInclude.h"
using namespace Mathbox;
using namespace Geometry;
using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Delaunay3;

typedef DelaunayTriangulation3D::TetPoints TetPoints;
typedef DelaunayTriangulation3D::TetIntPoints TetIntPoints;

namespace{
    
        TetPoints const tetPoints(){
            auto result = TetPoints{
                pointFromXY0(-1.0, -0.5),
                pointFromXY0(1.0, -0.5),
                pointFromXY0(0.0, 1.0),
                pointFromXYZ(0.0, 0.0, 1.0)
            };
            return result;
        }
        
        Point3D const insertionPoint()
        {
            return pointFromXYZ(0.0, 0.0, 0.5);
        }
    
}


TEST(Flip_1_4, executeFlip){
    DelaunayTriangulation3D dt;
    Tet tet = dt.makeTet(tetPoints());
    Flip1To4 result = dt.flip1to4(tet, insertionPoint());
    
    EXPECT_EQ(5, dt.getDomainCount());
    EXPECT_EQ(5, dt.getVertexCount());
    EXPECT_EQ(10, dt.getFaceCount());
    EXPECT_EQ(10, dt.getCornerCount());
    return;
}

TEST(Flip_1_4, orientation){

    DelaunayTriangulation3D dt;
    Tet tet = dt.makeTet(tetPoints());
    Tet::Triangles outerTris = tet.getTriangles();
    auto const innerPoint = TetPoints()[3];
    Flip1To4 result = dt.flip1to4(tet, insertionPoint());
    
    for (Triangle const& triangle: outerTris){
        triangle.pointBehind(innerPoint);
    }

}

