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
include bin/app/CMakeFiles/build_queries.dir/depend.make

# Include the progress variables for this target.
include bin/app/CMakeFiles/build_queries.dir/progress.make

# Include the compile flags for this target's objects.
include bin/app/CMakeFiles/build_queries.dir/flags.make

bin/app/CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.o: bin/app/CMakeFiles/build_queries.dir/flags.make
bin/app/CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/app/query_creator/build_queries.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/app/CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/query_creator/build_queries.cpp"

bin/app/CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/query_creator/build_queries.cpp" > CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.i

bin/app/CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/query_creator/build_queries.cpp" -o CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.s

# Object files for target build_queries
build_queries_OBJECTS = \
"CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.o"

# External object files for target build_queries
build_queries_EXTERNAL_OBJECTS =

bin/build_queries: bin/app/CMakeFiles/build_queries.dir/query_creator/build_queries.cpp.o
bin/build_queries: bin/app/CMakeFiles/build_queries.dir/build.make
bin/build_queries: lib/libnlohmann_json.a
bin/build_queries: lib/libQSBD_UTILS.a
bin/build_queries: lib/libQSBD_DEBUG.a
bin/build_queries: bin/app/CMakeFiles/build_queries.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../build_queries"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/build_queries.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/app/CMakeFiles/build_queries.dir/build: bin/build_queries

.PHONY : bin/app/CMakeFiles/build_queries.dir/build

bin/app/CMakeFiles/build_queries.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -P CMakeFiles/build_queries.dir/cmake_clean.cmake
.PHONY : bin/app/CMakeFiles/build_queries.dir/clean

bin/app/CMakeFiles/build_queries.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app/CMakeFiles/build_queries.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/app/CMakeFiles/build_queries.dir/depend

