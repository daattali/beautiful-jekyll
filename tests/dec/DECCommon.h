#if !defined(__DEC_TESTS_COMMON_H__)
#define __DEC_TESTS_COMMON_H__

#include <list>

#include "DGtal/dec/DiscreteExteriorCalculusFactory.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/math/linalg/EigenSupport.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusSolver.h"
#include "DGtal/dec/CDiscreteExteriorCalculusVectorSpace.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"

template <typename Container>
bool
is_all_zero(const Container& container)
{
    for (typename Container::Index ii=0; ii<container.rows(); ii++)
        for (typename Container::Index jj=0; jj<container.cols(); jj++)
            if (container.coeff(ii,jj) != 0)
                return false;
    return true;
}

template <typename Container>
bool
equal(const Container& aa, const Container& bb)
{
    if (aa.rows() != bb.rows()) return false;
    if (aa.cols() != bb.cols()) return false;
    for (typename Container::Index ii=0; ii<aa.rows(); ii++)
        for (typename Container::Index jj=0; jj<aa.cols(); jj++)
            if (aa.coeff(ii,jj) != bb.coeff(ii,jj))
                return false;
    return true;
}

template <typename Container, typename Value>
bool
is_identity(const Container& container, const Value& value)
{
    for (typename Container::Index ii=0; ii<container.rows(); ii++)
        for (typename Container::Index jj=0; jj<container.cols(); jj++)
        {
            const Value foo = static_cast<Value>(container.coeff(ii,jj));
            if ((ii != jj && foo != 0) || (ii == jj && foo != value))
                return false;
        }
    return true;
}

//DC: changing order to int (to match with -1 specialization)
template <typename Calculus, int order>
struct HodgeTester
{
    BOOST_STATIC_ASSERT(( order <= Calculus::dimensionEmbedded ));

    static bool test(const Calculus& calculus)
    {
        DGtal::trace.info() << "testing identity operators " << order << std::endl;

        { // test identity operator
            typedef DGtal::LinearOperator<Calculus, order, DGtal::PRIMAL, order, DGtal::PRIMAL> PrimalIdentity;
            PrimalIdentity primal_identity = calculus.template identity<order, DGtal::PRIMAL>();
            if (!is_identity(primal_identity.myContainer, 1)) return false;

            typedef DGtal::KForm<Calculus, order, DGtal::PRIMAL> SolveForm;
            SolveForm input(calculus);
            SolveForm output = primal_identity * input;
            typedef typename Calculus::LinearAlgebraBackend LinearAlgebraBackend;
            typedef typename LinearAlgebraBackend::SolverConjugateGradient LinearSolver;
            typedef DGtal::DiscreteExteriorCalculusSolver<Calculus, LinearSolver, order, DGtal::PRIMAL, order, DGtal::PRIMAL> Solver;
            Solver solver;
            SolveForm input_solved = solver.compute(primal_identity).solve(output);
            //if (input_solved != input) return false;

            typedef DGtal::LinearOperator<Calculus, order, DGtal::DUAL, order, DGtal::DUAL> DualIdentity;
            DualIdentity dual_identity = calculus.template identity<order, DGtal::DUAL>();
            if (!is_identity(dual_identity.myContainer, 1)) return false;
        }

        typedef DGtal::LinearOperator<Calculus, order, DGtal::PRIMAL, Calculus::dimensionEmbedded-order, DGtal::DUAL> PrimalHodge;
        typedef DGtal::LinearOperator<Calculus, Calculus::dimensionEmbedded-order, DGtal::DUAL, order, DGtal::PRIMAL> DualHodge;
        const PrimalHodge primal_hodge = calculus.template hodge<order, DGtal::PRIMAL>();
        const DualHodge dual_hodge= calculus.template hodge<Calculus::dimensionEmbedded-order, DGtal::DUAL>();

        DGtal::trace.info() << "testing primal to primal hodge composition order " << order << std::endl;

        { // test primal to primal composition
            typedef DGtal::LinearOperator<Calculus, order, DGtal::PRIMAL, order, DGtal::PRIMAL> PrimalPrimal;
            PrimalPrimal primal_primal = dual_hodge * primal_hodge;
            if (!is_identity(primal_primal.myContainer, pow(-1, order*(Calculus::dimensionEmbedded-order)))) return false;
        }

        DGtal::trace.info() << "testing dual to dual hodge composition order " << order << std::endl;

        { // test dual to dual composition
            typedef DGtal::LinearOperator<Calculus, Calculus::dimensionEmbedded-order, DGtal::DUAL, Calculus::dimensionEmbedded-order, DGtal::DUAL> DualDual;
            DualDual dual_dual = primal_hodge * dual_hodge;
            if (!is_identity(dual_dual.myContainer, pow(-1, order*(Calculus::dimensionEmbedded-order)))) return false;
        }

        return HodgeTester<Calculus, order-1>::test(calculus);
    }
};

