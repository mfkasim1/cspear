#ifndef CSPEAR_TEST_TEST_VIEW_TEST_CONTIGUOUS_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_CONTIGUOUS_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class ContiguousViewSingleElmt : public testing::Test {};
  template <typename T>
  class ContiguousViewMultiElmt : public testing::Test {};

  TYPED_TEST_SUITE(ContiguousViewSingleElmt, AllNumbers);
  TYPED_TEST_SUITE(ContiguousViewMultiElmt, AllNumbers);

  // test accessing the first dimension
  TYPED_TEST(ContiguousViewSingleElmt,FromContiguous1D) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3};
    auto b = a.at(0);
    auto c = a.at(1);

    std::vector<int> shape = {1};
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(c.size(), 1);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[0], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,FromContiguous2D) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    auto b = a.at(0);
    auto c = a.at(1);

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,FromContiguous2DError) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    try {
      auto b = a.at(2);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }

    try {
      auto b = a.at(-1);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
  }
  TYPED_TEST(ContiguousViewSingleElmt,InplaceAddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    a.at(0) += (TypeParam)1;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,InplaceAddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)1, (TypeParam)2, (TypeParam)4};
    a.at(0) += b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,InplaceClip) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    a.at(0).maximum_((TypeParam)3);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,AddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    auto b = a.at(0) + (TypeParam)1;

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,AddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> c = {(TypeParam)1, (TypeParam)2, (TypeParam)3};
    auto b = a.at(0) + c;

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,AddArrayBCast) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> c = {(TypeParam)1, (TypeParam)2, (TypeParam)3};
    auto b = a.at(0) + c.at(0); // c.at(0) is {1}

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,Assignment) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> c = {(TypeParam)1, (TypeParam)2, (TypeParam)3};
    a.at(0) = c;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,Aliasing1) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    a += a.at(0);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)8, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,Copy) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    auto b = a.at(0).copy();

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewSingleElmt,Copy2) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b;
    b = a.at(1).copy();
    b = a.at(0).copy();

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)3, AbsTol<TypeParam>::val);
  }

  // accessing a slice from the first dimension
  TYPED_TEST(ContiguousViewMultiElmt,FromContiguous1D) {
    csp::array<TypeParam> a = {(TypeParam)1, (TypeParam)4, (TypeParam)3};
    auto b = a.at(0,1);
    auto c = a.at(0,2);

    std::vector<int> shape1 = {1};
    std::vector<int> shape2 = {2};
    EXPECT_EQ(b.size(), 1);
    EXPECT_EQ(b.shape(), shape1);
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,FromContiguous2D) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    auto b = a.at(0,1);
    auto c = a.at(1,3);

    std::vector<int> shape = {1,3};
    std::vector<int> shape2 = {2,3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_EQ(c.size(), 6);
    EXPECT_EQ(c.shape(), shape2);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[4], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[5], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,FromContiguous2DError) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    try {
      auto b = a.at(-1,3);
      FAIL() << "A runtime_error should be thrown for negative index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }

    try {
      auto b = a.at(-1,1);
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime_error should be thrown for out-of-range index";
    }
  }
  TYPED_TEST(ContiguousViewMultiElmt,InplaceAddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    a.at(0,2) += (TypeParam)1;

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[6], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[7], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[8], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,InplaceAddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    csp::array<TypeParam> b = {(TypeParam)1, (TypeParam)2, (TypeParam)4};
    a.at(0,2) += b;

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[6], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[7], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[8], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,InplaceClip) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    a.at(0,2).maximum_((TypeParam)3);

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[6], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[7], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[8], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,AddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    auto b = a.at(0,2) + (TypeParam)1;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,AddArrayBCast) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    csp::array<TypeParam> c = {(TypeParam)1, (TypeParam)2, (TypeParam)3};
    auto b = a.at(0,2) + c;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(b.size(), 6);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[5], (TypeParam)8, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,Assignment) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    csp::array<TypeParam> c = {(TypeParam)1, (TypeParam)2, (TypeParam)3};
    a.at(0,2) = c;

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[6], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[7], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[8], (TypeParam)3, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(ContiguousViewMultiElmt,Aliasing1) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    a.at(0,2) = a.at(1,3);

    std::vector<int> shape = {3,3};
    EXPECT_EQ(a.size(), 9);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[6], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[7], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[8], (TypeParam)3, AbsTol<TypeParam>::val);
  }
}

#endif
