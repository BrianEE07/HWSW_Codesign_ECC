# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.22.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.22.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build

# Include any dependencies generated for this target.
include examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/flags.make

examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.o: examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/flags.make
examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.o: ../examples/sysc/2.1/sc_export/main.cpp
examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.o: examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.o"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.o -MF CMakeFiles/sc_export.dir/main.cpp.o.d -o CMakeFiles/sc_export.dir/main.cpp.o -c /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/2.1/sc_export/main.cpp

examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sc_export.dir/main.cpp.i"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/2.1/sc_export/main.cpp > CMakeFiles/sc_export.dir/main.cpp.i

examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sc_export.dir/main.cpp.s"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/2.1/sc_export/main.cpp -o CMakeFiles/sc_export.dir/main.cpp.s

# Object files for target sc_export
sc_export_OBJECTS = \
"CMakeFiles/sc_export.dir/main.cpp.o"

# External object files for target sc_export
sc_export_EXTERNAL_OBJECTS =

examples/sysc/2.1/sc_export/sc_export: examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/main.cpp.o
examples/sysc/2.1/sc_export/sc_export: examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/build.make
examples/sysc/2.1/sc_export/sc_export: src/libsystemc.2.3.3.dylib
examples/sysc/2.1/sc_export/sc_export: examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sc_export"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sc_export.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/build: examples/sysc/2.1/sc_export/sc_export
.PHONY : examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/build

examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/clean:
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export && $(CMAKE_COMMAND) -P CMakeFiles/sc_export.dir/cmake_clean.cmake
.PHONY : examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/clean

examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/depend:
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3 /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/2.1/sc_export /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sysc/2.1/sc_export/CMakeFiles/sc_export.dir/depend
