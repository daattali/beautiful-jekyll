/// @file dec/exampleDiscreteExteriorCalculusSolve.cpp
/**
   Example of primal and dual Helmoltz decomposition in 2D and 3D using Discrete Exterior Calculus.
   @see \ref sectDECHelmoltzProblem
   \image  html  solve_2d_primal_decomposition_calculusSmall.png "Primal Helmoltz decomposition harmonic component."
   \example dec/exampleDiscreteExteriorCalculusSolve.cpp
**/

#include <string>

#include <QApplication>

#include "DECExamplesCommon.h"

// always include EigenSupport.h before any other Eigen headers
#include "DGtal/math/linalg/EigenSupport.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusSolver.h"
#include "DGtal/dec/DiscreteExteriorCalculusFactory.h"

#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/readers/GenericReader.h"

using namespace DGtal;
using namespace std;

void solve2d_laplace()
{
    trace.beginBlock("2d discrete exterior calculus solve laplace");

    const Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(9,9));

    // create discrete exterior calculus from set
    //! [calculus_creation]
    typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus;
    typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;
    Calculus calculus = CalculusFactory::createFromDigitalSet(generateRingSet(domain));
    //! [calculus_creation]
    trace.info() << calculus << endl;

    //! [laplace_definition]
    Calculus::DualIdentity0 laplace = calculus.laplace<DUAL>() + 0.01 * calculus.identity<0, DUAL>();
    //! [laplace_definition]
    trace.info() << "laplace = " << laplace << endl;

    //! [dirac_definition]
    Calculus::DualForm0 dirac(calculus);
    dirac.myContainer(calculus.getCellIndex( calculus.myKSpace.uSpel(Z2i::Point(2,5))) ) = 1;
    //! [dirac_definition]

    {
        Board2D board;
        board << domain;
        board << dirac;
        board.saveSVG("solve_laplace_calculus.svg");
    }

    { // simplicial llt
        trace.beginBlock("simplicial llt");

        //! [solve_llt]
        typedef EigenLinearAlgebraBackend::SolverSimplicialLLT LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::DualForm0 solution = solver.solve(dirac);

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        //! [solve_llt]
        trace.info() << solution << endl;
        trace.endBlock();

        Board2D board;
        board << domain;
        board << solution;
        board.saveSVG("solve_laplace_simplicial_llt.svg");
    }

    { // simplicial ldlt
        trace.beginBlock("simplicial ldlt");

        //! [solve_ldlt]
        typedef EigenLinearAlgebraBackend::SolverSimplicialLDLT LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::DualForm0 solution = solver.solve(dirac);

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        //! [solve_ldlt]
        trace.info() << solution << endl;
        trace.endBlock();

        Board2D board;
        board << domain;
        board << solution;
        board.saveSVG("solve_laplace_simplicial_ldlt.svg");
    }

    { // conjugate gradient
        trace.beginBlock("conjugate gradient");

        //! [solve_conjugate_gradient]
        typedef EigenLinearAlgebraBackend::SolverConjugateGradient LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::DualForm0 solution = solver.solve(dirac);
        //! [solve_conjugate_gradient]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << solution << endl;
        trace.endBlock();

        Board2D board;
        board << domain;
        board << solution;
        board.saveSVG("solve_laplace_conjugate_gradient.svg");
    }

    { // biconjugate gradient stabilized
        trace.beginBlock("biconjugate gradient stabilized (bicgstab)");

        //! [solve_biconjugate_gradient]
        typedef EigenLinearAlgebraBackend::SolverBiCGSTAB LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::DualForm0 solution = solver.solve(dirac);
        //! [solve_biconjugate_gradient]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << solution << endl;
        trace.endBlock();

        Board2D board;
        board << domain;
        board << solution;
        board.saveSVG("solve_laplace_bicgstab.svg");
    }

    { // sparselu
        trace.beginBlock("sparse lu");

        //! [solve_sparse_lu]
        typedef EigenLinearAlgebraBackend::SolverSparseLU LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;

        Solver solver;
        solver.compute(laplace);
        Calculus::DualForm0 solution = solver.solve(dirac);
        //! [solve_sparse_lu]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << solution << endl;
        trace.endBlock();

        Board2D board;
        board << domain;
        board << solution;
        board.saveSVG("solve_laplace_sparse_lu.svg");
    }

    { // sparseqr
        trace.beginBlock("sparse qr");

        //! [solve_sparse_qr]
        typedef EigenLinearAlgebraBackend::SolverSparseQR LinearAlgebraSolver;
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;

        Solver solver;
        solver.compute(-laplace);
        Calculus::DualForm0 solution = -solver.solve(dirac);
        //! [solve_sparse_qr]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << solution << endl;
        trace.endBlock();

        Board2D board;
        board << domain;
        board << solution;
        board.saveSVG("solve_laplace_sparse_qr.svg");
    }

    trace.endBlock();
}

