# Find packages
find_package( GTest )

# include
include_directories( ../src ${GTEST_INCLUDE_DIRS} )

# target
add_executable( test_main ./test_main.cpp )

# target external libs
target_link_libraries( test_main src ${GTEST_BOTH_LIBRARIES} )
