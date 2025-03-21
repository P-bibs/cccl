//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// <chrono>
// class year_month_weekday_last;

// constexpr chrono::month month() const noexcept;
//  Returns: wd_

#include <cuda/std/cassert>
#include <cuda/std/chrono>
#include <cuda/std/type_traits>

#include "test_macros.h"

int main(int, char**)
{
  using year                    = cuda::std::chrono::year;
  using month                   = cuda::std::chrono::month;
  using weekday                 = cuda::std::chrono::weekday;
  using weekday_last            = cuda::std::chrono::weekday_last;
  using year_month_weekday_last = cuda::std::chrono::year_month_weekday_last;

  ASSERT_NOEXCEPT(cuda::std::declval<const year_month_weekday_last>().month());
  ASSERT_SAME_TYPE(month, decltype(cuda::std::declval<const year_month_weekday_last>().month()));

  static_assert(year_month_weekday_last{year{}, month{}, weekday_last{weekday{}}}.month() == month{}, "");

  for (unsigned i = 1; i <= 50; ++i)
  {
    year_month_weekday_last ymd(year{1234}, month{i}, weekday_last{weekday{}});
    assert(static_cast<unsigned>(ymd.month()) == i);
  }

  return 0;
}
