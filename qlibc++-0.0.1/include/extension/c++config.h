#ifndef QLIBC___0_0_1_C_CONFIG_H
#define QLIBC___0_0_1_C_CONFIG_H
#include <type_traits>

#define QLIBC_USED_STD  11

namespace qlibc{

/// Some Utility Function
#define QLIBC_NOEXCEPT      noexcept
#define QLIBC_CONSTEXPR     constexpr
#define QLIBC_EXPLICIT      explicit


    /// Type define For New-Used Type
    using size_t = unsigned long;
    using ptrdiff_t = long;
}

namespace _extern{
    /// Extern Dependencies from std::
    template <typename _Tp>
    using __is_trivial_destructible__ = std::is_trivially_destructible<_Tp>;

    template<typename _Tp, typename... _Args>
    using __is_nothrow_constructible__ = std::is_nothrow_constructible<_Tp, _Args...>;

    template<typename _Tp>
    using __is_nothrow_destructible__ = std::is_nothrow_destructible<_Tp>;
}

namespace _extern{

    template<typename _InputIterator>
    bool expect_range(_InputIterator __first, _InputIterator __last, _InputIterator __target){
        for ( ; __first != __last; ++__first, ++__target){
            if (*__first != *__target)
                return false;
        }
        return true;
    }
}
#endif //QLIBC___0_0_1_C_CONFIG_H
