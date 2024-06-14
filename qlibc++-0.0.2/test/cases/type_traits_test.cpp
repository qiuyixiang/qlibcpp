#include "../headers.h"

namespace type_traits_test{
    void base_type_traits(){
        qlibc::integral_constant<int, 10> integralConstant;
        EXPECT_EQUAL(integralConstant(), 10);
        EXPECT_EQUAL(integralConstant, 10);
        EXPECT_EQUAL(qlibc::true_type::value, std::true_type::value);
        EXPECT_EQUAL(qlibc::false_type::value, std::false_type::value);

        EXPECT((qlibc::is_same<decltype(qlibc::random_access_iterator_tag{}),
                qlibc::random_access_iterator_tag>::value));
        EXPECT(!(qlibc::is_same<int, double>::value));
        EXPECT((qlibc::is_same<typename qlibc::conditional<true, int, double>::type, int>::value));
        EXPECT((qlibc::is_same<typename qlibc::conditional<false, int, double>::type, double>::value));
    }
    void main_test(){
        type_traits_test::base_type_traits();
        std::cout << "Type Traits Library :\033[32m Passed\n\033[0m";
    }
}