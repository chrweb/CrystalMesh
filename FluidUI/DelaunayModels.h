/* 
 * File:   DelaunayModels.h
 * Author: christoph
 *
 * Created on 27. April 2015, 22:07
 */

#ifndef DELAUNAYMODELS_H
#define	DELAUNAYMODELS_H

namespace CrystalMesh{

    namespace Delaunay3{
        
        struct Triangle;
        
        class DelaunayTriangulation3D;
    };
    
    namespace UI{
        
        void drawTriangle(Delaunay3::Triangle const & aTri);
    
    }

}


 




#endif	/* DELAUNAYMODELS_H */

