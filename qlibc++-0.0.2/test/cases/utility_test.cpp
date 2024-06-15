#include "../headers.h"

namespace utility_test{

    class Move_Class{
    private:
        int flags;
    public:
        Move_Class() : flags() { };
        ~Move_Class() = default;
        Move_Class(const Move_Class&) : flags(1) { };
        Move_Class(Move_Class&&)  noexcept : flags(2) { };
        QLIBC_CONSTEXPR int get_flags() const noexcept { return this->flags; }
    };
    void move_and_forward(){
        double data = 3.4242;
        EXPECT_EQUAL(&data, qlibc::address_of(data));
        utility_test::Move_Class moveClass;
        utility_test::Move_Class moveClass1(qlibc::move(moveClass));
        EXPECT_EQUAL(moveClass1.get_flags(), 2);
        EXPECT_EQUAL(moveClass.get_flags(), 0);
        EXPECT((qlibc::is_same<decltype(qlibc::forward<int>(10)), decltype(std::forward<int>(10))>::value));
        EXPECT((qlibc::is_same<decltype(qlibc::forward<double>(10.3)), decltype(std::forward<double>(10.34))>::value));
        const int integral = 100;
        EXPECT((qlibc::is_same<decltype(qlibc::forward<decltype(integral)>(integral)),
                decltype(std::forward<decltype(integral)>(integral))>::value));
        EXPECT((qlibc::is_same<decltype(qlibc::forward<decltype(integral)>(integral + 1)),
                decltype(std::forward<decltype(integral)>(integral + 1))>::value));
    }

    void main_test(){
        utility_test::move_and_forward();
        std::cout << "Utility Library :\033[32m Passed\n\033[0m";
    }
}