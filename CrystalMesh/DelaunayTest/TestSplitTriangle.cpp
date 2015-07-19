#include "TestInclude.h"
using namespace Mathbox;
using namespace Geometry;
using namespace CrystalMesh;
using namespace Subdiv3;
using namespace Delaunay3;

typedef DelaunayTriangulation3D::TetPoints TetPoints;
typedef DelaunayTriangulation3D::TetIntPoints TetIntPoints;

namespace{
    
        TetPoints const tetPoints(){
            auto result = TetPoints{
                pointFromXY0(-1.0, -0.5),
                pointFromXY0(1.0, -0.5),
                pointFromXY0(0.0, 1.0),
                pointFromXYZ(0.0, 0.0, 1.0)
            };
            return result;
        }
        
        Point3D const insertionPoint()
        {
            return pointFromXYZ(0.0, 0.0, 0.5);
        }
        
        Point3D const meanOf(Point3D const p0, Point3D const p1, Point3D const p2){
            auto resultVec = 1/3*vectorTo(p0)+vectorTo(p1)+vectorTo(p2);
            return pointAt(resultVec);
        }
    
}

TEST(SplitTriangle, executeSplit){
    DelaunayTriangulation3D dt;
    Tet tet = dt.makeTet(tetPoints());
    Triangle triangle = tet.getTriangleAt(0);
    
    dt.flip1to4(tet, insertionPoint());

    Triangle innerTriangle = triangleLeftOf(triangle.getBoundaryEdges()[0]->getInvFnext());
    
    //inner triangle holds insertion point?
    ASSERT_TRUE(innerTriangle.isVertexPoint(insertionPoint()));
    
    //perform split
    auto innerPoints = innerTriangle.getBoundaryPoints();
    Point3D splitPoint = meanOf(innerPoints[0], innerPoints[1], innerPoints[2]);
    dt.splitTriangle(innerTriangle, splitPoint);
    
    
    
}