template <typename Calculus>
struct HodgeTester<Calculus, -1>
{
  static bool test(const Calculus& calculus)
  {
    boost::ignore_unused_variable_warning( calculus );
    return true;
  }
};

template <typename DigitalSet, typename LinearAlgebraBackend>
void
test_hodge(int domain_size)
{
    BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDigitalSet<DigitalSet> ));

    typedef typename DigitalSet::Domain Domain;
    typedef typename DigitalSet::Point Point;
    DGtal::trace.info() << "dimension=" << Point::dimension << std::endl;
    Domain domain(Point(), Point::diagonal(domain_size-1));
    DGtal::trace.info() << "domain=" << domain << std::endl;

    DigitalSet set(domain);
    for (typename Domain::ConstIterator di=domain.begin(), die=domain.end(); di!=die; di++)
    {
        if (std::rand()%4!=0) continue;
        const typename Domain::Point& point = *di;
        set.insertNew(point);
    }
    DGtal::trace.info() << "domain.size()=" << domain.size() << std::endl;
    DGtal::trace.info() << "set.size()=" << set.size() << std::endl;

    typedef DGtal::DiscreteExteriorCalculus<Domain::Space::dimension, Domain::Space::dimension, LinearAlgebraBackend> Calculus;
    Calculus calculus = DGtal::DiscreteExteriorCalculusFactory<LinearAlgebraBackend>::createFromDigitalSet(set);
    {
        DGtal::trace.beginBlock("testing indexes");

        {
            typename Calculus::Properties properties = calculus.getProperties();
            DGtal::trace.info() << "properties.size()=" << properties.size() << std::endl;
        }

        typedef typename Calculus::ConstIterator ConstIterator;
        typedef typename Calculus::Cell Cell;
        typedef typename Calculus::SCell SCell;
        typedef typename Calculus::Index Index;
        typedef typename Calculus::KSpace KSpace;

        bool test_result = true;
        for (ConstIterator iter = calculus.begin(), iter_end = calculus.end(); test_result && iter!=iter_end; iter++)
        {
            const Cell& cell = iter->first;
            const Index& index = calculus.getCellIndex(cell);
            test_result &= (iter->second.index == index);
            const SCell& signed_cell = calculus.myKSpace.signs(cell, iter->second.flipped ? KSpace::NEG : KSpace::POS);
            const SCell& primal_signed_cell = calculus.getSCell(calculus.myKSpace.uDim(cell), DGtal::PRIMAL, index);
            test_result &= (signed_cell == primal_signed_cell);
            const SCell& dual_signed_cell = calculus.getSCell(Calculus::dimensionEmbedded-calculus.myKSpace.uDim(cell), DGtal::DUAL, index);
            test_result &= (signed_cell == dual_signed_cell);
        }
        DGtal::trace.endBlock();

        FATAL_ERROR(test_result);
    }

    {
        DGtal::trace.beginBlock("testing laplace sign");

        const typename Calculus::PrimalIdentity0 primal_laplace = calculus.template laplace<DGtal::PRIMAL>();
        DGtal::trace.info() << "primal_laplace_trace=" << primal_laplace.myContainer.diagonal().sum() << std::endl;
        FATAL_ERROR( ( primal_laplace.myContainer.diagonal().array() >= 0 ).prod() == true );

        const typename Calculus::DualIdentity0 dual_laplace = calculus.template laplace<DGtal::DUAL>();
        DGtal::trace.info() << "dual_laplace_trace=" << dual_laplace.myContainer.diagonal().sum() << std::endl;
        FATAL_ERROR( ( dual_laplace.myContainer.diagonal().array() >= 0 ).prod() == true );

        DGtal::trace.endBlock();
    }

    DGtal::trace.beginBlock("testing hodge");
    bool test_result = HodgeTester<Calculus, Calculus::dimensionEmbedded>::test(calculus);
    DGtal::trace.endBlock();

    FATAL_ERROR(test_result);
}

