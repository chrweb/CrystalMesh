/*
 * Geometry.h
 *
 *  Created on: 14.06.2014
 *      Author: christoph
 *
 *      Declaration of types and functionality, I want to use in CM. I know, there are a lot of math/ geom libs,
 *      but I guess it's better to provide a uniform declaration throughout this project, implementations may delegate to certain libs.
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_


namespace CrystalMesh{

	namespace Math{



		namespace Geometry{




			struct Vector3D{
				double mX, mY, mZ;

				static Vector3D  const NaN;

				static Vector3D const zero;

				static Vector3D const xAxis;

				static Vector3D const yAxis;

				static Vector3D const zAxis;
			};

			struct Point3D{
				double mX, mY, mZ;

				 static Point3D const NaN;

				 static Point3D const zero;
			};


			struct Vector2D{
				double mX, mY;

				static Vector2D const NaN;

				static Vector2D const zero;

				static Vector2D const xAxis;

				static Vector2D const yAxis;
			};

			struct Point2D{
				double mX, mY;

				static Point2D const NAN;

				static Point2D const zero;
			};


			struct LineSegment3D{
				Point3D mStartpoint;
				Point3D mEndpoint;
			};

			struct Line3D{
				Point3D mAnyPointOnLine;
				Point3D mDirection;
			};


			struct Plane3D{
				Point3D mPointOnPlane;
				Vector3D mOrtho;
			};

			struct OrientedPlane3D{
				Point3D mOrigin;
				Point3D mUdir;
				Point3D mVdir;
			};


			struct UvCoords{
				double mU;
				double mV;
			};

		}

	}

}

#include "Geometry Point3D.h"
//#include "Geometry Vector3D.h"



#endif /* GEOMETRY_H_ */
