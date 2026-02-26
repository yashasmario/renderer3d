cmake_minimum_required(VERSION 3.20)
project(renderer3d)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address")

find_package(SDL3 REQUIRED)

add_executable(renderer
    src/main.c
)
add_executable(lines
    src/lines.c
)

target_link_libraries(renderer PRIVATE
    SDL3::SDL3
)
target_link_libraries(lines PRIVATE
    SDL3::SDL3
)
