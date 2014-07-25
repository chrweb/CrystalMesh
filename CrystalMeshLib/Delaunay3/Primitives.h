/*
 * Primitives.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once

namespace CrystalMesh{

	namespace Subdiv3{

		struct DirectedEdgeRing;

		struct Vertex;


	}

	namespace Delaunay3{

		struct Vertex{
			Subdiv3::Vertex* mpPrimalVertex;

			Math::Geometry::Point3D const getPoint() const;

			void setPoint(Math::Geometry::Point3D const & aPoint);
		};

		struct Corner{

		};

		struct FacetEdgeThreeTuple{
			Subdiv3::FacetEdge * mTuple[3];
		};

		struct PointThreeTuple{
			Math::Geometry::Point3D mTuple[3];
		};

		struct Fan{

			Triangle mTri[3];
			Corner mCorner;

			FacetEdgeThreeTuple const getBlossomAdapter() const;
		};

		struct Triangle
		{
			Triangle const getCounterOriented() const;

			FacetEdgeThreeTuple const getBoundary() const;

			PointThreeTuple const getPoints() const;

			Subdiv3::DirectedEdgeRing* mpDualEdgeRing;
		};



		struct Tetraeder{
			Triangle mBounds[4];
			Vertex mVerts[4];
		};

	}
}

