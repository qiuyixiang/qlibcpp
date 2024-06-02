#ifndef QLIBC___0_0_1_QLIBC_CONSTRUCT_H
#define QLIBC___0_0_1_QLIBC_CONSTRUCT_H

#include "../utility/qlibc_move.h"
#include "../extension/c++config.h"
#include "../iterator/qlibc_iterator_base.h"

namespace __qlibc__{
    /// These Functions Are Auxiliary Functions
    /// Not Belong bo ISO/ANSI C++

    template<typename _Tp, typename... _Args>
    inline _Tp* _Construct(_Tp* __pointer, _Args&&... __args){
        return ::new (static_cast<void*>(__pointer))
        _Tp(qlibc::forward<decltype(__args)>(__args)...);
    }
    template<typename _Tp>
    inline _Tp* _Construct(_Tp * __pointer){
        return ::new (static_cast<void*>(__pointer)) _Tp();
    }
    template<typename _Tp>
    inline void _Destroy(_Tp* __pointer){
        /// Call Destructor of the Object through the pointer
        __pointer->~_Tp();
    }
    template<bool>
    struct _Destroy_Aux{
        template<typename _ForwardIterator>
        static inline void __destroy(_ForwardIterator __first, _ForwardIterator __last){
            for ( ; __first != __last; ++__first)
                _Destroy(&(*__first));
        }
    };
    template<>
    struct _Destroy_Aux<true>{
        template<typename _ForwardIterator>
        static inline void __destroy(_ForwardIterator, _ForwardIterator) { }
    };
    /// Destroy the Range
    template<typename _ForwardIterator>
    inline void _Destroy(_ForwardIterator _first, _ForwardIterator _last){
        typedef typename qlibc::iterator_traits<_ForwardIterator>::value_type _Val_Type;
        _Destroy_Aux<_extern::__is_trivial_destructible__<_Val_Type>::value>
                ::__destroy(_first, _last);
    }
}
#endif //QLIBC___0_0_1_QLIBC_CONSTRUCT_H
