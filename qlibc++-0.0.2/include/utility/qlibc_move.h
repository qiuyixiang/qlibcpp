#ifndef QLIBC___0_0_2_QLIBC_MOVE_H
#define QLIBC___0_0_2_QLIBC_MOVE_H
#include "../type_traits.h"
namespace qlibc{

    /// Move
    template<typename _Tp>
    inline QLIBC_CONSTEXPR typename qlibc::remove_reference<_Tp>::type&& move(_Tp&& __t) QLIBC_NOTHROW{
        return static_cast<typename qlibc::remove_reference<_Tp>::type&&>(__t);
    }
    /// Address of
    template<typename _Tp>
    inline QLIBC_CONSTEXPR _Tp* address_of(_Tp& __t) QLIBC_NOTHROW{
        return static_cast<_Tp*>(&__t);
    }
    /// Forward
    template<typename _Tp>
    inline QLIBC_CONSTEXPR _Tp&& forward(typename qlibc::remove_reference<_Tp>::type& __t) QLIBC_NOTHROW{
        return static_cast<_Tp&&>(__t);
    }
    template<typename _Tp>
    inline QLIBC_CONSTEXPR _Tp&& forward(typename qlibc::remove_reference<_Tp>::type&& __t) QLIBC_NOTHROW{
        return static_cast<_Tp&&>(__t);
    }
}

#endif //QLIBC___0_0_2_QLIBC_MOVE_H
