# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mellk\source\repos\FCG2024-2\build

# Include any dependencies generated for this target.
include glm/CMakeFiles/glm_dummy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include glm/CMakeFiles/glm_dummy.dir/compiler_depend.make

# Include the progress variables for this target.
include glm/CMakeFiles/glm_dummy.dir/progress.make

# Include the compile flags for this target's objects.
include glm/CMakeFiles/glm_dummy.dir/flags.make

glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: glm/CMakeFiles/glm_dummy.dir/flags.make
glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: glm/CMakeFiles/glm_dummy.dir/includes_CXX.rsp
glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: C:/Users/mellk/source/repos/FCG2024-2/Dependencies/glm/glm/detail/dummy.cpp
glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj: glm/CMakeFiles/glm_dummy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mellk\source\repos\FCG2024-2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj -MF CMakeFiles\glm_dummy.dir\detail\dummy.cpp.obj.d -o CMakeFiles\glm_dummy.dir\detail\dummy.cpp.obj -c C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm\detail\dummy.cpp

glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glm_dummy.dir/detail/dummy.cpp.i"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm\detail\dummy.cpp > CMakeFiles\glm_dummy.dir\detail\dummy.cpp.i

glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glm_dummy.dir/detail/dummy.cpp.s"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm\detail\dummy.cpp -o CMakeFiles\glm_dummy.dir\detail\dummy.cpp.s

glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: glm/CMakeFiles/glm_dummy.dir/flags.make
glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: glm/CMakeFiles/glm_dummy.dir/includes_CXX.rsp
glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: C:/Users/mellk/source/repos/FCG2024-2/Dependencies/glm/glm/detail/glm.cpp
glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj: glm/CMakeFiles/glm_dummy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mellk\source\repos\FCG2024-2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj -MF CMakeFiles\glm_dummy.dir\detail\glm.cpp.obj.d -o CMakeFiles\glm_dummy.dir\detail\glm.cpp.obj -c C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm\detail\glm.cpp

glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/glm_dummy.dir/detail/glm.cpp.i"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm\detail\glm.cpp > CMakeFiles\glm_dummy.dir\detail\glm.cpp.i

glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/glm_dummy.dir/detail/glm.cpp.s"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && C:\msys64\ucrt64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm\detail\glm.cpp -o CMakeFiles\glm_dummy.dir\detail\glm.cpp.s

# Object files for target glm_dummy
glm_dummy_OBJECTS = \
"CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj" \
"CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj"

# External object files for target glm_dummy
glm_dummy_EXTERNAL_OBJECTS =

glm/glm_dummy.exe: glm/CMakeFiles/glm_dummy.dir/detail/dummy.cpp.obj
glm/glm_dummy.exe: glm/CMakeFiles/glm_dummy.dir/detail/glm.cpp.obj
glm/glm_dummy.exe: glm/CMakeFiles/glm_dummy.dir/build.make
glm/glm_dummy.exe: glm/CMakeFiles/glm_dummy.dir/linkLibs.rsp
glm/glm_dummy.exe: glm/CMakeFiles/glm_dummy.dir/objects1.rsp
glm/glm_dummy.exe: glm/CMakeFiles/glm_dummy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\mellk\source\repos\FCG2024-2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable glm_dummy.exe"
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\glm_dummy.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
glm/CMakeFiles/glm_dummy.dir/build: glm/glm_dummy.exe
.PHONY : glm/CMakeFiles/glm_dummy.dir/build

glm/CMakeFiles/glm_dummy.dir/clean:
	cd /d C:\Users\mellk\source\repos\FCG2024-2\build\glm && $(CMAKE_COMMAND) -P CMakeFiles\glm_dummy.dir\cmake_clean.cmake
.PHONY : glm/CMakeFiles/glm_dummy.dir/clean

glm/CMakeFiles/glm_dummy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm C:\Users\mellk\source\repos\FCG2024-2\Dependencies\glm\glm C:\Users\mellk\source\repos\FCG2024-2\build C:\Users\mellk\source\repos\FCG2024-2\build\glm C:\Users\mellk\source\repos\FCG2024-2\build\glm\CMakeFiles\glm_dummy.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : glm/CMakeFiles/glm_dummy.dir/depend

