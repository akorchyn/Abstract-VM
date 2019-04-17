cmake_minimum_required(VERSION 3.13)
project(AbstractVM)

SET (BOOST_ROOT "$ENV{HOME}/.brew/Cellar/boost/1.69.0")
SET (BOOST_INCLUDEDIR "${BOOST_ROOT}/includes")
SET (BOOST_LIBRARYDIR "${BOOST_ROOT}/lib")
SET (BOOST_MIN_VERSION "1.69.0")

set (Boost_NO_BOOST_CMAKE ON)
FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
aux_source_directory(. t)
add_executable(AbstractVM training.cpp)


