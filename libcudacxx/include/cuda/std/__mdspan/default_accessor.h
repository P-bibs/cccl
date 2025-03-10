/*
//@HEADER
// ************************************************************************
//
//                        Kokkos v. 2.0
//              Copyright (2019) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Christian R. Trott (crtrott@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#ifndef _LIBCUDACXX___MDSPAN_DEFAULT_ACCESSOR_HPP
#define _LIBCUDACXX___MDSPAN_DEFAULT_ACCESSOR_HPP

#include <cuda/std/detail/__config>

#if defined(_CCCL_IMPLICIT_SYSTEM_HEADER_GCC)
#  pragma GCC system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_CLANG)
#  pragma clang system_header
#elif defined(_CCCL_IMPLICIT_SYSTEM_HEADER_MSVC)
#  pragma system_header
#endif // no system header

#include <cuda/std/__mdspan/macros.h>
#include <cuda/std/__type_traits/is_convertible.h>
#include <cuda/std/cstddef>

_LIBCUDACXX_BEGIN_NAMESPACE_STD

template <class _ElementType>
struct default_accessor
{
  using offset_policy    = default_accessor;
  using element_type     = _ElementType;
  using reference        = _ElementType&;
  using data_handle_type = _ElementType*;

  _CCCL_HIDE_FROM_ABI constexpr default_accessor() noexcept = default;

  _CCCL_TEMPLATE(class _OtherElementType)
  _CCCL_REQUIRES(_CCCL_TRAIT(is_convertible, _OtherElementType (*)[], element_type (*)[]))
  _LIBCUDACXX_HIDE_FROM_ABI constexpr default_accessor(default_accessor<_OtherElementType>) noexcept {}

  _LIBCUDACXX_HIDE_FROM_ABI constexpr data_handle_type offset(data_handle_type __p, size_t __i) const noexcept
  {
    return __p + __i;
  }

  __MDSPAN_FORCE_INLINE_FUNCTION
  constexpr reference access(data_handle_type __p, size_t __i) const noexcept
  {
    return __p[__i];
  }
};

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___MDSPAN_DEFAULT_ACCESSOR_HPP
