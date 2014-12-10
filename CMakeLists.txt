################################################################
# General
################################################################

# CMake version
cmake_minimum_required(VERSION 2.8.8)

# Declare project name
project(SFML_APP)

# Version information
set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 0)

# Include scripts
set(CMAKE_MODULE_PATH cmake ${CMAKE_MODULE_PATH})
include(ExternalProject)

################################################################
# Configure tool chain
################################################################

# Enable modern C++ features
if (UNIX OR MINGW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
endif()

# Build variants, default to release
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING
	"Whether to build Debug or Release builds." FORCE)

# Library linkage, default to static
if (UNIX)
	set(BUILD_SHARED_LIBS TRUE CACHE BOOL "")
else()
	set(BUILD_SHARED_LIBS FALSE CACHE BOOL "")
endif()
set(BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS} CACHE BOOL
	"Whether to build static or dynamic libraries." FORCE)

# Runtime linkage, default to static
if (BUILD_SHARED_LIBS)
	set(USE_STATIC_STD_LIBS FALSE CACHE BOOL "")
else()
	set(USE_STATIC_STD_LIBS TRUE CACHE BOOL "")
endif()
set(USE_STATIC_STD_LIBS ${USE_STATIC_STD_LIBS} CACHE BOOL
	"Whether to use statically or dynamically link to the runtime library." FORCE)
if (USE_STATIC_STD_LIBS)
	if (UNIX OR MINGW)
		set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
	elseif (MSVC)
		set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
	else()
		message(ERROR "Unsupported compiler.")
	endif()
endif()

# Find correct file extension for libraries
if (UNIX)
	if (BUILD_SHARED_LIBS)
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
	else()
		set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
	endif()
endif()

# Linkage options are mutually exclusive
if (BUILD_SHARED_LIBS AND USE_STATIC_STD_LIBS)
	message(FATAL_ERROR "Can't link libraries dynamically but runtime "
		"statically. BUILD_SHARED_LIBS and USE_STATIC_STD_LIBS are mutually "
		"exclusive.")
endif()

################################################################
# External settings
################################################################

# Make GIT_EXECUTABLE show up in the graphical user interface
set(GIT_EXECUTABLE "git" CACHE FILEPATH "")
set(GIT_EXECUTABLE ${GIT_EXECUTABLE} CACHE FILEPATH
	"Path to the git executable used to download dependencies." FORCE)

################################################################
# Project and test target
################################################################

# create_target(<name> [directories...])
# Create executable from all code inside the given directories
function(create_target NAME)
	set(HEADERS)
	set(SOURCES)
	# Collect files inside project directories
	foreach(ROOT ${ARGV})
		file(GLOB_RECURSE HEADERS_CURRENT ${ROOT}/*.hpp ${ROOT}/*.inl)
		file(GLOB_RECURSE SOURCES_CURRENT ${ROOT}/*.cpp)
		list(APPEND HEADERS ${HEADERS_CURRENT})
		list(APPEND SOURCES ${SOURCES_CURRENT})
		include_directories(${ROOT})
	endforeach()
	# Add the collected files and add root as include directory
	add_executable(${NAME} ${HEADERS} ${SOURCES})
	# Display status message
	list(LENGTH HEADERS HEADERS_COUNT)
	list(LENGTH SOURCES SOURCES_COUNT)
	message(STATUS "Added project " ${NAME} " with " ${HEADERS_COUNT} " "
		"headers and " ${SOURCES_COUNT} " source files.")
endfunction()

# Use function above
create_target(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/src)

################################################################
# Library dependencies
################################################################

# Add another project and build it at configure time
function(add_subdirectory_and_build DIRECTORY)
	# Configure project
	exec_program(${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR}/external/${DIRECTORY} ARGS
		-G\"${CMAKE_GENERATOR}\"
		-DCMAKE_CONFIGURATION_TYPES:STRING="Debug\;Release"
		-DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
		-DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}
		-DUSE_STATIC_STD_LIBS:BOOL=${USE_STATIC_STD_LIBS}
		-DGIT_EXECUTABLE:FILEPATH=${GIT_EXECUTABLE})
	# Force build at compile time
	exec_program(${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR}/external/${DIRECTORY} ARGS
		--build .
		--config ${CMAKE_BUILD_TYPE})
	# Clean up CMake files
	# ...
endfunction()

# Use function above
add_subdirectory_and_build(sfml)
add_subdirectory_and_build(glm)

# Find and include headers and binaries of dependencies that match the
# configuration and link them against the requiring targets
include(UseSFML)
include(UseGLM)
use_sfml(${PROJECT_NAME})
use_glm(${PROJECT_NAME})
