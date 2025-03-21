//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <chrono>
// class year_month_day;

//  year_month_day() = default;
//  constexpr year_month_day(const chrono::year& y, const chrono::month& m,
//                                   const chrono::day& d) noexcept;
//
//  Effects:  Constructs an object of type year_month_day by initializing
//                y_ with y, m_ with m, and d_ with d.
//
//  constexpr chrono::year   year() const noexcept;
//  constexpr chrono::month month() const noexcept;
//  constexpr chrono::day     day() const noexcept;
//  constexpr bool             ok() const noexcept;

#include <cuda/std/cassert>
#include <cuda/std/chrono>
#include <cuda/std/type_traits>

#include "test_macros.h"

int main(int, char**)
{
  using year           = cuda::std::chrono::year;
  using month          = cuda::std::chrono::month;
  using day            = cuda::std::chrono::day;
  using year_month_day = cuda::std::chrono::year_month_day;

  ASSERT_NOEXCEPT(year_month_day{});
  ASSERT_NOEXCEPT(year_month_day{year{1}, month{1}, day{1}});

  constexpr month January = cuda::std::chrono::January;

  constexpr year_month_day ym0{};
  static_assert(ym0.year() == year{}, "");
  static_assert(ym0.month() == month{}, "");
  static_assert(ym0.day() == day{}, "");
  static_assert(!ym0.ok(), "");

  constexpr year_month_day ym1{year{2019}, January, day{12}};
  static_assert(ym1.year() == year{2019}, "");
  static_assert(ym1.month() == January, "");
  static_assert(ym1.day() == day{12}, "");
  static_assert(ym1.ok(), "");

  return 0;
}
