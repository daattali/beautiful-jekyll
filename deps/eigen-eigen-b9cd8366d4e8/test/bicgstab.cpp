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

template<typename T> void test_bicgstab_T()
{
  BiCGSTAB<SparseMatrix<T>, DiagonalPreconditioner<T> > bicgstab_colmajor_diag;
  BiCGSTAB<SparseMatrix<T>, IdentityPreconditioner    > bicgstab_colmajor_I;
  BiCGSTAB<SparseMatrix<T>, IncompleteLUT<T> >           bicgstab_colmajor_ilut;
  //BiCGSTAB<SparseMatrix<T>, SSORPreconditioner<T> >     bicgstab_colmajor_ssor;

  CALL_SUBTEST( check_sparse_square_solving(bicgstab_colmajor_diag)  );
//   CALL_SUBTEST( check_sparse_square_solving(bicgstab_colmajor_I)     );
  CALL_SUBTEST( check_sparse_square_solving(bicgstab_colmajor_ilut)     );
  //CALL_SUBTEST( check_sparse_square_solving(bicgstab_colmajor_ssor)     );
}

void test_bicgstab()
{
  CALL_SUBTEST_1(test_bicgstab_T<double>());
  CALL_SUBTEST_2(test_bicgstab_T<std::complex<double> >());
}
