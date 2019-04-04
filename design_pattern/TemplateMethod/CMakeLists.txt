cmake_minimum_required (VERSION 2.6)
project (TemplateMethod)

add_compile_options(-std=c++11)

add_executable(TemplateMethod ICar.cpp Car.cpp main.cpp)

