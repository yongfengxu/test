cmake_minimum_required (VERSION 2.6)
project (AbstractFactory)

add_compile_options(-std=c++11)

add_executable(AbstractFactory ProductA.cpp ProductB.cpp Factory.cpp main.cpp)

