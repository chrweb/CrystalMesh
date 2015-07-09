#include <functional>

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
        
        
        void triangleTestFan(){
            
             
            Point3D const uPoint = pointFromXYZ( 0.0,  0.0,  1.0);
            Point3D const dPoint = pointFromXYZ( 0.0,  0.0,  -1.0);

   
            std::array<Point3D,4> sample = {
                pointFromXYZ( 1.0,  0.0,  0.0), 
                pointFromXYZ(0.0, 1.0, 0.0), 
                pointFromXYZ(-1.0, 0.0, 0.0),
                pointFromXYZ(0.0, -1.0, 0.0)};

            
            auto fan = dt->makeFan(uPoint, dPoint, std::vector<Mathbox::Geometry::Point3D>(sample.begin(), sample.end()));
            selectedTri = fan.getTriangles().at(0);
            
            
            selectedEdge = cornerOf(selectedTri.getBoundaryEdges()[0]);
        
        }
        
        void triangleTestCrater(){
            
            Point3D center = pointFromXYZ(0.0, 0.0, -1.0);
            std::array<Point3D,3> bnd0= {
                pointFromXY0(1.0, -0.5),
                pointFromXY0(0.0, 0.5),
                pointFromXY0(-1.0, -0.5)
                };
            Crater const crater = dt->makeCrater(center, DelaunayTriangulation3D::CraterPoints(bnd0.begin(), bnd0.end()));
            auto triangle = crater.getTriangles().front();
            
            selectedTri = triangle;
            selectedEdge = cornerOf(triangle.getBoundaryEdges()[0]);

            return;
        }
        
        void triangleTestTetInteriour(){
        
            DelaunayTriangulation3D::TetIntPoints const points = {
                pointFromXY0(1.0, -0.5),
                pointFromXY0(0.0, 0.5),
                pointFromXY0(-1.0, -0.5),
                pointFromXYZ( 0.0,  0.0,  3.0),
                pointFromXYZ( 0.0,  0.0,  1.0)};
            
            TetInteriour ti = dt->makeTetInterior(points);
            
            auto triangle = ti.getTriangleAt(0);
            
            selectedTri = triangle;
            selectedEdge = cornerOf(triangle.getBoundaryEdges()[0]);

            return;    
        }
        
        void triangleTestTet(){
            
            DelaunayTriangulation3D::TetPoints points = {
                pointFromXY0(-1.0, -0.5),
                pointFromXY0(1.0, -0.5),
                pointFromXY0(0.0, 1.0),
                pointFromXYZ(0.0, 0.0, 1.0)};
            
            Tet tet = dt->makeTet(points);
            
            auto triangle = tet.getTriangleAt(0);
            
            selectedTri = triangle;
            selectedEdge = cornerOf(triangle.getBoundaryEdges()[0]);

            return;
        
        }
        
        void triangleTest_launch(){
            dt = new DelaunayTriangulation3D();
            
            triangleTestTet();

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
            //move upwards in fnext ring und set the selected
            Subdiv3::FacetEdge* next = selectedEdge.mRef->getFnext();
            selectedEdge = cornerOf(next);
            // set the triangle
            selectedTri = cornerOf(next).adjancentTriangle();
            return currentSelectedTrig();
        }
        
        GLTriangle const selectedTrigSetPrev(){
            //move backwards in selected
            Subdiv3::FacetEdge* prev = selectedEdge.mRef->getInvFnext();
            ///set selected
            selectedEdge = cornerOf(prev);
            //set the selected triangle
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
