/// qlibc++ Standard C++ Template Library
/// This File was used to test for version for qlibc++ 0.0.1 originally

/// The qlibc++ Library is implemented using only header files
/// in the /include directory, it will include all the header files in the qlibc
/// in the /test directory, the only purpose for this directory is just for test cases
/// When Compile your own application just using the header file and using the double quote notation

/// Name Convention:
/// the Header file macro  : QLIBC_XX Mainly Used for Interface Header Files
/// the Header file macro : __QLIBC_XX Mainly Used for Inner Implementation Header Files


/// Namespace : qlibc:: is used to distinguish between C++ GNU For ISO/ANSI C++ Version
///             __qlibc__:: is not suggested for user, its just some complex implementation details

/// Main test Entrance For qlibc++
/// Test For The All Cases of the qlibc++ Standard C++ Template Library

/// Project Create on : 2024-05-08
/// Copyright : @QiuYiXiang (All Rights Reversed)

/// Include For GNU glibc++ (For Compare)
#include <iostream>
#include <type_traits>
#include <iterator>
#include <queue>

/// Include For Test Cases
#include "test/test.h"

/// Include For qlibc++ Header File !
#include "include/utility.h"
#include "include/iterator.h"
#include "include/type_traits.h"

///########### Test Case For Meta-Programming ###################
/// Test Case For Type Traits
TEST_CASE(type_traits){
    EXPECT((std::is_same<int, int>::value));
    EXPECT_EQUAL((qlibc::is_same<int, int>::value), true);
    EXPECT_EQUAL((qlibc::is_same<int, double>::value), false);
    EXPECT_EQUAL((qlibc::is_same<int, double>()), false);
    EXPECT_EQUAL((qlibc::is_same<int*, double*>()), false);
}
///########### Test Case For Iterator ###################
/// Test Case For Base Iterator
TEST_CASE(iterator){
    /// Test For Iterator Traits And Iterator Basics
    int * int_ptr = nullptr;
    double * double_ptr = nullptr;
    auto Iter_type = __qlibc__::__iterator_category(int_ptr);
    EXPECT((std::is_same<qlibc::random_access_iterator_tag(), qlibc::random_access_iterator_tag()>::value));
    EXPECT_EQUAL((std::is_same<qlibc::random_access_iterator_tag, decltype(Iter_type)>::value), true);
    EXPECT_EQUAL(__qlibc__::__is_same_iterator_category(int_ptr, double_ptr), true);
    EXPECT_EQUAL((qlibc::is_same<qlibc::random_access_iterator_tag, decltype(int_ptr)>()), false);
    EXPECT_EQUAL((qlibc::is_same<qlibc::random_access_iterator_tag,
            decltype(qlibc::iterator_traits<decltype(int_ptr)>::iterator_category())>()), true);
    /// Test For Iterator Function
    int iter_group[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    decltype(&iter_group[0]) first_one = &iter_group[0];
    qlibc::advance(first_one, 2);
    EXPECT_EQUAL(*first_one, iter_group[2]);
    qlibc::advance(first_one, -1);
    EXPECT_EQUAL(*first_one, iter_group[1]);
    auto next_one = qlibc::next(first_one);
    EXPECT_EQUAL(*next_one, iter_group[2]);
    EXPECT_EQUAL(*(qlibc::prev(next_one)), iter_group[1]);
    EXPECT_EQUAL(*qlibc::prev((qlibc::prev(next_one))), iter_group[0]);

    EXPECT_EQUAL(qlibc::distance(&iter_group[0], qlibc::next(&iter_group[0], 3)), 3);
    EXPECT_EQUAL(qlibc::distance(&iter_group[0], &iter_group[0]), 0);

    unsigned long D1 = 100;
    unsigned long D2 = 200;
    qlibc::iter_swap(&D1, &D2);
    EXPECT_EQUAL(D1, 200);
    EXPECT_EQUAL(D2, 100);
    /// Test For Iterator Adaptor
}
///########### Test Case For Memory ###################
TEST_CASE(memory){
    std::allocator<>
}
int main(int argc, char * argv[]) {
    /// Run All Test Cases
    RUN_ALL_TEST()
    return 0;
}
