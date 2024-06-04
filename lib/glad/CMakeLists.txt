cmake_minimum_required(VERSION 3.14)
project(Glad)

add_library(glad src/glad.c src/glad.h src/linmath.h src/KHR/khrplatform.h)

# target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(glad PUBLIC src)
