#include "Mathbox.h"


namespace Mathbox{
    
    namespace Geometry{
    
        OrientedPlane3D const orientedPlaneFrom(Plane3D const & aPlane){
            auto const trafo = matrixFromNormal(aPlane.mNormal);
            OrientedPlane3D result;
            result.mTrafo = matrixFromCoordinateSystem(
                    xAxisOf(trafo),
                    yAxisOf(trafo),
                    zAxisOf(trafo),
                    pointOnPlaneOf(aPlane)
                    );
            return result;
        }
        
        OrientedPlane3D const orientedPlaneFrom(Point3D const & ap0, Point3D const & ap1, Point3D const & ap2){
            return orientedPlaneFrom(
                    planeFromThreePoints(ap0, ap1, ap2)
                    );
        }
        
        PointToPlaneProjection const pointPlaneProjection(OrientedPlane3D const & aPlane, Point3D const & aPoint){
            auto plane = planeFromOrientedPlane(aPlane);
            return pointPlaneProjection(plane, aPoint);
        }
        
        Point3D const originOf(OrientedPlane3D const & aPlane){
            return originOf(aPlane.mTrafo);
        }
        
        Vector3D const normalOf(OrientedPlane3D const & aPlane){
            return zAxisOf(aPlane.mTrafo);
        }
    }

}