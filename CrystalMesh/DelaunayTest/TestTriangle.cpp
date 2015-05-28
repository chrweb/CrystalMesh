#include "TestInclude.h"

using namespace CrystalMesh;
using namespace Mathbox;
using namespace Geometry;
using namespace Toolbox;
using namespace Delaunay3;
using namespace Subdiv3;

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
            
            //edges, edge rings:
            for (FacetEdge* current: bnds){
                DirectedEdgeRing * dring = current->getDirectedEdgeRing();
                EXPECT_TRUE(dring!=nullptr);
                EXPECT_TRUE(dring->getRingMember() == current);
            }
            
            // vertices:
            auto verts = aTri.getBoundaryVertices();
            
            //unique
            auto vertsEnd = std::unique(verts.begin(), verts.end());
            EXPECT_EQ(verts.end(), vertsEnd);
            
            //to adjancent edge rings
            for (auto const&current : verts){
                auto adj = getAdjacentFacetEdges(*current);
                EXPECT_EQ(2, adj.size());
            }
            
            //Domain:
            Vertex* domain = aTri.mpDualEdgeRing->getOrg();
            EXPECT_TRUE(domain != nullptr);
            auto adjDual = getAdjacentRingsOf(*domain);
            EXPECT_EQ(2, adjDual.size());
        }
}



TEST_F(TriangleTester, construction){

    
    Triangle trig0 = mDT.makeTriangle(vertexDataFrom(p0), vertexDataFrom(p1), vertexDataFrom(p2));
    SCOPED_TRACE("construction");
    validSingletonTrianlge(trig0);
    validSingletonTrianlge(trig0.getCounterOriented());
    
}

TEST_F(TriangleTester, findBnd){
    Triangle trig0 = mDT.makeTriangle(vertexDataFrom(p0), vertexDataFrom(p1), vertexDataFrom(p2));
    auto bnd0 = trig0.boundaryWith(p0, p1);
    auto bnd1 = trig0.boundaryWith(p1, p2);
    auto bnd2 = trig0.boundaryWith(p2, p0);
    
    EXPECT_NE(bnd0, nullptr);
    EXPECT_NE(bnd1, nullptr);
    EXPECT_NE(bnd2, nullptr);
    
    auto bndC0 = trig0.boundaryWith(p1,p0);
    auto bndC1 = trig0.boundaryWith(p2,p1);
    auto bndC2 = trig0.boundaryWith(p0,p2);
   
    EXPECT_NE(bndC0, nullptr);
    EXPECT_NE(bndC1, nullptr);
    EXPECT_NE(bndC2, nullptr);
    
    EXPECT_EQ(bndC0, bnd0->getClock());
    EXPECT_EQ(bndC1, bnd1->getClock());
    EXPECT_EQ(bndC2, bnd2->getClock());
    
    EXPECT_EQ(mDT.getCornerCount(), 3);
    EXPECT_EQ(mDT.getDomainCount(), 1);
    EXPECT_EQ(mDT.getVertexCount(), 3);
    EXPECT_EQ(mDT.getFaceCount(), 1);
}






