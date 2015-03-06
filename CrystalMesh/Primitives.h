/*
 * Primitives.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once
#include "ForwardDecs.h"
#include "EdgeRing.h"
#include "FacetEdge.h"
#include "Vertex.h"
#include <array>
#include <vector>

namespace CrystalMesh{

	namespace Delaunay3{
            
                Mathbox::Geometry::Point3D const pointFromSubdiv3Vertex(Subdiv3::Vertex const *pVertex);
                
                Mathbox::Geometry::Point3D const originPointOf(Subdiv3::FacetEdge const * pFacetEdge);
                
                Mathbox::Geometry::Point3D const destinationPointOf(Subdiv3::FacetEdge const pFacetEdge);
                
                Mathbox::Geometry::Point3D const originPointOf(Subdiv3::DirectedEdgeRing const * pFacetEdge);
                
                Mathbox::Geometry::Point3D const destinationPointOf(Subdiv3::DirectedEdgeRing const * pFacetEdge);
                
                void setVertexPointTo(Mathbox::Geometry::Point3D const & aPoint, Subdiv3::Vertex * pVertex);
                

                //Describes an inner corner of a domain
                struct Corner{
                    Subdiv3::FacetEdge* mRef;   // a FacetEdge Reference
                    Subdiv3::FacetEdge* mFnext; // Fnext to above
                    
                    bool representsSegment(Mathbox::Geometry::Point3D const& p0, Mathbox::Geometry::Point3D const & p1) const;
		};

                
                //TODO: Remove
		struct FacetEdgeThreeTuple{
			Subdiv3::FacetEdge * f0, *f1, *f2;
		};

                
                //TODO: Remove
		FacetEdgeThreeTuple const facetEdgeThreeTupleOf(
				Subdiv3::FacetEdge const & a0,
				Subdiv3::FacetEdge const & a1,
				Subdiv3::FacetEdge const & a2);

                //TODO: Remove
		struct PointThreeTuple{
			Mathbox::Geometry::Point3D p0, p1, p2;
		};

                //TODO: Remove
		PointThreeTuple const pointTreeTupleOf(
				Mathbox::Geometry::Point3D const & a0,
				Mathbox::Geometry::Point3D const & a1,
				Mathbox::Geometry::Point3D const & a2);
                
                
                struct Tet;

		struct Triangle
		{
			typedef std::array<Subdiv3::FacetEdge*, 3> Boundary;
			typedef std::array<Mathbox::Geometry::Point3D, 3> BoundaryPoints;
                        typedef std::array<Subdiv3::Vertex*, 3> BoundaryVertices;
                        
			Boundary const getBoundaryArray() const;

			BoundaryPoints const getBoundaryPoints() const;
                        
                        BoundaryVertices const getBoundaryVertices() const;

			Mathbox::Geometry::OrientedPlane3D const getOrientedPlane() const;
                        
                        bool const operator == (const Triangle& other) const;
                        
                        bool const operator != (const Triangle& other) const;
                        
                        Tet const upperTet() const;
                        
                        Tet const lowerTet() const;

			Subdiv3::DirectedEdgeRing* mpDualEdgeRing;
                        
                        static Triangle const invalid;
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

			std::array<Subdiv3::EdgeRing*,6> mpOuterEdgeRing;
			Subdiv3::Vertex * mpVertex[5];

			struct Vertices{
                                //Boundary Vertices
				std::array<Subdiv3::Vertex *,4> mAtCorners;
                                //Inner Vertex
				Subdiv3::Vertex * mInTet;
			};

			Vertices const getVertices() const;
                        
                        Triangle const getTriangleAt(Index aIndex) const;
                        
                        Subdiv3::FacetEdge* getAdapterOf(Corner const & aCorner) const;
                        
                        Subdiv3::FacetEdge* getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const;
		};
                
                //ToDo: implement for flip 
                struct TetInteriourFan{
                    
                    std::array<Subdiv3::EdgeRing*, 6> mCornerEdgeRings;
                    
                    typedef std::array<Subdiv3::Vertex, 5> Vertices;
                    Vertices mVertices;
                    
                    Subdiv3::FacetEdge* getAdapterOf(Corner const & aCorner) const;
                    
                    Subdiv3::FacetEdge* getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const;
                    
                    Vertices const getVertices() const;
                };
                
                
                
		struct Tet{
                        typedef std::array<Triangle,4> Triangles;   
                        typedef std::array<Subdiv3::Vertex*, 4> Vertices;
                        typedef std::array<Corner, 6> Corners;
			
                        Subdiv3::Vertex* mpDualVertex;
			Triangles mTri;
                        
                        bool const operator == (Tet const & rhs) const;
                        
                        bool const operator != (Tet const & rhs) const;
                        
                        bool const isPartOf(Subdiv3::Vertex const *apVert) const;
			
			Triangle const getTriangleAt(Index aIndex) const;
                        
                        Tet const adjancentTetAt(Index aIndex) const;
                        
                        Triangle const commonBoundaryWith(Tet const & aOther) const;

			Vertices const getVertices() const;

			Triangles const getTriangles() const;
                        
                        Corners const getCorners() const;      
		};
                
                typedef std::vector<Subdiv3::Vertex*> IntersectingVertices;
                
                IntersectingVertices intersectionOf(const Tet& aTet0, const Tet& aTet1);
                
                typedef std::vector<Subdiv3::Vertex*> SymmetricDifferenceVertices;
                
                SymmetricDifferenceVertices symmetricDifferenceOf(const Tet& aTet0, const Tet& aTet1);
                
                
                struct Domain{
                    typedef std::vector<Corner> Corners;
                    
                    Subdiv3::Vertex* mpDual;
                    
                    bool const operator == (Tet const & rhs) const;
                        
                    bool const operator != (Tet const & rhs) const;
                    
                    Corners const getCorners() const;
                
                
                };





	}
}

