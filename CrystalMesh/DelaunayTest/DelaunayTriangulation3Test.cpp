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

TEST_F(DelaunayTester, MakeTriangle){
    using namespace Subdiv3;
    Triangle tri = mDt.makeTriangle();
    
    // Test a valid set of edge rings:
    auto edges = tri.getBoundaryArray();
    std::array<EdgeRing*,3>  edgeRings = {edges[0]->getDirectedEdgeRing()->getEdgeRing(), edges[1]->getDirectedEdgeRing()->getEdgeRing(), edges[2]->getDirectedEdgeRing()->getEdgeRing()};
    std::sort(edgeRings.begin(), edgeRings.end());
    auto uniqueEnd = std::unique(edgeRings.begin(), edgeRings.end());
    EXPECT_TRUE(uniqueEnd == edgeRings.end());
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
    using namespace Subdiv3;
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
    
    void validateCornerDomains(Corner const & aCorner, Vertex const * toInnerDomain, Vertex const * toOuterDomain){
        auto & ref = aCorner.mRef;
        auto & next = aCorner.mFnext;
        
        EXPECT_EQ(ref->getFnext(), next);
        EXPECT_EQ(toOuterDomain,ref->getDual()->getOrg());
        EXPECT_EQ(toInnerDomain,next->getDual()->getOrg());
        
    }
}

TEST_F(DelaunayTester, TetCorners){
    using namespace Subdiv3;
    TetPoints const tp = {p0, p1, p2, p3};
    auto tet = mDt.makeTetrahedron(tp);
    Tet::Corners const corners = tet.getCorners();
    
    std::array<Corner,6> cornerArray = {
        findCorner(p0, p1, corners),
        findCorner(p0, p2, corners),
        findCorner(p0, p3, corners),
        findCorner(p1, p2, corners),
        findCorner(p1, p3, corners),
        findCorner(p2, p3, corners)
    };
            
    Vertex* toInnerDomain = tet.mpDualVertex;
    Vertex* toOuterDomain = tet.getTriangleAt(0).mpDualEdgeRing->getSym()->getOrg();
    
    SCOPED_TRACE("in TetCorners");
    
    for (int i = 0; i<6; i++){
        Corner const& corner = cornerArray[i];
        EXPECT_TRUE(isValidCorner(corner));
        validateCornerDomains(corner, toInnerDomain, toOuterDomain);
    }
    
    //all edge rings unique?
    auto trafo  = [](Corner const & corner){
        return corner.mFnext->getDirectedEdgeRing()->getEdgeRing();
    };
    
    std::array<EdgeRing*, 6> edgeRings;
    
    std::transform(cornerArray.begin(), cornerArray.end(), edgeRings.begin(), trafo);
    std::sort(edgeRings.begin(), edgeRings.end());
    auto uniqueEnd = std::unique(edgeRings.begin(), edgeRings.end());
    EXPECT_EQ(uniqueEnd,edgeRings.end());
    
    return;
}




//Test Tet Interiour and adapter
TEST_F(DelaunayTester, TetAdapter){
    using namespace Subdiv3;
    //p4 is the in tet point
    TetIntPoints const tip = {p0, p1, p2, p3, p4};
    //points permutation:
    typedef std::array<Point3D, 2> Tuple;
    Tuple t0 = {p0, p1};
    Tuple t1 = {p0, p2};
    Tuple t2 = {p0, p3};
    Tuple t3 = {p1, p2};
    Tuple t4 = {p1, p3};
    Tuple t5 = {p2, p3};
    
    std::array<Tuple, 6> tuples = {t0, t1, t2, t3, t4, t5 };
    
    //construct tet interiour
    auto const tetInt = mDt.makeTetInterior(tip);
    
    std::vector<EdgeRing*> edgeRings;
    
    //verify adapters as expected:
    for (auto const tuple: tuples){
        auto point0 = tuple[0];
        auto point1 = tuple[1];
        
        FacetEdge * adapterFacetEdge0 = tetInt.getAdapterOf(point0, point1); 
        EdgeRing* ring0 = adapterFacetEdge0->getDirectedEdgeRing()->getEdgeRing();
        EXPECT_TRUE(exactEqual( originPointOf(adapterFacetEdge0), point0));
        EXPECT_TRUE(exactEqual( destinationPointOf(adapterFacetEdge0), point1));
        
        //vice versa:
        auto adapterFacetEdge1 = tetInt.getAdapterOf(point1, point0); 
        
        EXPECT_TRUE(exactEqual( originPointOf(adapterFacetEdge1), point1));
        EXPECT_TRUE(exactEqual( destinationPointOf(adapterFacetEdge1), point0));    
    
        EdgeRing* ring1 = adapterFacetEdge0->getDirectedEdgeRing()->getEdgeRing();
        
        EXPECT_EQ(ring0,ring1);
        edgeRings.push_back(ring0);
    }
    
    //ToDo: all edge ring unique?
    std::sort(edgeRings.begin(), edgeRings.end());
    auto toUniqueEnd = std::unique(edgeRings.begin(), edgeRings.end());
    
    EXPECT_EQ(toUniqueEnd, edgeRings.end());
    
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
    
    //check validity of corners:
    auto corners = tet.getCorners();
    
    SCOPED_TRACE("in Flip1_4");
    for (Corner const & corner : corners){
        validateCornerDomains(corner, tet.mpDualVertex, outerDomain.mpDualVertex);
    }
    
    
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



TEST_F(DelaunayTester, DestroyTriangle){
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
    
    Domain domain = mDt.destroyTriangle(bound);
    
    auto itsTris = domain.getTriangles();
    
    EXPECT_EQ(6, itsTris.size());
    for (auto const& triangle: itsTris){
        EXPECT_TRUE(triangle != Triangle::invalid);
    }
    
    auto itsVerts = domain.getVertices();
    EXPECT_EQ(5, itsVerts.size());
    
    auto itsCorners = domain.getCorners();
    EXPECT_EQ(9, itsCorners.size());   
}


//TEST_F(DelaunayTester, TetInteriourFan){
//    DelaunayTriangulation3D::TopBottomPoints tb = {p3, p4};
//    DelaunayTriangulation3D::FanPoints fp = {p0, p1, p2};
//    TetInteriourFan sample = mDt.makeFan3(tb, fp);
//    
//    return;
//}

//ToDo: Reactivate
//TEST_F(DelaunayTester, Flip2_3){
//    //create test setup.
//    //Firstly I'll only take care for topological issues
//    TetPoints const tp = {p1, p0, p2, p3};
//    PointInsertion pins = pointInsertionOf(p4);
//    
//    auto tet = mDt.makeTetrahedron(tp);
//    Tet outerDomain = tet.adjancentTetAt(0);
//    
//    mDt.flip1to4(tet, pins);
//    
//    //now let's get 3 representative inner domains:
//    Tet inner0 = outerDomain.adjancentTetAt(0);
//    Tet inner1 = outerDomain.adjancentTetAt(1);
//    // lets get ther common bound:
//    Triangle  bound = inner0.commonBoundaryWith(inner1);
//    EXPECT_TRUE(bound!=Triangle::invalid);
//    
//    Flip2To3 result = mDt.flip2to3(bound);
    
    //auto vertsIntersection = intersectionOf(inner0, inner1);
    //auto vertsDiff = symmetricDifferenceOf(inner0, inner1);
    
    //EXPECT_TRUE(vertsIntersection.size() == 3);
    //EXPECT_TRUE(vertsDiff.size() == 2);
    
    //Subdiv3::
    //if (inner0 )
    
//    return;
//    
//
//}
