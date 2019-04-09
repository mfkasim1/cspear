#ifndef CSPEAR_RANDOM_SHUFFLE_H
#define CSPEAR_RANDOM_SHUFFLE_H

#include <random>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <initializer_list>
#include <cspear/array/array.h>
#include <cspear/views/contiguous-view.h>
#include <cspear/random/init.h>

namespace csp {
  namespace random {
    // using SFINAE to make sure it is an array type
    template <typename ArrType,
              typename T = typename ArrType::DataType,
              typename I = typename ArrType::IndexType,
              typename ViewType = typename ArrType::ViewType>
    ArrType& shuffle_(ArrType& arr) {
      // can only be done in contiguous view
      static_assert(std::is_same<ViewType,ContiguousView<I> >::value,
          "Shuffle can only be done with contiguous view array. Please use "
          ".copy() method to get the contiguous copy of the array.");
      std::shuffle((T*)arr.begin(), (T*)arr.end(), rng);
      return arr;
    }
  }
}

#endif
