#ifndef QLIBC___0_0_1_QLIBC_ITERATOR_BASE_H
#define QLIBC___0_0_1_QLIBC_ITERATOR_BASE_H

#include "../extension/c++config.h"
#include "../meta_programming/qlibc_type_traits.h"
namespace qlibc{

    /// Iterator Categories For Iterator Traits
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag {  };

    /// Base Type For Iterator
    template<typename _Category, typename _Tp, typename _Distance = qlibc::ptrdiff_t,
            typename _Pointer = _Tp*, typename _Reference = _Tp&>
    struct iterator{
        typedef _Category       iterator_category;
        typedef _Tp             value_type;
        typedef _Distance       difference_type;
        typedef _Pointer        pointer;
        typedef _Reference      reference;
    };

    /// Iterator Traits
    template<typename Iterator>
    struct __iterator_traits{
        typedef typename Iterator::iterator_category    iterator_category;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
    };

    /// Specialization for Iterator Traits
    /// Specialization for Raw Pointer
    template<typename _Tp>
    struct __iterator_traits<_Tp*>{
        typedef qlibc::random_access_iterator_tag   iterator_category;
        typedef _Tp                                 value_type;
        typedef _Tp*                                pointer;
        typedef _Tp&                                reference;
        typedef qlibc::ptrdiff_t                    difference_type;
    };
    /// Specialization for Const Raw Pointer
    template<typename _Tp>
    struct __iterator_traits<const _Tp*>{
        typedef qlibc::random_access_iterator_tag   iterator_category;
        typedef _Tp                                 value_type;
        typedef const _Tp*                          pointer;
        typedef const _Tp&                          reference;
        typedef qlibc::ptrdiff_t                    difference_type;
    };

    template<typename _Tp>
    using iterator_traits = __iterator_traits<_Tp>;
}

namespace __qlibc__{

    /// Help Function For Iterator
    template<typename _Iterator>
    inline QLIBC_CONSTEXPR typename qlibc::__iterator_traits<_Iterator>::iterator_category
    __iterator_category(const _Iterator&)
    { return typename qlibc::__iterator_traits<_Iterator>::iterator_category(); }

    /// This Helper Function is outside ISO C++ Standard
    template<typename _Iterator1, typename _Iterator2>
    inline QLIBC_CONSTEXPR bool
    __is_same_type_iterator(const _Iterator1&, const _Iterator2&){
        return qlibc::is_same<decltype(qlibc::iterator_traits<_Iterator1>::iterator_category),
                decltype(qlibc::iterator_traits<_Iterator2>::iterator_category)>();
    }
}

#endif
