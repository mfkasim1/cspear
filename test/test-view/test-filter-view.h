#ifndef CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H
#define CSPEAR_TEST_TEST_VIEW_TEST_FILTER_VIEW_H

#include <vector>
#include "gtest/gtest.h"
#include <cspear/cspear>
#include "test_params.h"

namespace {
  template <typename T>
  class FilterView : public testing::Test {};
  template <typename T>
  class FilterViewOutlierTest : public testing::Test {};

  TYPED_TEST_SUITE(FilterView, RealDoubleNumber);
  TYPED_TEST_SUITE(FilterViewOutlierTest, RealDoubleNumber);

  TYPED_TEST(FilterView,FromContiguous) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)3);

    std::vector<int> shape = {3};
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)2, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    a.filter(a <= (TypeParam)3) += (TypeParam)2;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceAddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    a.filter(a <= (TypeParam)3) += b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,InplaceClip) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    a.filter(a <= (TypeParam)3).maximum_((TypeParam)2);

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,AddAValue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto c = a.filter(a <= (TypeParam)3) + (TypeParam)2;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)4, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,AddArray) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    auto c = a.filter(a <= (TypeParam)3) + b;

    std::vector<int> shape = {3};
    EXPECT_EQ(c.size(), 3);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)9, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)6, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,MismatchShape) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    try {
      auto c = a.filter(b >= (TypeParam)2);
      FAIL() << "A runtime error should be thrown with mismatched filter shape.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "A runtime error should be thrown with mismatched filter shape.";
    }
  }
  TYPED_TEST(FilterView,Assign) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    csp::array<TypeParam> b = {(TypeParam)2, (TypeParam)6, (TypeParam)4};
    a.filter(a <= (TypeParam)3) = b;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }

  // reduce
  TYPED_TEST(FilterView,ReduceAll) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)4);
    EXPECT_NEAR(b.sum(), (TypeParam)10, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,ReduceAxis) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)4);
    b.reshape_({2,2});
    auto c = b.sum(0);
    EXPECT_NEAR(c[0], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)6, AbsTol<TypeParam>::val);

    auto d = b.sum(1);
    EXPECT_NEAR(d[0], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[1], (TypeParam)5, AbsTol<TypeParam>::val);
  }

  // broadcast
  TYPED_TEST(FilterView,BCast0) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)3); // (3,)
    auto c = a + b;
    a += b; // in-place

    EXPECT_EQ(c.size(), 6);
    EXPECT_NEAR(c[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[4], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[5], (TypeParam)7, AbsTol<TypeParam>::val);

    EXPECT_EQ(a.size(), 6);
    EXPECT_NEAR(a[0], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)7, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterView,BCast1) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)4); // (2,2): [[1,4],[3,2]]
    auto c = a.filter(a >= (TypeParam)5); // (2,1): [[7],[5]]
    b.reshape_({2,2});
    c.reshape_({2,1});
    auto d = b + c;
    b += c; // in-place, changes a as well

    EXPECT_EQ(d.size(), 4);
    EXPECT_NEAR(d[0], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[1], (TypeParam)11, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[2], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[3], (TypeParam)7, AbsTol<TypeParam>::val);

    EXPECT_EQ(b.size(), 4);
    EXPECT_NEAR(b[0], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)11, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_EQ(a.size(), 6);
    EXPECT_NEAR(a[0], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)11, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }

  // accumulate
  TYPED_TEST(FilterView,Accumulate0) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    auto b = a.filter(a <= (TypeParam)4); // (2,2): [[1,4],[3,2]]
    b.reshape_({2,2});

    auto c = b.cumsum();
    auto d = b.cumsum(0);
    auto e = b.cumsum(1);
    b.cumsum_(0);

    std::vector<int> shape = {2,2};
    std::vector<int> shapea = {2,3};
    EXPECT_EQ(c.size(), 4);
    EXPECT_EQ(c.shape(), shape);
    EXPECT_NEAR(c[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[2], (TypeParam)8, AbsTol<TypeParam>::val);
    EXPECT_NEAR(c[3], (TypeParam)10, AbsTol<TypeParam>::val);
    EXPECT_EQ(d.size(), 4);
    EXPECT_EQ(d.shape(), shape);
    EXPECT_NEAR(d[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(d[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_EQ(e.size(), 4);
    EXPECT_EQ(e.shape(), shape);
    EXPECT_NEAR(e[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(e[1], (TypeParam)5, AbsTol<TypeParam>::val);
    EXPECT_NEAR(e[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(e[3], (TypeParam)5, AbsTol<TypeParam>::val);

    // after inplace
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.shape(), shape);
    EXPECT_NEAR(b[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(b[3], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shapea);
    EXPECT_NEAR(a[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)6, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }

  TYPED_TEST(FilterViewOutlierTest,InplaceAddAValueWithNoTrue) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)7, (TypeParam)2, (TypeParam)5}};
    a.filter(a <= (TypeParam)0) += (TypeParam)2;

    std::vector<int> shape = {2,3};
    EXPECT_EQ(a.size(), 6);
    EXPECT_EQ(a.shape(), shape);
    EXPECT_NEAR(a[0], (TypeParam)1, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[1], (TypeParam)4, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[2], (TypeParam)3, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[3], (TypeParam)7, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[4], (TypeParam)2, AbsTol<TypeParam>::val);
    EXPECT_NEAR(a[5], (TypeParam)5, AbsTol<TypeParam>::val);
  }
  TYPED_TEST(FilterViewOutlierTest,Resize) {
    csp::array<TypeParam> a = {{(TypeParam)1, (TypeParam)4, (TypeParam)3},
                               {(TypeParam)6, (TypeParam)2, (TypeParam)5},
                               {(TypeParam)1, (TypeParam)9, (TypeParam)3}};
    auto b = a.filter(a <= (TypeParam)4);
    EXPECT_THROW({b.resize_(50);}, std::runtime_error);
  }
}

#endif
