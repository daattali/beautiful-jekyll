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
 * @file io/viewers/viewer3D-11-extension.cpp
 * @ingroup examples/3dViewer
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/03/05
 *
 * Simple example of class Viewer3D.
 *
 * This file is part of the DGtal library.
 */

/**
 * Example of extension of Viewer3D interface by deriving the class
 * Viewer3D::Extension.  Here we have added a callback to the
 * "Shift+R" keypressed event, which adds a point randomly in the domain.
 *
 * @see moduleQGLExtension
 * \example io/viewers/viewer3D-11-extension.cpp
 * \image html simple3dVisu1.png "Extending the Viewer3D interface: just press
 * Shift+R and you have new points added randomly in the scene."
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/viewers/Viewer3D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

//! [viewer3D-extension-derivation]
// Deriving from Viewer3D::Extension to add new callbacks to events.
struct RandomPointKeyExtension : public Viewer3D<Space, KSpace>::Extension
{
  RandomPointKeyExtension()
  {
  }

  // Here we override the "key pressed" event, and a point randomly in
  // the scene if the key "Shift+R" is pressed.
  virtual bool keyPressEvent( Viewer & viewer, QKeyEvent * event )
  {
    bool handled = false;
    // Get event modifiers key
    const Qt::KeyboardModifiers modifiers = event->modifiers();
    if ( ( event->key() == Qt::Key_R ) && ( modifiers == Qt::ShiftModifier ) )
    {
      Point p = viewer.space().lowerBound();
      Point q = viewer.space().upperBound();
      Point d = q - p;
      Point a( ( rand() % d[ 0 ] ) + p[ 0 ], ( rand() % d[ 1 ] ) + p[ 1 ],
               ( rand() % d[ 2 ] ) + p[ 2 ] );
      viewer << a;
      viewer << Viewer::updateDisplay;
      trace.info() << "Adding point " << a << std::endl;
      handled = true;
    }
    return handled;
  }

  // We also override the Viewer3D::init method to add a key
  // description in the help window.
  virtual void init( Viewer & viewer )
  {
    viewer.setKeyDescription( Qt::ShiftModifier + Qt::Key_R,
                              "Creates a random digital point." );
  }

  // We also override the Viewer3D::helpString method to add a
  // description to the viewer.
  virtual QString helpString( const Viewer & /*viewer*/ ) const
  {
    QString text( "<h2> Random point Viewer3D </h2>" );
    text += "Press Shift+R to add points.";
    return text;
  }
};
//! [viewer3D-extension-derivation]

int main( int argc, char ** argv )
{

  QApplication application( argc, argv );

  Point p1( 0, 0, 0 );
  Point p2( 5, 5, 5 );
  Point p3( 2, 3, 4 );
  Domain domain( p1, p2 );

  typedef Viewer3D<> MyViewer;
  KSpace K;
  K.init( p1, p2, true );
  //! [viewer3D-extension-set-extension]
  MyViewer viewer( K );
  viewer.setExtension( new RandomPointKeyExtension );
  //! [viewer3D-extension-set-extension]
  viewer.show();
  viewer << domain;
  viewer << p1 << p2 << p3;

  viewer << MyViewer::updateDisplay;
  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
