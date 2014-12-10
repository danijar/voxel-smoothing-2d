# SFML
cmake_minimum_required(VERSION 2.8.8)
include(ExternalProject)

# Download, configure, build and install
ExternalProject_Add(SFML
	# DEPENDS
	PREFIX         ${CMAKE_SOURCE_DIR}
	TMP_DIR        ${CMAKE_SOURCE_DIR}/temp
	STAMP_DIR      ${CMAKE_SOURCE_DIR}/stamp
	#--Download step--------------
	DOWNLOAD_DIR   ${CMAKE_SOURCE_DIR}/source
	GIT_REPOSITORY https://github.com/LaurentGomila/SFML.git
	GIT_TAG        e257909
	#--Update/Patch step----------
	UPDATE_COMMAND ""
	#--Configure step-------------
	SOURCE_DIR     ${CMAKE_SOURCE_DIR}/source
	CMAKE_ARGS     -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/install
	               -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
	               -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
	               -DSFML_USE_STATIC_STD_LIBS=${USE_STATIC_STD_LIBS}
	#--Build step-----------------
	BINARY_DIR     ${CMAKE_SOURCE_DIR}/build
	#--Install step---------------
	INSTALL_DIR    ${CMAKE_SOURCE_DIR}/install
)
