# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Sau/gameEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Sau/gameEngine/cmake-build-debug

# Include any dependencies generated for this target.
include glm/tests/CMakeFiles/gamma.dir/depend.make

# Include the progress variables for this target.
include glm/tests/CMakeFiles/gamma.dir/progress.make

# Include the compile flags for this target's objects.
include glm/tests/CMakeFiles/gamma.dir/flags.make

glm/tests/CMakeFiles/gamma.dir/gamma.c.o: glm/tests/CMakeFiles/gamma.dir/flags.make
glm/tests/CMakeFiles/gamma.dir/gamma.c.o: ../glfw/tests/gamma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Sau/gameEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object glm/tests/CMakeFiles/gamma.dir/gamma.c.o"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gamma.dir/gamma.c.o   -c /Users/Sau/gameEngine/glfw/tests/gamma.c

glm/tests/CMakeFiles/gamma.dir/gamma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/gamma.c.i"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Sau/gameEngine/glfw/tests/gamma.c > CMakeFiles/gamma.dir/gamma.c.i

glm/tests/CMakeFiles/gamma.dir/gamma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/gamma.c.s"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Sau/gameEngine/glfw/tests/gamma.c -o CMakeFiles/gamma.dir/gamma.c.s

glm/tests/CMakeFiles/gamma.dir/gamma.c.o.requires:

.PHONY : glm/tests/CMakeFiles/gamma.dir/gamma.c.o.requires

glm/tests/CMakeFiles/gamma.dir/gamma.c.o.provides: glm/tests/CMakeFiles/gamma.dir/gamma.c.o.requires
	$(MAKE) -f glm/tests/CMakeFiles/gamma.dir/build.make glm/tests/CMakeFiles/gamma.dir/gamma.c.o.provides.build
.PHONY : glm/tests/CMakeFiles/gamma.dir/gamma.c.o.provides

glm/tests/CMakeFiles/gamma.dir/gamma.c.o.provides.build: glm/tests/CMakeFiles/gamma.dir/gamma.c.o


glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o: glm/tests/CMakeFiles/gamma.dir/flags.make
glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o: ../glfw/deps/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Sau/gameEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gamma.dir/__/deps/glad.c.o   -c /Users/Sau/gameEngine/glfw/deps/glad.c

glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/__/deps/glad.c.i"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Sau/gameEngine/glfw/deps/glad.c > CMakeFiles/gamma.dir/__/deps/glad.c.i

glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/__/deps/glad.c.s"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Sau/gameEngine/glfw/deps/glad.c -o CMakeFiles/gamma.dir/__/deps/glad.c.s

glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.requires:

.PHONY : glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.requires

glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.provides: glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.requires
	$(MAKE) -f glm/tests/CMakeFiles/gamma.dir/build.make glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.provides.build
.PHONY : glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.provides

glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.provides.build: glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o


# Object files for target gamma
gamma_OBJECTS = \
"CMakeFiles/gamma.dir/gamma.c.o" \
"CMakeFiles/gamma.dir/__/deps/glad.c.o"

# External object files for target gamma
gamma_EXTERNAL_OBJECTS =

glm/tests/gamma.app/Contents/MacOS/gamma: glm/tests/CMakeFiles/gamma.dir/gamma.c.o
glm/tests/gamma.app/Contents/MacOS/gamma: glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o
glm/tests/gamma.app/Contents/MacOS/gamma: glm/tests/CMakeFiles/gamma.dir/build.make
glm/tests/gamma.app/Contents/MacOS/gamma: glm/src/libglfw3.a
glm/tests/gamma.app/Contents/MacOS/gamma: glm/tests/CMakeFiles/gamma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Sau/gameEngine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gamma.app/Contents/MacOS/gamma"
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gamma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glm/tests/CMakeFiles/gamma.dir/build: glm/tests/gamma.app/Contents/MacOS/gamma

.PHONY : glm/tests/CMakeFiles/gamma.dir/build

glm/tests/CMakeFiles/gamma.dir/requires: glm/tests/CMakeFiles/gamma.dir/gamma.c.o.requires
glm/tests/CMakeFiles/gamma.dir/requires: glm/tests/CMakeFiles/gamma.dir/__/deps/glad.c.o.requires

.PHONY : glm/tests/CMakeFiles/gamma.dir/requires

glm/tests/CMakeFiles/gamma.dir/clean:
	cd /Users/Sau/gameEngine/cmake-build-debug/glm/tests && $(CMAKE_COMMAND) -P CMakeFiles/gamma.dir/cmake_clean.cmake
.PHONY : glm/tests/CMakeFiles/gamma.dir/clean

glm/tests/CMakeFiles/gamma.dir/depend:
	cd /Users/Sau/gameEngine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Sau/gameEngine /Users/Sau/gameEngine/glfw/tests /Users/Sau/gameEngine/cmake-build-debug /Users/Sau/gameEngine/cmake-build-debug/glm/tests /Users/Sau/gameEngine/cmake-build-debug/glm/tests/CMakeFiles/gamma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glm/tests/CMakeFiles/gamma.dir/depend

