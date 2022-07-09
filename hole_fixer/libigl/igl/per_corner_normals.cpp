// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "per_corner_normals.h"

#include "vertex_triangle_adjacency.h"
#include "per_face_normals.h"
#include "PI.h"

template <typename DerivedV, typename DerivedF, typename DerivedCN>
IGL_INLINE void igl::per_corner_normals(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const double corner_threshold,
  Eigen::PlainObjectBase<DerivedCN> & CN)
{
  using namespace Eigen;
  using namespace std;
  Eigen::Matrix<typename DerivedV::Scalar,Eigen::Dynamic,3> FN;
  per_face_normals(V,F,FN);
  vector<vector<int> > VF,VFi;
  vertex_triangle_adjacency(V,F,VF,VFi);
  return per_corner_normals(V,F,FN,VF,corner_threshold,CN);
}

template <
  typename DerivedV, 
  typename DerivedF, 
  typename DerivedFN, 
  typename DerivedCN>
IGL_INLINE void igl::per_corner_normals(
  const Eigen::PlainObjectBase<DerivedV>& V,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const Eigen::PlainObjectBase<DerivedFN>& FN,
  const double corner_threshold,
  Eigen::PlainObjectBase<DerivedCN> & CN)
{
  using namespace Eigen;
  using namespace std;
  vector<vector<int> > VF,VFi;
  vertex_triangle_adjacency(V,F,VF,VFi);
  return per_corner_normals(V,F,FN,VF,corner_threshold,CN);
}

template <
  typename DerivedV, 
  typename DerivedF, 
  typename DerivedFN, 
  typename IndexType,
  typename DerivedCN>
IGL_INLINE void igl::per_corner_normals(
  const Eigen::PlainObjectBase<DerivedV>& /*V*/,
  const Eigen::PlainObjectBase<DerivedF>& F,
  const Eigen::PlainObjectBase<DerivedFN>& FN,
  const std::vector<std::vector<IndexType> >& VF,
  const double corner_threshold,
  Eigen::PlainObjectBase<DerivedCN> & CN)
{
  using namespace Eigen;
  using namespace std;

  // number of faces
  const int m = F.rows();
  // valence of faces
  const int n = F.cols();

  // initialize output to ***zero***
  CN.setZero(m*n,3);

  // loop over faces
  for(size_t i = 0;int(i)<m;i++)
  {
    // Normal of this face
    Eigen::Matrix<typename DerivedV::Scalar,3,1> fn = FN.row(i);
    // loop over corners
    for(size_t j = 0;int(j)<n;j++)
    {
      const std::vector<IndexType> &incident_faces = VF[F(i,j)];
      // loop over faces sharing vertex of this corner
      for(int k = 0;k<(int)incident_faces.size();k++)
      {
        Eigen::Matrix<typename DerivedV::Scalar,3,1> ifn = FN.row(incident_faces[k]);
        // dot product between face's normal and other face's normal
        double dp = fn.dot(ifn);
        // if difference in normal is slight then add to average
        if(dp > cos(corner_threshold*PI/180))
        {
          // add to running sum
          CN.row(i*n+j) += ifn;
        // else ignore
        }else
        {
        }
      }
      // normalize to take average
      CN.row(i*n+j).normalize();
    }
  }
}
#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template void igl::per_corner_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, double, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
template void igl::per_corner_normals<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<double, -1, -1, 0, -1, -1> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> > const&, double, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&);
template void igl::per_corner_normals<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, double, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> >&);
template void igl::per_corner_normals<Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<int, -1, 3, 0, -1, 3>, Eigen::Matrix<double, -1, 3, 0, -1, 3>, Eigen::Matrix<double, -1, 3, 0, -1, 3> >(Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, 3, 0, -1, 3> > const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> > const&, double, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, 3, 0, -1, 3> >&);
#endif
