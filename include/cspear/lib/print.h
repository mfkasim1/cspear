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
      if (i < vec.size()-1) {
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

  // printing array
  template <typename T, typename I, template<typename> typename View>
  std::ostream& operator<<(std::ostream& os, const array<T,I,View>& arr) {
    // print the content
    std::vector<I> strides = arr.shape();
    for (auto i = 1; i < strides.size(); ++i) {
      strides[i] *= strides[i-1];
    }

    for (auto i = 0; i < arr.size(); ++i) {
      // opening bracket
      for (auto j = 0; j < strides.size(); ++j) {
        if (i % strides[j] == 0) {
          os << "[";
        }
      }

      // the content
      os << arr[i];

      // closing bracket
      for (auto j = 0; j < strides.size(); ++j) {
        if (i % strides[j] == strides[j]-1) {
          os << "]";
        }
      }
      // comma for in-between
      if (i < arr.size()-1) {
        os << ",";
        for (auto j = 0; j < strides.size(); ++j) {
          if (i % strides[j] == strides[j]-1) {
            os << std::endl;
          }
        }
      }
    }

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
    os << " with " << arr.view() << " of memory.";
    os << std::endl;

    return os;
  }
}

#endif
