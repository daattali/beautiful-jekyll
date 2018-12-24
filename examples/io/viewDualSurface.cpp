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
 * @file io/viewDualSurface.cpp
 * @ingroup Examples
 *
 * @date 2011/03/25
 *
 * An example file named viewDualSurface.
 *
 * This file is part of the DGtal library.
 */


/**
 *  Example of viewing dual surfaces in Viewer3D.  
 *  \image html viewDualSurface.png " " 
 *  \example io/viewDualSurface.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "ConfigExamples.h"
#include "DGtal/io/viewers/Viewer3D.h"


using namespace std;
using namespace DGtal;
using namespace Z3i;



template <typename Vector>
Vector wedge( const Vector & v1, const Vector & v2 )
{
  return Vector( v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ],
                 v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ],
                 v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ] );
}

template <typename Vector>
struct LessThanOnFace
{
  Vector N; // expected normal
  Vector P; // origin or first point
  const std::vector< Vector > & pts;
  inline LessThanOnFace( const Vector & aN, const Vector & aP,
                         const std::vector< Vector > & aPts )
    : N( aN ), P( aP ), pts( aPts )
  {}
  inline bool operator()( unsigned int i1, unsigned int i2 ) const
  {
    return N.dot( wedge( pts[ i1 ] - P, pts[ i2 ] - P ) ) > 0;
  }
};

// Very naive convex hull algorithm.  O(n^4) complexity ! But very
// short. Takes care also of polygonal faces.
template <typename Vector>
void naiveConvexHull
( std::vector< std::vector< unsigned int > > & indices,
  const std::vector<Vector> & points, bool left_handed )
{
  typedef typename Vector::Component Scalar;
  // Checks all triplets of points.
  std::vector< unsigned int > aFace;
  for ( unsigned int i1 = 0; i1 < points.size(); ++i1 )
    for ( unsigned int i2 = 0; i2 < points.size(); ++i2 )
      if ( i1 != i2 )
        for ( unsigned int i3 = i1 > i2 ? i1+1 : i2+1; i3 < points.size(); ++i3 )
          {
            Vector P12 = points[ i2 ] - points[ i1 ];
            Vector P13 = points[ i3 ] - points[ i1 ];
            Vector N = wedge( P12, P13 );
            if ( N == Vector::zero ) continue;

            unsigned int nbBadPos = 0;
            for ( unsigned int i4 = 0; i4 < points.size(); ++i4 )
              {
                Vector P14 = points[ i4 ] - points[ i1 ];
                Scalar c = N.dot( P14 );
                if ( c == 0 ) aFace.push_back( i4 );
                else if ( ( left_handed && ( c > 0 ) )
                          || ( ! left_handed && ( c < 0 ) ) )
                  ++nbBadPos;
              }
            if ( nbBadPos == 0 )
              {
                LessThanOnFace<Vector> LTOF( N, points[ aFace[ 0 ] ], points );
                std::sort( ++aFace.begin(), aFace.end(), LTOF );
                indices.push_back( aFace );
              }
            aFace.clear();
          }
  // purge faces.
  for ( unsigned int i = 0; i < indices.size(); ++i )
    {
      auto s = indices[ i ].size();
      for ( unsigned int j = i+1; j < indices.size(); )
        {
          if ( indices[ j ].size() == s )
            {
              bool equal = true;
              for ( unsigned int k = 0; equal && ( k < s ); ++k )
                if ( indices[ i ][ k ] != indices[ j ][ k ] )
                  equal = false;
              if ( equal )
                {
                  std::swap( indices[ j ], indices.back() );
                  indices.pop_back();
                }
              else
                ++j;
            }
          else ++j;
        }
    }
}

double rescale( double x )
{
  return ( x - 1.0 ) * 0.5 + 0.5;
}

template <typename Viewer,
          typename Vector>
void viewPolygons
( Viewer & viewer,
  const DGtal::Color & color,
  const std::vector< std::vector< unsigned int > > & indices,
  const std::vector<Vector> & points )
{
  typedef typename Viewer::RealPoint RealPoint;
  std::vector<RealPoint> pts3d;
  DGtal::Color fillColorSave = viewer.getFillColor();
  for ( unsigned int f = 0; f < indices.size(); ++f )
    {
      pts3d.clear();
      RealPoint P;
      for ( unsigned int v = 0; v < indices[ f ].size(); ++v )
        {
          unsigned int i = indices[ f ][ v ];
          P[0] = rescale( points[ i ][ 0 ] );
          P[1] = rescale( points[ i ][ 1 ] );
          P[2] = rescale( points[ i ][ 2 ] );
          pts3d.push_back( P );
        }
      viewer.setFillColor(color);
      viewer.addPolygon( pts3d );
    }
}

template <typename Vector>
unsigned int dim( const Vector & z )
{
  unsigned int d = 0;
  for ( unsigned int i = 0; i < Vector::dimension; ++i )
    if ( ( z[ i ] % 2 ) == 1 ) ++d;
  return d;
}

template <typename Vector>
unsigned int openDim( const Vector & z )
{
  for ( unsigned int i = 0; i < Vector::dimension; ++i )
    if ( ( z[ i ] % 2 ) == 1 ) return i;
  return Vector::dimension;
}
template <typename Vector>
Vector lower( const Vector & z, unsigned int k )
{
  Vector z2( z );
  --z2[ k ];
  return z2;
}
template <typename Vector>
Vector upper( const Vector & z, unsigned int k )
{
  Vector z2( z );
  ++z2[ k ];
  return z2;
}

template <typename Vector>
unsigned int nbLighted( std::map< Vector, bool > & f,
                const Vector & z )
{ // z of dim >=2
  unsigned int d = dim( z );
  if ( d == 0 ) return f[ z ] ? 1 : 0;
  unsigned int i = openDim( z );
  return nbLighted( f, lower( z, i ) )
    + nbLighted( f, upper( z, i ) );
}


// Most similar to convex hull... but not exactly, e.g. cfg 31.
template <typename Vector>
bool lightBetween( std::map< Vector, bool > & f,
                   const Vector & z )
{
  unsigned int d = dim( z );
  if ( d == 0 ) return f[ z ];
  else if ( d == 1 )
    {
      unsigned int i = openDim( z );
      return f[ lower( z, i ) ] || f[ upper( z, i ) ];
    }
  else
    {
      Vector v1, v2;
      for ( unsigned int i = 0; i < Vector::dimension; ++i )
        {
          v1[ i ] = ( ( z[ i ] % 2 ) == 1 ) ? z[ i ] - 1 : z[ i ];
          v2[ i ] = ( ( z[ i ] % 2 ) == 1 ) ? z[ i ] + 1 : z[ i ];
        }
      Domain domain( v1, v2 );
      for ( Domain::ConstIterator it = domain.begin(), itE = domain.end();
            it != itE; ++it )
        {
          if ( *it == z ) break;
          Point zp = z*2 - *it;
          // std::cerr << *it << " <--> " << zp << std::endl;
          if ( lightBetween( f, *it ) && lightBetween( f, zp ) )
            return true;
        }
      return false;
    }

}


template <typename Vector>
bool lightMax( std::map< Vector, bool > & f,
               const Vector & z )
{
  unsigned int d = dim( z );
  if ( d == 0 ) return f[ z ];
  else if ( d == 1 )
    {
      unsigned int i = openDim( z );
      return f[ lower( z, i ) ] || f[ upper( z, i ) ];
    }
  else // if ( d > 1 )
    {
      unsigned int n = nbLighted( f, z );
      return n >= 2;
    }
}
template <typename Vector>
bool lightMinMax( std::map< Vector, bool > & f,
                  const Vector & z )
{
  unsigned int d = dim( z );
  if ( d == 0 ) return f[ z ];
  else
    {
      Vector tmp( z );
      bool val = true;
      for ( unsigned i = 0; i < d; ++i )
        {
          unsigned int k = openDim( tmp );
          tmp = lower( tmp, k );
          val = val && ( lightMinMax( f, lower( z, k ) ) || lightMinMax( f, upper( z, k ) ) );
        }
      return val;
    }
}
template <typename Vector>
bool lightMaxMin( std::map< Vector, bool > & f,
                  const Vector & z )
{
  unsigned int d = dim( z );
  if ( d == 0 ) return f[ z ];
  else
    {
      Vector tmp( z );
      bool val = false;
      for ( unsigned i = 0; i < d; ++i )
        {
          unsigned int k = openDim( tmp );
          tmp = lower( tmp, k );
          val = val || ( lightMaxMin( f, lower( z, k ) ) && lightMaxMin( f, upper( z, k ) ) );
        }
      return val;
    }
}

template <typename Vector>
bool lightEpsilon( std::map< Vector, bool > & f,
                   const Vector & z,
                   unsigned int epsilon )
{
  unsigned int d = dim( z );
  if ( d == 0 ) return f[ z ];
  else
    {
      Vector tmp( z );
      bool eps_d = ( ( epsilon >> (d-1)) & 1 ) != 0;
      bool val = eps_d ? true : false;
      for ( unsigned i = 0; i < d; ++i )
        {
          unsigned int k = openDim( tmp );
          tmp = lower( tmp, k );
          if ( eps_d )
            val = val && ( lightEpsilon( f, lower( z, k ), epsilon )
                           || lightEpsilon( f, upper( z, k ), epsilon ) );
          else
            val = val || ( lightEpsilon( f, lower( z, k ), epsilon )
                           && lightEpsilon( f, upper( z, k ), epsilon ) );
        }
      return val;
    }
}


template <typename Vector>
void fillCfg( std::map< Vector, bool > & f,
              const Vector & z,
              unsigned int cfg )
{
  unsigned int d = dim( z );
  if ( d == 0 )
    {
      f[ z ] = (cfg == 1);
      //std::cerr << "f[" << z << "] = " << f[ z ] << std::endl;
    }
  else
    {
      unsigned n = 1 << ( d - 1 );
      unsigned int cfgLow = 0;
      unsigned int cfgUp  = 0;
      for ( unsigned int j = 0; j < n; ++j )
        {
          cfgLow += ( cfg & 1 ) << j;
          cfg >>= 1;
          cfgUp += ( cfg & 1 ) << j;
          cfg >>= 1;
        }
      unsigned int i = openDim( z );
      fillCfg( f, lower( z, i ), cfgLow );
      fillCfg( f, upper( z, i ), cfgUp );
    }
}

template <typename Vector>
void localDualVolume( std::vector<Vector> & points,
                      std::map< Vector, bool > & f,
                      const Vector & z )
{
  points.clear();
  Z3i::Domain domain( z, z + Vector::diagonal(1) );
  for ( Z3i::Domain::ConstIterator it = domain.begin(), itE = domain.end();
        it != itE; ++it )
    {
      if ( f[ *it ] ) points.push_back( *it );
    }
}

template <typename Vector>
struct ConfigPointPredicate
{
  std::map< Vector, bool > & fct;
  Vector base;
  ConfigPointPredicate( std::map< Vector, bool > & aFct, Vector aBase )
    : fct( aFct ), base( aBase )  {}
  bool operator()( const Vector & p ) const
  {
    return fct[ p * 2 + base];
  }
};

int main( int argc, char** argv )
{
  typedef KSpace::CellSet CellSet;
  QApplication application(argc,argv);

  KSpace KS;

  Viewer3D<Z3i::Space,Z3i::KSpace> viewer(KS);
  viewer.show();
  DGtal::Color fillColor( 200, 200, 220, 255 );
  DGtal::Color surfelColor( 255, 0, 0, 150 );
  DGtal::Color voxelColor( 150, 150, 0, 150 );

  std::vector<Vector> pts;

  unsigned int cfg = argc > 1 ? atoi( argv[1] ) : 0;
  unsigned int cfg2 = argc > 2 ? atoi( argv[2] ) : 255;
  std::map< Vector, bool > f;
  for ( unsigned int y = 0; (y < 16) && (cfg <= cfg2); ++y )
    for ( unsigned int x = 0; (x < 16) && (cfg <= cfg2); ++x, ++cfg )
      {
        Vector offset( x*6, y*6, 0 );
        fillCfg( f, offset + Vector( 1, 1, 1 ), cfg );
        Domain domain( offset + Vector( 0, 0, 0), offset + Vector( 2, 2, 2 ) );
        KSpace K;
        K.init( Vector( 0, 0, 0), Vector( 2, 2, 2 ), true );
        ConfigPointPredicate<Vector> cpp( f, offset );
        CellSet aBoundary;
        Surfaces<KSpace>::uMakeBoundary( aBoundary, K, cpp, Vector( 0, 0, 0), Vector( 1, 1, 1 ) );
        for ( CellSet::const_iterator it = aBoundary.begin(), itE = aBoundary.end();
              it != itE; ++it )
          {
            viewer << CustomColors3D( surfelColor, surfelColor );
            viewer << KS.uTranslation( *it, offset/2 );
          }
        for ( Domain::ConstIterator it = domain.begin(), itE = domain.end();
              it != itE; ++it )
          {
            // lightEpsilon( f, *it, 5 ); // {1,-1,1}=5 // interesting
            f[ *it ] = lightBetween( f, *it );
          }
        viewer << CustomColors3D( DGtal::Color( 255, 0, 0, 255 ), fillColor );
        std::vector< std::vector< unsigned int > > indices;
        Domain domain2( offset + Vector( 0, 0, 0), offset + Vector( 1, 1, 1 ) );

        for ( Domain::ConstIterator it = domain.begin(), itE = domain.end();
              it != itE; ++it )
          {
            localDualVolume( pts, f, *it );
            indices.clear();
            naiveConvexHull( indices, pts, false ); // right_handed
            viewPolygons( viewer, fillColor, indices, pts );
            }
      }
  viewer << Viewer3D<>::updateDisplay;

  return application.exec();
}
