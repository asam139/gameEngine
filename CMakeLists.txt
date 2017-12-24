cmake_minimum_required(VERSION 3.9)
project(gameEngine)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

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