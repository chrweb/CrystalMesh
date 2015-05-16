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
#include "ComplexConstruction.h"
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
                
                void setVertexPointTo(Mathbox::Geometry::Point3D const & aPoint, Subdiv3::Vertex * pVertex){
                    VertexData * data = reinterpret_cast<VertexData*>(pVertex->mpData);
                    data->mPoint = aPoint;
                }


		namespace{
                    
                    Subdiv3::FacetEdge * toPointer(Subdiv3::FacetEdge const & aRef){
                        return const_cast<Subdiv3::FacetEdge*>(&aRef);
                    }
                    
                    
                   

		FacetEdgeThreeTuple const facetEdgeThreeTupleOf(Subdiv3::FacetEdge const & a0, Subdiv3::FacetEdge const & a1, Subdiv3::FacetEdge const & a2){
			FacetEdgeThreeTuple result = {toPointer(a0), toPointer(a1), toPointer(a2)};
			return result;
		}

		PointThreeTuple const pointTreeTupleOf(Mathbox::Geometry::Point3D const & a0, Mathbox::Geometry::Point3D const & a1, Mathbox::Geometry::Point3D const & a2){
			PointThreeTuple result = { a0, a1, a2};
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
                    return triangleOf(aTri.mpDualEdgeRing->getSym());
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
                    
                    return facetEdgeWithEndPoints(org, dest, mpOuterEdgeRing);
                }
                
                Subdiv3::FacetEdge* TetInteriour::getAdapterOf(Corner const & aCorner) const{
                    return getAdapterOf(
                            originPointOf(aCorner.mRef),
                            destinationPointOf(aCorner.mRef));
                }
                
                Subdiv3::FacetEdge* TetInteriourFan::getAdapterOf(Corner const & aCorner) const{
                    UNREACHABLE;
                }
                    
                Subdiv3::FacetEdge* TetInteriourFan::getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const{
                    UNREACHABLE;
                }
                    
                TetInteriourFan::Vertices const TetInteriourFan::getVertices() const{
                    return mVertices;
                }
                    
                TetInteriourFan::Triangles const TetInteriourFan::getTriangles() const {
                    return mTriangles;
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
                
                bool const Tet::operator == (Tet const & rhs) const{
                    return mpDualVertex == rhs.mpDualVertex;
                }
                
                bool const Tet::operator != (Tet const & rhs) const{
                    return !operator ==(rhs);
                }
                
                Triangle const Tet::getTriangleAt(Index aIndex) const{
                    SHOULD_BE(aIndex < 4);
                    return mTri[aIndex];
                }
                
                bool const Tet::isPartOf(Subdiv3::Vertex const *apVert) const{
                    auto const verts = getVertices();
                    auto result = std::find(verts.begin(), verts.end(), apVert);
                    return (result != verts.end());
                }
                
                Tet const Tet::adjancentTetAt(Index aIndex) const{
                    auto const tri = getTriangleAt(aIndex);
                    auto vertex =  tri.mpDualEdgeRing->getSym()->getOrg();
                    return tetFromDomain(*vertex);
                }
                
                Tet::Triangles const Tet::getTriangles() const{
                    return mTri;                    
                }
                
                Triangle const Tet::commonBoundaryWith(Tet const & aOther) const{
                    
                    if (aOther == (*this)){
                        return Triangle::invalid;
                    }
                        
                    
                    for (Triangle const & myTriangle :mTri ){
                        for (Triangle const & otherTriangle : aOther.mTri){
                            auto myRing = myTriangle.mpDualEdgeRing->getEdgeRing();
                            auto otherRing = otherTriangle.mpDualEdgeRing->getEdgeRing();
                            if (myRing == otherRing){
                                return myTriangle;
                            }
                        }
                    }
                    
                    return Triangle::invalid;
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
                   
                    /**
                     * Constructs cornes. Corners Fnext-member is adjancent to the given domain.
                     * @param apRing: The primal edge ring 
                     * @param apDomain the inner domain
                     * @return 
                     */
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
                
                
                IntersectingVertices intersectionInVerticesOf(const Tet& aTet0, const Tet& aTet1){
                    auto vertices0 = aTet0.getVertices();
                    auto vertices1 = aTet1.getVertices();
                    std::array<Subdiv3::Vertex*,4> intersection = {nullptr, nullptr, nullptr, nullptr};
                    std::sort(vertices0.begin(), vertices0.end());
                    std::sort(vertices1.begin(), vertices1.end());
                    auto setEnd = std::set_intersection(vertices0.begin(), vertices0.end(), vertices1.begin(), vertices1.end(), intersection.begin());
                    IntersectingVertices result(intersection.begin(), setEnd);
                    return result;                    
                }
                
                
                SymmetricDifferenceVertices symmetricDifferenceInVerticesOf(const Tet& aTet0, const Tet& aTet1){
                    auto vertices0 = aTet0.getVertices();
                    auto vertices1 = aTet1.getVertices();
                    std::array<Subdiv3::Vertex*,8> intersection = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
                    std::sort(vertices0.begin(), vertices0.end());
                    std::sort(vertices1.begin(), vertices1.end());
                    auto setEnd = std::set_symmetric_difference(vertices0.begin(), vertices0.end(), vertices1.begin(), vertices1.end(), intersection.begin());
                    IntersectingVertices result(intersection.begin(), setEnd);
                    return result;
                }
                
                SymmetricDiffenrenceTriangles symmetricDifferenceInTriangles(Tet const & aTet0, Tet const & aTet1){
                    std::array<Triangle,4> intersection = {Triangle::invalid, Triangle::invalid, Triangle::invalid, Triangle::invalid};
                    
                    auto sorter = [](Triangle const & t0, Triangle const & t1){
                        return t0.mpDualEdgeRing < t1.mpDualEdgeRing;
                    };
                    
                    auto tris0 = aTet0.getTriangles();
                    auto tris1 = aTet1.getTriangles();
                    Tet::Triangles ccw1; 
                    
                    std::transform(tris1.begin(), tris1.end(), ccw1.begin(), getCounterOrientedOf);
                    std::sort(tris0.begin(), tris0.end(), sorter);
                    std::sort(ccw1.begin(), ccw1.end(), sorter);
                    
                    auto setEnd = std::set_symmetric_difference(tris0.begin(), tris0.end(), ccw1.begin(), ccw1.end(), intersection.begin(), sorter);
                    SymmetricDiffenrenceTriangles result(intersection.begin(), setEnd);
                    return result;
                }

                Domain const domainOf(Subdiv3::Vertex*  apVertex){
                    Domain result = {apVertex};
                    return result;
                }
                
                bool const Domain::operator == (Domain const & rhs) const{
                    return rhs.mpDual == mpDual;
                }
                        
                bool const Domain::operator != (Domain const & rhs) const{
                    return !operator ==(rhs);
                }
                
               
                Domain::Corners const Domain::getCorners() const{
                    using namespace Subdiv3;
                    std::vector<EdgeRing*> edgeRings;
                    auto triangles = getTriangles();
                    
                    for (auto const & triangle : triangles){
                        auto bound = triangle.getBoundaryArray();
                        
                        for (auto const fe: bound){
                            edgeRings.push_back(fe->getDirectedEdgeRing()->getEdgeRing());
                        }
                        
                    }
                    
                    std::sort(edgeRings.begin(), edgeRings.end());
                    auto toUniqueEnd = std::unique(edgeRings.begin(), edgeRings.end());
                
                    Corners result;
                    
                    for (auto iterator = edgeRings.begin(); iterator != toUniqueEnd; iterator++){
                        result.push_back(cornerOf(*iterator, mpDual));
                    }
                    
                    return result;
                
                }               
                
                Domain::Vertices const Domain::getVertices() const{
                    auto triangles = getTriangles();
                    Vertices result;
                    
                    for (auto const& triangle : triangles){
                        auto triVerts = triangle.getBoundaryVertices();
                        result.insert(result.end(), triVerts.begin(), triVerts.end());
                    }
                    
                    std::sort(result.begin(), result.end());
                    auto uniqueEnd = std::unique(result.begin(), result.end());
                    return Vertices(result.begin(), uniqueEnd);
                    
                    
                }
                    
                Domain::Triangles const Domain::getTriangles() const{
                    auto adjDualEdgeRings = getAdjacentRingsOf(*mpDual);
                    
                    Triangles result(adjDualEdgeRings.size(),Triangle::invalid);
                    std::transform(adjDualEdgeRings.begin(), adjDualEdgeRings.end(), result.begin(), triangleOf);
                
                    return result;
                }

                

	}  // namespace Delaunay



}  // namespace CrystalMesh




