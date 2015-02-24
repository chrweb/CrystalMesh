/*
 * Primitives.cpp
 *
 *  Created on: 26.07.2014
 *      Author: christoph
 */

#include "DelaunayTriangulation3D.h"
#include "Vertex.h"
#include "FacetEdge.h"
#include "DirectedEdgeRing.h"
#include "EdgeRing.h"
#include "../Mathbox/Mathbox.h"
#include "Primitives.h"
#include <vector>
#include "../Toolbox/Checks.h"
#include "AdjacentDirectedEdgeRings.h"
#include <algorithm>
#include <array>

namespace CrystalMesh {

	namespace Delaunay3 {

		using namespace Mathbox::Geometry;

		typedef Subdiv3::FacetEdge FacetEdge;


		

		Point3D const pointFromSubdiv3Vertex(Subdiv3::Vertex const *pVertex){
			VertexData const & data = *reinterpret_cast<VertexData const *>(pVertex->mpData);
			return data.mPoint;
		}
		
                Point3D const originPointOf(Subdiv3::FacetEdge const * pFacetEdge){
                    return pointFromSubdiv3Vertex(pFacetEdge->getOrg());
                }
                
                Point3D const destinationPointOf(Subdiv3::FacetEdge const * pFacetEdge){
                    return pointFromSubdiv3Vertex(pFacetEdge->getDest());
                }
                
                Point3D const originPointOf(Subdiv3::DirectedEdgeRing const * pRing){
                    return originPointOf(pRing->getRingMember());
                }
                
