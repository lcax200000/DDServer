# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.6

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/shares/DDServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/shares/DDServer/debug

# Include any dependencies generated for this target.
include CMakeFiles/DDServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DDServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DDServer.dir/flags.make

CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o: ../tinyxmlparser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o -c /mnt/shares/DDServer/tinyxmlparser.cpp

CMakeFiles/DDServer.dir/tinyxmlparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/tinyxmlparser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/tinyxmlparser.cpp > CMakeFiles/DDServer.dir/tinyxmlparser.cpp.i

CMakeFiles/DDServer.dir/tinyxmlparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/tinyxmlparser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/tinyxmlparser.cpp -o CMakeFiles/DDServer.dir/tinyxmlparser.cpp.s

CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.requires

CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.provides: CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.provides

CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.provides.build: CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o
.PHONY : CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.provides.build

CMakeFiles/DDServer.dir/tinyxml.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/tinyxml.cpp.o: ../tinyxml.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/tinyxml.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/tinyxml.cpp.o -c /mnt/shares/DDServer/tinyxml.cpp

CMakeFiles/DDServer.dir/tinyxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/tinyxml.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/tinyxml.cpp > CMakeFiles/DDServer.dir/tinyxml.cpp.i

CMakeFiles/DDServer.dir/tinyxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/tinyxml.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/tinyxml.cpp -o CMakeFiles/DDServer.dir/tinyxml.cpp.s

CMakeFiles/DDServer.dir/tinyxml.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/tinyxml.cpp.o.requires

CMakeFiles/DDServer.dir/tinyxml.cpp.o.provides: CMakeFiles/DDServer.dir/tinyxml.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/tinyxml.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/tinyxml.cpp.o.provides

CMakeFiles/DDServer.dir/tinyxml.cpp.o.provides.build: CMakeFiles/DDServer.dir/tinyxml.cpp.o
.PHONY : CMakeFiles/DDServer.dir/tinyxml.cpp.o.provides.build

CMakeFiles/DDServer.dir/Time_Value.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Time_Value.cpp.o: ../Time_Value.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Time_Value.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Time_Value.cpp.o -c /mnt/shares/DDServer/Time_Value.cpp

CMakeFiles/DDServer.dir/Time_Value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Time_Value.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Time_Value.cpp > CMakeFiles/DDServer.dir/Time_Value.cpp.i

CMakeFiles/DDServer.dir/Time_Value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Time_Value.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Time_Value.cpp -o CMakeFiles/DDServer.dir/Time_Value.cpp.s

CMakeFiles/DDServer.dir/Time_Value.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Time_Value.cpp.o.requires

CMakeFiles/DDServer.dir/Time_Value.cpp.o.provides: CMakeFiles/DDServer.dir/Time_Value.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Time_Value.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Time_Value.cpp.o.provides

CMakeFiles/DDServer.dir/Time_Value.cpp.o.provides.build: CMakeFiles/DDServer.dir/Time_Value.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Time_Value.cpp.o.provides.build

CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o: ../Allocator_Manager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o -c /mnt/shares/DDServer/Allocator_Manager.cpp

CMakeFiles/DDServer.dir/Allocator_Manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Allocator_Manager.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Allocator_Manager.cpp > CMakeFiles/DDServer.dir/Allocator_Manager.cpp.i

CMakeFiles/DDServer.dir/Allocator_Manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Allocator_Manager.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Allocator_Manager.cpp -o CMakeFiles/DDServer.dir/Allocator_Manager.cpp.s

CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.requires

CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.provides: CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.provides

CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.provides.build: CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.provides.build

CMakeFiles/DDServer.dir/server.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/server.cpp.o: ../server.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/server.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/server.cpp.o -c /mnt/shares/DDServer/server.cpp

CMakeFiles/DDServer.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/server.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/server.cpp > CMakeFiles/DDServer.dir/server.cpp.i

CMakeFiles/DDServer.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/server.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/server.cpp -o CMakeFiles/DDServer.dir/server.cpp.s

