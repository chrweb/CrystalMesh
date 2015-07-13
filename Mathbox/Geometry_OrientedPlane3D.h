/*
 * Geometry OrientedPlane3D.h
 *
 *  Created on: 05.10.2014
 *      Author: christoph
 */
#pragma once

namespace Mathbox {

        namespace Geometry {

            struct OrientedPlane3D;
            struct Plane3D;        
            struct Vector3D;
            struct Point3D;
            enum struct PointToPlaneProjection;
            
            OrientedPlane3D const orientedPlaneFrom(Plane3D const & aPlane);
            
            OrientedPlane3D const orientedPlaneFrom(Point3D const & ap0, Point3D const & ap1, Point3D const & ap2);
            
            PointToPlaneProjection const pointPlaneProjection(OrientedPlane3D const & aPlane, Point3D const & aPoint);
            
            Point3D const originOf(OrientedPlane3D const & aPlane);
            
            Vector3D const normalOf(OrientedPlane3D const & aPlane); 


    }  // namespace Geometry



}  // namespace Mathbox


