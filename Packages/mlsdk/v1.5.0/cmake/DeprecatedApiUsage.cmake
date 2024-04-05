# Copyright 2023 (c) Magic Leap Inc.

#[=======================================================================[.rst:
DeprecatedApiUsage.cmake
-------

Adds new command for building sample/test apps using deprecated C-API.


Inputs:
-------

CMAKE_CXX_COMPILER_ID

Outputs:
--------

use_deprecated_api command, that will let You compile app even when using
deprecated C-API.

#]=======================================================================]

if (COMMAND use_deprecated_api)
  return()
endif()

macro(use_deprecated_api target)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${target} PUBLIC -w34996)
else()
  target_compile_options(${target} PUBLIC -Wno-error=deprecated-declarations)
endif()
endmacro()
