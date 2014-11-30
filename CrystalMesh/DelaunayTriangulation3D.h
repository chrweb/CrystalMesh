/*
 * Delaunay3.h
 *
 *  Created on: 26.06.2014
 *      Author: christoph
 */
#pragma once

#include "../Mathbox/Mathbox.h"
#include "Primitives.h"
#include <array>

namespace CrystalMesh{

	namespace Subdiv3{
		class Manifold;

	}





	namespace Delaunay3{

		struct VertexData{
			Mathbox::Geometry::Point3D  mPoint;
			void const * mpPropPtr;
		};

		class VertexDataContainer;

		class DelaunayTriangulation3D{

		public:

			DelaunayTriangulation3D();

			template<typename Iterator>
			DelaunayTriangulation3D( Iterator const & aPointsBegin, Iterator const & aPointsEnd);

			DelaunayTriangulation3D( DelaunayTriangulation3D const & aSrc);

			~DelaunayTriangulation3D();

			struct Flip1To4Result{

			};

			Flip1To4Result const flip1to4(Tet& aTetToFlip);

			struct Flip2To3Result{

			};

			Flip2To3Result flip2to3(Corner& aCornerToFlip);

			struct Flip3To2Result{

			};

			Flip3To2Result flip3to2(Triangle& aTriangleToFlip);

//			struct PointLocation{
//
//				enum struct Situation{
//					inTetraeder,
//					onFace,
//					onSegment,
//					onVertex
//				} mSituation;
//
//				union Location{
//					Tet mInTet;
//					Triangle  mOnFace;
//					Corner   mOnCorner;
//					Vertex	  mOnVertex;
//				} mLocation;
//			};
//
//
//			PointLocation const locatePoint(Mathbox::Geometry::Point3D const & aPoint);


			void insertPoint(Mathbox::Geometry::Point3D const & aPoint);

			typedef std::array<Mathbox::Geometry::Point3D,4 > TetPoints;

			// constructs a tet of the given 4 points
			Tet const makeTetrahedron(TetPoints const & aTetPoints);

			/**
			 * Creates the interior of execute a 1-4 Flip,
			 * Points [0-3]: tet bunds
			 * Point [4]: in-tet point
			 */
			TetInteriour const makeTetInterior( Mathbox::Geometry::Point3D const (aTetPoints)[5]);

			VertexData * makeVertexData(Mathbox::Geometry::Point3D const & aPoint, void * apPropPtr = nullptr);



		private:

			Subdiv3::Manifold * mpManifold;

			VertexDataContainer *mpToVetexData;
		};

	}
}

