#ifndef CSPEAR_ARRAY_MACRO_REDUCE_H
#define CSPEAR_ARRAY_MACRO_REDUCE_H

#include <cspear/array/reduce.h>

/*
T is the array's data type, View is the array's view.
*/

#define CSPEAR_REDUCE_ALL(opname,ufuncname,error_if_empty) \
  T opname() const { \
    return reduce_all<ufuncname<T>,error_if_empty >(*this); \
  }
#define CSPEAR_REDUCE_AXIS(opname,ufuncname,error_if_empty) \
  array<T,I,ContiguousView> opname(I ax) const { \
    return reduce_axis<array<T,I,ContiguousView>, \
                       ufuncname<T>,error_if_empty >( \
      *this, ax); \
  }
#define CSPEAR_REDUCE_AXES(opname,ufuncname,error_if_empty) \
  array<T,I,ContiguousView> opname(const std::vector<I>& ax) const { \
    return reduce_axes<array<T,I,ContiguousView>, \
                       ufuncname<T>,error_if_empty >( \
      *this, ax); \
  }

#define CSPEAR_REDUCE(opname,ufuncname,error_if_empty) \
  CSPEAR_REDUCE_ALL(opname,ufuncname,error_if_empty); \
  CSPEAR_REDUCE_AXIS(opname,ufuncname,error_if_empty); \
  CSPEAR_REDUCE_AXES(opname,ufuncname,error_if_empty);

#endif
