cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(assignment04)

# Include directories
include_directories(include)
include_directories(external)

# Add source files
add_executable(assignment04 
    src/main.cpp
    src/shaderClass.cpp
    src/Texture.cpp
    src/VAO.cpp 
    src/VBO.cpp 
    src/EBO.cpp
    src/stb_image.cpp
    external/glad/glad.c
)

# Find and link OpenGL and GLFW
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED CONFIG)

# Link GLFW and OpenGL
target_link_libraries(assignment04 
    glfw
    OpenGL::GL
)
