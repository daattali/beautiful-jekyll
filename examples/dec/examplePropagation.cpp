/// @file dec/examplePropagation.cpp
/**
   Example of 2D wave propagation using the DEC package.
    @see \ref moduleDECPropagation
   \image html  propagation_time_wave_ii.gif  "You should obtain such wave propagation (by converting svg files)."
   \example dec/examplePropagation.cpp
**/

#include <iomanip>
#include "DECExamplesCommon.h"
#include "DGtal/math/linalg/EigenSupport.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/dec/DiscreteExteriorCalculusSolver.h"
#include "DGtal/dec/DiscreteExteriorCalculusFactory.h"
#include "DGtal/io/boards/Board2D.h"

template <typename Calculus>
typename Calculus::Scalar
sample_dual_0_form(const typename Calculus::Properties& properties, const typename Calculus::DualForm0& form, const typename Calculus::Point& point)
{
    const typename Calculus::Cell cell = form.myCalculus->myKSpace.uSpel(point);
    const typename Calculus::Properties::const_iterator iter = properties.find(cell);
    if (iter == properties.end()) return 0;

    const typename Calculus::Index index = iter->second.index;
    return form.myContainer(index);
}

template <typename Calculus>
void
set_initial_phase_dir_yy(Calculus& calculus, Eigen::VectorXcd& initial_wave)
{
    typedef typename Calculus::Cell Cell;
    typedef typename Calculus::Index Index;
    typedef typename Calculus::Point Point;

    //! [time_phase_yy]
    for (int xx=9; xx<13; xx++)
    for (int yy=13; yy<17; yy++)
    {
        const Point point(xx,yy);
        const Cell cell = calculus.myKSpace.uSpel(point);
        const Index index = calculus.getCellIndex(cell);
        initial_wave(index) = std::exp(std::complex<double>(0,2*M_PI*(yy-14.5)/8));
    }
    //! [time_phase_yy]
}

template <typename Calculus>
void
set_initial_phase_null(Calculus& calculus, Eigen::VectorXcd& initial_wave)
{
    typedef typename Calculus::Cell Cell;
    typedef typename Calculus::Index Index;
    typedef typename Calculus::Point Point;

    //! [time_phase_null]
    for (int xx=9; xx<13; xx++)
    for (int yy=13; yy<17; yy++)
    {
        const Point point(xx,yy);
        const Cell cell = calculus.myKSpace.uSpel(point);
        const Index index = calculus.getCellIndex(cell);
        initial_wave(index) = 1;
    }
    //! [time_phase_null]
}

using namespace DGtal;
using std::endl;

