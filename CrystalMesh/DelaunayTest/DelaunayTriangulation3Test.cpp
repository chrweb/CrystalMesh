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


namespace{
    void verifyAdapter(TetInteriour::TetAdapter const & aAdapter, BoundaryPoints const & aBnd){
        for (Index i = 0; i<3; i++){
            auto const current = pointFromSubdiv3Vertex(aAdapter[i]->getOrg());
            auto const expected = aBnd[i];
            EXPECT_TRUE(exactEqual(current, expected));
        }
        return;
    }
}

//Test Tet Interiour and adapter
TEST_F(DelaunayTester, TetAdapter){
    TetIntPoints const tip = {p0, p1, p2, p3, p4};
    auto const tetInt = mDt.makeTetInterior(tip);
    
    //look for adapter, defined by boundary points:
    
    auto const adp0 = tetInt.getTetAdapterOf(bnd0[0], bnd0[1], bnd0[2]);
    auto const adp1 = tetInt.getTetAdapterOf(bnd1[0], bnd1[1], bnd1[2]);
    auto const adp2 = tetInt.getTetAdapterOf(bnd2[0], bnd2[1], bnd2[2]);
    auto const adp3 = tetInt.getTetAdapterOf(bnd3[0], bnd3[1], bnd3[2]);
    
    SCOPED_TRACE("DelaunayTester, Adapter0");
    verifyAdapter(adp0, bnd0);
    
    SCOPED_TRACE("DelaunayTester, Adapter1");
    verifyAdapter(adp1, bnd1);
    
    SCOPED_TRACE("DelaunayTester, Adapter2");
    verifyAdapter(adp2, bnd2);
    
    SCOPED_TRACE("DelaunayTester, Adapter3");
    verifyAdapter(adp3, bnd3);
    
    return;
}

//let's test the point 1-4 flip:
TEST_F(DelaunayTester, Flip1_4){
    TetPoints const tp = {p1, p0, p2, p3};
    PointInsertion pins = pointInsertionOf(p4);
    
    auto tet = mDt.makeTetrahedron(tp);
    auto result = mDt.flip1to4(tet, pins);
    
    return;
}