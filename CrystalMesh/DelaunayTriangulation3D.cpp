/*
 * DelaunayTriangulation3.cpp
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#include "DelaunayTriangulation3D.h"
#include "Subdiv3Prototypes.h"
#include "MaintenerTemplate.h"
#include "FacetEdge.h"
#include "ComplexConstruction.h"
#include "../Mathbox/Mathbox.h"
#include "AdjacentDirectedEdgeRings.h"
#include <algorithm>
#include <iterator>


namespace CrystalMesh{


	namespace Delaunay3{
            
            using namespace Toolbox;

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

		}

		namespace{

			VertexData const vertexDataOf(Mathbox::Geometry::Point3D const & aPoint, void * apPropPtr){
				VertexData result{ aPoint, apPropPtr};
				return result;
			}

			VertexData const vertexDataOf(Mathbox::Geometry::Point3D const & aPoint){
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


		TetInteriour const DelaunayTriangulation3D::makeTetInterior( TetIntPoints const & aTetIntPoints)
		{
                    // construct interior, given five Points: [0]...[3] tetBounds
                    // [4] in-tet-point

                    // construct the topological structure
                    TetInteriour tetInterior = constructTetInteriourInComplex(*this->mpManifold);
                    
                    TetInteriour::Vertices itsVerts = tetInterior.getVertices();

                    // for tet bounds...
                    for (Index i = 0; i < 4; i++)
                    {
                            auto vertexData= makeVertexData(aTetIntPoints[i], nullptr);
                            linkVertexDataVertex(vertexData, itsVerts.mAtCorners[i]);
                    }

                    // in-tet-vertex
                    auto inTetData = makeVertexData(aTetIntPoints[4], nullptr);
                    linkVertexDataVertex(inTetData, itsVerts.mInTet);

                    return tetInterior;
		}

		VertexData * DelaunayTriangulation3D::makeVertexData(Mathbox::Geometry::Point3D const & aPoint, void * apPropPtr)
		{
			auto result = mpToVetexData->constructEntity();
			result->mPoint = aPoint;
			result->mpPropPtr = apPropPtr;
			return result;
		}
                
                namespace{
                    
                    DelaunayTriangulation3D::TetPoints  permutate(DelaunayTriangulation3D::TetPoints const & aPoints){
                        
                        using namespace Mathbox;
			using namespace Geometry;
                        
                        auto const plane = planeFromThreePoints(aPoints[0], aPoints[1], aPoints[2]);
                        
                        auto permutation = aPoints;
                        
                                   //FIXME: eps issue in Point projection
			//auto const eps = 1e-6;
                        
                        PointToPlaneProjection projection = pointPlaneProjection(plane, aPoints[3]);
                        
                        switch (projection){
                            case PointToPlaneProjection::overPlane:
                                // swap
                                std::swap(permutation[0], permutation[1]);
                                return permutation;

                            case PointToPlaneProjection::underPlane:
                                return permutation;

			default:
				// very bad
				UNREACHABLE;
			}    
                    }
                                
                }
        

		Tet const DelaunayTriangulation3D::makeTetrahedron(TetPoints const & aTetPoints){
			using namespace CrystalMesh;
			using namespace Mathbox;
			using namespace Geometry;

                        //Bring points into correct order:
                        TetPoints permutation = permutate(aTetPoints);
                        
                        //permutation holds in [0] to [2] a points forming a plane,
                        //[3] appears below this face.


			VertexData * vertexData[4];
			// construct vertex data:
			for(Index i = 0 ; i < 4; i++){
				vertexData[i] = makeVertexData(permutation[i]);
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
			for (Index i = 0; i <3; i++){
				if (noData(bound[i]->getOrg())){
					linkVertexDataVertex(vertexData[3], bound[i]->getOrg());
					count++;
				}
			}

			// very bad error!
			MUST_BE(count == 1);

			//done
			return tet;
		}
                
                
                namespace{
                    typedef std::array<Triangle,4> TriangleArray;
                    
                    TriangleArray const getTriangleArrayOf(Tet const & aTet){
                        TriangleArray result;
                        
                        for (Index i = 0; i<4 ;i ++){
                            result[i] = aTet.getTriangleAt(i);
                        }
                        
                        return result;
                    }
                    
                    typedef std::array<Triangle::BoundaryPoints,4> BoundaryPointArray;
                    
                    //all boundary points of the given tet:
                    BoundaryPointArray const getBoundaryPointArrayOf(Tet const & aTet){
                        
                        BoundaryPointArray result;
                        for (Index i = 0; i<4; i++){
                            auto currentTri = aTet.getTriangleAt(i);
                            result[i]= currentTri.getBoundaryPoints();
                        }
                        
                        return result;
                    }
                    
                    DelaunayTriangulation3D::TetIntPoints const getTetIntPointsOf(Tet const & aTet, Mathbox::Geometry::Point3D const & aPoint){
                        DelaunayTriangulation3D::TetIntPoints result;
                        
                        auto const vertices = aTet.getVertices();
                        
                        auto extractPoint = [](Subdiv3::Vertex * apVertex){
                            return pointFromSubdiv3Vertex(apVertex);
                        };
                        
                        //set first 4 points
                        std::transform(vertices.begin(), vertices.end(), result.begin(), extractPoint);
                        
                        //set last:
                        result[5] = aPoint;
                    } 
                    
                    Subdiv3::DirectedEdgeRing* directedEdgeRingFromTriangle(Triangle const& aTri){
                        return aTri.mpDualEdgeRing;
                    }
                } 
                
                Flip1To4 const DelaunayTriangulation3D::flip1to4(Tet& aTetToFlip, PointInsertion const aIns){
                    
                    auto const tetsTriangles = getTriangleArrayOf(aTetToFlip);
                    
                    auto const tetsBndArray = getBoundaryPointArrayOf(aTetToFlip);
                    
                    auto const tetsPoints = aTetToFlip.getVertices();
                    
                    auto const tetIntPoints = getTetIntPointsOf(aTetToFlip, aIns.mPoint);
                    
                    TetInteriour interiour  = makeTetInterior(tetIntPoints);
                    
                    //do things for each bnd triangle
                    for (Index i=0; i<4; i++){
                        auto currentTriEdges = tetsTriangles[i].getBoundaryArray();
                        auto currentBndPoints = tetsBndArray[i];  
                        auto currentAdapter = interiour.getTetAdapterOf(currentBndPoints[0], currentBndPoints[1], currentBndPoints[2]);
                        
                        //topological operations:
                        for (Index i = 0; i<3; i++){
                            //Edges tp splice
                            Subdiv3::FacetEdge * currentEdgeOnTet = currentTriEdges[i]->getInvFnext();
                            Subdiv3::FacetEdge * currentEdgeOnAdapter = currentAdapter[i];
                            
                            //Edge rings to merge
                            auto dring0 = currentEdgeOnAdapter->getDirectedEdgeRing();
                            auto dring1 = currentEdgeOnTet->getDirectedEdgeRing();
                            
                            //Vertices to merge
                            auto vert0 = currentEdgeOnAdapter->getOrg();
                            auto vert1 = currentEdgeOnTet->getOrg();
                            
                            //splice
                            mpManifold->spliceFacets(*currentEdgeOnTet, *currentEdgeOnAdapter);
                            
                            //unify linked entities:
                            unifyEdgeRings(dring0, dring1);
                            unifyVertices(vert0, vert1);
                        }
                    }
                    
                    //link dual entities:
                    
                    //destroy old body:
                    destroyTet(aTetToFlip);
                    
                    //create four new
                    typedef std::array<Subdiv3::Vertex* ,4> Bodies;
                    
                    Bodies bodies = {makeBody(), makeBody(), makeBody(), makeBody()};
                    
                    //link each one
                    for (Index i = 0; i< 4; i++){
                        auto currentDring = directedEdgeRingFromTriangle(tetsTriangles[i]);
                        auto currentVertex = bodies[i];
                        
                        mpManifold->linkVertexDirectedEdgeRings(*currentVertex, *currentDring);   
                    }
                          
                    Flip1To4 result;
                    
                    result.result = Flip1To4::Result::success;
                    
                    //fill from tet
                    for (Index i = 0 ; i < 4; i++){
                        result.tris[i] = aTetToFlip.getTriangleAt(i);
                    }
                    
                    //fill from interiour
                    for (Index i = 0; i < 6; i++){
                        result.tris[i+4] = interiour.getTriangleAt(i);
                    }
                        
                    return result;
                }
                
                void DelaunayTriangulation3D::unifyVertices(Subdiv3::Vertex  * apVert0, Subdiv3::Vertex  * apVert1){
                    //TODO: delete point of vertex
                    //get adjacent representative
                    auto adjacentRing = apVert0->getDirectedEdgeRing();
                    //dislink
                    mpManifold->dislinkVertexDirectedEdgeRings(*apVert0);
                    //delete one
                    mpManifold->deletePrimalVertex(*apVert1);
                    //relink other
                    mpManifold->linkVertexDirectedEdgeRings(*apVert0, *adjacentRing);
                    
                    return;
                }
                    
                void DelaunayTriangulation3D::unifyEdgeRings(Subdiv3::DirectedEdgeRing* apDring0 ,Subdiv3::DirectedEdgeRing* apDring1){
                    //get ring representative
                    auto ringRep = apDring0->getRingMember();
                    //unlink
                    mpManifold->dislinkEdgeRing(*apDring0->getEdgeRing());
                    //delete one
                    mpManifold->deletePrimalEdgeRing(*apDring1->getEdgeRing());
                    //relink other
                    mpManifold->linkEdgeRingAndFacetEdges(*apDring0->getEdgeRing(), *ringRep);
                    
                    return;
                }
                    
                void DelaunayTriangulation3D::destroyTet(Tet & aTet){
                    mpManifold->dislinkVertexDirectedEdgeRings(*aTet.mpDualVertex);
                    mpManifold->deleteDualVertex(*(aTet.mpDualVertex));
                    return;
                }
                
                
                Subdiv3::Vertex * DelaunayTriangulation3D::makeBody(){
                    return mpManifold->makeDualVertex();
                }


	}

}




