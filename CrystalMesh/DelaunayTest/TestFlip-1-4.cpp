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
    dt.flip1to4(tet, insertionPoint());
    
    for (Triangle const& triangle: outerTris){
        triangle.pointBehind(innerPoint);
    }
}

TEST(Flip_1_4, tets){
    DelaunayTriangulation3D dt;
    Tet tet = dt.makeTet(tetPoints());
    Tet::Triangles outerTris = tet.getTriangles();

    dt.flip1to4(tet, insertionPoint());
    
    
    
    //inspect the tets
    EXPECT_NO_THROW(outerTris[0].getTetUnder());
    EXPECT_NO_THROW(outerTris[1].getTetUnder());
    EXPECT_NO_THROW(outerTris[2].getTetUnder());
    EXPECT_NO_THROW(outerTris[3].getTetUnder());
    
 
    auto domain0 = outerTris[0].getDomainUnder();
    auto domain1 = outerTris[1].getDomainUnder();
    auto domain2 = outerTris[2].getDomainUnder();
    auto domain3 = outerTris[3].getDomainUnder();
    
    return;
}