CMakeFiles/DDServer.dir/server.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/server.cpp.o.requires

CMakeFiles/DDServer.dir/server.cpp.o.provides: CMakeFiles/DDServer.dir/server.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/server.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/server.cpp.o.provides

CMakeFiles/DDServer.dir/server.cpp.o.provides.build: CMakeFiles/DDServer.dir/server.cpp.o
.PHONY : CMakeFiles/DDServer.dir/server.cpp.o.provides.build

CMakeFiles/DDServer.dir/Stream.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Stream.cpp.o: ../Stream.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Stream.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Stream.cpp.o -c /mnt/shares/DDServer/Stream.cpp

CMakeFiles/DDServer.dir/Stream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Stream.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Stream.cpp > CMakeFiles/DDServer.dir/Stream.cpp.i

CMakeFiles/DDServer.dir/Stream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Stream.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Stream.cpp -o CMakeFiles/DDServer.dir/Stream.cpp.s

CMakeFiles/DDServer.dir/Stream.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Stream.cpp.o.requires

CMakeFiles/DDServer.dir/Stream.cpp.o.provides: CMakeFiles/DDServer.dir/Stream.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Stream.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Stream.cpp.o.provides

CMakeFiles/DDServer.dir/Stream.cpp.o.provides.build: CMakeFiles/DDServer.dir/Stream.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Stream.cpp.o.provides.build

CMakeFiles/DDServer.dir/Lua_C.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Lua_C.cpp.o: ../Lua_C.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Lua_C.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Lua_C.cpp.o -c /mnt/shares/DDServer/Lua_C.cpp

CMakeFiles/DDServer.dir/Lua_C.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Lua_C.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Lua_C.cpp > CMakeFiles/DDServer.dir/Lua_C.cpp.i

CMakeFiles/DDServer.dir/Lua_C.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Lua_C.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Lua_C.cpp -o CMakeFiles/DDServer.dir/Lua_C.cpp.s

CMakeFiles/DDServer.dir/Lua_C.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Lua_C.cpp.o.requires

CMakeFiles/DDServer.dir/Lua_C.cpp.o.provides: CMakeFiles/DDServer.dir/Lua_C.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Lua_C.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Lua_C.cpp.o.provides

CMakeFiles/DDServer.dir/Lua_C.cpp.o.provides.build: CMakeFiles/DDServer.dir/Lua_C.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Lua_C.cpp.o.provides.build

CMakeFiles/DDServer.dir/Block_Allocator.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Block_Allocator.cpp.o: ../Block_Allocator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Block_Allocator.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Block_Allocator.cpp.o -c /mnt/shares/DDServer/Block_Allocator.cpp

CMakeFiles/DDServer.dir/Block_Allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Block_Allocator.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Block_Allocator.cpp > CMakeFiles/DDServer.dir/Block_Allocator.cpp.i

CMakeFiles/DDServer.dir/Block_Allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Block_Allocator.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Block_Allocator.cpp -o CMakeFiles/DDServer.dir/Block_Allocator.cpp.s

CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.requires

CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.provides: CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.provides

CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.provides.build: CMakeFiles/DDServer.dir/Block_Allocator.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.provides.build

CMakeFiles/DDServer.dir/tinystr.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/tinystr.cpp.o: ../tinystr.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/tinystr.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/tinystr.cpp.o -c /mnt/shares/DDServer/tinystr.cpp

CMakeFiles/DDServer.dir/tinystr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/tinystr.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/tinystr.cpp > CMakeFiles/DDServer.dir/tinystr.cpp.i

CMakeFiles/DDServer.dir/tinystr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/tinystr.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/tinystr.cpp -o CMakeFiles/DDServer.dir/tinystr.cpp.s

CMakeFiles/DDServer.dir/tinystr.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/tinystr.cpp.o.requires

CMakeFiles/DDServer.dir/tinystr.cpp.o.provides: CMakeFiles/DDServer.dir/tinystr.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/tinystr.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/tinystr.cpp.o.provides

