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
CMAKE_BINARY_DIR = "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest"

# Include any dependencies generated for this target.
include bin/test/CMakeFiles/test_gk.dir/depend.make

# Include the progress variables for this target.
include bin/test/CMakeFiles/test_gk.dir/progress.make

# Include the compile flags for this target's objects.
include bin/test/CMakeFiles/test_gk.dir/flags.make

bin/test/CMakeFiles/test_gk.dir/test_gk.cpp.o: bin/test/CMakeFiles/test_gk.dir/flags.make
bin/test/CMakeFiles/test_gk.dir/test_gk.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/test/test_gk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/test/CMakeFiles/test_gk.dir/test_gk.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_gk.dir/test_gk.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/test/test_gk.cpp"

bin/test/CMakeFiles/test_gk.dir/test_gk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_gk.dir/test_gk.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/test/test_gk.cpp" > CMakeFiles/test_gk.dir/test_gk.cpp.i

bin/test/CMakeFiles/test_gk.dir/test_gk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_gk.dir/test_gk.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/test/test_gk.cpp" -o CMakeFiles/test_gk.dir/test_gk.cpp.s

# Object files for target test_gk
test_gk_OBJECTS = \
"CMakeFiles/test_gk.dir/test_gk.cpp.o"

# External object files for target test_gk
test_gk_EXTERNAL_OBJECTS =

bin/test_gk: bin/test/CMakeFiles/test_gk.dir/test_gk.cpp.o
bin/test_gk: bin/test/CMakeFiles/test_gk.dir/build.make
bin/test_gk: lib/libQSBD_GK.a
bin/test_gk: lib/libQSBD_UTILS.a
bin/test_gk: lib/libQSBD_STREAM_MAKER.a
bin/test_gk: lib/libQSBD_QUANTILE_SKETCH.a
bin/test_gk: lib/libQSBD_COMMUM_HEADER.a
bin/test_gk: lib/libQSBD_GLOBAL_GEN.a
bin/test_gk: lib/libQSBD_DEBUG.a
bin/test_gk: bin/test/CMakeFiles/test_gk.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../test_gk"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_gk.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/test/CMakeFiles/test_gk.dir/build: bin/test_gk

.PHONY : bin/test/CMakeFiles/test_gk.dir/build

bin/test/CMakeFiles/test_gk.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test" && $(CMAKE_COMMAND) -P CMakeFiles/test_gk.dir/cmake_clean.cmake
.PHONY : bin/test/CMakeFiles/test_gk.dir/clean

bin/test/CMakeFiles/test_gk.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/test" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/test/CMakeFiles/test_gk.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/test/CMakeFiles/test_gk.dir/depend

