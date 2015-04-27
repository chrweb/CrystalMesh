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
        
    }
} 