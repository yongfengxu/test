#cmake_minimum_required(VERSION 3.15)

project(mockTest)

add_executable(test test-src/TrainerTest.cpp)
#dyanmic lib
link_directories(GTEST_LIB_DIR)
target_link_libraries(test gtest_main gmock gtest pthread)

#static lib
#target_link_libraries(test ${GTEST_STATIC_LIBS})
