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
 * @file MultiStatistics.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @author Jacques-Olivier Lachaud
 * @date 2015/11/09
 *
 * Header file for module MultiStatistics.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MultiStatistics_RECURSES)
#error Recursive header files inclusion detected in MultiStatistics.h
#else // defined(MultiStatistics_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MultiStatistics_RECURSES

#if !defined MultiStatistics_h
/** Prevents repeated inclusion of headers. */
#define MultiStatistics_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class MultiStatistics
/**
 * Description of class 'MultiStatistics' <p> \brief Aim: This class
 * stores a set of sample values for several variables and can then
 * compute different statistics, like sample mean, sample variance,
 * sample unbiased variance, etc.
 *
 * @note the method @ref terminate() should be called before accessing
 * to the quantities like mean, variance, etc.
 * 
 *
 * The proposed implementation is mainly a backport from
 * [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene) with some
 * various refactoring.
 */
class MultiStatistics
{
    // ----------------------- Standard services ------------------------------
public:


    /**
     * Destructor.
     */
    ~MultiStatistics();



   /** 
     * Creates an object for computing [size] statistics.
     * 
     * @param[in] size the number of statistical variables.
     * @param[in] storeSamples when 'true', stores each given sample,
     * default is 'false'
     */    
    MultiStatistics( const unsigned int size, const bool storeSamples = false );



  /**
     * Reads the input stream [in] line by line, excluding line beginning
     * with '#' and selects some columns according to [indices] to fill
     * the array of samples [samples]. For instance, if indices == { 3, 4,
     * 1 }, then samples( 0 ) will contain the third column, samples( 1 ),
     * the fourth column and samples( 2 ) the first column.
     *
     * @param[out] in (modified) the input stream.
     * @param[out] samples (updates) stores the data.
     * @param[in] indices specifies in which columns data are read.
     */
     static void read( std::istream & in, MultiStatistics & samples,
                       const std::vector<unsigned int> & indices );



    // ----------------------- Accessors ------------------------------
  public:

    /** 
     * @return the number of statistical variables.
     */
    inline unsigned int nb() const;


    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the number of samples for this variable.
     */
    inline unsigned int samples( const unsigned int k ) const;

    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the sample mean for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline double mean( const unsigned int k ) const;

    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the sample variance for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline double variance( const unsigned int k ) const;

    /** 
     * @param k the statistical variable.
     * 
     * @return the unbiased sample variance for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline double unbiasedVariance( const unsigned int k ) const;

    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the maximal value for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline double max( const unsigned int k ) const;


    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the indice of the maximal value for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline unsigned int maxIndice( unsigned int k ) const;



    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the minimal value for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline double min( const unsigned int k ) const;



    /** 
     * @param[in] k the statistical variable.
     * 
     * @return the indice of the minimal value for this variable.
     * @pre method 'terminate' must have been called.
     * @see terminate
     */
    inline unsigned int minIndice(const unsigned int k ) const;



    /** 
     * Returns a stored sample value that was added before. The object
     * should have been initialized with 'store_samples = true'.
     *
     * @param[in] k the statistical variable.
     *
     * @param[in] i the index of the sample value, '0<=i<samples(k)'.
     * 
     * @return the [i]-th value for this variable.
     *
     * @see MultiStatistics, init
     */
    inline double value( const unsigned int k, const unsigned int i ) const;
  


    /** 
     * Adds a new sample value [v] for the variable [k].
     * 
     * @param[in] k the statistical variable.
     * @param[in] v the new sample value.
     */
    void addValue( unsigned int k, double v );

  
    /**
     * Adds a sequence of sample values for the variable [k], scanning
     * a container from iterators [b] to [e].
     * 
     * Exemple: 
     @code
     vector<double> x;
     MultiStatistics stats( 1, true );
     stats.addValue( x + 4, x + 10 );
     @endcode
     *
     * @param[in] k the statistical variable.
     * @param[in] b an iterator on the starting point.
     * @param[in] e an iterator after the last point.
     */
    template <class Iter>
    void addValues(const  unsigned int k, Iter b, Iter e );

    /** 
     * Once all sample values have been added to this object, computes
     * meaningful statistics like sample mean, variance and unbiased
     * variance.
     * 
     * @see mean, variance, unbiasedVariance, min, max
     */
    void terminate();


