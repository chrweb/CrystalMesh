/* 
 * File:   DelaunayModels.h
 * Author: christoph
 *
 * Created on 27. April 2015, 22:07
 */

#ifndef DELAUNAYMODELS_H
#define	DELAUNAYMODELS_H

#include "../CrystalMesh/DelaunayForwardDecs.h"
#include "../Mathbox/Mathbox.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <vector>

namespace CrystalMesh{


    
    namespace UI{
        
        struct Pointf{
            float x;
            float y;
            float z;
        };
        
        Pointf const glPointOf(Mathbox::Geometry::Point3D const & aPoint);
        
        struct GLTriangle{
            GLuint id0;
            GLuint id1;
            GLuint id2;
        };
        
        GLTriangle const glTriangleOf(Delaunay3::Index id0, Delaunay3::Index id1, Delaunay3::Index id2);
         
        
            
        
        class DelaunayOpenGLExporter
        :public Delaunay3::Exporter
        {

            DelaunayOpenGLExporter();
            virtual ~DelaunayOpenGLExporter();
            
            virtual Delaunay3::Index addVertex(Mathbox::Geometry::Point3D const & aPoint3D) override;
            virtual void addTriangle(Delaunay3::Index id0, Delaunay3::Index id1, Delaunay3::Index id2) override;
            
            std::vector<Pointf> const * getVertexBuffer() const;
            
            std::vector<GLTriangle> const * getTriangleBuffer() const;
            
        private:
            
            std::vector<Pointf> mVertexBuffer;
            std::vector<GLTriangle> mTriangleBuffer;
            
            GLuint mLastFreeIndex;
        
        };
        

    
    }

}


 




#endif	/* DELAUNAYMODELS_H */

