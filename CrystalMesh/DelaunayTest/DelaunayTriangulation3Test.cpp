/*
 * DelaunayTriangulation3Test.cpp
 *
 *  Created on: 30.06.2014
 *      Author: christoph
 */

#include "TestInclude.h"
#include <cstdlib>

using namespace CrystalMesh;
using namespace Delaunay3;
using namespace Mathbox;
using namespace Geometry;


//TODO Test  with Points
namespace{

	typedef CrystalMesh::Delaunay3::DelaunayTriangulation3D::TetPoints TetPoints;

	Point3D const p0 = pointFromXY0(0.0, 0.0);
	Point3D const p1 = pointFromXY0(0.0, 1.0);
	Point3D const p2 = pointFromXY0(0.5, 1.0);
	Point3D const p3 = pointFromXYZ(0.5, 0.5, 1.0);

	// Tetpoints to construct a tet
	TetPoints const tp = {p0, p1, p2, p3};


	typedef CrystalMesh::Delaunay3::Triangle::BoundaryPoints BoundaryPoints;

	// Expect this Boundarypoints or cyclic permutations:
	BoundaryPoints const bnd0 = BoundaryPoints{ p0, p2, p1};
	BoundaryPoints const bnd1 = BoundaryPoints{ p0, p3, p2};
	BoundaryPoints const bnd2 = BoundaryPoints{ p2, p3, p1};
	BoundaryPoints const bnd3 = BoundaryPoints{ p0, p1, p2};

	// struct for checking results:
	struct BndPointChecker{
		typedef std::array<BoundaryPoints,4> Bnds;
		typedef std::array<bool, 3> Visited;

		Bnds mBnds;
		Visited mVst;
	};

	// Factory
	BndPointChecker const createBndPointChecker(){
		BndPointChecker result;
		result.mBnds = {bnd0, bnd1, bnd2, bnd3};
		result.mVst = {false, false, false};
		return result;
	}


	// Criteria, 2 BoundaryPoints are equal:
	bool const allContained(BoundaryPoints const & a0, BoundaryPoints const & a1){
            //ToDo: Implment
            UNREACHABLE;
//		for (auto const & currentPoint: a0){
//			auto found = std::find(a1.begin() a1.end());
//			if (found == a1.end())
//				return false;
//		}
//
//		return true;
	}

	// both contain the same points, correct cyclic permutation
	bool const operator == (BoundaryPoints const & a0, BoundaryPoints const & a1){
            //TODO: implement
            UNREACHABLE;
//		auto const & point0 = a0[0];
//
//		// copy, because we're doing maipulations:
//		BoundaryPoints other;
//		std::copy(a1.begin(), a1.end(), other.begin());
//
//		auto found = std::find(other.begin(), other.end());
//		//not found? false
//		if (found == other.end())
//			return false;
//
//		// rotate to front
//		std::rotate(other.begin(), found, other.end());
//
//		//compare
//		for (Index i = 0; i<3; i++){
//			if (a0[i]!= other[i])
//				return false;
//		}
//
//		return true;
	}

	class DelaunayTester
	: public ::testing::Test{

	private:

	public:

		CrystalMesh::Delaunay3::DelaunayTriangulation3D mDt;
	};
}

TEST_F(DelaunayTester, Tet){
        //TODO: implment
	// create a tet with triangle points:
	auto tet = mDt.makeTetrahedron(tp);

	// its triangles:
	auto tris = tet.getTriangles();

	auto checker = createBndPointChecker();
//
//	// all triangles ccw?
//	for (auto const & currentTri: tris){
//		auto const itsBndPoints = currentTri.getBoundaryPoints();
//		if ()
//	}



}
