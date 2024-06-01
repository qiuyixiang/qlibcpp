#ifndef QLIBC___0_0_1_QLIBC_ALLOCATOR_H
#define QLIBC___0_0_1_QLIBC_ALLOCATOR_H

#include "../extension/c++config.h"
namespace __qlibc__{

    template<typename _Tp>
    class __allocator{
        /// Type Define For Allocator
    public:
        typedef _Tp                 value_type;
        typedef _Tp*                pointer;
        typedef const _Tp*          const_pointer;
        typedef _Tp&                reference;
        typedef const _Tp&          const_reference;
        typedef qlibc::size_t       size_type;
        typedef qlibc::ptrdiff_t    difference_type;

        template<typename _Up>
        struct rebind{
            typedef __allocator<_Up> other;
        };
    };
}
namespace qlibc{

    template<typename _Tp>
    using allocator = __qlibc__::__allocator<_Tp>;
}
#endif //QLIBC___0_0_1_QLIBC_ALLOCATOR_H
