#ifndef CSPEAR_TEST_TEST_PARAMS_H
#define CSPEAR_TEST_TEST_PARAMS_H

#include <cstdlib>
#include "gtest/gtest.h"

namespace {
  template <typename T>
  struct AbsTol {
    static const T val;
  };
  template <> const double AbsTol<double>::val = 1e-10;
  template <> const float AbsTol<float>::val = 1e-5;
  template <> const std::int8_t AbsTol<std::int8_t>::val = 0;
  template <> const std::int16_t AbsTol<std::int16_t>::val = 0;
  template <> const std::int32_t AbsTol<std::int32_t>::val = 0;
  template <> const std::int64_t AbsTol<std::int64_t>::val = 0;
  template <> const std::uint8_t AbsTol<std::uint8_t>::val = 0;
  template <> const std::uint16_t AbsTol<std::uint16_t>::val = 0;
  template <> const std::uint32_t AbsTol<std::uint32_t>::val = 0;
  template <> const std::uint64_t AbsTol<std::uint64_t>::val = 0;

  using testing::Types;
  typedef Types<double, float,
                std::int8_t, std::int16_t, std::int32_t, std::int64_t,
                std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t>
                AllNumbers;
  typedef Types<double, float> RealNumbers;
  typedef Types<double, float, bool,
                std::int8_t, std::int16_t, std::int32_t, std::int64_t,
                std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t>
                AllTypes;
}

#endif
