project(huffman_compression)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

include_directories(${huffman_compression_SOURCE_DIR})


if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare -std=c++11 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

add_library(huffman_library
               huffmantree.h
               huffmantree.cpp
               encoded_vector.h
               encoded_vector.cpp
               huffman_coder.h
               huffman_coder.cpp)

install(TARGETS huffman_library
        DESTINATION lib)

install(FILES
        huffmantree.h
        encoded_vector.h
        huffman_coder.h
        DESTINATION include/huffman_library)

add_executable(huffman_compression
               main.cpp)

target_link_libraries(huffman_compression
                      huffman_library)




