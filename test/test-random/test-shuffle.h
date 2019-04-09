#ifndef CSPEAR_TEST_TEST_RANDOM_TEST_SHUFFLE_H
#define CSPEAR_TEST_TEST_RANDOM_TEST_SHUFFLE_H

#include <cstdlib>
#include <cspear/cspear>
#include "gtest/gtest.h"
#include "test_params.h"

namespace {
  template <typename T>
  class ShuffleTest : public testing::Test {};

  TYPED_TEST_SUITE(ShuffleTest, RealDoubleNumber);

  TYPED_TEST(ShuffleTest,Shuffle1) {
    csp::array<TypeParam> a = csp::arange((TypeParam)10);
    csp::random::shuffle_(a);
    EXPECT_NEAR(a.sum(), (TypeParam)45, AbsTol<TypeParam>::val);
  }
}

#endif
