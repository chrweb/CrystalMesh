/* 
 * File:   DelaunayTestView.cpp
 * Author: christoph
 * 
 * Created on 27. April 2015, 22:43
 */

#include "DelaunayTestView.h"
#include "DelaunayModels.h"

namespace CrystalMesh{
   
    namespace UI{
        DelaunayTestView::DelaunayTestView(int x, int y, int w, int h, const char* l)
        :Fl_Gl_Window(x, y, w, h, l)
        {

        }

        
        void DelaunayTestView::registerModel(const DelaunayOpenGLExporter* pModel){
            mpModel = pModel;
        }
        
        
        
        void DelaunayTestView::draw(){}
    
        DelaunayTestView::~DelaunayTestView(){}
    
    
    }

}


