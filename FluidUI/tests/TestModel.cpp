#include "TestModel.h"
#include "../../CrystalMesh/DelaunayTriangulation3D.h"
#include "../../Mathbox/Mathbox.h"
#include "delaunayTriangleTest.h"
using namespace CrystalMesh;
using namespace Delaunay3;
using namespace Mathbox;
using namespace Geometry;
using namespace UI;
    
namespace{
    
    
    DelaunayTriangulation3D * dt = nullptr;
    DelaunayOpenGLExporter* model = nullptr;
    
    Triangle selectedTri = Triangle::invalid;
    Corner selectedEdge = Corner::invalid;

}

namespace CrystalMesh{
    
    namespace UI{
        
        namespace{
            Point3D const uPoint = pointFromXYZ( 0.0,  0.0,  1.0);
            Point3D const dPoint = pointFromXYZ( 0.0,  0.0,  -1.0);

   
            std::array<Point3D,4> sample2 = {
                pointFromXYZ( 1.0,  0.0,  0.0), 
                pointFromXYZ(0.0, 1.0, 0.0), 
                pointFromXYZ(0.0, -1.0, 0.0),
                pointFromXYZ(0.0, -1.0, 0.0)};

        }
        
        void triangleTest_launch(){
            dt = new DelaunayTriangulation3D();
            
            dt->makeTriangle(
                    vertexDataFrom(pointFromXYZ(0.0, 0.0, 0.0)),
                    vertexDataFrom(pointFromXYZ(1.0, 0.3, 0.0)),
                    vertexDataFrom(pointFromXYZ(0.5, 1.0, 0.0))
                    );
            
            selectedTri = dt->makeTriangle(
                    vertexDataFrom(pointFromXYZ(0.0, 0.0, 0.0)),
                    vertexDataFrom(pointFromXYZ(1.0, -0.3, 1.0)),
                    vertexDataFrom(pointFromXYZ(0.5, -1.0, 2.0))
                    );
            
            selectedEdge = cornerOf(selectedTri.getBoundaryEdges()[0]);
            
            model = new DelaunayOpenGLExporter;
            
            dt->addVertices(*model);
            dt->addTriangles(*model);
            dt->addCorners(*model);
            
            dtView->registerModel(model);
            
        }
        
        DelaunayOpenGLExporter const * currentModel(){
            return model;
        }

        void triangleTest_tearDown(){
            if (dt != nullptr)
                delete dt;
            
            if (model != nullptr )
                delete model;
            
            return;
        }
        
        
        
        
        GLTriangle const currentSelectedTrig(){
            auto const verts = selectedTri.getBoundaryVertices();
            GLTriangle result = glTriangleOf
                    (idOf(verts[0])
                    ,idOf(verts[1])
                    ,idOf(verts[2]));
            
            return result;
        }
        
        GLTriangle const selectedTrigSetNext(){
            auto next = selectedEdge.mRef->getFnext();
            selectedTri = cornerOf(next).adjancentTriangle();
            return currentSelectedTrig();
        }
        
        GLTriangle const selectedTrigSetPrev(){
            auto prev = selectedEdge.mRef->getInvFnext();
            selectedTri = cornerOf(prev).adjancentTriangle();
            return currentSelectedTrig();
        }
        
        GLEdge const currentSelectedEdge(){
            GLEdge result = glEdgeOf(originIndexOf(selectedEdge.mRef), destinationIndexOf(selectedEdge.mRef));
            return result;
        }
        
        GLEdge const selectedEdgeSetNext(){
            auto next = selectedEdge.mRef->getEnext();
            selectedEdge = cornerOf(next);
            return currentSelectedEdge();
        }
        
        GLEdge const selectedEdgeSetPrev(){
            auto prev = selectedEdge.mRef->getInvEnext();
            selectedEdge = cornerOf(prev);
            return currentSelectedEdge();
        }
        

        
    }
        
}
