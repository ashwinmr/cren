# cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# Set minimum cpp version
set (CMAKE_CXX_STANDARD 11)

# project name
project( cren )

# Find packages
set(Boost_USE_STATIC_LIBS ON)
find_package( Boost COMPONENTS program_options filesystem )

# add subdirectories
add_subdirectory (src)
add_subdirectory (test)

# include
include_directories( ./src ${Boost_INCLUDE_DIRS} )

# add executable
add_executable( cren ./src/main.cpp )

# use main source code as a library and target other libraries
target_link_libraries( cren src ${Boost_LIBRARIES} )

# testing
enable_testing()
add_test(
  NAME test_main
  COMMAND test_main
)
