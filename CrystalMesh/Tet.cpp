#include <stddef.h>
#include "Corner.h"
#include "../Toolbox/Checks.h"
#include "Tet.h"

namespace CrystalMesh{

    namespace Delaunay3{
        using namespace Subdiv3;
        using namespace Mathbox;
        using namespace Geometry;
        
        Triangle const Tet::getTriangleAt(Index aIndex) const{
            SHOULD_BE(aIndex<5);
            return mTri[aIndex];
        }
    
    
    }
}