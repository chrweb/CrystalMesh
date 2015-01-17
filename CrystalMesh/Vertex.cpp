/*
 * Vertex.cpp
 *
 *  Created on: 16.07.2014
 *      Author: christoph
 */
#include "Vertex.h"
#include "../Toolbox/Checks.h"
#include "DirectedEdgeRing.h"

namespace CrystalMesh {

    namespace Subdiv3 {

        using namespace Toolbox;

        bool const Vertex::isDual() const{
            MUST_BE(notNullptr(mpOut));
            return mpOut->isDual();
        }

        bool const Vertex::isPrimal() const{
                return !isDual();
        }

        DirectedEdgeRing * Vertex::getDirectedEdgeRing(){
            MUST_BE(notNullptr(mpOut));
            return mpOut;
        }

        DirectedEdgeRing const * Vertex::getDirectedEdgeRing() const{
            MUST_BE(notNullptr(mpOut));
            return mpOut;
        }
    }  // namespace Subdiv3

}  // namespace CrystalMesh





