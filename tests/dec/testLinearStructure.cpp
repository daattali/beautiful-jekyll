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
 * @file testLinearStructure.cpp
 * @ingroup Tests
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 * This file is part of the DGtal library
 */

#include "DGtal/math/linalg/EigenSupport.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusSolver.h"

//#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "boost/version.hpp"

using namespace DGtal;
using namespace Z2i;
using std::endl;

#if BOOST_VERSION >= 105000
#define TEST_HARDCODED_ORDER
#endif

void test_linear_structure()
{
    trace.beginBlock("creating dec problem with neumann border condition");

    //! [neumann-creation]
    typedef DiscreteExteriorCalculus<1, 2, EigenLinearAlgebraBackend> Calculus;

    typedef std::list<Calculus::SCell> SCells;
    SCells cells;

    // fill cells container
    {
        const Calculus::KSpace kspace;

        for (int kk=20; kk>0; kk--) cells.push_back( kspace.sCell(Point(0,kk), kk%2 != 0 ? Calculus::KSpace::NEG : Calculus::KSpace::POS) );
        for (int kk=0; kk<10; kk++) cells.push_back( kspace.sCell(Point(kk,0)) );
        for (int kk=0; kk<10; kk++) cells.push_back( kspace.sCell(Point(10,kk)) );
        cells.push_back( kspace.sCell(Point(10,10)) );
        cells.push_back( kspace.sCell(Point(9,10), Calculus::KSpace::NEG) );
        for (int kk=10; kk<20; kk++) cells.push_back( kspace.sCell(Point(8,kk)) );
        for (int kk=8; kk<12; kk++) cells.push_back( kspace.sCell(Point(kk,20)) );
        for (int kk=20; kk>0; kk--) cells.push_back( kspace.sCell(Point(12,kk), kk%2 != 0 ? Calculus::KSpace::NEG : Calculus::KSpace::POS) );
        cells.push_back( kspace.sCell(Point(12,0)) );
    }

    // fill calculus
    const Domain domain(Point(-1,-1), Point(10,10));

    // create DEC structure
    Calculus calculus;
    calculus.initKSpace<Domain>(domain);
    for (SCells::const_iterator ci=cells.begin(), ce=cells.end(); ci!=ce; ci++) calculus.insertSCell( *ci );
    calculus.updateIndexes();
    //! [neumann-creation]

    trace.info() << calculus << endl;

    //! [input-dirac]
    Calculus::Cell dirac_cell = calculus.myKSpace.uCell(Point(10,4));
    Calculus::PrimalForm0 dirac = Calculus::PrimalForm0::dirac(calculus, dirac_cell);
    //! [input-dirac]
    trace.info() << "dirac_cell_index=" << calculus.getCellIndex(dirac_cell) << endl;

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << dirac;
        board.saveSVG("linear_structure_neumann_dirac.svg");
    }

    trace.endBlock();

    {
        trace.beginBlock("solving problem with neumann border condition using sparse qr solver");

        //! [neumann-laplace-definition]
        const Calculus::PrimalIdentity0 laplace = calculus.laplace<PRIMAL>();
        //! [neumann-laplace-definition]
        trace.info() << "laplace = " << laplace << endl;

        const Calculus::PrimalIdentity0 reorder = calculus.reorder<0, PRIMAL>(cells.begin(), cells.end());
        const Calculus::PrimalIdentity0 laplace_ordered = reorder * laplace * reorder.transpose();
        trace.info() << Eigen::MatrixXd(laplace_ordered.myContainer) << endl;

        //! [neumann-solve]
        typedef EigenLinearAlgebraBackend::SolverSparseQR LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, PRIMAL, 0, PRIMAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::PrimalForm0 solved_solution = solver.solve(dirac);
        //! [neumann-solve]
        Calculus::PrimalForm0 solved_solution_ordered = reorder * solved_solution;

        Calculus::PrimalForm0 analytic_solution(calculus);
        {
            const Calculus::Index dirac_position = 17;
            const Calculus::Index length = analytic_solution.length();
            for (Calculus::Index kk=0; kk<length; kk++)
            {
                Calculus::Scalar alpha = 1. * (kk)/dirac_position * (kk+1.)/(dirac_position+1.);
                if (kk>dirac_position)
                {
                    alpha = 1. * (length-kk)/dirac_position * (length-kk-1.)/(dirac_position+1);
                    alpha -= 1. * (length-dirac_position)/dirac_position * (length-dirac_position-1.)/(dirac_position+1);
                    alpha += 1;
                }
                analytic_solution.myContainer(kk) = alpha;
            }
        }

        const double shift = solved_solution_ordered.myContainer[0]-analytic_solution.myContainer[0];
        for (Calculus::Index index=0; index<solved_solution_ordered.length(); index++) solved_solution_ordered.myContainer[index] -= shift;
        solved_solution_ordered.myContainer /= solved_solution_ordered.myContainer.maxCoeff();

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;

        {
            std::ofstream handle("linear_structure_neumann.dat");
            for (Calculus::Index kk=0; kk<analytic_solution.length(); kk++)
            {
                handle << solved_solution_ordered.myContainer(kk) << " " << analytic_solution.myContainer(kk) << endl;
            }
        }

        const double error = (solved_solution_ordered-analytic_solution).myContainer.array().abs().maxCoeff();
        trace.info() << "error=" << error << endl;
        FATAL_ERROR( error < 1e-5 );

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << solved_solution;
            board.saveSVG("linear_structure_neumann_solution.svg");
        }

        {
            Calculus::PrimalForm1 solved_solution_gradient = calculus.derivative<0, PRIMAL>() * solved_solution;
            Board2D board;
            board << domain;
            board << calculus;
            board << solved_solution_gradient;
            board << CustomStyle("VectorField", new VectorFieldStyle2D(1));
            board << calculus.sharp(solved_solution_gradient);
            board.saveSVG("linear_structure_neumann_solution_gradient.svg");
        }

        trace.endBlock();
    }

    trace.beginBlock("creating dec problem with dirichlet border condition");

    //! [dirichlet-creation]
    calculus.insertSCell( calculus.myKSpace.sCell(Point(13,0)) );
    calculus.insertSCell( calculus.myKSpace.sCell(Point(1,20), Calculus::KSpace::NEG) );
    calculus.updateIndexes();
    //! [dirichlet-creation]

    dirac = Calculus::PrimalForm0::dirac(calculus, dirac_cell);
    trace.info() << calculus << endl;
    trace.info() << "dirac_cell_index=" << calculus.getCellIndex(dirac_cell) << endl;

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << dirac;
        board.saveSVG("linear_structure_dirichlet_dirac.svg");
    }

    trace.endBlock();

    {
        trace.beginBlock("solving problem with dirichlet border condition using sparse qr solver");

        //! [dirichlet-laplace-definition]
        const Calculus::PrimalIdentity0 laplace = calculus.laplace<PRIMAL>();
        //! [dirichlet-laplace-definition]
        trace.info() << "laplace = " << laplace << endl;

        const Calculus::PrimalIdentity0 reorder = calculus.reorder<0, PRIMAL>(cells.begin(), cells.end());
        const Calculus::PrimalIdentity0 laplace_ordered = reorder * laplace * reorder.transpose();
        trace.info() << Eigen::MatrixXd(laplace_ordered.myContainer) << endl;

        //! [dirichlet-solve]
        typedef EigenLinearAlgebraBackend::SolverSparseQR LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, PRIMAL, 0, PRIMAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::PrimalForm0 solved_solution = solver.solve(dirac);
        //! [dirichlet-solve]
        solved_solution.myContainer.array() /= solved_solution.myContainer.maxCoeff();
        Calculus::PrimalForm0 solved_solution_ordered = reorder * solved_solution;

        Calculus::PrimalForm0 analytic_solution(calculus);
        {
            const Calculus::Index dirac_position = 17;
            const Calculus::Index length = analytic_solution.length();
            for (Calculus::Index kk=0; kk<length; kk++)
            {
                Calculus::Scalar alpha = (kk+1.)/(dirac_position+1.);
                if (kk>dirac_position)
                {
                    alpha = 1. - (kk-dirac_position)/(1.*length-dirac_position);
                }
                analytic_solution.myContainer(kk) = alpha;
            }
        }

        const double shift = solved_solution_ordered.myContainer[0]-analytic_solution.myContainer[0];
        for (Calculus::Index index=0; index<solved_solution_ordered.length(); index++) solved_solution_ordered.myContainer[index] -= shift;
        solved_solution_ordered.myContainer /= solved_solution_ordered.myContainer.maxCoeff();

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;

        {
            std::ofstream handle("linear_structure_dirichlet.dat");
            for (Calculus::Index kk=0; kk<analytic_solution.length(); kk++)
            {
                handle << solved_solution_ordered.myContainer(kk) << " " << analytic_solution.myContainer(kk) << endl;
            }
        }

        const double error = (solved_solution_ordered-analytic_solution).myContainer.array().abs().maxCoeff();
        trace.info() << "error=" << error << endl;
        FATAL_ERROR( error < 1e-5 );

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << solved_solution;
            board.saveSVG("linear_structure_dirichlet_solution.svg");
        }

        {
            Calculus::PrimalForm1 solved_solution_gradient = calculus.derivative<0, PRIMAL>() * solved_solution;

            Board2D board;
            board << domain;
            board << calculus;
            board << solved_solution_gradient;
            board << calculus.sharp(solved_solution_gradient);
            board.saveSVG("linear_structure_dirichlet_solution_gradient.svg");
        }

        trace.endBlock();
    }

}

