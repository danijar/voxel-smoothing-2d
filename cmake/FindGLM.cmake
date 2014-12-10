# - Find GLM
# Find the GLM include and library
#
#  GLM_INCLUDE_DIR - The include directory
#  GLM_FOUND       - True if GLM has been found

find_path(GLM_INCLUDE_DIR
	glm/glm.hpp
	HINTS ${GLM_ROOT}
	PATH_SUFFIXES
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)

mark_as_advanced(GLM_INCLUDE_DIR)
