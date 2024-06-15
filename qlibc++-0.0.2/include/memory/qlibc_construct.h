#ifndef QLIBC___0_0_2_QLIBC_CONSTRUCT_H
#define QLIBC___0_0_2_QLIBC_CONSTRUCT_H
#include "../utility/qlibc_move.h"
#include "../iterator/qlibc_iterator_base.h"
#include "../config.h"

/// Forward Declaration With NameSpace
namespace qlibc{
    template<typename _Tp>
    inline void Destroy(_Tp * __ptr);
}
namespace __qlibc__{

    template<bool Non_Trivial_Destructor>
    struct _Destroy_Aux{
        template<typename _ForwardIterator>
        QLIBC_STATIC void _Destroy(_ForwardIterator __first, _ForwardIterator __last){
            for (; __first != __last; ++__first)
                qlibc::Destroy(qlibc::address_of(*__first));
        }
    };
    template<>
    struct _Destroy_Aux<true>{
        template<typename _ForwardIterator>
        QLIBC_STATIC void _Destroy(_ForwardIterator, _ForwardIterator) { }
    };
}
namespace qlibc{
    /// construct
    template<typename _Tp, typename... _Args>
    inline void Construct(_Tp * __ptr, _Args&&... __args){
        ::new (static_cast<void*>(__ptr)) _Tp(qlibc::forward<decltype(__args)>(__args)...);
    }
    template<typename _Tp>
    inline void Construct(_Tp * __ptr){
        ::new (static_cast<void*>(__ptr)) _Tp;
    }

    template<typename _ForwardIterator, typename... _Args>
    inline void Construct_range(_ForwardIterator __first, _ForwardIterator __last, _Args&& ... __args){
        for ( ; __first != __last ; ++__first)
            Construct(qlibc::address_of(*__first), qlibc::forward<decltype(__args)>(__args)...);
    }
    /// destroy
    template<typename _Tp>
    inline void Destroy(_Tp * __ptr){
        __ptr->~_Tp();
    }
    template<typename _ForwardIterator>
    inline void Destroy(_ForwardIterator __first, _ForwardIterator __last){
        typedef typename qlibc::iterator_traits<_ForwardIterator>::value_type Value_Type;
        __qlibc__::_Destroy_Aux<qlibc::is_trivially_destructible<Value_Type>::value>
                ::_Destroy(__first, __last);
    }
}

#endif //QLIBC___0_0_2_QLIBC_CONSTRUCT_H
