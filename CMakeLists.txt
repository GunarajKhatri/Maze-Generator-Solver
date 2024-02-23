cmake_minimum_required(VERSION 3.0)
project(MazeGeneration)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(maze main.cpp maze.cpp)

# Link SFML libraries
target_link_libraries(maze PRIVATE sfml-graphics sfml-window sfml-system)

configure_file(arial.ttf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
