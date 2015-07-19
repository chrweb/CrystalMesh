/* 
 * File:   Geometry_LineSegment3D.h
 * Author: christoph
 *
 * Created on 15. Juli 2015, 14:04
 */

#ifndef GEOMETRY_LINESEGMENT3D_H
#define	GEOMETRY_LINESEGMENT3D_H

namespace Mathbox{
    
    namespace Geomtry{
        
        struct LineSegment3D;
        
        struct Point3D;
        
        LineSegment3D const lineSegmentBetween(Point3D const& aP0, Point3D const& aP1);
    
    }
}

#endif	/* GEOMETRY_LINESEGMENT3D_H */

