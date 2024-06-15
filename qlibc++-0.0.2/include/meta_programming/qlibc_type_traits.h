#ifndef QLIBC___0_0_2_QLIBC_TYPE_TRAITS_H
#define QLIBC___0_0_2_QLIBC_TYPE_TRAITS_H

#include "../config.h"

namespace qlibc{

    /// Base Type For Type Traits
    template<typename _Tp, _Tp __v>
    struct integral_constant{
        static constexpr _Tp        value = __v;
        using value_type = _Tp;
        /// Cast To The Inner Type
        constexpr operator value_type() const QLIBC_NOTHROW;
        constexpr value_type operator()() const QLIBC_NOTHROW;
    };

    template<typename _Tp, _Tp __v>
    QLIBC_CONSTEXPR integral_constant<_Tp, __v>::operator value_type() const QLIBC_NOTHROW {
        return this->value;
    }
    template<typename _Tp, _Tp __v>
    QLIBC_CONSTEXPR typename integral_constant<_Tp, __v>::value_type
    integral_constant<_Tp, __v>::operator()() const noexcept {
        return this->value;
    }
    /// Alias For integral_constant
    template<bool Bool>
    using bool_constant = integral_constant<bool, Bool>;

    /// True Type And False Type
    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;

    /// Utility For Type Traits
    /// Is_Same
    template<typename _Tp, typename _Up>
    struct is_same : public false_type { };

    template<typename _Tp>
    struct is_same<_Tp, _Tp> : public true_type { };
    /// Conditional
    template<bool Bool, typename _True_Type, typename _False_Type>
    struct conditional {
        using type = _True_Type;
    };
    template<typename _True_Type, typename _False_Type>
    struct conditional<false, _True_Type, _False_Type>{
        using type = _False_Type;
    };
    template<bool Bool, typename _True_Type, typename _False_Type>
    using conditional_t = typename conditional<Bool, _True_Type, _False_Type>::type;

    /// Remove Reference
    template<typename _Tp>
    struct remove_reference {
        using type = _Tp;
    };
    template<typename _Tp>
    struct remove_reference<_Tp&>{
        using type = _Tp;
    };
    template<typename _Tp>
    struct remove_reference<_Tp&&>{
        using type = _Tp;
    };
}

#endif //QLIBC___0_0_2_QLIBC_TYPE_TRAITS_H