template <typename Operator>
void display_operator_info(const std::string& name, const Operator& op)
{
    trace.info() << name << endl << op << endl << Eigen::MatrixXd(op.myContainer) << endl;
}

void test_linear_ring()
{
    trace.beginBlock("linear ring");

    const Domain domain(Point(-5,-5), Point(5,5));

    typedef DiscreteExteriorCalculus<1, 2, EigenLinearAlgebraBackend> Calculus;
    Calculus calculus;
    calculus.initKSpace<Domain>(domain);

    for (int kk=-8; kk<10; kk++) calculus.insertSCell( calculus.myKSpace.sCell(Point(-8,kk), kk%2 == 0 ? Calculus::KSpace::POS : Calculus::KSpace::NEG) );
    for (int kk=-8; kk<10; kk++) calculus.insertSCell( calculus.myKSpace.sCell(Point(kk,10), kk%2 == 0 ? Calculus::KSpace::POS : Calculus::KSpace::NEG) );
    for (int kk=10; kk>-8; kk--) calculus.insertSCell( calculus.myKSpace.sCell(Point(10,kk)) );
    for (int kk=10; kk>-8; kk--) calculus.insertSCell( calculus.myKSpace.sCell(Point(kk,-8)) );
    calculus.updateIndexes();

    {
        trace.info() << calculus << endl;
        Board2D board;
        board << domain;
        board << calculus;
        board.saveSVG("ring_structure.svg");
    }

    const Calculus::PrimalDerivative0 d0 = calculus.derivative<0, PRIMAL>();
    display_operator_info("d0", d0);

    const Calculus::PrimalHodge0 h0 = calculus.hodge<0, PRIMAL>();
    display_operator_info("h0", h0);

    const Calculus::DualDerivative0 d0p = calculus.derivative<0, DUAL>();
    display_operator_info("d0p", d0p);

    const Calculus::PrimalHodge1 h1 = calculus.hodge<1, PRIMAL>();
    display_operator_info("h1", h1);

    const Calculus::PrimalIdentity0 laplace = calculus.laplace<PRIMAL>();
    display_operator_info("laplace", laplace);

    const int laplace_size = calculus.kFormLength(0, PRIMAL);
    const Eigen::MatrixXd laplace_dense(laplace.myContainer);

    for (int ii=0; ii<laplace_size; ii++)
        FATAL_ERROR( laplace_dense(ii,ii) == 2 );

    FATAL_ERROR( laplace_dense.array().rowwise().sum().abs().sum() == 0 );
    FATAL_ERROR( laplace_dense.transpose() == laplace_dense );

    trace.endBlock();
}

