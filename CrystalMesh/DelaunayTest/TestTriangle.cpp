#include "TestInclude.h"

using namespace CrystalMesh;
using namespace Mathbox;
using namespace Geometry;
using namespace Toolbox;
using namespace Delaunay3;

namespace{

	using namespace Subdiv3;

	class TriangleTester
	: public ::testing::Test{

	private:


	protected:

            Delaunay3::DelaunayTriangulation3D mDT;


	};
        
        
        Point3D p0 = pointFromXYZ(0.0, 0.0, 0.0);
        Point3D p1 = pointFromXYZ(1.0, 0.0, 0.0);
        Point3D p2 = pointFromXYZ(0.0, 0.5, 0.0);

        void validSingletonTrianlge(Triangle const & aTri){
            
            // exepect a well annotated directed edge ring
            auto dRing0 = aTri.mpDualEdgeRing;
            EXPECT_TRUE(notNullptr(dRing0));

            // clocking returns a triangle with sym edge ring
            auto trig1 = aTri.getCounterOriented();
            EXPECT_EQ(dRing0->getSym(), trig1.mpDualEdgeRing);

            //well defined bounds:
            auto bnds = aTri.getBoundaryEdges();
            EXPECT_EQ(bnds[0]->getEnext(), bnds[1]);
            EXPECT_EQ(bnds[1]->getEnext(), bnds[2]);
            EXPECT_EQ(bnds[2]->getEnext(), bnds[0]);
        
        }
}



TEST_F(TriangleTester, construction){

    
    Triangle trig0 = mDT.makeTriangle(vertexDataOf(p0), vertexDataOf(p1), vertexDataOf(p2));
    SCOPED_TRACE("construction");
    validSingletonTrianlge(trig0);
    
}




