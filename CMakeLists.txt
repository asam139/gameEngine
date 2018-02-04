cmake_minimum_required(VERSION 3.9)
project(gameEngine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_subdirectory(
        glfw
)

add_subdirectory(
        glm
)

include_directories(
        external_headers
        glfw/include
        glm
        stb

        headers
)

file (GLOB_RECURSE HEADER_FILES
        external_headers/glad/*.h
        glm/glm/*.hpp
        stb/stb_image.h
        headers/*
)

file (GLOB_RECURSE DEPS_SRC_FILES
        external_source/deps/glad/*.c
)

file (GLOB_RECURSE SRC_FILES
        source/*
)

add_executable(gameEngine
        ${HEADER_FILES}
        ${DEPS_SRC_FILES}
        ${SRC_FILES})

target_link_libraries(gameEngine
        glfw ${GLFW_LIBRARIES}
)
