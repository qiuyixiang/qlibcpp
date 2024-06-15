#ifndef QLIBC___0_0_2_CONFIG_H
#define QLIBC___0_0_2_CONFIG_H

/// Extern Dependent Header Files
#include <type_traits>
#include <iostream>
#include <cstdlib>

#define QLIBC_CONSTEXPR constexpr
#define QLIBC_THROW     throw
#define QLIBC_STATIC    static
#define QLIBC_NOTHROW   noexcept


namespace qlibc{
    /// Type Define For qlibc
    typedef unsigned long   size_t;
    typedef signed long     ptrdiff_t;

    /// Dependencies
    template<typename _Tp>
    using is_trivially_destructible = std::is_trivially_destructible<_Tp>;
}

#endif //QLIBC___0_0_2_CONFIG_H
