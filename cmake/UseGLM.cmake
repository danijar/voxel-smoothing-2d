# CMake version
cmake_minimum_required(VERSION 2.8.8)

# use_glm([targets...])
# Try to find GLM add it as the include directoy
function(use_glm)
	# GLM
	set(GLM_ROOT ${CMAKE_SOURCE_DIR}/external/glm/install CACHE FILEPATH "")
	set(GLM_ROOT ${GLM_ROOT} CACHE FILEPATH "Path to GLM installation." FORCE)

	# Find package and include headers and libraries
	find_package(GLM)
	if (GLM_FOUND)
		include_directories(${GLM_INCLUDE_DIR})
		message(STATUS "Found dependency GLM at " ${GLM_ROOT} ".")
	else()
		message(SEND_ERROR "Dependency GLM not found. Please set GLM_ROOT to "
			"the installation directory.")
	endif()
endfunction()
