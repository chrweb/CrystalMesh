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

		Tet const constructTetInComplex(Subdiv3::Manifold & aComplex);

		Triangle const constructTriangleInComplex(Subdiv3::Manifold & aComplex);

		Fan const constructFanInComplex(Subdiv3::Manifold & aComplex);

		TetInteriour const constructTetInteriourInComplex( Subdiv3::Manifold & aComplex );

		Blossom const constructBlossomInComplex(Subdiv3::Manifold & aComplex);





	}  // namespace Delaunay3



}  // namespace CrystalMesh

