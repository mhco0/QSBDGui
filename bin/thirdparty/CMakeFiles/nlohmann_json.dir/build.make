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
include bin/thirdparty/CMakeFiles/nlohmann_json.dir/depend.make

# Include the progress variables for this target.
include bin/thirdparty/CMakeFiles/nlohmann_json.dir/progress.make

# Include the compile flags for this target's objects.
include bin/thirdparty/CMakeFiles/nlohmann_json.dir/flags.make

# Object files for target nlohmann_json
nlohmann_json_OBJECTS =

# External object files for target nlohmann_json
nlohmann_json_EXTERNAL_OBJECTS =

lib/libnlohmann_json.a: bin/thirdparty/CMakeFiles/nlohmann_json.dir/build.make
lib/libnlohmann_json.a: bin/thirdparty/CMakeFiles/nlohmann_json.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library ../../lib/libnlohmann_json.a"
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/thirdparty" && $(CMAKE_COMMAND) -P CMakeFiles/nlohmann_json.dir/cmake_clean_target.cmake
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/thirdparty" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nlohmann_json.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/thirdparty/CMakeFiles/nlohmann_json.dir/build: lib/libnlohmann_json.a

.PHONY : bin/thirdparty/CMakeFiles/nlohmann_json.dir/build

bin/thirdparty/CMakeFiles/nlohmann_json.dir/clean:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/thirdparty" && $(CMAKE_COMMAND) -P CMakeFiles/nlohmann_json.dir/cmake_clean.cmake
.PHONY : bin/thirdparty/CMakeFiles/nlohmann_json.dir/clean

bin/thirdparty/CMakeFiles/nlohmann_json.dir/depend:
	cd "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/Big-Data-IC/thirdparty" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/thirdparty" "/mnt/c/Users/Marcos/OneDrive/Área de Trabalho/Meus Projetos/QSBDGuiTest/bin/thirdparty/CMakeFiles/nlohmann_json.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : bin/thirdparty/CMakeFiles/nlohmann_json.dir/depend

