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
		

//		Point3D const Vertex::getPoint() const{
//			return pointFromSub3Vertex(mpPrimalVertex);
//		}
//
//		void Vertex::setPoint(Point3D const & aPoint){
//			VertexData & data = *reinterpret_cast<VertexData *>(mpPrimalVertex->mpData);
//			data.mPoint = aPoint;
//			return;
//		}

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

		FacetEdgeThreeTuple const Triangle::getBoundary() const{
			auto pBnd = mpDualEdgeRing->getRingMember()->getDual();

			FacetEdgeThreeTuple result = {pBnd, pBnd->getEnext(), pBnd->getEnext()->getEnext()};
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
                
//		PointThreeTuple const Triangle::getPoints() const{
//
//			auto const bnd = getBoundary();
//			PointThreeTuple result;
//			result.p0 = pointFromSub3Vertex(bnd.f0->getOrg());
//			result.p1 = pointFromSub3Vertex(bnd.f1->getOrg());
//			result.p2 = pointFromSub3Vertex(bnd.f2->getOrg());
//
//			return result;
//		}

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

			Mathbox::Geometry::Point3D const originPointOf(Subdiv3::DirectedEdgeRing const * apRing){
				return pointFromSubdiv3Vertex(apRing->getOrg());
			}

		}  // namespace

		TetInteriour::TetAdapter const TetInteriour::getTetAdapterOf(
				Mathbox::Geometry::Point3D const &a0,
				Mathbox::Geometry::Point3D const &a1,
				Mathbox::Geometry::Point3D const &a2) const{

			Mathbox::Geometry::Point3D const point[3] = {a0, a1, a2};
			Subdiv3::DirectedEdgeRing  * dring[12];

			// Extract all directed edge ring
			for (Index i = 0; i<6; i++){

				dring[i] = &mpOuterEdgeRing[i]->getItem(0);
				dring[i+6] = &mpOuterEdgeRing[i]->getItem(1);
			}


			std::vector<FacetEdge*> resultVec;

			// find those with specified point
			for (Mathbox::Geometry::Point3D const & currentPoint: point){

                            auto condition = [&currentPoint](Subdiv3::DirectedEdgeRing  * apRing) -> bool{
                                    using  namespace Mathbox::Geometry;
                                    return exactEqual(currentPoint, originPointOf(apRing));
                            };

                            auto  beg = std::begin(dring);
                            auto  end = std::end(dring);

                            auto  found = std::find_if(beg, end, condition);

                            // must be found
                            MUST_BE(found != end);

                            resultVec.push_back((*found)->getRingMember());
			}
                        
                        MUST_BE(resultVec.size() == 3);
                        
                        TetInteriour::TetAdapter result;
                        
                        std::copy(resultVec.begin(), resultVec.end(), result.begin());
                        
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
                    typedef std::vector<Subdiv3::FacetEdge*>  FacetEdgeVector;
                    
                    //get dual representation
                    FacetEdgeVector const toDualSpace(Subdiv3::AdjacentFacetEdges const & adj){
                        FacetEdgeVector result = adj;
                        
                        auto toDual = [](Subdiv3::FacetEdge * aFE){
                            return  aFE->getDual();
                        };
                        
                        std::transform(adj.begin(), adj.end(), result.begin(), toDual);
                        return result;
                    }
                    
                    
                    FacetEdgeVector const toClocked(FacetEdgeVector const & vec){
                        FacetEdgeVector result = vec;
                        auto toClocked = [](Subdiv3::FacetEdge* aFE){
                            return aFE->getClock();
                        };
                        std::transform(vec.begin(), vec.end(), result.begin(),toClocked);
                        return result;
                    }
                    //adds clocked version for each item
                    FacetEdgeVector const unfold(FacetEdgeVector const & vec){
                        FacetEdgeVector result = vec;
                        FacetEdgeVector clocked = toClocked(vec);
                        result.insert(result.end(), clocked.begin(), clocked.end());
                        return result;
                    }
                    
                    
                    Corner const swapIfNes(Corner const& aCorner){
                        if (aCorner.mRef->getFnext() != aCorner.mFnext){
                            Corner result = {aCorner.mFnext, aCorner.mRef};
                            
                            MUST_BE( result.mRef->getFnext() == result.mFnext);
                            return result;
                        }
                        
                        return aCorner;
                    }
                }
                
                //ToDo: Test This function
                Tet::Corners const Tet::getCorners() const{
                    
                    auto const verts = getVertices();
                    
                    typedef std::array<Subdiv3::Vertex*, 2> Segment;
                    typedef std::array<Segment, 6> TetSegments;
                    
                    //list of segments, represented as vertex pairs
                    Segment segs[] = {    
                                        {verts[0], verts[1]}, 
                                        {verts[0], verts[2]}, 
                                        {verts[1], verts[2]}, 
                                        {verts[3], verts[0]},
                                        {verts[3], verts[1]}, 
                                        {verts[3], verts[2]},
                                        };
                    
                    //adjanced to dual
                    Subdiv3::AdjacentFacetEdges const adj = getAdjacentFacetEdges(*mpDualVertex);
                    
                    //get duals
                    FacetEdgeVector const toDual = toDualSpace(adj);
                    
                    //unfold: get additionally their clocked versions:
                    auto const unfolded = unfold(toDual);
                    
                    Corners result;
                    
                    for (Index i = 0; i<6; i++){
                        Segment currentSegment = segs[i];
                        
                        Corner currentCorner = {nullptr, nullptr};
                        
                        auto cornerBuilder = [&currentCorner, currentSegment](Subdiv3::FacetEdge* aFE){
                            //Vertex pattern fits?
                            if (currentSegment[0] == aFE->getOrg() && currentSegment[1] == aFE->getDest()){
                                //set members of currentcorner
                                if (currentCorner.mRef == nullptr){
                                    currentCorner.mRef = aFE;
                                    return;
                                }
                                
                                if (currentCorner.mFnext == nullptr){
                                    currentCorner.mFnext = aFE;
                                    return;
                                }
                                
                                UNREACHABLE;
                            }
                            
                            return;
                        };
                        //look for the segments in unfolded: each one schould fit to 2 FE references:
                        std::for_each(unfolded.begin(), unfolded.end(), cornerBuilder);
                        
                        //currentcorner may be swapped get its two members in corrcet fnext direction
                        result[i] = swapIfNes(currentCorner);
                       
                    }
                    
                    return result;
                }

	}  // namespace Delaunay



}  // namespace CrystalMesh




