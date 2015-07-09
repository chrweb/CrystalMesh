#include <stddef.h>
#include "../Mathbox/Mathbox.h"
#include "ComplexTypes.h"
#include "AdjacentDirectedEdgeRings.h"
#include "DelaunayVertex.h"
#include "../Toolbox/Checks.h"

#include "Corner.h"
namespace CrystalMesh{

    namespace Delaunay3{
        using namespace Mathbox;
        using namespace Geometry;
        using namespace Subdiv3;
        
        bool Corner::representsSegment(Mathbox::Geometry::Point3D const& p0, Mathbox::Geometry::Point3D const & p1) const{
            auto org = originPointOf(mRef);
            auto dest = destinationPointOf(mRef);
            
            if (exactEqual(p0, org) && exactEqual( p1, dest))
                return true;
            
            if (exactEqual(p0, dest) && exactEqual(p1, org))
                return true;
            
            return false;
        }
        
        Corner const Corner::invalid  = {nullptr, nullptr};
        
        Triangle const Corner::adjancentTriangle() const{
            return triangleOf(mRef->getDual()->getDirectedEdgeRing());
        }

        
        Point3D const Corner::getOriginPoint() const{
            return originPointOf(mRef);
        }
            
        Point3D const Corner::getDestinationPoint() const{
            return destinationPointOf(mRef);
        }
        
        
        namespace{
            Corner const cornerFrom(Subdiv3::EdgeRing * apRing, Subdiv3::Vertex* apDomain){
            
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

                MUST_BE(false);
                UNREACHABLE;                    
            }
        
        }
        
        
        Corner const cornerFrom(Subdiv3::EdgeRing * apRing, Delaunay3::Domain const& aDomainAbove){
            return cornerFrom(apRing, aDomainAbove.mDual);
        }

    }
}