void test_manual_operators_3d()
{
    trace.beginBlock("testing 3d operators");

    const Z3i::Domain domain(Z3i::Point(0,0,0), Z3i::Point(1,1,1));

    typedef DiscreteExteriorCalculus<3, 3, EigenLinearAlgebraBackend> Calculus;

    Calculus calculus;
    calculus.initKSpace<Z3i::Domain>(domain);

    { // filling primal calculus
        // 0-cells
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(0,0,0)) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(2,0,0)) );

        // 1-cells
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(0,1,0), Calculus::KSpace::POS) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(0,0,1), Calculus::KSpace::POS) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(1,0,0), Calculus::KSpace::POS) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(2,1,0), Calculus::KSpace::NEG) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(2,0,1), Calculus::KSpace::NEG) );

        // 2-cells
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(0,1,1), Calculus::KSpace::NEG) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(1,0,1), Calculus::KSpace::POS) ); //FIXME strange cell orientation
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(2,1,1), Calculus::KSpace::POS) );
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(1,1,0), Calculus::KSpace::NEG) );

        // 3-cells
        calculus.insertSCell( calculus.myKSpace.sCell(Z3i::Point(1,1,1)) );

        calculus.updateIndexes();

        trace.info() << calculus << endl;
    }

    trace.beginBlock("base operators");

    {
        const Calculus::PrimalDerivative0 d0 = calculus.derivative<0, PRIMAL>();
        const Calculus::DualDerivative2 d2p = calculus.derivative<2, DUAL>();
        display_operator_info("d0", d0);
        display_operator_info("d2p", d2p);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd d0_th(5, 2);
        d0_th <<
           -1,  0,
           -1,  0,
           -1,  1,
            0,  1,
            0,  1;

        FATAL_ERROR( Eigen::MatrixXd(d0.myContainer) == d0_th );
#endif
        FATAL_ERROR( Eigen::MatrixXd(d2p.transpose().myContainer) == Eigen::MatrixXd(d0.myContainer) );
    }

    {
        const Calculus::PrimalDerivative1 d1 = calculus.derivative<1, PRIMAL>();
        const Calculus::DualDerivative1 d1p = calculus.derivative<1, DUAL>();
        display_operator_info("d1", d1);
        display_operator_info("d1p", d1p);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd d1_th(4, 5);
        d1_th <<
             0, -1,  1,  0, -1,
             1,  0, -1,  1,  0,
             0,  0,  0, -1,  1,
            -1,  1,  0,  0,  0;

        FATAL_ERROR( Eigen::MatrixXd(d1.myContainer) == d1_th );
#endif
        FATAL_ERROR( Eigen::MatrixXd(d1p.transpose().myContainer) == Eigen::MatrixXd(d1.myContainer) );
    }

    {
        const Calculus::PrimalDerivative2 d2 = calculus.derivative<2, PRIMAL>();
        const Calculus::DualDerivative0 d0p = calculus.derivative<0, DUAL>();
        display_operator_info("d2", d2);
        display_operator_info("d0p", d0p);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd d2_th(1, 4);
        d2_th << -1, -1, -1, -1;

        FATAL_ERROR( Eigen::MatrixXd(d2.myContainer) == d2_th );
#endif
        FATAL_ERROR( Eigen::MatrixXd(d0p.transpose().myContainer) == Eigen::MatrixXd(d2.myContainer) );
    }

    trace.endBlock();

    /*
    QApplication app(0, NULL);

    typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
    Viewer* viewer = new Viewer(calculus.myKSpace);
    viewer->show();
    viewer->setWindowTitle("structure");
    (*viewer) << CustomColors3D(DGtal::Color(255,0,0), DGtal::Color(0,0,0));
    (*viewer) << domain;
    Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, calculus);
    (*viewer) << Viewer::updateDisplay;

    app.exec();
    */

    trace.endBlock();
}

