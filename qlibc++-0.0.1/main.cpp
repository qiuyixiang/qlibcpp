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


/// Include For Test Cases
#include "test/test.h"

/// Include For qlibc++ Header File !
#include "include/utility.h"

/// Test Cases

/// Test For Utility

int main(int argc, char * argv[]) {

    RUN_ALL_TEST()

    return 0;
}
