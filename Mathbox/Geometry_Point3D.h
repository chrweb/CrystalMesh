/*
 * Geometry Point3D.h
 *
 *  Created on: 20.06.2014
 *      Author: christoph
 */
#pragma once


namespace Mathbox{

	namespace Geometry{

			struct Point3D;
			struct Vector3D;

			Point3D const operator + (Point3D const & aPoint, Vector3D const & aVec);

			Point3D const operator - (Point3D const & aPoint, Vector3D const & aVec);

			/**
			 * all components bitwise identical
			*/
			bool const exactEqual(Point3D const & a0, Point3D const & a1);

			/**
			* distance may differ by distance aDeltaD
			*/
			bool const almostEqual(Point3D const & a0, Point3D const & a1, double const aDeltaD);


			Point3D const pointFromXYZ(double aX, double aY, double aZ);

			Point3D const pointFromXY0(double aX, double aY);

			Point3D const pointAt(Vector3D const & aVec);

			double const distanceBetween(Point3D const & a0, Point3D const & a1);

			double const squaredDistanceBetween(Point3D const & a0, Point3D const & a1);
	}
}
