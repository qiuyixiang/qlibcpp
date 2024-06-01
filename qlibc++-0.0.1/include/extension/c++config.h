#ifndef QLIBC___0_0_1_C_CONFIG_H
#define QLIBC___0_0_1_C_CONFIG_H

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

#endif //QLIBC___0_0_1_C_CONFIG_H
