cmake_minimum_required(VERSION 3.20)
project(renderer3d)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fsanitize=address")

find_package(SDL3 REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(renderer
    src/main.c
    glad/src/glad.c
)

# Include directories
target_include_directories(renderer PRIVATE
    glad/include
)

# Link libraries
target_link_libraries(renderer PRIVATE
    SDL3::SDL3
    OpenGL::GL
)
