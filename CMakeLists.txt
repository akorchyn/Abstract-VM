cmake_minimum_required(VERSION 3.10.2)
project(cmake-build-debug/AbstractVM)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Ofast")

aux_source_directory(src/Operations opers)
add_executable(AbstractVM ${opers} src/main.cpp src/Classes/AbstractRuntimeException.cpp src/Classes/IOperandGenerator.cpp src/Classes/Parser.cpp)


