/*
 * Primitives.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once
#include "ForwardDecs.h"
#include <array>

namespace CrystalMesh{

	namespace Delaunay3{

		struct Vertex{
			Subdiv3::Vertex* mpPrimalVertex;

			Mathbox::Geometry::Point3D const getPoint() const;

			void setPoint(Mathbox::Geometry::Point3D const & aPoint);
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
			Mathbox::Geometry::Point3D p0, p1, p2;
		};

		PointThreeTuple const pointTreeTupleOf(
				Mathbox::Geometry::Point3D const & a0,
				Mathbox::Geometry::Point3D const & a1,
				Mathbox::Geometry::Point3D const & a2);


		struct Triangle
		{
			typedef std::array<Subdiv3::FacetEdge*, 3> Boundary;
			typedef std::array<Mathbox::Geometry::Point3D, 3> BoundaryPoints;

			Boundary const getBoundaryArray() const;

			BoundaryPoints const getBoundaryPoints() const;

			FacetEdgeThreeTuple const getBoundary() const;

			PointThreeTuple const getPoints() const;

			Mathbox::Geometry::OrientedPlane3D const getOrientedPlane() const;

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
					Mathbox::Geometry::Point3D const &a0,
					Mathbox::Geometry::Point3D const &a1,
					Mathbox::Geometry::Point3D const &a2) const;

			struct Vertices{
                                //Boundary Vertices
				Subdiv3::Vertex * mAtCorners[4];
                                //Inner Vertex
				Subdiv3::Vertex * mInTet;
			};

			Vertices const getVertices();

		};

		struct Tet{
                        typedef std::array<Triangle,4> Triangles;   
                        typedef std::array<Subdiv3::Vertex*, 4> Vertices;
			
                        Subdiv3::Vertex* mpDualVertex;
			Triangles mTri;

			
			Triangle const getTriangleAt(Index aIndex) const ;

			//Subdiv3::Vertex const  * getVertexAt(Index aIndex) const;

			Vertices const getVertices() const;

			

			Triangles const getTriangles() const;
		};





	}
}

