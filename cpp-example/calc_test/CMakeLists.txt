cmake_minimum_required(VERSION 4.2)
project(calc)
add_executable(calc)
target_sources(calc
    PRIVATE    
    test_calculator.cpp
)
