set(SOURCE project_source)
set(PROJECT_NAME myF)

cmake_minimum_required(VERSION 3.21)
project(${PROJECT_NAME} C)
set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
add_executable("${PROJECT_NAME}" "${SOURCE}")

include_directories("/usr/include/SDL2")
target_link_libraries(${PROJECT_NAME} m SDL2 SDL2_gfx SDL2_ttf SDL2_image)