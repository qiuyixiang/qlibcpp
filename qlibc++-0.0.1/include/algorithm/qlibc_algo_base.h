#ifndef QLIBC___0_0_1_QLIBC_ALGO_BASE_H
#define QLIBC___0_0_1_QLIBC_ALGO_BASE_H

#include <cstring> /// For Memory Management
#include <iostream>  /// For Debugger Information

#include "../extension/c++config.h"
#include "../iterator/qlibc_iterator_base.h"

namespace __qlibc__{
    /// Specialization of qlibc::copy

    /// All of these Version will call the Copy-Constructor of the object
    /// Random Access Iterator Version Using Distance As the Iteration Flag !
    template<typename _RandomAccessIterator, typename _OutIterator>
    inline _OutIterator __copy_distance(_RandomAccessIterator __first,_RandomAccessIterator __last,
                                        _OutIterator __result){
#if defined(QLIBC_DEBUG_INFO) && (QLIBC_DEBUG_INFO == 1)
        std::cout << "qlibc++ debugger info : \n";
        std::cout << "\tcopy version : Random-Access-Iterator Copy Using Difference Index\n";
#endif
        typedef typename qlibc::iterator_traits<_RandomAccessIterator>::difference_type _Dis_Type;
        for (_Dis_Type __diff = __last - __first; __diff != 0; --__diff, ++__first, ++__result)
            *__result = *__first;
        return __result;
    }
    /// Input Iterator Version, Often used for linked list and other Data Structure
    template<typename _InputIterator, typename _OutputIterator>
    inline _OutputIterator __copy_imp(_InputIterator __first, _InputIterator __last,
                                  _OutputIterator __result, qlibc::input_iterator_tag){
#if defined(QLIBC_DEBUG_INFO) && (QLIBC_DEBUG_INFO == 1)
        std::cout << "qlibc++ debugger info : \n";
        std::cout << "\tcopy version : Input-Iterator Copy Using Increment\n";
#endif
        for ( ; __first != __last; ++__first, ++__result)
            *__result = *__first;
        return __result;
    }
    template<typename _RandomAccessIterator, typename _OutputIterator>
    inline _OutputIterator __copy_imp(_RandomAccessIterator __first, _RandomAccessIterator __last,
                                  _OutputIterator __result, qlibc::random_access_iterator_tag){
        return __qlibc__::__copy_distance(__first, __last, __result);
    }
    /// Trivial Copy Assignment
    template<bool>
    struct __copy_pointer{
        template<typename _Tp>
        static inline _Tp* __copy(const _Tp* __first, const _Tp* __last, _Tp* __result) QLIBC_NOEXCEPT{
#if defined(QLIBC_DEBUG_INFO) && (QLIBC_DEBUG_INFO == 1)
            std::cout << "qlibc++ debugger info : \n";
            std::cout << "\tcopy version : Copy For Plain Pointer \n";
#endif
            memmove(static_cast<void*>(__result), static_cast<const void*>(__first),
                    sizeof(_Tp) * (__last - __first));
            return __result + (__last - __first);
        }
    };
    /// Non-Trivial Copy Assignment
    /// Even This Version Can't Directly Call memmove version, but it can used Random-Access-Iterator
    /// Version Copy
    template<>
    struct __copy_pointer<false>{
        template<typename _II, typename _OI>
        static inline _OI __copy(_II __first, _II __last, _OI __result){
            return __qlibc__::__copy_distance(__first, __last, __result);
        }
    };
    /// Iterator Version
    template<typename _II, typename _OI>
    struct __copy_dispatch{
        static inline _OI __copy(_II __first, _II __last, _OI __result){
            typedef typename qlibc::iterator_traits<_II>::iterator_category _Iter_type;
            return __copy_imp(__first, __last, __result, _Iter_type{ });
        }
    };
    template<typename _Tp>
    struct __copy_dispatch<_Tp*, _Tp*>{
        static inline _Tp* __copy(_Tp* __first, _Tp* __last, _Tp* __result){
            return __copy_pointer<_extern::__is_trivial_copy_assignemnt__<_Tp>::value>
                    ::__copy(__first, __last, __result);
        }
    };
    template<typename _Tp>
    struct __copy_dispatch<const _Tp*, _Tp*>{
        static inline _Tp* __copy(const _Tp* __first, const _Tp* __last, _Tp* __result){
            return __copy_pointer<_extern::__is_trivial_copy_assignemnt__<_Tp>::value>
            ::__copy(__first, __last, __result);
        }
    };
}
namespace qlibc{

