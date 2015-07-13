#include "Mathbox.h"
#include "Geometry_Matrix4x3.h"
#include "../Toolbox/Checks.h"
using namespace Mathbox;
using namespace Geometry;

namespace{
 

    double const signumNonZero(double const aNumber){
        double result = signumOf(aNumber);
        if (result == 0.0)
            return 1;

        return result;
    }


    Vector3D const directionWithSmallestComponentOf(Vector3D const& aVec){
        using namespace Mathbox;
        double minimumComp = minimumOf( minimumOf(absoluteOf(aVec.mX), absoluteOf(aVec.mY)), absoluteOf(aVec.mZ));



        if (minimumComp == absoluteOf(aVec.mX)){
            return signumNonZero(minimumComp)*Vector3D::xAxis;
        }

        if (minimumComp== absoluteOf(aVec.mY)){
            return signumNonZero(minimumComp)*Vector3D::yAxis;
        }

        if (minimumComp== absoluteOf(aVec.mZ)){
            return signumNonZero(minimumComp)* Vector3D::zAxis;
        }

        UNREACHABLE;

}

        }

namespace Mathbox{
    namespace Geometry{
    /*
    //Matrix4x3 result;
    //Vector3D & x = xAxisOf(result);
    //Vector3D & y = yAxisOf(result);
    //Vector3D & z = zAxisOf(result);
    //originOf(result) = Vector3D::zero;

    Vector3D const & z = aNormal;
    Vector3D x;
    Vector3D y;
    
    
    if(isWithin(0.0001, z.mY, 0.9999)) { 
            y = normalizedCrossProductOf(z, Vector3D::yAxis);
            x = normalizedCrossProductOf(y, z);
            
         
    } else if(isWithin(-0.9999, z.mY, -0.0001)) { 
            y = normalized(crossProductOf(z, -Vector3D::yAxis));
            x = normalized(crossProductOf(y, z));
    } else { 
        //vertical
            if(absoluteOf(z.mX) < absoluteOf(z.mY)) {
                    auto const length = squareRootOf(squared(z.mY) + squared(z.mZ));
                    y.mX = 0.0;
                    y.mY = z.mZ / length;
                    y.mZ = z.mY / length;
                            x = normalizedCrossProductOf(y, z);
                    } else {
                //horizontal
                            auto const length = squareRootOf(squared(z.mX)+ squared(z.mZ));
                            x.mX = z.mZ / length;
                            x.mY = 0.0;
                            x.mZ = -z.mX / length;
                            y = normalizedCrossProductOf(z, x);
                    }

                    y = normalizedCrossProductOf(z, x);
            }

            auto result = matrixFromCoordinateSystem(x, y, z, Point3D::zero);

            SHOULD_BE("expected right handed" && isRightHanded(result));
            return result;
             * */
        
        Matrix4x3 const matrixFromNormal( Vector3D const & aNormal) 
        {
            SHOULD_BE(isValidDirection(aNormal));
            Vector3D const minComp = directionWithSmallestComponentOf(aNormal);
            Vector3D const vy = normalizedCrossProductOf(aNormal, minComp);
            Vector3D const vx = normalizedCrossProductOf(vy, aNormal);

            Matrix4x3 result = matrixFromCoordinateSystem(vx, vy, aNormal, Point3D::zero);

            if (isRightHanded(result))
                return result;

            result = matrixFromCoordinateSystem(vy, vx, aNormal, Point3D::zero);

            SHOULD_BE(isRightHanded(result));
            return result;
        }

        Matrix4x3 const matrixFromCoordinateSystem(Vector3D const & aX, Vector3D const & aY, Vector3D const & aZ, Point3D const & aOrg){
            Matrix4x3 result;
            result.mX = aX;
            result.mY = aY;
            result.mZ = aZ;
            result.mT = vectorTo(aOrg);
            return result;

        }

        bool const isLeftHanded(Matrix4x3 const& aMatrix){
            auto const x = xAxisOf(aMatrix);
            auto const y = yAxisOf(aMatrix);
            auto const z = zAxisOf(aMatrix);
            return tripleProductOf(x, y, z) < 0.0;
        }

        bool const isRightHanded(Matrix4x3 const& aMatrix){
            auto const x = xAxisOf(aMatrix);
            auto const y = yAxisOf(aMatrix);
            auto const z = zAxisOf(aMatrix);
            return tripleProductOf(x, y, z) > 0.0;

        }

        Vector3D const xAxisOf(Matrix4x3 const& aMatrix){
            return aMatrix.mX;
        }

        Vector3D const yAxisOf(Matrix4x3 const& aMatrix){
            return aMatrix.mY;
        }

        Vector3D const zAxisOf(Matrix4x3 const& aMatrix){
            return aMatrix.mZ;
        }

        Point3D const originOf(Matrix4x3 const& aMatrix){
            return pointAt(aMatrix.mT);
}
    }

}



   
    
