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
include examples/sysc/fir/CMakeFiles/fir_rtl.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/sysc/fir/CMakeFiles/fir_rtl.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/sysc/fir/CMakeFiles/fir_rtl.dir/progress.make

# Include the compile flags for this target's objects.
include examples/sysc/fir/CMakeFiles/fir_rtl.dir/flags.make

examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/flags.make
examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.o: ../examples/sysc/fir/main_rtl.cpp
examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.o"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.o -MF CMakeFiles/fir_rtl.dir/main_rtl.cpp.o.d -o CMakeFiles/fir_rtl.dir/main_rtl.cpp.o -c /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/main_rtl.cpp

examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fir_rtl.dir/main_rtl.cpp.i"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/main_rtl.cpp > CMakeFiles/fir_rtl.dir/main_rtl.cpp.i

examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fir_rtl.dir/main_rtl.cpp.s"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/main_rtl.cpp -o CMakeFiles/fir_rtl.dir/main_rtl.cpp.s

examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/flags.make
examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o: ../examples/sysc/fir/fir_fsm.cpp
examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o -MF CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o.d -o CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o -c /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/fir_fsm.cpp

examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fir_rtl.dir/fir_fsm.cpp.i"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/fir_fsm.cpp > CMakeFiles/fir_rtl.dir/fir_fsm.cpp.i

examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fir_rtl.dir/fir_fsm.cpp.s"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/fir_fsm.cpp -o CMakeFiles/fir_rtl.dir/fir_fsm.cpp.s

examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/flags.make
examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.o: ../examples/sysc/fir/fir_data.cpp
examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.o"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.o -MF CMakeFiles/fir_rtl.dir/fir_data.cpp.o.d -o CMakeFiles/fir_rtl.dir/fir_data.cpp.o -c /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/fir_data.cpp

examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fir_rtl.dir/fir_data.cpp.i"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/fir_data.cpp > CMakeFiles/fir_rtl.dir/fir_data.cpp.i

examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fir_rtl.dir/fir_data.cpp.s"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/fir_data.cpp -o CMakeFiles/fir_rtl.dir/fir_data.cpp.s

examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/flags.make
examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.o: ../examples/sysc/fir/stimulus.cpp
examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.o"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.o -MF CMakeFiles/fir_rtl.dir/stimulus.cpp.o.d -o CMakeFiles/fir_rtl.dir/stimulus.cpp.o -c /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/stimulus.cpp

examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fir_rtl.dir/stimulus.cpp.i"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/stimulus.cpp > CMakeFiles/fir_rtl.dir/stimulus.cpp.i

examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fir_rtl.dir/stimulus.cpp.s"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/stimulus.cpp -o CMakeFiles/fir_rtl.dir/stimulus.cpp.s

examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/flags.make
examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.o: ../examples/sysc/fir/display.cpp
examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.o: examples/sysc/fir/CMakeFiles/fir_rtl.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.o"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.o -MF CMakeFiles/fir_rtl.dir/display.cpp.o.d -o CMakeFiles/fir_rtl.dir/display.cpp.o -c /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/display.cpp

examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fir_rtl.dir/display.cpp.i"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/display.cpp > CMakeFiles/fir_rtl.dir/display.cpp.i

examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fir_rtl.dir/display.cpp.s"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir/display.cpp -o CMakeFiles/fir_rtl.dir/display.cpp.s

# Object files for target fir_rtl
fir_rtl_OBJECTS = \
"CMakeFiles/fir_rtl.dir/main_rtl.cpp.o" \
"CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o" \
"CMakeFiles/fir_rtl.dir/fir_data.cpp.o" \
"CMakeFiles/fir_rtl.dir/stimulus.cpp.o" \
"CMakeFiles/fir_rtl.dir/display.cpp.o"

# External object files for target fir_rtl
fir_rtl_EXTERNAL_OBJECTS =

examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/main_rtl.cpp.o
examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_fsm.cpp.o
examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/fir_data.cpp.o
examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/stimulus.cpp.o
examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/display.cpp.o
examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/build.make
examples/sysc/fir/fir_rtl: src/libsystemc.2.3.3.dylib
examples/sysc/fir/fir_rtl: examples/sysc/fir/CMakeFiles/fir_rtl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable fir_rtl"
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fir_rtl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/sysc/fir/CMakeFiles/fir_rtl.dir/build: examples/sysc/fir/fir_rtl
.PHONY : examples/sysc/fir/CMakeFiles/fir_rtl.dir/build

examples/sysc/fir/CMakeFiles/fir_rtl.dir/clean:
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir && $(CMAKE_COMMAND) -P CMakeFiles/fir_rtl.dir/cmake_clean.cmake
.PHONY : examples/sysc/fir/CMakeFiles/fir_rtl.dir/clean

examples/sysc/fir/CMakeFiles/fir_rtl.dir/depend:
	cd /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3 /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/examples/sysc/fir /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir /Users/fanyungwei/Documents/MyDoc/senior_2022/Hardware_Software_Codesign/HWSW_Codesign_ECC/src/systemc-2.3.3/build/examples/sysc/fir/CMakeFiles/fir_rtl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/sysc/fir/CMakeFiles/fir_rtl.dir/depend

