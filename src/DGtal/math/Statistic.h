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
 * @file
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2011/06/24
 *
 * Header file for module Statistics
 *
 * This file is part of the DGtal library.
 */

#if defined(Statistics_RECURSES)
#error Recursive header files inclusion detected in Statistics.h
#else // defined(Statistics_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Statistics_RECURSES

#if !defined Statistics_h
/** Prevents repeated inclusion of headers. */
#define Statistics_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CCommutativeRing.h"
#include "DGtal/kernel/NumberTraits.h"
#include <utility>
#include <vector>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /**
    Description of class 'Statistic' <p> \brief Aim: This class processes a
    set of sample values for one variable and can then compute
    different statistics, like sample mean, sample variance, sample
    unbiased variance, etc. It is minimalistic for space
    efficiency. For multiple variables, sample storage and others,
    see Statistics class.

    Backported from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene). \cite Lachaud03b
    
    @see testStatistics.cpp

    @tparam TQuantity any model of CCommutativeRing.
   */
  template <typename TQuantity>
  class Statistic
  {

    // ----------------------- public types -----------------------------------
  public:
    typedef TQuantity Quantity;
    BOOST_CONCEPT_ASSERT(( concepts::CCommutativeRing<Quantity> ) );
    typedef std::vector< Quantity > Container;
    typedef typename Container::const_iterator ConstIterator;
    
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor. 
     */
    ~Statistic();

    /**
     * Constructor.
     */
    Statistic(bool storeSample=false);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Statistic( const Statistic & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Statistic & operator=( const Statistic & other );

    /**
     * Adds to self another set of statistics (should be of the same
     * variable).
     *
     * @param other the object to add.
     * @return a reference on 'this'.
     */
    Statistic & operator+=( const Statistic & other );

    /**
     * Adds two set of statistics (should be of the same variable).
     *
     * @param other the object to add.
     * @return a new object that is the union of these statistics.
     */
    Statistic operator+( const Statistic & other ) const;

    /**
       @return an iterator on the first stored value (if storeSample was set).
    */
    ConstIterator begin() const;

    /**
       @return an iterator after the last stored value (if storeSample was set).
    */
    ConstIterator end() const;
 
    // ----------------------- Accessors ------------------------------
  public:


    /** 
     * @return the number of samples.
     */
    unsigned int samples() const;

    /** 
     * @return the number of samples.
     */
    unsigned int size() const;

    /** 
     * @return the sample mean (given as double).
     */
    double mean() const;

    /** 
     * @return the sample variance (given as double).
     */
    double variance() const;

    /** 
     * @return the unbiased sample variance (given as double).
     */
    double unbiasedVariance() const;

    /** 
     * @return the maximal value.
     */
    Quantity max() const;

    /** 
     * @return the minimal value.
     */
    Quantity min() const;
    

    /**
     * Return the median value of the Statistic values. It can be given in two possible cases:
     * - if the the values are stored in the 'Statistic' objects (not always a good solution). (complexity: linear on average)
     * - if the values were first stored and computed by the function @ref terminate(). 
     *  @return the median value.
     * 
     * @see terminate, Statistic 
     */
    Quantity median();

    /// @param[in] i a valid index
    /// @return the corresponding value (if stored).
    Quantity operator[]( unsigned int i ) const;
    
    /** 
     * Adds a new sample value [v].
     * 
     * @param v the new sample value.
     */
    void addValue( Quantity v );
  
    /**
     * Adds a sequence of sample values, scanning a container from
     * iterators [b] to [e].
     * 
     * Exemple: 
     @code
     vector<Quantity> x;
     Statistic stats;
     stats.addValue( x + 4, x + 10 );
     @endcode
     *
     * @param b an iterator on the starting point.
     * @param e an iterator after the last point.
     */
    template <class Iter>
    void addValues( Iter b, Iter e );

    /** 
     * Clears the object. As if it has just been created.
     */
    void clear();
 
    /**
     * Computes the median value of the statistics and switch to mode
     * which does not save the statistics samples (@ref
     * myStoreSamples = false). Usefull only if the values are stored
     * (specified in the the constructor) else it doest nothing.
     *
     * @see median, Statistic, myStoreSamples
     */
    void terminate();
    

    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param that_stream the output stream where the object is written.
     */
    void selfDisplay( std::ostream & that_stream ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool OK() const;
  

    // ------------------------- Datas ----------------------------------------
  private:


    // ------------------------- Datas ----------------------------------------
  private:

    /**
     * number of samples
     */
    unsigned int mySamples;

    /**
     * stores the sum of sample values for computing sample mean.
     */
    Quantity myExp;

    /**
     * stores the sum of squared sample values for
     * computing sample variance.
     */
    Quantity myExp2;

    /**
     * stores the maximal sample value.
     */
    Quantity myMax;

    /**
     * stores the minimal sample value.
     */
    Quantity myMin;


    /**
     * stores the median sample value.
     */
    Quantity myMedian;
    
    
    /**
     * stores the sample to determine the median value 
     * 
     **/
    Container myValues;


    /**
     * Tells if values must be stored or not. 
     */
    bool myStoreSamples;
     
    
    /**
     * Tells if terminate was called. Usefull to return median value
     * even if the m_values are no more stored (possible after
     * serialisation which doest store the values.).
     *
     */
    bool myIsTerminated;
  
  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'Statistic'.
   * @param thatStream the output stream where the object is written.
   * @param that_object_to_display the object of class 'Statistic' to write.
   * @return the output stream after the writing.
   */
  template <typename TQuantity>
  std::ostream&
  operator<<( std::ostream & thatStream, 
        const Statistic<TQuantity> & that_object_to_display );
  
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#include "DGtal/math/Statistic.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Statistic_h

#undef Statistic_RECURSES
#endif // else defined(Statistic_RECURSES)
