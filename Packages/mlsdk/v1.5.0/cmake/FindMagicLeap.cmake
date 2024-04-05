# Copyright 2021 (c) Magic Leap Inc.

#[=======================================================================[.rst:
FindMagicLeap
-------

ToDO:
  [1] Adapt this script to work for Android Studio workflow.

Finds the MagicLeap library.


Inputs:
-------


MLSDK = path to the top level installation directory of the
                    MagicLeap SDK.

MAGICLEAP_APP_FRAMEWORK_ROOT  = path to the top level installation directory of the
                    App Framework.

Outputs:
--------

ML_TARGET = operating system we are targetting.
CMAKE_MODULE_PATH is appended with location of APP_FRAMEWORK if found.

Setups the interfaces for the Magic Leap public libraries, examples
are graphics.magicleap, perception.magicleap and input.magicleap. Full list
can be seen below.

#]=======================================================================]

if (MagicLeap_FOUND)
  return()
endif()

project(ML)

# Target Selection
if (WIN32)
  set (ML_TARGET "win")
  add_definitions(-DML_WINDOWS)
endif()
if (ANDROID)
  set (ML_TARGET "ml2")
  add_definitions(-DML_LUMIN)
  set (LUMIN ON CACHE INTERNAL "Use LUMIN switch of ANDROID in lumin CMAKE" FORCE)
else()
  if (UNIX)
    if (APPLE)
      set (ML_TARGET "osx")
      add_definitions(-DML_OSX)
      set(CMAKE_OSX_DEPLOYMENT_TARGET 10.12)
    else()
      set (ML_TARGET "linux")
      add_definitions(-DML_LINUX)
    endif()
    # ZI overrides the ML API libraries at runtime; don't find the stubs
    set(CMAKE_SKIP_RPATH TRUE)
  endif()
endif()

##################################################################
#
# Check C-API
#
##################################################################

file(TO_CMAKE_PATH "$ENV{MAGICLEAP_APP_FRAMEWORK_ROOT}" MAGICLEAP_APP_FRAMEWORK_ROOT)

set(ML_SDK_ROOT "${CMAKE_CURRENT_LIST_DIR}/..")

# Test if the API is indeed here.
if(NOT EXISTS "${ML_SDK_ROOT}/include/ml_api.h")
  message(FATAL_ERROR "FindMagicLeap: Unable to find C-API.")
endif()

set(ML_FOUND "TRUE")
set(ML_SDK_TARGET "${ML_SDK_ROOT}")
set(ML_SDK_LIBRARY_PATH "${ML_SDK_ROOT}/lib/${ML_TARGET}")
set(ML_SDK_INCLUDE_PATH "${ML_SDK_ROOT}/include")

message("Found MagicLeap SDK at ${ML_SDK_ROOT}")
message(VERBOSE "MagicLeap Library path = ${ML_SDK_LIBRARY_PATH}")
message(VERBOSE "MagicLeap Include path = ${ML_SDK_INCLUDE_PATH}")

##################################################################
#
# AppFramework Hints.
#
##################################################################
#
# This is here as a convenience so that find_package(MagicLeapAppFramework)
# can work without further configuration.
#
include(AppFrameworkLocator)

# ************************************************************************
#
# Interface definition.
#
# ************************************************************************
add_library(base.magicleap INTERFACE)
target_include_directories(base.magicleap
    INTERFACE
    ${ML_SDK_INCLUDE_PATH}
)

target_link_directories(base.magicleap
    INTERFACE
    ${ML_SDK_LIBRARY_PATH}
)

# Suppress the flexible array warning in Visual Studio.
target_compile_options(base.magicleap
  INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/wd4200>
)

set(ml_libs
  "audio"
  "camera_metadata"
  "camera"
  "capi"
  "graphics"
  "graphics_utils"
  "input"
  "license"
  "media_ccparser"
  "media_cea708parser"
  "media_codec"
  "media_codeclist"
  "media_crypto"
  "media_drm"
  "media_error"
  "media_extractor"
  "media_format"
  "media_muxer"
  "media_player"
  "media_recorder"
  "native_surface"
  "perception"
  "space"
  "platform"
  "power_manager"
  "system_notification_manager"
  "webview"
  "webrtc"
)

foreach(lib ${ml_libs})
  add_library("${lib}.magicleap" INTERFACE)
  add_library(ML::${lib} ALIAS "${lib}.magicleap")
  target_link_libraries("${lib}.magicleap"
      INTERFACE
      base.magicleap
      $<IF:$<STREQUAL:${ML_TARGET},win>,${lib}.magicleap.lib,-l${lib}.magicleap>
  )
endforeach()

unset(ML_SDK_ROOT)
unset(ML_FOUND)
unset(ML_SDK_TARGET)
unset(ML_SDK_LIBRARY_PATH)
unset(ML_SDK_INCLUDE_PATH)

set(MagicLeap_FOUND TRUE)
