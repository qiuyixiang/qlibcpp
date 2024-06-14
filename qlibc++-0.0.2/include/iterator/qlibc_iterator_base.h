#ifndef QLIBC___0_0_2_QLIBC_ITERATOR_BASE_H
#define QLIBC___0_0_2_QLIBC_ITERATOR_BASE_H

#include "../config.h"

namespace qlibc{

    /// Iterator Tags
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    /// Iterator Template
    template<typename _Tp, typename _Category, 
            typename _Difference = qlibc::ptrdiff_t, typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator{
        using value_type = _Tp;
        using iterator_category = _Category;
        using difference_type = _Difference;
        using reference = _Reference;
        using pointer = _Pointer;
    };

    /// Template For Iterator Traits
    template<typename _Iterator>
    struct iterator_traits{
        typedef typename _Iterator::value_type              value_type;
        typedef typename _Iterator::iterator_category       iterator_category;
        typedef typename _Iterator::difference_type         difference_type;
        typedef typename _Iterator::reference               reference;
        typedef typename _Iterator::pointer                 pointer;
    };
    template<typename _Tp>
    struct iterator_traits<_Tp*>{
        typedef typename qlibc::random_access_iterator_tag  iterator_category;
        typedef _Tp     value_type;
        typedef _Tp*    pointer;
        typedef _Tp&    reference;
        typedef qlibc::ptrdiff_t    difference_type;
    };
    template<typename _Tp>
    struct iterator_traits<const _Tp*>{
        typedef typename qlibc::random_access_iterator_tag  iterator_category;
        typedef _Tp                 value_type;
        typedef const _Tp*          pointer;
        typedef const _Tp&          reference;
        typedef qlibc::ptrdiff_t    difference_type;
    };

    template<typename _Iterator>
    inline QLIBC_CONSTEXPR typename qlibc::iterator_traits<_Iterator>::iterator_category
    iterator_category(const _Iterator&){
        return typename qlibc::iterator_traits<_Iterator>::iterator_category{ };
    }

    template<typename _Iterator>
    inline QLIBC_CONSTEXPR typename qlibc::iterator_traits<_Iterator>::value_type
    value_type(const _Iterator&){
        return typename qlibc::iterator_traits<_Iterator>::value_type{ };
    }
    template<typename _Iterator>
    inline QLIBC_CONSTEXPR typename qlibc::iterator_traits<_Iterator>::difference_type
    difference_type(const _Iterator&){
        return typename qlibc::iterator_traits<_Iterator>::difference_type{ };
    }
}

#endif //QLIBC___0_0_2_QLIBC_ITERATOR_BASE_H
