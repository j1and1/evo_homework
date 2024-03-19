cmake_minimum_required(VERSION 3.16.3)

project(evo_homework)

set(CMAKE_CXX_STANDARD 20)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_executable(${PROJECT_NAME} 
    src/generator.cpp
    src/processor.cpp
    src/agregator.cpp
    src/main.cpp)