// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2017 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

#include "ml_api.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup CameraMetadata

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK CAMERA APIs:
            https://developer.android.com/training/camera2
            https://developer.android.com/ndk/reference/group/camera

  \brief Enumeration definitions for the various metadata entries.

  \{
*/

/*! Color correction mode. */
typedef enum MLCameraMetadataColorCorrectionMode {
  /*! Uses data provided by the High Quality or Fast method to provide a picture with the same white point as the previous frame. */
  MLCameraMetadataColorCorrectionMode_TransformMatrix = 0,
  /*! The camera device will not slow down capture rate when applying color correction. */
  MLCameraMetadataColorCorrectionMode_Fast,
  /*! The camera device will use the highest-quality color correction algorithm, at the expense of capture rate speed.*/
  MLCameraMetadataColorCorrectionMode_HighQuality,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataColorCorrectionMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataColorCorrectionMode;

/*! Color correction aberration mode. */
typedef enum MLCameraMetadataColorCorrectionAberrationMode {
  /*! No aberration correction is applied. */
  MLCameraMetadataColorCorrectionAberrationMode_Off = 0,
  /*! The camera device will not slow down capture rate when applying aberration correction. */
  MLCameraMetadataColorCorrectionAberrationMode_Fast,
  /*! The camera device will use the highest-quality aberration correction algorithm, at the expense of capture rate speed. */
  MLCameraMetadataColorCorrectionAberrationMode_HighQuality,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataColorCorrectionAberrationMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataColorCorrectionAberrationMode;

/*! The list of auto-exposure (AE) antibanding modes. These controls prevent the appearance of vertical lines when capturing TV screens or monitors. */
typedef enum MLCameraMetadataControlAEAntibandingMode {
  /*! AE antibanding is disabled. */
  MLCameraMetadataControlAEAntibandingMode_Off = 0,
  /*! 50Hz. */
  MLCameraMetadataControlAEAntibandingMode_50Hz,
  /*! 60Hz. */
  MLCameraMetadataControlAEAntibandingMode_60Hz,
  /*! Auto. */
  MLCameraMetadataControlAEAntibandingMode_Auto,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAEAntibandingMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAEAntibandingMode;

/*! The current auto-exposure (AE) lockc controls. */
typedef enum MLCameraMetadataControlAELock {
  /*! Auto-exposure lock is disabled. The algorithm can update exposure parameters. */
  MLCameraMetadataControlAELock_Off = 0,
  /*! Auto-exposure lock is enabled. The algorithm cannot update exposure parameters. */
  MLCameraMetadataControlAELock_On,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAELock_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAELock;

/*!  The current auto-exposure (AE) mode controls. */
typedef enum MLCameraMetadataControlAEMode {
  /*! Disables the camera device's auto-exposure routine. */
  MLCameraMetadataControlAEMode_Off = 0,
  /*! Enables the camera device's auto-exposure routine. */
  MLCameraMetadataControlAEMode_On,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAEMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAEMode;

/*! Control AWB lock. */
typedef enum MLCameraMetadataControlAWBLock {
  /*! Disables the auto-white balance lock. AWB algorithm is free to update its parameters. */
  MLCameraMetadataControlAWBLock_Off = 0,
  /*! Enables the auto-white balance lock. AWB algorithm cannot update its parameters. */
  MLCameraMetadataControlAWBLock_On,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBLock_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBLock;

/*! The current auto-white-balance (AWB) mode controls. */
typedef enum MLCameraMetadataControlAWBMode {
  /*! Disables the camera device's auto-white balance routine. */
  MLCameraMetadataControlAWBMode_Off = 0,
  /*! Sets the camera device's auto-white balance routine to automatic. */
  MLCameraMetadataControlAWBMode_Auto,
  /*! Incandescent light is assumed for the white balance. Auto-white balance is disabled. White balance transforms will approximately match the CIE standard illuminant A.*/
  MLCameraMetadataControlAWBMode_Incandescent,
  /*! Fluorescent light is assumed for the white balance. Auto-white balance is disabled. White balance transforms will approximately match the CIE standard illuminant F2. */
  MLCameraMetadataControlAWBMode_Fluorescent,
  /*! Warm fluorescent light is assumed for the white balance. Auto-white balance is disabled. White balance transforms will approximately match the CIE standard illuminant F4. */
  MLCameraMetadataControlAWBMode_WarmFluorescent,
  /*! Daylight light is assumed for the white balance. Auto-white balance is disabled. White balance transforms will approximately match the CIE standard illuminant D65. */
  MLCameraMetadataControlAWBMode_Daylight,
  /*! Cloudy daylight is assumed for the white balance. Auto-white balance is disabled. */
  MLCameraMetadataControlAWBMode_CloudyDaylight,
  /*! Twilight light is assumed for the white balance. Auto-white balance is disabled. */
  MLCameraMetadataControlAWBMode_Twilight,
  /*! Shade light is assumed for the white balance. Auto-white balance is disabled. */
  MLCameraMetadataControlAWBMode_Shade,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBMode;

/*! The current auto-focus (AF) mode controls. */
typedef enum MLCameraMetadataControlAFMode {
  /*! Disables the camera device's auto-focus routine. */
  MLCameraMetadataControlAFMode_Off = 0,
  /*! Sets the camera device's auto-focus routine to automatic. */
  MLCameraMetadataControlAFMode_Auto,
  /*! Sets the camera device's auto-focus routine to close-up focusing mode. */
  MLCameraMetadataControlAFMode_Macro,
  /*! Sets the camera device's auto-focus routine to Continuous Video Mode. The focusing behavior should be suitable for good quality video recording. */
  MLCameraMetadataControlAFMode_ContinuousVideo,
  /*! Sets the camera device's auto-focus routine to Continuous Picture Mode. The focusing behavior should be suitable for still image capture. */
  MLCameraMetadataControlAFMode_ContinuousPicture,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAFMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAFMode;

/*! The current auto-focus (AF) trigger. */
typedef enum MLCameraMetadataControlAFTrigger {
  /*! AF trigger is idle. */
  MLCameraMetadataControlAFTrigger_Idle = 0,
  /*! AF will trigger now. */
  MLCameraMetadataControlAFTrigger_Start,
  /*! Cancel any currently active AF trigger. */
  MLCameraMetadataControlAFTrigger_Cancel,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAFTrigger_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAFTrigger;

/*! Overall control mode of the 3A (auto-white balance, auto-focus, auto-exposure) parameters. */
typedef enum MLCameraMetadataControlMode {
  /*! Disables control of the device's metering and focusing routines (3A). */
  MLCameraMetadataControlMode_Off = 0,
  /*! Manual control of capture parameters is disabled. */
  MLCameraMetadataControlMode_Auto,
  /*! Use a specific scene mode. This setting is available only if scene mode is supported. */
  MLCameraMetadataControlMode_UseSceneMode,
  /*! Same as `MLCameraMetadataControlMode_Off` mode, except any statistics or state updates collected from manual captures will be discarded by the camera device. */
  MLCameraMetadataControlMode_OffKeepState,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlMode;

/*! Scene mode. */
typedef enum MLCameraMetadataControlSceneMode {
  /*! Scene mode not used. */
  MLCameraMetadataControlSceneMode_None = 0,
  /*! Action mode – optimized for photos of quickly moving objects. */
  MLCameraMetadataControlSceneMode_Action = 2,
  /*! Portrait mode – optimized for still photos of people. */
  MLCameraMetadataControlSceneMode_Portrait = 3,
  /*! Landscape mode – optimized for photos of distant macroscopic objects. */
  MLCameraMetadataControlSceneMode_Landscape = 4,
  /*! Theatre mode – ptimized for dim, indoor settings without flash. */
  MLCameraMetadataControlSceneMode_Theatre = 7,
  /*! Sports mode – similar to Action mode, and optimized for photos of quickly moving people. */
  MLCameraMetadataControlSceneMode_Sports = 13,
  /*! Party mode – optimized for dim, indoor settings with multiple moving people. */
  MLCameraMetadataControlSceneMode_Party = 14,
  /*! CandleLight mode – optimized for extremely dim settings with a single light source. */
  MLCameraMetadataControlSceneMode_CandleLight = 15,
  /*! Barcode mode. This mode is optimized for accurately capturing barcode images with the intent of processing the barcode value. */
  MLCameraMetadataControlSceneMode_Barcode = 16,
  /*! Medical mode. This mode is optimized for brightly lit settings (100-200K lux) such as an operation theater.  */
  MLCameraMetadataControlSceneMode_Medical = 100,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlSceneMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlSceneMode;

/*! Effect mode. Applies color effects. */
typedef enum MLCameraMetadataControlEffectMode {
  /*! Off. */
  MLCameraMetadataControlEffectMode_Off = 0,
  /*! GrayScale – maps the image into grayscale colors. */
  MLCameraMetadataControlEffectMode_Grayscale,
  /*! Negative – inverts the colors of the image. */
  MLCameraMetadataControlEffectMode_Negative,
  /*! Sepia – maps the image into warm gray, red, and brown tones. */
  MLCameraMetadataControlEffectMode_Sepia,
  /*! ColorSelection. */
  MLCameraMetadataControlEffectMode_ColorSelection,
  /*! Sharpening – emphasises the edges of adjacent areas with tonal contrast to one another. */
  MLCameraMetadataControlEffectMode_Sharpening,
  /*! Emboss – applies an emboss filter, replacing each pixel with shadow or highlight depending on its light or dark boundaries. */
  MLCameraMetadataControlEffectMode_Emboss,
  /*! Sketch. */
  MLCameraMetadataControlEffectMode_Sketch,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlEffectMode_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlEffectMode;

/*! Currents state of auto-exposure (AE) controls. */
typedef enum MLCameraMetadataControlAEState {
  /*! AE is off or recently reset. The camera device begins in this mode. Device may fail to report this state. */
  MLCameraMetadataControlAEState_Inactive = 0,
  /*! AE does not yet have a good set of control values for the current scene. Device may fail to report this state. */
  MLCameraMetadataControlAEState_Searching,
  /*! AE has a good set of control values for the current scene. */
  MLCameraMetadataControlAEState_Converged,
  /*! AE is locked. */
  MLCameraMetadataControlAEState_Locked,
  /*! AE has a good set of control values, but flash is required for good quality still capture. */
  MLCameraMetadataControlAEState_FlashRequired,
  /*! AE has been asked to do a precapture sequence and is currently executing it. Once this mode is complete, AE will transition to `MLCameraMetadataControlAEState_Converged` or `MLCameraMetadataControlAEState_FlashRequired`. */
  MLCameraMetadataControlAEState_PreCapture,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAEState_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAEState;

/*! Current state of auto-white-balance (AWB) controls. */
typedef enum MLCameraMetadataControlAWBState {
  /*! AWB is in not in automatic mode or has not yet started metering. The camera device begins in this mode. Device may fail to report this state. */
  MLCameraMetadataControlAWBState_Inactive = 0,
  /*! AWB does not yet have a good set of control values for the current scene. Device may fail to report this state. */
  MLCameraMetadataControlAWBState_Searching,
  /*! AWB has a good set of control values for the current scene. */
  MLCameraMetadataControlAWBState_Converged,
  /*! AWB is locked. */
  MLCameraMetadataControlAWBState_Locked,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAWBState_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAWBState;

/*! Current state of auto-focus (AF) routine. */
typedef enum MLCameraMetadataControlAFState {
  /*! AF is off or has not yet tried to scan. */
  MLCameraMetadataControlAFState_Inactive = 0,
  /*! AF is currently performing an AF scan initiated by the camera device in a continuous autofocus mode. */
  MLCameraMetadataControlAFState_PassiveScan,
  /*! AF currently is in focus, but may restart scanning at any time. */
  MLCameraMetadataControlAFState_PassiveFocussed,
  /*! AF is performing an AF scan triggered by AF trigger. */
  MLCameraMetadataControlAFState_ActiveScan,
  /*! AF is focused correctly and has locked focus. */
  MLCameraMetadataControlAFState_FocusedLocked,
  /*! AF has failed to focus successfully and has locked focus. */
  MLCameraMetadataControlAFState_NotFocusedLocked,
  /*! AF finished a passive scan without finding focus,and may restart scanning at any time. */
  MLCameraMetadataControlAFState_PassiveUnFocussed,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAFState_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAFState;

/*! Whether a significant scene change is detected by AF algorithm. */
typedef enum MLCameraMetadataControlAFSceneChange {
  /*! No scene change detected by AF. */
  MLCameraMetadataControlAFSceneChange_NotDetected = 0,
  /*! Scene change detected by AF. */
  MLCameraMetadataControlAFSceneChange_Detected,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlAFSceneChange_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataControlAFSceneChange;

/*! Current Lens status. */
typedef enum MLCameraMetadataLensState {
  /*! Lens focal length is not changing. */
  MLCameraMetadataLensState_Stationary = 0,
  /*! Lens focal length is changing. */
  MLCameraMetadataLensState_Moving,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataLensState_Ensure32Bits  = 0x7FFFFFFF
} MLCameraMetadataLensState;

/*! Scaler available formats. */
typedef enum MLCameraMetadataScalerAvailableFormats {
  /*! Raw16. */
  MLCameraMetadataScalerAvailableFormats_RAW16                  = 0x20,
  /*! Raw opaque. */
  MLCameraMetadataScalerAvailableFormats_RAW_OPAQUE             = 0x24,
  /*! TV12. */
  MLCameraMetadataScalerAvailableFormats_YV12                   = 0x32315659,
  /*! YCrCb 420 SP. */
  MLCameraMetadataScalerAvailableFormats_YCrCb_420_SP           = 0x11,
  /*! Implementation defined. */
  MLCameraMetadataScalerAvailableFormats_IMPLEMENTATION_DEFINED = 0x22,
  /*! YCrCb 420 888. */
  MLCameraMetadataScalerAvailableFormats_YCbCr_420_888          = 0x23,
  /*! BLOB. */
  MLCameraMetadataScalerAvailableFormats_BLOB                   = 0x21,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataScalerAvailableFormats_Ensure32Bits           = 0x7FFFFFFF
} MLCameraMetadataScalerAvailableFormats;

/*! The available stream configurations . */
typedef enum MLCameraMetadataScalerAvailableStreamConfigurations {
  /*! Output. */
  MLCameraMetadataScalerAvailableStreamConfigurations_OUTPUT = 0,
  /*! Input. */
  MLCameraMetadataScalerAvailableStreamConfigurations_INPUT,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataScalerAvailableStreamConfigurations_Ensure32Bits = 0x7FFFFFFF
} MLCameraMetadataScalerAvailableStreamConfigurations;

/*! JPEG Thumbnail Size. */
typedef enum MLCameraMetadataJpegThumbnailSize {
  /*! 160x120. */
  MLCameraMetadataJpegThumbnailSize_160x120   = 1,
  /*! 240x135. */
  MLCameraMetadataJpegThumbnailSize_240x135 = 2,
  /*! 256x135. */
  MLCameraMetadataJpegThumbnailSize_256x135 = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataJpegThumbnailSize_Ensure32Bits = 0x7FFFFFFF
} MLCameraMetadataJpegThumbnailSize;

/*! Force Apply Metadata Settings. */
typedef enum MLCameraMetadataControlForceApplyMode {
  /*! Off. */
  MLCameraMetadataControlForceApplyMode_Off  = 0,
  /*! On. */
  MLCameraMetadataControlForceApplyMode_On  = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMetadataControlForceApplyMode_Ensure32Bits = 0x7FFFFFFF
} MLCameraMetadataControlForceApplyMode;

/*! \} */

ML_EXTERN_C_END
