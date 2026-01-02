cmake_minimum_required(VERSION 3.20)
project(interview_prep LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
  src/main.cpp
  dsa-implementations/dsu.cpp
)

target_include_directories(main PRIVATE dsa-implementations)
target_compile_options(main PRIVATE -Wall -Wextra -Wshadow -Wconversion)
