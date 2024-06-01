#ifndef QLIBC___0_0_1_QLIBC_ITERATOR_FUNC_H
#define QLIBC___0_0_1_QLIBC_ITERATOR_FUNC_H
#include "./qlibc_iterator_base.h"

namespace __qlibc__{
    template<typename _InputIterator, typename _Distance>
    inline void __advance(_InputIterator& __Iter, _Distance __n, qlibc::input_iterator_tag){
        static_assert(__n >= 0, "Input Iterator Type Cannot Move BackWard !");
        while (__n--)
            ++__Iter;
    }
    template<typename _BidirectionalIterator, typename _Distance>
    inline void __advance(_BidirectionalIterator& __Iter, _Distance __n, qlibc::bidirectional_iterator_tag){
        if (__n >= 0)
            while (__n--)
                ++__Iter;
        else
            while (__n++)
                --__Iter;
    }
    template<typename _BidirectionalIterator, typename _Distance>
    inline void __advance(_BidirectionalIterator& __Iter, _Distance __n, qlibc::random_access_iterator_tag){
        __Iter += __n;
    }

    template<typename _InputIterator>
    inline typename qlibc::iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last, qlibc::input_iterator_tag){
        typename qlibc::iterator_traits<_InputIterator>::difference_type __counter = 0;
        while (__first != __last){
            ++__first;
            ++__counter;
        }
        return __counter;
    }
    template<typename _InputIterator>
    inline typename qlibc::iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last, qlibc::random_access_iterator_tag){
        return __last - __first;
    }
}
namespace qlibc{
    
    /// Auxiliary Function For Iterator

    /// advance()
    template<typename _InputIterator, typename _Distance>
    inline void advance(_InputIterator& _Iter, _Distance _n){
        typedef typename qlibc::iterator_traits<_InputIterator>::iterator_category Iter_Type;
        __qlibc__::__advance(_Iter, _n, Iter_Type{ });
    }
    /// next()
    template<typename _InputIterator>
    inline _InputIterator next(_InputIterator _Iter,
           typename qlibc::iterator_traits<_InputIterator>::difference_type _N = 1){
        advance(_Iter, _N);
        return _Iter;
    }
    /// prev()
    template<typename _InputIterator>
    inline _InputIterator prev(_InputIterator _Iter,
           typename qlibc::iterator_traits<_InputIterator>::difference_type _N = 1){
        advance(_Iter, -_N);
        return _Iter;
    }
    /// distance()
    template<typename _InputIterator>
    inline typename qlibc::iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator _first, _InputIterator _last){
        typedef typename qlibc::iterator_traits<_InputIterator>::iterator_category Iter_Type;
        return __qlibc__::__distance(_first, _last, Iter_Type{ });
    }
    /// iter_swap()
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    void iter_swap(_ForwardIterator1 _lhs, _ForwardIterator2 _rhs){
        typename qlibc::iterator_traits<_ForwardIterator1>::value_type _temp_val = *_lhs;
        *_lhs = *_rhs;
        *_rhs = _temp_val;
    }
}

#endif //QLIBC___0_0_1_QLIBC_ITERATOR_FUNC_H