CMakeFiles/DDServer.dir/tinystr.cpp.o.provides.build: CMakeFiles/DDServer.dir/tinystr.cpp.o
.PHONY : CMakeFiles/DDServer.dir/tinystr.cpp.o.provides.build

CMakeFiles/DDServer.dir/Socket_Poll.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Socket_Poll.cpp.o: ../Socket_Poll.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Socket_Poll.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Socket_Poll.cpp.o -c /mnt/shares/DDServer/Socket_Poll.cpp

CMakeFiles/DDServer.dir/Socket_Poll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Socket_Poll.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Socket_Poll.cpp > CMakeFiles/DDServer.dir/Socket_Poll.cpp.i

CMakeFiles/DDServer.dir/Socket_Poll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Socket_Poll.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Socket_Poll.cpp -o CMakeFiles/DDServer.dir/Socket_Poll.cpp.s

CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.requires

CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.provides: CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.provides

CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.provides.build: CMakeFiles/DDServer.dir/Socket_Poll.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.provides.build

CMakeFiles/DDServer.dir/Thread.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/Thread.cpp.o: ../Thread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/Thread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/Thread.cpp.o -c /mnt/shares/DDServer/Thread.cpp

CMakeFiles/DDServer.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/Thread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/Thread.cpp > CMakeFiles/DDServer.dir/Thread.cpp.i

CMakeFiles/DDServer.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/Thread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/Thread.cpp -o CMakeFiles/DDServer.dir/Thread.cpp.s

CMakeFiles/DDServer.dir/Thread.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/Thread.cpp.o.requires

CMakeFiles/DDServer.dir/Thread.cpp.o.provides: CMakeFiles/DDServer.dir/Thread.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/Thread.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/Thread.cpp.o.provides

CMakeFiles/DDServer.dir/Thread.cpp.o.provides.build: CMakeFiles/DDServer.dir/Thread.cpp.o
.PHONY : CMakeFiles/DDServer.dir/Thread.cpp.o.provides.build

CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o: ../tinyxmlerror.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o -c /mnt/shares/DDServer/tinyxmlerror.cpp

CMakeFiles/DDServer.dir/tinyxmlerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/tinyxmlerror.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/tinyxmlerror.cpp > CMakeFiles/DDServer.dir/tinyxmlerror.cpp.i

CMakeFiles/DDServer.dir/tinyxmlerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/tinyxmlerror.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/tinyxmlerror.cpp -o CMakeFiles/DDServer.dir/tinyxmlerror.cpp.s

CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.requires

CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.provides: CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.provides

CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.provides.build: CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o
.PHONY : CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.provides.build

CMakeFiles/DDServer.dir/ServiceObj.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/ServiceObj.cpp.o: ../ServiceObj.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/ServiceObj.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/ServiceObj.cpp.o -c /mnt/shares/DDServer/ServiceObj.cpp

CMakeFiles/DDServer.dir/ServiceObj.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/ServiceObj.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/ServiceObj.cpp > CMakeFiles/DDServer.dir/ServiceObj.cpp.i

CMakeFiles/DDServer.dir/ServiceObj.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/ServiceObj.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/ServiceObj.cpp -o CMakeFiles/DDServer.dir/ServiceObj.cpp.s

CMakeFiles/DDServer.dir/ServiceObj.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/ServiceObj.cpp.o.requires

CMakeFiles/DDServer.dir/ServiceObj.cpp.o.provides: CMakeFiles/DDServer.dir/ServiceObj.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/ServiceObj.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/ServiceObj.cpp.o.provides

CMakeFiles/DDServer.dir/ServiceObj.cpp.o.provides.build: CMakeFiles/DDServer.dir/ServiceObj.cpp.o
.PHONY : CMakeFiles/DDServer.dir/ServiceObj.cpp.o.provides.build

CMakeFiles/DDServer.dir/OS_Buffer.cpp.o: CMakeFiles/DDServer.dir/flags.make
CMakeFiles/DDServer.dir/OS_Buffer.cpp.o: ../OS_Buffer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/shares/DDServer/debug/CMakeFiles $(CMAKE_PROGRESS_14)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/DDServer.dir/OS_Buffer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/DDServer.dir/OS_Buffer.cpp.o -c /mnt/shares/DDServer/OS_Buffer.cpp

