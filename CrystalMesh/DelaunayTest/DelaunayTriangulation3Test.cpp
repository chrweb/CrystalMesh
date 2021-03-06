/*
 * DelaunayTriangulation3Test.cpp
 *
 *  Created on: 30.06.2014
 *      Author: christoph
 */

#include "TestInclude.h"
#include <cstdlib>
#include <algorithm>

using namespace CrystalMesh;
using namespace Delaunay3;
using namespace Mathbox;
using namespace Geometry;


namespace{

	typedef CrystalMesh::Delaunay3::DelaunayTriangulation3D::TetPoints TetPoints;
        typedef CrystalMesh::Delaunay3::DelaunayTriangulation3D::TetIntPoints TetIntPoints;
        
	Point3D const p0 = pointFromXY0(0.0, 0.0);
	Point3D const p1 = pointFromXY0(1.0, 0.0);
	Point3D const p2 = pointFromXY0(0.5, 1.0);
	Point3D const p3 = pointFromXYZ(0.5, 0.5, 1.0);
        Point3D const p4 = pointFromXYZ(0.5, 0.5, 0.25);
	


	typedef CrystalMesh::Delaunay3::Triangle::BoundaryPoints BoundaryPoints;

	// Expect this Boundarypoints or cyclic permutations:
	BoundaryPoints const bnd0 = BoundaryPoints{ p0, p2, p1};
	BoundaryPoints const bnd1 = BoundaryPoints{ p0, p1, p3};
	BoundaryPoints const bnd2 = BoundaryPoints{ p1, p2, p3};
	BoundaryPoints const bnd3 = BoundaryPoints{ p0, p3, p2};

	// struct for checking results:
        std::array<BoundaryPoints,4> expectedBounds = {bnd0, bnd1, bnd2, bnd3};
        
	// Criteria: both BoundaryPoints hold the same set of points:
	bool const allContained(BoundaryPoints const & bnds, Triangle::BoundaryPoints const & triBnd){
            
            auto pred = [](Point3D const & p0, Point3D const & p1) -> bool{
                return exactEqual(p0, p1);
            };
            
            return std::is_permutation(bnds.begin(), bnds.end(), triBnd.begin(), pred);            
        }
        
        bool const sameCyclicOrder(BoundaryPoints const & aBnds, Triangle::BoundaryPoints & aTriBnds){
            const Point3D first = aBnds.front();
            auto finder = [&first](Point3D const & aPoint) -> bool{
                return exactEqual(first, aPoint);
            };
            
            auto position = std::find_if(aTriBnds.begin(), aTriBnds.end(), finder);
            MUST_BE(position != aTriBnds.end());
            //position to front, preseve orientation:
            Triangle::BoundaryPoints rotated;
            
            std::rotate_copy(aTriBnds.begin(), position, aTriBnds.end(), rotated.begin());
            //all points are exact equal:
            for (Index i = 0; i<3; i++){
                if (!exactEqual(aBnds[i], rotated[i]))
                    return false;
            }
            
            return true;
        }
        
        void testTetConstruction(Tet const & aTet){
            // its triangles:
            auto tris = aTet.getTriangles();
            // its boundary points:
             std::array<Triangle::BoundaryPoints, 4> trisBnds = {
                tris[0].getBoundaryPoints(), 
                tris[1].getBoundaryPoints(), 
                tris[2].getBoundaryPoints(), 
                tris[3].getBoundaryPoints()};

            // a stack with all expected bnds:
            std::vector<BoundaryPoints> stack(expectedBounds.begin(), expectedBounds.end());

            while(! stack.empty()){

                auto currentBound = stack.back();
                stack.pop_back();

                //find this currentBound points in tet's triangle
                auto equal = [&currentBound](Triangle::BoundaryPoints const & aTriangleBnds) ->bool{
                    return allContained(currentBound, aTriangleBnds);
                };

                //currentbound exists once 
                EXPECT_EQ(1 , std::count_if(trisBnds.begin(), trisBnds.end(), equal));

                //This bound must be found
                auto result = std::find_if(trisBnds.begin(), trisBnds.end(), equal);

                //if not, breakup:
                if (result == trisBnds.end())
                    return;

                //check for expected cyclic permututation
                EXPECT_TRUE(sameCyclicOrder(currentBound, *result));
            }

        return;
    }

	class DelaunayTester
	: public ::testing::Test{

	private:

	public:

		CrystalMesh::Delaunay3::DelaunayTriangulation3D mDt;
	};
}

TEST_F(DelaunayTester, Tet0){
    // Tetpoints to construct a tet
    TetPoints const tp = {p0, p1, p2, p3};
    auto tet = mDt.makeTetrahedron(tp);

    SCOPED_TRACE("DelaunayTester, Tet0");
    testTetConstruction(tet);
}

//let's take a different order
TEST_F(DelaunayTester, Tet1){
    TetPoints const tp = {p1, p0, p2, p3};
    auto tet = mDt.makeTetrahedron(tp);
    SCOPED_TRACE("DelaunayTester, Tet1");
    testTetConstruction(tet);
}

//and another one:
TEST_F(DelaunayTester, Tet2){
    TetPoints const tp = {p1, p3, p2, p0};
    auto tet = mDt.makeTetrahedron(tp);
    SCOPED_TRACE("DelaunayTester, Tet2");
    testTetConstruction(tet);
}

namespace {
    
    Corner const invalidCorner = {nullptr, nullptr}; 
    
    bool isValidCorner(Corner aCorner){
        return (aCorner.mFnext != nullptr) && (aCorner.mRef != nullptr);
    }

