cmake_minimum_required(VERSION 3.0)
project(MacJS9)

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources      src/*.c src/*.h src/*.cpp src/*.hpp)
file(GLOB_RECURSE data resources/*)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
if(CMAKE_SYSTEM_NAME MATCHES Retro)
    add_application(MacJS9 ${sources} ${data} CONSOLE)
else()
    add_executable(MacJS9 ${sources} ${data})
endif()
# just for MacJS9 add some compiler flags
target_compile_options(MacJS9 PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# this lets me include files relative to the root source directory with a <> pair
target_include_directories(MacJS9 PUBLIC src/main)



set_target_properties(MacJS9 PROPERTIES COMPILE_OPTIONS -ffunction-sections)
if(CMAKE_SYSTEM_NAME MATCHES Retro68)
    set_target_properties(MacJS9 PROPERTIES LINK_FLAGS "-Wl,-gc-sections -Wl,--mac-strip-macsbug")
else()
    set_target_properties(MacJS9 PROPERTIES LINK_FLAGS "-Wl,-gc-sections")
endif()

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
file(COPY ${data} DESTINATION resources)