/*
 * Copyright (c) 2016, Graphics Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Humanoid Lab, Georgia Tech Research Corporation
 * Copyright (c) 2016, Personal Robotics Lab, Carnegie Mellon University
 * All rights reserved.
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_MATH_DETAIL_SO3VECTOR_IMPL_HPP_
#define DART_MATH_DETAIL_SO3VECTOR_IMPL_HPP_

#include "dart/math/SO3Vector.hpp"

namespace dart {
namespace math {

//==============================================================================
template <typename S>
SO3Vector<S>::SO3Vector() : Base(), mRepData()
{
  // Do nothing
}

//==============================================================================
template <typename S>
SO3Vector<S>::SO3Vector(const SO3Vector& other)
  : Base(), mRepData(other.mRepData)
{
  // Do nothing
}

//==============================================================================
template <typename S>
SO3Vector<S>::SO3Vector(SO3Vector&& other)
  : Base(), mRepData(std::move(other.mRepData))
{
  // Do nothing
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Vector<S>::SO3Vector(const SO3Base<Derived>& other)
  : Base(), mRepData()
{
  *this = other;
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Vector<S>::SO3Vector(SO3Base<Derived>&& other)
  : Base(), mRepData()
{
  *this = std::move(other);
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Vector<S>::SO3Vector(const Eigen::MatrixBase<Derived>& matrix)
  : Base(), mRepData()
{
  *this = matrix;
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Vector<S>::SO3Vector(Eigen::MatrixBase<Derived>&& matrix)
  : Base(), mRepData()
{
  *this = std::move(matrix);
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Vector<S>::SO3Vector(const Eigen::RotationBase<Derived, Dim>& rot)
  : Base(), mRepData()
{
  *this = rot;
}

//==============================================================================
template <typename S>
template <typename Derived>
SO3Vector<S>::SO3Vector(Eigen::RotationBase<Derived, Dim>&& rot)
  : Base(), mRepData()
{
  *this = std::move(rot);
}

//==============================================================================
template <typename S>
SO3Vector<S>& SO3Vector<S>::operator=(const SO3Vector& other)
{
  mRepData = other.mRepData;
  return *this;
}

//==============================================================================
template <typename S>
SO3Vector<S>& SO3Vector<S>::operator=(SO3Vector&& other)
{
  mRepData = std::move(other.mRepData);
  return *this;
}

//==============================================================================
template <typename S>
bool SO3Vector<S>::operator==(const SO3Vector& other)
{
  return mRepData == other.mRepData;
}

//==============================================================================
template <typename S>
void SO3Vector<S>::fromCanonical(const SO3Matrix<S>& mat)
{
  detail::SO3Log(mRepData, mat.getRepData());
}

//==============================================================================
template <typename S>
SO3Matrix<S> SO3Vector<S>::toCanonical() const
{
  SO3Matrix<S> res;
  detail::SO3Exp(res.getRepData(), mRepData);

  return res;
}

//==============================================================================
template <typename S>
template <typename MatrixDerived>
void SO3Vector<S>::fromRotationVector(const Eigen::MatrixBase<MatrixDerived>& vector)
{
  assert(vector.rows() == 3);
  assert(vector.cols() == 1);

  mRepData = vector;
}

//==============================================================================
template <typename S>
template <typename MatrixDerived>
void SO3Vector<S>::fromRotationVector(Eigen::MatrixBase<MatrixDerived>&& vector)
{
  assert(vector.rows() == 3);
  assert(vector.cols() == 1);

  mRepData = std::move(vector);
}

//==============================================================================
template <typename S>
typename SO3Vector<S>::Vector3 SO3Vector<S>::toRotationVector() const
{
  return mRepData;
}

//==============================================================================
template <typename S>
void SO3Vector<S>::setRotationVector(const Vector3& axisAngle)
{
  mRepData = axisAngle;
}

//==============================================================================
template <typename S>
const typename SO3Vector<S>::Vector3& SO3Vector<S>::getRotationVector() const
{
  return mRepData;
}

//==============================================================================
template <typename S>
void SO3Vector<S>::setRandom()
{
  mRepData.setRandom();
}

//==============================================================================
template <typename S>
void SO3Vector<S>::setIdentity()
{
  mRepData.setZero();
}

//==============================================================================
template <typename S>
bool SO3Vector<S>::isIdentity()
{
  return mRepData == RepData::Zero();
}

//==============================================================================
template <typename S>
void SO3Vector<S>::invert()
{
  mRepData *= static_cast<S>(-1);
}

//==============================================================================
template <typename S>
const SO3Vector<S> SO3Vector<S>::getInverse() const
{
  return SO3Vector(-mRepData);
}

} // namespace math
} // namespace dart

#endif // DART_MATH_DETAIL_SO3VECTOR_IMPL_HPP_