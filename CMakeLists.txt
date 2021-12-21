
cmake_minimum_required(VERSION 3.1)
project(pogla VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(include)

set(SOURCES
    src/init.cpp)

add_executable(pogla src/main.cpp)
target_sources(pogla PRIVATE ${SOURCES})

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)

set(LIBS GL GLEW glut)
target_link_libraries(${PROJECT_NAME} ${LIBS})