//DC Order->int (see above)
template <typename Calculus, int order>
struct DerivativeTester
{
    BOOST_STATIC_ASSERT(( order < (int)Calculus::dimensionEmbedded - 1 ));

    static bool test(const Calculus& calculus)
    {
        DGtal::trace.info() << "testing primal derivative composition order " << order << std::endl;

        { // test primal composition
            typedef DGtal::LinearOperator<Calculus, order, DGtal::PRIMAL, order+1, DGtal::PRIMAL> FirstDerivative;
            FirstDerivative first_derivative = calculus.template derivative<order, DGtal::PRIMAL>();
            typedef DGtal::LinearOperator<Calculus, order+1, DGtal::PRIMAL, order+2, DGtal::PRIMAL> SecondDerivative;
            SecondDerivative second_derivative = calculus.template derivative<order+1, DGtal::PRIMAL>();
            typedef DGtal::LinearOperator<Calculus, order, DGtal::PRIMAL, order+2, DGtal::PRIMAL> DoubleDerivative;
            DoubleDerivative double_derivative = second_derivative * first_derivative;
            if (!is_all_zero(double_derivative.myContainer)) return false;
        }

        DGtal::trace.info() << "testing dual derivative composition order " << order << std::endl;

        { // test dual composition
            typedef DGtal::LinearOperator<Calculus, order, DGtal::DUAL, order+1, DGtal::DUAL> FirstDerivative;
            FirstDerivative first_derivative = calculus.template derivative<order, DGtal::DUAL>();
            typedef DGtal::LinearOperator<Calculus, order+1, DGtal::DUAL, order+2, DGtal::DUAL> SecondDerivative;
            SecondDerivative second_derivative = calculus.template derivative<order+1, DGtal::DUAL>();
            typedef DGtal::LinearOperator<Calculus, order, DGtal::DUAL, order+2, DGtal::DUAL> DoubleDerivative;
            DoubleDerivative double_derivative = second_derivative * first_derivative;
            if (!is_all_zero(double_derivative.myContainer)) return false;
        }

        /*
        DGtal::trace.info() << "testing liebnitz rule order " << order << std::endl;

        {
            typedef DGtal::LinearOperator<Calculus, order, DGtal::PRIMAL, order+1, DGtal::PRIMAL> Derivative;
            Derivative derivative = calculus.template derivative<order, DGtal::PRIMAL>();

            typedef DGtal::KForm<Calculus, order, DGtal::PRIMAL> InputForm;
            typedef DGtal::KForm<Calculus, order+1, DGtal::PRIMAL> OutputForm;
            InputForm alpha(calculus), beta(calculus), gamma(calculus);

            for (int kk=0; kk<calculus.kFormLength(order, DGtal::PRIMAL); kk++)
            {
                const double ak = static_cast<double>(random())/RAND_MAX;
                const double bk = static_cast<double>(random())/RAND_MAX;
                alpha.myContainer(kk) = ak;
                beta.myContainer(kk) = bk;
                gamma.myContainer(kk) = ak*bk;
            }

        }
        */

        return DerivativeTester<Calculus, order-1>::test(calculus);
    }
};

template <typename Calculus>
struct DerivativeTester<Calculus, -1>
{
    static bool test(const Calculus& )
    {
        return true;
    }
};