                Point3D const destinationPointOf(Subdiv3::DirectedEdgeRing const * pRing){
                    return destinationPointOf(pRing->getRingMember());
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

		PointThreeTuple const pointTreeTupleOf(Mathbox::Geometry::Point3D const & a0, Mathbox::Geometry::Point3D const & a1, Mathbox::Geometry::Point3D const & a2){
			PointThreeTuple result = { a0, a1, a2};
			return result;
		}

		

		Triangle::Boundary const Triangle::getBoundaryArray() const{
			auto pBnd = mpDualEdgeRing->getRingMember()->getDual();

			Triangle::Boundary result;

			result[0] = pBnd;
			result[1] = result[0]->getEnext();
			result[2] = result[1]->getEnext();

			return result;
		}
                
                Triangle::BoundaryPoints const Triangle::getBoundaryPoints() const{
                    auto const bndEdges = getBoundaryArray();
                    BoundaryPoints result;
                    for (Index i = 0; i<3; i++){
                        result[i] = pointFromSubdiv3Vertex(bndEdges[i]->getOrg());
                    }
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


		TetInteriour::Vertices const TetInteriour::getVertices() const{
			Vertices result; 
			result.mInTet = mpVertex[0];
                        
			for (Index i = 0; i < 4; i++ ){
				result.mAtCorners[i] = mpVertex[i+1];
			}

			return result;
		}
                
                Triangle const TetInteriour::getTriangleAt(Index aIndex) const{
                    MUST_BE(aIndex < 6);
                    Triangle result;
                    result.mpDualEdgeRing = mpOuterEdgeRing[aIndex]->getItem(0).getRingMember()->getDual()->getDirectedEdgeRing();
                    return result;
                }
                
                Subdiv3::FacetEdge* TetInteriour::getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const{
                    using namespace Subdiv3;
                    
                    auto finder0 = [&dest, &org](EdgeRing const * ring)->bool{
                        
                        DirectedEdgeRing const * dring = &ring->getItem(0);            
                        Point3D ringOrg = originPointOf(dring);
                        Point3D ringDest= destinationPointOf(dring);
                        
                        if ( exactEqual(ringOrg, org) && exactEqual(ringDest, dest))
                            return true; 
                        
                        return false;
                    };
                    
                    auto finder1 = [&dest, &org](EdgeRing const * ring)->bool{
                        
                        DirectedEdgeRing const * dring = &ring->getItem(1);            
                        Point3D ringOrg = originPointOf(dring);
                        Point3D ringDest= destinationPointOf(dring);
                        
                        if ( exactEqual(ringOrg, org) && exactEqual(ringDest, dest))
                            return true;                       
                        
                        return false;
                    };
                    
                    
                    auto const result0 = std::find_if(mpOuterEdgeRing.begin(), mpOuterEdgeRing.end(), finder0);
                    
                    if (result0!= mpOuterEdgeRing.end()){
                        return (*result0)->getItem(0).getRingMember();
                    }
                    
                    auto const result1 = std::find_if(mpOuterEdgeRing.begin(), mpOuterEdgeRing.end(), finder1);
                    
                    if (result1 != mpOuterEdgeRing.end())
                        return (*result1)->getItem(1).getRingMember();
                    
                    return nullptr;
                }
                
                Subdiv3::FacetEdge* TetInteriour::getAdapterOf(Corner const & aCorner) const{
                    return getAdapterOf(
                            originPointOf(aCorner.mRef),
                            destinationPointOf(aCorner.mRef));
                }
                
                
		namespace{

                    typedef std::array<Subdiv3::Vertex*,3> VertexThreeTuple;

                    VertexThreeTuple collectVerts(Triangle const & aTri){
                        auto const bnd = aTri.getBoundaryArray();
                        VertexThreeTuple result;

                        auto getOrg = [](Subdiv3::FacetEdge * e){
                            return e->getOrg();
                        };

                        std::transform(bnd.begin(), bnd.end(), result.begin(), getOrg);

                        return result;
                    }

		}
                
                Triangle const Tet::getTriangleAt(Index aIndex) const{
                    SHOULD_BE(aIndex < 4);
                    return mTri[aIndex];
                }
                
                Tet::Triangles const Tet::getTriangles() const{
                    return mTri;                    
                }
		
                Tet::Vertices const Tet::getVertices() const{
                    Tet::Vertices result;
                    // two triangles hold all vertices:
                    auto tuple0 = collectVerts(mTri[0]);
                    auto tuple1= collectVerts(mTri[1]);

                    std::vector<Subdiv3::Vertex*> all(tuple0.begin(), tuple0.end());
                    all.insert(all.end(), tuple1.begin(), tuple1.end());

                    std::sort(all.begin(), all.end());
                    auto un = std::unique(all.begin(), all.end());

                    std::copy(all.begin(), un, result.begin());

                    return result;
		}
                
                
                namespace{
                   
                    Corner const cornerOf(Subdiv3::EdgeRing * apRing, Subdiv3::Vertex* apDomain){
                        using namespace Subdiv3;
                        
                        RingMembers const ringmembers0 = getFnextRingMembersOf(apRing->getItem(0));
                        Corner result = {nullptr, nullptr};
                        
                        auto finder = [apDomain](FacetEdge* apFedge)->bool{
                            auto const currentDomain = apFedge->getDual()->getOrg();
                            return (currentDomain == apDomain);
                        };
                        
                        auto toResult0 = std::find_if(ringmembers0.begin(), ringmembers0.end(), finder);
                        
                        if (toResult0 != ringmembers0.end()){
                            result.mFnext = *toResult0;
                            result.mRef = result.mFnext->getInvFnext();
                            return result;
                        }
                        
                        auto const ringmembers1 = getFnextRingMembersOf(apRing->getItem(1));
                        
                        auto toResult1 = std::find_if(ringmembers1.begin(), ringmembers1.end(), finder);
                        
                        if (toResult1 != ringmembers1.end()){
                            result.mFnext = *toResult1;
                            result.mRef = result.mFnext->getInvFnext();
                            return result;
                        }
                        
                        UNREACHABLE;                    
                    }
                }
                
                
                Tet::Corners const Tet::getCorners() const{
                    using namespace Subdiv3;
                    std::vector<EdgeRing*> edgeRings;
                    
                    for (auto const & triangle : mTri){
                        auto bound = triangle.getBoundaryArray();
                        
                        for (auto const fe: bound){
                            edgeRings.push_back(fe->getDirectedEdgeRing()->getEdgeRing());
                        }
                        
                    }
                    
                    std::sort(edgeRings.begin(), edgeRings.end());
                    auto toUniqueEnd = std::unique(edgeRings.begin(), edgeRings.end());
                
                    SHOULD_BE((toUniqueEnd-edgeRings.begin()) == 6 );
                    std::array<EdgeRing*, 6> uniqueEdgeRings;
                    std::copy(edgeRings.begin(), toUniqueEnd, uniqueEdgeRings.begin());
                    
                    
                    Corners result;
                    for (Index i = 0; i<6; i++){
                        Corner current = cornerOf(uniqueEdgeRings[i], mpDualVertex);
                        result[i] = current;
                    }
                    
                    return result;
                }
                
                

	}  // namespace Delaunay



}  // namespace CrystalMesh




