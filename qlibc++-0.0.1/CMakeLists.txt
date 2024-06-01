cmake_minimum_required(VERSION 3.27)
project(qlibc___0_0_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(qlibc___0_0_1 main.cpp
        test/test.h
        include/meta_programming/qlibc_type_traits.h
        include/type_traits.h
        include/iterator/qlibc_iterator_func.h
        include/memory/qlibc_allocator.h
        include/memory.h
        include/memory/qlibc_uninitialized.h
        include/memory/qlibc_new.h
)
