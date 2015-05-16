/* 
 * File:   DelaunayTestView.cpp
 * Author: christoph
 * 
 * Created on 27. April 2015, 22:43
 */
#define GL_GLEXT_PROTOTYPES
#include "DelaunayTestView.h"
#include "DelaunayModels.h"
#include <GL/gl.h>
#include <GL/glext.h>

namespace CrystalMesh{
   
    namespace UI{
        DelaunayTestView::DelaunayTestView(int x, int y, int w, int h, const char* l)
        :Fl_Gl_Window(x, y, w, h, l)
        ,mpModel(nullptr)
        {
            vAng = 0.0; 
            hAng=0.0; 
            size=10.0;
            
        }

        
        void DelaunayTestView::registerModel(const DelaunayOpenGLExporter* pModel){
            mpModel = pModel;
        }
        
        
        
        void DelaunayTestView::draw(){
            if (!valid()) {
                glLoadIdentity(); 
                glViewport(0,0,w(),h());
                glOrtho(-10,10,-10,10,-20000,10000); 
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix(); 
            glTranslatef(xshift, yshift, 0);
            glRotatef(hAng,0,1,0); 
            glRotatef(vAng,1,0,0);
            glScalef(float(size),float(size),float(size)); 
            drawModel();
            glPopMatrix();
        }
        
//        void DelaunayTestView::drawModel(){
//            glShadeModel(GL_FLAT);
//            glBegin(GL_TRIANGLES);
//            glColor4f(0.0, 0.0, 1.0, 0.5);
//            auto const &buffer = *mpModel->getVertexBuffer();
//            glVertex3fv((GLfloat*) &buffer[0]);
//            glVertex3fv((GLfloat*) &buffer[1]);
//            glVertex3fv((GLfloat*) &buffer[2]);
//                
//            glEnd();
//        }
//        
//        void DelaunayTestView::drawModel(){
//            if (mpModel == nullptr)
//                return;
//            
//            auto vbo = mpModel->getVertexBuffer();
//            auto tbo = mpModel->getTriangleBuffer();
//            
//            glShadeModel(GL_FLAT);
//            glColor4f(0.0, 0.0, 1.0, 0.5);
//            GLuint vbh;        
//            glGenBuffers(1, &vbh);
//            glBindBuffer(GL_ARRAY_BUFFER, vbh);
//            glBufferData(GL_ARRAY_BUFFER, vbo->size()*sizeof(Pointf), vbo->data(), GL_STATIC_DRAW);        
//       //     glDeleteBuffers(1, &vbh);
//            
//            glDisable(GL_CULL_FACE);
//            
//            GLuint tbh;
//            glGenBuffers(1, &tbh);
//            glBindBuffer(GL_ARRAY_BUFFER, tbh);
//            glBufferData(GL_ELEMENT_ARRAY_BUFFER, tbo->size()*sizeof(GLTriangle), tbo->data(), GL_STATIC_DRAW);
//            
//            glDrawArrays(GL_TRIANGLES, 0, tbo->size());
//            
//     //       glDrawElements(GL_TRIANGLES, tbo->size(), GL_UNSIGNED_SHORT, NULL);
//    
//        };
        
    void DelaunayTestView::drawModel(){
            if (mpModel == nullptr)
                return;
            
            auto vbo = mpModel->getVertexBuffer();
            auto const & tbo = *mpModel->getTriangleBuffer();
            
            glShadeModel(GL_FLAT);
            glColor4f(0.0, 0.0, 1.0, 0.5);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, mpModel->getVertexBuffer()->data());
            
            glBegin(GL_TRIANGLES);
            for (auto const tri : tbo){
                glArrayElement(tri.id0);
                glArrayElement(tri.id1);
                glArrayElement(tri.id2);
            }
            glEnd();
      
    
        };


    
        DelaunayTestView::~DelaunayTestView(){
            return;
        }
    
    
    }

}