void solve2d_dual_decomposition()
{
    trace.beginBlock("2d discrete exterior calculus solve dual helmoltz decomposition");

    const Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(44,29));

    // create discrete exterior calculus from set
    typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus;
    typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;
    Calculus calculus = CalculusFactory::createFromDigitalSet(generateDoubleRingSet(domain));
    trace.info() << calculus << endl;

    // choose linear solver
    typedef EigenLinearAlgebraBackend::SolverSparseQR LinearAlgebraSolver;

    //! [2d_dual_decomposition_operator_definition]
    const Calculus::DualDerivative0 d0 = calculus.derivative<0, DUAL>();
    const Calculus::DualDerivative1 d1 = calculus.derivative<1, DUAL>();
    const Calculus::PrimalDerivative0 d0p = calculus.derivative<0, PRIMAL>();
    const Calculus::PrimalDerivative1 d1p = calculus.derivative<1, PRIMAL>();
    const Calculus::DualHodge1 h1 = calculus.hodge<1, DUAL>();
    const Calculus::DualHodge2 h2 = calculus.hodge<2, DUAL>();
    const Calculus::PrimalHodge1 h1p = calculus.hodge<1, PRIMAL>();
    const Calculus::PrimalHodge2 h2p = calculus.hodge<2, PRIMAL>();
    const LinearOperator<Calculus, 1, DUAL, 0, DUAL> ad1 = h2p * d1p * h1;
    const LinearOperator<Calculus, 2, DUAL, 1, DUAL> ad2 = h1p * d0p * h2;
    //! [2d_dual_decomposition_operator_definition]

    //! [2d_dual_decomposition_input_field_definition]
    Calculus::DualVectorField input_vector_field(calculus);
    for (Calculus::Index ii=0; ii<input_vector_field.length(); ii++)
    {
        const Z2i::RealPoint cell_center = Z2i::RealPoint(input_vector_field.getSCell(ii).preCell().coordinates)/2.;
        input_vector_field.myCoordinates(ii, 0) = cos(-.5*cell_center[0]+ .3*cell_center[1]);
        input_vector_field.myCoordinates(ii, 1) = cos(.4*cell_center[0]+ .8*cell_center[1]);
    }
    trace.info() << input_vector_field << endl;

    const Calculus::DualForm1 input_one_form = calculus.flat(input_vector_field);
    const Calculus::DualForm0 input_one_form_anti_derivated = ad1 * input_one_form;
    const Calculus::DualForm2 input_one_form_derivated = d1 * input_one_form;
    //! [2d_dual_decomposition_input_field_definition]

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << CustomStyle("KForm", new KFormStyle2D(-1, 1));
        board << input_one_form;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(.75));
        board << input_vector_field;
        board.saveSVG("solve_2d_dual_decomposition_calculus.svg");
    }


    Calculus::DualForm0 solution_curl_free(calculus);
    { // solve curl free problem
        trace.beginBlock("solving curl free component");

        //! [2d_dual_decomposition_curl_free_solve]
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, DUAL, 0, DUAL> Solver;
        Solver solver;
        solver.compute(ad1 * d0);
        solution_curl_free = solver.solve(input_one_form_anti_derivated);
        //! [2d_dual_decomposition_curl_free_solve]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << "min=" << solution_curl_free.myContainer.minCoeff() << " max=" << solution_curl_free.myContainer.maxCoeff() << endl;
        trace.endBlock();
    }

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << solution_curl_free;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(.75));
        board << calculus.sharp(d0*solution_curl_free);
        board.saveSVG("solve_2d_dual_decomposition_curl_free.svg");
    }

    Calculus::DualForm2 solution_div_free(calculus);
    { // solve divergence free problem
        trace.beginBlock("solving divergence free component");

        //! [2d_dual_decomposition_div_free_solve]
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 2, DUAL, 2, DUAL> Solver;
        Solver solver;
        solver.compute(d1 * ad2);
        solution_div_free = solver.solve(input_one_form_derivated);
        //! [2d_dual_decomposition_div_free_solve]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << "min=" << solution_div_free.myContainer.minCoeff() << " max=" << solution_div_free.myContainer.maxCoeff() << endl;
        trace.endBlock();
    }

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << solution_div_free;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(1.5));
        board << calculus.sharp(ad2*solution_div_free);
        board.saveSVG("solve_2d_dual_decomposition_div_free.svg");
    }

    //! [2d_dual_decomposition_solution]
    const Calculus::DualForm1 solution_harmonic = input_one_form - d0*solution_curl_free - ad2*solution_div_free;
    //! [2d_dual_decomposition_solution]
    trace.info() << "min=" << solution_harmonic.myContainer.minCoeff() << " max=" << solution_harmonic.myContainer.maxCoeff() << endl;

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << solution_harmonic;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(20));
        board << calculus.sharp(solution_harmonic);
        board.saveSVG("solve_2d_dual_decomposition_harmonic.svg");
    }

    trace.endBlock();
}

