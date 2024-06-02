#ifndef QLIBC___0_0_1_QLIBC_MOVE_H
#define QLIBC___0_0_1_QLIBC_MOVE_H

#include "../meta_programming/qlibc_type_traits.h"
namespace qlibc{

    /// move()
    template<typename _Tp>
    inline QLIBC_CONSTEXPR
    typename qlibc::remove_reference<_Tp>::type&& move(_Tp&& _arg) QLIBC_NOEXCEPT {
        return static_cast<typename qlibc::remove_reference<_Tp>::type&&>(_arg);
    }

    /// forward()
    /// The Specifier qlibc::remove_reference<_Tp>::type&& is used to lock reference type
    template<typename _Tp>
    inline QLIBC_CONSTEXPR _Tp&&
    forward(typename qlibc::remove_reference<_Tp>::type& _arg) QLIBC_NOEXCEPT{
        return static_cast<_Tp&&>(_arg);
    }
    template<typename _Tp>
    inline QLIBC_CONSTEXPR _Tp&&
    forward(typename qlibc::remove_reference<_Tp>::type&& _arg) QLIBC_NOEXCEPT{
        static_assert(!is_lvalue_reference<_Tp>::value, "qlibc::forward forward type error!");
        return static_cast<_Tp&&>(_arg);
    }
}

#endif //QLIBC___0_0_1_QLIBC_MOVE_H
