#include "TestInclude.h"

using namespace CrystalMesh;
using namespace Mathbox;
using namespace Geometry;
using namespace Toolbox;
using namespace Delaunay3;
using namespace Subdiv3;


namespace{
    Point3D center = pointFromXYZ(0.0, 0.0, -1.0);
    std::array<Point3D,3> bnd0= {
        pointFromXY0(1.0, -0.5),
        pointFromXY0(0.0, 0.5),
        pointFromXY0(-1.0, -0.5)
    };
    
    Point3D const uPoint = pointFromXYZ( 0.0,  0.0,  1.0);
    Point3D const dPoint = pointFromXYZ( 0.0,  0.0,  -1.0);
    
    DelaunayTriangulation3D::TetIntPoints constructionPoints(){
        DelaunayTriangulation3D::TetIntPoints const points = {
        bnd0[0], 
        bnd0[1], 
        bnd0[2], 
        uPoint, 
        dPoint};
        
        return points;
    
    }

}


TEST(TetInteriour, construction){
    
    DelaunayTriangulation3D dt;
    
    DelaunayTriangulation3D::TetIntPoints  points = constructionPoints();
    TetInteriour result = dt.makeTetInterior(points);
    
    EXPECT_EQ(1,dt.getDomainCount());
    EXPECT_EQ(6, dt.getFaceCount());
    EXPECT_EQ(5, dt.getVertexCount());
    EXPECT_EQ(10, dt.getCornerCount());
    return;
}
