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

/**
* @file testContainerTraits.cpp
* @ingroup Tests
* @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
* Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
*
* @date 2015/08/28
*
* This file is part of the DGtal library
*/

/**
 * Description of testContainerTraits' <p>
 * Aim: simple tests of module \ref ContainerTraits.h with Catch unit test framework.
 */
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <forward_list>
#include <array>
#include <unordered_set>
#include <unordered_map>

#include "DGtal/base/Common.h"
#include "DGtal/base/ContainerTraits.h"

#include "DGtalCatch.h"

using namespace DGtal;
using namespace std;


TEST_CASE( "int container traits", "[int][traits]" )
{
  typedef int Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == false) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::vector<> container traits", "[vector][traits]" )
{
  typedef std::vector<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == true) );
      REQUIRE( (IsAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::list<> container traits", "[list][traits]" )
{
  typedef std::list<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == true) );
      REQUIRE( (IsAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::deque<> container traits", "[deque][traits]" )
{
  typedef std::deque<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == true) );
      REQUIRE( (IsAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::forward_list<> container traits", "[forward_list][traits]" )
{
  typedef std::forward_list<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == true) );
      REQUIRE( (IsAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::array<> container traits", "[array][traits]" )
{
  typedef std::array<int, 10> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == true) );
      REQUIRE( (IsAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::set<> container traits", "[set][traits]" )
{
  typedef std::set<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::multiset<> container traits", "[multiset][traits]" )
{
  typedef std::multiset<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == true) );
    }
}

TEST_CASE( "std::map<> container traits", "[map][traits]" )
{
  typedef std::map<int,int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::multimap<> container traits", "[multimap][traits]" )
{
  typedef std::multimap<int,int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == true) );
    }
}

TEST_CASE( "boost::unordered_set<> container traits", "[unordered_set][traits]" )
{
  typedef boost::unordered_set<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "boost::unordered_map<> container traits", "[unordered_map][traits]" )
{
  typedef boost::unordered_map<int,int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "boost::unordered_multiset<> container traits", "[unordered_multiset][traits]" )
{
  typedef boost::unordered_multiset<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == true) );
    }
}

TEST_CASE( "boost::unordered_multimap<> container traits", "[unordered_multimap][traits]" )
{
  typedef boost::unordered_multimap<int,int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == true) );
    }
}

TEST_CASE( "std::unordered_set<> container traits", "[unordered_set][traits]" )
{
  typedef std::unordered_set<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}
TEST_CASE( "std::unordered_multiset<> container traits", "[unordered_multiset][traits]" )
{
  typedef std::unordered_multiset<int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == true) );
    }
}

TEST_CASE( "std::unordered_map<> container traits", "[unordered_map][traits]" )
{
  typedef std::unordered_map<int,int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == false) );
    }
}

TEST_CASE( "std::unordered_multimap<> container traits", "[unordered_multimap][traits]" )
{
  typedef std::unordered_multimap<int,int> Container;
  SECTION( "Checking container traits" )
    {
      REQUIRE( (IsContainer< Container >::value == true) );
      REQUIRE( (IsSequenceContainer< Container >::value == false) );
      REQUIRE( (IsAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsOrderedAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsUnorderedAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsSimpleAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsPairAssociativeContainer< Container >::value == true) );
      REQUIRE( (IsUniqueAssociativeContainer< Container >::value == false) );
      REQUIRE( (IsMultipleAssociativeContainer< Container >::value == true) );
    }
}

/** @ingroup Tests **/
