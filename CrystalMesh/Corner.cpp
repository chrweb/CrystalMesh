#include "../Mathbox/Mathbox.h"
#include "Corner.h"
#include "DelaunayVertex.h"

namespace CrystalMesh{

    namespace Delaunay3{
        bool Corner::representsSegment(Mathbox::Geometry::Point3D const& p0, Mathbox::Geometry::Point3D const & p1) const{
            auto org = originPointOf(mRef);
            auto dest = destinationPointOf(mRef);
            
            if (exactEqual(p0, org) && exactEqual( p1, dest))
                return true;
            
            if (exactEqual(p0, dest) && exactEqual(p1, org))
                return true;
            
            return false;
        }

    }
}
