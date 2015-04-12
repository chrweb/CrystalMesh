#include <algorithm>
#include "Triangle.h"
#include "DelaunayVertex.h"

using namespace CrystalMesh;
using namespace Delaunay3;

Triangle::BoundaryEdges const Triangle::getBoundaryEdges() const{
	auto pBnd = mpDualEdgeRing->getRingMember()->getDual();

	Triangle::BoundaryEdges result;

	result[0] = pBnd;
	result[1] = result[0]->getEnext();
	result[2] = result[1]->getEnext();

	return result;
}

Triangle::BoundaryPoints const Triangle::getBoundaryPoints() const{
    auto const bndEdges = getBoundaryEdges();
    BoundaryPoints result;
    for (Index i = 0; i<3; i++){
        result[i] = pointOf(bndEdges[i]->getOrg());
    }
    return result;
}

Triangle::BoundaryVertices const Triangle::getBoundaryVertices() const{
    auto bnd = getBoundaryEdges();
    BoundaryVertices result = {bnd[0]->getOrg(), bnd[1]->getOrg(), bnd[2]->getOrg()};
    return result;
}

Subdiv3::FacetEdge* Triangle::boundaryWith(Mathbox::Geometry::Point3D const & aOrg, Mathbox::Geometry::Point3D const & aDest){
    using namespace Subdiv3;
    auto boundaryEdges =getBoundaryEdges();
    std::array<EdgeRing*,3> edgeRings;
    
    auto toEdgeRing = [](FacetEdge* edge)->EdgeRing*{
        return edge->getDirectedEdgeRing()->getEdgeRing();
    };
    
    std::transform(boundaryEdges.begin(), boundaryEdges.end(), edgeRings.begin(), toEdgeRing);
    return facetEdgeWithEndPoints(aOrg, aOrg, edgeRings);
}

Triangle const Triangle::getCounterOriented() const{
    Triangle result;
    result.mpDualEdgeRing = this->mpDualEdgeRing->getSym();
    return result;
}
       

bool const Triangle::operator == (const Triangle& other) const{
    return (other.mpDualEdgeRing == mpDualEdgeRing);
}
        
bool const Triangle::operator != (const Triangle& other) const{
    return ! operator ==(other);
}

/*
Tet const Triangle::lowerTet() const{
    Triangle other = getCounterOrientedOf(*this);
    return other.upperTet();
}

Tet const Triangle::upperTet() const{
    Subdiv3::Vertex* domain = mpDualEdgeRing->getOrg();
    auto adj = getAdjacentRingsOf(*domain);
    Tet result;
    result.mpDualVertex = domain;
   
    for (Index i = 0 ; i<4; i++){
        result.mTri[i] = triangleOf(adj[i]);
    }
    
    return result;
}
*/

Triangle const Triangle::invalid  = {nullptr};