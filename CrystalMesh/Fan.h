/* 
 * File:   Fan.h
 * Author: christoph
 *
 * Created on 17. Mai 2015, 22:01
 */

#ifndef FAN_H
#define	FAN_H
#include "ComplexTypes.h"
#include "Triangle.h"

namespace CrystalMesh{

    namespace Delaunay3{
        
        struct Fan{
            typedef std::vector<Triangle> Triangles;

            Subdiv3::DirectedEdgeRing * mpDring;
            
            Triangles getTriangles() const;
            
            Mathbox::Geometry::Point3D const getTopPoint() const;
            
            Mathbox::Geometry::Point3D const getBotPoint() const;

	};
        
        Fan const fanFrom(Subdiv3::DirectedEdgeRing * apDring);
    
    }
}

#endif	/* FAN_H */

