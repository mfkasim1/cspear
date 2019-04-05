#ifndef CSPEAR_TEST_TEST_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class SliceViewTest : public testing::Test {};

  TYPED_TEST_SUITE(FilterView, AllNumbers);

  TYPED_TEST(SliceViewTest,FromContiguous) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.slice({csp::whole(), {0,2}});

    std::vector<int> shape = {2,2};
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
  }
}

#endif
