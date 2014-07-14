/*
 * Delaunay3.h
 *
 *  Created on: 26.06.2014
 *      Author: christoph
 */
#pragma once

#include "../Math/Geometry.h"
#include "Primitives.h"

namespace CrystalMesh{

	namespace Subdiv3{
		class Manifold;

	}

	struct VertexData{
		Math::Geometry::Point3D  mPoint;
	};

	class VertexDataContainer;

	namespace Delaunay3{

		class DelaunayTriangulation3D{

		public:

			DelaunayTriangulation3D();

			template<typename Iterator>
			DelaunayTriangulation3D( Iterator const & aPointsBegin, Iterator const & aPointsEnd);

			DelaunayTriangulation3D( DelaunayTriangulation3D const & aSrc);

			~DelaunayTriangulation();

			struct Flip1To4Result{

			};

			Flip1To4Result const flip1to4(Tetraeder& aTetToFlip);

			struct Flip2To3Result{

			};

			Flip2To3Result flip2to3(Corner& aCornerToFlip);

			struct Flip3To2Result{

			};

			Flip3To2Result flip3to2(Triangle& aTriangleToFlip);

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
					Corner   mOnCorner;
					Vertex	  mOnVertex;
				} mLocation;
			};


			PointLocation const locatePoint(Math::Geometry::Point3D const & aPoint);


			void insertPoint(Math::Geometry::Point3D const & aPoint);

			Triangle const makeTriangle();

			Tetraeder const makeTetrahedron();



		private:

			Subdiv3::Manifold * mpManifold;

			VertexDataContainer *mpToVetexData;
		};

	}
}

