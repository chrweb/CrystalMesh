/*
 * Geometry Point3D.h
 *
 *  Created on: 20.06.2014
 *      Author: christoph
 */
#pragma once


namespace CrystalMesh{

	namespace Geometry{

		struct Point3D;
		struct Vector3D;

		Point3D const operator + (Point3D const & aPoint, Vector3D const & aVec);

		Point3D const operator - (Point3D const & aPoint, Vector3D const & aVec);

		Point3D const point3DFromXYZ( double aX, double aY, double aZ);

		Point3D const pointAt(Vector3D const & aVec);


	}
}
