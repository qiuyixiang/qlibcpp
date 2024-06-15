cmake_minimum_required(VERSION 3.27)
project(qlibc___0_0_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(qlibc___0_0_2 main.cpp
        test/test.h
        include/iterator.h
        include/iterator/qlibc_iterator_base.h
        include/iterator/qlibc_iterator_algo.h
        include/iterator/qlibc_iterator.h
        test/headers.h
        include/type_traits.h
        include/allocator.h
        include/memory.h
        test/cases/iterator_test.cpp
        test/cases/type_traits_test.cpp
        test/cases/utility_test.cpp
        test/cases/algorithm_test.cpp
        test/cases/memory_test.cpp
        test/cases/container_test.cpp)

add_executable(main main.cpp
        include/config.h
        include/meta_programming/qlibc_type_traits.h
        include/utility.h
        include/utility/qlibc_move.h
        include/algorithm/qlibc_algorithm_base.h
        include/algorithm/qlibc_algorithm.h
        include/algorithm/qlibc_numeric.h
        include/algorithm.h
        include/numeric.h
        include/memory/qlibc_allocator.h
        include/memory/qlibc_initialized.h
        include/memory/qlibc_smart_ptr.h
        include/memory/qlibc_construct.h
        include/container/sequence_container/qlibc_forward_list.h
        include/forward_list.h
        include/container/dep.h)