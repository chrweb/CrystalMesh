/*
 * DelaunayTriangulation3Test.cpp
 *
 *  Created on: 30.06.2014
 *      Author: christoph
 */

#include "../TestInclude.h"
#include <cstdlib>

using namespace CrystalMesh;
using namespace Math;
using namespace Geometry;

TEST(Delaunay3, TriangleTopology){
	using namespace Delaunay3;

	DelaunayTriangulation3D dt;

	auto triangle = dt.makeTriangle();
}

//TEST(Delaunay3, TetTopology){
//	using namespace Delaunay3;
//
//	DelaunayTriangulation3D dt;
//
//	auto tet = dt.makeTetrahedron();
//
//}


