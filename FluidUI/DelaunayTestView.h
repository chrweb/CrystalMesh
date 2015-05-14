/* 
 * File:   DelaunayTestView.h
 * Author: christoph
 *
 * Created on 27. April 2015, 22:43
 */

#ifndef DELAUNAYTESTVIEW_H
#define	DELAUNAYTESTVIEW_H

#include <FL/Fl_Gl_Window.H>

#include "DelaunayModels.h"


namespace CrystalMesh{

    namespace UI{
        
        class DelaunayOpenGLExporter;
        
        class DelaunayTestView: public Fl_Gl_Window {
            
            public:
    
            DelaunayTestView(int x,int y,int w,int h,const char *l=0);
            
            void registerModel(DelaunayOpenGLExporter const *mpModel);
            
           //void setCurrentSelectedCorner(Delaunay3::Triangle const aTri)
    
            void draw();
    
            virtual ~DelaunayTestView();

            private:
                
            void drawModel();
                
            DelaunayOpenGLExporter const * mpModel;
            
            float vAng,hAng; 
            
            float xshift,yshift;
                
        };

    
    
    }

}


#endif	/* DELAUNAYTESTVIEW_H */

