# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/cmake/1210/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1210/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/furich/QTProjects/Client-Server-Chat/Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug

# Include any dependencies generated for this target.
include CMakeFiles/Server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Server.dir/flags.make

CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: Server_autogen/mocs_compilation.cpp
CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o -MF CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o -c /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/Server_autogen/mocs_compilation.cpp

CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/Server_autogen/mocs_compilation.cpp > CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i

CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/Server_autogen/mocs_compilation.cpp -o CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s

CMakeFiles/Server.dir/main.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/main.cpp.o: /home/furich/QTProjects/Client-Server-Chat/Server/main.cpp
CMakeFiles/Server.dir/main.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Server.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/main.cpp.o -MF CMakeFiles/Server.dir/main.cpp.o.d -o CMakeFiles/Server.dir/main.cpp.o -c /home/furich/QTProjects/Client-Server-Chat/Server/main.cpp

CMakeFiles/Server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/furich/QTProjects/Client-Server-Chat/Server/main.cpp > CMakeFiles/Server.dir/main.cpp.i

CMakeFiles/Server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/furich/QTProjects/Client-Server-Chat/Server/main.cpp -o CMakeFiles/Server.dir/main.cpp.s

CMakeFiles/Server.dir/server.cpp.o: CMakeFiles/Server.dir/flags.make
CMakeFiles/Server.dir/server.cpp.o: /home/furich/QTProjects/Client-Server-Chat/Server/server.cpp
CMakeFiles/Server.dir/server.cpp.o: CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Server.dir/server.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Server.dir/server.cpp.o -MF CMakeFiles/Server.dir/server.cpp.o.d -o CMakeFiles/Server.dir/server.cpp.o -c /home/furich/QTProjects/Client-Server-Chat/Server/server.cpp

CMakeFiles/Server.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/server.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/furich/QTProjects/Client-Server-Chat/Server/server.cpp > CMakeFiles/Server.dir/server.cpp.i

CMakeFiles/Server.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/server.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/furich/QTProjects/Client-Server-Chat/Server/server.cpp -o CMakeFiles/Server.dir/server.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/Server.dir/main.cpp.o" \
"CMakeFiles/Server.dir/server.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server: CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o
Server: CMakeFiles/Server.dir/main.cpp.o
Server: CMakeFiles/Server.dir/server.cpp.o
Server: CMakeFiles/Server.dir/build.make
Server: /home/furich/Qt5.12.12/5.12.12/gcc_64/lib/libQt5Network.so.5.12.12
Server: /home/furich/Qt5.12.12/5.12.12/gcc_64/lib/libQt5Core.so.5.12.12
Server: CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Server.dir/build: Server
.PHONY : CMakeFiles/Server.dir/build

CMakeFiles/Server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Server.dir/clean

CMakeFiles/Server.dir/depend:
	cd /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/furich/QTProjects/Client-Server-Chat/Server /home/furich/QTProjects/Client-Server-Chat/Server /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug /home/furich/QTProjects/Client-Server-Chat/build-Server-Desktop_Qt_5_12_12_GCC_64bit-Debug/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Server.dir/depend
