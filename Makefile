# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/karim/src/iptv_rest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/karim/src/iptv_rest

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/karim/src/iptv_rest/CMakeFiles /home/karim/src/iptv_rest/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/karim/src/iptv_rest/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named copy

# Build rule for target.
copy: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 copy
.PHONY : copy

# fast build rule for target.
copy/fast:
	$(MAKE) -f CMakeFiles/copy.dir/build.make CMakeFiles/copy.dir/build
.PHONY : copy/fast

#=============================================================================
# Target rules for targets named iptv_api

# Build rule for target.
iptv_api: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 iptv_api
.PHONY : iptv_api

# fast build rule for target.
iptv_api/fast:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/build
.PHONY : iptv_api/fast

src/hardware.o: src/hardware.cpp.o

.PHONY : src/hardware.o

# target to build an object file
src/hardware.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/hardware.cpp.o
.PHONY : src/hardware.cpp.o

src/hardware.i: src/hardware.cpp.i

.PHONY : src/hardware.i

# target to preprocess a source file
src/hardware.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/hardware.cpp.i
.PHONY : src/hardware.cpp.i

src/hardware.s: src/hardware.cpp.s

.PHONY : src/hardware.s

# target to generate assembly for a file
src/hardware.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/hardware.cpp.s
.PHONY : src/hardware.cpp.s

src/launcher.o: src/launcher.cpp.o

.PHONY : src/launcher.o

# target to build an object file
src/launcher.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/launcher.cpp.o
.PHONY : src/launcher.cpp.o

src/launcher.i: src/launcher.cpp.i

.PHONY : src/launcher.i

# target to preprocess a source file
src/launcher.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/launcher.cpp.i
.PHONY : src/launcher.cpp.i

src/launcher.s: src/launcher.cpp.s

.PHONY : src/launcher.s

# target to generate assembly for a file
src/launcher.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/launcher.cpp.s
.PHONY : src/launcher.cpp.s

src/live.o: src/live.cpp.o

.PHONY : src/live.o

# target to build an object file
src/live.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/live.cpp.o
.PHONY : src/live.cpp.o

src/live.i: src/live.cpp.i

.PHONY : src/live.i

# target to preprocess a source file
src/live.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/live.cpp.i
.PHONY : src/live.cpp.i

src/live.s: src/live.cpp.s

.PHONY : src/live.s

# target to generate assembly for a file
src/live.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/live.cpp.s
.PHONY : src/live.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/mongo_driver.o: src/mongo_driver.cpp.o

.PHONY : src/mongo_driver.o

# target to build an object file
src/mongo_driver.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/mongo_driver.cpp.o
.PHONY : src/mongo_driver.cpp.o

src/mongo_driver.i: src/mongo_driver.cpp.i

.PHONY : src/mongo_driver.i

# target to preprocess a source file
src/mongo_driver.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/mongo_driver.cpp.i
.PHONY : src/mongo_driver.cpp.i

src/mongo_driver.s: src/mongo_driver.cpp.s

.PHONY : src/mongo_driver.s

# target to generate assembly for a file
src/mongo_driver.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/mongo_driver.cpp.s
.PHONY : src/mongo_driver.cpp.s

src/report.o: src/report.cpp.o

.PHONY : src/report.o

# target to build an object file
src/report.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/report.cpp.o
.PHONY : src/report.cpp.o

src/report.i: src/report.cpp.i

.PHONY : src/report.i

# target to preprocess a source file
src/report.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/report.cpp.i
.PHONY : src/report.cpp.i

src/report.s: src/report.cpp.s

.PHONY : src/report.s

# target to generate assembly for a file
src/report.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/report.cpp.s
.PHONY : src/report.cpp.s

src/status.o: src/status.cpp.o

.PHONY : src/status.o

# target to build an object file
src/status.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/status.cpp.o
.PHONY : src/status.cpp.o

src/status.i: src/status.cpp.i

.PHONY : src/status.i

# target to preprocess a source file
src/status.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/status.cpp.i
.PHONY : src/status.cpp.i

src/status.s: src/status.cpp.s

.PHONY : src/status.s

# target to generate assembly for a file
src/status.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/status.cpp.s
.PHONY : src/status.cpp.s

src/storage.o: src/storage.cpp.o

.PHONY : src/storage.o

# target to build an object file
src/storage.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/storage.cpp.o
.PHONY : src/storage.cpp.o

src/storage.i: src/storage.cpp.i

.PHONY : src/storage.i

# target to preprocess a source file
src/storage.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/storage.cpp.i
.PHONY : src/storage.cpp.i

src/storage.s: src/storage.cpp.s

.PHONY : src/storage.s

# target to generate assembly for a file
src/storage.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/storage.cpp.s
.PHONY : src/storage.cpp.s

src/system.o: src/system.cpp.o

.PHONY : src/system.o

# target to build an object file
src/system.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/system.cpp.o
.PHONY : src/system.cpp.o

src/system.i: src/system.cpp.i

.PHONY : src/system.i

# target to preprocess a source file
src/system.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/system.cpp.i
.PHONY : src/system.cpp.i

src/system.s: src/system.cpp.s

.PHONY : src/system.s

# target to generate assembly for a file
src/system.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/system.cpp.s
.PHONY : src/system.cpp.s

src/users.o: src/users.cpp.o

.PHONY : src/users.o

# target to build an object file
src/users.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/users.cpp.o
.PHONY : src/users.cpp.o

src/users.i: src/users.cpp.i

.PHONY : src/users.i

# target to preprocess a source file
src/users.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/users.cpp.i
.PHONY : src/users.cpp.i

src/users.s: src/users.cpp.s

.PHONY : src/users.s

# target to generate assembly for a file
src/users.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/users.cpp.s
.PHONY : src/users.cpp.s

src/util.o: src/util.cpp.o

.PHONY : src/util.o

# target to build an object file
src/util.cpp.o:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/util.cpp.o
.PHONY : src/util.cpp.o

src/util.i: src/util.cpp.i

.PHONY : src/util.i

# target to preprocess a source file
src/util.cpp.i:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/util.cpp.i
.PHONY : src/util.cpp.i

src/util.s: src/util.cpp.s

.PHONY : src/util.s

# target to generate assembly for a file
src/util.cpp.s:
	$(MAKE) -f CMakeFiles/iptv_api.dir/build.make CMakeFiles/iptv_api.dir/src/util.cpp.s
.PHONY : src/util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... copy"
	@echo "... iptv_api"
	@echo "... src/hardware.o"
	@echo "... src/hardware.i"
	@echo "... src/hardware.s"
	@echo "... src/launcher.o"
	@echo "... src/launcher.i"
	@echo "... src/launcher.s"
	@echo "... src/live.o"
	@echo "... src/live.i"
	@echo "... src/live.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/mongo_driver.o"
	@echo "... src/mongo_driver.i"
	@echo "... src/mongo_driver.s"
	@echo "... src/report.o"
	@echo "... src/report.i"
	@echo "... src/report.s"
	@echo "... src/status.o"
	@echo "... src/status.i"
	@echo "... src/status.s"
	@echo "... src/storage.o"
	@echo "... src/storage.i"
	@echo "... src/storage.s"
	@echo "... src/system.o"
	@echo "... src/system.i"
	@echo "... src/system.s"
	@echo "... src/users.o"
	@echo "... src/users.i"
	@echo "... src/users.s"
	@echo "... src/util.o"
	@echo "... src/util.i"
	@echo "... src/util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

