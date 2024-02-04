# renderer CMake configuration file:
# This file is meant to be placed in a cmake subfolder of renderer-devel-2.x.y-VC
cmake_minimum_required(VERSION 3.26)

include(FeatureSummary)
set_package_properties(renderer PROPERTIES
    URL "https://www.g10.app/status#parser_serializer"
    DESCRIPTION "renderer parser/serializer"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(RENDERER_FOUND TRUE)

# For compatibility with autotools renderer-config.cmake, provide RENDERER_* variables.

set_and_check(RENDERER_PREFIX       "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(RENDERER_EXEC_PREFIX  "${CMAKE_CURRENT_LIST_DIR}/..")
set_and_check(RENDERER_INCLUDE_DIR  "${RENDERER_PREFIX}/include")
set(RENDERER_INCLUDE_DIRS           "${RENDERER_INCLUDE_DIR}")
set_and_check(RENDERER_BINDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")
set_and_check(RENDERER_LIBDIR       "${CMAKE_CURRENT_LIST_DIR}/../build/Debug/")

set(RENDERER_LIBRARIES renderer::renderer)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated renderer-target.cmake files.

set(_RENDERER_library     "${RENDERER_LIBDIR}/renderer.lib")
set(_RENDERER_dll_library "${RENDERER_BINDIR}/renderer.dll")
if(EXISTS "${_RENDERER_library}" AND EXISTS "${_RENDERER_dll_library}")
    if(NOT TARGET renderer::renderer)
        add_library(renderer::renderer SHARED IMPORTED)
        set_target_properties(renderer::renderer
            PROPERTIES
                INTERFACE_INCLUDE_DIRECTORIES "${RENDERER_INCLUDE_DIRS}"
                IMPORTED_IMPLIB "${_RENDERER_library}"
                IMPORTED_LOCATION "${_RENDERER_dll_library}"
                COMPATIBLE_INTERFACE_BOOL "RENDERER_SHARED"
                INTERFACE_RENDERER_SHARED "ON"
        )
    endif()
    set(RENDERER_RENDERER_FOUND TRUE)
else()
    set(RENDERER_RENDERER_FOUND FALSE)
endif()
unset(_RENDERER_library)
unset(_RENDERER_dll_library)

check_required_components(renderer)
