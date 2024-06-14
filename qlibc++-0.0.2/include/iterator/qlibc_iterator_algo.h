#ifndef QLIBC___0_0_2_QLIBC_ITERATOR_ALGO_H
#define QLIBC___0_0_2_QLIBC_ITERATOR_ALGO_H

#include "./qlibc_iterator_base.h"
namespace __qlibc__{
    /// Forward Declaration
    template<typename _InputIterator, typename _Distance>
    inline void __advance(_InputIterator&, _Distance, qlibc::input_iterator_tag);
    template<typename _BidirectionalIterator, typename _Distance>
    inline void __advance(_BidirectionalIterator&, _Distance, qlibc::bidirectional_iterator_tag);
    template<typename _RandomAccessIterator, typename _Distance>
    inline void __advance(_RandomAccessIterator&, _Distance , qlibc::random_access_iterator_tag);

    template<typename _InputIterator>
    inline typename qlibc::iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator, _InputIterator, qlibc::input_iterator_tag);

    template<typename _RandomAccessIterator>
    inline typename qlibc::iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator, _RandomAccessIterator, qlibc::random_access_iterator_tag);
}
namespace qlibc{
    /// advance
    template<typename _InputIterator, typename _Distance>
    inline void advance(_InputIterator& _iter, _Distance _n){
        __qlibc__::__advance(_iter, _n, qlibc::iterator_category(_iter));
    }
    /// distance
    template<typename _InputIterator>
    inline typename qlibc::iterator_traits<_InputIterator>::difference_type
    distance(_InputIterator __first, _InputIterator __last){
        return __qlibc__::__distance(__first, __last, qlibc::iterator_category(__first));
    }
    /// prev
    template<typename _BidirectionalIterator>
    inline _BidirectionalIterator prev(_BidirectionalIterator __iter){
        qlibc::advance(__iter, -1);
        return __iter;
    }
    template<typename _BidirectionalIterator>
    inline _BidirectionalIterator prev(_BidirectionalIterator __iter,
                        typename qlibc::iterator_traits<_BidirectionalIterator>::difference_type __n){
        qlibc::advance(__iter, -__n);
        return __iter;
    }
    /// next
    template<typename _InputIterator>
    inline _InputIterator next(_InputIterator __iter){
        qlibc::advance(__iter, 1);
        return __iter;
    }
    template<typename _InputIterator>
    inline _InputIterator next(_InputIterator __iter,
                           typename qlibc::iterator_traits<_InputIterator>::difference_type __n){
        qlibc::advance(__iter, __n);
        return __iter;
    }
    /// iter_swap
    template<typename _ForwardIterator1, typename _ForwardIterator2>
    inline void iter_swap(_ForwardIterator1 __iter1, _ForwardIterator2 __iter2){
        typedef typename qlibc::iterator_traits<_ForwardIterator1>::value_type Value_Type1;
        typedef typename qlibc::iterator_traits<_ForwardIterator2>::value_type Value_Type2;
        Value_Type1 __temp = *__iter1;
        *__iter1 = (Value_Type1)*__iter2;
        *__iter2 = (Value_Type2)__temp;
    }
}
namespace __qlibc__{
    template<typename _InputIterator, typename _Distance>
    inline void __advance(_InputIterator& __iter, _Distance __n, qlibc::input_iterator_tag){
        while ( __n-- != _Distance(0))
            ++__iter;
    }
    template<typename _BidirectionalIterator, typename _Distance>
    inline void __advance(_BidirectionalIterator& __iter, _Distance __n, qlibc::bidirectional_iterator_tag){
        if (__n > 0)
            while (__n-- != _Distance(0))
                ++__iter;
        else
            while (__n++)
                --__iter;

    }
    template<typename _RandomAccessIterator, typename _Distance>
    inline void __advance(_RandomAccessIterator& __iter, _Distance __n, qlibc::random_access_iterator_tag){
        __iter += __n;
    }

    template<typename _InputIterator>
    inline typename qlibc::iterator_traits<_InputIterator>::difference_type
    __distance(_InputIterator __first, _InputIterator __last, qlibc::input_iterator_tag){
        typename qlibc::iterator_traits<_InputIterator>::difference_type _Counter = 0;
        while (__first != __last){
            ++_Counter;
            ++__first;
        }
        return _Counter;
    }
    template<typename _RandomAccessIterator>
    inline typename qlibc::iterator_traits<_RandomAccessIterator>::difference_type
    __distance(_RandomAccessIterator __first, _RandomAccessIterator __last, qlibc::random_access_iterator_tag){
        return __last - __first;
    }
}

#endif //QLIBC___0_0_2_QLIBC_ITERATOR_ALGO_H