template <typename DigitalSet, typename LinearAlgebraBackend>
void
test_derivative(int domain_size)
{
    BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDigitalSet<DigitalSet> ));

    typedef typename DigitalSet::Domain Domain;
    typedef typename DigitalSet::Point Point;
    DGtal::trace.info() << "dimension=" << Point::dimension << std::endl;
    Domain domain(Point(), Point::diagonal(domain_size-1));
    DGtal::trace.info() << "domain=" << domain << std::endl;

    DigitalSet set(domain);
    for (typename Domain::ConstIterator di=domain.begin(), die=domain.end(); di!=die; di++)
    {
        if (std::rand()%3!=0) continue;
        const typename Domain::Point& point = *di;
        set.insertNew(point);
    }
    DGtal::trace.info() << "domain.size()=" << domain.size() << std::endl;
    DGtal::trace.info() << "set.size()=" << set.size() << std::endl;

    typedef DGtal::DiscreteExteriorCalculusFactory<LinearAlgebraBackend> CalculusFactory;
    typedef DGtal::DiscreteExteriorCalculus<Domain::Space::dimension, Domain::Space::dimension, LinearAlgebraBackend> Calculus;

    {
        DGtal::trace.beginBlock("testing derivative without border");
        Calculus calculus = CalculusFactory::createFromDigitalSet(set, false);

        typename Calculus::Properties properties = calculus.getProperties();
        DGtal::trace.info() << "properties.size()=" << properties.size() << std::endl;

        bool test_result = DerivativeTester<Calculus, (int)Calculus::dimensionEmbedded-2>::test(calculus);
        FATAL_ERROR(test_result);

        DGtal::trace.endBlock();
    }

    {
        DGtal::trace.beginBlock("testing derivative with border");
        Calculus calculus = CalculusFactory::createFromDigitalSet(set, true);

        typename Calculus::Properties properties = calculus.getProperties();
        DGtal::trace.info() << "properties.size()=" << properties.size() << std::endl;

        bool test_result = DerivativeTester<Calculus, (int)Calculus::dimensionEmbedded-2>::test(calculus);
        FATAL_ERROR(test_result);

        DGtal::trace.endBlock();
    }
}

template <typename LinearAlgebraBackend>
void
test_concepts()
{
    DGtal::trace.beginBlock("concepts");

    //FIXME add 1d

    { // 2d
        typedef DGtal::DiscreteExteriorCalculus<2, 2, LinearAlgebraBackend> Calculus;
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm2> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalVectorField> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualVectorField> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative1> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge2> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity2> ));
    }

    { // 2d embedded in 3d
        typedef DGtal::DiscreteExteriorCalculus<2, 3, LinearAlgebraBackend> Calculus;
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm2> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalVectorField> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualVectorField> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative1> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge2> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity2> ));
    }

    { // 3d
        typedef DGtal::DiscreteExteriorCalculus<3, 3, LinearAlgebraBackend> Calculus;
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalForm3> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualForm3> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalVectorField> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualVectorField> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalDerivative2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualDerivative2> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalHodge3> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualHodge3> ));

        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::PrimalIdentity3> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity0> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity1> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity2> ));
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CDiscreteExteriorCalculusVectorSpace<typename Calculus::DualIdentity3> ));
    }

    DGtal::trace.endBlock();
}

template <typename LinearAlgebraBackend>
void
test_hodge_sign()
{
    typedef DGtal::DiscreteExteriorCalculusFactory<LinearAlgebraBackend> CalculusFactory;

    DGtal::trace.beginBlock("testing hodge sign");

    {
        typedef DGtal::DiscreteExteriorCalculus<2, 2, LinearAlgebraBackend> Calculus;
        const DGtal::Z2i::Domain domain;
        const DGtal::Z2i::DigitalSet set(domain);
        const Calculus calculus = CalculusFactory::createFromDigitalSet(set);
        typedef DGtal::Z2i::Point Point;

        // primal point, dual cell
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,0)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,0)), DGtal::DUAL ) == 1 );
        // primal horizontal edge, dual vertical edge
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,0)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,0)), DGtal::DUAL ) == -1 );
        // primal vectical edge, dual horizontal edge
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,1)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,1)), DGtal::DUAL ) == -1 );
        // primal cell, dual point
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,1)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,1)), DGtal::DUAL ) == 1 );
    }

    {
        typedef DGtal::DiscreteExteriorCalculus<3, 3, LinearAlgebraBackend> Calculus;
        const DGtal::Z3i::Domain domain;
        const DGtal::Z3i::DigitalSet set(domain);
        const Calculus calculus = CalculusFactory::createFromDigitalSet(set);
        typedef DGtal::Z3i::Point Point;
        
        // primal point, dual cell
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,0,0)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,0,0)), DGtal::DUAL ) == 1 );
        // primal edge, dual surfel
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,0,0)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,0,0)), DGtal::DUAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,1,0)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,1,0)), DGtal::DUAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,0,1)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,0,1)), DGtal::DUAL ) == 1 );
        // primal surfel, dual edge
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,1,0)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,1,0)), DGtal::DUAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,1,1)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(0,1,1)), DGtal::DUAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,0,1)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,0,1)), DGtal::DUAL ) == 1 );
        // primal cell, dual point
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,1,1)), DGtal::PRIMAL ) == 1 );
        FATAL_ERROR( calculus.hodgeSign( calculus.myKSpace.uFirst(Point(1,1,1)), DGtal::DUAL ) == 1 );
    }

    DGtal::trace.endBlock();
}

