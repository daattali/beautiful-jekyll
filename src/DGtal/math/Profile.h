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
 * @file Profile.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/11/08
 *
 * Header file for module Profile.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Profile_RECURSES)
#error Recursive header files inclusion detected in Profile.h
#else // defined(Profile_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Profile_RECURSES

#if !defined Profile_h
/** Prevents repeated inclusion of headers. */
#define Profile_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/math/Statistic.h"

#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class Profile
  /**
   * Description of class 'Profile' <p> \brief Aim: This class can be
   * used to represent a profile (PX, PY) defined from an input set of
   * samples (Xi, Yi). For all sample (Xk, Yk) having the same value
   * Xk, the associated value PY is computed (by default) by the mean
   * of the values Yk. Note that other definitions can be used (MAX,
   * MIN or MEDIAN). Internally each sample abscissa is an instance of
   * DGtal::Statistic. 
   *
   * 
   * This class is templated by the type of the functor TValueFunctor
   * which is applied on the two coordinate values of the resulting
   * profile (PX, PY). This functor is by default set to the identity
   * functor. The default type (double) of the values added to the
   * profile can also be changed by using the template parameter
   * TValue.
   *
   * For instance to construct a Profile defined from a data sample
   * having its Xi integer values from 1 to 10, you can construct
   * and initialize a Profile as follows:
   *
   * @code 
   * Profile<> sp;
   * sp.init(10);
   * @endcode 
   * 
   * Alternatively you can customize the Xi initialisation by using an
   * iterator:
   *
   * @code
   * std::vector<double> xDef;
   * for (double i = 0.5; i < 5; i=i+0.5){
   *     xDef.push_back(i);
   * }   
   * Profile<> sp;
   * sp.init(xDef.begin(), xDef.end());
   * @endcode
   *
   * Then, you can add the samples (Xk, Yk):
   * @code
   * sp.addValue(0, 23.0);
   * sp.addValue(0, 20.0);
   * sp.addValue(1, 20.2);
   * sp.addValue(2, 10.4);
   * ...
   * sp.addValue(9, 20);
   * // then you can get a profile:
   * std::vector<double> x; 
   * std::vector<double> y;
   * sp.getProfile(x, y); 
   * @endcode
   *
   * To obtain a profile given in log space, you just have to define the following basic log functor:
   *
   * @code 
   *  struct LogFct{
   *   double operator()(const double &a) const {
   *     return log(a);
   *    }
   *  };
   *
   * @endcode
   *
   *
   * And then you can construct a profile as previously:
   * @code 
   *  Profile<LogFct> pLog;
   *  pLog.init(10);
   *   ...
   *  @endcode
   *
   * @tparam TValueFunctor the type of the functor applied in the resulting Profile (any model of CUnaryFunctor)
   * @tparam TValue the type value stored in the profile.  
   * 
   * The proposed implementation is mainly a backport from
   * [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene) with some
   * various refactoring.
   */

  template<typename TValueFunctor = functors::Identity, typename TValue = double >
  class Profile
  {
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Used to specify the method to compute the profile values
     * (used in @ref getProfile())
     * 
     **/
    enum ProfileType{MEAN, MAX, MIN, MEDIAN};

    /**
     * The type of the functor applied to the resulting Profile
     **/
    typedef TValueFunctor Functor;

    /**
     * The type value stored in the profile.  
     **/
    typedef TValue Value;

    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<Functor, Value, Value>  ));

    
    /**
     * Destructor.
     */
    ~Profile();

    /**
     * Constructor. The object is not valid.
     */
    Profile();


    /**
     * Constructor. The object is not valid.
     * @param[in] type allows to specify the used to computes the profile points from the added samples.
     */
    Profile(ProfileType type);
    

    /**
     * Copy constructor.
     * @param[in] other the object to clone.
     */
    Profile( const Profile & other );


    /**
     * Assignment.
     * @param[in] other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Profile & operator= ( const Profile & other );


 
    /**
     * Clears the object as if it has been just created.
     */
    void clear();



    /**
     * Initializer. Must be called before adding datas. Specifies the
     * X values  of the profile (generally an iterator on a sequence
     * (1,2,3,4,...N)).
     *
     * @param[in] beginXvalues an iterator pointing on the first X value.
     * @param[in] endXvalues an iterator pointing after the last X value.
     * @param[in] storeValsInStats flag to store values in statistics (so that 
     *    the median value is accessible (default false)). 
     */
    template <typename Iterator>
    void init(  Iterator beginXvalues,  Iterator endXvalues, 
                const bool storeValsInStats=false );



    /**
     * Initializer. Must be called before adding datas. Specifies the
     * X values of the profile as the sequence (1,2,3,4,...,nb).
     *
     * @param[in] nb an integer number strictly positive.
     * @param[in] storeValsInStats flag to store values in statistics (so that 
     *   the median value is accessible (default false)). 
     */
    void init( const unsigned int nb, const bool storeValsInStats=false );
    

    /**
     * Adds some sample value at the given X value.
     *
     * @param[in] indexX some valid index (according to init).
     * @param[in] value any value.
     */
    void addValue( const unsigned int indexX, const TValue value );
    

    /**
     * Adds some statistic at the given X value.
     *
     * @param[in] indexX some valid index (according to init).
     * @param[in] stat any statistic (which is added to the current
     * statistic object).
     */
    void addStatistic( const unsigned int indexX, const Statistic<Value> & stat );



    /**
     * It stops and Erase the stats saved values. It must be called to
     * avoid to store all statistics values when we have to access to
     * the median value.  Typically if you nedd to access to the
     * median value of the profile, you need to follow this example:
     * @code
     * Profile sp;
     * // the value are now stored and you can access to the median value of the profile.
     * sp.init(true);
     * sp.addValue(0, 10.5);
     * sp.addValue(0, 9.2);
     *  ...
     * // When all values have been added you can stop to store them again
     * sp.stopStatsSaving();
     * // before erasing all statistics data, the median is computed and stored.
     * @endcode
     **/
    void stopStatsSaving() ;    




    // ----------------------- Profile services --------------------------------
  public:
    
    /**
     * Used to define the method to determine the profile values from
     * the samples of X  statistics.
     * 
     * @param[in] type the method applied to the statistics samples: MEAN, MAX, MIN.
     **/    
    void setType(const ProfileType type);
    

    
    /**
     * @param[out] x (modified) adds the x-value of the profile 
     * to the back of the vector.
     *
     * @param[out] y (modified) adds the y-value of the profile
     * (log(Exp(samples))) to the back of the vector.
     */
    void getProfile( std::vector<Value> & x, 
		     std::vector<Value> & y ) const;
    
    


    

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

    Functor myFunctor;
    
    /**
     * The vector containing the different X samples for the analysis.
     */
    std::vector<Value>* myXsamples;

    /**
     * The vector containing the different statistics for the analysis.
     */
    std::vector< Statistic<Value> >* myStats;

    /**
     * Used to define the method to compute the profile: several choice are possible:
     * MEAN (default), MAX, MIN (not efficient) or MEDIAN.
     */    
    ProfileType myProfileDef;
    


    /**
     * Used to temporaly store values in statistics in order to be
     * able to access to the median value. By default the value is set
     * to false and the median is not available. 
     * @see setStoreStats
     */
    bool myStoreValInStats;
    


    // ------------------------- Hidden services ------------------------------
  protected:


  private:

  

 
    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Profile


  /**
   * Overloads 'operator<<' for displaying objects of class 'Profile'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Profile' to write.
   * @return the output stream after the writing.
   */
  template< typename TValueFunctor, typename TValue >
  std::ostream&
  operator<< ( std::ostream & out, const Profile<TValueFunctor, TValue> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/math/Profile.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Profile_h

#undef Profile_RECURSES
#endif // else defined(Profile_RECURSES)
