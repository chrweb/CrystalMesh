#include <algorithm>
#include "ComplexTypes.h"
#include "Corner.h"
#include "Domain.h"
#include "Triangle.h"
#include "DelaunayVertex.h"
#include "../Toolbox/Checks.h"
#include "Tet.h"



using namespace CrystalMesh;
using namespace Delaunay3;
using namespace Mathbox::Geometry;

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

Subdiv3::FacetEdge* Triangle::boundaryWith(Mathbox::Geometry::Point3D const & aOrg, Mathbox::Geometry::Point3D const & aDest) const{
    using namespace Subdiv3;
    auto boundaryEdges =getBoundaryEdges();
    std::array<EdgeRing*,3> edgeRings;
    
    auto toEdgeRing = [](FacetEdge* edge)->EdgeRing*{
        return edge->getDirectedEdgeRing()->getEdgeRing();
    };
    
    std::transform(boundaryEdges.begin(), boundaryEdges.end(), edgeRings.begin(), toEdgeRing);
    return facetEdgeWithEndPoints(aOrg, aDest, edgeRings);
}

Triangle const Triangle::getCounterOriented() const{
    Triangle result;
    result.mpDualEdgeRing = this->mpDualEdgeRing->getSym();
    return result;
}

bool const Triangle::pointBehind(Mathbox::Geometry::Point3D const& aPoint) const{
    auto orientedPlane = getOrientedPlane();
    auto result = pointPlaneProjection(orientedPlane, aPoint);
    return result == PointToPlaneProjection::underPlane;
}

Mathbox::Geometry::OrientedPlane3D const Triangle::getOrientedPlane() const{
    auto points = getBoundaryPoints();
    return orientedPlaneFrom(points[0], points[1], points[2]);
}     

bool const Triangle::operator == (const Triangle& other) const{
    return (other.mpDualEdgeRing == mpDualEdgeRing);
}
        
bool const Triangle::operator != (const Triangle& other) const{
    return ! operator ==(other);
}

bool const Triangle::isVertexPoint(Mathbox::Geometry::Point3D const& aPoint) const{
    auto resultvertex = vertexWithPoint(aPoint);
    return resultvertex != Subdiv3::invalidVertex;
}

Delaunay3::Domain const Triangle::getDomainUnder() const{
    return domainFrom(mpDualEdgeRing->getOrg());
}
           
Delaunay3::Domain const Triangle::getDomainOver() const{
    Triangle other = getCounterOriented();
    return other.getDomainUnder();
}

namespace{
    Delaunay3::Tet const tetFromDomain(Domain const& domain){
        Tet result;
        auto triangles = domain.getTriangles();
        //is a triangle?
        MUST_BE(triangles.size() == 4);
        std::copy(triangles.begin(), triangles.end(), result.mTri.begin());
        return result;
    }

}

Delaunay3::Tet const Triangle::getTetOver() const{
    auto domain = getDomainOver();
    return tetFromDomain(domain);
    
}
            
Delaunay3::Tet const Triangle::getTetUnder() const{
    auto domain = getDomainUnder();
    return tetFromDomain(domain);
}

Subdiv3::VertexPtr const Triangle::vertexWithPoint(Mathbox::Geometry::Point3D const & aPoint) const{
    auto points = getBoundaryPoints();
    auto const&pointToFind = aPoint;
    auto finder = [&pointToFind](Point3D const& aCurrentPoint){
        return exactEqual(pointToFind, aCurrentPoint);
    };
    auto found = std::find_if(points.begin(), points.end(), finder);
    if (found == points.end())
        return Subdiv3::invalidVertex;
    
    auto verts = getBoundaryVertices();
    return verts[found-points.begin()];
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





Triangle const Triangle::invalid = {nullptr}; 
    
namespace CrystalMesh{

    namespace Delaunay3{
        
        Triangle const triangleOf(Subdiv3::DirectedEdgeRing * apDring){
            SHOULD_BE(apDring->computeEdgeRingSize()  == 3);
            Triangle result = {apDring};
            return result;
        }
        
        Triangle const triangleLeftOf(Subdiv3::FacetEdge* aFacetEdge){
            return triangleOf(aFacetEdge->getDual()->getDirectedEdgeRing());
        }
    }
}

