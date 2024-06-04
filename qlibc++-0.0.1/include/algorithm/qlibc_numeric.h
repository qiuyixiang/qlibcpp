#ifndef QLIBC___0_0_1_QLIBC_NUMERIC_H
#define QLIBC___0_0_1_QLIBC_NUMERIC_H

#include "../extension/c++config.h"
/// Numeric Algorithm Defined Here
namespace qlibc{
    /// accumulate()
    template<typename InputIterator, typename _Tp>
    _Tp accumulate(InputIterator __first, InputIterator __last, _Tp __init){
        for (; __first != __last; ++__first)
            __init += *__first;
        return __init;
    }
    template<typename InputIterator, typename _Tp, typename Binary_Op>
    _Tp accumulate(InputIterator __first, InputIterator __last, _Tp __init, Binary_Op __binary_op){
        for (; __first != __last; ++__first)
            __init = __binary_op(__init, *__first);
        return __init;
    }
}
#endif //QLIBC___0_0_1_QLIBC_NUMERIC_H
