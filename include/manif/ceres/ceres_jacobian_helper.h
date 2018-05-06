#ifndef _MANIF_MANIF_CERES_JACOBIAN_HELPER_H_
#define _MANIF_MANIF_CERES_JACOBIAN_HELPER_H_

#include "manif/SO2.h"

namespace manif
{

//template <typename _Derived>
//Eigen::Matrix<typename ManifoldBase<_Derived>::Scalar,
//              ManifoldBase<_Derived>::RepSize,
//              ManifoldBase<_Derived>::DoF>
//computeJacobian(const ManifoldBase<_Derived> m)
//{
//  MANIF_NOT_IMPLEMENTED_YET
//  return Eigen::Matrix<typename ManifoldBase<_Derived>::Scalar,
//                       ManifoldBase<_Derived>::RepSize,
//                       ManifoldBase<_Derived>::DoF>();
//}

template <typename _Manifold>
Eigen::Matrix<typename _Manifold::Scalar,
              _Manifold::RepSize,
              _Manifold::DoF>
computeJacobian(const _Manifold& /*m*/)
{
  MANIF_NOT_IMPLEMENTED_YET;
  return Eigen::Matrix<typename _Manifold::Scalar,
                       _Manifold::RepSize,
                       _Manifold::DoF>();
}

template<>
Eigen::Matrix<SO2d::Scalar,
              SO2d::RepSize,
              SO2d::DoF>
computeJacobian<Eigen::Map<const SO2d>>(const Eigen::Map<const SO2d>& m)
{
  using Jacobian_lift_coeffs = Eigen::Matrix<SO2d::Scalar,
                                             SO2d::RepSize,
                                             SO2d::DoF>;
  return (Jacobian_lift_coeffs()
           << -m.imag(),
               m.real() ).finished();
}

} /* namespace manif */

#endif /* _MANIF_MANIF_CERES_JACOBIAN_HELPER_H_ */
