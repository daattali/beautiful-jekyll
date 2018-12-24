#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i; 

int main(int /*argc*/, char** /*argv*/)
{
  


////////////////////////////////////////
  Board2D board;
  board.setUnit(Board2D::UCentimeter);
  board.drawArc(0.0, 1.0, 5.0, 0, M_PI/2.0, false); 
  board.drawArc(0.0, 1.0, 4.0, 0, M_PI/2.0, true); 
  board.drawArc(0.0, 1.0, 3.0, -0.5, M_PI/2.0-0.5, false); 
  board.drawArc(0.0, 1.0, 2.0, 0.5, M_PI/2.0+0.5, false); 
  board.saveEPS( "essai.eps" );
  board.saveSVG( "essai.svg" );  
  board.saveTikZ( "essai.tikz" );
#ifdef WITH_CAIRO
    board.saveCairo("essai.pdf", Board2D::CairoPDF);
#endif
////////////////////////////////////////

  return 0;
}

