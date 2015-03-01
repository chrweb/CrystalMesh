/*
 * Delaunay3.h
 *
 *  Created on: 26.06.2014
 *      Author: christoph
 */
#pragma once

#include "../Mathbox/Mathbox.h"
#include "Primitives.h"
#include "Vertex.h"
#include "DirectedEdgeRing.h"
#include <array>

namespace CrystalMesh{

	namespace Subdiv3{
		class Manifold;

	}


	namespace Delaunay3{
            
                struct Flip1To4{
                    enum struct Result{
                        success,
                        failure
                    };

                    typedef std::array<Triangle,10> Triangles;
                    
                    Result result;
                    Triangles tris;
                };
                
                struct Flip2To3{

		};

                struct PointInsertion{
                    Mathbox::Geometry::Point3D mPoint;
                };
                
                PointInsertion pointInsertionOf(Mathbox::Geometry::Point3D const & aPoint);

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

			Flip1To4 const flip1to4(Tet& aTetToFlip, PointInsertion const aIns);

			Flip2To3 flip2to3(Triangle& aTriangleToFlip);

		

			//Flip3To2Result flip3to2();

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

                        typedef std::array<Mathbox::Geometry::Point3D, 5> TetIntPoints;
			/**
			 * Creates the interior of execute a 1-4 Flip,
			 * Points [0-3]: tet bunds
			 * Point [4]: in-tet point
			 */
			TetInteriour const makeTetInterior( TetIntPoints const & aTetIntPoints);
                        
                        typedef std::array<Mathbox::Geometry::Point3D, 3>  FanPoints;
                        typedef std::array<Mathbox::Geometry::Point3D, 2>  TopBottomPoints;
                        Fan const makeFan3(TopBottomPoints const & aTbPoints, FanPoints const& aFanPoints);

			VertexData * makeVertexData(Mathbox::Geometry::Point3D const & aPoint, void * apPropPtr = nullptr);



		private:
                    
                    void unifyVertices(Subdiv3::Vertex * apVert0, Subdiv3::Vertex * apVert1);
                    
                    void unifyEdgeRings(Subdiv3::EdgeRing* apRing0 ,Subdiv3::EdgeRing* apRing1);
                    
                    void destroyTet(Tet & aTet);
                    
                    void separateTriangle(Triangle & aTri);
                    
                    //void dislinkTriangle(Triangle & aTri);
                    
                    void destroyTriangle(Triangle & aTri);
                    
                    Subdiv3::Vertex * makeBody();
                    
                    Subdiv3::Manifold * mpManifold;

                    VertexDataContainer *mpToVetexData;
		};

	}
}

