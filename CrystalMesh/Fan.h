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
#include "Domain.h"

namespace CrystalMesh{

    namespace Delaunay3{
        
        struct Fan{
            typedef std::vector<Triangle> Triangles;

            Subdiv3::DirectedEdgeRing * mpDring;
            
            Triangles getTriangles() const;
            
            Subdiv3::DirectedEdgeRing* centerToTop() const;
            
            Mathbox::Geometry::Point3D const getTopPoint() const;
            
            Mathbox::Geometry::Point3D const getBotPoint() const;
            
            Subdiv3::FacetEdge* getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const;
            
            Domain const getDomain() const;

	};
        
        Fan const fanFrom(Subdiv3::DirectedEdgeRing * apDring);
    
    }
}

#endif	/* FAN_H */

