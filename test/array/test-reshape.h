#ifndef CSPEAR_TEST_ARRAY_TEST_RESHAPE_H
#define CSPEAR_TEST_ARRAY_TEST_RESHAPE_H

#include <vector>
#include <cspear/cspear>

namespace {
  TEST(ReshapeTest,Resize) {
    csp::array<double> arr = {1.0, 2.0};
    arr.resize_(5);

    EXPECT_EQ(arr.size(), 5);
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 5);
    EXPECT_EQ(shape.size(), 1);
  }

  TEST(ReshapeTest,Reshape1) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    arr.reshape_({3,2});

    EXPECT_EQ(arr.size(), 6);
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TEST(ReshapeTest,Reshape2) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<int> sh = {3,2};
    arr.reshape_(sh);

    EXPECT_EQ(arr.size(), 6);
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 2);
    EXPECT_EQ(shape.size(), 2);
  }

  TEST(ReshapeTest,Squeeze) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    arr.reshape_({3,1,2,1});

    EXPECT_EQ(arr.size(), 6);
    auto shape = arr.shape();
    EXPECT_EQ(shape[0], 3);
    EXPECT_EQ(shape[1], 1);
    EXPECT_EQ(shape[2], 2);
    EXPECT_EQ(shape[3], 1);
    EXPECT_EQ(shape.size(), 4);

    // squeeze
    arr.squeeze_();
    std::vector<int> sh = {3,2};
    EXPECT_EQ(arr.shape(), sh);
  }

  TEST(ReshapeTest,ExpandDims) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    arr.reshape_({3,2,1});

    EXPECT_EQ(arr.size(), 6);
    std::vector<int> sh0 = {3,2,1};
    EXPECT_EQ(arr.shape(), sh0);

    // expand_dims_
    arr.expand_dims_(1);
    std::vector<int> sh = {3,1,2,1};
    EXPECT_EQ(arr.shape(), sh);
    arr.expand_dims_(0);
    std::vector<int> sh2 = {1,3,1,2,1};
    EXPECT_EQ(arr.shape(), sh2);
  }

  TEST(ReshapeTest,Ravel) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    arr.reshape_({3,2,1});

    EXPECT_EQ(arr.size(), 6);
    std::vector<int> sh0 = {3,2,1};
    EXPECT_EQ(arr.shape(), sh0);

    // ravel_
    arr.ravel_();
    std::vector<int> sh = {6};
    EXPECT_EQ(arr.shape(), sh);
  }

  TEST(ReshapeTest,ReshapeError1) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    try {
      arr.reshape_({3,3});
      FAIL() << "Expected runtime_error with unmatched reshape.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "Expected runtime_error with unmatched reshape.";
    }

    // the shape should stay the same
    std::vector<int> sh = {6};
    EXPECT_EQ(arr.shape(), sh);
  }

  TEST(ReshapeTest,ReshapeError2) {
    csp::array<double> arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    std::vector<int> shape = {3,3};
    try {
      arr.reshape_(shape);
      FAIL() << "Expected runtime_error with unmatched reshape.";
    }
    catch (const std::runtime_error& e) {
      SUCCEED();
    }
    catch (...) {
      FAIL() << "Expected runtime_error with unmatched reshape.";
    }

    // the shape should stay the same
    std::vector<int> sh = {6};
    EXPECT_EQ(arr.shape(), sh);
  }
}

#endif
