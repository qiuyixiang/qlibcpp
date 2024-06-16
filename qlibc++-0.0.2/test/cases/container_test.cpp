#include "../headers.h"

namespace container_test{

    namespace sequence{

        void forward_list_test(){
            std::forward_list<int>;
        }
    }
    namespace associative{

    }
    void main_test(){
        /// Test For Sequence Containers
        container_test::sequence::forward_list_test();
        /// Test For Associative Containers

        std::cout << "Container Library :\033[32m Passed\n\033[0m";
    }
}