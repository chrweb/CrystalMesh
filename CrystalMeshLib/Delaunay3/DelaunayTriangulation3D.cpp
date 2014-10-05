/*
 * DelaunayTriangulation3.cpp
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#include "DelaunayTriangulation3D.h"
#include "../Subdiv3/Subdiv3Prototypes.h"
#include "../Subdiv3/MaintenerTemplate.h"
#include "../Subdiv3/FacetEdge.h"
#include "ComplexConstruction.h"
#include "../Math/Geometry.h"
#include <algorithm>
#include <iterator>

namespace CrystalMesh{


	namespace Delaunay3{

		class VertexDataContainer
		:public Subdiv3::EntityMaintener<VertexData>
		 {};


		DelaunayTriangulation3D::DelaunayTriangulation3D()
		: mpManifold(new Subdiv3::Manifold)
		, mpToVetexData(new VertexDataContainer)
		{

		}

		DelaunayTriangulation3D::~DelaunayTriangulation3D(){
			delete mpManifold;
			delete mpToVetexData;
		}

		namespace{
			Triangle const triangleOf(Subdiv3::DirectedEdgeRing * apRing){
				Triangle result;
				result.mpDualEdgeRing = apRing;
				return result;
			}

		}


		namespace {

			typedef uint32_t Counter;

			struct EdgeArray{
				Subdiv3::FacetEdge * mArray[3];

				Subdiv3::FacetEdge * operator[](Counter i){
					return mArray[i];
				}
			};

			EdgeArray const edgeArrayOf(Triangle const & aTri){
				using namespace Subdiv3;
				EdgeArray result;
				int counter = 0;

				auto collector = [&result, &counter](FacetEdge  & aInst){
					MUST_BE(counter < 3);
					result.mArray[counter] = aInst.getDual();
					counter++;
				};

				forEachElementInFnextRing(*aTri.mpDualEdgeRing->mpRingMember, collector);

				return result;
			}

			Triangle const clockedTriangle(Triangle const & aTri){
				Triangle result;
				result.mpDualEdgeRing = aTri.mpDualEdgeRing->mpRingMember->getClock()->getDirectedEdgeRing();
				return result;
			}

			Vertex const vertexOf(Subdiv3::Vertex  * aVert){
				Vertex result;
				result.mpPrimalVertex = aVert;
				return result;
			}
		}

		namespace{

			VertexData const vertexDataOf(Math::Geometry::Point3D const & aPoint, void * apPropPtr){
				VertexData result{ aPoint, apPropPtr};
				return result;
			}

			VertexData const vertexDataOf(Math::Geometry::Point3D const & aPoint){
				VertexData result{ aPoint, nullptr};
				return result;
			}

			bool noData(Subdiv3::Vertex const * apVertex){
							MUST_BE(notNullptr(apVertex));
							return isNullptr(apVertex->mpData);
			}

			void linkVertexDataVertex(VertexData * apData, Subdiv3::Vertex * apVertex){
				MUST_BE(notNullptr(apVertex));
				MUST_BE(notNullptr(apData));
				MUST_BE(noData(apVertex));

				apVertex->mpData = reinterpret_cast<void*>(apData);

				return;
			}


		}


		TetInteriour const DelaunayTriangulation3D::makeTetInterior( Math::Geometry::Point3D const  (aTetPoints)[5] )
		{
			// construct interior, given five Points: [0]...[3] tetBounds
			//										  [4] in-tet-point

			// construct the topological structure
			TetInteriour tetInterior = constructTetInteriourInComplex(*this->mpManifold);
			TetInteriour::Vertices itsVerts = tetInterior.getVertices();

			// for tet bounds...
			for (Index i = 0; i < 4; i++)
			{
				auto vertexData= makeVertexData(aTetPoints[i], nullptr);
				linkVertexDataVertex(vertexData, itsVerts.mAtCorners[i]);
			}

			// in-tet-vertex
			auto inTetData = makeVertexData(aTetPoints[4], nullptr);
			linkVertexDataVertex(inTetData, itsVerts.mInTet);

			return tetInterior;
		}

		VertexData * DelaunayTriangulation3D::makeVertexData(Math::Geometry::Point3D const & aPoint, void * apPropPtr)
		{
			auto result = mpToVetexData->constructEntity();
			result->mPoint = aPoint;
			result->mpPropPtr = apPropPtr;
			return result;
		}

		Tet const DelaunayTriangulation3D::makeTetrahedron(TetPoints const & aTetPoints){
			using namespace CrystalMesh;
			using namespace Math;
			using namespace Geometry;


			auto const eps = 1e-6;

			// [0]-[2]: basic trianlge
			Point3D points[4];
			std::copy(aTetPoints.begin(), aTetPoints.end(), std::begin(points));
			// plane of basic triangle
			auto const plane = planeFromThreePoints(points[0], points[1], points[2]);

			// last point above?
			switch (pointPlaneProjection(plane, aTetPoints[4],eps)){
			case PointToPlaneProjection::overPlane:
				// swap
				std::swap(points[0], points[1]);
				break;

			case PointToPlaneProjection::underPlane:
				// fine
				break;

			default:
				// very bad
				UNREACHABLE();
			}


			VertexData * vertexData[4];
			// construct vertex data:
			for(Index i = 0 ; i < 4; i++){
				vertexData[i] = makeVertexData(points[i]);
			}

			// construct tet
			auto tet = constructTetInComplex(*this->mpManifold);

			// get a bounding tri
			auto bound = tet.getTriangleAt(0).getBoundaryArray();

			//link first three vertex data:
			for (Index i = 0; i<3; i++){
				linkVertexDataVertex(vertexData[i], bound[i]->getOrg() );
			}

			// get another triangle
			bound = tet.getTriangleAt(1).getBoundaryArray();

			// look for vertex with no data,
			// give him the remaining point
			Index count(0);
			for (Index i = 0; i <=3; i++){
				if (noData(bound[i]->getOrg())){
					linkVertexDataVertex(vertexData[4], bound[i]->getOrg());
					count++;
				}
			}

			// very bad error?
			MUST_BE(count == 1);

			//done
			return tet;
		}

	}

}




