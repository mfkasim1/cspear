#ifndef CSPEAR_RANDOM_INIT_H
#define CSPEAR_RANDOM_INIT_H

// This file contains initialization of array in a random manner
#include <random>
#include <chrono>
#include <vector>
#include <type_traits>
#include <initializer_list>
#include <cspear/array/array.h>
#include <cspear/lib/init.h>
#include <cspear/tools/types.h>
#include <cspear/tools/misc.h>

namespace csp {
  namespace random {
    using seed_type = uint32_t;
    using rng_type = std::mt19937;

    // random number generator and the seed
    seed_type seed = std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch()).count();
    rng_type rng(seed);

    // single number random generator
    template <typename T, typename I=tools::Int>
    T random(T lb=0, T ub=1) {
      typename std::conditional<std::is_integral<T>::value,
          std::uniform_int_distribution<T>,
          std::uniform_real_distribution<T> >::type dist(lb, ub);
      return dist(rng);
    }

    template <typename T, typename I=tools::Int>
    array<T,I> randn(T mean=0, T std=1) {
      std::normal_distribution<T> dist(mean, std);
      return dist(rng);
    }

    /**begin repeat
    tpename = ["const std::vector<I>&",
               "std::initializer_list<T>"];
    */
    // uniform random
    template <typename T, typename I=tools::Int>
    array<T,I> _random(@tpename@ shape, T lb=0, T ub=1) {
      array<T,I> res = empty<T,I>(shape);

      // generate the random number
      I sz = res.size();
      typename std::conditional<std::is_integral<T>::value,
          std::uniform_int_distribution<T>,
          std::uniform_real_distribution<T> >::type dist(lb, ub);

      // dist_t dist(lb, ub);
      for (I i = 0; i < sz; ++i) {
        res[i] = dist(rng);
      }
      return res;
    }
    template <typename T, typename I=tools::Int>
    array<T,I> random(@tpename@ shape) {
      return _random(shape, (T)0, (T)1);
    }
    template <typename T, typename I=tools::Int>
    array<T,I> random(@tpename@ shape, T ub) {
      return _random(shape, (T)0, ub);
    }
    template <typename T, typename I=tools::Int>
    array<T,I> random(@tpename@ shape, T lb, T ub) {
      return _random(shape, lb, ub);
    }

    template <typename T, typename I=tools::Int>
    array<T,I> randn(@tpename@ shape, T mean=0, T std=1) {
      array<T,I> res = empty<T,I>(shape);

      I sz = res.size();
      std::normal_distribution<T> dist(mean, std);
      for (I i = 0; i < sz; ++i) {
        res[i] = dist(rng);
      }
      return res;
    }
    /**end repeat**/
  }
}

#endif
