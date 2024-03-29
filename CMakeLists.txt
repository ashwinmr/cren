# Cmake version to be used
cmake_minimum_required( VERSION 3.1 )

# Set minimum cpp version
set (CMAKE_CXX_STANDARD 11)

# Project name
project( cren )

# Add subdirectories
add_subdirectory (src)
add_subdirectory (test)

# Find packages for all dependencies
set(Boost_USE_STATIC_LIBS ON)
find_package( Boost COMPONENTS program_options filesystem )

# Include all dependencies
include_directories( ./src ${Boost_INCLUDE_DIRS} )

# Add executable
add_executable( cren ./src/main.cpp )

# Use main source code as a library and target it
target_link_libraries( cren src )

# Install
install(TARGETS cren DESTINATION bin)

# Testing
enable_testing()
add_test(
  NAME test_main
  COMMAND test_main
)
