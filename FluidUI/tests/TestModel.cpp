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

}

namespace CrystalMesh{
    
    namespace UI{
        
        void triangleTest_launch(){
            dt = new DelaunayTriangulation3D();
            
            dt->makeTriangle(
                    vertexDataOf(pointFromXYZ(0.0, 0.0, 0.0)),
                    vertexDataOf(pointFromXYZ(1.0, 0.3, 0.0)),
                    vertexDataOf(pointFromXYZ(0.5, 1.0, 0.0))
                    );
            
            dt->makeTriangle(
                    vertexDataOf(pointFromXYZ(0.0, 0.0, 0.0)),
                    vertexDataOf(pointFromXYZ(1.0, -0.3, 1.0)),
                    vertexDataOf(pointFromXYZ(0.5, -1.0, 2.0))
                    );
            
            model = new DelaunayOpenGLExporter;
            
            dt->addVertices(*model);
            dt->addTriangles(*model);
            
            TestView->registerModel(model);
            
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

        
    }
        
}
