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
 * @file DigitalSetInserter.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/15
 *
 * Header file for module DigitalSetInserter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSetInserter_RECURSES)
#error Recursive header files inclusion detected in DigitalSetInserter.h
#else // defined(DigitalSetInserter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSetInserter_RECURSES

#if !defined DigitalSetInserter_h
/** Prevents repeated inclusion of headers. */
#define DigitalSetInserter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "DGtal/kernel/sets/CDigitalSet.h"

#include <iostream>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalSetInserter
  /**
   * Description of template class 'DigitalSetInserter' <p>
   * \brief Aim: this output iterator class is designed to 
   * allow algorithms to insert points in the digital set.
   * Using the assignment operator, even when dereferenced, 
   * causes the digital set to insert a point. 
   *
   * @tparam TDigitalSet any model of CDigitalSet
   */
  template <typename TDigitalSet>
  class DigitalSetInserter:
    public std::iterator<std::output_iterator_tag,void,void,void,void>
{

    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSet<TDigitalSet> )); 

    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Constructor.
     * @param aSet any digital set
     */
  explicit DigitalSetInserter (TDigitalSet& aSet)
    : mySet(&aSet) {}

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Assignment operator.
     * @param aPoint the point to insert
     */
  DigitalSetInserter<TDigitalSet>& operator= (typename TDigitalSet::Point aPoint)
    { mySet->insert(aPoint); return *this; }

    /**
     * Dereference operator
     * @return a reference to *this
     */
  DigitalSetInserter<TDigitalSet>& operator* ()
    { return *this; }
    /**
     * Pre-increment operator
     * @return a reference to *this
     */
  DigitalSetInserter<TDigitalSet>& operator++ ()
    { return *this; }
    /**
     * Post-increment operator
     * @return *this
     */
  DigitalSetInserter<TDigitalSet> operator++ (int)
    { return *this; }


    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Aliasing pointer on the underlying set
     */
  TDigitalSet* mySet;

  }; // end of class DigitalSetInserter

}
///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
//#include "DGtal/images/DigitalSetInserter.ih"

//
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSetInserter_h

#undef DigitalSetInserter_RECURSES
#endif // else defined(DigitalSetInserter_RECURSES)
