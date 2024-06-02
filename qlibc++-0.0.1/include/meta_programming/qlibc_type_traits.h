#ifndef QLIBC___0_0_1_QLIBC_TYPE_TRAITS_H
#define QLIBC___0_0_1_QLIBC_TYPE_TRAITS_H

#include "../extension/c++config.h"
namespace qlibc{

    /// Base Type For C++ Type Traits
    template<typename _Tp, _Tp __v>
    struct integral_const;

    template<bool _B>
    using bool_constant = integral_const<bool, _B>;

    /// Type Define Specification for integral_const
    using true_type = integral_const<bool, true>;
    using false_type = integral_const<bool, false>;

    template<typename _Tp, _Tp __v>
    struct integral_const{
        static constexpr _Tp        value = __v;
        using value_type = _Tp;
        using type = integral_const<_Tp, __v>;
        /// Type Conversion
        /// All of the Operation of Member Operator will return value
        QLIBC_CONSTEXPR operator value_type() const QLIBC_NOEXCEPT { return value; };
        QLIBC_CONSTEXPR value_type operator()() const QLIBC_NOEXCEPT {
            return value;
        }
    };

    /// Type Relation

    /// is_same
    template<typename _Tp, typename _Up>
    struct is_same : public qlibc::false_type { };

    template<typename _Tp>
    struct is_same<_Tp, _Tp> : public qlibc::true_type  { };

    /// remove_reference
    template<typename _Tp>
    struct remove_reference{
        typedef _Tp type;
    };
    template<typename _Tp>
    struct remove_reference<_Tp&>{
        typedef _Tp type;
    };
    template<typename _Tp>
    struct remove_reference<_Tp&&>{
        typedef _Tp type;
    };

    template<typename _Tp>
    struct is_lvalue_reference : public false_type { };

    template<typename _Tp>
    struct is_lvalue_reference<_Tp&> : public true_type { };

    template<typename _Tp>
    struct is_rvalue_reference : public false_type { };

    template<typename _Tp>
    struct is_rvalue_reference<_Tp&&> : public true_type { };
}

#endif //QLIBC___0_0_1_QLIBC_TYPE_TRAITS_H
