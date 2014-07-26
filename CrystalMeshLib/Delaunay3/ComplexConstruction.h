/*
 * ComplexConstruction.h
 *
 *  Created on: 25.07.2014
 *      Author: christoph
 *
 *      The construction of 3D cell complexes is error-prone,
 *      therefore here several subroutines declared which may be tested.
 */
#pragma once
#include "Primitives.h"
#include "ForwardDecs.h"

namespace CrystalMesh {


	namespace Delaunay3 {

		Triangle const constructTriangleInComplex(Subdiv3::Manifold & aComplex);





		Fan const constructFanInComplex(Subdiv3::Manifold & aComplex);


		struct TetInteriour{

			Triangle mTri[6];
			Corner mCorner[4];
			Vertex mVertex;

			FacetEdgeThreeTuple const getAdaptersFor(Triangle const & aTriangle) const;

		};

		TetInteriour const constructTetInteriourInComplex(Subdiv3::Manifold & aComplex);


		struct Blossom{
			Triangle mTri[3];

			FacetEdgeThreeTuple const getFanAdapter() const;
		};

		Blossom const constructBlossomInComplex(Subdiv3::Manifold & aComplex);





	}  // namespace Delaunay3



}  // namespace CrystalMesh