    Delaunay3::Corner findCorner(Point3D const & aOrg, Point3D const & aDest, Tet::Corners const &aList ){
        
        for (auto const &current: aList){
            Point3D const refOrg = pointFromSubdiv3Vertex(current.mRef->getOrg());
            Point3D const refDest = pointFromSubdiv3Vertex(current.mRef->getDest());
            
            //ceck forward
            if (exactEqual(refOrg, aOrg) && exactEqual(refDest, aDest))
                return current;
            
            if (exactEqual(refOrg, aDest) && exactEqual(refDest, aOrg))
                return current;
        }
        
        return invalidCorner;    
    }
}

TEST_F(DelaunayTester, TetCorners){
    using namespace Subdiv3;
    TetPoints const tp = {p0, p1, p2, p3};
    auto tet = mDt.makeTetrahedron(tp);
    Tet::Corners const corners = tet.getCorners();
    
    Corner c0 = findCorner(p0, p1, corners);
    Corner c1 = findCorner(p0, p2, corners);
    Corner c2 = findCorner(p0, p3, corners);
    Corner c3 = findCorner(p1, p2, corners);
    Corner c4 = findCorner(p1, p3, corners);
    Corner c5 = findCorner(p2, p3, corners);
    
    EXPECT_TRUE(isValidCorner(c0));
    EXPECT_TRUE(isValidCorner(c1));
    EXPECT_TRUE(isValidCorner(c2));
    EXPECT_TRUE(isValidCorner(c3));
    EXPECT_TRUE(isValidCorner(c4));
    EXPECT_TRUE(isValidCorner(c5));
    
    Corner cornerArray[] = {c0, c1, c2, c3, c4, c5};
    
    Vertex* toInnerDomain = tet.mpDualVertex;
    Vertex* toOuterDomain = tet.getTriangleAt(0).mpDualEdgeRing->getSym()->getOrg();
    
    for (int i = 0; i<6; i++){
        auto & ref = cornerArray[i].mRef;
        auto & next = cornerArray[i].mFnext;
        EXPECT_EQ(ref->getFnext(), next);
        EXPECT_TRUE(ref->getDual()->getOrg() == toOuterDomain);
        EXPECT_TRUE(next->getDual()->getOrg() == toInnerDomain);
    }
    
    
    
}




//Test Tet Interiour and adapter
TEST_F(DelaunayTester, TetAdapter){
    using namespace Subdiv3;
    //p4 is the in tet point
    TetIntPoints const tip = {p0, p1, p2, p3, p4};
    auto const tetInt = mDt.makeTetInterior(tip);
    
    //get adpaters
    std::array<FacetEdge*,6> adapters = {
        tetInt.getAdapterOf(p0, p1),
        tetInt.getAdapterOf(p0, p2),
        tetInt.getAdapterOf(p0, p3),
        tetInt.getAdapterOf(p1, p2),
        tetInt.getAdapterOf(p3, p1),
        tetInt.getAdapterOf(p3, p2),
        };
    
    
    for (auto const current: adapters){
        EXPECT_TRUE(current!=nullptr);
    }
    return;
}


//let's test the point 1-4 flip:
TEST_F(DelaunayTester, Flip1_4){
    TetPoints const tp = {p1, p0, p2, p3};
    PointInsertion pins = pointInsertionOf(p4);
    
    auto tet = mDt.makeTetrahedron(tp);
    Tet outerDomain = tet.adjancentTetAt(0);
    
    //tet is adjancent to the aouter domain with all its faces:
    EXPECT_TRUE(outerDomain==tet.adjancentTetAt(1));
    EXPECT_TRUE(outerDomain==tet.adjancentTetAt(2));
    EXPECT_TRUE(outerDomain==tet.adjancentTetAt(3));
    
    auto result = mDt.flip1to4(tet, pins);
    
    EXPECT_TRUE(result.result ==Flip1To4::Result::success);
    
    //outer domain it adjacent to 4 different inner domains:
    std::array<Tet,4> inner= {  outerDomain.adjancentTetAt(0), 
                                outerDomain.adjancentTetAt(1),
                                outerDomain.adjancentTetAt(2),
                                outerDomain.adjancentTetAt(3)};
    //4 different domains?
    auto it = std::unique(inner.begin(), inner.end());
    EXPECT_TRUE(it = inner.end());
    //not domain equal to outer=
    for (auto const & domain: inner){
        EXPECT_TRUE(domain!=outerDomain);
    }
    
     
    return;
}

TEST_F(DelaunayTester, Flip2_3){
    //create test setup.
    //Firstly I'll only take care for topological issues
    TetPoints const tp = {p1, p0, p2, p3};
    PointInsertion pins = pointInsertionOf(p4);
    
    auto tet = mDt.makeTetrahedron(tp);
    Tet outerDomain = tet.adjancentTetAt(0);
    
    mDt.flip1to4(tet, pins);
    
    //now let's get 3 representative inner domains:
    Tet inner0 = outerDomain.adjancentTetAt(0);
    Tet inner1 = outerDomain.adjancentTetAt(1);
    // lets get ther common bound:
    Triangle  bound = inner0.commonBoundaryWith(inner1);
    EXPECT_TRUE(bound!=Triangle::invalid);
    
    Flip2To3 result = mDt.flip2to3(bound);
    
    //auto vertsIntersection = intersectionOf(inner0, inner1);
    //auto vertsDiff = symmetricDifferenceOf(inner0, inner1);
    
    //EXPECT_TRUE(vertsIntersection.size() == 3);
    //EXPECT_TRUE(vertsDiff.size() == 2);
    
    //Subdiv3::
    //if (inner0 )
    
    return;
    

}
 