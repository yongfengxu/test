cmake_minimum_required(VERSION 3.15)
project(Learning)

# Set variables
SET(ROOT_PATH ~/test)
SET(EXECUTABLE_OUTPUT_PATH ${ROOT_PATH}/build)

set(GTEST_SRC_DIR ${ROOT_PATH}/googletest)
set(GTEST_HEADER_DIR ${GTEST_SRC_DIR}/googletest/include)
set(GMOCK_HEADER_DIR ${GTEST_SRC_DIR}/googlemock/include)
set(GTEST_LIB_DIR ${GTEST_SRC_DIR}/build/lib)
set(GTEST_STATIC_LIBS ${GTEST_LIB_DIR}/libgmock.a ${GTEST_LIB_DIR}/libgtest.a ${GTEST_LIB_DIR}/libgtest_main.a ${GTEST_LIB_DIR}/libgmock_main.a)


include_directories(${GTEST_HEADER_DIR} ${GMOCK_HEADER_DIR})
link_directories(GTEST_LIB_DIR)

add_subdirectory(gtest_learning)

