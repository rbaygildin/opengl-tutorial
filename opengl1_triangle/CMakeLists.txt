cmake_minimum_required(VERSION 3.8)
project(opengl1_triangle)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)

# glfw
find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

file(GLOB_RECURSE SRC src/*.c src/*.cpp src/.*h src/*.hpp)

set(SOURCE_FILES ${SRC})

add_executable(opengl1_triangle ${SOURCE_FILES})

add_custom_command(TARGET opengl1_triangle POST_BUILD
        COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
        )

target_link_libraries(
        opengl1_triangle
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
)