    /// Base Algorithm
    /// Create on : 2024-06-04
    /// CopyRight : QIUYIXIANG

    /// fill()
    /// fill function will treat the memory range as initialized, if the _Tp type is an object
    /// it will automatically call the operator=
    template<typename _ForwardIterator, typename _Tp>
    inline void fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val){
        while ( __first != __last ){
            *__first = __val;
            ++__first;
        }
    }
    /// fill_n()
    template<typename _OutputIterator, typename _Size, typename _Tp>
    inline _OutputIterator fill_n(_OutputIterator __first, _Size __n, const _Tp& _value){
        for ( ; __n != 0; ++__first, --__n)
            *__first = _value;
        return __first;
    }
    /// max()
    template<typename _Tp>
    inline QLIBC_CONSTEXPR const _Tp& max(const _Tp& lhs, const _Tp& rhs){
        return lhs < rhs ? rhs : lhs;
    }
    template<typename _Tp, typename _Compare>
    inline QLIBC_CONSTEXPR const _Tp& max(const _Tp& lhs, const _Tp& rhs, _Compare compare){
        return compare(lhs, rhs) ? rhs : lhs;
    }
    /// min()
    template<typename _Tp>
    inline QLIBC_CONSTEXPR const _Tp& min(const _Tp& lhs, const _Tp& rhs){
        return rhs < lhs ? rhs : lhs;
    }
    template<typename _Tp, typename _Compare>
    inline QLIBC_CONSTEXPR const _Tp& min(const _Tp& lhs, const _Tp& rhs, _Compare compare){
        return compare(rhs, lhs) ? rhs : lhs;
    }
    /// equal()
    template<typename _InputIterator1, typename _InputIterator2>
    inline bool equal(_InputIterator1 __first, _InputIterator1 __last, _InputIterator2 __target){
        for ( ; __first != __last; ++__first, ++__target)
            if (*__first != *__target)
                return false;
        return true;
    }
    template<typename _InputIterator1, typename _InputIterator2, typename _Compare>
    inline bool equal(_InputIterator1 __first, _InputIterator1 __last,
                      _InputIterator2 __target, _Compare __compare_binary){
        for ( ; __first != __last; ++__first, ++__target)
            if (!__compare_binary(*__first, *__last))
                return false;
        return true;
    }
    /// swap()
    template<typename _Tp>
    inline void swap(_Tp& lhs, _Tp& rhs){
        _Tp __temp = qlibc::move(lhs);
        lhs = qlibc::move(rhs);
        rhs = qlibc::move(__temp);
    }
    /// copy()
    template<typename _II, typename _OI>
    inline _OI copy(_II __first, _II __last, _OI __result){
        return __qlibc__::__copy_dispatch<_II, _OI>::
                __copy(__first, __last, __result);
    }
    template<>
    inline char * copy(const char * __first, const char * __last, char * __result){
#if defined(QLIBC_DEBUG_INFO) && (QLIBC_DEBUG_INFO == 1)
        std::cout << "qlibc++ debugger info : \n";
        std::cout << "\tcopy version : Copy Specialization For char * \n";
#endif
        memmove(static_cast<void*>(__result), static_cast<const void*>(__first),
                (__last - __first));
        return __result + (__last - __first);
    }
    template<>
    inline wchar_t * copy(const wchar_t * __first, const wchar_t * __last, wchar_t * __result){
#if defined(QLIBC_DEBUG_INFO) && (QLIBC_DEBUG_INFO == 1)
        std::cout << "qlibc++ debugger info : \n";
        std::cout << "\tcopy version : Copy Specialization For wchar * \n";
#endif
        memmove(static_cast<void*>(__result), static_cast<const void*>(__first),
                (__last - __first) * sizeof(wchar_t));
        return __result + (__last - __first);
    }
}

#endif //QLIBC___0_0_1_QLIBC_ALGO_BASE_H
