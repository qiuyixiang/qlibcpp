#include "../headers.h"

namespace algorithm_test{
    void equal_test(){
        std::vector<int>buffer{1,2,3,4,5,6,7};
        std::vector<int>buffer_copy(buffer);
        EXPECT(qlibc::equal(buffer.begin(), buffer.end(), buffer_copy.begin()));
        EXPECT(std::equal(buffer.begin(), buffer.end(), buffer_copy.begin()));
    }
    void fill_test(){
        auto INT_Ptr = new int [10];
        std::vector<int> buffer{20,20,20,20,20,20,20,20,20,20};
        qlibc::fill(INT_Ptr, INT_Ptr + 10, 20);
        EXPECT_EQUAL(INT_Ptr[7], 20);
        EXPECT(qlibc::equal(buffer.begin(), buffer.end(), INT_Ptr));
        qlibc::fill_n(buffer.begin(), 10, 30);
        qlibc::fill(INT_Ptr, INT_Ptr + 10, 30);
        EXPECT(qlibc::equal(INT_Ptr, INT_Ptr + 10, buffer.begin()));
        delete[] INT_Ptr;
    }
    void lexicographical_compare_test(){
        const std::string data1 {"QIUYIXIANG"};
        const std::string data2 {"QIUYIXIANG1"};
        EXPECT_EQUAL(qlibc::lexicographical_compare(data1.begin(), data1.end(),
                                                    data2.begin(),data2.end()),
                     std::lexicographical_compare(data1.begin(), data1.end(),
                                                  data2.begin(), data2.end()));
        EXPECT(qlibc::lexicographical_compare(data1.begin(), data1.end(),
                                              data2.begin(),data2.end()));
        const std::string data3 {"QIUYIXIAN"};
        EXPECT(!qlibc::lexicographical_compare(data1.begin(), data1.end(),
                                               data3.begin(),data3.end()));
        auto greater_func = [](const char lhs, const char  rhs) -> bool {
            return lhs > rhs;
        };
        const std::string greater1 {"ABB"};
        const std::string greater2 {"AB"};
        EXPECT(greater1 > greater2);
        EXPECT_EQUAL(qlibc::lexicographical_compare(greater1.begin(), greater1.end(),
                                      greater2.begin(), greater2.end(), greater_func),
                     std::lexicographical_compare(greater1.begin(), greater1.end(),
                                      greater2.begin(), greater2.end(), greater_func));
    }
    void algorithm_base_test(){
        algorithm_test::equal_test();
        algorithm_test::fill_test();
        algorithm_test::lexicographical_compare_test();
    }
    void algorithm_test(){

    }
    void numeric_test(){

    }
    void main_test(){
        algorithm_test::algorithm_base_test();
        algorithm_test::algorithm_test();
        algorithm_test::numeric_test();
        std::cout << "Algorithm Library :\033[32m Passed\n\033[0m";
    }
}