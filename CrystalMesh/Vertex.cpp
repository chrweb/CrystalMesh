/*
 * Vertex.cpp
 *
 *  Created on: 16.07.2014
 *      Author: christoph
 */
#include "Vertex.h"
#include "FacetEdge.h"
#include "../Toolbox/Checks.h"
#include "DirectedEdgeRing.h"

namespace CrystalMesh {

    namespace Subdiv3 {

        using namespace Toolbox;

        bool const Vertex::isDual() const{
            SHOULD_BE(notNullptr(mpOut));
            return mpOut->isDual();
        }

        bool const Vertex::isPrimal() const{
                return !isDual();
        }

        DirectedEdgeRing * Vertex::getDirectedEdgeRing(){
            SHOULD_BE(notNullptr(mpOut));
            SHOULD_BE(notNullptr(mpOut->mpDirectedEdgeRing));
            return mpOut->mpDirectedEdgeRing;
        }

        DirectedEdgeRing const * Vertex::getDirectedEdgeRing() const{
            SHOULD_BE(notNullptr(mpOut));
            SHOULD_BE(notNullptr(mpOut->mpDirectedEdgeRing));
            return mpOut->mpDirectedEdgeRing;        }
        
        FacetEdge * Vertex::getFacetEdge(){
            SHOULD_BE(notNullptr(mpOut))
            return mpOut;
        }
                        
        FacetEdge const * Vertex::getFacetEdge() const{
            SHOULD_BE(notNullptr(mpOut))
            return mpOut;        
        }
    }  // namespace Subdiv3

}  // namespace CrystalMesh





