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
 * @file Histogram.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/10/25
 *
 * Header file for module Histogram.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Histogram_RECURSES)
#error Recursive header files inclusion detected in Histogram.h
#else // defined(Histogram_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Histogram_RECURSES

#if !defined Histogram_h
/** Prevents repeated inclusion of headers. */
#define Histogram_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Clone.h"
#include "DGtal/math/CBinner.h"
#include "DGtal/kernel/CEuclideanRing.h"
#include "DGtal/math/Statistic.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /**
    Description of template class 'RegularBinner' <p> \brief Aim:
    Represents an elementary functor that partitions quantities into
    regular intervals, given a range [\a min,\a max] range and a
    number \a nb of intervals (each interval is called a bin).

    Model of CBinner.

    @tparam TQuantity any number type, model of CEuclideanRing.
  */
  template <typename TQuantity>
  struct RegularBinner {
    typedef TQuantity Quantity;
    typedef RegularBinner< Quantity > Self;
    typedef DGtal::uint32_t Bin;

    Quantity myMin; /**< any value below is considered the same. */
    Quantity myMax; /**< any value above is considered the same. */
    Bin myNb;       /**< the number of bins. */
    Quantity myWidth;/**< the width of each bin. */

    /**
       Creates a regular binner that place quantities in range [\a
       min,\a max] in \a n bins (numbered from 0 to \a n-1), such
       that all bins have equal width \f$\frac{max-min}{n}\f$.

       @param min any quantity smaller than \a min falls into bin 0.
       @param max any quantity greater than \a max falls into bin \a n-1.
       @param n the number of bins.
       @pre \a n>0.
    */
    RegularBinner( const Quantity & min, const Quantity & max, Bin n )
      : myMin( min ), myMax( max ), myNb( n )
    {
      ASSERT( max > min );
      ASSERT( n > 0 );
      myWidth = ( max - min ) / static_cast<Quantity>( n );
    }

    /**
       @return the number of bins of this binner.
    */
    inline Bin size() const
    { 
      return myNb;
    }

    /**
       Places the quantity \a q into the correct bin.
       @param q any quantity
       @return the associated bin (integer in [0,\c size()-1].
    */
    inline Bin operator()( const Quantity & q ) const
    {
      if ( q <= myMin )      return NumberTraits<Bin>::ZERO;
      else if ( q >= myMax ) return myNb - NumberTraits<Bin>::ONE;
      else return static_cast<Bin>( floor( NumberTraits<Quantity>::castToDouble( ( q - myMin ) / myWidth ) ) );
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // template class Histogram
  /**
    Description of template class 'Histogram' <p>
    \brief Aim: Represents a typical histogram in statistics, which is
    a discrete estimate of the probability distribution of a
    continuous variable.

    @code
    std::vector<double> v; 
    ...
    Statistic<double> stats;
    stats.addValues( v.begin(), v.end() );
    stats.terminate(); // stats are computed.

    Histogram<double> hist;
    hist.init( Histogram<double>::Scott, stats );
    hist.addValues( v.begin(), v.end() );
    hist.terminate();
    // Displays the estimated probability density function
    for ( unsigned int i = 0; i < hist.size(); ++i )
      std::cout << i << " " << hist.pdf( i ) << std::endl;
    @endcode

    @tparam TQuantity any model of CEuclideanRing listed in
    NumberTraits and that can be castToDouble.

    @tparam TBinner any model of CBinner that puts a quantity into a
    bin. Default is RegularBinner<TQuantity>.
   */
  template < typename TQuantity,
             typename TBinner = RegularBinner< TQuantity > >
  class Histogram
  {
  public:
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing< TQuantity > ));
    BOOST_CONCEPT_ASSERT(( concepts::CBinner< TBinner > ));
    BOOST_STATIC_ASSERT(( boost::is_same< TQuantity, typename TBinner::Quantity >::value ));

    // ----------------------- public types ------------------------------
  public:
    typedef TQuantity Quantity;
    typedef TBinner Binner;
    typedef Histogram< Quantity, Binner > Self;
    typedef typename Binner::Bin Bin;
    typedef DGtal::uint64_t Size;
    typedef std::vector<Size> Container;
    typedef Container::const_iterator ConstIterator;

    /**
       Determines the number of bins \a k or the width \a h as a function of \a n
       (number of samples), \a s (variance of samples).
    */
    enum Formula { SquareRoot /**< Rule is k=sqrt(n) */,
                   Sturges /**< Rule is k=ceil(log_2(n)+1) */, 
                   Rice /**< Rule is k=ceil(n^(1/3)) */,
                   Scott /**< Rule is h=3.5s/(n^(1/3)) */ };
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~Histogram();

    /**
     * Constructor. The object is not valid.
     */
    Histogram();

    /**
       The object is fully cleared. The object must be initialized in order to be valid.
    */
    void clear();

    /**
     * Initialization from Binner. The binner is cloned into this object.
     */
    void init( Clone<Binner> binner );

    /**
       Initialization from a statistic (min, max, samples, variance
       can typically be used) and a given \a formula.
    */
    void init( Formula formula, const Statistic<Quantity> & stat );

    /**
       Initialization from a number of bins and a statistic (min, max, samples, variance
       can typically be used).
    */
    void init( Bin nbBins, const Statistic<Quantity> & stat );

    /**
       Add the quantity \a q to the histogram.
       @param q any quantity.
    */
    void addValue( Quantity q );

    /**
       Add the quantities stored in range [it,itE) to the histogram.
       @tparam TInputIterator any model of boost::InputIterator on Quantity.
       @param it an iterator on the first element of the range [it,itE)
       @param itE an iterator after the last element of the range [it,itE)
    */
    template <typename TInputIterator>
    void addValues( TInputIterator it, TInputIterator itE );

    /**
       Should be called when all values have been added.
    */
    void terminate();

    /**
       @param q any quantity
       @return the bin in which quantity \a q would fall if added to this object.
    */
    Bin bin( Quantity q ) const;

    /**
       @return the number of bins.
    */
    Bin size() const;

    /**
       @return the total number of samples in the histogram, i.e. the number of added quantities.
       @pre terminate() must be called before.
    */
    Size area() const;

    /**
       @param b any bin in 0 .. size()-1
       @return the number of quantities in bin \a b.
    */
    Size nb( Bin b ) const;

    /**
       @param b any bin in 0 .. size()-1
       @return the total number of quantities in bins 0 to \a b (included).
       @pre terminate() must be called before.
    */
    Size accumulation( Bin b ) const;

    /**
       @return the probability density function in the whole bin \a b (constant).
       @pre terminate() must be called before.
    */
    double pdf( Bin b ) const;

    /**
       @return the cumulative distribution function at bin \a b.
       @pre terminate() must be called before.
    */
    double cdf( Bin b ) const;

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
  protected:
    /// The binner that places quantities into a bin.
    const Binner* myBinner;
    /// The histogram data.
    Container myHistogram;
    /// The cumulative histogram data.
    Container myCumulativeHistogram;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    Histogram ( const Histogram & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Histogram & operator= ( const Histogram & other );

    // ------------------------- Internals ------------------------------------
  private:
    /**
       Prepares container for further data.
    */
    void prepare( Bin size );


  }; // end of class Histogram


  /**
   * Overloads 'operator<<' for displaying objects of class 'Histogram'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Histogram' to write.
   * @return the output stream after the writing.
   */
  template <typename TQuantity, typename TBinner>
  std::ostream&
  operator<< ( std::ostream & out, const Histogram<TQuantity, TBinner> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/math/Histogram.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Histogram_h

#undef Histogram_RECURSES
#endif // else defined(Histogram_RECURSES)
