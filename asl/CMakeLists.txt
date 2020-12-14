cmake_minimum_required(VERSION 3.0.0)

project (als_tests)

find_package( ASL REQUIRED )

# Executable 1: Overview of basic utilities
# ./asl_test_00
add_executable(asl_test_00 asl_test_00.cpp)
target_link_libraries( asl_test_00 asls ) # if static lib to be used (recommended)
# No need for include_directories()

# Executable 2: Communication 1/2
# ./asl_test_01
add_executable(asl_test_01 asl_test_01.cpp)
target_link_libraries( asl_test_01 asls ) # if static lib to be used (recommended)
# No need for include_directories()

# Executable 3: Communication 2/2
# ./asl_test_02
add_executable(asl_test_02 asl_test_02.cpp)
target_link_libraries( asl_test_02 asls ) # if static lib to be used (recommended)
# No need for include_directories()