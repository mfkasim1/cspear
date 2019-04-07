#ifndef CSPEAR_TOOLS_MISC_H
#define CSPEAR_TOOLS_MISC_H

#include <type_traits>
#include <initializer_list>

namespace csp {
  namespace tools {
    template <typename Vec>
    auto _prod_init_list(const Vec& a) -> // returns the element type of `a`
          typename std::remove_const< typename
                   std::remove_reference<
                   decltype(*a.begin())>::type>::type {
      using T = typename std::remove_const< typename
                         std::remove_reference<
                         decltype(*a.begin())>::type>::type;
      if (a.size() == 0) return (T)0;
      T res = 1;
      for (auto it = a.begin(); it < a.end(); ++it) {
        res *= *it;
      }
      return res;
    }
  }
}

#endif
