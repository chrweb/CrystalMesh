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
#include <bits/stl_tree.h>


namespace CrystalMesh{


	namespace Delaunay3{
            
            PointInsertion pointInsertionOf(Mathbox::Geometry::Point3D const & aPoint){
                PointInsertion result;
                result.mPoint = aPoint;
                return result;
            }

            
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
                        result[4] = aPoint;
                        
                        return result;
                    } 
                    
                    Subdiv3::DirectedEdgeRing* directedEdgeRingFromTriangle(Triangle const& aTri){
                        return aTri.mpDualEdgeRing;
                    }
                    
                    
                    bool const inLexicographicalOrder(Subdiv3::Vertex const * pV0, Subdiv3::Vertex const * pV1){
                        auto const p0 = pointFromSubdiv3Vertex(pV0);
                        auto const p1 = pointFromSubdiv3Vertex(pV1);
                        return inLexicographicalOrder(p0, p1);
                    }
                } 
                
                Flip1To4 const DelaunayTriangulation3D::flip1to4(Tet& aTetToFlip, PointInsertion const aIns){
                    using namespace Subdiv3;
                    //construct to inner complex
                    auto const tetIntPoints = getTetIntPointsOf(aTetToFlip, aIns.mPoint);
                    TetInteriour innerComplex  = makeTetInterior(tetIntPoints);
                    
                    //get adapters
                    Tet::Corners  const corners = aTetToFlip.getCorners();
                    std::array<FacetEdge*, 6> adapters;
                    
                    //get triangles outer boundary faces
                    Tet:: Triangles const tetsTriangles = getTriangleArrayOf(aTetToFlip);
                    
                    
                    for (Index i = 0 ; i<6; i++){
                        adapters[i]= innerComplex.getAdapterOf(corners[i]);
                    }
                    
                    //Tet' vertices:
                    Tet::Vertices tetVerts = aTetToFlip.getVertices();
                    //inner complex vertices
                    TetInteriour::Vertices intVerts = innerComplex.getVertices();
                    
                    //destroy the tet
                    destroyTet(aTetToFlip);
                    
                    //do topological operations
                    for (Index i = 0; i<6; i++){
                        FacetEdge* fromTet= corners[i].mRef;
                        FacetEdge* fromInnerComplex = adapters[i];
                        
                        mpManifold->spliceFacets(*fromTet, *fromInnerComplex);
                        
                        //update edge rings:
                        EdgeRing* tetEdgeRing = fromTet->getDirectedEdgeRing()->getEdgeRing();
                        EdgeRing* innerEdgeRing = fromInnerComplex->getDirectedEdgeRing()->getEdgeRing();
                        
                        unifyEdgeRings(tetEdgeRing, innerEdgeRing);
                    }
                    
                    //update verices:
                    //sort lexicogrphical
                   
                    auto sortedTetVerts = tetVerts;
                    auto sortedInnerVerts = intVerts.mAtCorners;
                    
                    std::sort(sortedInnerVerts.begin(), sortedInnerVerts.end(), inLexicographicalOrder);
                    std::sort(sortedTetVerts.begin(), sortedTetVerts.end(), inLexicographicalOrder);
                    
                    for (Index i = 0; i < 4; i++){
                        Vertex* fromTet = sortedTetVerts[i];
                        Vertex* fromInner = sortedInnerVerts[i];
                        unifyVertices(fromInner, fromTet);
                    }
                    
                    //create four new bodies
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
                    
                    //collect all boundary faces:
                    typedef std::array<DirectedEdgeRing*,16> OrientedFaces;
                    OrientedFaces orientedFaces = { nullptr, nullptr, nullptr, nullptr, 
                                                    nullptr, nullptr, nullptr, nullptr,
                                                    nullptr, nullptr, nullptr, nullptr,
                                                    nullptr, nullptr, nullptr, nullptr};
                    
                    //copy all in one buffer
                    for (Index i = 0; i<4; i++){
                        AdjacentRings adj = getAdjacentRingsOf(*bodies[i]);
                        auto dest = orientedFaces.begin() + (4*i);
                        std::copy(adj.begin(), adj.end(), dest);
                    }
                    
                    typedef std::array<EdgeRing*,16> Faces;
                    Faces faces;
                    auto transformer = [](DirectedEdgeRing* ring)->EdgeRing*{
                        ring->getEdgeRing();
                    };
                    
                    std::transform(orientedFaces.begin(), orientedFaces.end(), faces.begin(), transformer);
                    
                   
                    std::sort(faces.begin(), faces.end());
                    auto const uniqueEnd = std::unique(faces.begin(), faces.end());
                    
                    SHOULD_BE(uniqueEnd-faces.begin() == 10);
                    
                    auto toTriangle = [](EdgeRing* ring)->Triangle {
                        return triangleOf(&ring->getItem(0));
                    };
                    
                    std::transform(faces.begin(), uniqueEnd, result.tris.begin(), toTriangle);
                    
                    return result;
                }
                
                
                Flip2To3 DelaunayTriangulation3D::flip2to3(Triangle& aTriangleToFlip){
                    Tet tet0 = aTriangleToFlip.upperTet();
                    Tet tet1 = aTriangleToFlip.lowerTet();
                    //getting top/bottom points
                    auto symDiff = symmetricDifferenceOf(tet0, tet1);
                    //triangle holds fanpoints:
                    auto triVerts = aTriangleToFlip.getBoundaryVertices();
                    
                    SHOULD_BE(symDiff.size() == 2);
                    
                    if (! tet0.isPartOf(symDiff[0])){
                        std::swap(symDiff[0], symDiff[1]);
                    }
                    
                    TopBottomPoints tbPoints;
                    FanPoints fanPoints;
                    
                    std::transform(symDiff.begin(), symDiff.end(), tbPoints.begin(), pointFromSubdiv3Vertex);
                    std::transform(triVerts.begin(), triVerts.end(), fanPoints.begin(), pointFromSubdiv3Vertex);
                    
                    //construct the fan:
                    TetInteriourFan const fan = makeFan3(tbPoints, fanPoints);
                    
                    //destoy the tets:
                    destroyTet(tet0);
                    destroyTet(tet1);
                    
                    //destroy separating bound
                    separateTriangle(aTriangleToFlip);
                    destroyTriangle(aTriangleToFlip);
                    
                    //construct a temp domain:
                    Domain domain = {makeBody()};
                    
                    //get its corners:
                    auto corners = domain.getCorners();
                    
                    //exclude corners with fanPoints:
                    auto finder = [&fanPoints](Corner const& aCorner)-> bool{
                        if (aCorner.representsSegment(fanPoints[0], fanPoints[1]))
                            return false;
                        
                        if (aCorner.representsSegment(fanPoints[1], fanPoints[2]))
                            return false;
                        
                        
                        if (aCorner.representsSegment(fanPoints[2], fanPoints[0]))
                            return false;
                        
                        return true;
                    };
                    
                    auto range = std::partition(corners.begin(), corners.end(), finder);
                    
                    //copy the valid set of corners:
                    std::vector<Corner> validCorners(corners.begin(), range);
                    
                    //do topologic ops:
                    for (Corner& corner :validCorners){
                        Subdiv3::FacetEdge * adapter = fan.getAdapterOf(corner);
                        SHOULD_BE(adapter!=nullptr);
                        mpManifold->spliceFacets(*corner.mRef, *adapter);
                        //unify edge ring for each splice operation
                        auto ring0 = corner.mRef->getDirectedEdgeRing()->getEdgeRing();
                        auto ring1 = adapter->getDirectedEdgeRing()->getEdgeRing();
                        unifyEdgeRings(ring0, ring1);
                    }
                    
                    //unify vertices:
                    auto domainVerts = domain.getVertices();
                    auto innerVerts = fan.getVertices();
                    
                    std::sort(domainVerts.begin(), domainVerts.end(), inLexicographicalOrder);
                    std::sort(innerVerts.begin(), innerVerts.end(), inLexicographicalOrder);
                    
                    SHOULD_BE(domainVerts.size() == innerVerts.size());
                    for (Index i = 0; i < domainVerts.size(); i++){
                        //unifyVertices(domainVerts[i], innerVerts[i]);
                    }
                    
                    //destroy domain:
                    destroyDomain(domain);
                    
                    //..and construct 3 new:
                    std::array<Subdiv3::Vertex*,3> tets = {makeBody(), makeBody(), makeBody()};
                    // links them
                    TetInteriourFan::Triangles tris = fan.getTriangles();
                    
                    SHOULD_BE(tets.size() == tris.size());
                    
                    for (Index i = 0; i<3; i++){
                        auto currentDomain = tets[i];
                        auto currentRing = directedEdgeRingFromTriangle(tris[i]);
                        mpManifold->linkVertexDirectedEdgeRings(*currentDomain, *currentRing);
                    }
                    
                    // prepare result:
                    
                    Flip2To3 result;
                    return result;
                }
                
                
                void DelaunayTriangulation3D::unifyVertices(Subdiv3::Vertex  * apVert0, Subdiv3::Vertex  * apVert1){
                    //data of vertex1
                    VertexData * data1 = reinterpret_cast<VertexData*>(apVert1->mpData);
                
                    //get adjacent representative
                    auto adjacentRing = apVert0->getDirectedEdgeRing();
                    //dislink
                    mpManifold->dislinkVertexDirectedEdgeRings(*apVert0);
                    //delete one
                    mpManifold->deletePrimalVertex(*apVert1);
                    //delete its data:
                    mpToVetexData->deleteEntity(data1);
                    
                    //relink other
                    mpManifold->linkVertexDirectedEdgeRings(*apVert0, *adjacentRing);
                    
                    return;
                }
                    
                void DelaunayTriangulation3D::unifyEdgeRings(Subdiv3::EdgeRing* apRing0 ,Subdiv3::EdgeRing* apRing1){
                    //get ring representative
                    auto ringRep = apRing0->getItem(0).getRingMember();
                    //unlink
                    mpManifold->dislinkEdgeRing(*apRing0);
                    //delete one
                    mpManifold->deletePrimalEdgeRing(*apRing1);
                    //relink other
                    mpManifold->linkEdgeRingAndFacetEdges(*apRing0, *ringRep);
                    
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