void propa_2d()
{
    trace.beginBlock("2d propagation");

    typedef DiscreteExteriorCalculus<2, 2, EigenLinearAlgebraBackend> Calculus;
		typedef DiscreteExteriorCalculusFactory<EigenLinearAlgebraBackend> CalculusFactory;

    {
        trace.beginBlock("solving time dependent equation");

        const Calculus::Scalar cc = 8; // px/s
        trace.info() << "cc = " << cc << endl;

        const Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(29,29));
        const Calculus calculus = CalculusFactory::createFromDigitalSet(generateDiskSet(domain), false);

        //! [time_laplace]
        const Calculus::DualIdentity0 laplace = calculus.laplace<DUAL>() + 1e-8 * calculus.identity<0, DUAL>();
        //! [time_laplace]
        trace.info() << "laplace = " << laplace << endl;

        trace.beginBlock("finding eigen pairs");
        //! [time_eigen]
        typedef Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> EigenSolverMatrix;
        const EigenSolverMatrix eigen_solver(laplace.myContainer);

        const Eigen::VectorXd eigen_values = eigen_solver.eigenvalues();
        const Eigen::MatrixXd eigen_vectors = eigen_solver.eigenvectors();
        //! [time_eigen]
        trace.info() << "eigen_values_range = " << eigen_values.minCoeff() << "/" << eigen_values.maxCoeff() << endl;
        trace.endBlock();

        //! [time_omega]
        const Eigen::VectorXd angular_frequencies = cc * eigen_values.array().sqrt();
        //! [time_omega]

        Eigen::VectorXcd initial_wave = Eigen::VectorXcd::Zero(calculus.kFormLength(0, DUAL));
        //set_initial_phase_null(calculus, initial_wave);
        set_initial_phase_dir_yy(calculus, initial_wave);

        {
            Board2D board;
            board << domain;
            board << CustomStyle("KForm", new KFormStyle2D(-1, 1));
            board << Calculus::DualForm0(calculus, initial_wave.real());
            board.saveSVG("propagation_time_wave_initial_coarse.svg");
        }

        //! [time_init_proj]
        Eigen::VectorXcd initial_projections = eigen_vectors.transpose() * initial_wave;
        //! [time_init_proj]

        // low pass
        //! [time_low_pass]
        const Calculus::Scalar lambda_cutoff = 4.5;
        const Calculus::Scalar angular_frequency_cutoff = 2*M_PI * cc / lambda_cutoff;
        int cutted = 0;
        for (int kk=0; kk<initial_projections.rows(); kk++)
        {
            const Calculus::Scalar angular_frequency = angular_frequencies(kk);
            if (angular_frequency < angular_frequency_cutoff) continue;
            initial_projections(kk) = 0;
            cutted ++;
        }
        //! [time_low_pass]
        trace.info() << "cutted = " << cutted << "/" << initial_projections.rows() << endl;

        {
            const Eigen::VectorXcd wave = eigen_vectors * initial_projections;
            Board2D board;
            board << domain;
            board << CustomStyle("KForm", new KFormStyle2D(-1, 1));
            board << Calculus::DualForm0(calculus, wave.real());
            board.saveSVG("propagation_time_wave_initial_smoothed.svg");
        }

        const int kk_max = 60;
        trace.progressBar(0,kk_max);
        for (int kk=0; kk<kk_max; kk++)
        {
            //! [time_solve_time]
            const Calculus::Scalar time = kk/20.;
            const Eigen::VectorXcd current_projections = (angular_frequencies * std::complex<double>(0,time)).array().exp() * initial_projections.array();
            const Eigen::VectorXcd current_wave = eigen_vectors * current_projections;
            //! [time_solve_time]

            std::stringstream ss;
            ss << "propagation_time_wave_solution_" << std::setfill('0') << std::setw(3) << kk << ".svg";

            Board2D board;
            board << domain;
            board << CustomStyle("KForm", new KFormStyle2D(-1, 1));
            board << Calculus::DualForm0(calculus, current_wave.real());
            board.saveSVG(ss.str().c_str());

            trace.progressBar(kk+1,kk_max);
        }
        trace.info() << endl;

        trace.endBlock();
    }

    {
        trace.beginBlock("forced oscillations");

        const Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(50,50));
        const Calculus calculus = CalculusFactory::createFromDigitalSet(generateDiskSet(domain), false);

        const Calculus::DualIdentity0 laplace = calculus.laplace<DUAL>();
        trace.info() << "laplace = " << laplace << endl;

        trace.beginBlock("finding eigen pairs");
        typedef Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> EigenSolverMatrix;
        const EigenSolverMatrix eigen_solver(laplace.myContainer);

        const Eigen::VectorXd laplace_eigen_values = eigen_solver.eigenvalues();
        const Eigen::MatrixXd laplace_eigen_vectors = eigen_solver.eigenvectors();
        trace.info() << "eigen_values_range = " << laplace_eigen_values.minCoeff() << "/" << laplace_eigen_values.maxCoeff() << endl;
        trace.endBlock();

        Calculus::DualForm0 concentration(calculus);
        {
            const Z2i::Point point(25,25);
            const Calculus::Cell cell = calculus.myKSpace.uSpel(point);
            const Calculus::Index index = calculus.getCellIndex(cell);
            concentration.myContainer(index) = 1;
        }

        {
            Board2D board;
            board << domain;
            board << concentration;
            board.saveSVG("propagation_forced_concentration.svg");
        }

        for (int ll=0; ll<6; ll++)
        {
            //! [forced_lambda]
            const Calculus::Scalar lambda = 4*20.75/(1+2*ll);
            //! [forced_lambda]
            trace.info() << "lambda = " << lambda << endl;

            //! [forced_dalembert_eigen]
            const Eigen::VectorXd dalembert_eigen_values = (laplace_eigen_values.array() - (2*M_PI/lambda)*(2*M_PI/lambda)).array().inverse();
            const Eigen::MatrixXd concentration_to_wave = laplace_eigen_vectors * dalembert_eigen_values.asDiagonal() * laplace_eigen_vectors.transpose();
            //! [forced_dalembert_eigen]

            //! [forced_wave]
            Calculus::DualForm0 wave(calculus, concentration_to_wave * concentration.myContainer);
            //! [forced_wave]
            wave.myContainer /= wave.myContainer(calculus.getCellIndex(calculus.myKSpace.uSpel(Z2i::Point(25,25))));

            {
                trace.info() << "saving samples" << endl;
                const Calculus::Properties properties = calculus.getProperties();
                {
                    std::stringstream ss;
                    ss << "propagation_forced_samples_hv_" << ll << ".dat";
                    std::ofstream handle(ss.str().c_str());
                    for (int kk=0; kk<=50; kk++)
                    {
                        const Z2i::Point point_horizontal(kk,25);
                        const Z2i::Point point_vertical(25,kk);
                        const Calculus::Scalar xx = 2 * (kk/50. - .5);
                        handle << xx << " ";
                        handle << sample_dual_0_form<Calculus>(properties, wave, point_horizontal) << " ";
                        handle << sample_dual_0_form<Calculus>(properties, wave, point_vertical) << endl;
                    }
                }

                {
                    std::stringstream ss;
                    ss << "propagation_forced_samples_diag_" << ll << ".dat";
                    std::ofstream handle(ss.str().c_str());
                    for (int kk=0; kk<=50; kk++)
                    {
                        const Z2i::Point point_diag_pos(kk,kk);
                        const Z2i::Point point_diag_neg(kk,50-kk);
                        const Calculus::Scalar xx = 2 * sqrt(2) * (kk/50. - .5);
                        handle << xx << " ";
                        handle << sample_dual_0_form<Calculus>(properties, wave, point_diag_pos) << " ";
                        handle << sample_dual_0_form<Calculus>(properties, wave, point_diag_neg) << endl;
                    }
                }
            }

            {
                std::stringstream ss;
                ss << "propagation_forced_wave_" << ll << ".svg";
                Board2D board;
                board << domain;
                board << CustomStyle("KForm", new KFormStyle2D(-.5, 1));
                board << wave;
                board.saveSVG(ss.str().c_str());
            }
        }

        trace.endBlock();
    }
    trace.endBlock();
}

int main()
{
    propa_2d();
    return 0;
}
