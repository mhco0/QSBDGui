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
include bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/depend.make

# Include the progress variables for this target.
include bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/progress.make

# Include the compile flags for this target's objects.
include bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/flags.make

bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.o: bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/flags.make
bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/src/global_generator/global_generator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/src/global_generator/global_generator.cpp"

bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/src/global_generator/global_generator.cpp" > CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.i

bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/src/global_generator/global_generator.cpp" -o CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.s

# Object files for target QSBD_GLOBAL_GEN
QSBD_GLOBAL_GEN_OBJECTS = \
"CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.o"

# External object files for target QSBD_GLOBAL_GEN
QSBD_GLOBAL_GEN_EXTERNAL_OBJECTS =

lib/libQSBD_GLOBAL_GEN.a: bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/global_generator/global_generator.cpp.o
lib/libQSBD_GLOBAL_GEN.a: bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/build.make
lib/libQSBD_GLOBAL_GEN.a: bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libQSBD_GLOBAL_GEN.a"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" && $(CMAKE_COMMAND) -P CMakeFiles/QSBD_GLOBAL_GEN.dir/cmake_clean_target.cmake
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/QSBD_GLOBAL_GEN.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/build: lib/libQSBD_GLOBAL_GEN.a

.PHONY : bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/build

bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" && $(CMAKE_COMMAND) -P CMakeFiles/QSBD_GLOBAL_GEN.dir/cmake_clean.cmake
.PHONY : bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/clean

bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/src" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/src/CMakeFiles/QSBD_GLOBAL_GEN.dir/depend

