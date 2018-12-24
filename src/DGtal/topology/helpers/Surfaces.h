/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file Surfaces.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/03/19
 *
 * Header file for module Surfaces
 *
 * This file is part of the DGtal library.
 */

#if defined(Surfaces_RECURSES)
#error Recursive header files inclusion detected in Surfaces.h
#else // defined(Surfaces_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Surfaces_RECURSES

#if !defined Surfaces_h
/** Prevents repeated inclusion of headers. */
#define Surfaces_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"

//////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable : 4290)
#endif

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Surfaces
  /**
     Description of template class 'Surfaces' <p> \brief Aim: A
     utility class for constructing surfaces (i.e. set of
     (n-1)-cells).
     
     @tparam TKSpace the type of cellular grid space (e.g. a
     KhalimskySpaceND).

     Note that many methods requires a surfel adjacency so as to know
     how connected surfels are linked (first by the interior or first
     by the exterior). Secondly, many methods are parameterized by a
     PointPredicate which describes the shape as a characteristic
     function. This is to be more generic than a simple
     DigitalSet. With this approach, shapes can be defined implicitly.

     Essentially a backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   */
  template <typename TKSpace>
  class Surfaces
  {
    // ----------------------- Types ------------------------------
  public:
    typedef TKSpace                      KSpace;
    typedef typename KSpace::Integer     Integer;
    typedef typename KSpace::Point       Point;
    typedef typename KSpace::Vector      Vector;
    typedef typename KSpace::Cell        Cell;
    typedef typename KSpace::SCell       SCell;
    typedef typename KSpace::Surfel      Surfel;
    typedef typename KSpace::DirIterator DirIterator;
    typedef std::vector<Cell>            CellRange;
    
    // ----------------------- Static services ------------------------------
  public:

    /**
       Find a bel in some digital set by random tries then dichotomy.

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.

       @param K any cellular grid space.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param nbtries the maximum number of random tries (default 1000).

       @return a signed surfel separating a digital point in [dset]
       from a face adjacent digital point outside [dset] or throws an
       InputException if none was found after [nbtries] iterations.
    */
    template <typename PointPredicate>
    static
    SCell findABel( const KSpace & K,
        const PointPredicate & pp,
        unsigned int nbtries = 1000 );

    /**
       Find a bel in some digital set given two hints (one point
       inside, one point outside).

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.

       @pre we must have pp( x1 ) != pp( x2 ), i.e. one point should
       satisfy the predicate while the other not.

       @param K any cellular grid space.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param x1 a point within the bounds of K and such that pp( x1 )
       != pp( x2 ).

       @param x2 a point within the bounds of K and such that pp( x1 )
       != pp( x2 ).

       @return a signed surfel separating a digital point in [dset]
       from a face adjacent digital point outside [dset].
    */
    template <typename PointPredicate>
    static
    SCell findABel( const KSpace & K,
                    const PointPredicate & pp,
                    Point x1, Point x2 );

    /**
       Function that extracts the boundary of a nD digital shape
       (specified by a predicate on point), closed or open, in a nD
       KSpace. The boundary is returned as a set of surfels.

       Creates a set of signed surfels whose elements represents a
       boundary component of a digital shape described by a
       PointPredicate. The algorithms tracks surfels along the
       boundary of the shape.
       
       @tparam SCellSet a model of a set of SCell (e.g., std::set<SCell>).

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param surface (modified) a set of cells (which are all surfels),
       the boundary component of [spelset] which touches [start_surfel].
       
       @param K any space.
       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param start_surfel a signed surfel which should be between an
       element of [shape] and an element not in [shape].
    */
    template <typename SCellSet, typename PointPredicate >
    static 
    void trackBoundary( SCellSet & surface,
      const KSpace & K,
      const SurfelAdjacency<KSpace::dimension> & surfel_adj,
      const PointPredicate & pp,
      const SCell & start_surfel );

    /**
       Function that extracts the \b closed boundary of a nD digital
       shape (specified by a predicate on point), in a nD KSpace. The
       boundary is returned as a set of surfels.

       Creates a set of signed surfels whose elements represents a
       boundary component of a digital shape described by a
       PointPredicate. The algorithms tracks surfels along the
       boundary of the shape. It follows only direct orientations, so
       that it is faster than trackBoundary but requires the object to
       be fully inside the space. Follows the idea of Artzy, Frieder
       and Herman algorithm [Artzy:1981-cgip], but in nD.
       
       @tparam SCellSet a model of a set of SCell (e.g., std::set<SCell>).

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param surface (modified) a set of cells (which are all surfels),
       the boundary component of [spelset] which touches [start_surfel].
       
       @param K any space.
       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param start_surfel a signed surfel which should be between an
       element of [shape] and an element not in [shape].
    */
    template <typename SCellSet, typename PointPredicate >
    static 
    void trackClosedBoundary( SCellSet & surface,
            const KSpace & K,
            const SurfelAdjacency<KSpace::dimension> & surfel_adj,
            const PointPredicate & pp,
            const SCell & start_surfel );


    /**
       Function that extracts a n-1 digital surface (specified by a
       predicate on surfel), closed or open, in a nD KSpace. The
       surface is returned as a set of surfels.

       Creates a set of signed surfels whose elements represents a
       boundary component of a digital surface described by a
       SurfelPredicate. The algorithms tracks surfels along the surface.
       
       @tparam SCellSet a model of a set of SCell (e.g., std::set<SCell>).

       @tparam SurfelPredicate a model of CSurfelPredicate describing
       whether a surfel belongs or not to the surface.
       
       @param surface (modified) a set of cells (which are all surfels),
       the boundary component of [spelset] which touches [start_surfel].
       
       @param K any space.
       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of CSurfelPredicate.

       @param start_surfel a signed surfel which should be part of the
       surface, ie. 'sp(start_surfel)==true'.
    */
    template <typename SCellSet, typename SurfelPredicate >
    static 
    void trackSurface( SCellSet & surface,
                       const KSpace & K,
                       const SurfelAdjacency<KSpace::dimension> & surfel_adj,
                       const SurfelPredicate & pp,
                       const SCell & start_surfel );

    /**
       Function that extracts a \b closed n-1 digital surface
       (specified by a predicate on surfel) in a nD KSpace. The
       surface is returned as a set of surfels.

       Creates a set of signed surfels whose elements represents a
       boundary component of a digital surface described by a
       SurfelPredicate. The algorithms tracks surfels along the
       surface. This is an optimized version of trackSurface, which is
       valid only when the tracked surface is closed.
       
       @tparam SCellSet a model of a set of SCell (e.g., std::set<SCell>).

       @tparam SurfelPredicate a model of CSurfelPredicate describing
       whether a surfel belongs or not to the surface.
       
       @param surface (modified) a set of cells (which are all surfels),
       the boundary component of [spelset] which touches [start_surfel].
       
       @param K any space.
       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of CSurfelPredicate.

       @param start_surfel a signed surfel which should be part of the
       surface, ie. 'sp(start_surfel)==true'.
    */
    template <typename SCellSet, typename SurfelPredicate >
    static 
    void trackClosedSurface( SCellSet & surface,
                             const KSpace & K,
                             const SurfelAdjacency<KSpace::dimension> & surfel_adj,
                             const SurfelPredicate & pp,
                             const SCell & start_surfel );


    /**
       Function that extracts the boundary of a 2D shape (specified by
       a predicate on point) in a 2D KSpace. The boundary is returned
       as a vector of surfels. The surfels are guaranteed to be in the
       direct orientation ordering.

       Creates a vector of signed surfels whose elements represents a
       2D boundary component of a digital shape described by a
       PointPredicate. The algorithm tracks surfels along the boundary
       of the shape by starting from the given [start_surfel]. It only
       tracks the boundary of a 2D shape.
       
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param aSCellContour2D (modified) a vector of cells (which are
       all surfels), containing the ordered list of the boundary
       component of [spelset] which touches [start_surfel].
       
       @param K any space of dimension 2.

       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param start_surfel a signed surfel which should be between an
       element of [shape] and an element not in [shape].
    */
    template <typename PointPredicate >
    static 
    void track2DBoundary( std::vector<SCell> & aSCellContour2D,
        const KSpace & K,
        const SurfelAdjacency<KSpace::dimension> & surfel_adj,
        const PointPredicate & pp,
        const SCell & start_surfel );



    /**
       Function that extracts a 2D slice of the boundary of a nD shape
       (specified by a predicate on point) in a nD KSpace. The
       boundary is returned as a vector of surfels. The surfels are
       guaranteed to be in the direct orientation ordering.

       Creates a vector of signed surfels whose elements represents a
       2D boundary component of a digital shape described by a
       PointPredicate. The algorithms tracks surfels along the
       boundary of the shape by starting from the given
       [start_surfel], along the direction specified by [trackDir]. More
       precisely, it is the boundary of the slice of the shape along
       directions [trackDir] and the orthogonal direction of
       [start_surfel].
       
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param aSCellContour2D (modified) a vector of cells (which are
       all surfels), containing the ordered list of the boundary
       component of [spelset] which touches [start_surfel].
       
       @param K any space (dimension is arbitrary).

       @param trackDir the initial track direction at [start_surfel],
       should be different from the orthogonal direction of
       [start_surfel].

       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param start_surfel a signed surfel which should be between an
       element of [shape] and an element not in [shape].
    */
    template <typename PointPredicate>
    static 
    void track2DSliceBoundary( std::vector<SCell> & aSCellContour2D,
			       const KSpace & K, 
			       const Dimension & trackDir,
			       const SurfelAdjacency<KSpace::dimension> & surfel_adj,
			       const PointPredicate & pp,
			       const SCell & start_surfel );


    /**
       Function that extracts a 1d-contour (specified by a predicate
       on surfel) in a 2D KSpace. The boundary is returned as a vector
       of surfels. The surfels are guaranteed to be in the direct
       orientation ordering.

       Creates a vector of signed surfels whose elements represents a
       component of a digital surface described by a
       SurfelPredicate. The algorithm tracks surfels along the surface
       by starting from the given \a start_surfel. All surfels are
       returned so as to follow the direct orientation. If the surface
       is open, the first surfel is at one extremity (the indirect
       extremity) while the last surfel is at the other
       extremity. Otherwise, the first surfel is \a start_surfel.
       
       @tparam SurfelPredicate a model of CSurfelPredicate, meaning a
       functor taking a Surfel (SCell) and returning 'true' whenever
       the surfel belongs to the digital surface. Models include
       FrontierPredicate and BoundaryPredicate.
       
       @param aSCellContour (modified) a vector of cells (which are
       all surfels), containing the ordered list of surfels that forms
       the connected component containing surfel [start_surfel].
       
       @param K any space of dimension 2.

       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param sp an instance of a model of CSurfelPredicate, for
       instance a FrontierPredicate or a BoundaryPredicate.

       @param start_surfel a signed surfel such that sp(start_surfel) is true.
    */
    template <typename SurfelPredicate >
    static 
    void track2DSurface( std::vector<SCell> & aSCellContour,
			 const KSpace & K,
			 const SurfelAdjacency<KSpace::dimension> & surfel_adj,
			 const SurfelPredicate & sp,
			 const SCell & start_surfel );



    /**
       Function that extracts a 2D slice of a n-1 digital surface
       (specified by a predicate on surfel) in a nD KSpace. The
       boundary is returned as a vector of surfels. The surfels (of
       dimension n-1) are guaranteed to be in the direct orientation
       ordering.

       Creates a vector of signed surfels whose elements represents a
       component of a slice of digital surface described by a
       SurfelPredicate. The algorithm tracks surfels along the surface
       by starting from the given \a start_surfel and by moving along
       the directions \a trackDir and the orthogonal direction to \a
       start_surfel. All surfels are returned so as to follow the
       direct orientation. If the surface is open, the first surfel is
       at one extremity (the indirect extremity) while the last surfel
       is at the other extremity. Otherwise, the first surfel is \a
       start_surfel.

       @tparam SurfelPredicate a model of CSurfelPredicate, meaning a
       functor taking a Surfel (SCell) and returning 'true' whenever
       the surfel belongs to the digital surface.  Models include
       FrontierPredicate and BoundaryPredicate.
       
       @param aSCellContour (modified) a vector of cells (which are
       all surfels), containing the ordered list of surfels that forms
       the connected component of the digital surface slice containing
       surfel \a start_surfel and the direction \a trackDir.
        
       @param K any space (dimension is arbitrary).

       @param trackDir the initial track direction at [start_surfel],
       should be different from the orthogonal direction of
       [start_surfel].

       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param sp an instance of a model of CSurfelPredicate, for
       instance a FrontierPredicate or a BoundaryPredicate.

       @param start_surfel a signed surfel such that sp(start_surfel) is true.
    */
    template <typename SurfelPredicate>
    static 
    void track2DSliceSurface( std::vector<SCell> & aSCellContour,
			       const KSpace & K, 
			       const Dimension & trackDir,
			       const SurfelAdjacency<KSpace::dimension> & surfel_adj,
			       const SurfelPredicate & sp,
			       const SCell & start_surfel );



    /**
       Function that extracts the boundary of a 2D shape (specified by
       a predicate on point) in a 2D KSpace. The boundary is returned
       as a vector of points.
       
       This method uses random tries to find a first linel separating
       an interior pixel from an exterior one. It then follows direct
       orientations to extract the 4-connected set of points.

       @param aVectorOfPoints (returns) the sequence of points of the
       boundary component of the digitized shape containing [start_surfel].

       @param K any space of dimension 2.

       @param surfel_adj the surfel adjacency chosen for the tracking.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape,
       which should be at least partially included in the bounds of
       space [K].

       @param start_surfel a signed surfel which should be between an
       element of [shape] and an element not in [shape].
    */
    template <typename PointPredicate>
    static
    void 
    track2DBoundaryPoints( std::vector<Point> & aVectorOfPoints,
         const KSpace & K, 
         const SurfelAdjacency<KSpace::dimension> & surfel_adj,
         const PointPredicate & pp,
         const SCell & start_surfel );


    /**
       Function that extracts all the boundaries of a 2D shape
       (specified by a predicate on point) in a 2D KSpace. The
       boundaries are returned as a vector of vector of points.

       Extract all 4-connected contours as a vector containing the sequence
       of contour Points.  Each contour is represented by a vector of
       points defined by the sequence of pointels extracted from the
       boundary surfels. Calls extractAll2DSCellContours.
       
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param aVectPointContour2D (modified) a vector of contour represented
       by a vector of cells (which are all surfels), containing the
       ordered list of the boundary component of [pp].
       
       @param aKSpace any space.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.

       @param aSAdj the surfel adjacency chosen for the tracking.

    */
    template <typename PointPredicate>
    static 
    void extractAllPointContours4C
    ( std::vector< std::vector< Point > > & aVectPointContour2D,
      const KSpace & aKSpace,
      const PointPredicate & pp,
      const SurfelAdjacency<2> &aSAdj );

    

    /**
       Extract all contours as a vector containing the set of contours
       composed of SCell.  Each contour is represented by a vector of
       signed surfels whose elements represents a boundary component of
       a digital shape defined by the predicate [pp]. The algorithms
       tracks surfels along the boundary of the shape.
       
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param aVectSCellContour2D (modified) a vector of contour represented
       by a vector of cells (which are all surfels), containing the
       ordered list of the boundary component of [spelset].
       
       @param aKSpace any space.
       
       @param aSurfelAdj the surfel adjacency chosen for the tracking.
       
       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.
    */
    template <typename PointPredicate>
    static 
    void extractAll2DSCellContours
    ( std::vector< std::vector<SCell> > & aVectSCellContour2D,
      const KSpace & aKSpace,
      const SurfelAdjacency<KSpace::dimension> & aSurfelAdj,
      const PointPredicate & pp );
    

    /**
       Extract all surfel elements associated to each connected
       components of the given DigitalSet. The connected surfel set
       are given as result in a vector containing all components. The
       orientation of the resulting SCell indicates the exterior
       orientation according the positive axis.
       
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.

       @param aVectConnectedSCell (modified) a vector containing for
       each connected components a vector of the sequence of connected
       SCells.
       
       @param aKSpace any space.
       
       @param aSurfelAdj the surfel adjacency chosen for the tracking.
       
       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.
       
       @param forceOrientCellExterior if 'true', used to change the
       default cell orientation in order to get the direction of shape
       exterior (default =false). This is used only for displaying
       cells with Viewer3D. This mechanism should evolve shortly.
    */
    template <typename PointPredicate >
    static 
    void extractAllConnectedSCell
    ( std::vector< std::vector<SCell> > & aVectConnectedSCell,
      const KSpace & aKSpace,
      const SurfelAdjacency<KSpace::dimension> & aSurfelAdj,
      const PointPredicate & pp,
      bool forceOrientCellExterior=false );

    
    

    /**
       Orient the SCell positively in the direction of the exterior of
       the DigitalSet shape. It simply check if the direct
       incident Cell in the first upper dimension (obtain with
       @ref KhalimskySpaceND::sDirectIncident) belongs to the DigitalSet or not.
       
       This method is used to change the default cell orientation in
       order to get the direction of shape exterior (default
       =false). This is used only for displaying cells with
       Viewer3D. This mechanism should evolve shortly.

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.

       @param aVectOfSCell (modified) a vector containing the SCell to
       be oriented positively in the direction of the exterior.
       
       @param aKSpace any space.
       
       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.
       
    */
    template <typename PointPredicate>
    static 
    void orientSCellExterior(std::vector<SCell> & aVectOfSCell,  
           const KSpace & aKSpace, 
           const PointPredicate & pp  );

    

    
    
    
    /**
       Creates a set of unsigned surfels whose elements represents all the
       boundary components of a digital shape described by the predicate
       [pp].
       
       @tparam CellSet a model of a set of Cell (e.g., std::set<Cell>).
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param aBoundary (modified) a set of cells (which are all surfels),
       the boundary component of [aSpelSet].
       
       @param aKSpace any space.
       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.

       @param aLowerBound and @param aUpperBound points giving the
       bounds of the extracted boundary.
    */
    template <typename CellSet, typename PointPredicate >
    static 
    void uMakeBoundary( CellSet & aBoundary,
                        const KSpace & aKSpace,
                        const PointPredicate & pp,
                        const Point & aLowerBound, 
                        const Point & aUpperBound  );
    
    /**
       Creates a set of signed surfels whose elements represents all the
       boundary components of a digital shape described by the predicate
       [pp].
       
       @tparam SCellSet a model of a set of SCell (e.g., std::set<SCell>).
       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param aBoundary (modified) a set of cells (which are all surfels),
       the boundary component of [aSpelSet].
       
       @param aKSpace any space.
       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.

       @param aLowerBound and @param aUpperBound points giving the
       bounds of the extracted boundary.
    */
    template <typename SCellSet, typename PointPredicate >
    static 
    void sMakeBoundary( SCellSet & aBoundary,
                        const KSpace & aKSpace,
                        const PointPredicate & pp,
                        const Point & aLowerBound, 
                        const Point & aUpperBound  );

    /**
       Writes on the output iterator @a out_it the unsigned surfels
       whose elements represents all the boundary elements of a
       digital shape described by the predicate [pp].
       
       @tparam OutputIterator any output iterator (like
       std::back_insert_iterator< std::vector<Cell> >).

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param out_it any output iterator for writing the cells.
       
       @param aKSpace any space.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.

       @param aLowerBound and @param aUpperBound points giving the
       bounds of the extracted boundary.
    */
    template <typename OutputIterator, typename PointPredicate >
    static 
    void uWriteBoundary( OutputIterator & out_it,
                         const KSpace & aKSpace,
                         const PointPredicate & pp,
                         const Point & aLowerBound, 
                         const Point & aUpperBound  );
    
    /**
       Writes on the output iterator @a out_it the signed surfels
       whose elements represents all the boundary elements of a
       digital shape described by the predicate [pp].
       
       @tparam OutputIterator any output iterator (like
       std::back_insert_iterator< std::vector<SCell> >).

       @tparam PointPredicate a model of concepts::CPointPredicate describing
       the inside of a digital shape, meaning a functor taking a Point
       and returning 'true' whenever the point belongs to the shape.
       
       @param out_it any output iterator for writing the signed cells.
       
       @param aKSpace any space.

       @param pp an instance of a model of concepts::CPointPredicate, for
       instance a SetPredicate for a digital set representing a shape.

       @param aLowerBound and @param aUpperBound points giving the
       bounds of the extracted boundary.
    */
    template <typename OutputIterator, typename PointPredicate >
    static 
    void sWriteBoundary( OutputIterator & out_it,
                         const KSpace & aKSpace,
                         const PointPredicate & pp,
                         const Point & aLowerBound, 
                         const Point & aUpperBound  );
    

    


    /**
     * Given a boundary surface [aSurfPred] in [aKSpace] (given as
     * SurfelPredicate), fills its interior in a given image [anImage]
     * by a specific value [aValue] (considered as increment if
     * [incrementMode] is set to true). The technique is to fill line
     * by line and tests the intersection with the surface. Note that
     * the set of the surfel of the boundary has to be a closed
     * surface.
     * 
     * 
     * @param aKSpace the digital space.
     * @param aSurfPred the digital Jordan surface.
     * @param anImage the image to be filled.
     * @param aValue the value to fill the image.
     * @param empty_is_inside when 'true', an empty line is considered
     * interior, otherwise exterior (set by default to false).
     * @param incrementMode if set to 'true' the image value is incremented by [aValue] instead to be set to [aValue]  (default).
     * @return the number of cells filled in the image.
     */
    template < typename TSurfelPredicate, typename TImageContainer> 
    unsigned int
    static
    uFillInterior( const KSpace & aKSpace, 
                   const TSurfelPredicate & aSurfPred,
                   TImageContainer & anImage,
                   const typename TImageContainer::Value & aValue,
                   bool empty_is_inside=false,
                   bool incrementMode=true );


    /**
     * Given a boundary surface [aSurfPred] in [aKSpace] (given as
     * SurfelPredicate), fills its exterior in a given image [anImage]
     * by a specific value [aValue] (considered as increment if
     * [incrementMode] is set to true). The technique is to fill line
     * by line and tests the intersection with the surface. Note that
     * the set of the surfel of the boundary has to be a closed
     * surface.
     *
     * @param aKSpace the digital space.
     * @param aSurfPred the digital Jordan surface.
     * @param anImage the image to be filled.
     * @param aValue the value to fill the image.
     * @param empty_is_outside when 'true', an empty line is considered
     * exterior, otherwise interior.
     * @param incrementMode if set to 'true' the image value is incremented by [aValue] instead to be set to [aValue]  (default).
     * @return the number of cells filled in the image.
     */
    template < typename SurfelPredicate, typename TImageContainer> 
    unsigned int
    static
    uFillExterior( const KSpace & aKSpace, 
                   const SurfelPredicate & aSurfPred,
                   TImageContainer & anImage,
                   const typename TImageContainer::Value & aValue,
                   bool empty_is_outside=true,
                   bool incrementMode=true );

    
    /// Given a space \a K and an oriented cell \a s, returns its vertices.
    /// @param K any cellular grid space.
    /// @param s any signed cell.
    /// @return the vector of the vertices of s, as unsigned cells of dimension 0.
    static
    CellRange getPrimalVertices( const KSpace& K, const SCell& s );
    
    /// Given a space \a K and a surfel \a s, returns its vertices in ccw or cw order.
    /// @param K any cellular grid space of dimension 3.
    /// @param s any surfel, a signed cell of dimension 2.
    /// @param ccw when 'true', the order corresponds to a ccw orientation seen from the exterior normal to the surfel, otherwise it is a cw order.
    /// @return the vector of the vertices of s, as unsigned cells of dimension 0.
    /// @note useful when exporting faces to OBJ format. 
    static
    CellRange getPrimalVertices( const KSpace& K, const Surfel& s, bool ccw );
    

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~Surfaces();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    Surfaces();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    Surfaces ( const Surfaces & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Surfaces & operator= ( const Surfaces & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Surfaces


  /**
   * Overloads 'operator<<' for displaying objects of class 'Surfaces'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Surfaces' to write.
   * @return the output stream after the writing.
   */
  template <typename TKSpace>
  std::ostream&
  operator<< ( std::ostream & out, const Surfaces<TKSpace> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/helpers/Surfaces.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Surfaces_h

#undef Surfaces_RECURSES
#endif // else defined(Surfaces_RECURSES)
