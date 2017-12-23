cmake_minimum_required(VERSION 3.9)
project(gameEngine)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(
        glfw

)
include_directories(
        include
        glfw/include
)



file (GLOB_RECURSE HEADER_FILES
        include/glad/*.h

        include/glm/*.h
        include/glm/*.hpp
        include/glm/*.inl
        include/KHR/*.h
        )

file (GLOB_RECURSE DEPS_SRC_FILES
        src/glad/*.c

        src/deps/glfw_deps/*
        )

#[[file (GLOB_RECURSE UNIX_DEPS_SRC_FILES
        src/deps/glfw/cocoa_init.m
        src/deps/glfw/cocoa_joystick.h
        src/deps/glfw/cocoa_joystick.m
        src/deps/glfw/cocoa_monitor.m
        src/deps/glfw/cocoa_monitor.m
        src/deps/glfw/cocoa_platform.h
        src/deps/glfw/cocoa_time.c
        src/deps/glfw/cocoa_window.m

        )]]

file (GLOB_RECURSE SRC_FILES
        src/main.cpp
        )

add_executable(gameEngine
        ${HEADER_FILES}
        ${SRC_FILES})

target_link_libraries(gameEngine glfw ${GLFW_LIBRARIES})