/*
 * Primitives.h
 *
 *  Created on: 29.06.2014
 *      Author: christoph
 */
#pragma once
#include "DelaunayForwardDecs.h"
#include "EdgeRing.h"
#include "FacetEdge.h"
#include "Vertex.h"
#include <array>
#include <vector>

namespace CrystalMesh{

	namespace Delaunay3{
            
                



                
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
                    typedef std::array<Subdiv3::Vertex*, 5> Vertices;
                    typedef std::array<Triangle, 3> Triangles;
                    
                    Triangles mTriangles;
                    
                    Vertices mVertices;
                    
                    Subdiv3::FacetEdge* getAdapterOf(Corner const & aCorner) const;
                    
                    Subdiv3::FacetEdge* getAdapterOf(Mathbox::Geometry::Point3D const &  org, Mathbox::Geometry::Point3D const & dest) const;
                    
                    Vertices const getVertices() const;
                    
                    Triangles const getTriangles() const;
                };
                
                
                
		struct Tet{
                        typedef std::array<Triangle,4> Triangles;   
                        typedef std::array<Subdiv3::Vertex*, 4> Vertices;
                        typedef std::array<Corner, 6> Corners;
			
                        Subdiv3::Vertex* mpDualVertex;
			Triangles mTri;
                        
                        bool const operator == (Tet const & rhs) const;
                        
                        bool const operator != (Tet const & rhs) const;
                        
                        /**
                         * True, if Vertex is part of this Tet
                         * @param apVert
                         * @return 
                         */
                        bool const isPartOf(Subdiv3::Vertex const *apVert) const;
			
			Triangle const getTriangleAt(Index aIndex) const;
                        
                        Tet const adjancentTetAt(Index aIndex) const;
                        
                        Triangle const commonBoundaryWith(Tet const & aOther) const;

			Vertices const getVertices() const;

			Triangles const getTriangles() const;
                        
                        Corners const getCorners() const;      
		};
                
                Tet const tetOf(Subdiv3::Vertex* pVertex, Tet::Triangles tris);
                
                typedef std::vector<Subdiv3::Vertex*> IntersectingVertices;
                
                /**
                 * Returns a set of intersecting vertices of th two given tets. This is,
                 * their shared Vertices
                 * @param aTet0
                 * @param aTet1
                 * @return 
                 */
                IntersectingVertices intersectionInVerticesOf(const Tet& aTet0, const Tet& aTet1);
                
                typedef std::vector<Subdiv3::Vertex*> SymmetricDifferenceVertices;
                
                /**
                 * Returns all non non shared Vertives of the two given tets
                 * @param aTet0
                 * @param aTet1
                 * @return 
                 */
                SymmetricDifferenceVertices symmetricDifferenceInVerticesOf(const Tet& aTet0, const Tet& aTet1);
                
                typedef std::vector<Triangle> IntersectionTriangles;
                
                IntersectionTriangles intersectionInTrianglesOf(Tet const & aTet0, Tet const & aTet1);
                
                typedef std::vector<Triangle> SymmetricDiffenrenceTriangles;
                
                SymmetricDiffenrenceTriangles symmetricDifferenceInTriangles(Tet const & aTet0, Tet const & aTet1);
                
                /*A general domain with triangles as boundary faces*/
                struct Domain{
                    typedef std::vector<Corner> Corners;
                    typedef std::vector<Subdiv3::Vertex*> Vertices;
                    typedef std::vector<Triangle> Triangles;
                    Subdiv3::Vertex* mpDual;
                    
                    bool const operator == (Domain const & rhs) const;
                        
                    bool const operator != (Domain const & rhs) const;
                    
                    Corners const getCorners() const;
                
                    Vertices const getVertices() const;
                    
                    Triangles const getTriangles() const;
                };
                
                Domain const domainOf(Subdiv3::Vertex*  apVertex);





	}
}

