#include "TestInclude.h"
#include <array>
using namespace Mathbox;
using namespace Geometry;
using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Delaunay3;
typedef DelaunayTriangulation3D::FanPoints FanPoints;
namespace{
    
    Point3D const uPoint = pointFromXYZ( 0.0,  0.0,  1.0);
    Point3D const dPoint = pointFromXYZ( 0.0,  0.0,  -1.0);

    std::array<Point3D,2> sample1 = {pointFromXYZ( 0.0,  1.0,  0.0), pointFromXYZ(0.0, -1.0, 0.0)};
    std::array<Point3D,4> sample2 = {
                pointFromXYZ( 1.0,  0.0,  0.0), 
                pointFromXYZ(0.0, 1.0, 0.0), 
                pointFromXYZ(-1.0, 0.0, 0.0),
                pointFromXYZ(0.0, -1.0, 0.0)};


}

TEST(FanTest, Fan1 ){
    DelaunayTriangulation3D dt;
    FanPoints fp(sample1.begin(), sample1.end());
    Fan fan = dt.makeFan(uPoint, dPoint, fp);
    
    EXPECT_EQ(dt.getCornerCount(), 5);
    EXPECT_EQ(dt.getFaceCount(), 2);
    EXPECT_EQ(dt.getVertexCount(), 4);
    EXPECT_EQ(dt.getDomainCount(), 1);
    
    auto tris = fan.getTriangles();
    EXPECT_EQ(tris.size(), 2);
    
    EXPECT_TRUE(exactEqual(fan.getBotPoint(), dPoint));
    EXPECT_TRUE(exactEqual(fan.getTopPoint(), uPoint));
    
    return;
}

TEST(FanTest, Fan2){
    DelaunayTriangulation3D dt;
    FanPoints fp(sample2.begin(), sample2.end());
    Fan fan = dt.makeFan(uPoint, dPoint, fp);
    
    EXPECT_EQ(dt.getCornerCount(), 9);
    EXPECT_EQ(dt.getFaceCount(), 4);
    EXPECT_EQ(dt.getVertexCount(), 6);
    EXPECT_EQ(dt.getDomainCount(), 1);
    
    return;
}
