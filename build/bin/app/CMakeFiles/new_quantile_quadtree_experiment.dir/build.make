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
include bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/depend.make

# Include the progress variables for this target.
include bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/progress.make

# Include the compile flags for this target's objects.
include bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/flags.make

bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.o: bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/flags.make
bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.o: /mnt/c/Users/Marcos/OneDrive/Área\ de\ Trabalho/Meus\ Projetos/Big-Data-IC/app/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.o"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.o -c "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp"

bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.i"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp" > CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.i

bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.s"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp" -o CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.s

# Object files for target new_quantile_quadtree_experiment
new_quantile_quadtree_experiment_OBJECTS = \
"CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.o"

# External object files for target new_quantile_quadtree_experiment
new_quantile_quadtree_experiment_EXTERNAL_OBJECTS =

bin/new_quantile_quadtree_experiment: bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/quantile_quadtree_experiment/new_quantile_quadtree_experiment.cpp.o
bin/new_quantile_quadtree_experiment: bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/build.make
bin/new_quantile_quadtree_experiment: lib/libQSBD_TIMER.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_QUANTILE_QUADTREE.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_GK_FACTORY.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_KLL_FACTORY.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_DCS_FACTORY.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_Q_DIGEST_FACTORY.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_UTILS.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_LOG.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_DEBUG.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_AABB.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_POINT.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_GK.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_KLL.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_DCS.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_COUNT_SKETCH.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_COMMUM_HEADER.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_TWO_WISE_FAMILY.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_GLOBAL_GEN.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_SKETCH_FACTORY.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_Q_DIGEST.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_UTILS.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_QUANTILE_SKETCH.a
bin/new_quantile_quadtree_experiment: lib/libQSBD_DEBUG.a
bin/new_quantile_quadtree_experiment: bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../new_quantile_quadtree_experiment"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/new_quantile_quadtree_experiment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/build: bin/new_quantile_quadtree_experiment

.PHONY : bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/build

bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" && $(CMAKE_COMMAND) -P CMakeFiles/new_quantile_quadtree_experiment.dir/cmake_clean.cmake
.PHONY : bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/clean

bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/build/bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/app/CMakeFiles/new_quantile_quadtree_experiment.dir/depend

