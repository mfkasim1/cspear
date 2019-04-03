#ifndef CSPEAR_ARRAY_MACRO_OP_H
#define CSPEAR_ARRAY_MACRO_OP_H

#include <cspear/array/op.h>
// #include <cspear/views/contiguous-view.h>

/*
T is the array's data type, View is the array's view.
*/

// unary operations
#define CSPEAR_UNARY_OP_NOT_INPLACE_GENERAL(opname,ufuncname,rettype) \
  array<rettype,I,ContiguousView> opname() const { \
    return unary_op<array<rettype,I,ContiguousView>,ufuncname<T> >(*this); \
  }
#define CSPEAR_UNARY_OP_INPLACE_GENERAL(opname,ufuncname) \
  array<T,I,View>& opname() { \
    return inplace_unary_op< ufuncname<T> >(*this); \
  }

#define CSPEAR_UNARY_OP_NOT_INPLACE(opname,ufuncname) \
  CSPEAR_UNARY_OP_NOT_INPLACE_GENERAL(opname,ufuncname,T)

#define CSPEAR_UNARY_OP_NOT_INPLACE_TO_BOOL(opname,ufuncname) \
  CSPEAR_UNARY_OP_NOT_INPLACE_GENERAL(opname,ufuncname,bool)

#define CSPEAR_UNARY_OP(opname,ufuncname) \
  CSPEAR_UNARY_OP_NOT_INPLACE_GENERAL(opname,ufuncname,T); \
  CSPEAR_UNARY_OP_INPLACE_GENERAL(opname##_,ufuncname)

#define CSPEAR_UNARY_OP_TO_BOOL(opname,ufuncname) \
  CSPEAR_UNARY_OP_NOT_INPLACE_GENERAL(opname,ufuncname,bool)

// binary operations
#define CSPEAR_BINARY_OP_NOT_INPLACE_A_VALUE_GENERAL(opname,ufuncname,rettype) \
  array<rettype,I,ContiguousView> opname(T a) const { \
    return ewise_binary_op_with_val< \
                    array<rettype,I,ContiguousView>, \
                    ufuncname<T> >(*this, a); \
  }
#define CSPEAR_BINARY_OP_INPLACE_A_VALUE_GENERAL(opname,ufuncname) \
  array<T,I,View>& opname(T a) { \
    return ewise_inplace_binary_op_with_val< ufuncname<T> >(*this, a); \
  }
#define CSPEAR_BINARY_OP_NOT_INPLACE_ARRAY_GENERAL(opname,ufuncname,rettype) \
  template <template<typename> typename View2> \
  array<rettype,I,ContiguousView> opname(const array<T,I,View2>& a) const { \
    return binary_op< array<rettype,I,ContiguousView>, \
                      ufuncname<T> >(*this, a); \
  }
#define CSPEAR_BINARY_OP_INPLACE_ARRAY_GENERAL(opname,ufuncname) \
  template <template<typename> typename View2> \
  array<T,I,View>& opname(const array<T,I,View2>& a) { \
    return inplace_binary_op< ufuncname<T> >(*this, a); \
  }

#define CSPEAR_BINARY_OP_NOT_INPLACE(opname,ufuncname) \
  CSPEAR_BINARY_OP_NOT_INPLACE_A_VALUE_GENERAL(opname,ufuncname,T); \
  CSPEAR_BINARY_OP_NOT_INPLACE_ARRAY_GENERAL(opname,ufuncname,T)

#define CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(opname,ufuncname) \
  CSPEAR_BINARY_OP_NOT_INPLACE_A_VALUE_GENERAL(opname,ufuncname,bool); \
  CSPEAR_BINARY_OP_NOT_INPLACE_ARRAY_GENERAL(opname,ufuncname,bool)

#define CSPEAR_BINARY_OP_INPLACE(opname,ufuncname) \
  CSPEAR_BINARY_OP_INPLACE_A_VALUE_GENERAL(opname,ufuncname); \
  CSPEAR_BINARY_OP_INPLACE_ARRAY_GENERAL(opname,ufuncname)

#define CSPEAR_BINARY_OP(opname,ufuncname) \
  CSPEAR_BINARY_OP_INPLACE(opname##_,ufuncname); \
  CSPEAR_BINARY_OP_NOT_INPLACE(opname,ufuncname)

#define CSPEAR_BINARY_OP_TO_BOOL(opname,ufuncname) \
  CSPEAR_BINARY_OP_INPLACE(opname##_,ufuncname); \
  CSPEAR_BINARY_OP_NOT_INPLACE_TO_BOOL(opname,ufuncname,bool)
#endif
