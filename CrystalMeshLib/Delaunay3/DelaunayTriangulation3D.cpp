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

//		Triangle const DelaunayTriangulation3D::makeTriangle(){
//			auto e0 = mpManifold->makeFacetEdge();
//			auto e1 = mpManifold->makeFacetEdge();
//			auto e2 = mpManifold->makeFacetEdge();
//
//			mpManifold->spliceEdges(*e0, *e1);
//			mpManifold->spliceEdges(*e1, *e2);
//
//			auto ring = mpManifold->makeDualEdgeRing();
//
//			mpManifold->linkEdgeRingAndFacetEdges(*ring, *e0->getDual());
//
//			Triangle result;
//			result.mpDualEdgeRing = e0->getDual()->getDirectedEdgeRing();
//
//			return result;
//		}

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

			void linkVertexDataVertex(VertexData * apData, Subdiv3::Vertex * apVertex){
				MUST_BE(notNullptr(apVertex));
				MUST_BE(notNullptr(apData));
				MUST_BE(isNullptr(apVertex->mpData));

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

		Tet const DelaunayTriangulation3D::makeTetrahedron(Math::Geometry::Point3D const aTetPoint[4]){

			auto tet = constructTetInComplex(*this->mpManifold);
			auto itsVerts = tet.getVertices();

			for (Index i = 0 ; i<4; i++){
				auto vd = makeVertexData(aTetPoint[i], nullptr);
				linkVertexDataVertex(vd, itsVerts.mpVert[i]);
			}

			return tet;

		}


//		Tetraeder const DelaunayTriangulation3D::makeTetrahedron(){
//
//			Tetraeder result;
//
//			Triangle tri[4];
//			Subdiv3::Vertex* verts[4];
//
//			// four primal vertices,
//			// four tris
//			for (Counter i = 0; i<4; i++){
//				tri[i] = makeTriangle();
//				verts[i] = mpManifold->makePrimalVertex();
//			}
//
//			// two dual verts
//			auto extr = mpManifold->makeDualVertex();
//			auto intr = mpManifold->makeDualVertex();
//
//			EdgeArray ea0 = edgeArrayOf(tri[0]);
//			EdgeArray ea1 = edgeArrayOf(tri[1]);
//			EdgeArray ea2 = edgeArrayOf(tri[2]);
//			EdgeArray ea3 = edgeArrayOf(tri[3]);
//
//			mpManifold->spliceFacets(*ea0.mArray[0], *ea1.mArray[0]->getClock());
//			mpManifold->spliceFacets(*ea0.mArray[1], *ea1.mArray[0]->getClock());
//			mpManifold->spliceFacets(*ea0.mArray[2], *ea1.mArray[0]->getClock());
//
//			mpManifold->spliceFacets(*ea1.mArray[2], *ea2.mArray[1]->getClock());
//			mpManifold->spliceFacets(*ea2.mArray[2], *ea3.mArray[1]->getClock());
//			mpManifold->spliceFacets(*ea3.mArray[2], *ea1.mArray[1]->getClock());
//
//			// constructing edge rings for tet's corner:
//			Subdiv3::EdgeRing* ring[6];
//			for (Counter c = 0; c < 6; c++){
//				ring[c] = mpManifold->makePrimalEdgeRing();
//			}
//			// link them..
//			mpManifold->linkEdgeRingAndFacetEdges(*ring[0], *ea0[0]);
//			mpManifold->linkEdgeRingAndFacetEdges(*ring[1], *ea0[1]);
//			mpManifold->linkEdgeRingAndFacetEdges(*ring[2], *ea0[2]);
//
//			mpManifold->linkEdgeRingAndFacetEdges(*ring[3], *ea1[2]);
//			mpManifold->linkEdgeRingAndFacetEdges(*ring[4], *ea2[2]);
//			mpManifold->linkEdgeRingAndFacetEdges(*ring[5], *ea3[2]);
//
//			// linking the primal vertices:
//			mpManifold->linkVertexDirectedEdgeRings(*verts[0], ring[3]->operator [](0));
//			mpManifold->linkVertexDirectedEdgeRings(*verts[1], ring[2]->operator [](0));
//			mpManifold->linkVertexDirectedEdgeRings(*verts[2], ring[0]->operator [](0));
//			mpManifold->linkVertexDirectedEdgeRings(*verts[3], ring[1]->operator [](0));
//
//			// prepare result:
//			for (Counter i = 0; i < 4; i++){
//				result.mVerts[i] =  vertexOf(verts[i]);
//				result.mBounds[i] = clockedTriangle(tri[i]);
//			}
//
//			// link dual  verts:
//			Subdiv3::DirectedEdgeRing * pToOuter = result.mBounds[0].mpDualEdgeRing;
//			Subdiv3::DirectedEdgeRing * pToInner = pToOuter->getSym();
//
//
//			mpManifold->linkVertexDirectedEdgeRings(*extr, *pToInner);
//			mpManifold->linkVertexDirectedEdgeRings(*intr, *pToOuter);
//
//			return result;
//		}


	}

}




