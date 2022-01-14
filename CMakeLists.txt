cmake_minimum_required(VERSION 3.1)
project(pogla VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include_directories(include)

set(SOURCES
  src/program.cpp
  src/objloader.cpp
  src/mouse.cpp
  src/model.cpp
  src/mesh.cpp)

add_executable(pogla src/main.cpp)
target_sources(pogla PRIVATE ${SOURCES})

# Used to find shaders file
#configure_file(configure.h.in "${CMAKE_SOURCE_DIR}/include/configure.hh")

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
find_path(GLEW_INCLUDE_DIR GL/glew.h)
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s PATH_SUFFIXES lib64)

find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)

set(LIBS glfw GL assimp GLEW SDL2)
target_link_libraries(${PROJECT_NAME} ${LIBS})
