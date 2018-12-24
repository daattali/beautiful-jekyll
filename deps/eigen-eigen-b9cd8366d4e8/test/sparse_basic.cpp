// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008-2011 Gael Guennebaud <gael.guennebaud@inria.fr>
// Copyright (C) 2008 Daniel Gomez Ferro <dgomezferro@gmail.com>
// Copyright (C) 2013 Désiré Nuentsa-Wakam <desire.nuentsa_wakam@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "sparse.h"

template<typename SparseMatrixType> void sparse_basic(const SparseMatrixType& ref)
{
  typedef typename SparseMatrixType::Index Index;
  typedef Matrix<Index,2,1> Vector2;
  
  const Index rows = ref.rows();
  const Index cols = ref.cols();
  typedef typename SparseMatrixType::Scalar Scalar;
  enum { Flags = SparseMatrixType::Flags };

  double density = (std::max)(8./(rows*cols), 0.01);
  typedef Matrix<Scalar,Dynamic,Dynamic> DenseMatrix;
  typedef Matrix<Scalar,Dynamic,1> DenseVector;
  typedef Matrix<Scalar,1,Dynamic> RowDenseVector;
  Scalar eps = 1e-6;

  Scalar s1 = internal::random<Scalar>();
  {
    SparseMatrixType m(rows, cols);
    DenseMatrix refMat = DenseMatrix::Zero(rows, cols);
    DenseVector vec1 = DenseVector::Random(rows);

    std::vector<Vector2> zeroCoords;
    std::vector<Vector2> nonzeroCoords;
    initSparse<Scalar>(density, refMat, m, 0, &zeroCoords, &nonzeroCoords);

    if (zeroCoords.size()==0 || nonzeroCoords.size()==0)
      return;

    // test coeff and coeffRef
    for (int i=0; i<(int)zeroCoords.size(); ++i)
    {
      VERIFY_IS_MUCH_SMALLER_THAN( m.coeff(zeroCoords[i].x(),zeroCoords[i].y()), eps );
      if(internal::is_same<SparseMatrixType,SparseMatrix<Scalar,Flags> >::value)
        VERIFY_RAISES_ASSERT( m.coeffRef(zeroCoords[0].x(),zeroCoords[0].y()) = 5 );
    }
    VERIFY_IS_APPROX(m, refMat);

    m.coeffRef(nonzeroCoords[0].x(), nonzeroCoords[0].y()) = Scalar(5);
    refMat.coeffRef(nonzeroCoords[0].x(), nonzeroCoords[0].y()) = Scalar(5);

    VERIFY_IS_APPROX(m, refMat);
      
      // test InnerIterators and Block expressions
      for (int t=0; t<10; ++t)
      {
        int j = internal::random<int>(0,cols-1);
        int i = internal::random<int>(0,rows-1);
        int w = internal::random<int>(1,cols-j-1);
        int h = internal::random<int>(1,rows-i-1);

        VERIFY_IS_APPROX(m.block(i,j,h,w), refMat.block(i,j,h,w));
        for(int c=0; c<w; c++)
        {
          VERIFY_IS_APPROX(m.block(i,j,h,w).col(c), refMat.block(i,j,h,w).col(c));
          for(int r=0; r<h; r++)
          {
            VERIFY_IS_APPROX(m.block(i,j,h,w).col(c).coeff(r), refMat.block(i,j,h,w).col(c).coeff(r));
            VERIFY_IS_APPROX(m.block(i,j,h,w).coeff(r,c), refMat.block(i,j,h,w).coeff(r,c));
          }
        }
        for(int r=0; r<h; r++)
        {
          VERIFY_IS_APPROX(m.block(i,j,h,w).row(r), refMat.block(i,j,h,w).row(r));
          for(int c=0; c<w; c++)
          {
            VERIFY_IS_APPROX(m.block(i,j,h,w).row(r).coeff(c), refMat.block(i,j,h,w).row(r).coeff(c));
            VERIFY_IS_APPROX(m.block(i,j,h,w).coeff(r,c), refMat.block(i,j,h,w).coeff(r,c));
          }
        }
        
        VERIFY_IS_APPROX(m.middleCols(j,w), refMat.middleCols(j,w));
        VERIFY_IS_APPROX(m.middleRows(i,h), refMat.middleRows(i,h));
        for(int r=0; r<h; r++)
        {
          VERIFY_IS_APPROX(m.middleCols(j,w).row(r), refMat.middleCols(j,w).row(r));
          VERIFY_IS_APPROX(m.middleRows(i,h).row(r), refMat.middleRows(i,h).row(r));
          for(int c=0; c<w; c++)
          {
            VERIFY_IS_APPROX(m.col(c).coeff(r), refMat.col(c).coeff(r));
            VERIFY_IS_APPROX(m.row(r).coeff(c), refMat.row(r).coeff(c));
            
            VERIFY_IS_APPROX(m.middleCols(j,w).coeff(r,c), refMat.middleCols(j,w).coeff(r,c));
            VERIFY_IS_APPROX(m.middleRows(i,h).coeff(r,c), refMat.middleRows(i,h).coeff(r,c));
            if(m.middleCols(j,w).coeff(r,c) != Scalar(0))
            {
              VERIFY_IS_APPROX(m.middleCols(j,w).coeffRef(r,c), refMat.middleCols(j,w).coeff(r,c));
            }
            if(m.middleRows(i,h).coeff(r,c) != Scalar(0))
            {
              VERIFY_IS_APPROX(m.middleRows(i,h).coeff(r,c), refMat.middleRows(i,h).coeff(r,c));
            }
          }
        }
        for(int c=0; c<w; c++)
        {
          VERIFY_IS_APPROX(m.middleCols(j,w).col(c), refMat.middleCols(j,w).col(c));
          VERIFY_IS_APPROX(m.middleRows(i,h).col(c), refMat.middleRows(i,h).col(c));
        }
      }

      for(int c=0; c<cols; c++)
      {
        VERIFY_IS_APPROX(m.col(c) + m.col(c), (m + m).col(c));
        VERIFY_IS_APPROX(m.col(c) + m.col(c), refMat.col(c) + refMat.col(c));
      }

      for(int r=0; r<rows; r++)
      {
        VERIFY_IS_APPROX(m.row(r) + m.row(r), (m + m).row(r));
        VERIFY_IS_APPROX(m.row(r) + m.row(r), refMat.row(r) + refMat.row(r));
      }
      
      
      // test assertion
      VERIFY_RAISES_ASSERT( m.coeffRef(-1,1) = 0 );
      VERIFY_RAISES_ASSERT( m.coeffRef(0,m.cols()) = 0 );
    }

    // test insert (inner random)
    {
      DenseMatrix m1(rows,cols);
      m1.setZero();
      SparseMatrixType m2(rows,cols);
      if(internal::random<int>()%2)
        m2.reserve(VectorXi::Constant(m2.outerSize(), 2));
      for (Index j=0; j<cols; ++j)
      {
        for (Index k=0; k<rows/2; ++k)
        {
          Index i = internal::random<Index>(0,rows-1);
          if (m1.coeff(i,j)==Scalar(0))
            m2.insert(i,j) = m1(i,j) = internal::random<Scalar>();
        }
      }
      m2.finalize();
      VERIFY_IS_APPROX(m2,m1);
    }

    // test insert (fully random)
    {
      DenseMatrix m1(rows,cols);
      m1.setZero();
      SparseMatrixType m2(rows,cols);
      if(internal::random<int>()%2)
        m2.reserve(VectorXi::Constant(m2.outerSize(), 2));
      for (int k=0; k<rows*cols; ++k)
      {
        Index i = internal::random<Index>(0,rows-1);
        Index j = internal::random<Index>(0,cols-1);
        if ((m1.coeff(i,j)==Scalar(0)) && (internal::random<int>()%2))
          m2.insert(i,j) = m1(i,j) = internal::random<Scalar>();
        else
        {
          Scalar v = internal::random<Scalar>();
          m2.coeffRef(i,j) += v;
          m1(i,j) += v;
        }
      }
      VERIFY_IS_APPROX(m2,m1);
    }
    
    // test insert (un-compressed)
    for(int mode=0;mode<4;++mode)
    {
      DenseMatrix m1(rows,cols);
      m1.setZero();
      SparseMatrixType m2(rows,cols);
      VectorXi r(VectorXi::Constant(m2.outerSize(), ((mode%2)==0) ? m2.innerSize() : std::max<int>(1,m2.innerSize()/8)));
      m2.reserve(r);
      for (int k=0; k<rows*cols; ++k)
      {
        Index i = internal::random<Index>(0,rows-1);
        Index j = internal::random<Index>(0,cols-1);
        if (m1.coeff(i,j)==Scalar(0))
          m2.insert(i,j) = m1(i,j) = internal::random<Scalar>();
        if(mode==3)
          m2.reserve(r);
      }
      if(internal::random<int>()%2)
        m2.makeCompressed();
      VERIFY_IS_APPROX(m2,m1);
    }

  // test innerVector()
  {
    DenseMatrix refMat2 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m2(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    Index j0 = internal::random<Index>(0,rows-1);
    Index j1 = internal::random<Index>(0,rows-1);
    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m2.innerVector(j0), refMat2.row(j0));
    else
      VERIFY_IS_APPROX(m2.innerVector(j0), refMat2.col(j0));

    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m2.innerVector(j0)+m2.innerVector(j1), refMat2.row(j0)+refMat2.row(j1));
    else
      VERIFY_IS_APPROX(m2.innerVector(j0)+m2.innerVector(j1), refMat2.col(j0)+refMat2.col(j1));

    SparseMatrixType m3(rows,rows);
    m3.reserve(VectorXi::Constant(rows,rows/2));
    for(Index j=0; j<rows; ++j)
      for(Index k=0; k<j; ++k)
        m3.insertByOuterInner(j,k) = k+1;
    for(Index j=0; j<rows; ++j)
    {
      VERIFY(j==numext::real(m3.innerVector(j).nonZeros()));
      if(j>0)
        VERIFY(j==numext::real(m3.innerVector(j).lastCoeff()));
    }
    m3.makeCompressed();
    for(Index j=0; j<rows; ++j)
    {
      VERIFY(j==numext::real(m3.innerVector(j).nonZeros()));
      if(j>0)
        VERIFY(j==numext::real(m3.innerVector(j).lastCoeff()));
    }

    //m2.innerVector(j0) = 2*m2.innerVector(j1);
    //refMat2.col(j0) = 2*refMat2.col(j1);
    //VERIFY_IS_APPROX(m2, refMat2);
  }

  // test innerVectors()
  {
    DenseMatrix refMat2 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m2(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    if(internal::random<float>(0,1)>0.5) m2.makeCompressed();
    
    Index j0 = internal::random<Index>(0,rows-2);
    Index j1 = internal::random<Index>(0,rows-2);
    Index n0 = internal::random<Index>(1,rows-(std::max)(j0,j1));
    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m2.innerVectors(j0,n0), refMat2.block(j0,0,n0,cols));
    else
      VERIFY_IS_APPROX(m2.innerVectors(j0,n0), refMat2.block(0,j0,rows,n0));
    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m2.innerVectors(j0,n0)+m2.innerVectors(j1,n0),
                       refMat2.middleRows(j0,n0)+refMat2.middleRows(j1,n0));
    else
      VERIFY_IS_APPROX(m2.innerVectors(j0,n0)+m2.innerVectors(j1,n0),
                      refMat2.block(0,j0,rows,n0)+refMat2.block(0,j1,rows,n0));
    
    VERIFY_IS_APPROX(m2, refMat2);
    
    m2.innerVectors(j0,n0) = m2.innerVectors(j0,n0) + m2.innerVectors(j1,n0);
    if(SparseMatrixType::IsRowMajor)
      refMat2.middleRows(j0,n0) = (refMat2.middleRows(j0,n0) + refMat2.middleRows(j1,n0)).eval();
    else
      refMat2.middleCols(j0,n0) = (refMat2.middleCols(j0,n0) + refMat2.middleCols(j1,n0)).eval();
    
    VERIFY_IS_APPROX(m2, refMat2);
    
  }
  
  // test basic computations
  {
    DenseMatrix refM1 = DenseMatrix::Zero(rows, rows);
    DenseMatrix refM2 = DenseMatrix::Zero(rows, rows);
    DenseMatrix refM3 = DenseMatrix::Zero(rows, rows);
    DenseMatrix refM4 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m1(rows, rows);
    SparseMatrixType m2(rows, rows);
    SparseMatrixType m3(rows, rows);
    SparseMatrixType m4(rows, rows);
    initSparse<Scalar>(density, refM1, m1);
    initSparse<Scalar>(density, refM2, m2);
    initSparse<Scalar>(density, refM3, m3);
    initSparse<Scalar>(density, refM4, m4);

    VERIFY_IS_APPROX(m1+m2, refM1+refM2);
    VERIFY_IS_APPROX(m1+m2+m3, refM1+refM2+refM3);
    VERIFY_IS_APPROX(m3.cwiseProduct(m1+m2), refM3.cwiseProduct(refM1+refM2));
    VERIFY_IS_APPROX(m1*s1-m2, refM1*s1-refM2);

    VERIFY_IS_APPROX(m1*=s1, refM1*=s1);
    VERIFY_IS_APPROX(m1/=s1, refM1/=s1);

    VERIFY_IS_APPROX(m1+=m2, refM1+=refM2);
    VERIFY_IS_APPROX(m1-=m2, refM1-=refM2);

    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m1.innerVector(0).dot(refM2.row(0)), refM1.row(0).dot(refM2.row(0)));
    else
      VERIFY_IS_APPROX(m1.innerVector(0).dot(refM2.row(0)), refM1.col(0).dot(refM2.row(0)));
    
    DenseVector rv = DenseVector::Random(m1.cols());
    DenseVector cv = DenseVector::Random(m1.rows());
    Index r = internal::random<Index>(0,m1.rows()-2);
    Index c = internal::random<Index>(0,m1.cols()-1);
    VERIFY_IS_APPROX(( m1.template block<1,Dynamic>(r,0,1,m1.cols()).dot(rv)) , refM1.row(r).dot(rv));
    VERIFY_IS_APPROX(m1.row(r).dot(rv), refM1.row(r).dot(rv));
    VERIFY_IS_APPROX(m1.col(c).dot(cv), refM1.col(c).dot(cv));

    VERIFY_IS_APPROX(m1.conjugate(), refM1.conjugate());
    VERIFY_IS_APPROX(m1.real(), refM1.real());

    refM4.setRandom();
    // sparse cwise* dense
    VERIFY_IS_APPROX(m3.cwiseProduct(refM4), refM3.cwiseProduct(refM4));
    // dense cwise* sparse
    VERIFY_IS_APPROX(refM4.cwiseProduct(m3), refM4.cwiseProduct(refM3));
