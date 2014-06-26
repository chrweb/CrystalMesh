/*
 * Delaunay3.h
 *
 *  Created on: 26.06.2014
 *      Author: christoph
 */
#pragma once

#include "../Math/CrystalMesh Math.h"

namespace CrastalMesh{

	namespace Delaunay3{

		class Tetraeder;



		class DelaunayTriangulation3D{

		public:

			DelaunayTriangulation3D();

			template<typename Iterator>
			DelaunayTriangulation3D( Iterator const & aPointsBegin, Iterator const & aPointsEnd);

			DelaunayTriangulation3D( DelaunayTriangulation3D const & aSrc);

			void flip1to4();

			void flip2to3();

			void flip3to2();


			Tetraeder const locatePoint()


			void insertPoint();

		private:

		};

	}
}

