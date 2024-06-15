#ifndef QLIBC___0_0_2_QLIBC_ALGORITHM_BASE_H
#define QLIBC___0_0_2_QLIBC_ALGORITHM_BASE_H

#include "../config.h"

namespace __qlibc__{

}
namespace qlibc{
    /// equal
    template<typename _InputIterator1, typename _InputIterator2>
    inline bool equal(_InputIterator1 __first, _InputIterator1 __last, _InputIterator2 __target){
        for ( ; __first != __last; ++__first, ++__target)
            if (*__first != *__target)
                return false;
        return true;
    }
    template<typename _InputIterator1, typename _InputIterator2, typename _BinaryPredicate>
    inline bool equal(_InputIterator1 __first, _InputIterator1 __last,
                      _InputIterator2 __target, _BinaryPredicate __binary_func){
        for ( ; __first != __last; ++__first, ++__target)
            if (!__binary_func(*__first, *__target))
                return false;
        return true;
    }
    /// fill
    template<typename _ForwardIterator, typename _Tp>
    inline void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __value){
        for (; __first != __last; ++__first)
            *__first = __value;
    }
    template<typename _ForwardIterator, typename _Tp, typename _Size>
    inline _ForwardIterator fill_n(_ForwardIterator __first, _Size __n, const _Tp& __value){
        for (; __n != 0; --__n, ++__first)
            *__first = __value;
        return __first;
    }
    /// lexicographical_compare (Judge Whether Less-Than)
    template<typename _InputIterator1, typename _InputIterator2>
    inline bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                                        _InputIterator2 __first2, _InputIterator2 __last2){
        for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2){
            if (*__first1 < *__first2)
                return true;
            if (*__first2 < *__first1)
                return false;
        }
        return __first1 == __last1 && __first2 != __last2;
    }
    template<typename _InputIterator1, typename _InputIterator2, typename _Binary_Compare>
    inline bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
                            _InputIterator2 __first2, _InputIterator2 __last2, _Binary_Compare __compare){
        for ( ; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2){
            if (__compare(*__first1, *__first2))
                return true;
            if (__compare(*__first2, *__first1))
                return false;
        }
        return __first1 == __last1 && __first2 != __last2;
    }
}
namespace __qlibc__{

}
#endif //QLIBC___0_0_2_QLIBC_ALGORITHM_BASE_H
