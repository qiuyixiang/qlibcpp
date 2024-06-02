#ifndef QLIBC___0_0_1_QLIBC_ALLOCATOR_H
#define QLIBC___0_0_1_QLIBC_ALLOCATOR_H

#include "../extension/c++config.h"
#include "./qlibc_construct.h"
namespace __qlibc__{

    template<typename _Tp>
    class __allocator;

    template<typename _Tp>
    inline QLIBC_CONSTEXPR bool
    operator==(const __allocator<_Tp>&, const __allocator<_Tp>&) QLIBC_NOEXCEPT;

    template<typename _Tp>
    inline QLIBC_CONSTEXPR bool
    operator != (const __allocator<_Tp>&, const __allocator<_Tp>&) QLIBC_NOEXCEPT;

    template<typename _Tp>
    class __allocator{
        template<typename _Tp1>
        friend inline QLIBC_CONSTEXPR bool
        operator==(const __allocator<_Tp1>&, const __allocator<_Tp1>&) QLIBC_NOEXCEPT;

        template<typename _Tp1>
        friend inline QLIBC_CONSTEXPR bool
        operator != (const __allocator<_Tp1>&, const __allocator<_Tp1>&) QLIBC_NOEXCEPT;
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
    public:
        QLIBC_CONSTEXPR __allocator() QLIBC_NOEXCEPT = default;
        ~__allocator() QLIBC_NOEXCEPT = default;

        __allocator(const __allocator& ) QLIBC_NOEXCEPT = default;

    public:
        pointer allocate(size_type __n);
        void deallocate(pointer __ptr);

        template<typename _Up, typename... _Args>
        void construct(_Up* __ptr, _Args&&... __args)
        QLIBC_NOEXCEPT(_extern::__is_nothrow_constructible__<_Up, _Args...>::value);

        void destroy(pointer __ptr)
        QLIBC_NOEXCEPT(_extern::__is_nothrow_destructible__<_Tp>::value);

        template<typename _ForwardIterator>
        void destroy(_ForwardIterator __first, _ForwardIterator __last)
        QLIBC_NOEXCEPT(_extern::__is_nothrow_destructible__
                <typename qlibc::iterator_traits<_ForwardIterator>::value_type>::value);

        pointer address(reference _ref) const QLIBC_NOEXCEPT;
        const_pointer address(const_reference _ref) const QLIBC_NOEXCEPT;
        QLIBC_CONSTEXPR size_type max_size() const QLIBC_NOEXCEPT;
    };

    template<typename _Tp>
    inline QLIBC_CONSTEXPR bool
    operator==(const __allocator<_Tp>&, const __allocator<_Tp>&) QLIBC_NOEXCEPT
    {   return true;    }

    template<typename _Tp>
    inline QLIBC_CONSTEXPR bool
    operator != (const __allocator<_Tp>&, const __allocator<_Tp>&) QLIBC_NOEXCEPT
    {   return false;   }

    /// Using C Memory Management Function Directly
    template<typename _Tp>
    typename __allocator<_Tp>::pointer
    __allocator<_Tp>::allocate(size_type __n) {
        if (__n > this->max_size())
            throw std::bad_alloc{ };
        auto __res_ptr = static_cast<pointer>(malloc(__n * sizeof(value_type)));
        if (!__res_ptr)
            throw std::bad_alloc{ };
        return __res_ptr;
    }
    template<typename _Tp>
    void __allocator<_Tp>::deallocate(pointer __ptr) {
        if (!__ptr)
            free(static_cast<void*>(__ptr));
    }
    template<typename _Tp>
    template<typename _Up, typename ..._Args>
    void __allocator<_Tp>::construct(_Up *__ptr, _Args&&...__args)
    noexcept(_extern::__is_nothrow_constructible__<_Up, _Args...>::value) {
        ::new (static_cast<void*>(__ptr)) _Up(qlibc::forward<decltype(__args)>(__args)...);
    }
    template<typename _Tp>
    void __allocator<_Tp>::destroy(pointer __ptr)
    noexcept(_extern::__is_nothrow_destructible__<_Tp>::value) {
        __ptr-> ~_Tp();
    }
    template<typename _Tp>
    template<typename _ForwardIterator>
    void __allocator<_Tp>::destroy(_ForwardIterator __first, _ForwardIterator __last)
    noexcept(_extern::__is_nothrow_destructible__
            <typename qlibc::iterator_traits<_ForwardIterator>::value_type>::value) {
        __qlibc__::_Destroy(__first, __last);
    }

    template<typename _Tp>
    typename __allocator<_Tp>::pointer
    __allocator<_Tp>::address(reference _ref) const QLIBC_NOEXCEPT {
        return static_cast<pointer>(&_ref);
    }
    template<typename _Tp>
    typename __allocator<_Tp>::const_pointer
    __allocator<_Tp>::address(const_reference _ref) const QLIBC_NOEXCEPT {
        return static_cast<const_pointer>(&_ref);
    }

    template<typename _Tp>
    QLIBC_CONSTEXPR typename __allocator<_Tp>::size_type
    __allocator<_Tp>::max_size() const QLIBC_NOEXCEPT {
        return size_type(-1) / sizeof(_Tp);
    }
}
namespace qlibc{

    template<typename _Tp>
    using allocator = __qlibc__::__allocator<_Tp>;
}
#endif //QLIBC___0_0_1_QLIBC_ALLOCATOR_H
