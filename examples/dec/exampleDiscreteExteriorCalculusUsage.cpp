/// @file dec/exampleDiscreteExteriorCalculusUsage.cpp
/**
   Example of vector field manipulation using Discrete Exterior Calculus.
   @see \ref sectDECIntroduction
   \image html usage_primal_one_form_sharp_flat.png "Flat sharped primal gradient vector field."
   \example dec/exampleDiscreteExteriorCalculusUsage.cpp
**/
#include <string>

#include "DECExamplesCommon.h"

//! [usage_calculus_headers]
// always include EigenSupport.h before any other Eigen headers
#include "DGtal/math/linalg/EigenSupport.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusSolver.h"
#include "DGtal/dec/DiscreteExteriorCalculusFactory.h"
//! [usage_calculus_headers]

#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/readers/GenericReader.h"

using namespace std;
using namespace DGtal;

void usage2d()
{
    trace.beginBlock("2d discrete exterior calculus usage");

    const Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(9,9));

    //! [usage_calculus_typedef]
    typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus;
    typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;
    //! [usage_calculus_typedef]

    // create discrete exterior calculus from set without border
    {
    //! [usage_calculus_definition_without_border]
    Calculus calculus = CalculusFactory::createFromDigitalSet(generateRingSet(domain), false);

    calculus.eraseCell(calculus.myKSpace.uSpel(Z2i::Point(8, 5)));

    calculus.updateIndexes();
    //! [usage_calculus_definition_without_border]

        trace.info() << calculus << endl;

        Board2D board;
        board << domain;
        board << calculus;
        board.saveSVG("usage_calculus_without_border.svg");
    }

    // create discrete exterior calculus from set with border
    //! [usage_calculus_definition_with_border]
    Calculus calculus = CalculusFactory::createFromDigitalSet(generateRingSet(domain), true);

    calculus.eraseCell(calculus.myKSpace.uSpel(Z2i::Point(8, 5)));
    calculus.eraseCell(calculus.myKSpace.uCell(Z2i::Point(18, 11)));

    calculus.updateIndexes();
    //! [usage_calculus_definition_with_border]

    trace.info() << calculus << endl;

    {
        Board2D board;
        board << domain;
        board << calculus;
        board.saveSVG("usage_calculus_with_border.svg");
    }

    const Z2i::Point center(13,7);

    // primal path
    {
        trace.info() << "primal path" << endl;

        // create primal 0-form and fill it with euclidian metric
        //! [usage_primal_fill_zero_form]
        Calculus::PrimalForm0 primal_zero_form(calculus);
        for (Calculus::Index index=0; index<primal_zero_form.length(); index++)
        {
            const Calculus::SCell& cell = primal_zero_form.getSCell(index);
            const Calculus::Scalar& value = Z2i::l2Metric(calculus.myKSpace.sKCoords(cell), center)/2;
            primal_zero_form.myContainer(index) = value;
        }
        //! [usage_primal_fill_zero_form]
        // one can do linear algebra operation between equaly typed kforms
        //! [usage_primal_form_algebra]
        const Calculus::PrimalForm0 foo = 2 * primal_zero_form + primal_zero_form;
        //! [usage_primal_form_algebra]

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << primal_zero_form;
            board.saveSVG("usage_primal_zero_form.svg");
        }

        // create primal gradient vector field and primal derivative one form
        //! [usage_primal_gradient]
        const Calculus::PrimalDerivative0 primal_zero_derivative = calculus.derivative<0, PRIMAL>();
        const Calculus::PrimalForm1 primal_one_form = primal_zero_derivative * primal_zero_form;
        const Calculus::PrimalVectorField primal_vector_field = calculus.sharp(primal_one_form);
        //! [usage_primal_gradient]

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << primal_one_form;
            board << primal_vector_field;
            board.saveSVG("usage_primal_one_form.svg");
        }

        // test primal flat and sharp
        //! [usage_primal_flat_sharp]
        const Calculus::PrimalForm1 flat_sharp_primal_one_form = calculus.flat(primal_vector_field);
        const Calculus::PrimalVectorField sharp_flat_primal_vector_field = calculus.sharp(flat_sharp_primal_one_form);
        //! [usage_primal_flat_sharp]

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << flat_sharp_primal_one_form;
            board << sharp_flat_primal_vector_field;
            board.saveSVG("usage_primal_one_form_sharp_flat.svg");
        }

        // create dual gradient vector field and hodge*d dual one form
        //! [usage_primal_hodge_gradient]
        const Calculus::PrimalHodge1 primal_one_hodge = calculus.hodge<1, PRIMAL>();
        const Calculus::DualForm1 dual_one_form = primal_one_hodge * primal_zero_derivative * primal_zero_form;
        const Calculus::DualVectorField dual_vector_field = calculus.sharp(dual_one_form);
        //! [usage_primal_hodge_gradient]

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << dual_one_form;
            board << dual_vector_field;
            board << primal_vector_field;
            board.saveSVG("usage_primal_one_form_hodge.svg");
        }
    }

    // dual path
    {
        trace.info() << "dual path" << endl;

        // create dual 0-form and fill it with euclidian metric
        Calculus::DualForm0 dual_zero_form(calculus);
        for (Calculus::Index index=0; index<dual_zero_form.length(); index++)
        {
            const Calculus::SCell& cell = dual_zero_form.getSCell(index);
            const Calculus::Scalar& value = Z2i::l2Metric(calculus.myKSpace.sKCoords(cell), center)/2;
            dual_zero_form.myContainer(index) = value;
        }

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << dual_zero_form;
            board.saveSVG("usage_dual_zero_form.svg");
        }

        // create dual gradient vector field and dual derivative one form
        const Calculus::DualDerivative0 dual_zero_derivative = calculus.derivative<0, DUAL>();
        const Calculus::DualForm1 dual_one_form = dual_zero_derivative * dual_zero_form;
        const Calculus::DualVectorField dual_vector_field = calculus.sharp(dual_one_form);

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << dual_one_form;
            board << dual_vector_field;
            board.saveSVG("usage_dual_one_form.svg");
        }

        // test primal flat and sharp
        const Calculus::DualForm1 flat_sharp_dual_one_form = calculus.flat(dual_vector_field);
        const Calculus::DualVectorField sharp_flat_dual_vector_field = -calculus.sharp(flat_sharp_dual_one_form);

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << flat_sharp_dual_one_form;
            board << -sharp_flat_dual_vector_field;
            board.saveSVG("usage_dual_one_form_sharp_flat.svg");
        }

        // create primal gradient vector field and hodge*d primal one form
        const Calculus::DualHodge1 dual_one_hodge = calculus.hodge<1, DUAL>();
        const Calculus::PrimalForm1 primal_one_form = dual_one_hodge * dual_zero_derivative * dual_zero_form;
        const Calculus::PrimalVectorField primal_vector_field = calculus.sharp(primal_one_form);

        {
            Board2D board;
            board << domain;
            board << calculus;
            board << primal_one_form;
            board << primal_vector_field;
            board << dual_vector_field;
            board.saveSVG("usage_dual_one_form_hodge.svg");
        }
    }

    trace.endBlock();
}

int main()
{
    usage2d();

    return 0;
}

