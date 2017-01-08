cmake_minimum_required(VERSION 3.4)
project(Minimum_cut)

# When releasing use CMAKE_CXX_FLAGS_RELEASE and -O3
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -std=c++14 -O3 -Wall -Wextra ")

add_subdirectory(src)

add_executable(Minimum_cut_run
        cut.cpp
        ${HEADER_FILES}
        ${SOURCE_FILES})

include_directories(
        ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(Minimum_cut_run src)