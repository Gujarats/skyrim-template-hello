cmake_minimum_required(VERSION 3.22)
message("Using toolchain file ${CMAKE_TOOLCHAIN_FILE}.")

project(
	SKyrimTemplateHello
	VERSION 0.0.1
	LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Enable for 1130 changes
set(ENABLE_SKYRIMAE1130 OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)
set(CMAKE_OPTIMIZE_DEPENDENCIES ON)
set(SKSE_SUPPORT_XBYAK ON)
set(ENABLE_SKYRIM_VR OFF)
set(BUILD_TESTS OFF)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()


#find_package(binary_io REQUIRED CONFIG)
#find_package(Boost MODULE REQUIRED)
#find_package(spdlog REQUIRED CONFIG)
#find_package(CommonLibSSE CONFIG REQUIRED)
#message("Find packages completed.")

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "in-source builds are not allowed")
endif()

#macro(set_from_environment VARIABLE)
#	if(NOT DEFINED ${VARIABLE} AND DEFINED ENV{${VARIABLE}})
#		set(${VARIABLE} $ENV{${VARIABLE}})
#	endif()
#endmacro()

#set_from_environment(CompiledPluginsPath)
#if(NOT DEFINED CompiledPluginsPath)
#	message(FATAL_ERROR "CompiledPluginsPath is not set")
#endif()

# If you're using Mod Organizer 2 or Vortex, you might want this to go inside
# of your "mods" folder, inside of a subfolder named "<your mod>".
#
# To do this automatically, set the `SKYRIM_MODS_FOLDER` environment variable
# to the path of your "mods" folder
if(DEFINED ENV{SKYRIM_MODS_FOLDER} AND IS_DIRECTORY "$ENV{SKYRIM_MODS_FOLDER}")
    set(OUTPUT_FOLDER "$ENV{SKYRIM_MODS_FOLDER}/${PROJECT_NAME}")
endif()

# Setup your SKSE plugin as an SKSE plugin!
#add_commonlibsse_plugin(${PROJECT_NAME} SOURCES "src/bin/main.cpp") # <--- specifies plugin.cpp
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23) # <--- use C++23 standard
#target_precompile_headers(${PROJECT_NAME} PRIVATE "src/PCH.h") # <--- PCH.h is required!
#message("compile source & libs added.")

# When your SKSE .dll is compiled, this will automatically copy the .dll into your mods folder.
# Only works if you configure DEPLOY_ROOT above (or set the SKYRIM_MODS_FOLDER environment variable)
if(DEFINED OUTPUT_FOLDER)
    # If you specify an <OUTPUT_FOLDER> (including via environment variables)
    # then we'll copy your mod files into Skyrim or a mod manager for you!

    # Copy the SKSE plugin .dll files into the SKSE/Plugins/ folder
    set(DLL_FOLDER "${OUTPUT_FOLDER}/SKSE/Plugins")

    message(STATUS "SKSE plugin output folder: ${DLL_FOLDER}")

    add_custom_command(
        TARGET "${PROJECT_NAME}"
        POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${DLL_FOLDER}"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        VERBATIM
    )

    # If you perform a "Debug" build, also copy .pdb file (for debug symbols)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(
            TARGET "${PROJECT_NAME}"
            POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_PDB_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/$<TARGET_PDB_FILE_NAME:${PROJECT_NAME}>"
            VERBATIM
        )
    endif()
endif()
message("Output folder is set!.")

message("Adding subdir cmake to the project")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
add_subdirectory(src)
include(cmake/packaging.cmake)
message("Subdir cmake added")



