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

TEST(Tet, domains){
    DelaunayTriangulation3D dt;
    Tet const tet = dt.makeTet(points());
  
    // inner domain distinct from outer
    for (Index i = 0 ; i< 4; i++){
        Triangle const t = tet.getTriangleAt(0);
        Domain const inner = t.getDomainUnder();
        Domain const outer = t.getDomainOver();
        
        EXPECT_FALSE(inner == outer);
    }
    
    //all inner domains equal
    //all outer domain equal
    Triangle const tRef = tet.getTriangleAt(0);
    Domain const innerRef = tRef.getDomainUnder();
    Domain const outerRef = tRef.getDomainOver();
    
    
    for (Index i = 1; i<4; i++){
        Triangle const tCurrent = tet.getTriangleAt(i);
        Domain const currenInner = tCurrent.getDomainUnder();
        Domain const currentOuter = tCurrent.getDomainOver();
        EXPECT_TRUE(innerRef == currenInner);
        EXPECT_TRUE(outerRef == currentOuter);
    } 
}
