/* 
 * File:   TestModel.h
 * Author: christoph
 *
 * Created on 16. Mai 2015, 21:29
 */

#ifndef TESTMODEL_H
#define	TESTMODEL_H
#include "../DelaunayModels.h"


namespace CrystalMesh{

    namespace UI{
        
        void triangleTest_launch();

        DelaunayOpenGLExporter const * currentModel();

        void triangleTest_tearDown();
        
        GLTriangle const currentSelectedTrig();
        
        GLTriangle const selectedTrigSetNext();
        
        GLTriangle const selectedTrigSetPrev();
        
        GLEdge const currentSelectedEdge();
        
        GLEdge const selectedEdgeSetNext();
        
        GLEdge const selectedEdgeSetPrev();
        
    }

}



#endif	/* TESTMODEL_H */
