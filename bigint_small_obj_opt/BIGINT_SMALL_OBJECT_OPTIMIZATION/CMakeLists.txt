project(BIGINT_SMALL_OBJECT_OPTIMIZATION)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

include_directories(${BIGINT_SMALL_OBJECT_OPTIMIZATION_SOURCE_DIR})

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare -std=c++11 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

add_executable(big_integer_small_optimization
               big_integer_testing.cpp
               big_integer.cpp
               big_integer.h
               opt_vector.cpp
               opt_vector.h
               gtest/gtest-all.cc
               gtest/gtest.h
#               main.cpp)
               gtest/gtest_main.cc)

target_link_libraries(big_integer_small_optimization -lgmp -lgmpxx -lpthread)