void solve2d_primal_decomposition()
{
    trace.beginBlock("2d discrete exterior calculus solve primal helmoltz decomposition");

    const Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(44,29));

    // create discrete exterior calculus from set
    typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus;
    typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;
    Calculus calculus = CalculusFactory::createFromDigitalSet(generateDoubleRingSet(domain));
    trace.info() << calculus << endl;

    // choose linear solver
    typedef EigenLinearAlgebraBackend::SolverSparseQR LinearAlgebraSolver;

    //! [2d_primal_decomposition_operator_definition]
    const Calculus::PrimalDerivative0 d0 = calculus.derivative<0, PRIMAL>();
    const Calculus::PrimalDerivative1 d1 = calculus.derivative<1, PRIMAL>();
    const Calculus::DualDerivative0 d0p = calculus.derivative<0, DUAL>();
    const Calculus::DualDerivative1 d1p = calculus.derivative<1, DUAL>();
    const Calculus::PrimalHodge1 h1 = calculus.hodge<1, PRIMAL>();
    const Calculus::PrimalHodge2 h2 = calculus.hodge<2, PRIMAL>();
    const Calculus::DualHodge1 h1p = calculus.hodge<1, DUAL>();
    const Calculus::DualHodge2 h2p = calculus.hodge<2, DUAL>();
    const LinearOperator<Calculus, 1, PRIMAL, 0, PRIMAL> ad1 = h2p * d1p * h1;
    const LinearOperator<Calculus, 2, PRIMAL, 1, PRIMAL> ad2 = h1p * d0p * h2;
    //! [2d_primal_decomposition_operator_definition]

    //! [2d_primal_decomposition_input_field_definition]
    Calculus::PrimalVectorField input_vector_field(calculus);
    for (Calculus::Index ii=0; ii<input_vector_field.length(); ii++)
    {
        const Z2i::RealPoint cell_center = Z2i::RealPoint(input_vector_field.getSCell(ii).preCell().coordinates)/2.;
        input_vector_field.myCoordinates(ii, 0) = cos(-.5*cell_center[0]+ .3*cell_center[1]);
        input_vector_field.myCoordinates(ii, 1) = cos(.4*cell_center[0]+ .8*cell_center[1]);
    }
    trace.info() << input_vector_field << endl;

    const Calculus::PrimalForm1 input_one_form = calculus.flat(input_vector_field);
    const Calculus::PrimalForm0 input_one_form_anti_derivated = ad1 * input_one_form;
    const Calculus::PrimalForm2 input_one_form_derivated = d1 * input_one_form;
    //! [2d_primal_decomposition_input_field_definition]

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << input_one_form;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(.75));
        board << input_vector_field;
        board.saveSVG("solve_2d_primal_decomposition_calculus.svg");
    }


    Calculus::PrimalForm0 solution_curl_free(calculus);
    { // solve curl free problem
        trace.beginBlock("solving curl free component");

        //! [2d_primal_decomposition_curl_free_solve]
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, PRIMAL, 0, PRIMAL> Solver;
        Solver solver;
        solver.compute(ad1 * d0);
        solution_curl_free = solver.solve(input_one_form_anti_derivated);
        //! [2d_primal_decomposition_curl_free_solve]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << "min=" << solution_curl_free.myContainer.minCoeff() << " max=" << solution_curl_free.myContainer.maxCoeff() << endl;
        trace.endBlock();
    }

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << solution_curl_free;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(.75));
        board << calculus.sharp(d0*solution_curl_free);
        board.saveSVG("solve_2d_primal_decomposition_curl_free.svg");
    }

    Calculus::PrimalForm2 solution_div_free(calculus);
    { // solve divergence free problem
        trace.beginBlock("solving divergence free component");

        //! [2d_primal_decomposition_div_free_solve]
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 2, PRIMAL, 2, PRIMAL> Solver;
        Solver solver;
        solver.compute(d1 * ad2);
        solution_div_free = solver.solve(input_one_form_derivated);
        //! [2d_primal_decomposition_div_free_solve]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << "min=" << solution_div_free.myContainer.minCoeff() << " max=" << solution_div_free.myContainer.maxCoeff() << endl;
        trace.endBlock();
    }

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << solution_div_free;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(1.5));
        board << calculus.sharp(ad2*solution_div_free);
        board.saveSVG("solve_2d_primal_decomposition_div_free.svg");
    }

    //! [2d_primal_decomposition_solution]
    const Calculus::PrimalForm1 solution_harmonic = input_one_form - d0*solution_curl_free - ad2*solution_div_free;
    //! [2d_primal_decomposition_solution]
    trace.info() << "min=" << solution_harmonic.myContainer.minCoeff() << " max=" << solution_harmonic.myContainer.maxCoeff() << endl;

    {
        Board2D board;
        board << domain;
        board << calculus;
        board << solution_harmonic;
        board << CustomStyle("VectorField", new VectorFieldStyle2D(30));
        board << calculus.sharp(solution_harmonic);
        board.saveSVG("solve_2d_primal_decomposition_harmonic.svg");
    }

    trace.endBlock();
}

