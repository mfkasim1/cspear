#ifndef CSPEAR_TEST_TEST_PARAMS_H
#define CSPEAR_TEST_TEST_PARAMS_H

template <typename T>
struct AbsTol {
  static const T val;
};
template <> const double AbsTol<double>::val = 1e-10;
template <> const float AbsTol<float>::val = 1e-5;

template <typename T>
struct AVXVectorSize {
  static const int val;
};
template <> const int AVXVectorSize<double>::val = 4;
template <> const int AVXVectorSize<float>::val  = 8;


#endif
