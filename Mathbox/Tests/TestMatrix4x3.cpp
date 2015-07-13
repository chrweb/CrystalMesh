#include "../TestIncludes.h"
#include "Geometry_Matrix4x3.h"

using namespace Mathbox;
using namespace Geometry;

TEST(Matrix4x3, coordinateSystem){
    auto const x = Vector3D::xAxis;
    auto const y = Vector3D::yAxis;
    auto const z = Vector3D::zAxis;
    auto const orgPoint = pointFromXYZ(1.0, 1.0, 1.0);
    Matrix4x3 matrix = matrixFromCoordinateSystem(x, y, z, orgPoint);
    
    EXPECT_TRUE(exactEqual(x, xAxisOf(matrix)));
    EXPECT_TRUE(exactEqual(y, yAxisOf(matrix)));
    EXPECT_TRUE(exactEqual(z, zAxisOf(matrix)));
    EXPECT_TRUE(exactEqual(orgPoint, originOf(matrix)));
    EXPECT_TRUE(isRightHanded(matrix));
    
    Matrix4x3 leftHanded = matrixFromCoordinateSystem(x, -y, z, orgPoint);
    EXPECT_TRUE(isLeftHanded(leftHanded));
}

void testNormalMatrix(Matrix4x3 const& matrix){
    EXPECT_TRUE(isRightHanded(matrix));
    EXPECT_TRUE(almostEqual(1.0, absoluteOf(xAxisOf(matrix)), 10));
    EXPECT_TRUE(almostEqual(1.0, absoluteOf(yAxisOf(matrix)), 10));
    EXPECT_TRUE(almostEqual(1.0, absoluteOf(zAxisOf(matrix)), 10));


}

TEST(Matrix4x3, normal0){
    auto const matrix = matrixFromNormal(Vector3D::xAxis);
    testNormalMatrix(matrix);

}

TEST(Matrix4x3, normal1){
    auto const matrix = matrixFromNormal(-Vector3D::xAxis);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal2){

    auto const matrix = matrixFromNormal(Vector3D::yAxis);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal3){
    auto const matrix = matrixFromNormal(-Vector3D::yAxis);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal4){
    auto const matrix = matrixFromNormal(Vector3D::zAxis);
    testNormalMatrix(matrix);
}
TEST(Matrix4x3, normal5){
    auto const matrix = matrixFromNormal(-Vector3D::zAxis);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal6){
#ifdef DEBUG
    EXPECT_ANY_THROW(matrixFromNormal(Vector3D::zero));
#endif
}

TEST(Matrix4x3, normal7){
    Vector3D const normal = normalized(vectorFromXYZ(0.5, 0.5, 0.5));
    Matrix4x3 matrix = matrixFromNormal(normal);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal8){
    Vector3D const normal = normalized(vectorFromXYZ(0.5, 0.5, 0.2));
    Matrix4x3 matrix = matrixFromNormal(normal);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal9){
    Vector3D const normal = normalized(vectorFromXYZ(0.5, 0.5, -0.2));
    Matrix4x3 matrix = matrixFromNormal(normal);
    testNormalMatrix(matrix);
}

TEST(Matrix4x3, normal10){
    Vector3D const normal = normalized(vectorFromXYZ(0.5, 0.33333, -0.2));
    Matrix4x3 matrix = matrixFromNormal(normal);
    testNormalMatrix(matrix);
}

