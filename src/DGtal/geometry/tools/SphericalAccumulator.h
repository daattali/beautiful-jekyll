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
 * @file SphericalAccumulator.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/09/17
 *
 * Header file for module SphericalAccumulator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SphericalAccumulator_RECURSES)
#error Recursive header files inclusion detected in SphericalAccumulator.h
#else // defined(SphericalAccumulator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SphericalAccumulator_RECURSES

#if !defined SphericalAccumulator_h
/** Prevents repeated inclusion of headers. */
#define SphericalAccumulator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <algorithm>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SphericalAccumulator
  /**
   * Description of template class 'SphericalAccumulator' <p>
   *
   * \brief Aim: implements an accumulator (as histograms for 1D scalars)
   * adapted to spherical point samples.
   *
   * Spherical accumulator is decomposed into 2D bins (i,j) such that:
   *  - each direction/point on the unit sphere falls in a single bin
   *  - each bin almost cover the same area on the unit sphere
   *  - each bin have a geometrical support which can be represented
   * as a quad except for its two poles
   *
   * Compared to exact geodesic covering, such spherical accumulator
   * bins do not have the exact same area. However, it allows fast
   * conversion between directions and bin coordinates.
   *
   * Such accumulator have been demonstrated in:
   *      ﻿Borrmann, D., Elseberg, J., & Lingemann, K. (2011). The 3D Hough
   *      ﻿Transform for plane detection in point clouds: A review and a new
   *      ﻿accumulator design. 3D Research, 02003. Retrieved from
   *      ﻿http://www.springerlink.com/index/N1W040850782VR85.pdf
   *
   *
   * Usage example:
   * @snippet testSphericalAccumulator.cpp SphericalAccum-init
   * @snippet testSphericalAccumulator.cpp SphericalAccum-add
   *
   * Once the accumulator is filled up with directions, you can get
   * the representative direction for each bin and the bin with
   * maximal number of samples.
   *
   * Furthermore, you can send the accumulator to a Viewer3D to see
   * the bin geometry and values:
   * @code
   * ...
   * Viewer3D viewer;
   * viewer << accumulator;
   * ...
   * @endcode
   *
   *
   * @see testSphericalAccumulator.cpp
   *
   * @tparam TVector type used to represent directions.
   *
   */
  template <typename TVector>
  class SphericalAccumulator
  {
    // ----------------------- Standard services ------------------------------
  public:

    ///Vector direction types
    typedef TVector Vector;

    ///Type to store the bin counts
    typedef DGtal::int32_t Quantity;

    ///Type to represent bin indexes
    typedef DGtal::uint32_t Size;

    ///Type to iterate on bin values.
    typedef std::vector<Quantity>::const_iterator  ConstIterator;

    ///Type to represent normalized vector (internal use).
    typedef PointVector<3,double>  RealVector;

    BOOST_STATIC_ASSERT( Vector::dimension == 3);

    /**
     * Constructs a spherical accumulator with @a aNphi slices along
     * latitudes (phi spherial coordinate).  The decomposition along
     * the theta axis is also a function of @a aNphi.
     *
     *
     * @param aNphi the number of slices in the longitude
     * polar coordinates.
     */
    SphericalAccumulator(const Size aNphi);

    /**
     * Destructor.
     */
    ~SphericalAccumulator();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Add a new direction into the accumulator. The accumulator
     * updates the bin coordinates with maximum count.
     *
     * @param aDir a direction
     */
    void addDirection(const Vector &aDir);

    /**
     * Given a normalized direction, this method computes the bin
     * coordinates.
     *
     * @pre @a aDir a direction.
     * @param aDir a direction represented as a unit norm vector.
     * @param posPhi position according to the first direction.
     * @param posTheta position according to the second direction.
     */
    void binCoordinates(const Vector &aDir,
			Size &posPhi,
			Size &posTheta) const;

    /**
     * Returns the current number of samples in the bin
     * (posPhi,posTheta).
     *
     * @param posPhi position according to the first direction
     * @param posTheta position according to the second direction
     *
     * @return the number of accumulated samples
     */
    Quantity count( const Size &posPhi,
		    const Size &posTheta) const;


    /**
     * Returns the representative direction associated with the bin
     * (posPhi,posTheta).
     * If the bin does not contain any sample, a null vector is
     * returned ( @a Vector::ZERO ).
     *
     * Otherwise, it returns the (unnormalized) sum of directions
     * added to the bin.
     *
     *
     * @param posPhi position according to the first direction
     * @param posTheta position according to the second direction
     *
     * @return the representative direction.
     */
    Vector representativeDirection(const Size &posPhi,
				   const Size &posTheta) const;

    /**
     * Get the representative direction of a bin specified by a
     * ConstIterator.
     *
     * @param it the iterator on the bin to get the direction
     *
     * @return the representative direction of bin @a it.
     */
    Vector representativeDirection(ConstIterator &it) const;


    /**
     * @return returns the number of directions in the current
     * accumulator.
     *
     */
    Quantity samples() const;

    /**
     * @return returns the number of bins in the accumulator.
     *
     */
    Quantity binNumber() const { return myBinNumber;}


    /**
     * Returns the coordinates of the bin containing the maximum
     * number of samples.
     *
     * @param posPhi coordinate along the phi axis.
     * @param posTheta coordinate along the theta axis.
     */
    void maxCountBin(Size &posPhi, Size &posTheta) const;

    /**
     * Clear the current accumulator.
     *
     */
    void clear();


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

    /**
     *
     * @return the class name.
     */
    std::string className() const
    {
      return "SphericalAccumulator";
    }


    /**
     * Returns true if is bin (posPhi,posTheta) is valid.
     *
     * @param posPhi posPhi index
     * @param posTheta posTheta index
     *
     * @return true if (posPhi,posTheta) is valid.
     */
    bool isValidBin(const Size &posPhi,
		    const Size &posTheta) const;


    /**
     * From the bin index(posPhi,posTheta), we compute the associated
     * spherical quad (a,b,c,d) counterclockwise on the unit sphere.
     *
     * @param posPhi bin index along the first direction.
     * @param posTheta bin index along the second direction.
     * @param a vertex position.
     * @param b vertex position.
     * @param c vertex position.
     * @param d vertex position.
     */
    void getBinGeometry(const Size &posPhi,
			const Size &posTheta,
			RealVector &a,
                        RealVector &b,
                        RealVector &c,
                        RealVector &d) const;

    /**
     * From the bin index(posPhi,posTheta), we compute the main
     * direction (quad geometry midpoint).
     *
     * @param posPhi bin index along the first direction.
     * @param posTheta bin index along the second direction.
     * @return the main direction of a bin (quand mid-point).
     */
    RealVector getBinDirection(const Size &posPhi,
                               const Size &posTheta) const;

    // ------------------------- Iterators ------------------------------

    /**
     * @warning Be careful, some of the iterators may be attached to
     * un-valid bins. Once you have the iterator, convert it to bin
     * coordinates using binCoordinates and then check if the bin is
     * valid using isValidBin method.
     * @return an iterator on the bin value container (begin).
     */
    ConstIterator begin() const
    {
      return myAccumulator.begin();
    }

    /**
     * @return an iterator on the bin value container (end).
     */
    ConstIterator end() const
    {
      return myAccumulator.end();
    }


    /**
     * Given an iterator on the bin container, this method computes the bin coordinates.
     *
     * @param aDir an iterator to the bin container.
     * @param posPhi position according to the first direction.
     * @param posTheta position according to the second direction.
     */
    void binCoordinates(ConstIterator &aDir,
			Size &posPhi,
			Size &posTheta) const;

    
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SphericalAccumulator ( const SphericalAccumulator & other )
    {
      myNphi = other.myNphi;
      myNtheta = other.myNtheta;
      myAccumulator = other.myAccumulator;
      myAccumulatorDir = other.myAccumulatorDir;
      myTotal = other.myTotal;
      myBinNumber = other.myBinNumber;
      myMaxBinPhi = other.myMaxBinPhi;
      myMaxBinTheta = other.myMaxBinTheta;
    }

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    SphericalAccumulator & operator= ( const SphericalAccumulator & other )
    {
      if (this!=other)
      {
        myNphi = other.myNphi;
        myNtheta = other.myNtheta;
        myAccumulator = other.myAccumulator;
        myAccumulatorDir = other.myAccumulatorDir;
        myTotal = other.myTotal;
        myBinNumber = other.myBinNumber;
        myMaxBinPhi = other.myMaxBinPhi;
        myMaxBinTheta = other.myMaxBinTheta; 
      }
      return *this;
    }
    

    
    // ------------------------- Private Datas --------------------------------
  private:

    ///Number of slices in the phi direction
    Size myNphi;

    ///Number of bins in the theta direction
    Size myNtheta;

    ///Accumulator container
    std::vector<Quantity> myAccumulator;

    ///Accumulator reprensentative directions
    std::vector<Vector> myAccumulatorDir;

    ///Number of samples
    Quantity myTotal;

    ///Number of bins
    Quantity myBinNumber;

    ///Phi coordinate of the max bin
    Size myMaxBinPhi;

    ///Theta coordinate of the max bin
    Size myMaxBinTheta;


    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    SphericalAccumulator();

  private:

        // ------------------------- Internals ------------------------------------
  private:

  }; // end of class SphericalAccumulator


  /**
   * Overloads 'operator<<' for displaying objects of class 'SphericalAccumulator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SphericalAccumulator' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const SphericalAccumulator<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools//SphericalAccumulator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SphericalAccumulator_h

#undef SphericalAccumulator_RECURSES
#endif // else defined(SphericalAccumulator_RECURSES)
