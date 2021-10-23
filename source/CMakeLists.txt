cmake_minimum_required(VERSION 3.10)
project(Torch)

# Subdirs
add_subdirectory(Game)

# Include dirs
include_directories(${PROJECT_SOURCE_DIR})

# Sources
set(SOURCES
   ${SOURCES}
   main.cpp
)

# Deps
find_package(SFML 2.5 COMPONENTS system window REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window)