#ifndef CSPEAR_ARRAY_UFUNCS_H
#define CSPEAR_ARRAY_UFUNCS_H

#include <iostream>
#include <cspear/simd/vector.h>

namespace csp {
  namespace ufunc {
    // unary operations
    template <typename T>
    struct neg {
      static const bool has_simd = true;
      static inline T unary(const T& a) { return -a; }
      static inline simd::Vector<T> simd_unary(const simd::Vector<T>& a) {
        return -a;
      }
    };
    template <typename T>
    struct logical_not {
      static const bool has_simd = false;
      static inline bool unary(const T& a) { return !a; }
      static inline simd::Vector<T> simd_unary(const simd::Vector<T>& a) {}
    };

    // binary operations
    template <typename T>
    struct add {
      static const bool has_simd = true;
      static constexpr T identity = (T)0;
      static inline T binary(const T& a, const T& b) { return a + b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return a + b; }
    };
    template <typename T>
    struct sub {
      static const bool has_simd = true;
      static inline T binary(const T& a, const T& b) { return a - b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return a - b; }
    };
    template <typename T>
    struct mult {
      static const bool has_simd = true;
      static constexpr T identity = (T)1;
      static inline T binary(const T& a, const T& b) { return a * b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return a * b; }
    };
    template <typename T>
    struct div {
      static const bool has_simd = true;
      static inline T binary(const T& a, const T& b) { return a / b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return a / b; }
    };
    template <typename T>
    struct reciprocal {
      static const bool has_simd = true;
      static inline T binary(const T& a, const T& b) { return b / a; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return b / a; }
    };
    template <typename T>
    struct max {
      static const bool has_simd = true;
      static constexpr T identity = std::numeric_limits<T>::lowest();
      static inline T binary(const T& a, const T& b) { return a>b?a:b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return a.max(b); }
    };
    template <typename T>
    struct min {
      static const bool has_simd = false;
      static constexpr T identity = std::numeric_limits<T>::max();
      static inline T binary(const T& a, const T& b) { return a<b?a:b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return a.min(b); }
    };
    template <typename T>
    struct assign {
      static const bool has_simd = true;
      static inline T binary(const T& a, const T& b) { return b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return b; }
    };
    template <typename T>
    struct gt {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a > b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct lt {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a < b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct gteq {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a >= b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct lteq {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a <= b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct eq {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a == b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct neq {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a != b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct logical_and {
      static const bool has_simd = false;
      static const bool identity = true;
      static inline bool binary(const T& a, const T& b) { return a && b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct logical_or {
      static const bool has_simd = false;
      static const bool identity = false;
      static inline bool binary(const T& a, const T& b) { return a || b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };

    // ternary operations
    template <typename T>
    struct clip {
      static const bool has_simd = false;
      static inline T ternary(const T& a, const T& b, const T& c) {
        return a < b ? b : (a > c ? c : a);
      }
      static inline simd::Vector<T> simd_ternary(
        const simd::Vector<T>& a,
        const simd::Vector<T>& b,
        const simd::Vector<T>& c) {}
    };
  }
}

#endif
