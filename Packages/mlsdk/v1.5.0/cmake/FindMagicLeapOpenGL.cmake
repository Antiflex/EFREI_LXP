# Copyright 2021 (c) Magic Leap Inc.

#[=======================================================================[.rst:
FindMagicLeapOpenGL
-------

Sets up the OpenGL interface libary.

Inputs:
-------

none

Outputs:
--------

gl.magicleap

#]=======================================================================]
find_package(MagicLeap REQUIRED)

if (FindMagicLeapOpenGL_FOUND)
  return()
endif()

add_library( gl.magicleap INTERFACE)

if(ML_TARGET STREQUAL ml2)


    find_path(GLES3_INCLUDE_DIR GLES3/gl3.h HINTS ${ANDROID_NDK})
    find_library(GLES3_LIBRARY libGLESv3.so HINTS ${GLES3_INCLUDE_DIR}/../lib)
    find_library(EGL_LIBRARY libEGL.so HINTS ${GLES3_INCLUDE_DIR}/../lib)

    target_include_directories(gl.magicleap INTERFACE ${GLES3_INCLUDE_DIR})
    target_link_libraries(gl.magicleap INTERFACE ${GLES3_LIBRARY} ${EGL_LIBRARY})

    unset(GLES3_INCLUDE_DIR)
    unset(GLES3_LIBRARY)
    unset(EGL_LIBRARY)

else()

    find_package(OpenGL REQUIRED)
    target_link_libraries(gl.magicleap INTERFACE "OpenGL::GL")

endif()
add_library(ML::gl ALIAS gl.magicleap)

set(FindMagicLeapOpenGL_FOUND TRUE)