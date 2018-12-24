#include "DGtal/math/linalg/EigenSupport.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusSolver.h"
#include "DGtal/dec/DiscreteExteriorCalculusFactory.h"

#define NOVIEWER // comment to enable 3d viewers

#if !defined(NOVIEWER)
#include "DGtal/io/viewers/Viewer3D.h"
#endif
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

using namespace DGtal;
using namespace std;
using namespace Eigen;

template <typename OperatorAA, typename OperatorBB>
bool
equal(const OperatorAA& aa, const OperatorBB& bb)
{
    return MatrixXd(aa.myContainer) == MatrixXd(bb.myContainer);
}

int main(int , char** )
{
#if !defined(NOVIEWER)
    typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
#endif
    //! [embedding_factory]
    typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;
    //! [embedding_factory]

#if !defined(NOVIEWER)
    QApplication app(argc, argv);
    Z3i::KSpace kspace_3d;
#endif
    Z2i::KSpace kspace_2d;

#if !defined(NOVIEWER)
    Viewer viewer1(kspace_3d);
    viewer1.show();
    viewer1.setWindowTitle("embedding_1d_calculus_3d");
    viewer1.camera()->setPosition( Vec(2,2,2) );
    viewer1.camera()->setUpVector( Vec(0,0,1), false );
    viewer1.camera()->lookAt( Vec(0,0,0) );

    Viewer viewer2(kspace_3d);
    viewer2.show();
    viewer2.setWindowTitle("embedding_2d_calculus_3d");
    viewer2.camera()->setPosition( Vec(2,2,2) );
    viewer2.camera()->setUpVector( Vec(0,0,2), false );
    viewer2.camera()->lookAt( Vec(0,0,0) );

    Viewer viewer3(kspace_3d);
    viewer3.show();
    viewer3.setWindowTitle("embedding_2d_calculus_3d_no_border");
    viewer3.camera()->setPosition( Vec(2,2,2) );
    viewer3.camera()->setUpVector( Vec(0,0,2), false );
    viewer3.camera()->lookAt( Vec(0,0,0) );
#endif

    {
        trace.beginBlock("1d manifold embedding");

        //! [embedding_1d_typedef]
        typedef DiscreteExteriorCalculus<1, 1, EigenLinearAlgebraBackend> Calculus1D;
        typedef DiscreteExteriorCalculus<1, 2, EigenLinearAlgebraBackend> Calculus2D;
        typedef DiscreteExteriorCalculus<1, 3, EigenLinearAlgebraBackend> Calculus3D;
        //! [embedding_1d_typedef]

        //! [embedding_1d_cells_1d]
        typedef std::set<Calculus1D::SCell> SCells1D;
        SCells1D ncells_1d_factory;
        //! [embedding_1d_cells_1d]
        SCells1D cells_1d_manual;
        Calculus1D calculus_1d_manual;
        for (int kk=0; kk<31; kk++)
        {
            Calculus1D::KSpace::Point point;
            point[0] = kk;
            const Calculus1D::SCell cell = calculus_1d_manual.myKSpace.sCell(point);
            calculus_1d_manual.insertSCell(cell, 1, kk == 0 || kk == 30 ? 1/2. : 1);
            cells_1d_manual.insert(cell);
            if (kk%2 != 0) ncells_1d_factory.insert(cell);
        }
        calculus_1d_manual.updateIndexes();
        trace.info() << "calculus_1d_manual=" << calculus_1d_manual << endl;

        {
            Board2D board;
            board << Z2i::Domain(Z2i::Point(-1,-1), Z2i::Point(15,0));
            board.setFillColor( DGtal::Color(128,128,128) );
            for (Calculus1D::ConstIterator ii=calculus_1d_manual.begin(), ie=calculus_1d_manual.end(); ii!=ie; ii++)
            {
                const Z2i::Point point(calculus_1d_manual.myKSpace.uKCoord(ii->first, 0), 0);
                const Z2i::KSpace::SCell cell = kspace_2d.sCell(point);
                Display2DFactory::drawDECSignedKhalimskyCell(board, cell);
            }
            board.saveSVG("embedding_1d_calculus_1d.svg");
        }

        //! [embedding_1d_factory_1d]
        const Calculus1D calculus_1d_factory = CalculusFactory::createFromNSCells<1>(ncells_1d_factory.begin(), ncells_1d_factory.end(), true);
        //! [embedding_1d_factory_1d]
        trace.info() << "calculus_1d_factory=" << calculus_1d_factory << endl;

        Calculus2D calculus_2d_manual;
        {
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,0)), 1, 1/2. );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,1), Calculus2D::KSpace::POS) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(7,2), Calculus2D::KSpace::POS) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,1), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,0)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,-1), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,-2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(7,-2), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,-2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(5,-2), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(4,-2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(3,-2), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,-2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,-2), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(0,-2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-1,-2), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,-2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,-1), Calculus2D::KSpace::POS) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,0)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,1), Calculus2D::KSpace::POS) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-1,2), Calculus2D::KSpace::POS) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(0,2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,2), Calculus2D::KSpace::POS) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,2)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,1), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,0)) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,0), Calculus2D::KSpace::NEG) );
            calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(0,0)), 1, 1/2.);
            calculus_2d_manual.updateIndexes();
        }
        trace.info() << "calculus_2d_manual=" << calculus_2d_manual << endl;

        {
            Board2D board;
            board << Z2i::Domain(Z2i::Point(-2,-2), Z2i::Point(4,1));
            board << calculus_2d_manual;
            board.saveSVG("embedding_1d_calculus_2d.svg");
        }

        //! [embedding_1d_cells_2d]
        typedef std::list<Calculus2D::SCell> SCells2D;
        SCells2D ncells_2d_factory;
        //! [embedding_1d_cells_2d]

        {
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,1), Calculus2D::KSpace::POS) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(7,2), Calculus2D::KSpace::POS) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,1), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,-1), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(7,-2), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(5,-2), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(3,-2), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,-2), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-1,-2), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,-1), Calculus2D::KSpace::POS) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,1), Calculus2D::KSpace::POS) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-1,2), Calculus2D::KSpace::POS) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,2), Calculus2D::KSpace::POS) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,1), Calculus2D::KSpace::NEG) );
            ncells_2d_factory.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,0), Calculus2D::KSpace::NEG) );
        }
        //! [embedding_1d_factory_2d]
        const Calculus2D calculus_2d_factory = CalculusFactory::createFromNSCells<1>(ncells_2d_factory.begin(), ncells_2d_factory.end(), true);
        //! [embedding_1d_factory_2d]
        trace.info() << "calculus_2d_factory=" << calculus_2d_factory << endl;

        SCells2D cells_2d_manual;
        {
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,0)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,1), Calculus2D::KSpace::POS) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(7,2), Calculus2D::KSpace::POS) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,1), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,0)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,-1), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(8,-2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(7,-2), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(6,-2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(5,-2), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(4,-2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(3,-2), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,-2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,-2), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(0,-2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-1,-2), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,-2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,-1), Calculus2D::KSpace::POS) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,0)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,1), Calculus2D::KSpace::POS) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-2,2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(-1,2), Calculus2D::KSpace::POS) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(0,2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,2), Calculus2D::KSpace::POS) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,2)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,1), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(2,0)) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(1,0), Calculus2D::KSpace::NEG) );
            cells_2d_manual.push_back( calculus_2d_manual.myKSpace.sCell(Z2i::Point(0,0)) );
        }

        Calculus3D calculus_3d_manual;
        {
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,0,0)), 1, 1/2. );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,0,0), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,0,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(3,0,0), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,0,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,1,0), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,2,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,3,0), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,4,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(3,4,0), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,4,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,4,0), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,4,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,3,0), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,2,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,2,0), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,1), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,2)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,3,2), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,4,2)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,5,2), Calculus3D::KSpace::POS) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,2)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,1), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,0)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,-1), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,-2)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,5,-2), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,4,-2)) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,3,-2), Calculus3D::KSpace::NEG) );
            calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,-2)), 1, 1/2. );
            calculus_3d_manual.updateIndexes();
        }
        trace.info() << "calculus_3d_manual=" << calculus_3d_manual << endl;

