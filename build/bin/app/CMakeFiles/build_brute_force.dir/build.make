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
include bin/app/CMakeFiles/build_brute_force.dir/depend.make

# Include the progress variables for this target.
include bin/app/CMakeFiles/build_brute_force.dir/progress.make

# Include the compile flags for this target's objects.
include bin/app/CMakeFiles/build_brute_force.dir/flags.make

bin/app/CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.o: bin/app/CMakeFiles/build_brute_force.dir/flags.make
bin/app/CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/app/brute_force/build_brute_force.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/app/CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/brute_force/build_brute_force.cpp"

bin/app/CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/brute_force/build_brute_force.cpp" > CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.i

bin/app/CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/brute_force/build_brute_force.cpp" -o CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.s

# Object files for target build_brute_force
build_brute_force_OBJECTS = \
"CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.o"

# External object files for target build_brute_force
build_brute_force_EXTERNAL_OBJECTS =

bin/build_brute_force: bin/app/CMakeFiles/build_brute_force.dir/brute_force/build_brute_force.cpp.o
bin/build_brute_force: bin/app/CMakeFiles/build_brute_force.dir/build.make
bin/build_brute_force: lib/libQSBD_UTILS.a
bin/build_brute_force: lib/libQSBD_DEBUG.a
bin/build_brute_force: bin/app/CMakeFiles/build_brute_force.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../build_brute_force"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/build_brute_force.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/app/CMakeFiles/build_brute_force.dir/build: bin/build_brute_force

.PHONY : bin/app/CMakeFiles/build_brute_force.dir/build

bin/app/CMakeFiles/build_brute_force.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -P CMakeFiles/build_brute_force.dir/cmake_clean.cmake
.PHONY : bin/app/CMakeFiles/build_brute_force.dir/clean

bin/app/CMakeFiles/build_brute_force.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app/CMakeFiles/build_brute_force.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/app/CMakeFiles/build_brute_force.dir/depend