void solve3d_decomposition()
{
    trace.beginBlock("3d discrete exterior calculus solve helmoltz decomposition");

    const Z3i::Domain domain(Z3i::Point(0,0,0), Z3i::Point(19,19,9));

    // choose linear solver
    typedef EigenLinearAlgebraBackend::SolverSparseQR LinearAlgebraSolver;

    //! [3d_decomposition_structure]
    // create discrete exterior calculus from set
    typedef DiscreteExteriorCalculus<3, 3, EigenLinearAlgebraBackend> Calculus;
    Calculus calculus;
    calculus.initKSpace<Z3i::Domain>(domain);

    // outer ring
    for (int kk=2; kk<=18; kk++)
        for (int ll=4; ll<=36; ll++)
        {
            { // bottom
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,4,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::NEG;
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // top
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,36,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // left
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(4,ll,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = ( *calculus.myKSpace.uDirs(cell) == 2 ? Calculus::KSpace::NEG : Calculus::KSpace::POS );
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // right
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(36,ll,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = ( *calculus.myKSpace.uDirs(cell) == 2 ? Calculus::KSpace::POS : Calculus::KSpace::NEG );
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

        }

    // inner ring
    for (int kk=2; kk<=18; kk++)
        for (int ll=16; ll<=24; ll++)
        {
            { // bottom
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,16,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = ( *calculus.myKSpace.uDirs(cell) == 0 ? Calculus::KSpace::NEG : Calculus::KSpace::POS );
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // top
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,24,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = ( *calculus.myKSpace.uDirs(cell) == 0 ? Calculus::KSpace::POS : Calculus::KSpace::NEG );
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // left
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(16,ll,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // right
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(24,ll,kk));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::NEG;
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }
        }

    // back and front
    for (int kk=4; kk<=36; kk++)
        for (int ll=0; ll<=12; ll++)
        {
            { // back
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(4+ll,kk,2));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // front
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(4+ll,kk,18));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::NEG;
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // back
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(24+ll,kk,2));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // front
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(24+ll,kk,18));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::NEG;
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }
        }

    // back and front
    for (int kk=0; kk<=12; kk++)
        for (int ll=16; ll<=24; ll++)
        {
            { // back
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,4+kk,2));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // front
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,4+kk,18));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::NEG;
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // back
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,24+kk,2));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 2:
                        sign = Calculus::KSpace::NEG;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }

            { // front
                const Calculus::Cell cell = calculus.myKSpace.uCell(Z3i::Point(ll,24+kk,18));
                const Dimension dim = calculus.myKSpace.uDim(cell);
                Calculus::KSpace::Sign sign = Calculus::KSpace::POS;
                switch (dim)
                {
                    case 0:
                        sign = Calculus::KSpace::POS;
                        break;
                    case 1:
                        sign = Calculus::KSpace::NEG;
                        break;
                    case 2:
                        sign = Calculus::KSpace::POS;
                        break;
                    default:
                        break;
                }
                calculus.insertSCell( calculus.myKSpace.signs(cell, sign) );
            }
        }

    calculus.updateIndexes();
    //! [3d_decomposition_structure]

    trace.info() << calculus << endl;

    {
        typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
        Viewer* viewer = new Viewer(calculus.myKSpace);
        viewer->show();
        viewer->setWindowTitle("structure");
        (*viewer) << CustomColors3D(DGtal::Color(255,0,0), DGtal::Color(0,0,0));
        (*viewer) << domain;
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, calculus);
        (*viewer) << Viewer::updateDisplay;
    }

    //! [3d_decomposition_operator_definition]
    const Calculus::PrimalDerivative0 d0 = calculus.derivative<0, PRIMAL>();
    const Calculus::PrimalDerivative1 d1 = calculus.derivative<1, PRIMAL>();
    const Calculus::DualDerivative1 d1p = calculus.derivative<1, DUAL>();
    const Calculus::DualDerivative2 d2p = calculus.derivative<2, DUAL>();
    const Calculus::PrimalHodge1 h1 = calculus.hodge<1, PRIMAL>();
    const Calculus::PrimalHodge2 h2 = calculus.hodge<2, PRIMAL>();
    const Calculus::DualHodge2 h2p = calculus.hodge<2, DUAL>();
    const Calculus::DualHodge3 h3p = calculus.hodge<3, DUAL>();
    const LinearOperator<Calculus, 1, PRIMAL, 0, PRIMAL> ad1 = h3p * d2p * h1;
    const LinearOperator<Calculus, 2, PRIMAL, 1, PRIMAL> ad2 = h2p * d1p * h2;
    //! [3d_decomposition_operator_definition]

    {
        const Calculus::PrimalIdentity0 laplace = calculus.laplace<PRIMAL>();
        const Eigen::VectorXd laplace_diag = laplace.myContainer.diagonal();

        boost::array<int, 7> degrees;
        std::fill(degrees.begin(), degrees.end(), 0);
        for (int kk=0; kk<laplace_diag.rows(); kk++)
        {
            const int degree = laplace_diag[kk];
            ASSERT( degree >= 0 );
            ASSERT( static_cast<unsigned int>(degree) < degrees.size() );
            degrees[degree] ++;
        }

        trace.info() << "node degrees" << endl;
        for (int kk=0; kk<7; kk++)
            trace.info() << kk << " " << degrees[kk] << endl;
    }

    //! [3d_decomposition_input_field_definition]
    Calculus::PrimalVectorField input_vector_field(calculus);
    for (Calculus::Index ii=0; ii<input_vector_field.length(); ii++)
    {
        const Z3i::RealPoint cell_center = Z3i::RealPoint(input_vector_field.getSCell(ii).preCell().coordinates)/2.;
        input_vector_field.myCoordinates(ii, 0) = -cos(-.3*cell_center[0] + .6*cell_center[1] + .8*cell_center[2]);
        input_vector_field.myCoordinates(ii, 1) = sin(.8*cell_center[0] + .3*cell_center[1] - .4*cell_center[2]);
        input_vector_field.myCoordinates(ii, 2) = -cos(cell_center[2]*.5);
    }
    trace.info() << input_vector_field << endl;

    const Calculus::PrimalForm1 input_one_form = calculus.flat(input_vector_field);
    //! [3d_decomposition_input_field_definition]
    const Calculus::PrimalForm0 input_one_form_anti_derivated = ad1 * input_one_form;
    const Calculus::PrimalForm2 input_one_form_derivated = d1 * input_one_form;

    {
        typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
        Viewer* viewer = new Viewer(calculus.myKSpace);
        viewer->show();
        viewer->setWindowTitle("input vector field");
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, input_one_form);
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, input_one_form_derivated);
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, input_one_form_anti_derivated);
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, input_vector_field);
        (*viewer) << Viewer::updateDisplay;
    }

    Calculus::PrimalForm0 solution_curl_free(calculus);
    { // solve curl free problem
        trace.beginBlock("solving curl free component");

        //! [3d_decomposition_curl_free_solve]
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 0, PRIMAL, 0, PRIMAL> Solver;
        Solver solver;
        solver.compute(ad1 * d0);
        solution_curl_free = solver.solve(input_one_form_anti_derivated);
        //! [3d_decomposition_curl_free_solve]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << "min=" << solution_curl_free.myContainer.minCoeff() << " max=" << solution_curl_free.myContainer.maxCoeff() << endl;
        trace.endBlock();
    }

    {
        typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
        Viewer* viewer = new Viewer(calculus.myKSpace);
        viewer->show();
        viewer->setWindowTitle("curl free solution");
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, solution_curl_free);
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, calculus.sharp(d0*solution_curl_free));
        (*viewer) << Viewer::updateDisplay;
    }

    Calculus::PrimalForm2 solution_div_free(calculus);
    { // solve divergence free problem
        trace.beginBlock("solving divergence free component");

        //! [3d_decomposition_div_free_solve]
        typedef DiscreteExteriorCalculusSolver<Calculus, LinearAlgebraSolver, 2, PRIMAL, 2, PRIMAL> Solver;
        Solver solver;
        solver.compute(d1 * ad2);
        solution_div_free = solver.solve(input_one_form_derivated);
        //! [3d_decomposition_div_free_solve]

        trace.info() << solver.isValid() << " " << solver.myLinearAlgebraSolver.info() << endl;
        trace.info() << "min=" << solution_div_free.myContainer.minCoeff() << " max=" << solution_div_free.myContainer.maxCoeff() << endl;
        trace.endBlock();
    }

    {
        typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
        Viewer* viewer = new Viewer(calculus.myKSpace);
        viewer->show();
        viewer->setWindowTitle("div free solution");
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, solution_div_free);
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, calculus.sharp(ad2*solution_div_free));
        (*viewer) << Viewer::updateDisplay;
    }

    //! [3d_decomposition_solution]
    const Calculus::PrimalForm1 solution_harmonic = input_one_form - d0*solution_curl_free - ad2*solution_div_free;
    //! [3d_decomposition_solution]
    trace.info() << "min=" << solution_harmonic.myContainer.minCoeff() << " max=" << solution_harmonic.myContainer.maxCoeff() << endl;

    {
        typedef Viewer3D<Z3i::Space, Z3i::KSpace> Viewer;
        Viewer* viewer = new Viewer(calculus.myKSpace);
        viewer->show();
        viewer->setWindowTitle("harmonic");
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, solution_harmonic);
        Display3DFactory<Z3i::Space, Z3i::KSpace>::draw(*viewer, calculus.sharp(solution_harmonic), 10.);
        (*viewer) << Viewer::updateDisplay;
    }

    trace.endBlock();
}

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    solve2d_laplace();
    solve2d_dual_decomposition();
    solve2d_primal_decomposition();
    solve3d_decomposition();

    return app.exec();
}
