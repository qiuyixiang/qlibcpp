#ifndef QLIBC___0_0_1__C_DEP_H
#define QLIBC___0_0_1__C_DEP_H

/// Container Dependencies

/// Create on : 2024-06-04
/// CopyRight : QIUYIXIANG
/// The Meaning of this File is Provide Support Header File
/// For All Of the qlibc container class
/// All of the Container header file only need to include this file !

#include "../extension/c++config.h"
#include "../iterator/qlibc_iterator_base.h"
#include "../memory/qlibc_construct.h"
#include "../memory/qlibc_allocator.h"
#include "../memory/qlibc_uninitialized.h"
#include "../utility/qlibc_move.h"

#include <initializer_list>
#include <iostream>

namespace __qlibc__{
    template<typename __NAME>
    using _initialized_list =  std::initializer_list<__NAME>;

/// These Macros Are Used To Replace std::IO By qlibc::IO In the Future
#define OSTREAM     std::ostream
#define STD_COUT    std::cout
#define STD_CERROR  std::cerr
}

#endif //QLIBC___0_0_1__C_DEP_H
