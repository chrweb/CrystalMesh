/*
 * DelaunayTriangulation3.cpp
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#include <algorithm>
#include "Triangle.h"
#include "Corner.h"
#include "Tet.h"
#include "DelaunayVertex.h"
#include "DelaunayTriangulation3D.h"
#include "Subdiv3Prototypes.h"
#include "MaintenerTemplate.h"
#include "FacetEdge.h"
#include "../Mathbox/Mathbox.h"
#include "AdjacentDirectedEdgeRings.h"






namespace CrystalMesh{


	namespace Delaunay3{
            
            using namespace Mathbox;
            using namespace Geometry;
            using namespace Subdiv3;
            
            
            PointInsertion pointInsertionOf(Mathbox::Geometry::Point3D const & aPoint){
                PointInsertion result;
                result.mPoint = aPoint;
                return result;
            }

            
            using namespace Toolbox;
            using namespace Subdiv3;
           

	class VertexDataContainer
	:public Subdiv3::EntityMaintener<VertexData>
	 {};


	DelaunayTriangulation3D::DelaunayTriangulation3D()
	: mpManifold(new Subdiv3::Manifold)
	, mpToVetexData(new VertexDataContainer)
	{
                return;
	}

	DelaunayTriangulation3D::~DelaunayTriangulation3D(){
		delete mpManifold;
		delete mpToVetexData;
	}


//	namespace {
//
//            typedef uint32_t Counter;
//
//            struct EdgeArray{
//                    Subdiv3::FacetEdge * mArray[3];
//
//                    Subdiv3::FacetEdge * operator[](Counter i){
//                            return mArray[i];
//                    }
//            };
//
//            EdgeArray const edgeArrayOf(Triangle const & aTri){
//                    using namespace Subdiv3;
//                    EdgeArray result;
//                    int counter = 0;
//
//                    auto collector = [&result, &counter](FacetEdge  & aInst){
//                            MUST_BE(counter < 3);
//                            result.mArray[counter] = aInst.getDual();
//                            counter++;
//                    };
//
//                    forEachElementInFnextRing(*aTri.mpDualEdgeRing->mpRingMember, collector);
//
//                    return result;
//            }
//
//            Triangle const clockedTriangle(Triangle const & aTri){
//                    Triangle result;
//                    result.mpDualEdgeRing = aTri.mpDualEdgeRing->mpRingMember->getClock()->getDirectedEdgeRing();
//                    return result;
//            }
//
//	}

		


	
            
            
//
//	auto fanArray = fromThreeTuble(fan.getBlossomAdapter());
//	auto blosArray = fromThreeTuble(blos.getFanAdapter());
//
//	for (Index i = 0; i<3; i++){
//		aComplex.spliceFacets(*fanArray.array[i], *blosArray.array[i]);
//	}
//
//		/**
//		 * to make flipping easier, construct well-linked entities..
//		 */
//		//construct and link interior corners (edge ring size 3)
//		Subdiv3::EdgeRing * innerRing[3];
//
//		for(Index i = 0; i<3; i++){
//			innerRing[i] = aComplex.makePrimalEdgeRing();
//			aComplex.linkEdgeRingAndFacetEdges(*innerRing[i], *fanArray.array[i]);
//		}
//
//
//		TetInteriour result;
//
//		//construct and link corners with edge ring size 1 (outer ones)
//		// these can be reached by fan tuple
//		Subdiv3::FacetEdge * outerEdges[6];
//		auto & outerRing = result.mpOuterEdgeRing;
//0
//		// get linking pairs
//		for (Index i = 0; i<3; i++){
//			outerEdges[i] =   fanArray.array[i]->getEnext();
//			outerEdges[i+3] =   fanArray.array[i]->getFnext()->getEnext();
//		}
//
//		// construct and link
//		for (Index i = 0; i<6; i++){
//			outerRing[i] = aComplex.makePrimalEdgeRing();
//			aComplex.linkEdgeRingAndFacetEdges(*outerRing[i], *outerEdges[i]);
//		}
//
//		//construct vertices
//		auto &  vert = result.mpVertex;
//		for(Index i = 0; i<5; i++){
//			vert[i] = aComplex.makePrimalVertex();
//		}
//
//		// link interiour vertex:
//		aComplex.linkVertexDirectedEdgeRings(*vert[0], *fanArray.array[0]->getDirectedEdgeRing());
//
//		// collect all adjacent edge rings:
//		auto const adjRings = getAdjacentRingsOf(*vert[0]);
//
//		// link their syms with vertex 1 to 4
//		for (Index i = 1; i<5; i++){
//			aComplex.linkVertexDirectedEdgeRings(*vert[i], *adjRings[i-1]->getSym());
//		}
//
//		// prepare result:
//		return result;
//             // construct interior, given five Points: [0]...[3] tetBounds
//             // [4] in-tet-point
//
//             // construct the topological structure
//             TetInteriour tetInterior = constructTetInteriourInComplex(*this->mpManifold);
//             
//             TetInteriour::Vertices itsVerts = tetInterior.getVertices();
//
//             // for tet bounds...
//             for (Index i = 0; i < 4; i++)
//             {
//                     auto vertexData= makeVertexData(aTetIntPoints[i], nullptr);
//                     linkVertexDataVertex(vertexData, itsVerts.mAtCorners[i]);
//             }
//
//             // in-tet-vertex
//             auto inTetData = makeVertexData(aTetIntPoints[4], nullptr);
//             linkVertexDataVertex(inTetData, itsVerts.mInTet);
//
//             return tetInterior;
//	}

                
                namespace{

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
                
                Subdiv3::Vertex* DelaunayTriangulation3D::makeVertexWith(VertexData const & aData){
                    
                    auto  vertex = mpManifold->makePrimalVertex();
                    auto  data = makeVertexData(aData.mPoint, aData.mpPropPtr);
                   
             
                    linkVertexDataVertex(data , vertex );
                    return vertex;
                }
                
 
		VertexData * DelaunayTriangulation3D::makeVertexData(Mathbox::Geometry::Point3D const & aPoint, void const * apPropPtr)
		{
                    auto result = mpToVetexData->constructEntity();
                    result->mPoint = aPoint;
                    result->mpPropPtr = apPropPtr;
                    return result;
		}
                
                
                void DelaunayTriangulation3D::deleteVertexData(VertexData* pData){
                    mpToVetexData->deleteEntity(pData);
                    return;
                }
  
                
                
                Triangle DelaunayTriangulation3D::makeTriangle(VertexData const& aData0, VertexData const& aData1, VertexData const& aData2 ){
                    
                    //basic structure
                    FacetEdge* edges[3] ={ mpManifold->makeFacetEdge(), mpManifold->makeFacetEdge(),  mpManifold->makeFacetEdge()};
                    mpManifold->spliceEdges(*edges[0], *edges[1]);
                    mpManifold->spliceEdges(*edges[1], *edges[2]);
                   
			
                    //add vertices:
                    Vertex* verts[3] = {makeVertexWith(aData0), makeVertexWith(aData1), makeVertexWith(aData2)};
                    //add edge rings:
                    EdgeRing* ering[3] = {mpManifold->makePrimalEdgeRing(), mpManifold->makePrimalEdgeRing(), mpManifold->makePrimalEdgeRing()};
                    
                    //edge ring linking:
                    for (Index i = 0; i<3; i++){
                        EdgeRing * eRing = ering[i];
                        FacetEdge* facetEdge = edges[i];
                        mpManifold->linkEdgeRingAndFacetEdges(*eRing, *facetEdge);
                        
                    }
                    
                    //Vertex linking
                    for (Index i = 0; i< 3; i++){
                        Vertex * vertex = verts[i];
                        FacetEdge* facetEdge = edges[i];
                        mpManifold->linkVertexFacetEdge(*vertex, *facetEdge);
                    }
                    
                     //dual edge ring linking
                    EdgeRing* dualRing = mpManifold->makeDualEdgeRing();
		    mpManifold->linkEdgeRingAndFacetEdges(*dualRing, *edges[0]->getDual());

                    //prepare result
                    Triangle result;
                    result.mpDualEdgeRing = edges[0]->getDual()->getDirectedEdgeRing();
                    
                    //domain construction
                    makeDomainUnder(result);
                    
                    return result;
                }
                
                namespace {
                    
                    std::vector<Subdiv3::Vertex*> const collectOrgsOf(Subdiv3::FacetEdge* aFedge){
                        AdjacentFacetEdges adj = getAdjacentFacetEdges(*aFedge);
                        std::vector<Subdiv3::Vertex*>  collectedVerts; 
                        
                        for (auto current: adj){
                            collectedVerts.push_back(current->getOrg());
                        }
                        
                       
                        std::sort(collectedVerts.begin(), collectedVerts.end());
                        auto uniqueEnd = std::unique(collectedVerts.begin(), collectedVerts.end());
                       
                        std::vector<Subdiv3::Vertex*> result(collectedVerts.begin(), uniqueEnd);
                        
                        return result;
                        
                    }
                    
                    std::vector<Subdiv3::EdgeRing*> const collectRingsFnext(Subdiv3::FacetEdge* aFedge){
                        std::vector<Subdiv3::EdgeRing*> result;
                        RingMembers ringMembers = getFnextRingMembersOf(*aFedge);
                        
                        for (auto current: ringMembers){
                            result.push_back(current->getDirectedEdgeRing()->getEdgeRing());
                        }
                        
                        std::sort(result.begin(), result.end());
                        auto unqEnd= std::unique(result.begin(), result.end());
                        result.erase(unqEnd, result.end());
                        
                        return result;
                        
                    
                    }
                  
                
                }
                
                Fan const DelaunayTriangulation3D::makeFan
                    (Mathbox::Geometry::Point3D const & aTopPoint
                    ,Mathbox::Geometry::Point3D const & aBotPoint
                    ,std::vector<Mathbox::Geometry::Point3D> const& aFanPoints){
                    
                    MUST_BE(aFanPoints.size() >1);
                    
                    std::vector<Triangle> tris;
                    tris.reserve(aFanPoints.size());
                    
                    for (auto const& point : aFanPoints){
                    
                        tris.push_back(makeTriangle
                                (vertexDataFrom(aTopPoint)
                                ,vertexDataFrom(aBotPoint)
                                ,vertexDataFrom(point)
                                ));
                    }
                    
                    
                    for (Index i = 0 ; i<aFanPoints.size()-1; i++){
                        Triangle const& tri0 = tris[i];
                        Triangle const& tri1 = tris[i+1];
                        FacetEdge *e0 = tri0.boundaryWith(aBotPoint, aTopPoint);
                        FacetEdge *e1 = tri1.boundaryWith(aBotPoint, aTopPoint);
                        
                        mpManifold->spliceFacets(*e0, *e1);
                    }
                    
                    
                    FacetEdge* commonCorner = tris[0].boundaryWith(aBotPoint, aTopPoint);
                    //collect domains
                    auto orgVerts = collectOrgsOf(commonCorner);
                    auto destVerts = collectOrgsOf(commonCorner->getClock());
                    //rearrange verts:
                    VertexPtr newOrg = unifyVertices(orgVerts);
                    VertexPtr newDest = unifyVertices(destVerts);
                    
                    //rearrange edge rings                      
                    auto edgeRings = collectRingsFnext(commonCorner);

                    
                    EdgeRingPtr newRing = unifyEdgeRings(edgeRings);
                 
                    mpManifold->linkEdgeRingAndFacetEdges(*newRing, *commonCorner);
      
                    mpManifold->linkVertexFacetEdge(*newOrg, *commonCorner);
                    mpManifold->linkVertexFacetEdge(*newDest, *commonCorner->getClock());
                
                    //rearrange domains:
                    auto domains = collectOrgsOf(tris[0].mpDualEdgeRing->getRingMember());
                   
                    VertexPtr newDomain = unifyDomains(domains);
                    mpManifold->linkVertexFacetEdge(*newDomain, *tris[0].mpDualEdgeRing->getRingMember());
                    return fanFrom(&newRing->getItem(0));
                }
                
                
                Crater DelaunayTriangulation3D::makeCrater(Mathbox::Geometry::Point3D const & aMidPoint, CraterPoints const& aCraterPoints ){
                    MUST_BE(aCraterPoints.size()>2);
                    CraterPoints bndPointsCpy(aCraterPoints);
                    bndPointsCpy.push_back(aCraterPoints.front());
                    std::vector<Triangle> triangles;
                    
                    for (Index i = 0; i < bndPointsCpy.size()-1; i++){
                        Point3D const& p0 = aMidPoint;
                        Point3D const& p1 = bndPointsCpy[i];
                        Point3D const& p2 = bndPointsCpy[i+1];
                        Triangle const trig = makeTriangle(
                            vertexDataFrom(p0),
                            vertexDataFrom(p2),
                            vertexDataFrom(p1)
                            );
                        
                        triangles.push_back(trig);
                    }
                    
                    triangles.push_back(triangles.front());
                    
                    for (Index i = 0; i<bndPointsCpy.size()-1; i++){
                        //auto points0 = triangles[i].getBoundaryPoints();
                        //auto points1 = triangles[i+1].getBoundaryPoints();
                        auto const &p0 = aMidPoint;
                        auto const &p1 = bndPointsCpy[i+1];
                        FacetEdge* b0 = triangles[i].boundaryWith(p0, p1);
                        FacetEdge* b1 = triangles[i+1].boundaryWith(p0, p1);
                        SHOULD_BE(b0!=nullptr);
                        SHOULD_BE(b1!=nullptr);
                        mpManifold->spliceFacets(*b0, *b1);
                        
                        //EdgeRingPtr newRing = unifyEdgeRings(rings);
                        //mpManifold->linkEdgeRingAndFacetEdges(*newRing, *bndToCenter);
                    }
                    
                    //rearrange inner vertex:
                    FacetEdge* centerToBnd = triangles[0].boundaryWith(aMidPoint, bndPointsCpy[0]);
                    SHOULD_BE(centerToBnd != nullptr);
                    auto orgsOfCenter = collectOrgsOf(centerToBnd);
                    VertexPtr newInnerVertex = unifyVertices(orgsOfCenter);
                    mpManifold->linkVertexFacetEdge(*newInnerVertex, *centerToBnd);
                    
                    
                    for (Index i = 0; i<bndPointsCpy.size()-1; i++){
                        
                        FacetEdge *bndToCenter = triangles[i].boundaryWith(bndPointsCpy[i], aMidPoint);
                        SHOULD_BE(bndToCenter!=nullptr);
                        //track bndVertex for rearrange
                        auto orgsOfBnd = collectOrgsOf(bndToCenter);
                        //track edge ring for rearrange
                        auto rings = collectRingsFnext(bndToCenter);
                        
                        //rearrange edge rings:
                        EdgeRingPtr newRing = unifyEdgeRings(rings);
                        mpManifold->linkEdgeRingAndFacetEdges(*newRing, *bndToCenter);
                        
                        //rearrage bnd vertex:
                        VertexPtr newVertex = unifyVertices(orgsOfBnd);
                        mpManifold->linkVertexFacetEdge(*newVertex, *bndToCenter);
                    }
                    
                    

                    
                    //rearrange domains:
                    FacetEdge * dual = centerToBnd->getDual();
                    auto oldDomains = collectOrgsOf(dual);
                    VertexPtr newDomain = unifyDomains(oldDomains);
                    mpManifold->linkVertexFacetEdge(*newDomain, *dual);
                    
                    return craterOf(newInnerVertex);
                }
                
        TetInteriour const DelaunayTriangulation3D::makeTetInterior( TetIntPoints const & aTetIntPoints)
	{
            // see https://github.com/chrweb/CrystalMesh/wiki/Cell-complexes-in-Delaunay3#tetrahedron-interior
            // for a sketch..
            Point3D const& topPoint = aTetIntPoints[0];
            Point3D const& botPoint = aTetIntPoints[4];
            FanPoints const fanPoints = FanPoints(aTetIntPoints.begin()+1, aTetIntPoints.begin()+3);
             
            Fan fan = makeFan(topPoint, botPoint, fanPoints);
             
            Point3D const & centerPoint = aTetIntPoints[4];
            CraterPoints const craterPoints = CraterPoints(aTetIntPoints.begin()+1, aTetIntPoints.begin()+3);
             
            Crater crater = makeCrater(centerPoint, craterPoints);
            
            RingMembers onextRing = crater.getOnextRingOfCenter();
            
            for (FacetEdge * current : onextRing){
                Point3D const& oPoint = originPointOf(current);
                Point3D const& dPoint = destinationPointOf(current);
                FacetEdge * adapter = fan.getAdapterOf(oPoint, dPoint);
                SHOULD_BE(notNullptr(adapter));
                mpManifold->spliceFacets(*current, *adapter);
                auto oldRings = collectRingsFnext(current);
                
                //rearrange edge rings
                EdgeRing* newRing = unifyEdgeRings(oldRings);
                mpManifold->linkEdgeRingAndFacetEdges(*newRing, *current);

                //rearrange destination vertex:
                auto oldVerts = collectOrgsOf(current->getClock());
                VertexPtr newVertex = unifyVertices(oldVerts);
                mpManifold->linkVertexFacetEdge(*newVertex, *current->getClock());
            }
            
            //rearrange in center/ in tet vertex:
            FacetEdge * centerToTop = fan.centerToTop()->getRingMember();
            
            auto oldVerts = collectOrgsOf(centerToTop);
            VertexPtr newVertex = unifyVertices(oldVerts);
            mpManifold->linkVertexFacetEdge(*newVertex, *centerToTop);
            
            //rearrange domains:
            Domain fanDomain = fan.getDomain();
            Domain craterDomain = crater.getDomain();
            
            auto oldDomains = collectOrgsOf(fanDomain.mpDual->getFacetEdge());
            VertexPtr newDomain = unifyDomains(oldDomains);
            mpManifold->linkVertexFacetEdge(*newDomain, *fanDomain.mpDual->getFacetEdge());
            
            
            
        }
                
               
                Subdiv3::VertexPtr DelaunayTriangulation3D::unifyVertices(VertexUnifyList& aList){
                    VertexPtr vp = aList.front();
                    
                    AdjacentFacetEdges adjFedges = getAdjacentFacetEdges(*vp);
                    VertexData  data = vertexDataFrom(vertexDataOf(vp));
                    
                    for (auto current : aList){
                        auto toData  = vertexDataPtrOf(current);
                        mpManifold->deletePrimalVertex(*current);                       
                        deleteVertexData(toData);
                    }
                    
                    for (FacetEdge* current: adjFedges){
                        current->mpOrg = nullptr;
                    }
                    
                    Subdiv3::VertexPtr result = makeVertexWith(data);            
                    return result;
                }
                
                Subdiv3::VertexPtr  DelaunayTriangulation3D::unifyDomains(VertexUnifyList& aList){
                    VertexPtr vp = aList.front();
                    AdjacentFacetEdges adjFedges = getAdjacentFacetEdges(*vp);

                    for (auto current: aList){
                        mpManifold->deleteDualVertex(*current);
                    }
                    
                    for (FacetEdge* current: adjFedges){
                        current->mpOrg = nullptr;
                    }
                   
                    
                    Subdiv3::VertexPtr result = mpManifold->makeDualVertex();
                    return result;
               
                }
         
                
                Subdiv3::EdgeRingPtr DelaunayTriangulation3D::unifyEdgeRings(EdgeRingUnifyList& aList){
                    FacetEdge* ringMember = aList.front()->getItem(0).getRingMember();
                    RingMembers ringMembers = getFnextRingMembersOf(*ringMember);
                 
                    for (EdgeRing * ring : aList){
                        mpManifold->deletePrimalEdgeRing(*ring);
                    }
                    
                    for (FacetEdge * current: ringMembers){
                        current->mpDirectedEdgeRing = nullptr;
                        current->getClock()->mpDirectedEdgeRing = nullptr;
                    }
                    
                    EdgeRingPtr result = mpManifold->makePrimalEdgeRing();
                    return result;
                }
                
                size_t DelaunayTriangulation3D::getDomainCount() const{
                    return mpManifold->dualVertexSize();
                }
                
                size_t DelaunayTriangulation3D::getFaceCount() const{
                    return mpManifold->dualEdgeRingSize();
                }
                
                size_t DelaunayTriangulation3D::getCornerCount() const{
                    return mpManifold->primalEdgeRingSize();
                }
                
                size_t DelaunayTriangulation3D::getVertexCount() const{
                    return mpManifold->primalVertexSize();
                }
                //TetInteriourFan const makeFan3(TopBottomPoints const & aTbPoints, FanPoints const& aFanPoints);
 
/*                
                TetInteriourFan const DelaunayTriangulation3D::makeFan3(TopBottomPoints const & aTbPoints, FanPoints const& aFanPoints){
                    
                    TetInteriourFan result;
                    result.mTriangles = {makeTriangle(), makeTriangle(), makeTriangle()};
                    auto & tris = result.mTriangles;
                    
                    for (Index i = 0 ; i<3; i++){
                        auto vertsArray = tris[i].getBoundaryVertices();
                        setVertexPointTo(aTbPoints[0], vertsArray[0]);
                        setVertexPointTo(aTbPoints[1], vertsArray[1]);
                        setVertexPointTo(aFanPoints[i], vertsArray[2]);
                    }
                    
                    Subdiv3::FacetEdge* edges[3] = {
                        tris[0].boundaryWith(aTbPoints[0], aTbPoints[1]),
                        tris[1].boundaryWith(aTbPoints[0], aTbPoints[1]),
                        tris[2].boundaryWith(aTbPoints[0], aTbPoints[1])
                    };                   
                 
                    mpManifold->spliceFacets(*edges[0], *edges[1]);
                    unifyEdgeRings(edges[0]->getDirectedEdgeRing()->getEdgeRing(), edges[1]->getDirectedEdgeRing()->getEdgeRing());
                    unifyVertices(edges[0]->getOrg(), edges[1]->getOrg());
                    unifyVertices(edges[0]->getDest(), edges[1]->getDest());
                    
                    mpManifold->spliceFacets(*edges[1], *edges[2]);
                    unifyEdgeRings(edges[1]->getDirectedEdgeRing()->getEdgeRing(), edges[2]->getDirectedEdgeRing()->getEdgeRing());
                    unifyVertices(edges[1]->getOrg(), edges[2]->getOrg());
                    unifyVertices(edges[1]->getDest(), edges[2]->getDest());
                    
                    return result;
                }
 */               
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
        
/*
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
 */             
    
                /*
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
                } */
/*                
                Flip1To4 const DelaunayTriangulation3D::flip1to4(Tet& aTetToFlip, PointInsertion const aIns){
                    using namespace Subdiv3;
                    //construct to inner complex
                    auto const tetIntPoints = getTetIntPointsOf(aTetToFlip, aIns.mPoint);
                    TetInteriour innerComplex  = makeTetInterior(tetIntPoints);
                    
                    //get adapters
                    Tet::Corners  const corners = aTetToFlip.getCorners();
                    std::array<FacetEdge*, 6> adapters;
                    
                    //get triangles outer boundary faces
                    Tet::Triangles const tetsTriangles = getTriangleArrayOf(aTetToFlip);
                    
                    
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
                       
                        auto dr0 = getAdjacentRingsOf(*tetsTriangles[0].mpDualEdgeRing);
                       
                        
                        FacetEdge* fromTet= corners[i].mRef;
                        FacetEdge* fromInnerComplex = adapters[i];
                        
                        mpManifold->spliceFacets(*fromTet, *fromInnerComplex);
                        
                        auto dr1 = getAdjacentRingsOf(*tetsTriangles[1].mpDualEdgeRing);
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
*/
/*                
                
                Flip2To3 DelaunayTriangulation3D::flip2to3(Triangle& aTriangleToFlip){
                    Tet tet0 = aTriangleToFlip.upperTet();
                    Tet tet1 = aTriangleToFlip.lowerTet();
                    //getting top/bottom points
                    auto symDiff = symmetricDifferenceInVerticesOf(tet0, tet1);
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
                    
                    //get a container with tris, representig the room partition
                    //given by the two tets
                    SymmetricDiffenrenceTriangles hull  = symmetricDifferenceInTriangles(tet0, tet1);
                    
                    //destoy the tets:
                    destroyTet(tet0);
                    destroyTet(tet1);
                    
                    //destroy separating bound
                    //separateTriangle(aTriangleToFlip);
                    //destroyTriangle(aTriangleToFlip);
                    
                    //creade a valid domain unifiying the two tets
                    //auto domainVertex = makeBody();         
                    //mpManifold->linkVertexDirectedEdgeRings(*domainVertex, *directedEdgeRingFromTriangle(hull.front()));
                    Domain domain = destroyTriangle(aTriangleToFlip);
                    
                    
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
                        unifyVertices(domainVerts[i], innerVerts[i]);
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
                    result.result = Flip2To3::Result::success;
                    
                    SHOULD_BE(hull.size() == 6);
                    //triangles from hull
                    auto position = std::copy(hull.begin(), hull.end(), result.tris.begin());
                    //triangles from fan
                    auto fanTris = fan.getTriangles();
                    SHOULD_BE(fanTris.size() == 3);
                    std::copy(fanTris.begin(), fanTris.end(), position);
                    
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
 * */
               /*    
                void DelaunayTriangulation3D::unifyEdgeRings(Subdiv3::EdgeRing* apRing0 ,Subdiv3::EdgeRing* apRing1){
////Validation:                    
//#ifdef DEBUG
//                    auto fnextRing = getFnextRingMembersOf()
//#endif
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
                }*/
 /*               
                void DelaunayTriangulation3D::destroyDomain(Domain & aDomain){
                    mpManifold->dislinkVertexDirectedEdgeRings(*aDomain.mpDual);
                    mpManifold->deleteDualVertex(*aDomain.mpDual);
                    return;
                }
       */            
                
                
                Domain const  DelaunayTriangulation3D::makeDomainUnder(Triangle& aTri){
                    Domain result;
                    result.mpDual = mpManifold->makeDualVertex();
                    mpManifold->linkVertexFacetEdge(*result.mpDual, *aTri.mpDualEdgeRing->getRingMember());
                    return result;
                }
                
                void DelaunayTriangulation3D::addCorners(Exporter& aExporter) const{
                    Subdiv3::EdgeRingBuffer buffer;
                    mpManifold->exportPrimalEdgeRings(buffer);
                    
                    for (EdgeRing* pRing: buffer){
                        DirectedEdgeRing * pDring = &pRing->getItem(0);
                        aExporter.addCorner(originIndexOf(pDring), destinationIndexOf(pDring));
                    }
                }
                
                void DelaunayTriangulation3D::addTriangles(Exporter & aExporter) const{
            
                    Subdiv3::EdgeRingBuffer buffer;
                    mpManifold->exportDualEdgeRings(buffer);
                    for (EdgeRing* pRing: buffer){
                        Triangle tri0 = triangleOf(&pRing->getItem(0));
                        auto verts = tri0.getBoundaryVertices();

                        //one dir
                        aExporter.addTriangle(idOf(verts[0]),
                                              idOf(verts[1]),
                                              idOf(verts[2]));


                        //other dir
//                        aExporter.addTriangle(idOf(verts[2]),
//                                              idOf(verts[1]),
//                                              idOf(verts[0]));
//                
                }
         
            }
                
        void DelaunayTriangulation3D::addVertices(Exporter & aExporter) const{
            Subdiv3::VertexBuffer buffer;
            mpManifold->exportPrimalVerts(buffer);
            for (auto pVertex: buffer)
            {
                auto const point = pointOf(pVertex);
                Index id = aExporter.addVertex(point);
                setVertexIdTo(id, pVertex);
                
            }

        }
                
  /*              
                //ToDo: continue here
                Domain const DelaunayTriangulation3D::destroyTriangle(Triangle& aTri){
                    using namespace Subdiv3;
                    //handle dual
                    DirectedEdgeRing* dualRing = aTri.mpDualEdgeRing;
                    DirectedEdgeRing* otherRing = aTri.mpDualEdgeRing->getRingMember()->getOnext()->getDirectedEdgeRing();
                    Vertex* upperDomainVertex = dualRing->getOrg();
                    Vertex* lowerDomainVertex = dualRing->getSym()->getOrg();
                    
                    mpManifold->dislinkVertexDirectedEdgeRings(*upperDomainVertex);
                    mpManifold->dislinkVertexDirectedEdgeRings(*lowerDomainVertex);
                    
                          
                    
                    //handle primal
                    auto boundary = aTri.getBoundaryArray();
                    for (FacetEdge* edge: boundary){
                        MUST_BE(edge->getDirectedEdgeRing()->computeEdgeRingSize()>1);
                        FacetEdge* inv = edge->getInvFnext();
                        DirectedEdgeRing* dRing = edge->getDirectedEdgeRing();
                        
                        //seperate
                        mpManifold->spliceFacets(*inv, *edge);
                        //garant validity:
                        dRing->mpRingMember = inv;
                        edge->mpDirectedEdgeRing = nullptr;   
                    }
                    
                    //delete primal:
                    for (FacetEdge* edge: boundary){
                        mpManifold->deleteQuaterNodeOf(*edge);
                    }
                    
                    //delete dual
                    mpManifold->deleteDualEdgeRing(*dualRing->getEdgeRing());
                    mpManifold->deleteDualVertex(*lowerDomainVertex);
                    
                    //recylce upper for domain
                    mpManifold->linkVertexDirectedEdgeRings(*upperDomainVertex, *otherRing);
                    
                    return domainOf(upperDomainVertex);
                }
                
 */            
                
                /*
                void DelaunayTriangulation3D::separateTriangle(Triangle & aTri){
                    using namespace Subdiv3;
                    //handle dual
                    Fa
                    
                    //handle primal
                    auto boundary = aTri.getBoundaryArray();
                    for (FacetEdge* edge: boundary){
                        MUST_BE(edge->getDirectedEdgeRing()->computeEdgeRingSize()>1);
                        FacetEdge* inv = edge->getInvFnext();
                        DirectedEdgeRing* dRing = edge->getDirectedEdgeRing();
                        
                        //seperate
                        mpManifold->spliceFacets(inv, *edge);
                        //garant validity:
                        dRing->mpRingMember = inv;
                        edge->mpDirectedEdgeRing = nullptr;   
                    }
                    
                }*/
                /*/
                void DelaunayTriangulation3D::destroyTriangle(Triangle& aTri){
                    MUST_BE(getAdjacentRingsOf(aTri.mpDualEdgeRing) ==1);
                    MUST_BE(aTri.mpDualEdgeRing->getOrg() == nullptr);
                    auto bound = aTri.getBoundaryArray();
                    for (auto edge : bound){
                        MUST_BE(edge->getDirectedEdgeRing() == nullptr);
                        MUST_BE(edge->getFnext() == edge);
                    }
                    
                    for (auto edge: bound){
                        mpManifold->deleteQuaterNodeOf(*edge);
                    }
                    
                    mpManifold->deleteDualEdgeRing(aTri.mpDualEdgeRing);
                    
                    return;
                }
                 
                 */

	}
        
        
        

}