#if !defined(NOVIEWER)
        Display3DFactory<Calculus3D::KSpace::Space, Calculus3D::KSpace>::draw(viewer1, calculus_3d_manual);
        viewer1 << Viewer::updateDisplay;
#endif

        //! [embedding_1d_cells_3d]
        typedef std::vector<Calculus3D::SCell> SCells3D;
        SCells3D ncells_3d_factory;
        //! [embedding_1d_cells_3d]
        {
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,0,0), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(3,0,0), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,1,0), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,3,0), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(3,4,0), Calculus3D::KSpace::NEG) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,4,0), Calculus3D::KSpace::NEG) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,3,0), Calculus3D::KSpace::NEG) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,2,0), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,1), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,3,2), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,5,2), Calculus3D::KSpace::POS) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,1), Calculus3D::KSpace::NEG) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,-1), Calculus3D::KSpace::NEG) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,5,-2), Calculus3D::KSpace::NEG) );
            ncells_3d_factory.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,3,-2), Calculus3D::KSpace::NEG) );
        }
        //! [embedding_1d_factory_3d]
        const Calculus3D calculus_3d_factory = CalculusFactory::createFromNSCells<1>(ncells_3d_factory.begin(), ncells_3d_factory.end(), true);
        //! [embedding_1d_factory_3d]
        trace.info() << "calculus_3d_factory=" << calculus_3d_factory << endl;

        SCells3D cells_3d_manual;
        {
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,0,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,0,0), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,0,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(3,0,0), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,0,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,1,0), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,2,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,3,0), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,4,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(3,4,0), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,4,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,4,0), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,4,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,3,0), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(0,2,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(1,2,0), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,1), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,2)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,3,2), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,4,2)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,5,2), Calculus3D::KSpace::POS) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,2)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,1), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,0)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,-1), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,6,-2)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,5,-2), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,4,-2)) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,3,-2), Calculus3D::KSpace::NEG) );
            cells_3d_manual.push_back( calculus_3d_manual.myKSpace.sCell(Z3i::Point(2,2,-2)) );
        }
        trace.beginBlock("checking operators");

        const Calculus1D::PrimalIdentity0 reorder_0cell_1d = calculus_1d_manual.reorder<0, PRIMAL>(cells_1d_manual.begin(), cells_1d_manual.end());
        const Calculus2D::PrimalIdentity0 reorder_0cell_2d = calculus_2d_manual.reorder<0, PRIMAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::PrimalIdentity0 reorder_0cell_3d = calculus_3d_manual.reorder<0, PRIMAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus1D::PrimalIdentity1 reorder_1cell_1d = calculus_1d_manual.reorder<1, PRIMAL>(cells_1d_manual.begin(), cells_1d_manual.end());
        const Calculus2D::PrimalIdentity1 reorder_1cell_2d = calculus_2d_manual.reorder<1, PRIMAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::PrimalIdentity1 reorder_1cell_3d = calculus_3d_manual.reorder<1, PRIMAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus1D::DualIdentity0 reorder_0cellp_1d = calculus_1d_manual.reorder<0, DUAL>(cells_1d_manual.begin(), cells_1d_manual.end());
        const Calculus2D::DualIdentity0 reorder_0cellp_2d = calculus_2d_manual.reorder<0, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::DualIdentity0 reorder_0cellp_3d = calculus_3d_manual.reorder<0, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus1D::DualIdentity1 reorder_1cellp_1d = calculus_1d_manual.reorder<1, DUAL>(cells_1d_manual.begin(), cells_1d_manual.end());
        const Calculus2D::DualIdentity1 reorder_1cellp_2d = calculus_2d_manual.reorder<1, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::DualIdentity1 reorder_1cellp_3d = calculus_3d_manual.reorder<1, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());

        { // testing primal operators
            const Calculus1D::PrimalIdentity0 primal_laplace_1d = reorder_0cell_1d * calculus_1d_manual.laplace<PRIMAL>() * reorder_0cell_1d.transpose();
            const Calculus2D::PrimalIdentity0 primal_laplace_2d = reorder_0cell_2d * calculus_2d_manual.laplace<PRIMAL>() * reorder_0cell_2d.transpose();
            const Calculus3D::PrimalIdentity0 primal_laplace_3d = reorder_0cell_3d * calculus_3d_manual.laplace<PRIMAL>() * reorder_0cell_3d.transpose();
            trace.info() << "primal_laplace_1d=" << primal_laplace_1d << endl;
            trace.info() << "primal_laplace_2d=" << primal_laplace_2d << endl;
            trace.info() << "primal_laplace_3d=" << primal_laplace_3d << endl;
            trace.info() << "primal_laplace_container=" << endl << MatrixXd(primal_laplace_1d.myContainer) << endl;
            FATAL_ERROR( equal(
                        reorder_1cellp_1d * calculus_1d_manual.hodge<0, PRIMAL>() * reorder_0cell_1d.transpose(),
                        reorder_1cellp_2d * calculus_2d_manual.hodge<0, PRIMAL>() * reorder_0cell_2d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cellp_1d * calculus_1d_manual.hodge<0, PRIMAL>() * reorder_0cell_1d.transpose(),
                        reorder_1cellp_3d * calculus_3d_manual.hodge<0, PRIMAL>() * reorder_0cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cellp_1d * calculus_1d_manual.hodge<1, PRIMAL>() * reorder_1cell_1d.transpose(),
                        reorder_0cellp_2d * calculus_2d_manual.hodge<1, PRIMAL>() * reorder_1cell_2d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cellp_1d * calculus_1d_manual.hodge<1, PRIMAL>() * reorder_1cell_1d.transpose(),
                        reorder_0cellp_3d * calculus_3d_manual.hodge<1, PRIMAL>() * reorder_1cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cell_1d * calculus_1d_manual.derivative<0, PRIMAL>() * reorder_0cell_1d.transpose(),
                        reorder_1cell_2d * calculus_2d_manual.derivative<0, PRIMAL>() * reorder_0cell_2d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cell_1d * calculus_1d_manual.derivative<0, PRIMAL>() * reorder_0cell_1d.transpose(),
                        reorder_1cell_3d * calculus_3d_manual.derivative<0, PRIMAL>() * reorder_0cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(primal_laplace_1d, primal_laplace_2d) );
            FATAL_ERROR( equal(primal_laplace_1d, primal_laplace_3d) );
        }

        { // testing dual operators
            const Calculus1D::DualIdentity0 dual_laplace_1d = reorder_0cellp_1d * calculus_1d_manual.laplace<DUAL>() * reorder_0cellp_1d.transpose();
            const Calculus2D::DualIdentity0 dual_laplace_2d = reorder_0cellp_2d * calculus_2d_manual.laplace<DUAL>() * reorder_0cellp_2d.transpose();
            const Calculus3D::DualIdentity0 dual_laplace_3d = reorder_0cellp_3d * calculus_3d_manual.laplace<DUAL>() * reorder_0cellp_3d.transpose();
            trace.info() << "dual_laplace_1d=" << dual_laplace_1d << endl;
            trace.info() << "dual_laplace_2d=" << dual_laplace_2d << endl;
            trace.info() << "dual_laplace_3d=" << dual_laplace_3d << endl;
            trace.info() << "dual_laplace_container=" << endl << MatrixXd(dual_laplace_1d.myContainer) << endl;
            FATAL_ERROR( equal(
                        reorder_1cell_1d * calculus_1d_manual.hodge<0, DUAL>() * reorder_0cellp_1d.transpose(),
                        reorder_1cell_2d * calculus_2d_manual.hodge<0, DUAL>() * reorder_0cellp_2d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cell_1d * calculus_1d_manual.hodge<0, DUAL>() * reorder_0cellp_1d.transpose(),
                        reorder_1cell_3d * calculus_3d_manual.hodge<0, DUAL>() * reorder_0cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cell_1d * calculus_1d_manual.hodge<1, DUAL>() * reorder_1cellp_1d.transpose(),
                        reorder_0cell_2d * calculus_2d_manual.hodge<1, DUAL>() * reorder_1cellp_2d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cell_1d * calculus_1d_manual.hodge<1, DUAL>() * reorder_1cellp_1d.transpose(),
                        reorder_0cell_3d * calculus_3d_manual.hodge<1, DUAL>() * reorder_1cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cellp_1d * calculus_1d_manual.derivative<0, DUAL>() * reorder_0cellp_1d.transpose(),
                        reorder_1cellp_2d * calculus_2d_manual.derivative<0, DUAL>() * reorder_0cellp_2d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cellp_1d * calculus_1d_manual.derivative<0, DUAL>() * reorder_0cellp_1d.transpose(),
                        reorder_1cellp_3d * calculus_3d_manual.derivative<0, DUAL>() * reorder_0cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(dual_laplace_1d, dual_laplace_2d) );
            FATAL_ERROR( equal(dual_laplace_1d, dual_laplace_3d) );
        }

        { // checking dual laplace factory calculus vs manual calculus
            const Calculus1D::DualIdentity0 reorder_0cellp_1d_factory = calculus_1d_factory.reorder<0, DUAL>(cells_1d_manual.begin(), cells_1d_manual.end());
            const Calculus2D::DualIdentity0 reorder_0cellp_2d_factory = calculus_2d_factory.reorder<0, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
            const Calculus3D::DualIdentity0 reorder_0cellp_3d_factory = calculus_3d_factory.reorder<0, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());
            FATAL_ERROR( equal(
                        reorder_0cellp_1d * calculus_1d_manual.laplace<DUAL>() * reorder_0cellp_1d.transpose(),
                        reorder_0cellp_1d_factory * calculus_1d_factory.laplace<DUAL>() * reorder_0cellp_1d_factory.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cellp_2d * calculus_2d_manual.laplace<DUAL>() * reorder_0cellp_2d.transpose(),
                        reorder_0cellp_2d_factory * calculus_2d_factory.laplace<DUAL>() * reorder_0cellp_2d_factory.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cellp_3d * calculus_3d_manual.laplace<DUAL>() * reorder_0cellp_3d.transpose(),
                        reorder_0cellp_3d_factory * calculus_3d_factory.laplace<DUAL>() * reorder_0cellp_3d_factory.transpose()
                        ) );
        }

        trace.endBlock();

        trace.beginBlock("checking border");

        { // 2d ambient border
            const Calculus2D calculus_2d_factory_no_border = CalculusFactory::createFromNSCells<1>(ncells_2d_factory.begin(), ncells_2d_factory.end(), false);
            trace.info() << "calculus_2d_factory_no_border=" << calculus_2d_factory_no_border << endl;
            trace.info() << "calculus_2d_factory=" << calculus_2d_factory << endl;
            FATAL_ERROR( calculus_2d_factory.containsCell(calculus_2d_factory.myKSpace.uCell(Z2i::Point(6,0))) );
            FATAL_ERROR( !calculus_2d_factory_no_border.containsCell(calculus_2d_factory_no_border.myKSpace.uCell(Z2i::Point(6,0))) );
            FATAL_ERROR( calculus_2d_factory.containsCell(calculus_2d_factory.myKSpace.uCell(Z2i::Point(0,0))) );
            FATAL_ERROR( !calculus_2d_factory_no_border.containsCell(calculus_2d_factory_no_border.myKSpace.uCell(Z2i::Point(0,0))) );
        }

        { // 3d ambient border
            const Calculus3D calculus_3d_factory_no_border = CalculusFactory::createFromNSCells<1>(ncells_3d_factory.begin(), ncells_3d_factory.end(), false);
            trace.info() << "calculus_3d_factory_no_border=" << calculus_3d_factory_no_border << endl;
            trace.info() << "calculus_3d_factory=" << calculus_3d_factory << endl;
            FATAL_ERROR( calculus_3d_factory.containsCell(calculus_3d_factory.myKSpace.uCell(Z3i::Point(2,2,-2))) );
            FATAL_ERROR( !calculus_3d_factory_no_border.containsCell(calculus_3d_factory_no_border.myKSpace.uCell(Z3i::Point(2,2,-2))) );
            FATAL_ERROR( calculus_3d_factory.containsCell(calculus_3d_factory.myKSpace.uCell(Z3i::Point(0,0,0))) );
            FATAL_ERROR( !calculus_3d_factory_no_border.containsCell(calculus_3d_factory_no_border.myKSpace.uCell(Z3i::Point(0,0,0))) );
        }

        trace.endBlock();

        trace.beginBlock("checking area");

        {
            const Calculus2D::Scalar area_th = calculus_2d_factory.kFormLength(0, DUAL);
            const Calculus2D::Scalar area_primal = (
                calculus_2d_factory.hodge<0, PRIMAL>() *
                Calculus2D::PrimalForm0::ones(calculus_2d_factory)
                ).myContainer.array().sum();
            const Calculus2D::Scalar area_dual = (
                calculus_2d_factory.hodge<0, DUAL>() *
                Calculus2D::DualForm0::ones(calculus_2d_factory)
                ).myContainer.array().sum();
            trace.info() << "area_2d_th=" << area_th << endl;
            trace.info() << "area_2d_primal=" << area_primal << endl;
            trace.info() << "area_2d_dual=" << area_dual << endl;
            FATAL_ERROR( area_th == area_primal );
            FATAL_ERROR( area_th == area_dual );
        }

        {
            const Calculus3D::Scalar area_th = calculus_3d_factory.kFormLength(0, DUAL);
            const Calculus3D::Scalar area_primal = (
                calculus_3d_factory.hodge<0, PRIMAL>() *
                Calculus3D::PrimalForm0::ones(calculus_3d_factory)
                ).myContainer.array().sum();
            const Calculus3D::Scalar area_dual = (
                calculus_3d_factory.hodge<0, DUAL>() *
                Calculus3D::DualForm0::ones(calculus_3d_factory)
                ).myContainer.array().sum();
            trace.info() << "area_3d_th=" << area_th << endl;
            trace.info() << "area_3d_primal=" << area_primal << endl;
            trace.info() << "area_3d_dual=" << area_dual << endl;
            FATAL_ERROR( area_th == area_primal );
            FATAL_ERROR( area_th == area_dual );
        }

        trace.endBlock();

        trace.endBlock();
    }

    /*{
        trace.beginBlock("2d manifold embedding");

        //! [embedding_2d_typedef]
        typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus2D;
        typedef DiscreteExteriorCalculus<2, 3, EigenLinearAlgebraBackend> Calculus3D;
        //! [embedding_2d_typedef]

        Calculus2D calculus_2d_manual;
        {
            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+4)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+8)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+12)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+16)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+4,yy)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+8,yy)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+12,yy)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_2d_manual.insertSCell( calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+16,yy)) );

            calculus_2d_manual.updateIndexes();
        }
        trace.info() << "calculus_2d_manual=" << calculus_2d_manual << endl;

        {
            Board2D board;
            board << Z2i::Domain(Z2i::Point(-1,-1), Z2i::Point(10,10));
            board << calculus_2d_manual;
            board.saveSVG("embedding_2d_calculus_2d.svg");
        }

        //! [embedding_2d_cells_2d]
        typedef std::list<Calculus2D::SCell> SCells2D;
        SCells2D ncells_2d_factory;
        //! [embedding_2d_cells_2d]
        for (int kk=0; kk<calculus_2d_manual.kFormLength(2, PRIMAL); kk++) ncells_2d_factory.push_back( calculus_2d_manual.getSCell(2, PRIMAL, kk) );
        //! [embedding_2d_factory_2d]
        const Calculus2D calculus_2d_factory_weighed = CalculusFactory::createFromNSCells<2>(ncells_2d_factory.begin(), ncells_2d_factory.end(), true);
        //! [embedding_2d_factory_2d]
        Calculus2D calculus_2d_factory = calculus_2d_factory_weighed;
        calculus_2d_factory.resetSizes();
        trace.info() << "calculus_2d_factory=" << calculus_2d_factory << endl;

        SCells2D cells_2d_manual;
        {
            std::set<Calculus2D::SCell> already_inserted;

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+4));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+8));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+12));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx,yy+16));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+4,yy));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+8,yy));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+12,yy));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus2D::SCell cell = calculus_2d_manual.myKSpace.sCell(Z2i::Point(xx+16,yy));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_2d_manual.push_back(cell);
            }
        }

        Calculus3D calculus_3d_manual;
        {
            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,yy,0)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,4,yy)) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,4-yy,4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    yy%2 != 0 ? Calculus3D::KSpace::NEG : // y-edge
                    Calculus3D::KSpace::POS) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,-yy,4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    yy%2 != 0 ? Calculus3D::KSpace::NEG : // y-edge
                    Calculus3D::KSpace::POS) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,-4,4-yy),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    yy%2 != 0 ? Calculus3D::KSpace::NEG : // y-edge
                    Calculus3D::KSpace::POS) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,yy,-xx),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::POS : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::NEG : // x-edge
                    Calculus3D::KSpace::POS) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(4-xx,yy,-4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::NEG : // x-edge
                    Calculus3D::KSpace::POS) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(-xx,yy,-4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::NEG : // x-edge
                    Calculus3D::KSpace::POS) );

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
                calculus_3d_manual.insertSCell( calculus_3d_manual.myKSpace.sCell(Z3i::Point(-4,yy,-4+xx),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::POS : // x-edge
                    Calculus3D::KSpace::POS) );

            calculus_3d_manual.updateIndexes();
        }
        trace.info() << "calculus_3d_manual=" << calculus_3d_manual << endl;

#if !defined(NOVIEWER)
        Display3DFactory<Calculus3D::KSpace::Space, Calculus3D::KSpace>::draw(viewer2, calculus_3d_manual);
        viewer2 << Viewer::updateDisplay;
#endif

        //! [embedding_2d_cells_3d]
        typedef std::list<Calculus3D::SCell> SCells3D;
        SCells3D ncells_3d_factory;
        //! [embedding_2d_cells_3d]
        for (int kk=0; kk<calculus_3d_manual.kFormLength(2, PRIMAL); kk++) ncells_3d_factory.push_back( calculus_3d_manual.getSCell(2, PRIMAL, kk) );
        //! [embedding_2d_factory_3d]
        const Calculus3D calculus_3d_factory_weighed = CalculusFactory::createFromNSCells<2>(ncells_3d_factory.begin(), ncells_3d_factory.end(), true);
        //! [embedding_2d_factory_3d]
        Calculus3D calculus_3d_factory = calculus_3d_factory_weighed;
        calculus_3d_factory.resetSizes();
        trace.info() << "calculus_3d_factory=" << calculus_3d_factory << endl;

        SCells3D cells_3d_manual;
        {
            std::set<Calculus3D::SCell> already_inserted;

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,yy,0));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,4,yy));
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,4-yy,4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    yy%2 != 0 ? Calculus3D::KSpace::NEG : // y-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,-yy,4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    yy%2 != 0 ? Calculus3D::KSpace::NEG : // y-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(xx,-4,4-yy),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    yy%2 != 0 ? Calculus3D::KSpace::NEG : // y-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(4,yy,-xx),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::POS : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::NEG : // x-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(4-xx,yy,-4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::NEG : // x-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(-xx,yy,-4),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::NEG : // x-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }

            for (int xx=0; xx<=4; xx++)
            for (int yy=0; yy<=4; yy++)
            {
                const Calculus3D::SCell cell = calculus_3d_manual.myKSpace.sCell(Z3i::Point(-4,yy,-4+xx),
                    xx%2 != 0 && yy%2 != 0 ? Calculus3D::KSpace::NEG : // surfels
                    xx%2 != 0 ? Calculus3D::KSpace::POS : // x-edge
                    Calculus3D::KSpace::POS);
                if (already_inserted.find(cell) != already_inserted.end()) continue;
                already_inserted.insert(cell);
                cells_3d_manual.push_back(cell);
            }
        }

        trace.beginBlock("checking operators");
        trace.info() << calculus_3d_manual << endl;
        trace.info() << cells_3d_manual.size() << endl;

        const Calculus2D::PrimalIdentity0 reorder_0cell_2d = calculus_2d_manual.reorder<0, PRIMAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::PrimalIdentity0 reorder_0cell_3d = calculus_3d_manual.reorder<0, PRIMAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus2D::PrimalIdentity1 reorder_1cell_2d = calculus_2d_manual.reorder<1, PRIMAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::PrimalIdentity1 reorder_1cell_3d = calculus_3d_manual.reorder<1, PRIMAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus2D::PrimalIdentity2 reorder_2cell_2d = calculus_2d_manual.reorder<2, PRIMAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::PrimalIdentity2 reorder_2cell_3d = calculus_3d_manual.reorder<2, PRIMAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus2D::DualIdentity0 reorder_0cellp_2d = calculus_2d_manual.reorder<0, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::DualIdentity0 reorder_0cellp_3d = calculus_3d_manual.reorder<0, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus2D::DualIdentity1 reorder_1cellp_2d = calculus_2d_manual.reorder<1, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::DualIdentity1 reorder_1cellp_3d = calculus_3d_manual.reorder<1, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());
        const Calculus2D::DualIdentity2 reorder_2cellp_2d = calculus_2d_manual.reorder<2, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
        const Calculus3D::DualIdentity2 reorder_2cellp_3d = calculus_3d_manual.reorder<2, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());

        { // check primal operators
            const Calculus2D::PrimalIdentity0 primal_laplace_2d = reorder_0cell_2d * calculus_2d_manual.laplace<PRIMAL>() * reorder_0cell_2d.transpose();
            const Calculus3D::PrimalIdentity0 primal_laplace_3d = reorder_0cell_3d * calculus_3d_manual.laplace<PRIMAL>() * reorder_0cell_3d.transpose();
            trace.info() << "primal_laplace_2d=" << primal_laplace_2d << endl;
            trace.info() << "primal_laplace_3d=" << primal_laplace_3d << endl;
            trace.info() << "primal_laplace_container=" << endl << MatrixXd(primal_laplace_2d.myContainer) << endl;
            FATAL_ERROR( equal(
                        reorder_2cellp_2d * calculus_2d_manual.hodge<0, PRIMAL>() * reorder_0cell_2d.transpose(),
                        reorder_2cellp_3d * calculus_3d_manual.hodge<0, PRIMAL>() * reorder_0cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cellp_2d * calculus_2d_manual.hodge<1, PRIMAL>() * reorder_1cell_2d.transpose(),
                        reorder_1cellp_3d * calculus_3d_manual.hodge<1, PRIMAL>() * reorder_1cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cellp_2d * calculus_2d_manual.hodge<2, PRIMAL>() * reorder_2cell_2d.transpose(),
                        reorder_0cellp_3d * calculus_3d_manual.hodge<2, PRIMAL>() * reorder_2cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cell_2d * calculus_2d_manual.derivative<0, PRIMAL>() * reorder_0cell_2d.transpose(),
                        reorder_1cell_3d * calculus_3d_manual.derivative<0, PRIMAL>() * reorder_0cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_2cell_2d * calculus_2d_manual.derivative<1, PRIMAL>() * reorder_1cell_2d.transpose(),
                        reorder_2cell_3d * calculus_3d_manual.derivative<1, PRIMAL>() * reorder_1cell_3d.transpose()
                        ) );
            FATAL_ERROR( equal(primal_laplace_2d, primal_laplace_3d) );
        }

        { // check dual operators
            const Calculus2D::DualIdentity0 dual_laplace_2d = reorder_0cellp_2d * calculus_2d_manual.laplace<DUAL>() * reorder_0cellp_2d.transpose();
            const Calculus3D::DualIdentity0 dual_laplace_3d = reorder_0cellp_3d * calculus_3d_manual.laplace<DUAL>() * reorder_0cellp_3d.transpose();
            trace.info() << "dual_laplace_2d=" << dual_laplace_2d << endl;
            trace.info() << "dual_laplace_3d=" << dual_laplace_3d << endl;
            trace.info() << "dual_laplace_container=" << endl << MatrixXd(dual_laplace_2d.myContainer) << endl;
            FATAL_ERROR( equal(
                        reorder_2cell_2d * calculus_2d_manual.hodge<0, DUAL>() * reorder_0cellp_2d.transpose(),
                        reorder_2cell_3d * calculus_3d_manual.hodge<0, DUAL>() * reorder_0cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cell_2d * calculus_2d_manual.hodge<1, DUAL>() * reorder_1cellp_2d.transpose(),
                        reorder_1cell_3d * calculus_3d_manual.hodge<1, DUAL>() * reorder_1cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cell_2d * calculus_2d_manual.hodge<2, DUAL>() * reorder_2cellp_2d.transpose(),
                        reorder_0cell_3d * calculus_3d_manual.hodge<2, DUAL>() * reorder_2cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_1cellp_2d * calculus_2d_manual.derivative<0, DUAL>() * reorder_0cellp_2d.transpose(),
                        reorder_1cellp_3d * calculus_3d_manual.derivative<0, DUAL>() * reorder_0cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_2cellp_2d * calculus_2d_manual.derivative<1, DUAL>() * reorder_1cellp_2d.transpose(),
                        reorder_2cellp_3d * calculus_3d_manual.derivative<1, DUAL>() * reorder_1cellp_3d.transpose()
                        ) );
            FATAL_ERROR( equal(dual_laplace_2d, dual_laplace_3d) );
        }

        { // checking dual laplace factory calculus vs manual calculus
            const Calculus2D::DualIdentity0 reorder_0cellp_2d_factory = calculus_2d_factory.reorder<0, DUAL>(cells_2d_manual.begin(), cells_2d_manual.end());
            const Calculus3D::DualIdentity0 reorder_0cellp_3d_factory = calculus_3d_factory.reorder<0, DUAL>(cells_3d_manual.begin(), cells_3d_manual.end());
            FATAL_ERROR( equal(
                        reorder_0cellp_2d * calculus_2d_manual.laplace<DUAL>() * reorder_0cellp_2d.transpose(),
                        reorder_0cellp_2d_factory * calculus_2d_factory.laplace<DUAL>() * reorder_0cellp_2d_factory.transpose()
                        ) );
            FATAL_ERROR( equal(
                        reorder_0cellp_3d * calculus_3d_manual.laplace<DUAL>() * reorder_0cellp_3d.transpose(),
                        reorder_0cellp_3d_factory * calculus_3d_factory.laplace<DUAL>() * reorder_0cellp_3d_factory.transpose()
                        ) );
        }

        trace.endBlock();

        trace.beginBlock("checking border");

        { // 2d ambient border
            //! [embedding_2d_factory_2d_no_border]
            const Calculus2D calculus_2d_factory_no_border = CalculusFactory::createFromNSCells<2>(ncells_2d_factory.begin(), ncells_2d_factory.end(), false);
            //! [embedding_2d_factory_2d_no_border]
            trace.info() << "calculus_2d_factory_no_border=" << calculus_2d_factory_no_border << endl;
            trace.info() << "calculus_2d_factory=" << calculus_2d_factory << endl;

            Board2D board;
            board << Z2i::Domain(Z2i::Point(-1,-1), Z2i::Point(10,10));
            board << calculus_2d_factory_no_border;
            board.saveSVG("embedding_2d_calculus_2d_no_border.svg");
        }

        { // 3d ambient border
            //! [embedding_2d_factory_3d_no_border]
            const Calculus3D calculus_3d_factory_no_border = CalculusFactory::createFromNSCells<2>(ncells_3d_factory.begin(), ncells_3d_factory.end(), false);
            //! [embedding_2d_factory_3d_no_border]
            trace.info() << "calculus_3d_factory_no_border=" << calculus_3d_factory_no_border << endl;
            trace.info() << "calculus_3d_factory=" << calculus_3d_factory << endl;

#if !defined(NOVIEWER)
            Display3DFactory<Calculus3D::KSpace::Space, Calculus3D::KSpace>::draw(viewer3, calculus_3d_factory_no_border);
            viewer3 << Viewer::updateDisplay;
#endif
        }

        trace.endBlock();

        trace.beginBlock("checking area");

        {
            const Calculus2D::Scalar area_th = calculus_2d_factory_weighed.kFormLength(0, DUAL);
            const Calculus2D::Scalar area_primal = (
                calculus_2d_factory_weighed.hodge<0, PRIMAL>() *
                Calculus2D::PrimalForm0::ones(calculus_2d_factory_weighed)
                ).myContainer.array().sum();
            const Calculus2D::Scalar area_dual = (
                calculus_2d_factory_weighed.hodge<0, DUAL>() *
                Calculus2D::DualForm0::ones(calculus_2d_factory_weighed)
                ).myContainer.array().sum();
            trace.info() << "area_2d_th=" << area_th << endl;
            trace.info() << "area_2d_primal=" << area_primal << endl;
            trace.info() << "area_2d_dual=" << area_dual << endl;
            FATAL_ERROR( area_th == area_primal );
            FATAL_ERROR( area_th == area_dual );
        }

        {
            const Calculus3D::Scalar area_th = calculus_3d_factory_weighed.kFormLength(0, DUAL);
            const Calculus3D::Scalar area_primal = (
                calculus_3d_factory_weighed.hodge<0, PRIMAL>() *
                Calculus3D::PrimalForm0::ones(calculus_3d_factory_weighed)
                ).myContainer.array().sum();
            const Calculus3D::Scalar area_dual = (
                calculus_3d_factory_weighed.hodge<0, DUAL>() *
                Calculus3D::DualForm0::ones(calculus_3d_factory_weighed)
                ).myContainer.array().sum();
            trace.info() << "area_3d_th=" << area_th << endl;
            trace.info() << "area_3d_primal=" << area_primal << endl;
            trace.info() << "area_3d_dual=" << area_dual << endl;
            FATAL_ERROR( area_th == area_primal );
            FATAL_ERROR( area_th == area_dual );
        }

        trace.endBlock();

        trace.endBlock();
    }*/

#if !defined(NOVIEWER)
    return app.exec();
#else
    return 0;
#endif
}

