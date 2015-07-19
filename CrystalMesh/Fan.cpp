/* 
 * File:   Fan.cpp
 * Author: christoph
 * 
 * Created on 17. Mai 2015, 22:01
 */

#include <stddef.h>

#include "Triangle.h"
#include "AdjacentDirectedEdgeRings.h"
#include "DelaunayVertex.h"
#include "Corner.h"
#include "Fan.h"


namespace CrystalMesh{

    namespace Delaunay3{
        using namespace Subdiv3;
        
        Fan::Triangles Fan::getTriangles() const{
            Triangles result;
            auto collector = [&result](FacetEdge & aFedge){
                result.push_back(
                        triangleOf(aFedge.getDual()->getDirectedEdgeRing()));
            };
            
            forEachElementInFnextRing(*mpDring->getRingMember(), collector);
            return result;
        }            
        
        Mathbox::Geometry::Point3D const Fan::getTopPoint() const{
            return destinationPointOf(mpDring);
        }
            
        Mathbox::Geometry::Point3D const Fan::getBotPoint() const{
            return originPointOf(mpDring);
        }
        
        
    
        Fan const fanFrom(Subdiv3::DirectedEdgeRing * apDring){
            Fan result = {apDring};
            return result;
        }
        
        Subdiv3::DirectedEdgeRing* Fan::BottomToTop() const{
            return mpDring;
                   
        }
        
        
        Subdiv3::FacetEdge* Fan::getAdapterOf(Mathbox::Geometry::Point3D const &  aOrg, Mathbox::Geometry::Point3D const & aDest) const{
            auto triangles = getTriangles();
            
            for (Triangle const& triangle : triangles){
                FacetEdge * bnd = triangle.boundaryWith(aOrg, aDest);
                
                if (bnd != nullptr){
                    return bnd;
                }
            }
            
            return nullptr;
        
        }
        
        
        namespace{
            FacetEdge* nextEdgeOf(FacetEdge* aFedge){
                return aFedge->getEnext();
            }
        
        }
        
        Fan::FanBoundary const Fan::getTopToSideBoundary() const{
      
            auto fnextRing = getFnextRingMembersOf(*mpDring);
            FanBoundary result(fnextRing.size(), nullptr);
            
            std::transform(fnextRing.begin(), fnextRing.end(), result.begin(), nextEdgeOf);
            
            return result;
        }
            
        Fan::FanBoundary const Fan::getBottomToSideBoundary() const{
            auto fnextRing = getFnextRingMembersOf(*mpDring->getSym());
            FanBoundary result(fnextRing.size(), nullptr);
            
            std::transform(fnextRing.begin(), fnextRing.end(), result.begin(), nextEdgeOf);
            
            return result;
        }
        
        Domain const Fan::getDomain() const{
            auto domain = domainFrom( mpDring->getRingMember()->getDual()->getOrg());
            return domain;
        }
           
    
    }
}