void test_manual_operators_2d()
{
    trace.beginBlock("testing 2d operators");

    const Domain domain(Point(0,0), Point(5,4));

    typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus;

    Calculus primal_calculus;
    primal_calculus.initKSpace<Domain>(domain);

    { // filling primal calculus
        // 0-cells
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(2,2)) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(4,2)) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(2,4)) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(4,4)) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(2,6)) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(4,6)) );

        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(1,2)) ); // insert cell

        // 1-cells
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(3,2), Calculus::KSpace::NEG) ); // insert negative cell
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(3,2), Calculus::KSpace::POS) ); // then reinserting negative cell in structure
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(2,3), Calculus::KSpace::NEG) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(4,3), Calculus::KSpace::POS) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(3,4), Calculus::KSpace::NEG) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(2,5), Calculus::KSpace::POS) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(4,5), Calculus::KSpace::NEG) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(3,6), Calculus::KSpace::POS) );

        primal_calculus.eraseCell( primal_calculus.myKSpace.uCell(Point(1,2)) ); // then remove it

        // 2-cells
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(3,3)) );
        primal_calculus.insertSCell( primal_calculus.myKSpace.sCell(Point(3,5)) );

        primal_calculus.updateIndexes();

        trace.beginBlock("primal calculus");
        trace.info() << primal_calculus << endl;
        for (Calculus::ConstIterator iter_property=primal_calculus.begin(), iter_property_end=primal_calculus.end(); iter_property!=iter_property_end; iter_property++)
        {
            const Calculus::Cell cell = iter_property->first;
            const Calculus::Property property = iter_property->second;
            const Dimension dim = primal_calculus.myKSpace.uDim(cell);
            const Calculus::SCell signed_cell = primal_calculus.myKSpace.signs(cell, property.flipped ? Calculus::KSpace::NEG : Calculus::KSpace::POS);

            ASSERT( signed_cell == primal_calculus.getSCell(dim, PRIMAL, property.index) );

            trace.info() << cell
                << " " << dim
                << " " << signed_cell
                << " " << property.primal_size
                << " " << property.dual_size
                << " " << property.index
                << " " << (property.flipped ? "negative" : "positive")
                << endl;
        }
        trace.endBlock();
    }


    Calculus dual_calculus;
    dual_calculus.initKSpace<Domain>(domain);

    { // filling dual calculus
        // 2-cells
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(7,3)) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(9,3)) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(7,5)) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(9,5)) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(7,7)) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(9,7)) );

        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(6,3)) ); // insert cell

        // 1-cells
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(8,3), Calculus::KSpace::NEG) ); // insert negative cell
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(8,3), Calculus::KSpace::POS) ); // then reinserting negative cell in structure
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(7,4), Calculus::KSpace::POS) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(9,4), Calculus::KSpace::NEG) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(8,5), Calculus::KSpace::NEG) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(7,6), Calculus::KSpace::NEG) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(9,6), Calculus::KSpace::POS) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(8,7), Calculus::KSpace::POS) );

        dual_calculus.eraseCell( dual_calculus.myKSpace.uCell(Point(6,3)) ); // then remove it

        // 0-cells
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(8,4)) );
        dual_calculus.insertSCell( dual_calculus.myKSpace.sCell(Point(8,6)) );

        dual_calculus.updateIndexes();

        trace.beginBlock("dual calculus");
        trace.info() << dual_calculus << endl;
        for (Calculus::ConstIterator iter_property=dual_calculus.begin(), iter_property_end=dual_calculus.end(); iter_property!=iter_property_end; iter_property++)
        {
            const Calculus::Cell cell = iter_property->first;
            const Calculus::Property property = iter_property->second;
            const Dimension dim = dual_calculus.myKSpace.uDim(cell);
            const Calculus::SCell signed_cell = dual_calculus.myKSpace.signs(cell, property.flipped ? Calculus::KSpace::NEG : Calculus::KSpace::POS);

            ASSERT( signed_cell == dual_calculus.getSCell(dim, PRIMAL, property.index) );

            trace.info() << cell
                << " " << dim
                << " " << signed_cell
                << " " << property.primal_size
                << " " << property.dual_size
                << " " << property.index
                << " " << (property.flipped ? "negative" : "positive")
                << endl;
        }
        trace.endBlock();
    }

    {
        Board2D board;
        board << domain;
        board << primal_calculus;
        board << dual_calculus;
        board.saveSVG("operators_structure.svg");
    }

    trace.beginBlock("base operators");

    const Calculus::PrimalDerivative0 primal_d0 = primal_calculus.derivative<0, PRIMAL>();
    const Calculus::DualDerivative0 dual_d0p = dual_calculus.derivative<0, DUAL>();
    {
        display_operator_info("primal d0", primal_d0);
        display_operator_info("dual d0p", dual_d0p);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd d0_th(7, 6);
        d0_th <<
            -1,  1,  0,  0,  0,  0,
             1,  0,  0, -1,  0,  0,
             0,  0,  1,  0,  0, -1,
             0,  0,  0,  0, -1,  1,
             0, -1,  1,  0,  0,  0,
             0,  0, -1,  1,  0,  0,
             0,  0,  0, -1,  1,  0;
        FATAL_ERROR( Eigen::MatrixXd(primal_d0.myContainer) == d0_th );

        Eigen::MatrixXd d0p_th(7, 6);
        d0p_th <<
             1, -1,  0,  0,  0,  0,
             0,  0, -1,  1,  0,  0,
             0,  1,  0, -1,  0,  0,
             0,  0,  1,  0, -1,  0,
             0,  0,  0,  0,  1, -1,
            -1,  0,  1,  0,  0,  0,
             0,  0,  0, -1,  0,  1;
        FATAL_ERROR( Eigen::MatrixXd(dual_d0p.myContainer) == d0p_th );
#endif
    }

    const Calculus::PrimalDerivative1 primal_d1 = primal_calculus.derivative<1, PRIMAL>();
    const Calculus::DualDerivative1 dual_d1p = dual_calculus.derivative<1, DUAL>();
    {
        display_operator_info("primal d1", primal_d1);
        display_operator_info("dual d1p", dual_d1p);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd d1_th(2, 7);
        d1_th <<
             1,  1,  0,  0,  1,  1,  0,
             0,  0, -1, -1,  0, -1, -1;
        FATAL_ERROR( Eigen::MatrixXd(primal_d1.myContainer) == d1_th );

        Eigen::MatrixXd d1p_th(2, 7);
        d1p_th <<
            -1, -1, -1,  0,  0, -1,  0,
             0,  1,  0,  1,  1,  0,  1;
        FATAL_ERROR( Eigen::MatrixXd(dual_d1p.myContainer) == d1p_th );
#endif
    }

    {
        display_operator_info("primal d1*d0", primal_d1*primal_d0);
        display_operator_info("dual d1p*d0p", dual_d1p*dual_d0p);

        FATAL_ERROR( Eigen::MatrixXd((primal_d1*primal_d0).myContainer) == Eigen::MatrixXd::Zero(2,6) );
        FATAL_ERROR( Eigen::MatrixXd((dual_d1p*dual_d0p).myContainer) == Eigen::MatrixXd::Zero(2,6) );
    }

    const Calculus::PrimalHodge0 primal_h0 = primal_calculus.hodge<0, PRIMAL>();
    const Calculus::DualHodge0 dual_h0p = dual_calculus.hodge<0, DUAL>();
    const Calculus::DualHodge2 primal_h2p = primal_calculus.hodge<2, DUAL>();
    const Calculus::PrimalHodge2 dual_h2 = dual_calculus.hodge<2, PRIMAL>();
    {
        display_operator_info("primal h0", primal_h0);
        display_operator_info("dual h0p", dual_h0p);
        display_operator_info("primal h2p", primal_h2p);
        display_operator_info("dual h2", dual_h2);

        FATAL_ERROR( Eigen::MatrixXd(primal_h0.myContainer) == Eigen::MatrixXd::Identity(6,6) );
        FATAL_ERROR( Eigen::MatrixXd(dual_h0p.myContainer) == Eigen::MatrixXd::Identity(6,6) );
        FATAL_ERROR( Eigen::MatrixXd(primal_h2p.myContainer) == Eigen::MatrixXd::Identity(6,6) );
        FATAL_ERROR( Eigen::MatrixXd(dual_h2.myContainer) == Eigen::MatrixXd::Identity(6,6) );
    }

    const Calculus::PrimalHodge2 primal_h2 = primal_calculus.hodge<2, PRIMAL>();
    const Calculus::DualHodge2 dual_h2p = dual_calculus.hodge<2, DUAL>();
    const Calculus::DualHodge0 primal_h0p = primal_calculus.hodge<0, DUAL>();
    const Calculus::PrimalHodge0 dual_h0 = dual_calculus.hodge<0, PRIMAL>();
    {
        display_operator_info("primal h2", primal_h2);
        display_operator_info("dual h2p", dual_h2p);
        display_operator_info("primal h0p", primal_h0p);
        display_operator_info("dual h0", dual_h0);

        FATAL_ERROR( Eigen::MatrixXd(primal_h2.myContainer) == Eigen::MatrixXd::Identity(2,2) );
        FATAL_ERROR( Eigen::MatrixXd(dual_h2p.myContainer) == Eigen::MatrixXd::Identity(2,2) );
        FATAL_ERROR( Eigen::MatrixXd(primal_h0p.myContainer) == Eigen::MatrixXd::Identity(2,2) );
        FATAL_ERROR( Eigen::MatrixXd(dual_h0.myContainer) == Eigen::MatrixXd::Identity(2,2) );
    }

    const Calculus::DualDerivative0 primal_d0p = primal_calculus.derivative<0, DUAL>();
    const Calculus::PrimalDerivative0 dual_d0 = dual_calculus.derivative<0, PRIMAL>();
    {
        display_operator_info("primal d0p", primal_d0p);
        display_operator_info("dual d0", dual_d0);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd d0p_th_transpose(2, 7);
        d0p_th_transpose <<
             1,  1,  0,  0,  1,  1,  0,
             0,  0, -1, -1,  0, -1, -1;
        FATAL_ERROR( Eigen::MatrixXd(primal_d0p.myContainer) == d0p_th_transpose.transpose() );

        Eigen::MatrixXd minus_d0_th_transpose(2, 7);
        minus_d0_th_transpose <<
            -1, -1, -1,  0,  0, -1,  0,
             0,  1,  0,  1,  1,  0,  1;
        FATAL_ERROR( Eigen::MatrixXd(dual_d0.myContainer) == -minus_d0_th_transpose.transpose() );
#endif
    }

    const Calculus::DualDerivative1 primal_d1p = primal_calculus.derivative<1, DUAL>();
    const Calculus::PrimalDerivative1 dual_d1 = dual_calculus.derivative<1, PRIMAL>();
    {
        display_operator_info("primal d1p", primal_d1p);
        display_operator_info("dual d1", dual_d1);

#if defined(TEST_HARDCODED_ORDER)
        Eigen::MatrixXd minus_d1p_th_transpose(7, 6);
        minus_d1p_th_transpose <<
            -1,  1,  0,  0,  0,  0,
             1,  0,  0, -1,  0,  0,
             0,  0,  1,  0,  0, -1,
             0,  0,  0,  0, -1,  1,
             0, -1,  1,  0,  0,  0,
             0,  0, -1,  1,  0,  0,
             0,  0,  0, -1,  1,  0;
        FATAL_ERROR( Eigen::MatrixXd(primal_d1p.myContainer) == -minus_d1p_th_transpose.transpose() );

        Eigen::MatrixXd d1_th_transpose(7, 6);
        d1_th_transpose <<
             1, -1,  0,  0,  0,  0,
             0,  0, -1,  1,  0,  0,
             0,  1,  0, -1,  0,  0,
             0,  0,  1,  0, -1,  0,
             0,  0,  0,  0,  1, -1,
            -1,  0,  1,  0,  0,  0,
             0,  0,  0, -1,  0,  1;
        FATAL_ERROR( Eigen::MatrixXd(dual_d1.myContainer) == d1_th_transpose.transpose() );
#endif
    }

    const Calculus::PrimalHodge1 primal_h1 = primal_calculus.hodge<1, PRIMAL>();
    const Calculus::DualHodge1 dual_h1p = dual_calculus.hodge<1, DUAL>();
    const Calculus::DualHodge1 primal_h1p = primal_calculus.hodge<1, DUAL>();
    const Calculus::PrimalHodge1 dual_h1 = dual_calculus.hodge<1, PRIMAL>();
    {
        display_operator_info("primal h1", primal_h1);
        display_operator_info("dual h1p", dual_h1p);
        display_operator_info("primal h1p", primal_h1p);
        display_operator_info("dual h1", dual_h1);

        FATAL_ERROR( Eigen::MatrixXd(primal_h1.myContainer) == Eigen::MatrixXd::Identity(7,7) );
        FATAL_ERROR( Eigen::MatrixXd(dual_h1p.myContainer) == -Eigen::MatrixXd::Identity(7,7) );
        FATAL_ERROR( Eigen::MatrixXd((primal_h1p*primal_h1).myContainer) == -Eigen::MatrixXd::Identity(7,7) );
        FATAL_ERROR( Eigen::MatrixXd((dual_h1*dual_h1p).myContainer) == -Eigen::MatrixXd::Identity(7,7) );
        FATAL_ERROR( Eigen::MatrixXd((primal_h1*primal_h1p).myContainer) == -Eigen::MatrixXd::Identity(7,7) );
        FATAL_ERROR( Eigen::MatrixXd((dual_h1p*dual_h1).myContainer) == -Eigen::MatrixXd::Identity(7,7) );
    }

    trace.endBlock();

    trace.beginBlock("laplace operators");
    display_operator_info("primal laplace", primal_calculus.laplace<PRIMAL>());
    display_operator_info("dual laplacep", dual_calculus.laplace<DUAL>());
    display_operator_info("primal laplacep", primal_calculus.laplace<DUAL>());
    display_operator_info("dual laplace", dual_calculus.laplace<PRIMAL>());
    trace.endBlock();

    trace.beginBlock("sharp operators");

    { // primal sharp
        display_operator_info("primal #x", primal_calculus.sharpDirectional<PRIMAL>(0));
        display_operator_info("dual #xp", dual_calculus.sharpDirectional<DUAL>(0));
        display_operator_info("primal #y", primal_calculus.sharpDirectional<PRIMAL>(1));
        display_operator_info("dual #yp", dual_calculus.sharpDirectional<DUAL>(1));

        {
            Calculus::PrimalForm1::Container dx_container(7);
            dx_container << -1, 0, 0, -1, 0, 1, 0;
            const Calculus::PrimalForm1 primal_dx(primal_calculus, dx_container);
            const Calculus::PrimalVectorField primal_dx_field = primal_calculus.sharp(primal_dx);

            Calculus::PrimalForm1::Container dxp_container(7);
            dxp_container << 1, -1, 0, 0, 1, 0, 0;
            const Calculus::DualForm1 dual_dx(dual_calculus, dxp_container);
            const Calculus::DualVectorField dual_dx_field = dual_calculus.sharp(dual_dx);

            {
                Board2D board;
                board << domain;
                board << primal_calculus;
                board << primal_dx << primal_dx_field;
                board << dual_calculus;
                board << dual_dx << dual_dx_field;
                board.saveSVG("operators_sharp_dx_primal.svg");
            }

#if defined(TEST_HARDCODED_ORDER)
            FATAL_ERROR( primal_dx_field.myCoordinates.col(0) == Eigen::VectorXd::Ones(6) );
            FATAL_ERROR( primal_dx_field.myCoordinates.col(1) == Eigen::VectorXd::Zero(6) );
            FATAL_ERROR( dual_dx_field.myCoordinates.col(0) == Eigen::VectorXd::Ones(6) );
            FATAL_ERROR( dual_dx_field.myCoordinates.col(1) == Eigen::VectorXd::Zero(6) );
#endif
        }

        {
            Calculus::PrimalForm1::Container dy_container(7);
            dy_container << 0, 1, 1, 0, -1, 0, -1;
            const Calculus::PrimalForm1 primal_dy(primal_calculus, dy_container);
            const Calculus::PrimalVectorField primal_dy_field = primal_calculus.sharp(primal_dy);

            Calculus::PrimalForm1::Container dyp_container(7);
            dyp_container << 0, 0, 1, 1, 0, -1, -1;
            const Calculus::DualForm1 dual_dy(dual_calculus, dyp_container);
            const Calculus::DualVectorField dual_dy_field = dual_calculus.sharp(dual_dy);

            {
                Board2D board;
                board << domain;
                board << primal_calculus;
                board << primal_dy << primal_dy_field;
                board << dual_calculus;
                board << dual_dy << dual_dy_field;
                board.saveSVG("operators_sharp_dy_primal.svg");
            }

#if defined(TEST_HARDCODED_ORDER)
            FATAL_ERROR( primal_dy_field.myCoordinates.col(0) == Eigen::VectorXd::Zero(6) );
            FATAL_ERROR( primal_dy_field.myCoordinates.col(1) == Eigen::VectorXd::Ones(6) );
            FATAL_ERROR( dual_dy_field.myCoordinates.col(0) == Eigen::VectorXd::Zero(6) );
            FATAL_ERROR( dual_dy_field.myCoordinates.col(1) == Eigen::VectorXd::Ones(6) );
#endif
        }
    }

    { // dual sharp
        display_operator_info("primal #xp", primal_calculus.sharpDirectional<DUAL>(0));
        display_operator_info("dual #x", dual_calculus.sharpDirectional<PRIMAL>(0));
        display_operator_info("primal #yp", primal_calculus.sharpDirectional<DUAL>(1));
        display_operator_info("dual #y", dual_calculus.sharpDirectional<PRIMAL>(1));

        {
            Calculus::DualForm1::Container dx_container(7);
            dx_container << 0, -1, -1, 0, 1, 0, 1;
            const Calculus::DualForm1 primal_dx(primal_calculus, dx_container);
            const Calculus::DualVectorField primal_dx_field = primal_calculus.sharp(primal_dx);

            Calculus::DualForm1::Container dxp_container(7);
            dxp_container << 0, 0, 1, 1, 0, -1, -1;
            const Calculus::PrimalForm1 dual_dx(dual_calculus, dxp_container);
            const Calculus::PrimalVectorField dual_dx_field = dual_calculus.sharp(dual_dx);

            {
                Board2D board;
                board << domain;
                board << primal_calculus;
                board << primal_dx << primal_dx_field;
                board << dual_calculus;
                board << dual_dx << dual_dx_field;
                board.saveSVG("operators_sharp_dx_dual.svg");
            }

#if defined(TEST_HARDCODED_ORDER)
            FATAL_ERROR( primal_dx_field.myCoordinates.col(0) == Eigen::VectorXd::Ones(2) );
            FATAL_ERROR( primal_dx_field.myCoordinates.col(1) == Eigen::VectorXd::Zero(2) );
            FATAL_ERROR( dual_dx_field.myCoordinates.col(0) == Eigen::VectorXd::Ones(2) );
            FATAL_ERROR( dual_dx_field.myCoordinates.col(1) == Eigen::VectorXd::Zero(2) );
#endif
        }

        {
            Calculus::DualForm1::Container dy_container(7);
            dy_container << -1, 0, 0, -1, 0 , 1, 0;
            const Calculus::DualForm1 primal_dy(primal_calculus, dy_container);
            const Calculus::DualVectorField primal_dy_field = primal_calculus.sharp(primal_dy);

            Calculus::DualForm1::Container dyp_container(7);
            dyp_container << -1, 1, 0, 0, -1, 0, 0;
            const Calculus::PrimalForm1 dual_dy(dual_calculus, dyp_container);
            const Calculus::PrimalVectorField dual_dy_field = dual_calculus.sharp(dual_dy);

            {
                Board2D board;
                board << domain;
                board << primal_calculus;
                board << primal_dy << primal_dy_field;
                board << dual_calculus;
                board << dual_dy << dual_dy_field;
                board.saveSVG("operators_sharp_dy_dual.svg");
            }

#if defined(TEST_HARDCODED_ORDER)
            FATAL_ERROR( primal_dy_field.myCoordinates.col(0) == Eigen::VectorXd::Zero(2) );
            FATAL_ERROR( primal_dy_field.myCoordinates.col(1) == Eigen::VectorXd::Ones(2) );
            FATAL_ERROR( dual_dy_field.myCoordinates.col(0) == Eigen::VectorXd::Zero(2) );
            FATAL_ERROR( dual_dy_field.myCoordinates.col(1) == Eigen::VectorXd::Ones(2) );
#endif
        }
    }

    trace.endBlock();

    trace.beginBlock("flat operators");

    { // primal flat
        display_operator_info("primal bx", primal_calculus.flatDirectional<PRIMAL>(0));
        display_operator_info("dual bxp", dual_calculus.flatDirectional<DUAL>(0));
        display_operator_info("primal by", primal_calculus.flatDirectional<PRIMAL>(1));
        display_operator_info("dual byp", dual_calculus.flatDirectional<DUAL>(1));

        Calculus::PrimalVectorField::Coordinates dx_coords(6,2);
        dx_coords.col(0) = Eigen::VectorXd::Ones(6);
        dx_coords.col(1) = Eigen::VectorXd::Zero(6);

        Calculus::PrimalVectorField::Coordinates dy_coords(6,2);
        dy_coords.col(0) = Eigen::VectorXd::Zero(6);
        dy_coords.col(1) = Eigen::VectorXd::Ones(6);

        const Calculus::PrimalVectorField primal_dx_field(primal_calculus, dx_coords);
        const Calculus::PrimalForm1 primal_dx = primal_calculus.flat(primal_dx_field);
        const Calculus::DualVectorField dual_dx_field(dual_calculus, dx_coords);
        const Calculus::DualForm1 dual_dx = dual_calculus.flat(dual_dx_field);

        {
            Board2D board;
            board << domain;
            board << primal_calculus;
            board << primal_dx << primal_dx_field;
            board << dual_calculus;
            board << dual_dx << dual_dx_field;
            board.saveSVG("operators_flat_dx_primal.svg");
        }

        const Calculus::PrimalVectorField primal_dy_field(primal_calculus, dy_coords);
        const Calculus::PrimalForm1 primal_dy = primal_calculus.flat(primal_dy_field);
        const Calculus::DualVectorField dual_dy_field(dual_calculus, dy_coords);
        const Calculus::DualForm1 dual_dy = dual_calculus.flat(dual_dy_field);

        {
            Board2D board;
            board << domain;
            board << primal_calculus;
            board << primal_dy << primal_dy_field;
            board << dual_calculus;
            board << dual_dy << dual_dy_field;
            board.saveSVG("operators_flat_dy_primal.svg");
        }

#if defined(TEST_HARDCODED_ORDER)
        Calculus::PrimalForm1::Container dx_container(7);
        dx_container << -1, 0, 0, -1, 0, 1, 0;
        Calculus::PrimalForm1::Container dxp_container(7);
        dxp_container << 1, -1, 0, 0, 1, 0, 0;
        FATAL_ERROR( primal_dx.myContainer == dx_container );
        FATAL_ERROR( dual_dx.myContainer == dxp_container );

        Calculus::PrimalForm1::Container dy_container(7);
        dy_container << 0, 1, 1, 0, -1, 0, -1;
        Calculus::PrimalForm1::Container dyp_container(7);
        dyp_container << 0, 0, 1, 1, 0, -1, -1;
        FATAL_ERROR( primal_dy.myContainer == dy_container );
        FATAL_ERROR( dual_dy.myContainer == dyp_container );
#endif
    }

    { // dual flat
        display_operator_info("primal bxp", primal_calculus.flatDirectional<DUAL>(0));
        display_operator_info("dual bx", dual_calculus.flatDirectional<PRIMAL>(0));
        display_operator_info("primal byp", primal_calculus.flatDirectional<DUAL>(1));
        display_operator_info("dual by", dual_calculus.flatDirectional<PRIMAL>(1));

        Calculus::PrimalVectorField::Coordinates dx_coords(2,2);
        dx_coords.col(0) = Eigen::VectorXd::Ones(2);
        dx_coords.col(1) = Eigen::VectorXd::Zero(2);

        Calculus::PrimalVectorField::Coordinates dy_coords(2,2);
        dy_coords.col(0) = Eigen::VectorXd::Zero(2);
        dy_coords.col(1) = Eigen::VectorXd::Ones(2);

        const Calculus::DualVectorField primal_dx_field(primal_calculus, dx_coords);
        const Calculus::DualForm1 primal_dx = primal_calculus.flat(primal_dx_field);
        const Calculus::PrimalVectorField dual_dx_field(dual_calculus, dx_coords);
        const Calculus::PrimalForm1 dual_dx = dual_calculus.flat(dual_dx_field);

        {
            Board2D board;
            board << domain;
            board << primal_calculus;
            board << primal_dx << primal_dx_field;
            board << dual_calculus;
            board << dual_dx << dual_dx_field;
            board.saveSVG("operators_flat_dx_dual.svg");
        }

        const Calculus::DualVectorField primal_dy_field(primal_calculus, dy_coords);
        const Calculus::DualForm1 primal_dy = primal_calculus.flat(primal_dy_field);
        const Calculus::PrimalVectorField dual_dy_field(dual_calculus, dy_coords);
        const Calculus::PrimalForm1 dual_dy = dual_calculus.flat(dual_dy_field);

        {
            Board2D board;
            board << domain;
            board << primal_calculus;
            board << primal_dy << primal_dy_field;
            board << dual_calculus;
            board << dual_dy << dual_dy_field;
            board.saveSVG("operators_flat_dy_dual.svg");
        }

#if defined(TEST_HARDCODED_ORDER)
        Calculus::PrimalForm1::Container dx_container(7);
        dx_container << 0, -1, -1, 0, 1, 0, 1;
        Calculus::PrimalForm1::Container dxp_container(7);
        dxp_container << 0, 0, 1, 1, 0, -1, -1;
        FATAL_ERROR( primal_dx.myContainer == dx_container );
        FATAL_ERROR( dual_dx.myContainer == dxp_container );

        Calculus::PrimalForm1::Container dy_container(7);
        dy_container << -1, 0, 0, -1, 0, 1, 0;
        Calculus::PrimalForm1::Container dyp_container(7);
        dyp_container << -1, 1, 0, 0, -1, 0, 0;
        FATAL_ERROR( primal_dy.myContainer == dy_container );
        FATAL_ERROR( dual_dy.myContainer == dyp_container );
#endif
    }

    trace.endBlock();


    trace.endBlock();
}


int
main()
{
#if !defined(TEST_HARDCODED_ORDER)
    trace.warning() << "hardcoded order tests are NOT performed" << endl;
#endif
    test_manual_operators_3d();
    test_manual_operators_2d();
    test_linear_ring();
    test_linear_structure();
#if !defined(TEST_HARDCODED_ORDER)
    trace.warning() << "hardcoded order tests are NOT performed" << endl;
#endif
    return 0;
}

