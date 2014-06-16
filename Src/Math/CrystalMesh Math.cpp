/*
 * CrystalMesh Math.cpp
 *
 *  Created on: 16.06.2014
 *      Author: christoph
 */

#include "CrystalMesh Math.h"
#include "Geometry.h"
#include <math.h>

namespace CrystalMesh{

	namespace Math{


		 double const NaN =  NAN;
		 double const PositivInf = INFINITY;
		 double const NegativInf = -INFINITY;

		 /*
		  * Define NaNs of Geometrical Objets
		  */
		 namespace Geometry{


		 	 Point3D const Point3D::NaN = {NAN, NAN, NAN};

		 }
	}



}





