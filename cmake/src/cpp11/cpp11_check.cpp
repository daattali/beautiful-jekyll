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

#include <cstddef>
#include <array>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <tuple>
#include <type_traits>

// Templated aliases & tuple
template < typename T >
using Record = std::tuple< double, char, T >;

// Delayed return type & decltype.
template < typename U, typename V >
constexpr auto AddIt( U u, V v ) -> decltype( u + v ) { return u + v; }

int main()
{
  constexpr auto N = 5u;      // constexpr & auto
  std::array<int, N> myArray; // array
  std::vector<int> myVector = {1, 2, 3, 4, 5}; // initializer list

  // Range-based loop
  for ( auto & v : myVector )
    v += N;

  // New algorithms and lambdas
  bool valid = std::all_of( myVector.begin(), myVector.end(), [&N] ( int v ) { return v > N; } );

  // decltype, declval & rvalue ref
  decltype( std::declval< std::vector<int> >()[0] ) && b = myVector[3];

  // Unordered set
  std::unordered_set<int> mySet;
  std::unordered_multiset<int> myMultiSet;

  // Unordered map
  std::unordered_map<int, int> myMap;

  // Forward list
  std::forward_list< Record<int> > myList;

  // variadic template & std::forward
  myList.emplace_front( 3.14, 'a', 3 );

  // type_traits & move
  constexpr bool isMovable = std::is_move_assignable< decltype( AddIt(3, 3.14) ) >::value;

  // nullptr
  int* ptr = nullptr;


  return 0;
}
