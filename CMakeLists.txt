cmake_minimum_required(VERSION 3.10)
project(SimpleFIFO)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Executable to run the actual simulation with sc_main()
add_executable(run_fifo_sim src/simple_fifo/simple_fifo.cpp)
target_link_libraries(run_fifo_sim systemc)

# Test target (DO NOT compile simple_fifo.cpp again — just #include it)
add_executable(test_simple_fifo tests/test_simple_fifo.cpp)
target_link_libraries(test_simple_fifo GTest::gtest GTest::gtest_main pthread systemc)

# Enable and register the test
enable_testing()
add_test(NAME test_simple_fifo COMMAND test_simple_fifo)

# Test for Stage1 in pipe
add_executable(test_stage1 tests/test_stage1.cpp src/pipe/stage1.cpp)
target_include_directories(test_stage1 PRIVATE ${CMAKE_SOURCE_DIR}/src/pipe)
target_link_libraries(test_stage1 gtest gtest_main systemc)
add_test(NAME test_stage1 COMMAND test_stage1)

#Test for Stage2 in pipe
add_executable(test_stage2 tests/test_stage2.cpp src/pipe/stage2.cpp)
target_include_directories(test_stage2 PRIVATE ${CMAKE_SOURCE_DIR}/src/pipe)
target_link_libraries(test_stage2 gtest systemc)
add_test(NAME test_stage2 COMMAND test_stage2)

# Test for Stage3 in pipe
add_executable(test_stage3 tests/test_stage3.cpp src/pipe/stage3.cpp)
target_include_directories(test_stage3 PRIVATE ${CMAKE_SOURCE_DIR}/src/pipe)
target_link_libraries(test_stage3 gtest systemc)
add_test(NAME test_stage3 COMMAND test_stage3)

# Test for simple_perf
add_executable(test_simple_perf tests/test_simple_perf.cpp)
target_include_directories(test_simple_perf PRIVATE ${CMAKE_SOURCE_DIR}/src/simple_perf)
target_link_libraries(test_simple_perf gtest systemc)
add_test(NAME test_simple_perf COMMAND test_simple_perf)
