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
        test/cases/type_traits_test.cpp)

add_executable(main main.cpp
        include/config.h
        include/meta_programming/qlibc_type_traits.h)