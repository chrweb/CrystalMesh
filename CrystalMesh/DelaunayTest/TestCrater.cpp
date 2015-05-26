#include "TestInclude.h"
#include <array>
using namespace Mathbox;
using namespace Geometry;
using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Delaunay3;

typedef DelaunayTriangulation3D::CraterPoints CraterPoints;

namespace{
    Point3D center = pointFromXYZ(0.0, 0.0, -1.0);
    std::array<Point3D,3> bnd0= {
        pointFromXY0(1.0, -0.5),
        pointFromXY0(0.0, 0.5),
        pointFromXY0(-1.0, -0.5)
    }; 
    
}

TEST(CraterTest, crater0){
    DelaunayTriangulation3D dt;
    dt.makeCrater(center, CraterPoints(bnd0.begin(), bnd0.end()));
    
    EXPECT_EQ(dt.getCornerCount(), 9);
    EXPECT_EQ(dt.getDomainCount(), 1);
    EXPECT_EQ(dt.getFaceCount(), 3);
    EXPECT_EQ(dt.getVertexCount(), 4);

}
