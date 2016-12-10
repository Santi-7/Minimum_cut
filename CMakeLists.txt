cmake_minimum_required(VERSION 3.5)
project(Minimum_cut)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra ")

add_subdirectory(src)

add_executable(Minimum_cut_run
        main.cpp
        ${HEADER_FILES}
        ${SOURCE_FILES})

include_directories(
        ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(Minimum_cut_run src)