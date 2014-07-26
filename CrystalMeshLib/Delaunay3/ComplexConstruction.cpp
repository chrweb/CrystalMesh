/*
 * ComplexConstruction.cpp
 *
 *  Created on: 25.07.2014
 *      Author: christoph
 */

#include "../Subdiv3/Manifold.h"
#include "../Math/Geometry.h"
#include "../Subdiv3/FacetEdge.h"

#include "ComplexConstruction.h"

namespace CrystalMesh {

	namespace Delaunay3 {

		Triangle const constructTriangleInComplex(Subdiv3::Manifold & aComplex){

			auto e0 = aComplex.makeFacetEdge();
			auto e1 = aComplex.makeFacetEdge();
			auto e2 = aComplex.makeFacetEdge();

			aComplex.spliceEdges(*e0, *e1);
			aComplex.spliceEdges(*e1, *e2);

			auto ring = aComplex.makeDualEdgeRing();

			aComplex.linkEdgeRingAndFacetEdges(*ring, *e0->getDual());

			Triangle result;
			result.mpDualEdgeRing = e0->getDual()->getDirectedEdgeRing();

			return result;
		}





	}  // namespace Delaunay3



}  // namespace CrystalMesh



