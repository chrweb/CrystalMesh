/*
 * Geometry Matrix4x3.h
 *
 *  Created on: Oct 4, 2014
 *      Author: christoph
 */
#pragma once

namespace Mathbox{
    
    namespace Geometry{
        
        struct Point3D;
        struct Vector3D;
        
        Matrix4x3 const matrixFromNormal( Vector3D const & aNormal);
        
        Matrix4x3 const matrixFromCoordinateSystem(Vector3D const & aX, Vector3D const & aY, Vector3D const & aZ, Point3D const & aOrg);
        
        Vector3D const xAxisOf(Matrix4x3 const& aMatrix);
        
        Vector3D const yAxisOf(Matrix4x3 const& aMatrix);
        
        Vector3D const zAxisOf(Matrix4x3 const& aMatrix);
        
        Point3D const originOf(Matrix4x3 const& aMatrix);
      
        bool const isLeftHanded(Matrix4x3 const& aMatrix);
        
        bool const isRightHanded(Matrix4x3 const& aMMatrix);
        
    
    }

}
