/**
 * This File is The Main Entry Test File For qlibc++ 0.0.2
 *
 * This Project Is A Simple Implementation of C++ Standard Library
 * Confirm ISO/ANSI C++ 11
 * Create On 2024-06-14
 * Copyright: @QIUYIXIANG
 * You Can Edit or Change Any Files In This Project
 *
 *
 * qlibc Version 0.0.2
 * Formal Version
 * The Directory <Include> Include All Needed Header File And Their Implementations
 * The Directory <Test> Include All Test Cases For qlibc++ 0.0.2
 * This File Is Only Used For Test Purpose
 *
 * NameSpace : qlibc Formal namespace For All Public Interfaces
 *             __qlibc__ Only used For Inner Implementation
 */

/// Only Need Include This Header File !
#include "test/test.h"

int main(int argc, char * argv[]){
    /// The Button For Choose The Test Cases
    /// Always Run All Test Cases
    RUN_TEST(Test_Choice::ALL_TEST);
}
