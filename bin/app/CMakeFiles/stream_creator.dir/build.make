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
include bin/app/CMakeFiles/stream_creator.dir/depend.make

# Include the progress variables for this target.
include bin/app/CMakeFiles/stream_creator.dir/progress.make

# Include the compile flags for this target's objects.
include bin/app/CMakeFiles/stream_creator.dir/flags.make

bin/app/CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.o: bin/app/CMakeFiles/stream_creator.dir/flags.make
bin/app/CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/app/stream_creator/stream_creator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/app/CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/stream_creator/stream_creator.cpp"

bin/app/CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/stream_creator/stream_creator.cpp" > CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.i

bin/app/CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/stream_creator/stream_creator.cpp" -o CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.s

# Object files for target stream_creator
stream_creator_OBJECTS = \
"CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.o"

# External object files for target stream_creator
stream_creator_EXTERNAL_OBJECTS =

bin/stream_creator: bin/app/CMakeFiles/stream_creator.dir/stream_creator/stream_creator.cpp.o
bin/stream_creator: bin/app/CMakeFiles/stream_creator.dir/build.make
bin/stream_creator: lib/libnlohmann_json.a
bin/stream_creator: lib/libQSBD_STREAM_MAKER.a
bin/stream_creator: lib/libQSBD_UTILS.a
bin/stream_creator: lib/libQSBD_LOG.a
bin/stream_creator: lib/libQSBD_DEBUG.a
bin/stream_creator: lib/libQSBD_COMMUM_HEADER.a
bin/stream_creator: lib/libQSBD_GLOBAL_GEN.a
bin/stream_creator: bin/app/CMakeFiles/stream_creator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../stream_creator"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stream_creator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/app/CMakeFiles/stream_creator.dir/build: bin/stream_creator

.PHONY : bin/app/CMakeFiles/stream_creator.dir/build

bin/app/CMakeFiles/stream_creator.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app" && $(CMAKE_COMMAND) -P CMakeFiles/stream_creator.dir/cmake_clean.cmake
.PHONY : bin/app/CMakeFiles/stream_creator.dir/clean

bin/app/CMakeFiles/stream_creator.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/app/CMakeFiles/stream_creator.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/app/CMakeFiles/stream_creator.dir/depend

