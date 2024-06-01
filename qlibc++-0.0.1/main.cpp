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
    int * int_ptr = nullptr;
    auto Iter_type = __qlibc__::__iterator_category(int_ptr);
    EXPECT((std::is_same<qlibc::random_access_iterator_tag(), qlibc::random_access_iterator_tag()>::value));
    EXPECT((std::is_same<qlibc::random_access_iterator_tag, decltype(Iter_type)>::value));

}

int main(int argc, char * argv[]) {

    RUN_ALL_TEST()

    return 0;
}
