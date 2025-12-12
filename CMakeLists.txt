cmake_minimum_required(VERSION 3.16)
project(seminar16 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(seminar16
    src/main.cpp
    src/algorithms.cpp
)

target_include_directories(seminar16 PRIVATE include)

# Warnings (beginner-friendly but helpful)
if (MSVC)
    target_compile_options(seminar16 PRIVATE /W4)
else()
    target_compile_options(seminar16 PRIVATE -Wall -Wextra -Wpedantic)
endif()