CMakeFiles/DDServer.dir/OS_Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DDServer.dir/OS_Buffer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/shares/DDServer/OS_Buffer.cpp > CMakeFiles/DDServer.dir/OS_Buffer.cpp.i

CMakeFiles/DDServer.dir/OS_Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DDServer.dir/OS_Buffer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/shares/DDServer/OS_Buffer.cpp -o CMakeFiles/DDServer.dir/OS_Buffer.cpp.s

CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.requires:
.PHONY : CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.requires

CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.provides: CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/DDServer.dir/build.make CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.provides.build
.PHONY : CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.provides

CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.provides.build: CMakeFiles/DDServer.dir/OS_Buffer.cpp.o
.PHONY : CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.provides.build

# Object files for target DDServer
DDServer_OBJECTS = \
"CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o" \
"CMakeFiles/DDServer.dir/tinyxml.cpp.o" \
"CMakeFiles/DDServer.dir/Time_Value.cpp.o" \
"CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o" \
"CMakeFiles/DDServer.dir/server.cpp.o" \
"CMakeFiles/DDServer.dir/Stream.cpp.o" \
"CMakeFiles/DDServer.dir/Lua_C.cpp.o" \
"CMakeFiles/DDServer.dir/Block_Allocator.cpp.o" \
"CMakeFiles/DDServer.dir/tinystr.cpp.o" \
"CMakeFiles/DDServer.dir/Socket_Poll.cpp.o" \
"CMakeFiles/DDServer.dir/Thread.cpp.o" \
"CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o" \
"CMakeFiles/DDServer.dir/ServiceObj.cpp.o" \
"CMakeFiles/DDServer.dir/OS_Buffer.cpp.o"

# External object files for target DDServer
DDServer_EXTERNAL_OBJECTS =

DDServer: CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o
DDServer: CMakeFiles/DDServer.dir/tinyxml.cpp.o
DDServer: CMakeFiles/DDServer.dir/Time_Value.cpp.o
DDServer: CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o
DDServer: CMakeFiles/DDServer.dir/server.cpp.o
DDServer: CMakeFiles/DDServer.dir/Stream.cpp.o
DDServer: CMakeFiles/DDServer.dir/Lua_C.cpp.o
DDServer: CMakeFiles/DDServer.dir/Block_Allocator.cpp.o
DDServer: CMakeFiles/DDServer.dir/tinystr.cpp.o
DDServer: CMakeFiles/DDServer.dir/Socket_Poll.cpp.o
DDServer: CMakeFiles/DDServer.dir/Thread.cpp.o
DDServer: CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o
DDServer: CMakeFiles/DDServer.dir/ServiceObj.cpp.o
DDServer: CMakeFiles/DDServer.dir/OS_Buffer.cpp.o
DDServer: CMakeFiles/DDServer.dir/build.make
DDServer: CMakeFiles/DDServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable DDServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DDServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DDServer.dir/build: DDServer
.PHONY : CMakeFiles/DDServer.dir/build

CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/tinyxmlparser.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/tinyxml.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Time_Value.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Allocator_Manager.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/server.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Stream.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Lua_C.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Block_Allocator.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/tinystr.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Socket_Poll.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/Thread.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/tinyxmlerror.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/ServiceObj.cpp.o.requires
CMakeFiles/DDServer.dir/requires: CMakeFiles/DDServer.dir/OS_Buffer.cpp.o.requires
.PHONY : CMakeFiles/DDServer.dir/requires

CMakeFiles/DDServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DDServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DDServer.dir/clean

CMakeFiles/DDServer.dir/depend:
	cd /mnt/shares/DDServer/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/shares/DDServer /mnt/shares/DDServer /mnt/shares/DDServer/debug /mnt/shares/DDServer/debug /mnt/shares/DDServer/debug/CMakeFiles/DDServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DDServer.dir/depend

