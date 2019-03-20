#ifndef CSPEAR_ARRAY_ARRAY_OP_H
#define CSPEAR_ARRAY_ARRAY_OP_H

// implementation of the array operations

#include <cspear/array/array.h>
#include <cspear/array/op.h>

namespace csp {
  // non inplace unary operators and binary with a value
  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator-() {
    return unary_op< array<T,I,ContiguousView> >([&](T& b) {return -b;}, *this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator+(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& a) {return b+a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator-(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& a) {return b-a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator*(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& a) {return b*a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::operator/(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& a) {return b/a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::reciprocal(T a) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& a) {return a/b;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip_lb(T lb) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& lb) {return (b < lb) ? lb : b;},
      *this, lb);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip_ub(T ub) {
    return ewise_binary_op_with_val< array<T,I,ContiguousView> >(
      [&](T& b, const T& ub) {return (b > ub) ? ub : b;},
      *this, ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,ContiguousView> array<T,I,View>::clip(T lb, T ub) {
    return unary_op< array<T,I,ContiguousView> >(
      [&](T& b) {return (b < lb) ? lb : ((b > ub) ? ub : b);},
      *this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator!() {
    return unary_op< array<bool,I,ContiguousView> >([&](T& b) {return !b;},
           *this);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator>(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b>a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator>=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b>=a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator<(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b<a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator<=(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b<=a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator==(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b==a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator&&(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b&&a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<bool,I,ContiguousView> array<T,I,View>::operator||(T a) {
    return ewise_binary_op_with_val< array<bool,I,ContiguousView> >(
      [&](T& b, const T& a) {return b||a;}, *this, a);
  }


  // inplace unary operators and binary operators with a value
  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator+=(T a) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& a) {b+=a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator-=(T a) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& a) {b-=a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator*=(T a) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& a) {b*=a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::operator/=(T a) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& a) {b/=a;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::reciprocal_(T a) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& a) {b=a/b;}, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_lb_(T lb) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& lb) {
        b = (b < lb) ? lb : b;
      }, *this, lb);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_ub_(T ub) {
    return ewise_inplace_binary_op_with_val(
      [&](T& b, const T& ub) {
        b = (b > ub) ? ub : b;
      }, *this, ub);
  }

  template <typename T, typename I, template<typename> typename View>
  array<T,I,View>& array<T,I,View>::clip_(T lb, T ub) {
    return inplace_unary_op(
      [&](T& b) {
        b = (b < lb) ? lb : (b > ub ? ub : b);
      }, *this);
  }

  // binary operators (non inplace)
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator+(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1 + b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator-(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1 - b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator*(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1 * b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,ContiguousView> array<T,I,View>::operator/(const array<T,I,View2>& a) {
    return binary_op< array<T,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1 / b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator>(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1>b2;
      }, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator>=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1>=b2;
      }, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator<(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1<b2;
      }, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator<=(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1<=b2;
      }, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator==(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1==b2;
      }, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator&&(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1&&b2;
      }, *this, a);
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<bool,I,ContiguousView> array<T,I,View>::operator||(const array<T,I,View2>& a) {
    return binary_op< array<bool,I,ContiguousView> >(
      [](T& b1, const T& b2) {
        return b1||b2;
      }, *this, a);
  }


  // inplace binary operators
  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator+=(const array<T,I,View2>& a) {
    return inplace_binary_op(
      [](T& b1, const T& b2) {
        b1 += b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator-=(const array<T,I,View2>& a) {
    return inplace_binary_op(
      [](T& b1, const T& b2) {
        b1 -= b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator*=(const array<T,I,View2>& a) {
    return inplace_binary_op(
      [](T& b1, const T& b2) {
        b1 *= b2;
      },
      *this, a
    );
  }

  template <typename T, typename I, template<typename> typename View>
  template <template<typename> typename View2>
  array<T,I,View>& array<T,I,View>::operator/=(const array<T,I,View2>& a) {
    return inplace_binary_op(
      [](T& b1, const T& b2) {
        b1 /= b2;
      },
      *this, a
    );
  }
}

#endif
