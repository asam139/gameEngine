cmake_minimum_required(VERSION 3.9)
project(gameEngine)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(
        glfw
        glm
)

include_directories(
        include
)

file (GLOB_RECURSE HEADER_FILES
        include/glad/*.h
)

file (GLOB_RECURSE DEPS_SRC_FILES
        src/deps/glad/*.c
)

file (GLOB_RECURSE SRC_FILES
        src/main.cpp
)

add_executable(gameEngine
        ${HEADER_FILES}
        ${DEPS_SRC_FILES}
        ${SRC_FILES}
)

target_link_libraries(gameEngine
        glfw ${GLFW_LIBRARIES}
)
#target_link_libraries(gameEngine glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})