/* 
 * File:   Fan.cpp
 * Author: christoph
 * 
 * Created on 17. Mai 2015, 22:01
 */

#include <stddef.h>
#include "Fan.h"
#include "Triangle.h"
#include "DelaunayVertex.h"


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
    
    }
}