void
test_duality()
{
    DGtal::trace.beginBlock("testing duality");

    BOOST_STATIC_ASSERT(( DGtal::OppositeDuality<DGtal::PRIMAL>::duality == DGtal::DUAL ));
    BOOST_STATIC_ASSERT(( DGtal::OppositeDuality<DGtal::DUAL>::duality == DGtal::PRIMAL ));

    DGtal::trace.endBlock();
}

template <typename LinearAlgebraBackend>
void
test_backend(const int& ntime, const int& maxdim)
{
    test_duality();

    test_hodge_sign<LinearAlgebraBackend>();

    for (int kk=0; kk<ntime; kk++)
    {
        typedef DGtal::SpaceND<1, int> Space1;
        typedef DGtal::HyperRectDomain<Space1> Domain1;
        typedef DGtal::DigitalSetBySTLSet<Domain1> DigitalSet1;

        typedef DGtal::SpaceND<4, int> Space4;
        typedef DGtal::HyperRectDomain<Space4> Domain4;
        typedef DGtal::DigitalSetBySTLSet<Domain4> DigitalSet4;

        typedef DGtal::SpaceND<5, int> Space5;
        typedef DGtal::HyperRectDomain<Space5> Domain5;
        typedef DGtal::DigitalSetBySTLSet<Domain5> DigitalSet5;

        typedef DGtal::SpaceND<6, int> Space6;
        typedef DGtal::HyperRectDomain<Space6> Domain6;
        typedef DGtal::DigitalSetBySTLSet<Domain6> DigitalSet6;

        typedef DGtal::SpaceND<7, int> Space7;
        typedef DGtal::HyperRectDomain<Space7> Domain7;
        typedef DGtal::DigitalSetBySTLSet<Domain7> DigitalSet7;

        DGtal::trace.beginBlock("testing hodges");
        if (maxdim>=1) test_hodge<DigitalSet1, LinearAlgebraBackend>(10);
        if (maxdim>=2) test_hodge<DGtal::Z2i::DigitalSet, LinearAlgebraBackend>(5);
        if (maxdim>=3) test_hodge<DGtal::Z3i::DigitalSet, LinearAlgebraBackend>(5);
        if (maxdim>=4) test_hodge<DigitalSet4, LinearAlgebraBackend>(4);
        if (maxdim>=5) test_hodge<DigitalSet5, LinearAlgebraBackend>(3);
        if (maxdim>=6) test_hodge<DigitalSet6, LinearAlgebraBackend>(3);
        if (maxdim>=7) test_hodge<DigitalSet7, LinearAlgebraBackend>(2);
        DGtal::trace.endBlock();

        DGtal::trace.beginBlock("testing derivatives");
        if (maxdim>=1) test_derivative<DigitalSet1, LinearAlgebraBackend>(10);
        if (maxdim>=2) test_derivative<DGtal::Z2i::DigitalSet, LinearAlgebraBackend>(5);
        if (maxdim>=3) test_derivative<DGtal::Z3i::DigitalSet, LinearAlgebraBackend>(5);
        if (maxdim>=4) test_derivative<DigitalSet4, LinearAlgebraBackend>(4);
        if (maxdim>=5) test_derivative<DigitalSet5, LinearAlgebraBackend>(3);
        if (maxdim>=6) test_derivative<DigitalSet6, LinearAlgebraBackend>(3);
        if (maxdim>=7) test_derivative<DigitalSet7, LinearAlgebraBackend>(2);
        DGtal::trace.endBlock();
    }

    test_concepts<LinearAlgebraBackend>();
}

#endif

