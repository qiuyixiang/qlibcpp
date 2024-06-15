#include "../headers.h"

namespace iterator_test{

    void iterator_base(){
        void * _void_pointer = nullptr;
        double * _double_pointer{nullptr};
        _double_pointer = static_cast<double*>(_void_pointer);
        EXPECT((qlibc::is_same<double*, typename std::iterator_traits<decltype(_double_pointer)>::pointer>::value));
        EXPECT((qlibc::is_same<qlibc::random_access_iterator_tag,
                typename qlibc::iterator_traits<decltype(_double_pointer)>::iterator_category>::value));
    }
    void iterator_func(){
        int array_buffer[10] = {0,1,2,3,4,5,6,7,8,9};
        auto first_buffer_pointer=  &array_buffer[0];
        qlibc::advance(first_buffer_pointer, 4);
        EXPECT_EQUAL(*first_buffer_pointer, array_buffer[4]);
        qlibc::advance(first_buffer_pointer, -2);
        EXPECT_EQUAL(*first_buffer_pointer, array_buffer[2]);
        EXPECT_EQUAL(std::distance(&array_buffer[0], &array_buffer[5]),
                     qlibc::distance(&array_buffer[0], &array_buffer[5]));
        EXPECT_EQUAL(*qlibc::next(&array_buffer[0]), *std::next(&array_buffer[0]));
        EXPECT_EQUAL(*qlibc::next(&array_buffer[0], 3), *std::next(&array_buffer[0], 3));
        EXPECT_EQUAL(*qlibc::next(&array_buffer[0], 5), *std::next(&array_buffer[0], 5));
        EXPECT_EQUAL(*qlibc::prev(&array_buffer[0]), *std::prev(&array_buffer[0]));
        EXPECT_EQUAL(*qlibc::prev(&array_buffer[5], 3), *std::prev(&array_buffer[5], 3));
        EXPECT_EQUAL(*qlibc::prev(&array_buffer[5], 1), *std::prev(&array_buffer[5], 1));
        int Data1 = 10, Data2 = 20;
        EXPECT_EQUAL(Data1, 10);
        EXPECT_EQUAL(Data2, 20);
        qlibc::iter_swap(&Data1, &Data2);
        EXPECT_EQUAL(Data1, 20);
        EXPECT_EQUAL(Data2, 10);
        double Data_Double = 3.14;
        long Data_Long = 3;
        EXPECT_EQUAL(Data_Double, 3.14);
        qlibc::iter_swap(&Data_Double, &Data_Long);
        EXPECT_EQUAL(Data_Double, 3.0);
        EXPECT_EQUAL(Data_Long, 3);
    }
    void reverse_iterator_test(){
        std::vector<int>linear_buffer {1,2,3,4,5,6,7,8,9,10};
        std::reverse_iterator<typename std::vector<int>::iterator>std_rIter(linear_buffer.end());
        qlibc::reverse_iterator<typename std::vector<int>::iterator> rIter =
                qlibc::make_reverse_iterator(linear_buffer.end());
        EXPECT_EQUAL(*std_rIter++, *rIter++);
        EXPECT_EQUAL(*std_rIter, *rIter);
        std_rIter = std::reverse_iterator<typename std::vector<int>::iterator>(linear_buffer.begin() + 5);
        rIter = qlibc::make_reverse_iterator(linear_buffer.begin() + 5);
        EXPECT_EQUAL(*std_rIter, *rIter);
        EXPECT_EQUAL(*(--std_rIter), *(--rIter));
        EXPECT_EQUAL(*(std_rIter + 3), *(rIter + 3));
        EXPECT_EQUAL(*(std_rIter - 4), *(rIter - 4));
        EXPECT_EQUAL(*(std_rIter)++, *(rIter)++);
        EXPECT((qlibc::make_reverse_iterator(linear_buffer.begin()) ==
        qlibc::make_reverse_iterator(linear_buffer.begin())));
        EXPECT((qlibc::make_reverse_iterator(linear_buffer.begin()) !=
                qlibc::make_reverse_iterator(linear_buffer.end())));
    }
    void inserter_iterator_test(){
        EXPECT((qlibc::is_same<qlibc::output_iterator_tag,
                qlibc::iterator_traits<qlibc::back_insert_iterator<std::vector<int>>>::iterator_category>::value));
        EXPECT((qlibc::is_same<qlibc::iterator_traits
                <qlibc::back_insert_iterator<std::vector<int>>>::value_type, void>::value));
        std::vector<int>buffer;
        auto back_inserter_iterator = qlibc::back_inserter(buffer);
        *back_inserter_iterator = 10;
        EXPECT_EQUAL(buffer[0], 10);
        *back_inserter_iterator = 20;
        EXPECT_EQUAL(buffer[1], 20);
        EXPECT_EQUAL(buffer.size(), 2);
        *back_inserter_iterator = 30;
        auto inserter_iterator = qlibc::inserter(buffer, buffer.begin() + 1);
        *inserter_iterator = 10;
        EXPECT_EQUAL(buffer.size(), 4);
        EXPECT_EQUAL(buffer[1], 10);
        EXPECT_EQUAL(buffer[0], 10);
        *inserter_iterator = 20;
        EXPECT_EQUAL(buffer[2], 20);
    }
    void main_test(){
        iterator_test::iterator_base();
        iterator_test::iterator_func();
        iterator_test::reverse_iterator_test();
        iterator_test::inserter_iterator_test();
        std::cout << "Iterator Library :\033[32m Passed\n\033[0m";
    }
}