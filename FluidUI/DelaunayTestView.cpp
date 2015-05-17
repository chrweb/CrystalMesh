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
            mSelectedEdge = GLEdge::invalid;
            mSelectedTrig = GLTriangle::invalid;
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
            glRotatef(hAng,1,0,0); 
            glRotatef(vAng,0,1,0);
            glScalef(float(size),float(size),float(size)); 
            drawModel();
            glPopMatrix();
        }
        
        void DelaunayTestView::setVerticalAngleTo(float aVang){
            vAng = aVang;
        }
            
        void DelaunayTestView::setHorizontalAngleTo(float aHang){
            hAng = aHang;
        }
            
        void DelaunayTestView::rotateViewH(float aHang){
            setHorizontalAngleTo(aHang);
            redraw();
        }
            
        void DelaunayTestView::rotateViewV(float aVang){
            setVerticalAngleTo(aVang);
            redraw();
        }
        
        void DelaunayTestView::incrementHorizontalAngleBy(float aDeltaH){
            hAng = hAng+aDeltaH;
        }
        
        void DelaunayTestView::incrementVerticalAngleBy(float aDeltaV){
            vAng = vAng+aDeltaV;
        }

        void DelaunayTestView::rotateIncrementalH(float aDeltaH){
            incrementHorizontalAngleBy(aDeltaH);
            redraw();
        }
        
        void DelaunayTestView::rotateIncrementalV(float aDeltaV){
            incrementVerticalAngleBy(aDeltaV);
            redraw();
        }
        
        
        void DelaunayTestView::setSelectedEdgeTo(const GLEdge& aEdge) {
            mSelectedEdge = aEdge;
            redraw();
        }
        
        void DelaunayTestView::setSelectedTrigTo(const GLTriangle& aTrig){
            mSelectedTrig = aTrig;
            redraw();
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
            
      
            auto const & tbo = *mpModel->getTriangleBuffer();
            
            glShadeModel(GL_FLAT);
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, mpModel->getVertexBuffer()->data());
            
            
            setTrigStyleDefault();
            glBegin(GL_TRIANGLES);
            for (auto const tri : tbo){
                drawTrig(tri);
            }
            glEnd();
            
            auto const& lbo = *mpModel->getEdgeBuffer();    
            setLineStyleDefault();
            glBegin(GL_LINES);
            for (auto const edge:lbo){
                drawLine(edge);
            }
            
            glEnd();
      
    
        };
        
        void DelaunayTestView::setTrigStyleDefault() const{
            glColor4f(0.0, 0.0, 1.0, 0.5);
        }
        
        void DelaunayTestView::setTrigStyleSelected() const{
            glColor4f(0.0, 0.0, 1.0, 1.0);
        }
        
        void DelaunayTestView::setLineStyleSelected() const{
            glColor4f(1.0, 0.0, 0.0, 1.0);
        }
        
        void DelaunayTestView::setLineStyleDefault() const{
            glColor4f(0.8, 0.2, 0.0, 1.0);
        }
        
        void DelaunayTestView::drawTrig(const GLTriangle& aTrig) const{
            if (aTrig == mSelectedTrig){
                setTrigStyleSelected();
            }
            
            glArrayElement(aTrig.id0);
            glArrayElement(aTrig.id1);
            glArrayElement(aTrig.id2);
            
            if (aTrig == mSelectedTrig){
                setTrigStyleDefault();
            }
        }
        
        void DelaunayTestView::drawLine(const GLEdge& aEdge) const{
            if (aEdge == mSelectedEdge){
                setLineStyleSelected();
            }
            
            glArrayElement(aEdge.id0);
            glArrayElement(aEdge.id1);
            
            if (aEdge == mSelectedEdge){
                setLineStyleDefault();
            }
        
        }


    
        DelaunayTestView::~DelaunayTestView(){
            return;
        }
    
    
    }

}


