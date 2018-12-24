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

#include <iostream>
#include <vector>
#include <gmpxx.h>

using namespace std;


int main()
{
  mpz_class  a, b, c;

  a = 1234;
  b = "-5678";
  c = a+b;

  std::cout << "Displaying a BigInteger : "<< a <<" " <<b << " " <<c<<std::endl;

  return 0;
}
