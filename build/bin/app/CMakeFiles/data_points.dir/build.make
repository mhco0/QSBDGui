# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build"

# Include any dependencies generated for this target.
include bin/app/CMakeFiles/data_points.dir/depend.make

# Include the progress variables for this target.
include bin/app/CMakeFiles/data_points.dir/progress.make

# Include the compile flags for this target's objects.
include bin/app/CMakeFiles/data_points.dir/flags.make

bin/app/CMakeFiles/data_points.dir/coletor/data_points.cpp.o: bin/app/CMakeFiles/data_points.dir/flags.make
bin/app/CMakeFiles/data_points.dir/coletor/data_points.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/app/coletor/data_points.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/app/CMakeFiles/data_points.dir/coletor/data_points.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/data_points.dir/coletor/data_points.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/coletor/data_points.cpp"

bin/app/CMakeFiles/data_points.dir/coletor/data_points.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/data_points.dir/coletor/data_points.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/coletor/data_points.cpp" > CMakeFiles/data_points.dir/coletor/data_points.cpp.i

bin/app/CMakeFiles/data_points.dir/coletor/data_points.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/data_points.dir/coletor/data_points.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/coletor/data_points.cpp" -o CMakeFiles/data_points.dir/coletor/data_points.cpp.s

# Object files for target data_points
data_points_OBJECTS = \
"CMakeFiles/data_points.dir/coletor/data_points.cpp.o"

# External object files for target data_points
data_points_EXTERNAL_OBJECTS =

bin/data_points: bin/app/CMakeFiles/data_points.dir/coletor/data_points.cpp.o
bin/data_points: bin/app/CMakeFiles/data_points.dir/build.make
bin/data_points: lib/libnlohmann_json.a
bin/data_points: lib/libQSBD_UTILS.a
bin/data_points: lib/libQSBD_DEBUG.a
bin/data_points: bin/app/CMakeFiles/data_points.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../data_points"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/data_points.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/app/CMakeFiles/data_points.dir/build: bin/data_points

.PHONY : bin/app/CMakeFiles/data_points.dir/build

bin/app/CMakeFiles/data_points.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -P CMakeFiles/data_points.dir/cmake_clean.cmake
.PHONY : bin/app/CMakeFiles/data_points.dir/clean

bin/app/CMakeFiles/data_points.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app/CMakeFiles/data_points.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/app/CMakeFiles/data_points.dir/depend

