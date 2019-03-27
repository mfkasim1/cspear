#ifndef CSPEAR_ARRAY_UFUNCS_H
#define CSPEAR_ARRAY_UFUNCS_H

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
      static const bool has_simd = false;
      static inline T binary(const T& a, const T& b) { return b / a; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct assign {
      static const bool has_simd = true;
      static inline T binary(const T& a, const T& b) { return b; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) { return b; }
    };
    template <typename T>
    struct clip_lb {
      static const bool has_simd = false;
      static inline T binary(const T& a, const T& lb) { return a < lb ? lb : a; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct clip_ub {
      static const bool has_simd = false;
      static inline T binary(const T& a, const T& ub) { return a > ub ? ub : a; }
      static inline simd::Vector<T> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
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
      static inline bool binary(const T& a, const T& b) { return a && b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
    template <typename T>
    struct logical_or {
      static const bool has_simd = false;
      static inline bool binary(const T& a, const T& b) { return a || b; }
      static inline simd::Vector<bool> simd_binary(const simd::Vector<T>& a,
        const simd::Vector<T>& b) {}
    };
  }
}

#endif
