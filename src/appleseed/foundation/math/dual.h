
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2015-2016 Esteban Tovagliari, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_FOUNDATION_MATH_DUAL_H
#define APPLESEED_FOUNDATION_MATH_DUAL_H

// appleseed.foundation headers.
#include "foundation/math/vector.h"

// Standard headers.
#include <cassert>

namespace foundation
{

//
// Dual holds a quantity and optionally its partial derivatives wrt. X and Y.
//

template <typename T>
class Dual
{
  public:
    // Types.
    typedef T ValueType;

    // Constructors.
    Dual();
    explicit Dual(const T& value);
    Dual(const T& value, const T& dx, const T& dy);

    // Value.
    const T& get_value() const;

    // Derivatives.
    bool has_derivatives() const;
    const T& get_dx() const;
    const T& get_dy() const;

  private:
    T       m_value;
    T       m_dx;
    T       m_dy;
    bool    m_has_derivatives;
};


//
// Full specializations for scalars and vectors of type float and double.
//

typedef Dual<float>     Dual1f;
typedef Dual<double>    Dual1d;

typedef Dual<Vector2f>  Dual2f;
typedef Dual<Vector2d>  Dual2d;

typedef Dual<Vector3f>  Dual3f;
typedef Dual<Vector3d>  Dual3d;


//
// Dual class implementation.
//

template <typename T>
inline Dual<T>::Dual()
  : m_has_derivatives(false)
{
}

template <typename T>
inline Dual<T>::Dual(const T& value)
  : m_value(value)
  , m_has_derivatives(false)
{
}

template <typename T>
inline Dual<T>::Dual(const T& value, const T& dx, const T& dy)
  : m_value(value)
  , m_dx(dx)
  , m_dy(dy)
  , m_has_derivatives(true)
{
}

template <typename T>
inline const T& Dual<T>::get_value() const
{
    return m_value;
}

template <typename T>
inline bool Dual<T>::has_derivatives() const
{
    return m_has_derivatives;
}

template <typename T>
inline const T& Dual<T>::get_dx() const
{
    assert(m_has_derivatives);
    return m_dx;
}

template <typename T>
inline const T& Dual<T>::get_dy() const
{
    assert(m_has_derivatives);
    return m_dy;
}

}       // namespace foundation

#endif  // !APPLESEED_FOUNDATION_MATH_DUAL_H
