#ifndef CSPEAR_ARRAY_MACRO_ACCUMULATE_H
#define CSPEAR_ARRAY_MACRO_ACCUMULATE_H

#include <type_traits>
#include <cspear/array/accumulate.h>
#include <cspear/tools/types.h>

/*
T is the array's data type, View is the array's view.
*/

#define CSPEAR_ACCUMULATE_ALL(opname,ufuncname)                                 \
  array<T,I,ContiguousView> opname() const {                                    \
    return accumulate_all<array<T,I,ContiguousView>,ufuncname<T> >(*this);      \
  }
#define CSPEAR_ACCUMULATE_ALL_INPLACE(opname,ufuncname)                         \
  array<T,I,ContiguousView> opname() const {                                    \
    return accumulate_all_inplace<ufuncname<T> >(*this);                        \
  }
#define CSPEAR_ACCUMULATE_AXIS(opname,ufuncname)                                \
  template <typename TI=tools::Int>                                             \
  array<T,I,ContiguousView> opname(TI ax) const {                               \
    static_assert(std::is_integral<TI>::value,                                  \
      "The axis of accumulate operation must be an integral type.");            \
    return accumulate_axis<array<T,I,ContiguousView>, ufuncname<T> >(           \
      *this, ax);                                                               \
  }
#define CSPEAR_ACCUMULATE_AXIS_INPLACE(opname,ufuncname)                        \
  template <typename TI=tools::Int>                                             \
  array<T,I,ContiguousView> opname(TI ax) const {                               \
    static_assert(std::is_integral<TI>::value,                                  \
      "The axis of accumulate operation must be an integral type.");            \
    return accumulate_axis_inplace<ufuncname<T> >(                              \
      *this, ax);                                                               \
  }

#define CSPEAR_ACCUMULATE(opname,ufuncname)                                     \
  CSPEAR_ACCUMULATE_ALL(opname,ufuncname);                                      \
  CSPEAR_ACCUMULATE_ALL_INPLACE(opname##_,ufuncname);                           \
  CSPEAR_ACCUMULATE_AXIS(opname,ufuncname);                                     \
  CSPEAR_ACCUMULATE_AXIS_INPLACE(opname##_,ufuncname);

#endif
