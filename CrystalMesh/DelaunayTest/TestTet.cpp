#include "TestInclude.h"
using namespace Mathbox;
using namespace Geometry;
using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Delaunay3;

typedef DelaunayTriangulation3D::TetPoints TetPoints;

namespace{
  
    TetPoints points(){
        return TetPoints{
                pointFromXY0(-1.0, -0.5),
                pointFromXY0(1.0, -0.5),
                pointFromXY0(0.0, 1.0),
                pointFromXYZ(0.0, 0.0, 1.0)
        };
    };
}

TEST(Tet, constuction){
    DelaunayTriangulation3D dt;
    dt.makeTet(points());
    
    EXPECT_EQ(2, dt.getDomainCount());
    EXPECT_EQ(4, dt.getVertexCount());
    EXPECT_EQ(6, dt.getCornerCount());
    EXPECT_EQ(4, dt.getFaceCount());
}