#ifndef QLIBC___0_0_2_TEST_H
#define QLIBC___0_0_2_TEST_H

#include "cases/iterator_test.cpp"
#include "cases/type_traits_test.cpp"

#include <cstdlib>

enum Test_Choice{
    ALL_TEST,
    ITERATOR_TEST,
    TYPE_TRAITS_TEST
};

void RUN_TEST(Test_Choice choice){
    switch (choice) {
        case ALL_TEST : {
            iterator_test::main_test();
            type_traits_test::main_test();
            break;
        }
        case ITERATOR_TEST:
            iterator_test::main_test();
            break;
        case TYPE_TRAITS_TEST:
            type_traits_test::main_test();
            break;
        default:
            exit(-1);
    }
}
#endif //QLIBC___0_0_2_TEST_H
