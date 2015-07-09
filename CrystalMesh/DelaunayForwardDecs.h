/*
 * ForwardDecs.h
 *
 *  Created on: 26.07.2014
 *      Author: christoph
 */
#pragma once
#include <stdint.h>

/**
 * Forward-declared types, often used in Delaunay3: 
 */

namespace Mathbox{
    namespace Geometry {
        struct Point3D;
    }  // namespace Geometry
}

namespace CrystalMesh {

	namespace Subdiv3{

		class Manifold;

		struct FacetEdge;

		struct DirectedEdgeRing;

		struct EdgeRing;

		struct Vertex;
                
                struct Tet;
               
	}

	namespace Delaunay3{

            typedef uint32_t Index;
            
            class Exporter{
                
            public:
                virtual Index addVertex(Mathbox::Geometry::Point3D const & aPoint3D) = 0;
                virtual void addTriangle(Index id0, Index id1, Index id2) = 0;  
                virtual void addCorner(Index id0, Index id1) = 0;
            };
            
            class DelaunayTriangulation3D;
            
            struct Domain;
                
	}

}  // namespace CrystalMesh



