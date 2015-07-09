/* 
 * File:   Corner.h
 * Author: christoph
 *
 * Created on 11. April 2015, 21:46
 */

#ifndef CORNER_H
#define	CORNER_H
#include "ComplexTypes.h"
#include "DelaunayForwardDecs.h"
#include "Triangle.h"
#include "Domain.h"
namespace CrystalMesh{

    namespace Delaunay3{
    
    
        //Describes an inner corner of a domain
        struct Corner{
            Subdiv3::FacetEdge* mRef;   // a FacetEdge Reference
            Subdiv3::FacetEdge* mFnext; // Fnext to above
            
            /**
             * True, if Corner holds p0 and p1 in arbitary order (origin, destination) or (destination, origin)
             * @param p0
             * @param p1
             * @return 
             */
            bool representsSegment(Mathbox::Geometry::Point3D const& p0, Mathbox::Geometry::Point3D const & p1) const;
            
            Delaunay3::Triangle const adjancentTriangle() const;
            
            Mathbox::Geometry::Point3D const getOriginPoint() const;
            
            Mathbox::Geometry::Point3D const getDestinationPoint() const;
            
            static Corner const invalid;
	};
       
        
        /**
         * Constructs a corner
         * @param aDring: The Edge Ring representation
         * @param aDomainAbove the Domain appearing above mRef of result Corner
         * @return  a Corner
         */
        Corner const cornerFrom(Subdiv3::EdgeRing* aDring, Delaunay3::Domain const& aDomainAbove);
    }
}

#endif	/* CORNER_H */

