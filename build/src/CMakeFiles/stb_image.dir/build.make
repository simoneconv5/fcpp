# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\build"

# Include any dependencies generated for this target.
include src/CMakeFiles/stb_image.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/stb_image.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/stb_image.dir/flags.make

src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.obj: src/CMakeFiles/stb_image.dir/flags.make
src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.obj: src/CMakeFiles/stb_image.dir/includes_CXX.rsp
src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.obj: ../src/external/stb_image/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.obj"
	cd /d C:\Users\luigi\DOCUME~1\GITREP~1\fcpp\fcpp\build\src && C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\stb_image.dir\external\stb_image\stb_image.cpp.obj -c "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\src\external\stb_image\stb_image.cpp"

src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.i"
	cd /d C:\Users\luigi\DOCUME~1\GITREP~1\fcpp\fcpp\build\src && C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\src\external\stb_image\stb_image.cpp" > CMakeFiles\stb_image.dir\external\stb_image\stb_image.cpp.i

src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.s"
	cd /d C:\Users\luigi\DOCUME~1\GITREP~1\fcpp\fcpp\build\src && C:\mingw-w64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\src\external\stb_image\stb_image.cpp" -o CMakeFiles\stb_image.dir\external\stb_image\stb_image.cpp.s

# Object files for target stb_image
stb_image_OBJECTS = \
"CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.obj"

# External object files for target stb_image
stb_image_EXTERNAL_OBJECTS =

src/libstb_image.a: src/CMakeFiles/stb_image.dir/external/stb_image/stb_image.cpp.obj
src/libstb_image.a: src/CMakeFiles/stb_image.dir/build.make
src/libstb_image.a: src/CMakeFiles/stb_image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libstb_image.a"
	cd /d C:\Users\luigi\DOCUME~1\GITREP~1\fcpp\fcpp\build\src && $(CMAKE_COMMAND) -P CMakeFiles\stb_image.dir\cmake_clean_target.cmake
	cd /d C:\Users\luigi\DOCUME~1\GITREP~1\fcpp\fcpp\build\src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\stb_image.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/stb_image.dir/build: src/libstb_image.a

.PHONY : src/CMakeFiles/stb_image.dir/build

src/CMakeFiles/stb_image.dir/clean:
	cd /d C:\Users\luigi\DOCUME~1\GITREP~1\fcpp\fcpp\build\src && $(CMAKE_COMMAND) -P CMakeFiles\stb_image.dir\cmake_clean.cmake
.PHONY : src/CMakeFiles/stb_image.dir/clean

src/CMakeFiles/stb_image.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp" "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\src" "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\build" "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\build\src" "C:\Users\luigi\Documents\Git Repos\fcpp\fcpp\build\src\CMakeFiles\stb_image.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/stb_image.dir/depend
