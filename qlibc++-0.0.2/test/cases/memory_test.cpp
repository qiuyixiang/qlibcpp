#include "../headers.h"

namespace memory_test{

    class Construct_tester{
    private:
        int data;
    public:
        Construct_tester() = default;
        Construct_tester(int ff) : data(ff) { };
        operator int () const { return data; }
        ~Construct_tester() = default;
    };
    void construct_test(){
        auto class_ptr = new Construct_tester[10];
        qlibc::Construct_range(class_ptr, class_ptr + 10, 15);
        Construct_tester buffer[10]{15,15,15,15,15,15,15,15,15,15};
        EXPECT(qlibc::equal(class_ptr, class_ptr + 10, buffer));
        delete[] class_ptr;
    }
    void allocator_test(){
        qlibc::allocator<int>allocator;
        int * base_ptr = allocator.allocate(10);
        for (int i = 0; i != 10; ++i)
            allocator.construct(&base_ptr[i], 10);
        int array_buffer[10]{10,10,10,10,10,10,10,10,10,10};
        EXPECT(qlibc::equal(array_buffer, array_buffer + 10, base_ptr));
        for (int ii = 0 ; ii != 10; ++ii)
            allocator.destroy(&base_ptr[ii]);
        allocator.deallocate(base_ptr);
        typename qlibc::allocator<int>::rebind<double>::other dd_allocator;
        auto res = dd_allocator.allocate(3);
        dd_allocator.deallocate(res);
    }
    void main_test(){
        memory_test::construct_test();
        memory_test::allocator_test();
        std::cout << "Memory Library :\033[32m Passed\n\033[0m";
    }
}