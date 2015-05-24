#include "TestInclude.h"

using namespace CrystalMesh;
using namespace Mathbox;
using namespace Geometry;
using namespace Toolbox;
using namespace Delaunay3;
using namespace Subdiv3;

namespace{

	using namespace Subdiv3;

	class VertexTester
	: public ::testing::Test{

	private:


	protected:

            Delaunay3::DelaunayTriangulation3D mDT;


	};
        
        Point3D p0 = Point3D::zero;
        Point3D p1 = pointFromXYZ(1.0, 1.0, 1.0);
        
        VertexData data0 = vertexDataFrom(p0);
}

TEST_F(VertexTester, makeVertex){
    
    Vertex* vertex = mDT.makeVertexWith(data0);
    
    MUST_BE(vertex != nullptr);
    
    Point3D point = pointOf(vertex);
    void const * prop = propertyPtrOf(vertex);
    EXPECT_TRUE(exactEqual(point, p0));
    EXPECT_EQ(prop, nullptr);
    EXPECT_EQ(vertex->mpOut, nullptr);
    
    VertexData vd = vertexDataOf(vertex);
    
    EXPECT_TRUE(exactEqual(vd.mPoint, p0));
    EXPECT_EQ(vd.mpPropPtr, nullptr);
}
