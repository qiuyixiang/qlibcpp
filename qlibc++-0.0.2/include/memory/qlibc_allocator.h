#ifndef QLIBC___0_0_2_QLIBC_ALLOCATOR_H
#define QLIBC___0_0_2_QLIBC_ALLOCATOR_H
#include "./qlibc_construct.h"
namespace qlibc{
    /// Standard Allocator
    template<typename _Tp>
    class allocator{
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
            using other = allocator<_Up>;
        };

        QLIBC_CONSTEXPR allocator() = default;
        allocator(const allocator& ) QLIBC_NOTHROW = default;
        allocator(allocator&& ) QLIBC_NOTHROW = default;
        template<typename _Up>
        allocator(const allocator<_Up>&) QLIBC_NOTHROW { };
        ~allocator() = default;

        pointer address(pointer __ptr) const QLIBC_NOTHROW;
        const_pointer address(const_pointer __ptr) const QLIBC_NOTHROW;
        pointer allocate(size_type __n) const;
        void deallocate(pointer __ptr) const;
        size_type max_size() const QLIBC_NOTHROW;

        template<typename _Up, typename... _Args>
        void construct(_Up* __ptr, _Args&&...__args) const;
        void destroy(pointer __ptr) const;
    };
    template<typename _Tp>
    typename allocator<_Tp>::size_type allocator<_Tp>::max_size() const QLIBC_NOTHROW {
        return static_cast<size_type>(size_type(-1) / sizeof(_Tp));
    }
    template<typename _Tp>
    void allocator<_Tp>::destroy(allocator::pointer __ptr) const {
        qlibc::Destroy(__ptr);
    }
    template<typename _Tp>
    template<typename _Up, typename... _Args>
    void allocator<_Tp>::construct(_Up *__ptr, _Args &&... __args) const {
        qlibc::Construct(__ptr, qlibc::forward<decltype(__args)>(__args)...);
    }
    template<typename _Tp>
    void allocator<_Tp>::deallocate(allocator::pointer __ptr) const {
        if (!__ptr)
            free(static_cast<void*>(__ptr));
    }
    template<typename _Tp>
    typename allocator<_Tp>::pointer allocator<_Tp>::allocate(allocator::size_type __n) const {
        if (__n > this->max_size())
            throw std::bad_alloc{ };
        auto __result = static_cast<pointer>(malloc(__n * sizeof(_Tp)));
        if (!__result)
            throw std::bad_alloc{ };
        return __result;
    }
    template<typename _Tp>
    typename allocator<_Tp>::const_pointer allocator<_Tp>::address(allocator::const_pointer __ptr) const QLIBC_NOTHROW {
        return qlibc::address_of(*__ptr);
    }
    template<typename _Tp>
    typename allocator<_Tp>::pointer allocator<_Tp>::address(allocator::pointer __ptr) const QLIBC_NOTHROW {
        return qlibc::address_of(*__ptr);
    }
    template<typename _Tp>
    inline QLIBC_CONSTEXPR bool operator==(const allocator<_Tp>&, const allocator<_Tp>&){
        return true;
    }
    template<typename _Tp>
    inline QLIBC_CONSTEXPR bool operator!=(const allocator<_Tp>&, const allocator<_Tp>&){
        return false;
    }
    template<typename _Tp, typename _Up>
    inline QLIBC_CONSTEXPR bool operator==(const allocator<_Tp>&, const allocator<_Up>&){
        return true;
    }
    template<typename _Tp, typename _Up>
    inline QLIBC_CONSTEXPR bool operator!=(const allocator<_Tp>&, const allocator<_Up>&){
        return false;
    }
    template<typename _Allocator>
    class allocator_traits{
    public:
        using allocator_type = _Allocator;
        using value_type = typename _Allocator::value_type;
        using pointer = typename _Allocator::pointer;
        using const_pointer = typename _Allocator::const_pointer;
        using void_pointer = void *;
        using const_void_pointer = const void*;
        using difference_type = typename _Allocator::difference_type;
        using size_type = typename _Allocator::size_type;

        template<typename _Up>
        using rebind_allocator_type = typename _Allocator::template rebind<_Up>::other;

        QLIBC_STATIC pointer  allocate(_Allocator& __allocator, size_type __n);
        QLIBC_STATIC void deallocate(_Allocator& __allocator, pointer __ptr);
        template<typename _Up, typename... _Args>
        QLIBC_STATIC void construct(_Allocator& __allocator, _Up* __ptr, _Args&&... __args);
        QLIBC_STATIC void destroy(_Allocator& __allocator, pointer __ptr);
        QLIBC_CONSTEXPR QLIBC_STATIC size_type max_size(_Allocator& __allocator);
    };
    template<typename _Allocator>
    QLIBC_CONSTEXPR typename allocator_traits<_Allocator>::size_type
    allocator_traits<_Allocator>::max_size(_Allocator &__allocator) {
        return __allocator.max_size();
    }
    template<typename _Allocator>
    void allocator_traits<_Allocator>::destroy(_Allocator &__allocator, pointer __ptr) {
        __allocator.destroy(__ptr);
    }
    template<typename _Allocator>
    template<typename _Up, typename... _Args>
    void allocator_traits<_Allocator>::construct(_Allocator &__allocator, _Up *__ptr, _Args &&... __args) {
        __allocator.construct(__ptr, qlibc::forward<decltype(__args)>(__args)...);
    }
    template<typename _Allocator>
    void allocator_traits<_Allocator>::deallocate(_Allocator &__allocator, pointer __ptr) {
        __allocator.deallocate(__ptr);
    }
    template<typename _Allocator>
    typename allocator_traits<_Allocator>::pointer
    allocator_traits<_Allocator>::allocate(_Allocator &__allocator, size_type __n) {
        return __allocator.allocate(__n);
    }
}
#endif //QLIBC___0_0_2_QLIBC_ALLOCATOR_H