    /** 
     * Reinitializes the object to contain [size] statistical
     * variables. All preceding sample values and statistics are
     * lost. Calls 'erase()'.
     * 
     * @param[in] size the number of statistical variables.
     *
     * @param[in] storeSamples when 'true', stores each given sample,
     *
     * @see erase
     */
    void init( unsigned int size, bool storeSamples );


    /** 
     * Clears the object from all given samples. The object still
     * represents 'nb()' statistical variables.
     */
    void clear();
  

    /** 
     * Erases the object as if it was just created. The user must call
     * 'init()' before any other method.
     * 
     * @see init
     */
    void erase();

    /**
     * Computes the covariance of the [x],[y] variables. The
     * 'MultiStatistics' object should have stored its values and
     * 'terminate' should have been called.
     *
     * @param[in] x the index of the statistics to be used as the x-variable (should be valid)
     * @param[in] y the index of the statistics to be used as the y-variable (should be valid)
     * @param[in] s the starting value index (default is 0 )
     * @param[in] e the after-the-end value index (default is 0, meaning all )
     *
     * @return the covariance of [x],[y] from indices [s] to [e].
     */
  double covariance( const unsigned int x, const unsigned int y, 
                     const unsigned int s = 0, unsigned int e = 0 ) const;
  
    /**
     * Computes the linear regression of the ([x],[y]) variables. The
     * 'MultiStatistics' object should have stored its values and
     * 'terminate' should have been called.
     *
     * @param[in] x the index of the x-variable (should be valid )
     * @param[in] y the index of the y-variable (should be valid )
     *
     * @return the pair (slope, shift at origin )
     */
    std::pair<double,double> linearRegression( const unsigned int x, 
                                               const unsigned int y ) const;



    /**
     * Computes the median value for a variable k. The
     * 'MultiStatistics' object should have stored its values and 'terminate'
     * should have been called.
     *
     * @param[in] k the statistical variable.
     *
     * @return the median value for the variable k.
     */
    double median( const unsigned int k );





    // ----------------------- Interface --------------------------------------
public:

    /**
     * Writes/Displays the object on an output stream.
     * @param[out] out the output stream where the object is written.
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

    /**
     * Number of statistical variables.
     */
    unsigned int myNb;

    /**
     * For each variable, number of samples
     */
    unsigned int* mySamples;

    /**
     * For each variable, stores the sum of sample values for
     * computing sample mean.
     */
    double* myExp;

    /**
     * For each variable, stores the sum of squared sample values for
     * computing sample variance.
     */
    double* myExp2;

    /**
     * For each variable, stores the sample variance.
     */
    double* myVar;

    /**
     * For each variable, stores the unbiased sample variance.
     */
    double* myUnbiasedVar;
    
    /**
     * For each variable, stores the maximal sample value.
     */
    double* myMax;

    /**
     * For each variable, stores the indice of the maximal sample value.
     */
    unsigned int* myIndiceMax;

    /**
     * For each variable, stores the minimal sample value.
     */
    double* myMin;

    /**
     * For each variable, stores the indice of the minimal sample value.
     */
    unsigned int* myIndiceMin;

    /**
     * Tells if values must be stored or not.
     */
    bool myStoreSamples;

    /**
     * For each variable, stores the sample values if
     * [myStoreSamples] is 'true'.
     */
    std::vector<double>* myValues;

  /**
   * To prevent that terminate() is called before using statistics like mean,
   *  variance etc.
   **/
  bool myIsTerminate;
  
    // ------------------------- Hidden services ------------------------------
protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    MultiStatistics();

private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    MultiStatistics ( const MultiStatistics & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    MultiStatistics & operator= ( const MultiStatistics & other );

    // ------------------------- Internals ------------------------------------
private:

}; // end of class MultiStatistics


/**
 * Overloads 'operator<<' for displaying objects of class 'MultiStatistics'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'MultiStatistics' to write.
 * @return the output stream after the writing.
 */
std::ostream&
operator<< ( std::ostream & out, const MultiStatistics & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/math/MultiStatistics.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MultiStatistics_h

#undef MultiStatistics_RECURSES
#endif // else defined(MultiStatistics_RECURSES)
