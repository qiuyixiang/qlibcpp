#ifndef __QLIBCPP_TEST_MAIN__
#define __QLIBCPP_TEST_MAIN__ 1

/**
 * This Header File Defined Some Interface For Test Cases
 */
#include <cassert>
#include <iostream>
#define __USING_QLIBCPP_TEST_MACRO__  1

#if defined(__USING_QLIBCPP_TEST_MACRO__) && __USING_QLIBCPP_TEST_MACRO__ == 1
#define MAXI_TEST_CASES         256
    typedef void (*__test_func_ptr)();
    static __test_func_ptr __test_cases_group[MAXI_TEST_CASES] { };
    static unsigned long __test_counter = 0;
#endif

/// Test Macro
#define EXPECT_EQUAL(_expr1, _expr2)    assert(((_expr1) == (_expr2)))
#define EXPECT(_)                       assert((_))

#define _MACRO_JOIN(_X, _Y) _X##_Y
#define _MACRO_TO_STR(__) #__

#define TEST_CASE(_)                                                \
void _MACRO_JOIN(fqlibcpp, _)();                                     \
__attribute__((constructor)) void _MACRO_JOIN(constructor, _)(){    \
    __test_cases_group[__test_counter++] =                          \
    static_cast<__test_func_ptr>(&_MACRO_JOIN(fqlibcpp, _));         \
}                                                                   \
void _MACRO_JOIN(fqlibcpp, _)()

#define RUN_ALL_TEST()                                                          \
   for (unsigned long __index = 0; __index != __test_counter; ++__index)        \
        (*(__test_cases_group[__index]))();                                     \
   std::cout<<"Passed Total : "<<__test_counter << " / "                        \
   << __test_counter <<"  Test Cases !!"<<std::endl;


#endif
