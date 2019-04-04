#ifndef CSPEAR_ARRAY_MACRO_REDUCE_H
#define CSPEAR_ARRAY_MACRO_REDUCE_H

#include <type_traits>
#include <cspear/array/reduce.h>
#include <cspear/tools/types.h>

/*
T is the array's data type, View is the array's view.
*/

#define CSPEAR_REDUCE_ALL(opname,ufuncname,error_if_empty)                      \
  T opname() const {                                                            \
    return reduce_all<ufuncname<T>,error_if_empty >(*this);                     \
  }
#define CSPEAR_REDUCE_AXIS(opname,ufuncname,error_if_empty)                     \
  template <typename TI=tools::Int>                                             \
  array<T,I,ContiguousView> opname(TI ax) const {                               \
    static_assert(std::is_integral<TI>::value,                                  \
      "The axis of reduce operation must be an integral type.");                \
    return reduce_axis<array<T,I,ContiguousView>,                               \
                       ufuncname<T>,error_if_empty >(                           \
      *this, ax);                                                               \
  }
#define CSPEAR_REDUCE_AXES(opname,ufuncname,error_if_empty)                     \
  template <typename TI=tools::Int>                                             \
  array<T,I,ContiguousView> opname(const std::vector<TI>& ax) const {           \
    static_assert(std::is_integral<TI>::value,                                  \
      "The axes of reduce operation must be an integral type.");                \
    return reduce_axes<array<T,I,ContiguousView>,                               \
                       ufuncname<T>,error_if_empty >(                           \
      *this, ax);                                                               \
  }                                                                             \
  template <typename TI, typename II>                                           \
  array<T,I,ContiguousView> opname(                                             \
    const array<TI,II,ContiguousView>& ax) const {                              \
                                                                                \
    static_assert(std::is_integral<TI>::value,                                  \
      "The axes of reduce operation must be an integral type.");                \
    std::vector<TI> axvec(ax.data(), ax.data()+ax.size());                      \
    return reduce_axes<array<T,I,ContiguousView>,                               \
                       ufuncname<T>,error_if_empty >(                           \
      *this, axvec);                                                            \
  }                                                                             \
  template <typename TI, typename II, template<typename> typename ViewI>        \
  array<T,I,ContiguousView> opname(const array<TI,II,ViewI>& ax) const {        \
    static_assert(std::is_integral<TI>::value,                                  \
      "The axes of reduce operation must be an integral type.");                \
    auto axcopy = ax.copy();                                                    \
    std::vector<TI> axvec(axcopy.data(), axcopy.data()+axcopy.size());          \
    return reduce_axes<array<T,I,ContiguousView>,                               \
                       ufuncname<T>,error_if_empty >(                           \
      *this, axvec);                                                            \
  }

#define CSPEAR_REDUCE(opname,ufuncname,error_if_empty)                          \
  CSPEAR_REDUCE_ALL(opname,ufuncname,error_if_empty);                           \
  CSPEAR_REDUCE_AXIS(opname,ufuncname,error_if_empty);                          \
  CSPEAR_REDUCE_AXES(opname,ufuncname,error_if_empty);

#endif
