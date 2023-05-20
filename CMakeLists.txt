cmake_minimum_required(VERSION 3.25)

project(sudoku)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)

add_executable(${PROJECT_NAME} src/main.cpp src/SudokuBoard.cpp)


target_link_libraries(
 ${PROJECT_NAME}
 sfml-graphics
 sfml-window
 sfml-system
)
