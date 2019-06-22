# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# Set minimum cpp version
set (CMAKE_CXX_STANDARD 11)

# project name
project( cren )

# Find packages
set(Boost_USE_STATIC_LIBS ON)
find_package( Boost COMPONENTS program_options filesystem )

# include
include_directories( ./src ${Boost_INCLUDE_DIRS} )

# target
add_executable( cren ./src/main.cpp )

# external libs
target_link_libraries( cren ${Boost_LIBRARIES} )
