

#include "../CrystalMesh/Triangle.h"
#include "../Mathbox/Mathbox.h"
#include "DelaunayModels.h"
#include <GL/freeglut.h>
#include <stdlib.h>


namespace CrystalMesh{

    namespace UI{
    
        using namespace Delaunay3;
        
        GLfloat const glFloatOf(double const aDouble){
            return (GLfloat) aDouble;
        }
        void drawPoint(Mathbox::Geometry::Point3D const & aPoint){
            glVertex3f(glFloatOf(aPoint.mX), glFloatOf(aPoint.mY), glFloatOf(aPoint.mZ));
        }
    
        void drawTriangle(Delaunay3::Triangle const & aTri){
            
            auto points = aTri.getBoundaryPoints();
            glBegin(GL_TRIANGLES);
            drawPoint(points[0]);
            drawPoint(points[1]);
            drawPoint(points[2]);
            glEnd();
            
            glBegin(GL_LINE);
            drawPoint(points[0]);
            drawPoint(points[1]);
            drawPoint(points[1]);
            glEnd();
                    
        }
        

            
        Pointf const glPointOf(Mathbox::Geometry::Point3D const & aPoint){
           Pointf result = {(float) aPoint.mX, (float) aPoint.mY, (float) aPoint.mZ};
           return result;
        }
       
        GLTriangle const glTriangleOf(Delaunay3::Index id0, Delaunay3::Index id1, Delaunay3::Index id2){
            GLTriangle result = {(GLuint) id0, (GLuint) id1, (GLuint) id2};
            return result;
        }
        
        
        DelaunayOpenGLExporter::DelaunayOpenGLExporter()
        :mVertexBuffer()
        ,mTriangleBuffer()
        {
            mLastFreeIndex = 0;
        }
        
        void DelaunayOpenGLExporter::initialze(){
            mLastFreeIndex = 0;
            mTriangleBuffer.clear();
            mVertexBuffer.clear();
        }
        
        DelaunayOpenGLExporter::~DelaunayOpenGLExporter(){}
        
        Delaunay3::Index DelaunayOpenGLExporter::addVertex(Mathbox::Geometry::Point3D const & aPoint3D){
            Index result = mLastFreeIndex;
            mVertexBuffer.push_back(glPointOf(aPoint3D));
            mLastFreeIndex++;
            return result;
        }
        
        void DelaunayOpenGLExporter::addTriangle(Delaunay3::Index id0, Delaunay3::Index id1, Delaunay3::Index id2){
            GLTriangle tri = glTriangleOf(id0, id1, id2);
            mTriangleBuffer.push_back(tri);
            return;
        }
        
        std::vector<Pointf> const * DelaunayOpenGLExporter::getVertexBuffer() const{
            return &mVertexBuffer;
        }
            
        std::vector<GLTriangle> const * DelaunayOpenGLExporter::getTriangleBuffer() const{
            return &mTriangleBuffer;
        }
        
    }
} 

int main(){};