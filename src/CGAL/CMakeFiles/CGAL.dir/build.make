# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = "/Applications/CMake 2.8-6.app/Contents/bin/cmake"

# The command to remove a file.
RM = "/Applications/CMake 2.8-6.app/Contents/bin/cmake" -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = "/Applications/CMake 2.8-6.app/Contents/bin/ccmake"

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0

# Include any dependencies generated for this target.
include src/CGAL/CMakeFiles/CGAL.dir/depend.make

# Include the progress variables for this target.
include src/CGAL/CMakeFiles/CGAL.dir/progress.make

# Include the compile flags for this target's objects.
include src/CGAL/CMakeFiles/CGAL.dir/flags.make

src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o: src/CGAL/CMakeFiles/CGAL.dir/flags.make
src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o: src/CGAL/all_files.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o"
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/CGAL.dir/all_files.cpp.o -c /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL/all_files.cpp

src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CGAL.dir/all_files.cpp.i"
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL/all_files.cpp > CMakeFiles/CGAL.dir/all_files.cpp.i

src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CGAL.dir/all_files.cpp.s"
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL/all_files.cpp -o CMakeFiles/CGAL.dir/all_files.cpp.s

src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.requires:
.PHONY : src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.requires

src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.provides: src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.requires
	$(MAKE) -f src/CGAL/CMakeFiles/CGAL.dir/build.make src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.provides.build
.PHONY : src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.provides

src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.provides.build: src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o

# Object files for target CGAL
CGAL_OBJECTS = \
"CMakeFiles/CGAL.dir/all_files.cpp.o"

# External object files for target CGAL
CGAL_EXTERNAL_OBJECTS =

lib/libCGAL.9.0.0.dylib: src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o
lib/libCGAL.9.0.0.dylib: /usr/local/lib/libboost_thread-mt.dylib
lib/libCGAL.9.0.0.dylib: src/CGAL/CMakeFiles/CGAL.dir/build.make
lib/libCGAL.9.0.0.dylib: src/CGAL/CMakeFiles/CGAL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../../lib/libCGAL.dylib"
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CGAL.dir/link.txt --verbose=$(VERBOSE)
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL && $(CMAKE_COMMAND) -E cmake_symlink_library ../../lib/libCGAL.9.0.0.dylib ../../lib/libCGAL.9.dylib ../../lib/libCGAL.dylib

lib/libCGAL.9.dylib: lib/libCGAL.9.0.0.dylib

lib/libCGAL.dylib: lib/libCGAL.9.0.0.dylib

# Rule to build all files generated by this target.
src/CGAL/CMakeFiles/CGAL.dir/build: lib/libCGAL.dylib
.PHONY : src/CGAL/CMakeFiles/CGAL.dir/build

src/CGAL/CMakeFiles/CGAL.dir/requires: src/CGAL/CMakeFiles/CGAL.dir/all_files.cpp.o.requires
.PHONY : src/CGAL/CMakeFiles/CGAL.dir/requires

src/CGAL/CMakeFiles/CGAL.dir/clean:
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL && $(CMAKE_COMMAND) -P CMakeFiles/CGAL.dir/cmake_clean.cmake
.PHONY : src/CGAL/CMakeFiles/CGAL.dir/clean

src/CGAL/CMakeFiles/CGAL.dir/depend:
	cd /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0 /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0 /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL /Users/SChatterjee/coi-pyon-libraries/code/cgal-4.0/CGAL-4.0/src/CGAL/CMakeFiles/CGAL.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CGAL/CMakeFiles/CGAL.dir/depend
