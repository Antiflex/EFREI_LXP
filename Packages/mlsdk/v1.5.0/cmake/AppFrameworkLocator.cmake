# Copyright 2022 (c) Magic Leap Inc.

#[=======================================================================[.rst:
AppFrameworkLocator.cmake
-------

Attempts to locate the Magic Leap AppFramework

MAGICLEAP_APP_FRAMEWORK_ROOT = path to the top level installation directory of the
                    App Framework. (optional)

This is here as a convenience so that find_package(MagicLeapAppFramework)
can work without further configuration.

Possible locations for app framework relative to your application:

1. Anywhere up from the location of the application's CMakeLists.txt in
   a directory named app_framework
2. Anywhere up from the location of the application's CMakeLists.txt in
   a directory named /sdk_native_samples_src/app_framework

Or not relative but directly configured:

1. Using the environment variable: MAGICLEAP_APP_FRAMEWORK_ROOT
2. Using the CMAKE_MODULE_PATH search path

This will detect the pre-built framework as well as the
build dependency installation. The order of detection is as follows:

1. First search the CMake Module path
2. Next check the environment variable "MAGICLEAP_APP_FRAMEWORK_ROOT"
3. Next walk up the tree
  a. Check if the directory has a pre-built app_framework. (Use if found)
  b. Check if the directory holds the app_framwork source code. (Use if found)

An example of directory layout that can be detected automatically:

top --+---sdk_native_samples_src
      |       |
      |       +-- app_framework
      |       +-- samples
      |       +-- scripts
      |
      +---your_c_api_application


or alternatively

top --+---app_framework (as taken from the sdk_native_samples_src)
      |
      +---your_c_api_application


#]=======================================================================]

function(find_app_framework result)
    # App framework search paths
    set(DIR_NAME_LIST
        "app_framework"
        "sdk_native_samples_src/app_framework"
    )

    set(POST_FIX_LIST
        "build/install/cmake"
        "cmake"
    )

    set(UP "/..")
    set(SEARCH "${CMAKE_CURRENT_SOURCE_DIR}")
    MATH(EXPR index "0")
    while( IS_DIRECTORY "${SEARCH}${UP}")

        MATH(EXPR index "${index}+1")
        # Bail after 20 tries,.. surely that's sufficient.
        if (${index} GREATER 20)
            return()
        endif()
        set(OLD "${SEARCH}")
        set(SEARCH "${SEARCH}${UP}")
        get_filename_component(SEARCH "${SEARCH}" ABSOLUTE)

        if ( "${OLD}" STREQUAL "${SEARCH}" )
            return()
        endif()

        foreach(DIR_NAME IN LISTS DIR_NAME_LIST)
            foreach(POST_FIX IN LISTS POST_FIX_LIST)
                set(P "${SEARCH}/${DIR_NAME}/${POST_FIX}/")
                if ( EXISTS "${P}/FindMagicLeapAppFramework.cmake" )
                    set(${result} "${P}" PARENT_SCOPE)
                    return()
                endif()
            endforeach()
        endforeach()

    endwhile()

endfunction()

# Check the module path first.
foreach(DIR_NAME IN LISTS CMAKE_MODULE_PATH)
    if ( EXISTS "${DIR_NAME}/FindMagicLeapAppFramework.cmake")
        message("Found MagicLeap AppFramework at ${DIR_NAME}")
        return()
    endif()
endforeach()

# Not in module path, check the environment variable
if ( EXISTS "${MAGICLEAP_APP_FRAMEWORK_ROOT}/cmake/FindMagicLeapAppFramework.cmake")
  list(APPEND CMAKE_MODULE_PATH "${MAGICLEAP_APP_FRAMEWORK_ROOT}/cmake")
  message("Found MagicLeap AppFramework at ${MAGICLEAP_APP_FRAMEWORK_ROOT}")
else()
  # Not in module path, not in environment variable,
  # start hunting...
  find_app_framework(app_framework)
  if ( EXISTS "${app_framework}" )
      list(APPEND CMAKE_MODULE_PATH ${app_framework})
      message("Found MagicLeap AppFramework at ${app_framework}")
  endif()
  unset(app_framework)
endif()

