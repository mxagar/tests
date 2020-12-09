cmake_minimum_required(VERSION 3.0.0)

project (als_tests)

find_package( ASL REQUIRED )
add_executable(asl_test_00 asl_test_00.cpp)
target_link_libraries( asl_test_00 asls ) # if static lib to be used (recommended)
# No need for include_directories()