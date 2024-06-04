#ifndef QLIBC___0_0_1_QLIBC_UNINITIALIZED_H
#define QLIBC___0_0_1_QLIBC_UNINITIALIZED_H

#include "../algorithm/qlibc_algo_base.h"
#include "./qlibc_construct.h"
namespace __qlibc__{
    template<bool TrivialValue>
    struct __uninitialized_fill_n{
        template<typename _ForwardIterator, typename _Size, typename _Tp>
        static _ForwardIterator _do_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __val){
            return qlibc::fill_n(__first, __n, __val);
        }
    };
    template<>
    struct __uninitialized_fill_n<false>{
        template<typename _ForwardIterator, typename _Size, typename _Tp>
        static _ForwardIterator _do_fill_n(_ForwardIterator __first, _Size __n, const _Tp& __val){
            auto __current = __first;
            try {
                for ( ; __n != 0; --__n, ++__current){
                    __qlibc__::_Construct(&(*__current), __val);
                }
                return __current;
            } catch (QLIBC_ALL_EXCEPTION) {
                __qlibc__::_Destroy(__first, __current);
                QLIBC_THROW_EXCEPTION_AGAIN;
            }
        }
    };
    template<bool Trivial_Value>
    struct __uninitialized_copy{
        template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator _do_copy(_InputIterator __first, _InputIterator __last,_ForwardIterator __result){
            return qlibc::copy(__first, __last, __result);
        }
    };
    template<>
    struct __uninitialized_copy<false>{
        template<typename _InputIterator, typename _ForwardIterator>
        static _ForwardIterator _do_copy(_InputIterator __first, _InputIterator __last,_ForwardIterator __result){
            auto __current = __first;
            try{
                for ( ; __current != __last; ++__current, ++__result){
                    __qlibc__::_Construct(&(*__result), *__current);
                }
                return __current;
            }catch (QLIBC_ALL_EXCEPTION){
                __qlibc__::_Destroy(__first, __current);
                QLIBC_THROW_EXCEPTION_AGAIN;
            }
        }
    };
    template<bool Trivial_Value>
    struct __uninitialized_fill{
        template<typename _ForwardIterator, typename _Tp>
        static void _do_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val){
            qlibc::fill(__first, __last, __val);
        }
    };
    template<>
    struct __uninitialized_fill<false>{
        template<typename _ForwardIterator, typename _Tp>
        static void _do_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val){
            auto __current = __first;
            try{
                for ( ; __current != __last; ++__current)
                    __qlibc__::_Construct(&(*__current), __val);
                return __current;
            }catch (QLIBC_ALL_EXCEPTION){
                __qlibc__::_Destroy(__first, __current);
                QLIBC_THROW_EXCEPTION_AGAIN;
            }
        }
    };
}
namespace qlibc{
    /// uninitialized_fill_n
    template<typename _ForwardIterator, typename _Size, typename _Tp>
    inline _ForwardIterator uninitialized_fill_n
        (_ForwardIterator __first, _Size __n, const _Tp& __val){
        return __qlibc__::__uninitialized_fill_n<_extern::__is_pod_type__
                <typename qlibc::iterator_traits<_ForwardIterator>::value_type>::value>
                ::_do_fill_n(__first, __n, __val);
    }
    /// uninitialized_fill
    template<typename _ForwardIterator, typename _Tp>
    inline void uninitialized_fill(_ForwardIterator __first, _ForwardIterator __last, const _Tp& __val){
        __qlibc__::__uninitialized_fill<_extern::__is_pod_type__
                <typename qlibc::iterator_traits<_ForwardIterator>::value_type>::value>
                ::_do_fill(__first, __last, __val);
    }
    /// uninitialized_copy
    template<typename _InputIterator, typename _ForwardIterator>
    inline _ForwardIterator uninitialized_copy
    (_InputIterator __first, _InputIterator __last,_ForwardIterator __result){
        return __qlibc__::__uninitialized_copy<_extern::__is_pod_type__
                <typename qlibc::iterator_traits<_InputIterator>::value_type>::value>
                ::_do_copy(__first, __last, __result);
    }
    /// uninitialized_copy_n
    template<typename _InputIterator, typename _ForwardIterator, typename _Size>
    inline _ForwardIterator uninitialized_copy_n(_InputIterator __first, _Size __n, _ForwardIterator __result){
        return qlibc::uninitialized_copy(__first, __first + __n, __result);
    }
}

#endif //QLIBC___0_0_1_QLIBC_UNINITIALIZED_H
