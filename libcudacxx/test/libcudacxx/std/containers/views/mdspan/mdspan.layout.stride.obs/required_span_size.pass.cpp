//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES.
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: msvc && c++14, msvc && c++17

#include <cuda/std/cassert>
#include <cuda/std/mdspan>

constexpr auto dyn = cuda::std::dynamic_extent;

int main(int, char**)
{
  using index_t = int;
  using ext2d_t = cuda::std::extents<index_t, dyn, dyn>;

  {
    cuda::std::extents<index_t, 16> e;
    cuda::std::array<index_t, 1> a{1};
    cuda::std::layout_stride::mapping<cuda::std::extents<index_t, 16>> m{e, a};

    assert(m.required_span_size() == 16);
  }

  {
    ext2d_t e{16, 32};
    cuda::std::array<index_t, 2> a{1, 16};
    cuda::std::layout_stride::mapping<ext2d_t> m{e, a};

    assert(m.required_span_size() == 16 * 32);
  }

  {
    ext2d_t e{16, 0};
    cuda::std::array<index_t, 2> a{1, 1};
    cuda::std::layout_stride::mapping<ext2d_t> m{e, a};

    assert(m.required_span_size() == 0);
  }

  {
    cuda::std::extents<index_t, 16, dyn> e{32};
    cuda::std::array<index_t, 2> a{1, 24};
    cuda::std::layout_stride::mapping<ext2d_t> m{e, a};

    assert(m.required_span_size() == 32 * 24 - (24 - 16));
  }

  {
    cuda::std::extents<index_t, 16, dyn> e{32};
    cuda::std::array<index_t, 2> a{48, 1};
    cuda::std::layout_stride::mapping<ext2d_t> m{e, a};

    assert(m.required_span_size() == 16 * 48 - (48 - 32));
  }

  return 0;
}
