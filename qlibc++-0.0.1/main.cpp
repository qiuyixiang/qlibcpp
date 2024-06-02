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
#include <new>
#include <queue>
#include <memory>

/// Include For Test Cases
#include "test/test.h"

/// Include For qlibc++ Header File !
#include "include/utility.h"
#include "include/iterator.h"
#include "include/type_traits.h"
#include "include/memory.h"

///########### Test Case For Meta-Programming ###################
/// Test Case For Type Traits
class type_traits_non_trivial_class{
    QLIBC_CONSTEXPR type_traits_non_trivial_class() = default;
    ~type_traits_non_trivial_class() = default;
};
TEST_CASE(type_traits){
    EXPECT((std::is_same<int, int>::value));
    EXPECT_EQUAL((qlibc::is_same<int, int>::value), true);
    EXPECT_EQUAL((qlibc::is_same<int, double>::value), false);
    EXPECT_EQUAL((qlibc::is_same<int, double>()), false);
    EXPECT_EQUAL((qlibc::is_same<int*, double*>()), false);

    int val = 10;
    int &val_reference = val;
    EXPECT_EQUAL((qlibc::is_same<decltype(val), decltype(val_reference)>::value), false);
    EXPECT_EQUAL((qlibc::is_same<decltype(val),
            decltype(qlibc::remove_reference<decltype(val_reference)>::type())>::value), true);

    EXPECT(std::is_trivially_destructible<int>::value);
    EXPECT(std::is_trivially_destructible<double>::value);
    EXPECT(!std::is_trivially_destructible<type_traits_non_trivial_class>::value);

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
class memory_test_class_delete_complete{
public:
    static unsigned long __destroy_counter;
    static unsigned long __construct_counter;
    memory_test_class_delete_complete()
    { ++(memory_test_class_delete_complete::__construct_counter); }
    ~memory_test_class_delete_complete()
    { ++(memory_test_class_delete_complete::__destroy_counter); }
};
unsigned long memory_test_class_delete_complete::__destroy_counter = 0;
unsigned long memory_test_class_delete_complete::__construct_counter = 0;
TEST_CASE(memory){
    auto ptr_int = new int;
    __qlibc__::_Construct(ptr_int, 10);
    EXPECT_EQUAL(*ptr_int, 10);
    __qlibc__::_Destroy(ptr_int);
    delete ptr_int;

    double PI = 3.1415926;
    qlibc::allocator<double> allocator_double;
    std::allocator<double> allocator_std_double;
    /// std::cout << allocator_double.max_size()<< "\n";
    EXPECT_EQUAL(allocator_double.address(PI), allocator_std_double.address(PI));

    qlibc::allocator<int> allocator_INT;
    auto _INT_res = allocator_INT.allocate(10);
    auto _INT_copy = _INT_res;
    int group_integer[] = {1,2,3,4,5,7,8,9,10};

    for (int index = 0; index != 10; ++index, ++_INT_copy)
        allocator_INT.construct(_INT_copy, group_integer[index]);
    EXPECT(_extern::expect_range(_INT_res, _INT_res + 10, &group_integer[0]));
    allocator_INT.destroy(_INT_res, _INT_res + 10);
    allocator_INT.deallocate(_INT_res);

    qlibc::allocator<memory_test_class_delete_complete> allocator_class;
    auto class_ptr = allocator_class.allocate(10);
    for (int counter = 0; counter != 10; ++counter)
        allocator_class.construct(class_ptr + counter);
    EXPECT_EQUAL(memory_test_class_delete_complete::__construct_counter, 10);
    allocator_class.destroy(class_ptr, class_ptr + 10);
    EXPECT_EQUAL(memory_test_class_delete_complete::__destroy_counter, 10);
    allocator_class.deallocate(class_ptr);
}

///########### Test Case For Utility ###################
class utility_test_for_rhs{
public:
    QLIBC_CONSTEXPR utility_test_for_rhs() = default;
    ~utility_test_for_rhs() = default;
    utility_test_for_rhs(const utility_test_for_rhs&, bool& flags)
    { flags = false; }
    utility_test_for_rhs(utility_test_for_rhs&&, bool & flags) QLIBC_NOEXCEPT
    { flags = true; }
};
class utility_perfect_forward{
public:
    QLIBC_CONSTEXPR utility_perfect_forward() = default;
    static bool _forwarder(int&)
    { return false; }
    static bool _forwarder(int&&)
    {  return true; }
    static bool _l_val_reference(int && val)
    { return _forwarder(qlibc::forward<decltype(val)>(val)); }
};
TEST_CASE(utility){
    int val = 100;
    int& l_val_reference = val;

    EXPECT_EQUAL((qlibc::is_same<int&&, decltype(qlibc::move(l_val_reference))>::value), true);
    EXPECT_EQUAL((qlibc::is_same<decltype(qlibc::move(val)),
            decltype(qlibc::move(l_val_reference))>::value), true);
    EXPECT((qlibc::is_same<decltype(qlibc::move(l_val_reference)), decltype(std::move(l_val_reference))>::value));

    bool _Flags{};
    utility_test_for_rhs _nothing;
    utility_test_for_rhs& _lhs_ref = _nothing;
    utility_test_for_rhs _rhs_obj(qlibc::move(_lhs_ref), _Flags);
    EXPECT(_Flags);

    EXPECT((qlibc::is_same<decltype(l_val_reference),
            decltype(qlibc::forward<decltype(l_val_reference)>(l_val_reference))>::value));
    EXPECT(utility_perfect_forward::_l_val_reference(qlibc::move(val)));
    qlibc::forward<decltype(l_val_reference)>(l_val_reference);
    qlibc::forward<decltype(qlibc::move(l_val_reference))>(qlibc::move(l_val_reference));

    EXPECT((qlibc::is_lvalue_reference<decltype(l_val_reference)>::value));
    EXPECT((qlibc::is_same<decltype(10), int>::value));
    EXPECT(qlibc::is_rvalue_reference<decltype(qlibc::move(10))>::value);
    EXPECT(qlibc::is_rvalue_reference<decltype(qlibc::move(l_val_reference))>::value);

}
int main(int argc, char * argv[]) {
    /// Run All Test Cases
    RUN_ALL_TEST()
    return 0;
}
