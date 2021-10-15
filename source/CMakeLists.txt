find_package(SFML 2.5 COMPONENTS system window REQUIRED)

add_executable(Torch main.cpp)
target_link_libraries(Torch sfml-system sfml-window)