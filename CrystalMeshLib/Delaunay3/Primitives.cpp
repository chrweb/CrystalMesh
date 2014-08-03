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
			std::vector<FacetEdge*> collected;

			auto collector = [&collected](Subdiv3::FacetEdge & arg){
				collected.push_back(arg.getInvEnext()->getClock());
			};

			Subdiv3::forEachElementInFnextRing(*mpCorner->getRingMember(), collector);

			return toThreeTuple(collected);
		}


		FacetEdgeThreeTuple const Blossom::getFanAdapter() const{

			return mTuple;
		}

		Triangle const getCounterOrientedOf(Triangle const aTri){
			Triangle result;
			result.mpDualEdgeRing = aTri.mpDualEdgeRing->getSym();
			return result;
		}


		namespace  {

			Math::Geometry::Point3D const pointOf(Subdiv3::Vertex const * apVertex){

			}



		}  // namespace

		FacetEdgeThreeTuple const TetInteriour::getTetAdapterOf(
				Math::Geometry::Point3D const &a0,
				Math::Geometry::Point3D const &a1,
				Math::Geometry::Point3D const &a2) const{

			Math::Geometry::Point3D const point[3] = {a0, a1, a2};
			Subdiv3::DirectedEdgeRing const * dring[12];

			// Extract all directed edge ring
			for (Index i = 0; i<6; i++){

				dring[i] = &mpOuterEdgeRing[i]->getItem(0);
				dring[i+6] = &mpOuterEdgeRing[i]->getItem(1);

			}

			//ToDo: continue

			// find those with spec point
			for (auto const & currentPoint: point)){
				Subdiv3::FacetEdge * found = std::find
			}






		}






	}  // namespace Delaunay



}  // namespace CrystalMesh




