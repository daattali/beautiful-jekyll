// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2011 Gael Guennebaud <g.gael@free.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "sparse_solver.h"
#include <Eigen/IterativeLinearSolvers>

template<typename T> void test_conjugate_gradient_T()
{
  ConjugateGradient<SparseMatrix<T>, Lower      > cg_colmajor_lower_diag;
  ConjugateGradient<SparseMatrix<T>, Upper      > cg_colmajor_upper_diag;
  ConjugateGradient<SparseMatrix<T>, Lower|Upper> cg_colmajor_loup_diag;
  ConjugateGradient<SparseMatrix<T>, Lower, IdentityPreconditioner> cg_colmajor_lower_I;
  ConjugateGradient<SparseMatrix<T>, Upper, IdentityPreconditioner> cg_colmajor_upper_I;

  CALL_SUBTEST( check_sparse_spd_solving(cg_colmajor_lower_diag)  );
  CALL_SUBTEST( check_sparse_spd_solving(cg_colmajor_upper_diag)  );
  CALL_SUBTEST( check_sparse_spd_solving(cg_colmajor_loup_diag)   );
  CALL_SUBTEST( check_sparse_spd_solving(cg_colmajor_lower_I)     );
  CALL_SUBTEST( check_sparse_spd_solving(cg_colmajor_upper_I)     );
}

void test_conjugate_gradient()
{
  CALL_SUBTEST_1(test_conjugate_gradient_T<double>());
  CALL_SUBTEST_2(test_conjugate_gradient_T<std::complex<double> >());
}
