# Copyright 2021 (c) Magic Leap Inc.

#[=======================================================================[.rst:
FindMagicLeapNativeAppGlue
-------

Sets up the Application Glue Library for Native Application development.

Inputs:
-------

none for device

for ZI / Host building:
MLSDK = path to the top level installation directory of the
                    MagicLeap SDK.

Outputs:
--------

native_app_glue

#]=======================================================================]

find_package(MagicLeap REQUIRED)

if (FindMagicLeapNativeAppGlue_FOUND)
  return()
endif()

if(ML_TARGET STREQUAL ml2)

    add_library(native_app_glue STATIC "${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c")
    target_include_directories(native_app_glue PUBLIC "${ANDROID_NDK}/sources/android/native_app_glue" )

    # Export ANativeActivity_onCreate(),
    # Refer to: https:github.com/android-ndk/ndk/issues/381.
    target_link_options(native_app_glue PUBLIC -u ANativeActivity_onCreate)
    target_link_libraries(native_app_glue PUBLIC android log)


else()

    add_library(native_app_glue STATIC "${MLSDK}/zi_android_sdk/native_app_glue/android_native_app_glue.cpp")
    target_include_directories(native_app_glue PUBLIC "${MLSDK}/zi_android_sdk/include" "${MLSDK}/zi_android_sdk/native_app_glue" )
    set_property(TARGET native_app_glue PROPERTY POSITION_INDEPENDENT_CODE TRUE)
    target_link_directories(native_app_glue PUBLIC "${MLSDK}/lib/${ML_TARGET}")
    target_link_libraries(native_app_glue android log)

    if(ML_TARGET STREQUAL osx)
    target_link_options(native_app_glue PUBLIC -u _OnAppLaunchZIv2)
    elseif(ML_TARGET STREQUAL linux)
    target_link_options(native_app_glue PUBLIC -u OnAppLaunchZIv2)
    elseif(ML_TARGET STREQUAL win)
    target_link_options(native_app_glue PUBLIC /include:OnAppLaunchZIv2)
    endif()


    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(native_app_glue PRIVATE -Werror -Wall -Wextra -Wno-unused-function -Wno-deprecated-declarations)
    endif()

    target_compile_features(native_app_glue PRIVATE cxx_std_11)

endif()


set(FindMagicLeapNativeAppGlue_FOUND TRUE)
