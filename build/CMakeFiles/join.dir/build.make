# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/deu/Google Drive/Projects/Wenceslas"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/deu/Google Drive/Projects/Wenceslas/build"

# Include any dependencies generated for this target.
include CMakeFiles/join.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/join.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/join.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/join.dir/flags.make

ui_jointimes.h: ../src/jointimes.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/deu/Google Drive/Projects/Wenceslas/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating ui_jointimes.h"
	/usr/bin/uic -o "/home/deu/Google Drive/Projects/Wenceslas/build/ui_jointimes.h" "/home/deu/Google Drive/Projects/Wenceslas/src/jointimes.ui"

CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o: CMakeFiles/join.dir/flags.make
CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o: join_autogen/mocs_compilation.cpp
CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o: CMakeFiles/join.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/deu/Google Drive/Projects/Wenceslas/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o -MF CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o -c "/home/deu/Google Drive/Projects/Wenceslas/build/join_autogen/mocs_compilation.cpp"

CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/deu/Google Drive/Projects/Wenceslas/build/join_autogen/mocs_compilation.cpp" > CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.i

CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/deu/Google Drive/Projects/Wenceslas/build/join_autogen/mocs_compilation.cpp" -o CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.s

# Object files for target join
join_OBJECTS = \
"CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o"

# External object files for target join
join_EXTERNAL_OBJECTS =

join: CMakeFiles/join.dir/join_autogen/mocs_compilation.cpp.o
join: CMakeFiles/join.dir/build.make
join: /usr/lib/libQt5Widgets.so.5.15.2
join: /usr/lib/libQt5Sql.so.5.15.2
join: /usr/lib/libQt5Gui.so.5.15.2
join: /usr/lib/libQt5Core.so.5.15.2
join: CMakeFiles/join.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/deu/Google Drive/Projects/Wenceslas/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable join"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/join.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/join.dir/build: join
.PHONY : CMakeFiles/join.dir/build

CMakeFiles/join.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/join.dir/cmake_clean.cmake
.PHONY : CMakeFiles/join.dir/clean

CMakeFiles/join.dir/depend: ui_jointimes.h
	cd "/home/deu/Google Drive/Projects/Wenceslas/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/deu/Google Drive/Projects/Wenceslas" "/home/deu/Google Drive/Projects/Wenceslas" "/home/deu/Google Drive/Projects/Wenceslas/build" "/home/deu/Google Drive/Projects/Wenceslas/build" "/home/deu/Google Drive/Projects/Wenceslas/build/CMakeFiles/join.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/join.dir/depend