//     VERIFY_IS_APPROX(m3.cwise()/refM4, refM3.cwise()/refM4);

    // test aliasing
    VERIFY_IS_APPROX((m1 = -m1), (refM1 = -refM1));
    VERIFY_IS_APPROX((m1 = m1.transpose()), (refM1 = refM1.transpose().eval()));
    VERIFY_IS_APPROX((m1 = -m1.transpose()), (refM1 = -refM1.transpose().eval()));
    VERIFY_IS_APPROX((m1 += -m1), (refM1 += -refM1));
  }

  // test transpose
  {
    DenseMatrix refMat2 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m2(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    VERIFY_IS_APPROX(m2.transpose().eval(), refMat2.transpose().eval());
    VERIFY_IS_APPROX(m2.transpose(), refMat2.transpose());

    VERIFY_IS_APPROX(SparseMatrixType(m2.adjoint()), refMat2.adjoint());
  }

  
  
  // test generic blocks
  {
    DenseMatrix refMat2 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m2(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    Index j0 = internal::random<Index>(0,rows-2);
    Index j1 = internal::random<Index>(0,rows-2);
    Index n0 = internal::random<Index>(1,rows-(std::max)(j0,j1));
    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m2.block(j0,0,n0,cols), refMat2.block(j0,0,n0,cols));
    else
      VERIFY_IS_APPROX(m2.block(0,j0,rows,n0), refMat2.block(0,j0,rows,n0));
    
    if(SparseMatrixType::IsRowMajor)
      VERIFY_IS_APPROX(m2.block(j0,0,n0,cols)+m2.block(j1,0,n0,cols),
                      refMat2.block(j0,0,n0,cols)+refMat2.block(j1,0,n0,cols));
    else
      VERIFY_IS_APPROX(m2.block(0,j0,rows,n0)+m2.block(0,j1,rows,n0),
                      refMat2.block(0,j0,rows,n0)+refMat2.block(0,j1,rows,n0));
      
    Index i = internal::random<Index>(0,m2.outerSize()-1);
    if(SparseMatrixType::IsRowMajor) {
      m2.innerVector(i) = m2.innerVector(i) * s1;
      refMat2.row(i) = refMat2.row(i) * s1;
      VERIFY_IS_APPROX(m2,refMat2);
    } else {
      m2.innerVector(i) = m2.innerVector(i) * s1;
      refMat2.col(i) = refMat2.col(i) * s1;
      VERIFY_IS_APPROX(m2,refMat2);
    }
    
    VERIFY_IS_APPROX(DenseVector(m2.col(j0)), refMat2.col(j0));
    VERIFY_IS_APPROX(m2.col(j0), refMat2.col(j0));
    
    VERIFY_IS_APPROX(RowDenseVector(m2.row(j0)), refMat2.row(j0));
    VERIFY_IS_APPROX(m2.row(j0), refMat2.row(j0));
    
    VERIFY_IS_APPROX(m2.block(j0,j1,n0,n0), refMat2.block(j0,j1,n0,n0));
    VERIFY_IS_APPROX((2*m2).block(j0,j1,n0,n0), (2*refMat2).block(j0,j1,n0,n0));
  }

  // test prune
  {
    SparseMatrixType m2(rows, rows);
    DenseMatrix refM2(rows, rows);
    refM2.setZero();
    int countFalseNonZero = 0;
    int countTrueNonZero = 0;
    for (Index j=0; j<m2.outerSize(); ++j)
    {
      m2.startVec(j);
      for (Index i=0; i<m2.innerSize(); ++i)
      {
        float x = internal::random<float>(0,1);
        if (x<0.1)
        {
          // do nothing
        }
        else if (x<0.5)
        {
          countFalseNonZero++;
          m2.insertBackByOuterInner(j,i) = Scalar(0);
        }
        else
        {
          countTrueNonZero++;
          m2.insertBackByOuterInner(j,i) = Scalar(1);
          if(SparseMatrixType::IsRowMajor)
            refM2(j,i) = Scalar(1);
          else
            refM2(i,j) = Scalar(1);
        }
      }
    }
    m2.finalize();
    VERIFY(countFalseNonZero+countTrueNonZero == m2.nonZeros());
    VERIFY_IS_APPROX(m2, refM2);
    m2.prune(Scalar(1));
    VERIFY(countTrueNonZero==m2.nonZeros());
    VERIFY_IS_APPROX(m2, refM2);
  }

  // test setFromTriplets
  {
    typedef Triplet<Scalar,Index> TripletType;
    std::vector<TripletType> triplets;
    int ntriplets = rows*cols;
    triplets.reserve(ntriplets);
    DenseMatrix refMat(rows,cols);
    refMat.setZero();
    for(int i=0;i<ntriplets;++i)
    {
      Index r = internal::random<Index>(0,rows-1);
      Index c = internal::random<Index>(0,cols-1);
      Scalar v = internal::random<Scalar>();
      triplets.push_back(TripletType(r,c,v));
      refMat(r,c) += v;
    }
    SparseMatrixType m(rows,cols);
    m.setFromTriplets(triplets.begin(), triplets.end());
    VERIFY_IS_APPROX(m, refMat);
  }

  // test triangularView
  {
    DenseMatrix refMat2(rows, rows), refMat3(rows, rows);
    SparseMatrixType m2(rows, rows), m3(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    refMat3 = refMat2.template triangularView<Lower>();
    m3 = m2.template triangularView<Lower>();
    VERIFY_IS_APPROX(m3, refMat3);

    refMat3 = refMat2.template triangularView<Upper>();
    m3 = m2.template triangularView<Upper>();
    VERIFY_IS_APPROX(m3, refMat3);

    refMat3 = refMat2.template triangularView<UnitUpper>();
    m3 = m2.template triangularView<UnitUpper>();
    VERIFY_IS_APPROX(m3, refMat3);

    refMat3 = refMat2.template triangularView<UnitLower>();
    m3 = m2.template triangularView<UnitLower>();
    VERIFY_IS_APPROX(m3, refMat3);

    refMat3 = refMat2.template triangularView<StrictlyUpper>();
    m3 = m2.template triangularView<StrictlyUpper>();
    VERIFY_IS_APPROX(m3, refMat3);

    refMat3 = refMat2.template triangularView<StrictlyLower>();
    m3 = m2.template triangularView<StrictlyLower>();
    VERIFY_IS_APPROX(m3, refMat3);
  }
  
  // test selfadjointView
  if(!SparseMatrixType::IsRowMajor)
  {
    DenseMatrix refMat2(rows, rows), refMat3(rows, rows);
    SparseMatrixType m2(rows, rows), m3(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    refMat3 = refMat2.template selfadjointView<Lower>();
    m3 = m2.template selfadjointView<Lower>();
    VERIFY_IS_APPROX(m3, refMat3);
  }
  
  // test sparseView
  {
    DenseMatrix refMat2 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m2(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    VERIFY_IS_APPROX(m2.eval(), refMat2.sparseView().eval());
  }

  // test diagonal
  {
    DenseMatrix refMat2 = DenseMatrix::Zero(rows, rows);
    SparseMatrixType m2(rows, rows);
    initSparse<Scalar>(density, refMat2, m2);
    VERIFY_IS_APPROX(m2.diagonal(), refMat2.diagonal().eval());
  }
  
  // test conservative resize
  {
      std::vector< std::pair<Index,Index> > inc;
      inc.push_back(std::pair<Index,Index>(-3,-2));
      inc.push_back(std::pair<Index,Index>(0,0));
      inc.push_back(std::pair<Index,Index>(3,2));
      inc.push_back(std::pair<Index,Index>(3,0));
      inc.push_back(std::pair<Index,Index>(0,3));
      
      for(size_t i = 0; i< inc.size(); i++) {
        Index incRows = inc[i].first;
        Index incCols = inc[i].second;
        SparseMatrixType m1(rows, cols);
        DenseMatrix refMat1 = DenseMatrix::Zero(rows, cols);
        initSparse<Scalar>(density, refMat1, m1);
        
        m1.conservativeResize(rows+incRows, cols+incCols);
        refMat1.conservativeResize(rows+incRows, cols+incCols);
        if (incRows > 0) refMat1.bottomRows(incRows).setZero();
        if (incCols > 0) refMat1.rightCols(incCols).setZero();
        
        VERIFY_IS_APPROX(m1, refMat1);
        
        // Insert new values
        if (incRows > 0) 
          m1.insert(m1.rows()-1, 0) = refMat1(refMat1.rows()-1, 0) = 1;
        if (incCols > 0) 
          m1.insert(0, m1.cols()-1) = refMat1(0, refMat1.cols()-1) = 1;
          
        VERIFY_IS_APPROX(m1, refMat1);
          
          
      }
  }

  // test Identity matrix
  {
    DenseMatrix refMat1 = DenseMatrix::Identity(rows, rows);
    SparseMatrixType m1(rows, rows);
    m1.setIdentity();
    VERIFY_IS_APPROX(m1, refMat1);
    for(int k=0; k<rows*rows/4; ++k)
    {
      Index i = internal::random<Index>(0,rows-1);
      Index j = internal::random<Index>(0,rows-1);
      Scalar v = internal::random<Scalar>();
      m1.coeffRef(i,j) = v;
      refMat1.coeffRef(i,j) = v;
      VERIFY_IS_APPROX(m1, refMat1);
      if(internal::random<Index>(0,10)<2)
        m1.makeCompressed();
    }
    m1.setIdentity();
    refMat1.setIdentity();
    VERIFY_IS_APPROX(m1, refMat1);
  }
}

void test_sparse_basic()
{
  for(int i = 0; i < g_repeat; i++) {
    int s = Eigen::internal::random<int>(1,50);
    EIGEN_UNUSED_VARIABLE(s);
    CALL_SUBTEST_1(( sparse_basic(SparseMatrix<double>(8, 8)) ));
    CALL_SUBTEST_2(( sparse_basic(SparseMatrix<std::complex<double>, ColMajor>(s, s)) ));
    CALL_SUBTEST_2(( sparse_basic(SparseMatrix<std::complex<double>, RowMajor>(s, s)) ));
    CALL_SUBTEST_1(( sparse_basic(SparseMatrix<double>(s, s)) ));
    CALL_SUBTEST_1(( sparse_basic(SparseMatrix<double,ColMajor,long int>(s, s)) ));
    CALL_SUBTEST_1(( sparse_basic(SparseMatrix<double,RowMajor,long int>(s, s)) ));
    
    CALL_SUBTEST_1(( sparse_basic(SparseMatrix<double,ColMajor,short int>(short(s), short(s))) ));
    CALL_SUBTEST_1(( sparse_basic(SparseMatrix<double,RowMajor,short int>(short(s), short(s))) ));
  }
}
