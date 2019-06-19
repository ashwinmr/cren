# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# Set minimum cpp version
set (CMAKE_CXX_STANDARD 11)

# project name
project( cren )

# include
include_directories( ./src )

# target
add_executable( cren ./src/main.cpp )
