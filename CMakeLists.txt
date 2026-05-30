cmake_minimum_required(VERSION 3.14)

project(findsubstr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -Wall -Wextra -Werror -gdwarf-4 -std=c++20")


set(SRC_LIST findsubstr.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST}  )
