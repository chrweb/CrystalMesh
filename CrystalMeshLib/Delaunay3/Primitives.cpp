/*
 * Primitives.cpp
 *
 *  Created on: 26.07.2014
 *      Author: christoph
 */

#include "DelaunayTriangulation3D.h"
#include "../Subdiv3/Vertex.h"
#include "../Subdiv3/FacetEdge.h"
#include "../Subdiv3/DirectedEdgeRing.h"
#include "../Math/Geometry.h"
#include "Primitives.h"
#include <vector>
#include "../Misc/Checks.h"

namespace CrystalMesh {

	namespace Delaunay3 {

		using namespace Math::Geometry;

		typedef Subdiv3::FacetEdge FacetEdge;


		namespace{

			Point3D const pointFromSub3Vertex(Subdiv3::Vertex const *pVertex){
				VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
				return data.mPoint;
			}
		}

		Point3D const Vertex::getPoint() const{
			return pointFromSub3Vertex(mpPrimalVertex);
		}

		void Vertex::setPoint(Point3D const & aPoint){
			VertexData & data = *reinterpret_cast<VertexData *>(mpPrimalVertex->mpData);
			data.mPoint = aPoint;
			return;
		}

		namespace{
			Subdiv3::FacetEdge * toPointer(Subdiv3::FacetEdge const & aRef){
				return const_cast<Subdiv3::FacetEdge*>(&aRef);
			}
		}

		FacetEdgeThreeTuple const facetEdgeThreeTupleOf(Subdiv3::FacetEdge const & a0, Subdiv3::FacetEdge const & a1, Subdiv3::FacetEdge const & a2){
			FacetEdgeThreeTuple result = {toPointer(a0), toPointer(a1), toPointer(a2)};
			return result;
		}

		PointThreeTuple const pointTreeTupleOf(Math::Geometry::Point3D const & a0, Math::Geometry::Point3D const & a1, Math::Geometry::Point3D const & a2){
			PointThreeTuple result = { a0, a1, a2};
			return result;
		}

		FacetEdgeThreeTuple const Triangle::getBoundary() const{
			auto pBnd = mpDualEdgeRing->getRingMember()->getDual();

			FacetEdgeThreeTuple result = {pBnd, pBnd->getEnext(), pBnd->getEnext()->getEnext()};
			return result;
		}

		PointThreeTuple const Triangle::getPoints() const{

			auto const bnd = getBoundary();
			PointThreeTuple result;
			result.p0 = pointFromSub3Vertex(bnd.f0->getOrg());
			result.p1 = pointFromSub3Vertex(bnd.f1->getOrg());
			result.p2 = pointFromSub3Vertex(bnd.f2->getOrg());

			return result;
		}

		namespace{

			FacetEdgeThreeTuple const toThreeTuple(std::vector<FacetEdge*> & aVec){
				MUST_BE(aVec.size() == 3u);
				FacetEdgeThreeTuple result = {aVec[0], aVec[1], aVec[2]};
				return result;
			}
		}


		FacetEdgeThreeTuple const Fan::getBlossomAdapter() const{
			std::vector<FacetEdge*> colleted;

			auto collector = [&collected](Subdiv3::FacetEdge & arg){
				colleted.push_back(arg.getInvEnext());
			};

			Subdiv3::forEachElementInFnextRing*(mpCorner->getRingMember(), collector);

			return toThreeTuple(collected);

		}






	}  // namespace Delaunay



}  // namespace CrystalMesh




