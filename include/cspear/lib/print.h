#ifndef CSPEAR_LIB_PRINT_H
#define CSPEAR_LIB_PRINT_H

#include <iostream>
#include <vector>

namespace csp {
  // printing vector (e.g. shape)
  template <typename I>
  std::ostream& operator<<(std::ostream& os, const std::vector<I>& vec) {
    os << "(";
    for (auto i = 0; i < vec.size(); ++i) {
      os << vec[i];
      if ((i < vec.size()-1) || (i == 0)) {
        os << ",";
      }
    }
    os << ")";
    return os;
  }

  // printing view
  template <typename I>
  std::ostream& operator<<(std::ostream& os, const ContiguousView<I>& view) {
    os << "contiguous view";
    return os;
  }
  template <typename I>
  std::ostream& operator<<(std::ostream& os, const FilterView<I>& view) {
    os << "filter view";
    return os;
  }
  template <typename I>
  std::ostream& operator<<(std::ostream& os, const SliceView<I>& view) {
    os << "slice view";
    return os;
  }

  // printing array
  template <typename T, typename I, template<typename> typename View>
  void print_array(std::ostream& os, const array<T,I,View>& arr,
                    const char* delim, const char* newline,
                    const char* lbracket, const char* rbracket) {
    // print the content
    auto ndim = arr.ndim();
    std::vector<I> strides(ndim);
    auto& sh = arr.shape();
    strides[0] = sh[ndim-1];
    for (auto i = 1; i < strides.size(); ++i) {
      strides[i] = strides[i-1] * sh[ndim-i-1];
    }

    auto it = EWiseIterator<T,I,View<I> >((T*)arr.data(), arr.view());
    for (auto i = 0; it; ++i, ++it) {
      // opening bracket
      for (auto j = 0; j < strides.size(); ++j) {
        if (i % strides[j] == 0) {
          os << lbracket;
        }
      }

      // the content
      os << *it;

      // closing bracket
      for (auto j = 0; j < strides.size(); ++j) {
        if (i % strides[j] == strides[j]-1) {
          os << rbracket;
        }
      }
      // comma for in-between
      if (i < arr.size()-1) {
        os << delim;
        for (auto j = 0; j < strides.size(); ++j) {
          if (i % strides[j] == strides[j]-1) {
            os << newline;
          }
        }
      }
    }
  }

  template <typename T, typename I, template<typename> typename View>
  std::ostream& operator<<(std::ostream& os, const array<T,I,View>& arr) {
    print_array(os, arr, ",", "\n", "[]", "]");

    // print the info
    os << std::endl;
    os << arr.shape() << " array";
    // get the type
    if (std::is_same<T,double>::value)
      os << " of double";
    else if (std::is_same<T,float>::value)
      os << " of float";
    else if (std::is_same<T,int>::value)
      os << " of int";
    else if (std::is_same<T,long int>::value)
      os << " of long int";
    else if (std::is_same<T,long long int>::value)
      os << " of long long int";
    else if (std::is_same<T,bool>::value)
      os << " of bool";

    // print the view
    os << " with " << arr.view();
    os << std::endl;

    return os;
  }
}

#endif
