cmake_minimum_required(VERSION 3.20)
project(renderer3d)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address -Wall")

find_package(SDL3 REQUIRED)

add_library(renderlib
    src/lines.c
)

target_link_libraries(renderlib PUBLIC SDL3::SDL3)

function(add_exe name)
    add_executable(${name} src/${name}.c)
    target_link_libraries(${name} PRIVATE SDL3::SDL3 renderlib)
endfunction()

add_exe(renderer)
add_exe(rectangle)
