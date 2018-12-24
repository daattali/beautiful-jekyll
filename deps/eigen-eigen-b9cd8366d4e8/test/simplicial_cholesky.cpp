// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2011 Gael Guennebaud <g.gael@free.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "sparse_solver.h"

template<typename T> void test_simplicial_cholesky_T()
{
  SimplicialCholesky<SparseMatrix<T>, Lower> chol_colmajor_lower_amd;
  SimplicialCholesky<SparseMatrix<T>, Upper> chol_colmajor_upper_amd;
  SimplicialLLT<SparseMatrix<T>, Lower> llt_colmajor_lower_amd;
  SimplicialLLT<SparseMatrix<T>, Upper> llt_colmajor_upper_amd;
  SimplicialLDLT<SparseMatrix<T>, Lower> ldlt_colmajor_lower_amd;
  SimplicialLDLT<SparseMatrix<T>, Upper> ldlt_colmajor_upper_amd;
  SimplicialLDLT<SparseMatrix<T>, Lower, NaturalOrdering<int> > ldlt_colmajor_lower_nat;
  SimplicialLDLT<SparseMatrix<T>, Upper, NaturalOrdering<int> > ldlt_colmajor_upper_nat;

  check_sparse_spd_solving(chol_colmajor_lower_amd);
  check_sparse_spd_solving(chol_colmajor_upper_amd);
  check_sparse_spd_solving(llt_colmajor_lower_amd);
  check_sparse_spd_solving(llt_colmajor_upper_amd);
  check_sparse_spd_solving(ldlt_colmajor_lower_amd);
  check_sparse_spd_solving(ldlt_colmajor_upper_amd);
  
  check_sparse_spd_determinant(chol_colmajor_lower_amd);
  check_sparse_spd_determinant(chol_colmajor_upper_amd);
  check_sparse_spd_determinant(llt_colmajor_lower_amd);
  check_sparse_spd_determinant(llt_colmajor_upper_amd);
  check_sparse_spd_determinant(ldlt_colmajor_lower_amd);
  check_sparse_spd_determinant(ldlt_colmajor_upper_amd);
  
  check_sparse_spd_solving(ldlt_colmajor_lower_nat);
  check_sparse_spd_solving(ldlt_colmajor_upper_nat);
}

void test_simplicial_cholesky()
{
  CALL_SUBTEST_1(test_simplicial_cholesky_T<double>());
  CALL_SUBTEST_2(test_simplicial_cholesky_T<std::complex<double> >());
}
