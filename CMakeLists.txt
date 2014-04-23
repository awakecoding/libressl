cmake_minimum_required(VERSION 2.6)

project(LibreSSL C)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_SUPPRESS_REGENERATION ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(TestBigEndian)
include(GNUInstallDirs)
include(CheckIncludeFiles)
include(CheckLibraryExists)
include(CheckCCompilerFlag)
include(CheckStructHasMember)
include(CMakeDetermineSystem)
include(FindPackageHandleStandardArgs)

# Force out of source build
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BINARY_DIR}" _in_source_build)
if(_in_source_build)
	message(SEND_ERROR "LibreSSL requires an out of source build. Please create a new directory and run cmake /path/to/libressl [options] from there. For instance: mkdir build && cd build && cmake ..")
	message(FATAL_ERROR "Clear the cache by removing the CMakeCache.txt file in ${CMAKE_SOURCE_DIR} first.")
endif(_in_source_build)

find_package(Perl)

if(WIN32)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
	set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
endif(WIN32)

if(MSVC)
	set(CMAKE_C_FLAGS "/DWIN32 /D_WIN32 /D_WINDOWS /W3 /GR /EHsc")
	set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
	set(CMAKE_C_FLAGS_RELEASE "/MT /O2 /Ob2 /DNDEBUG")
endif(MSVC)

# Silence "warning: ‘__bounded__’ attribute directive ignored [-Wattributes]" for now
check_c_compiler_flag(-Wno-attributes Wno-attributes)
if(Wno-attributes)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-attributes")
endif(Wno-attributes)

add_subdirectory(ssl)
