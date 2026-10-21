cmake_minimum_required(VERSION 3.20)
project(renderer3d)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address -Wall")

find_package(SDL3 REQUIRED)

add_library(renderlib
    src/lines.c
    src/matrix.c
    src/rectangle.c
    src/triangle.c
)

target_link_libraries(renderlib PUBLIC SDL3::SDL3)

add_executable(renderer src/renderer.c)
target_link_libraries(renderer PRIVATE SDL3::SDL3 renderlib)

add_executable(wheel src/color_wheel.c)
target_link_libraries(wheel PRIVATE SDL3::SDL3 renderlib)
