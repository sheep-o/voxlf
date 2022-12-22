cmake_minimum_required(VERSION 3.23)
project(engine)

set(CMAKE_CXX_STANDARD 23)

link_directories(/opt/homebrew/lib)
include_directories(/opt/homebrew/include)

file(GLOB SRC
        "*.h"
        "*.cpp"
        )

add_executable(engine ${SRC} ShaderProgram.cpp ShaderProgram.h Window.cpp Window.h Camera.cpp Camera.h Mesh.cpp Mesh.h)
find_package(OpenGL REQUIRED)
target_link_libraries(engine OpenGL::GL)
find_package(GLEW REQUIRED)
target_link_libraries(engine GLEW::GLEW)
target_link_libraries(engine glfw)
