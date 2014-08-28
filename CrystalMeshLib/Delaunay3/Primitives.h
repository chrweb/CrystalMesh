/*
 * Primitives.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once
#include "ForwardDecs.h"

namespace CrystalMesh{

	namespace Delaunay3{

		struct Vertex{
			Subdiv3::Vertex* mpPrimalVertex;

			Math::Geometry::Point3D const getPoint() const;

			void setPoint(Math::Geometry::Point3D const & aPoint);
		};



		struct Corner{

		};

		struct FacetEdgeThreeTuple{
			Subdiv3::FacetEdge * f0, *f1, *f2;
		};

		FacetEdgeThreeTuple const facetEdgeThreeTupleOf(
				Subdiv3::FacetEdge const & a0,
				Subdiv3::FacetEdge const & a1,
				Subdiv3::FacetEdge const & a2);

		struct PointThreeTuple{
			Math::Geometry::Point3D p0, p1, p2;
		};

		PointThreeTuple const pointTreeTupleOf(
				Math::Geometry::Point3D const & a0,
				Math::Geometry::Point3D const & a1,
				Math::Geometry::Point3D const & a2);


		struct Triangle
		{
			FacetEdgeThreeTuple const getBoundary() const;

			PointThreeTuple const getPoints() const;

			Subdiv3::DirectedEdgeRing* mpDualEdgeRing;
		};

		Triangle const getCounterOrientedOf(Triangle const aTri);


		struct Fan{

			Subdiv3::DirectedEdgeRing * mpCorner;

			FacetEdgeThreeTuple const getBlossomAdapter() const;
		};


		struct Blossom{

			FacetEdgeThreeTuple mTuple;

			FacetEdgeThreeTuple const getFanAdapter() const;
		};


		struct TetInteriour{

			Subdiv3::EdgeRing * mpOuterEdgeRing[6];
			Subdiv3::Vertex * mpVertex[5];

			FacetEdgeThreeTuple const getTetAdapterOf(
					Math::Geometry::Point3D const &a0,
					Math::Geometry::Point3D const &a1,
					Math::Geometry::Point3D const &a2) const;

			struct Vertices{

				Subdiv3::Vertex * mAtCorners[4];
				Subdiv3::Vertex * mInTet;
			};

			Vertices const getVertices();

		};

		struct Tet{

			Subdiv3::Vertex* mpDualVertex;
			Triangle tri[4];

			struct Vertices{
				Subdiv3::Vertex * mpVert[4];
			};

			struct Trinangles{
				Triangle mTri[4];
			};

			Triangle const getTriangleAt(Index aIndex);

			Vertex const getVertexAt(Index aIndex);

			Vertices const getVertices() const;

			Trinangles const getTriangles() const;
		};





	}
}

