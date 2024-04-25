cmake_minimum_required(VERSION 3.0)
project(MacJS9)

project(quickjs LANGUAGES C CXX)

# compile flags
set(COMPILE_FLAGS -Wall -MMD -Wno-array-bounds -Wno-format-truncation)

add_compile_options(${COMPILE_FLAGS})
add_compile_definitions(
    _GNU_SOURCE
    CONFIG_BIGNUM
    CONFIG_VERSION=${QUICKJS_VERSION}
    CONFIG_AGENT=0
)

set(QJSC_CONFIG -DCONFIG_PREFIX="/usr/local" -DCONFIG_LTO)
set(QJSC_EXE "${EXECUTABLE_OUTPUT_PATH}/qjsc")
set(QJS_CONFIG ${QJSC_CONFIG} -DCONFIG_CC="clang")

#set(QJS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/vendored/quickjs")
#set(QJS_FILE "${QJS_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}quickjs${CMAKE_STATIC_LIBRARY_SUFFIX}")

#add_custom_target(BuildQuickJS ALL COMMAND make WORKING_DIRECTORY ${QJS_PATH})
#add_library(QuickJS STATIC IMPORTED)
#set_property(TARGET QuickJS PROPERTY IMPORTED_LOCATION ${QJS_FILE})
#add_dependencies(QuickJS BuildQuickJS) # So that anyone linking against QuickJS causes BuildQuickJS to build first

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources 
    vendored/quickjs/cutils.c
    vendored/quickjs/libunicode.c
    vendored/quickjs/libregexp.c
    vendored/quickjs/libbf.c
    vendored/quickjs/quickjs.c     
    
    src/**/**/**/*.c src/**/**/**/*.h src/**/**/**/*.cpp src/**/**/**/*.hpp 
    src/**/**/*.c src/**/**/*.h src/**/**/*.cpp src/**/**/*.hpp 
    src/**/*.c src/**/*.h src/**/*.cpp src/**/*.hpp 
    src/*.c src/*.h src/*.cpp src/*.hpp
)
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

set_target_properties(MacJS9 PROPERTIES COMPILE_OPTIONS -ffunction-sections)
#target_link_libraries(MacJS9 "${RETRO68_ROOT}/InterfaceAndLibraries/Libraries/StubLibraries/ThreadsLib")

target_link_libraries( MacJS9 ThreadsLib)

if(CMAKE_SYSTEM_NAME MATCHES Retro68)
    set_target_properties(MacJS9 PROPERTIES LINK_FLAGS "-Wl,--mac-strip-macsbug")
endif()

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
file(COPY ${data} DESTINATION resources)