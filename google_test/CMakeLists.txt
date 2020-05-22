cmake_minimum_required(VERSION 3.15)

project(mockTest)
link_directories(/home/elmpprv/projs/lib64/)

#add_executable(test sample1.cpp sample1_unittest.cpp)
add_executable(test test-src/TrainerTest.cpp)
target_link_libraries(test gtest_main gmock gtest pthread)
