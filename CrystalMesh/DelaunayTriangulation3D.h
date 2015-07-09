/*
 * Delaunay3.h
 *
 *  Created on: 26.06.2014
 *      Author: christoph
 */
#pragma once

#include <array>
#include "../Mathbox/Mathbox.h"
#include "ComplexTypes.h"
#include "DelaunayForwardDecs.h"
#include "DelaunayVertex.h"
#include "Triangle.h"
#include "Corner.h"
#include "Tet.h"
#include "Fan.h"
#include "Domain.h"
#include "Crater.h"
#include "TetInteriour.h"

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
                enum struct Result{
                    success,
                    failure
                };
                
                typedef std::array<Triangle, 9> Triangles;
                
                Result result;
                Triangles tris;
	};

            struct PointInsertion{
                Mathbox::Geometry::Point3D mPoint;
            };
            
            PointInsertion pointInsertionOf(Mathbox::Geometry::Point3D const & aPoint);

	

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

            void insertPoint(Mathbox::Geometry::Point3D const & aPoint);

            typedef std::array<Mathbox::Geometry::Point3D,4 > TetPoints;

            // constructs a tet of the given 4 points
            Tet const makeTet(TetPoints const & aTetPoints);

            typedef std::array<Mathbox::Geometry::Point3D, 5> TetIntPoints;
            /**
             * Creates the interior of a Tet,
             * Points [0-3]: tet bounds
             * Point [4]: in-tet point
             */
            TetInteriour const makeTetInterior( TetIntPoints const & aTetIntPoints);
            
            typedef std::vector<Mathbox::Geometry::Point3D>  FanPoints;
            
            Fan const makeFan
                (Mathbox::Geometry::Point3D const & aTopPoint
                ,Mathbox::Geometry::Point3D const & aBotPoint
                ,FanPoints const& aFanPoints);

            VertexData * makeVertexData(Mathbox::Geometry::Point3D const & aPoint, void const * apPropPtr = nullptr);
            
            void deleteVertexData(VertexData* pData);
            
            Subdiv3::Vertex* makeVertexWith(VertexData const & aData);
            
            
            Triangle const makeTriangle(
                Mathbox::Geometry::Point3D const& aP0, 
                Mathbox::Geometry::Point3D const& aP1,
                Mathbox::Geometry::Point3D const& aP2);
            
            Triangle const makeTriangle(
                VertexData const& aData0, 
                VertexData const& aData1, 
                VertexData const& aData2);
            
            typedef std::vector<Mathbox::Geometry::Point3D> CraterPoints;
            Crater makeCrater(Mathbox::Geometry::Point3D const & aMidPoint, CraterPoints const& aCraterPoints );

            
            void addCorners(Exporter & aExporter) const;
            
            void addTriangles(Exporter & aExporter) const;
            
            void addVertices(Exporter & aExporter) const;
            
            size_t getDomainCount() const;
            
            size_t getFaceCount() const;
            
            size_t getCornerCount() const;
            
            size_t getVertexCount() const;
            
            private:
                
            typedef std::vector<Subdiv3::VertexPtr> VertexUnifyList;
            Subdiv3::VertexPtr unifyVertices(VertexUnifyList & aList);
            
            Subdiv3::VertexPtr unifyDomains(VertexUnifyList & aList);
            
            typedef std::vector<Subdiv3::EdgeRingPtr> EdgeRingUnifyList;
            
            Subdiv3::EdgeRingPtr unifyEdgeRings(EdgeRingUnifyList& aList);
            
            //void unifyVertices(Subdiv3::Vertex * apVert0, Subdiv3::Vertex * apVert1);
            
            //void unifyEdgeRings(Subdiv3::EdgeRing* apRing0 ,Subdiv3::EdgeRing* apRing1);
            
            //void unifyEdgeRingsF(RingMembers const& aFnextRing);
            
            //void destroyTet(Tet & aTet);
            
           
            Domain const makeDomain();
            
            void linkDomainUnderTriangle(Delaunay3::Domain& aDomain,  Delaunay3::Triangle& aTri);
            
            void linkDomainOverTriangle(Delaunay3::Domain& aDomain,  Delaunay3::Triangle& aTri);
            
            //void destroyDomain(Domain & aVert);
                   
            //Subdiv3::Vertex * makeBody();
            
            Subdiv3::Manifold * mpManifold;

            VertexDataContainer *mpToVetexData;
	};

	}
}



