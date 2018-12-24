#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>

class MatrixReplacement;
template<typename Rhs> class MatrixReplacement_ProductReturnType;

namespace Eigen {
namespace internal {
  template<>
  struct traits<MatrixReplacement> :  Eigen::internal::traits<Eigen::SparseMatrix<double> >
  {};

  template <typename Rhs>
  struct traits<MatrixReplacement_ProductReturnType<Rhs> > {
    // The equivalent plain objet type of the product. This type is used if the product needs to be evaluated into a temporary.
    typedef Eigen::Matrix<typename Rhs::Scalar, Eigen::Dynamic, Rhs::ColsAtCompileTime> ReturnType;
  };
}
}

// Inheriting EigenBase should not be needed in the future.
class MatrixReplacement : public Eigen::EigenBase<MatrixReplacement> {
public:
  // Expose some compile-time information to Eigen:
  typedef double Scalar;
  typedef double RealScalar;
  enum {
    ColsAtCompileTime = Eigen::Dynamic,
    RowsAtCompileTime = Eigen::Dynamic,
    MaxColsAtCompileTime = Eigen::Dynamic,
    MaxRowsAtCompileTime = Eigen::Dynamic
  };

  Index rows() const { return 4; }
  Index cols() const { return 4; }

  void resize(Index a_rows, Index a_cols)
  {
    // This method should not be needed in the future.
    assert(a_rows==0 && a_cols==0 || a_rows==rows() && a_cols==cols());
  }

  // In the future, the return type should be Eigen::Product<MatrixReplacement,Rhs>
  template<typename Rhs>
  MatrixReplacement_ProductReturnType<Rhs> operator*(const Eigen::MatrixBase<Rhs>& x) const {
    return MatrixReplacement_ProductReturnType<Rhs>(*this, x.derived());
  }

};

// The proxy class representing the product of a MatrixReplacement with a MatrixBase<>
template<typename Rhs>
class MatrixReplacement_ProductReturnType : public Eigen::ReturnByValue<MatrixReplacement_ProductReturnType<Rhs> > {
public:
  typedef MatrixReplacement::Index Index;
  
  // The ctor store references to the matrix and right-hand-side object (usually a vector).
  MatrixReplacement_ProductReturnType(const MatrixReplacement& matrix, const Rhs& rhs)
    : m_matrix(matrix), m_rhs(rhs)
  {}
  
  Index rows() const { return m_matrix.rows(); }
  Index cols() const { return m_rhs.cols(); }

  // This function is automatically called by Eigen. It must evaluate the product of matrix * rhs into y.
  template<typename Dest>
  void evalTo(Dest& y) const
  {
    y.setZero(4);

    y(0) += 2 * m_rhs(0); y(1) += 1 * m_rhs(0);
    y(0) += 1 * m_rhs(1); y(1) += 2 * m_rhs(1); y(2) += 1 * m_rhs(1);
    y(1) += 1 * m_rhs(2); y(2) += 2 * m_rhs(2); y(3) += 1 * m_rhs(2);
    y(2) += 1 * m_rhs(3); y(3) += 2 * m_rhs(3);
  }

protected:
  const MatrixReplacement& m_matrix;
  typename Rhs::Nested m_rhs;
};


/*****/

// This class simply warp a diagonal matrix as a Jacobi preconditioner.
// In the future such simple and generic wrapper should be shipped within Eigen itsel.
template <typename _Scalar>
class MyJacobiPreconditioner
{
    typedef _Scalar Scalar;
    typedef Eigen::Matrix<Scalar,Eigen::Dynamic,1> Vector;
    typedef typename Vector::Index Index;

  public:
    // this typedef is only to export the scalar type and compile-time dimensions to solve_retval
    typedef Eigen::Matrix<Scalar,Eigen::Dynamic,Eigen::Dynamic> MatrixType;

    MyJacobiPreconditioner() : m_isInitialized(false) {}

    void setInvDiag(const Eigen::VectorXd &invdiag) {
      m_invdiag=invdiag;
      m_isInitialized=true;
    }

    Index rows() const { return m_invdiag.size(); }
    Index cols() const { return m_invdiag.size(); }
    
    template<typename MatType>
    MyJacobiPreconditioner& analyzePattern(const MatType& ) { return *this; }
    
    template<typename MatType>
    MyJacobiPreconditioner& factorize(const MatType& mat) { return *this; }
    
    template<typename MatType>
    MyJacobiPreconditioner& compute(const MatType& mat) { return *this; }

    template<typename Rhs, typename Dest>
    void _solve(const Rhs& b, Dest& x) const
    {
      x = m_invdiag.array() * b.array() ;
    }

    template<typename Rhs> inline const Eigen::internal::solve_retval<MyJacobiPreconditioner, Rhs>
    solve(const Eigen::MatrixBase<Rhs>& b) const
    {
      eigen_assert(m_isInitialized && "MyJacobiPreconditioner is not initialized.");
      eigen_assert(m_invdiag.size()==b.rows()
                && "MyJacobiPreconditioner::solve(): invalid number of rows of the right hand side matrix b");
      return Eigen::internal::solve_retval<MyJacobiPreconditioner, Rhs>(*this, b.derived());
    }

  protected:
    Vector m_invdiag;
    bool m_isInitialized;
};

namespace Eigen {
namespace internal {

template<typename _MatrixType, typename Rhs>
struct solve_retval<MyJacobiPreconditioner<_MatrixType>, Rhs>
  : solve_retval_base<MyJacobiPreconditioner<_MatrixType>, Rhs>
{
  typedef MyJacobiPreconditioner<_MatrixType> Dec;
  EIGEN_MAKE_SOLVE_HELPERS(Dec,Rhs)

  template<typename Dest> void evalTo(Dest& dst) const
  {
    dec()._solve(rhs(),dst);
  }
};

}
}


/*****/


int main()
{
  MatrixReplacement A;
  Eigen::VectorXd b(4), x;
  b << 1, 1, 1, 1;

  // solve Ax = b using CG with matrix-free version:
  Eigen::ConjugateGradient < MatrixReplacement, Eigen::Lower|Eigen::Upper, MyJacobiPreconditioner<double> > cg;

  Eigen::VectorXd invdiag(4);
  invdiag << 1./3., 1./4., 1./4., 1./3.;

  cg.preconditioner().setInvDiag(invdiag);
  cg.compute(A);
  x = cg.solve(b);

  std::cout << "#iterations: " << cg.iterations() << std::endl;
  std::cout << "estimated error: " << cg.error() << std::endl;
}
