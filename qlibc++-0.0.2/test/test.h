#ifndef QLIBC___0_0_2_TEST_H
#define QLIBC___0_0_2_TEST_H

#include "cases/iterator_test.cpp"
#include "cases/type_traits_test.cpp"
#include "cases/utility_test.cpp"
#include "cases/algorithm_test.cpp"
#include "cases/memory_test.cpp"
#include "cases/container_test.cpp"

#include <cstdlib>

enum Test_Choice{
    ALL_TEST,
    ITERATOR_TEST,
    TYPE_TRAITS_TEST,
    UTILITY_TEST,
    ALGORITHM_TEST,
    MEMORY_TEST,
    CONTAINER_TEST,
};
void RUN_TEST(Test_Choice choice){
    switch (choice) {
        case ALL_TEST : {
            iterator_test::main_test();
            type_traits_test::main_test();
            utility_test::main_test();
            algorithm_test::main_test();
            memory_test::main_test();
            container_test::main_test();
            break;
        }
        case ITERATOR_TEST:
            iterator_test::main_test();
            break;
        case TYPE_TRAITS_TEST:
            type_traits_test::main_test();
            break;
        case UTILITY_TEST:
            utility_test::main_test();
            break;
        case ALGORITHM_TEST:
            algorithm_test::main_test();
            break;
        case MEMORY_TEST:
            memory_test::main_test();
            break;
        case CONTAINER_TEST:
            container_test::main_test();
            break;
        default:
            exit(-1);
    }
}
#endif //QLIBC___0_0_2_TEST_H
