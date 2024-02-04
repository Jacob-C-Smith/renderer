# Need CMake 3.28
cmake_minimum_required (VERSION 3.28)

# This is the name of the repository
project ("renderer")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif ()

add_compile_options(-gdwarf-4 -Wall -Wextra -Wpedantic -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference)

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the log module
if ( NOT "${HAS_LOG}")

    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the renderer module
if ( NOT "${HAS_RENDERER}")

    # Log
    message("[renderer] Adding renderer project")

    # Set the renderer include
    set(RENDERER_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the renderer project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_RENDERER true PARENT_SCOPE)
        set(RENDERER_INCLUDE_DIR ${RENDERER_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable (renderer_example "main.c")
add_dependencies(renderer_example renderer)
target_include_directories(renderer_example PUBLIC ${RENDERER_INCLUDE_DIR})
target_link_libraries(renderer_example renderer)

## Add source to the tester
add_executable (renderer_test "renderer_test.c")
add_dependencies(renderer_test renderer_test sync log)
target_include_directories(renderer_test PUBLIC ${RENDERER_INCLUDE_DIR} ${LOG_INCLUDE_DIR} ${SYNC_INCLUDE_DIR})
target_link_libraries(renderer_test renderer sync log)

# Add source to this project's library
add_library (renderer SHARED "integrator.c" "spectrum.c" "camera.c" "shape.c" "primitive.c" "sampler.c" "filter.c" "bxdf.c" "texture.c" "material.c" "medium.c" "light.c" "light_sampler.c")
add_dependencies(renderer sync)
target_include_directories(renderer PUBLIC ${RENDERER_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(renderer PUBLIC log sync)