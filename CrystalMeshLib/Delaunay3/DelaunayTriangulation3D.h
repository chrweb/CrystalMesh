/*
 * Delaunay3.h
 *
 *  Created on: 26.06.2014
 *      Author: christoph
 */
#pragma once

#include "../Math/Geometry.h"

namespace CrastalMesh{

	namespace Subdiv3{
		class Manifold;


	}

	namespace Delaunay3{

		class Triangle;
		class DirectedSegment{
		};
		class Segment;
		class Vertex{};


		class Tetraeder{
			Vertex[4] mVerts;
		};





		class DelaunayTriangulation3D{

		public:

			DelaunayTriangulation3D();

			template<typename Iterator>
			DelaunayTriangulation3D( Iterator const & aPointsBegin, Iterator const & aPointsEnd);

			DelaunayTriangulation3D( DelaunayTriangulation3D const & aSrc);

			void flip1to4();

			void flip2to3();

			void flip3to2();

			struct PointLocation{

				enum struct Situation{
					inTetraeder,
					onFace,
					onSegment,
					onVertex
				} mSituation;

				union Location{
					Tetraeder mInTet;
					Triangle  mOnFace;
					Segment   mOnSegment;
					Vertex	  mOnVertex;
				} mLocation;
			};


			PointLocation const locatePoint(Math::Geometry::Point3D const & aPoint);


			void insertPoint(Math::Geometry::Point3D const & aPoint);

		private:

			Subdiv3::Manifold * mpManifold;
		};

	}
}

