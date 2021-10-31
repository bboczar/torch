cmake_minimum_required(VERSION 3.8)

project(Torch)

# Compilation flags
set(CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g -Wall -pedantic -Werror")

# Include dirs
include_directories(${PROJECT_SOURCE_DIR}/source)

# Build dir
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

# Subdirs
add_subdirectory(source)

# Deps
find_package(SFML 2.5 COMPONENTS system window REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)

#copy resources
set(fonts Bebas-Regular.ttf)
set(resources ${images} ${fonts} ${sounds})
foreach(item IN LISTS resources)
    add_custom_command(
        TARGET Torch POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/resources/${item}" "${CMAKE_CURRENT_BINARY_DIR}/resources/${item}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/resources/${item}"
    )
endforeach()