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
#include "ml_camera_metadata_tags_v2.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup CameraMetadata Camera Metadata
  \addtogroup CameraMetadata
  \sharedobject camera_metadata.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK CAMERA APIs:
            https://developer.android.com/training/camera2
            https://developer.android.com/ndk/reference/group/camera

  \brief APIs for getting/setting camera characteristic/request/result metadata.
         Main camera and CV Camera share the same camera hardware resources. It is recommended that applications try to use as much as possible
         the default metadata returned by MLCameraPrepareCapture otherwise metadata properties from one camera can affect the other.
         When both the cameras are streaming, request metadata properties for both cameras are merged and then applied. While merging, the metadata
         properties from Main Camera take precedence over CV camera except for metadata proprties for exposure upper time limit, JPEG gps timestamp,
         JPEG gps coordinates, JPEG quality and JPEG thumbnail size. The Force Apply mode setting can be used to override this.
         If CV Camera metadata  have force apply mode on, the CV Camera metadata properties take precedence over Main Camera properties.
         The result metadata returned in #MLCameraCaptureCallbacks can be used to check the actual metadata settings applied.
         For exposure upper time limit the lower of 2 values (Main Camera and CV Camera) are applied by default.If one of the cameras has force apply
         mode on the exposure upper time limit setting from that camera is applied.
         The JPEG gps timestamp , JPEG gps coordinates, JPEG quality and JPEG thumbnail size settings from one camera donot affect the other camera.

  # State Machine for Auto Focus for different Modes.
  <table>
  <caption id="multi_row">AutoFocus Mode Auto/Macro</caption>
  <tr><th>State                      <th>Transition Cause        <th>New State  <th>Notes
  <tr><td>AFState_Inactive<td>AFTrigger_Start<td>AFState_ActiveScan<td>Start AF scan, Lens now moving
  <tr><td>AFState_ActiveScan<td>Camera AF completes current scan<td>AFState_FocussedLocked<td>Focussed, Lens now locked
  <tr><td>AFState_ActiveScan<td>Camera AF fails current scan<td>AFState_NotFocussedLocked<td>Not focussed, Lens now locked
  <tr><td>AFState_ActiveScan<td>AFTrigger_Cancel<td>AFState_Inactive<td>Cancel/reset AF
  <tr><td>AFState_FocussedLocked<td>AFTrigger_Cancel<td>AFState_Inactive<td>Cancel/reset AF
  <tr><td>AFState_FocussedLocked<td>AFTrigger_Start<td>AFState_ActiveScan<td>Restart AF scan, Lens now moving
  <tr><td>AFState_NotFocussedLocked<td>AFTrigger_Cancel<td>AFState_Inactive<td>Cancel/reset AF
  <tr><td>AFState_NotFocussedLocked<td>AFTrigger_Start<td>AFState_ActiveScan<td>Restart AF scan, Lens now moving
  </table>

   <table>
   <caption id="multi_row">AutoFocus Mode Continuous Video</caption>
   <tr><th>State                      <th>Transition Cause        <th>New State  <th>Notes
   <tr><td>AFState_PassiveScan<td>Camera AF completes current scan<td>AFState_PassiveFocussed<td>End AF scan, Lens Focussed
   <tr><td>AFState_PassiveScan<td>Camera AF fails current scan<td>AFState_PassiveUnFocussed<td>End AF scan, Lens Not Focussed
   <tr><td>AFState_PassiveScan<td>AFTrigger_Start<td>AFState_FocussedLocked<td>Immediate transition, if focus is good, Lens now locked
   <tr><td>AFState_PassiveScan<td>AFTrigger_Start<td>AFState_NotFocussedLocked<td>Immediate transition, if focus is not good, Lens now locked
   <tr><td>AFState_PassiveFocussed<td>Camera AF initiates new scan<td>AFState_PassiveScan<td>Restart AF scan, Lens now moving
   <tr><td>AFState_PassiveUnFocussed<td>Camera AF initiates new scan<td>AFState_PassiveScan<td>Restart AF scan, Lens now moving
   <tr><td>AFState_PassiveFocussed<td>AFTrigger_Start<td>AFState_FocussedLocked<td>Lens now locked and Focussed
   <tr><td>AFState_PassiveUnFocussed<td>AFTrigger_Start<td>AFState_NotFocussedLocked<td>Lens now locked and Not Focussed
   <tr><td>AFState_FocussedLocked<td>AFTrigger_Cancel<td>AFState_PassiveScan<td>Restart AF Scan, Lens now moving
   <tr><td>AFState_NotFocussedLocked<td>AFTrigger_Cancel<td>AFState_PassiveScan<td>Restart AF Scan, Lens now moving
   </table>

   <table>
   <caption id="multi_row">AutoFocus Mode Continuous Picture</caption>
   <tr><th>State                      <th>Transition Cause        <th>New State  <th>Notes
   <tr><td>AFState_PassiveScan<td>Camera AF completes current scan<td>AFState_PassiveFocussed<td>End AF scan, Lens Focussed
   <tr><td>AFState_PassiveScan<td>Camera AF fails current scan<td>AFState_PassiveUnFocussed<td>End AF scan, Lens Not Focussed
   <tr><td>AFState_PassiveScan<td>AFTrigger_Start<td>AFState_FocussedLocked<td>Eventual transition once focus is good, Lens now locked
   <tr><td>AFState_PassiveScan<td>AFTrigger_Start<td>AFState_NotFocussedLocked<td>Eventual transition if cannot find focus, Lens now locked
   <tr><td>AFState_PassiveFocussed<td>Camera AF initiates new scan<td>AFState_PassiveScan<td>Restart AF scan, Lens now moving
   <tr><td>AFState_PassiveUnFocussed<td>Camera AF initiates new scan<td>AFState_PassiveScan<td>Restart AF scan, Lens now moving
   <tr><td>AFState_PassiveFocussed<td>AFTrigger_Start<td>AFState_FocussedLocked<td>Lens now locked and Focussed
   <tr><td>AFState_PassiveUnFocussed<td>AFTrigger_Start<td>AFState_NotFocussedLocked<td>Lens now locked and Not Focussed
   <tr><td>AFState_FocussedLocked<td>AFTrigger_Cancel<td>AFState_PassiveScan<td>Restart AF Scan, Lens now moving
   <tr><td>AFState_NotFocussedLocked<td>AFTrigger_Cancel<td>AFState_PassiveScan<td>Restart AF Scan, Lens now moving
   </table>

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*! Rational data type. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraMetadataRational {
  /*! Numerator. */
  int32_t numerator;
  /*! Denominator. */
  int32_t denominator;
} MLCameraMetadataRational;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction aberration modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of aberration modes. The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain color correction aberration modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction aberration modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction aberration modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionAvailableAberrationModes(MLHandle characteristics_handle, MLCameraMetadataColorCorrectionAberrationMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-exposure modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of auto-exposure modes. The Library allocates and maintains the lifetime of the output data.

  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain AE modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEAvailableModes(MLHandle characteristics_handle, MLCameraMetadataControlAEMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets anti-banding modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of anti-banding modes. The Library allocates and maintains the lifetime of the output data.

  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain AntiBanding modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AntiBanding modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain AntiBanding modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEAvailableAntibandingModes(MLHandle characteristics_handle, MLCameraMetadataControlAEAntibandingMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-exposure compensation range.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of min (1st) and max (2nd) of auto-exposure compensation. The adjustment is measured as a count of steps.

  \retval MLResult_InvalidParam Failed to obtain AE compensation range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE compensation range.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE compensation range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAECompensationRange(MLHandle characteristics_handle, int32_t out_data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE compensation step.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE compensation step.

  \retval MLResult_InvalidParam Failed to obtain AE compensation step due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE compensation step.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE compensation step due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAECompensationStep(MLHandle characteristics_handle, MLCameraMetadataRational *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE lock.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data AE lock.

  \retval MLResult_InvalidParam Failed to obtain AE lock due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE lock.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAELockAvailable(MLHandle characteristics_handle, MLCameraMetadataControlAELock *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE Max Regions.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Num AE Regions.

  \retval MLResult_InvalidParam Failed to obtain AE Max Regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE Max Regions.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE Max Regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEMaxRegions(MLHandle characteristics_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Available Modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of modes. The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain Avaialble Modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained Available Modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain Available Modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAvailableModes(MLHandle characteristics_handle, MLCameraMetadataControlMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of AWB modes. The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain AWB modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBAvailableModes(MLHandle characteristics_handle, MLCameraMetadataControlAWBMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of AF modes. The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain AF modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFAvailableModes(MLHandle characteristics_handle, MLCameraMetadataControlAFMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets max number of AF regions supported.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Num AF Regions.

  \retval MLResult_InvalidParam Failed to obtain AF Max Regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF Max Regions.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF Max Regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFMaxRegions(MLHandle characteristics_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Scene modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of Scene modes. The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain Scene modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained Scene modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain Scene modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAvailableSceneModes(MLHandle characteristics_handle, MLCameraMetadataControlSceneMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Effect modes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Array of Effect modes. The Library allocates and maintains the lifetime of the output data.
  \param[out] out_count Number of output data elements.

  \retval MLResult_InvalidParam Failed to obtain Effect modes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained Effect modes.
  \retval MLResult_UnspecifiedFailure Failed to obtain Effect modes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAvailableEffectModes(MLHandle characteristics_handle, MLCameraMetadataControlEffectMode **out_data, uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB lock.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data AWB lock.

  \retval MLResult_InvalidParam Failed to obtain AWB lock due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB lock.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBLockAvailable(MLHandle characteristics_handle, MLCameraMetadataControlAWBLock *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor info active array sizes.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Active array size [left, top, right, bottom].

  \retval MLResult_InvalidParam Failed to obtain sensor info active array sizes due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor info active array sizes.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor info active array sizes due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorInfoActiveArraySize(MLHandle characteristics_handle, int32_t out_data[4]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor info sensitivity range (Analog Gain).

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor info sensitivity range[min, max].

  \retval MLResult_InvalidParam Failed to obtain sensor info sensitivity range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor info sensitivity range.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor info sensitivity range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorInfoSensitivityRange(MLHandle characteristics_handle, int32_t out_data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets post raw sensitivity boost range (Digital Gain).

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Post raw sensitivity boost range[min, max].

  \retval MLResult_InvalidParam Failed to obtain post raw sensitivity boost range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained post raw sensitivity boost range.
  \retval MLResult_UnspecifiedFailure Failed to obtain post raw sensitivity boost range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetPostRawSensitivityBoostRange(MLHandle characteristics_handle, int32_t out_data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets lens hyperfocal distance.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Lens hyperfocal distance in diopters.

  \retval MLResult_InvalidParam Failed to obtain hyperfocal distance due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained hyperfocal distance.
  \retval MLResult_UnspecifiedFailure Failed to obtain hyperfocal distance due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetLensInfoHyperfocalDistance(MLHandle characteristics_handle, float *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets lens minimum focus distance.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Minimum focus distance in diopters.

  \retval MLResult_InvalidParam Failed to obtain minimum focus distance due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained minimum focus distance.
  \retval MLResult_UnspecifiedFailure Failed to obtain minimum focus distance due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetLensInfoMinimumFocusDistance(MLHandle characteristics_handle, float *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets lens minimum focus distance increment.
         The lens position can be set in multiples of distance increments between hyperfocal distance and minimum focus distance.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Minimum focus distance increment in diopters.

  \retval MLResult_InvalidParam Failed to obtain minimum focus distance increment due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained minimum focus distance increment.
  \retval MLResult_UnspecifiedFailure Failed to obtain minimum focus distance increment due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetLensInfoMinimumFocusDistanceIncrement(MLHandle characteristics_handle, float *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor orientation degree.

  \apilevel 20

  \param[in] characteristics_handle Camera characteristic metadata handle acquired from #MLCameraGetCameraCharacteristics.
  \param[out] out_data Sensor orientation degree.

  \retval MLResult_InvalidParam Failed to obtain sensor orientation degree due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor orientation degree.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor orientation degree due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorOrientation(MLHandle characteristics_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction mode.

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Color correction mode.

  \apilevel 20

  \retval MLResult_InvalidParam Failed to obtain color correction mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionModeRequestMetadata(MLHandle request_handle, MLCameraMetadataColorCorrectionMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction transform.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data 3x3 color correction transform.

  \retval MLResult_InvalidParam Failed to obtain color correction transform due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction transform.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction transform due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionTransformRequestMetadata(MLHandle request_handle, MLCameraMetadataRational out_data[3][3]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction gains.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Color correction gains.

  \retval MLResult_InvalidParam Failed to obtain color correction gains due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction gains.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction gains due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionGainsRequestMetadata(MLHandle request_handle, float out_data[4]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction aberration.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Color correction aberration.

  \retval MLResult_InvalidParam Failed to obtain color correction aberration due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction aberration.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction aberration due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionAberrationModeRequestMetadata(MLHandle request_handle, MLCameraMetadataColorCorrectionAberrationMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE antibanding mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AE antibanding mode.

  \retval MLResult_InvalidParam Failed to obtain AE antibanding mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE antibanding mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE antibanding mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEAntibandingModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAEAntibandingMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE exposure compensation.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Exposure compensation value.

  \retval MLResult_InvalidParam Failed to obtain AE exposure compensation due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE exposure compensation.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE exposure compensation due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEExposureCompensationRequestMetadata(MLHandle request_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE lock.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AE Lock.

  \retval MLResult_InvalidParam Failed to obtain AE lock due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE lock.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAELockRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAELock *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AE mode.

  \retval MLResult_InvalidParam Failed to obtain AE mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAEMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-exposure regions.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Auto-exposure regions. Regions array of area_size x 5[xmin, ymin, xmax, ymax, weight].
                       Coordinates must be between [(0,0), (width, height)).
  \param[out] out_count Number of auto-exposure regions.

  \retval MLResult_InvalidParam Failed to obtain AE regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE regions.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAERegionsRequestMetadata(MLHandle request_handle, int32_t out_data[3][5], uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB lock.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AWB Lock.

  \retval MLResult_InvalidParam Failed to obtain AWB lock due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB lock.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBLockRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAWBLock *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AWB mode.

  \retval MLResult_InvalidParam Failed to obtain AWB mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAWBMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AF mode.

  \retval MLResult_InvalidParam Failed to obtain AF mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAFMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF trigger.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AF trigger.

  \retval MLResult_InvalidParam Failed to obtain AF trigger due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF trigger.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF trigger due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFTriggerRequestMetadata(MLHandle request_handle, MLCameraMetadataControlAFTrigger *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-focus regions.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Auto-focus regions. Regions array of area_size x 5[xmin, ymin, xmax, ymax, weight].
                       Coordinates must be between [(0,0), (width, height)).
  \param[out] out_count Number of auto-focus regions.

  \retval MLResult_InvalidParam Failed to obtain AF regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF regions.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFRegionsRequestMetadata(MLHandle request_handle, int32_t out_data[3][5], uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF distance range. Both Min and Max are specified as focus distance in diopters.
         The min value specifies the lower bound for focus distance used by Autofocus algorithm and should be
         more than min focus distance which can be queried using MLCameraMetadataGetLensInfoMinimumFocusDistance.
         The max value specifies the upper bound for focus distance used by Autofocus algorithm and should be
         less than hyperfocal distance which can be queried using api MLCameraMetadataGetLensInfoHyperfocalDistance.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data AF distance range [min, max].

  \retval MLResult_InvalidParam Failed to obtain AF distance range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF distance range.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF distance range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetAFDistanceRangeRequestMetadata(MLHandle request_handle, float out_data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Lens focus distance in diopters.
         The distance is between minimum focus distance and hyperfocal distance.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Lens focus distance.

  \retval MLResult_InvalidParam Failed to obtain Lens focus distance range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained Lens focus distance range.
  \retval MLResult_UnspecifiedFailure Failed to obtain Lens focus distance range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetLensFocusDistanceRequestMetadata(MLHandle request_handle, float *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Mode.

  \retval MLResult_InvalidParam Failed to obtain mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Scene mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Scene mode.

  \retval MLResult_InvalidParam Failed to obtain scene mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained scene mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain scene mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlSceneModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlSceneMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor exposure time.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Duration each pixel is exposed to light in nanoseconds.

  \retval MLResult_InvalidParam Failed to obtain sensor exposure time due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor exposure time.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor exposure time due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorExposureTimeRequestMetadata(MLHandle request_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor sensitivity.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Sensor sensitivity.

  \retval MLResult_InvalidParam Failed to obtain sensor sensitivity due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor sensitivity.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor sensitivity due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorSensitivityRequestMetadata(MLHandle request_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets post raw sensitivity boost.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Post raw sensitivity boost.

  \retval MLResult_InvalidParam Failed to obtain post raw sensitivity boost due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained post raw sensitivity boost.
  \retval MLResult_UnspecifiedFailure Failed to obtain post raw sensitivity boost due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetPostRawSensitivityBoostRequestMetadata(MLHandle request_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Effect mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Effect mode.

  \retval MLResult_InvalidParam Failed to obtain effect mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained effect mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain effect mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlEffectModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlEffectMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets exposure time upper limit.


  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Exposure time upper limit for auto exposure algorithm.

  \retval MLResult_InvalidParam Failed to obtain exposure time upper limit due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained exposure time upper limit.
  \retval MLResult_UnspecifiedFailure Failed to obtain exposure time upperlimit due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlExposureUpperTimeLimitRequestMetadata(MLHandle request_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG GPS coordinates.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data JPEG GPS coordinates – latitude and longitude in degrees, altitude in meters.

  \retval MLResult_InvalidParam Failed to obtain JPEG GPS coordinates due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG GPS coordinates.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG GPS coordinates due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegGPSCoordinatesRequestMetadata(MLHandle request_handle, double out_data[3]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG timestamp.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data JPEG timestamp in UNIX Epoch time (UTC in seconds since January 1, 1970).

  \retval MLResult_InvalidParam Failed to obtain JPEG timestamp due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG timestamp.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG timestamp due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegGPSTimestampRequestMetadata(MLHandle request_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG thumbnail size.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Resolution of embedded JPEG thumbnail.

  \retval MLResult_InvalidParam Failed to obtain JPEG thumbnail size due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG thumbnail size.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG thumbnail size due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegThumbnailSizeRequestMetadata(MLHandle request_handle, MLCameraMetadataJpegThumbnailSize *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG quality.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Compression quality of JPEG thumbnail, with 100 being the highest quality, and 1 the lowest.

  \retval MLResult_InvalidParam Failed to obtain JPEG quality due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG quality.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG quality due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegQualityRequestMetadata(MLHandle request_handle, uint8_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets force apply mode.
         Main camera and CV Camera share the same camera hardware resources. When both the cameras are streaming, request metadata properties
         for both cameras are merged and then applied. While merging, the metadata properties from Main Camera take precedence over CV camera
         metadata properties. The force apply mode property can be used to override this. If CV Camera metadata has force apply mode on,
         the CV Camera metadata properties take precedence over Main Camera metadata properties.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[out] out_data Force apply mode.

  \retval MLResult_InvalidParam Failed to obtain force apply mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained force apply mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain force apply mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlForceApplyModeRequestMetadata(MLHandle request_handle, MLCameraMetadataControlForceApplyMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets color correction mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Color correction mode.

  \retval MLResult_InvalidParam Failed to set color correction mode due to an invalid input parameter.
  \retval MLResult_Ok Set color correction mode.
  \retval MLResult_UnspecifiedFailure Failed to set color correction mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetColorCorrectionMode(MLHandle request_handle, const MLCameraMetadataColorCorrectionMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets color correction transform from RGB color space to output linear sRGB.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Color correction transform (3x3). Set all values to 0/1 to clear the data.

  \retval MLResult_InvalidParam Failed to set color correction transform due to an invalid input parameter.
  \retval MLResult_Ok Set color correction transform.
  \retval MLResult_UnspecifiedFailure Failed to set color correction transform due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetColorCorrectionTransform(MLHandle request_handle, const MLCameraMetadataRational data[3][3]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets color correction gains. The gains in the request metadata are the gains applied by the camera device.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data An array of floats for 4 color channel color correction gains. Set all values to 0 to clear the data.

  \retval MLResult_InvalidParam Failed to set color correction gains due to an invalid input parameter.
  \retval MLResult_Ok Set color correction gains.
  \retval MLResult_UnspecifiedFailure Failed to set color correction gains due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetColorCorrectionGains(MLHandle request_handle, const float data[4]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets color correction chromatic aberration, minimizing chromatic artifacts that may occur.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Color correction aberration.

  \retval MLResult_InvalidParam Failed to set color correction aberration due to an invalid input parameter.
  \retval MLResult_Ok Set color correction aberration.
  \retval MLResult_UnspecifiedFailure Failed to set color correction aberration due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetColorCorrectionAberrationMode(MLHandle request_handle, const MLCameraMetadataColorCorrectionAberrationMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets AE antiband mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data AE antibanding mode.

  \retval MLResult_InvalidParam Failed to set AE antiband mode due to an invalid input parameter.
  \retval MLResult_Ok Set AE antiband mode.
  \retval MLResult_UnspecifiedFailure Failed to set AE antiband mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAEAntibandingMode(MLHandle request_handle, const MLCameraMetadataControlAEAntibandingMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets auto-exposure compensation.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Exposure compensation value as a count of steps. If exposure compensation is set to 0, no exposure compensation will be applied.

  \retval MLResult_InvalidParam Failed to set AE exposure compensation due to an invalid input parameter.
  \retval MLResult_Ok Set AE exposure compensation.
  \retval MLResult_UnspecifiedFailure Failed to set AE exposure compensation due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAEExposureCompensation(MLHandle request_handle, const int32_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets auto-exposure lock.

  When auto-exposure is locked, the algorithm cannot update its parameters and adjust exposure times and sensitivity.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Auto-exposure Lock.

  \retval MLResult_InvalidParam Failed to set AE lock due to an invalid input parameter.
  \retval MLResult_Ok Set AE lock.
  \retval MLResult_UnspecifiedFailure Failed to set AE lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAELock(MLHandle request_handle, const MLCameraMetadataControlAELock *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets auto-exposure mode.
         MLCameraMetadataControlAEMode_Off is not supported if camera is configured for 15FPS.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Auto-exposure mode.

  \retval MLResult_InvalidParam Failed to set AE mode due to an invalid input parameter.
  \retval MLResult_Ok Set AE mode.
  \retval MLResult_UnspecifiedFailure Failed to set AE mode due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed to set AE Mode due to conflict between fps setting and AE Mode.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAEMode(MLHandle request_handle, const MLCameraMetadataControlAEMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets auto-exposure regions.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Auto-exposure regions. Regions array of area_size x 5[xmin, ymin, xmax, ymax, weight]
                   array with all zeros and count 1 clears the data.
                   Coordinates must be between [(0,0), (width, height)).
                   Max width, height can be obtained using MLCameraMetadataGetSensorInfoActiveArraySize.
                   Weight for a region can be between [0,1000].For a region to be used its weight should be > 0.
                   Weight is used to decide relative priority between multiple regions.
  \param[in] count Number of auto-exposure regions.

  \retval MLResult_InvalidParam Failed to set AE regions due to an invalid input parameter.
  \retval MLResult_Ok Set AE regions.
  \retval MLResult_UnspecifiedFailure Failed to set AE regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAERegions(MLHandle request_handle, const int32_t data[3][5], const uint32_t count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets automatic white balance lock.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Automatic White Balance Lock.

  \retval MLResult_InvalidParam Failed to set AE target FPS range due to an invalid input parameter.
  \retval MLResult_Ok Set automatic white balance lock.
  \retval MLResult_UnspecifiedFailure Failed to set automatic white balance lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAWBLock(MLHandle request_handle, const MLCameraMetadataControlAWBLock *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets AWB mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data AWB mode.

  \retval MLResult_InvalidParam Failed to set AWB mode due to an invalid input parameter.
  \retval MLResult_Ok Set AWB mode.
  \retval MLResult_UnspecifiedFailure Failed to set AWB mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAWBMode(MLHandle request_handle, const MLCameraMetadataControlAWBMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets AF mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data AF mode.

  \retval MLResult_InvalidParam Failed to set AF mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully set AF mode.
  \retval MLResult_UnspecifiedFailure Failed to set AF mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAFMode(MLHandle request_handle, const MLCameraMetadataControlAFMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets AF trigger.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data AF trigger.

  \retval MLResult_InvalidParam Failed to set AF trigger due to an invalid input parameter.
  \retval MLResult_Ok Successfully set AF trigger.
  \retval MLResult_UnspecifiedFailure Failed to set AF trigger due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAFTrigger(MLHandle request_handle, const MLCameraMetadataControlAFTrigger *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets auto-focus regions.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Auto-focus regions. Regions array of area_size x 5[xmin, ymin, xmax, ymax, weight].
                  Coordinates must be between [(0,0), (width, height)).
                  Max width, height can be obtained using MLCameraMetadataGetSensorInfoActiveArraySize.
                  Weight for a region can be between [0,1000]. For a region to be used its weight should be > 0.
                  All regions with weight > 0 are treated as same priority.
  \param[in] count Number of auto-focus regions.

  \retval MLResult_InvalidParam Failed to set AF regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully set AF regions.
  \retval MLResult_UnspecifiedFailure Failed to set AF regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlAFRegions(MLHandle request_handle, const int32_t data[3][5], const uint32_t count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets AF distance range. Both min and max are specified as focus distance in diopters.
         The min value specifies the lower bound for focus distance used by Autofocus algorithm and should be
         more than min focus distance which can be queried using MLCameraMetadataGetLensInfoMinimumFocusDistance.
         The max value specifies the upper bound for focus distance used by Autofocus algorithm and should be
         less than hyperfocal distance which can be queried using api MLCameraMetadataGetLensInfoHyperfocalDistance.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data AF distance range [min, max].

  \retval MLResult_InvalidParam Failed to set AF distance range due to an invalid input parameter.
  \retval MLResult_Ok Successfully set AF distance range.
  \retval MLResult_UnspecifiedFailure Failed to set AF distance range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetAFDistanceRange(MLHandle request_handle, const float data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets Lens focus distance.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Lens focus distance.

  \retval MLResult_InvalidParam Failed to set Lens focus distance due to an invalid input parameter.
  \retval MLResult_Ok Successfully set Lens focus distance.
  \retval MLResult_UnspecifiedFailure Failed to set Lens focus distance due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetLensFocusDistance(MLHandle request_handle, const float *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Mode.

  \retval MLResult_InvalidParam Failed to set mode due to an invalid input parameter.
  \retval MLResult_Ok Set mode.
  \retval MLResult_UnspecifiedFailure Failed to set mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlMode(MLHandle request_handle, const MLCameraMetadataControlMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets Scene mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Scene mode.

  \retval MLResult_InvalidParam Failed to set scene mode due to an invalid input parameter.
  \retval MLResult_Ok Set scene mode.
  \retval MLResult_UnspecifiedFailure Failed to set scene mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlSceneMode(MLHandle request_handle, const MLCameraMetadataControlSceneMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets sensor exposure time.

  Exposure time provided should be less than frame duration(1/framerate).
  If the sensor can't expose this exact duration, it will shorten the duration exposed to the nearest possible value.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Duration each pixel is exposed to light in nanoseconds.

  \retval MLResult_InvalidParam Failed to set sensor exposure time due to an invalid input parameter.
  \retval MLResult_Ok Set sensor exposure time.
  \retval MLResult_UnspecifiedFailure Failed to set sensor exposure time due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetSensorExposureTime(MLHandle request_handle, const int64_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets sensor sensitivity.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Sensor sensitivity.

  \retval MLResult_InvalidParam Failed to set sensor sensitivity due to an invalid input parameter.
  \retval MLResult_Ok Set sensor sensitivity.
  \retval MLResult_UnspecifiedFailure Failed to set sensor sensitivity due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetSensorSensitivity(MLHandle request_handle, const int32_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets post raw sensitivity boost.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Post raw sensitivity boost.

  \retval MLResult_InvalidParam Failed to set post raw sensitivity boost due to an invalid input parameter.
  \retval MLResult_Ok Set post raw sensitivity boost.
  \retval MLResult_UnspecifiedFailure Failed to set post raw sensitivity boost due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetPostRawSensitivityBoost(MLHandle request_handle, const int32_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets Effect mode.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Effect mode.

  \retval MLResult_InvalidParam Failed to set effect mode due to an invalid input parameter.
  \retval MLResult_Ok Set effect mode.
  \retval MLResult_UnspecifiedFailure Failed to set effect mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlEffectMode(MLHandle request_handle, const MLCameraMetadataControlEffectMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets exposure time upper limit.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Exposure time upper limit. Null pointer will clear the data.

  \retval MLResult_InvalidParam Failed to set exposure time upper limit due to an invalid input parameter.
  \retval MLResult_Ok Set exposure time upper limit.
  \retval MLResult_UnspecifiedFailure Failed to set exposure time upperlimit due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlExposureUpperTimeLimit(MLHandle request_handle, const int64_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets JPEG GPS coordinates.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data JPEG GPS coordinates – latitude and longitude in degrees, altitude in meters.Null pointer will clear the data.

  \retval MLResult_InvalidParam Failed to set JPEG GPS coordinates due to an invalid input parameter.
  \retval MLResult_Ok Set JPEG GPS coordinates.
  \retval MLResult_UnspecifiedFailure Failed to set JPEG GPS coordinates due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetJpegGPSCoordinates(MLHandle request_handle, const double data[3]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets JPEG timestamp.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data JPEG timestamp in UNIX Epoch time (UTC in seconds since January 1, 1970). Null pointer will clear the data.

  \retval MLResult_InvalidParam Failed to set JPEG timestamp due to an invalid input parameter.
  \retval MLResult_Ok Set JPEG timestamp.
  \retval MLResult_UnspecifiedFailure Failed to set JPEG timestamp due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetJpegGPSTimestamp(MLHandle request_handle, const int64_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets JPEG thumbnail size.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Resolution of embedded JPEG thumbnail. Null pointer will prevent the inclusion of a thumbnail.

  \retval MLResult_InvalidParam Failed to set JPEG thumbnail size due to an invalid input parameter.
  \retval MLResult_Ok Set JPEG thumbnail size.
  \retval MLResult_UnspecifiedFailure Failed to set JPEG thumbnail size due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetJpegThumbnailSize(MLHandle request_handle, const MLCameraMetadataJpegThumbnailSize *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets JPEG quality.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Compression quality of JPEG thumbnail, with 100 being the highest quality, and 1 the lowest.

  \retval MLResult_InvalidParam Failed to set JPEG quality due to an invalid input parameter.
  \retval MLResult_Ok Set JPEG quality.
  \retval MLResult_UnspecifiedFailure Failed to set JPEG quality due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetJpegQuality(MLHandle request_handle, const uint8_t *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets force apply mode.
         Main camera and CV Camera share the same camera hardware resources. When both the cameras are streaming, request metadata properties
         for both cameras are merged and then applied. While merging, the metadata properties from Main Camera take precedence over CV camera
         metadata properties. The force apply mode property can be used to override this. If CV Camera metadata has force apply mode on,
         the CV Camera metadata properties take precedence over Main Camera metadata properties.

  \apilevel 20

  \param[in] request_handle Camera capture request metadata handle acquired from #MLCameraPrepareCapture.
  \param[in] data Force apply mode.

  \retval MLResult_InvalidParam Failed to set force apply mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully set force apply mode.
  \retval MLResult_UnspecifiedFailure Failed to set force apply mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataSetControlForceApplyMode(MLHandle request_handle, const MLCameraMetadataControlForceApplyMode *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Color correction mode.

  \retval MLResult_InvalidParam Failed to obtain color correction due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionModeResultMetadata(MLHandle result_handle, MLCameraMetadataColorCorrectionMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction transform from RGB color space to output linear sRGB.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data 3x3 color correction transform matrix.

  \retval MLResult_InvalidParam Failed to obtain color correction transform due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction transform.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction transform due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionTransformResultMetadata(MLHandle result_handle, MLCameraMetadataRational out_data[3][3]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction aberration.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Color correction aberration mode.

  \retval MLResult_InvalidParam Failed to obtain color correction aberration due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction aberration.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction aberration due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionAberrationModeResultMetadata(MLHandle result_handle, MLCameraMetadataColorCorrectionAberrationMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets color correction gains. The gains in the result metadata are the gains applied by the camera device to the current frame.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data An array of floats for 4 color channel color correction gains.

  \retval MLResult_InvalidParam Failed to obtain color correction gains due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained color correction gains.
  \retval MLResult_UnspecifiedFailure Failed to obtain color correction gains due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetColorCorrectionGainsResultMetadata(MLHandle result_handle, float out_data[4]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE antibanding mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AE antibanding mode.

  \retval MLResult_InvalidParam Failed to obtain AE antibanding mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE antibanding mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE antibanding mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEAntibandingModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlAEAntibandingMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE exposure compensation.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AE exposure compensation.

  \retval MLResult_InvalidParam Failed to obtain AE exposure compensation due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE exposure compensation.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE exposure compensation due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEExposureCompensationResultMetadata(MLHandle result_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-exposure lock.

  When auto-exposure is locked, the algorithm cannot update its parameters and adjust exposure times and sensitivity.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AE lock.

  \retval MLResult_InvalidParam Failed to obtain AE lock due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE lock.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAELockResultMetadata(MLHandle result_handle, MLCameraMetadataControlAELock *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AE control mode.

  \retval MLResult_InvalidParam Failed to obtain AE mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlAEMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-exposure regions.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Auto-exposure regions. Regions array of area_size x 5[xmin, ymin, xmax, ymax, weight]. Coordinates must be between [(0,0), (width, height)).
  \param[out] out_count Number of auto-exposure regions.

  \retval MLResult_InvalidParam Failed to obtain AE regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE regions.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAERegionsResultMetadata(MLHandle result_handle, int32_t out_data[3][5], uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-exposure target FPS range.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Target range over which good exposure can be maintained by adjusting the capture frame rate.

  \retval MLResult_InvalidParam Failed to obtain AE target FPS range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE target FPS range.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE target FPS range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAETargetFPSRangeResultMetadata(MLHandle result_handle, int32_t out_data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AE state.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AE state.

  \retval MLResult_InvalidParam Failed to obtain AE state due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AE state.
  \retval MLResult_UnspecifiedFailure Failed to obtain AE state due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAEStateResultMetadata(MLHandle result_handle, MLCameraMetadataControlAEState *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB lock.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AWB Lock.

  \retval MLResult_InvalidParam Failed to obtain AWB lock due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB lock.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB lock due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBLockResultMetadata(MLHandle result_handle, MLCameraMetadataControlAWBLock *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB state.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AWB state.

  \retval MLResult_InvalidParam Failed to obtain AWB state due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB state.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB state due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBStateResultMetadata(MLHandle result_handle, MLCameraMetadataControlAWBState *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AWB mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AWB mode.

  \retval MLResult_InvalidParam Failed to obtain AWB mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AWB mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AWB mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAWBModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlAWBMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AF mode.

  \retval MLResult_InvalidParam Failed to obtain AF mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlAFMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF trigger.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AF trigger.

  \retval MLResult_InvalidParam Failed to obtain AF trigger due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF trigger.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF trigger due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFTriggerResultMetadata(MLHandle result_handle, MLCameraMetadataControlAFTrigger *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets auto-focus regions.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Auto-focus regions. Regions array of area_size x 5[xmin, ymin, xmax, ymax, weight].
                       Coordinates must be between [(0,0), (width, height)).
  \param[out] out_count Number of auto-focus regions.

  \retval MLResult_InvalidParam Failed to obtain AF regions due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF regions.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF regions due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFRegionsResultMetadata(MLHandle result_handle, int32_t out_data[3][5], uint32_t *out_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF distance range. Both Min and Max are specified as focus distance in diopters.
         The min value specifies the lower bound for focus distance used by Autofocus algorithm and should be
         more than min focus distance which can be queried using MLCameraMetadataGetLensInfoMinimumFocusDistance.
         The max value specifies the upper bound for focus distance used by Autofocus algorithm and should be
         less than hyperfocal distance which can be queried using API MLCameraMetadataGetLensInfoHyperfocalDistance.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AF distance range [min, max].

  \retval MLResult_InvalidParam Failed to obtain AF distance range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF distance range.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF distance range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetAFDistanceRangeResultMetadata(MLHandle result_handle, float out_data[2]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF state.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AF state.

  \retval MLResult_InvalidParam Failed to obtain AF state due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF state.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF state due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFStateResultMetadata(MLHandle result_handle, MLCameraMetadataControlAFState *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets AF scene change detection status.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data AF scene change detected or not.

  \retval MLResult_InvalidParam Failed to obtain AF scene change detection status due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained AF scene change detection status.
  \retval MLResult_UnspecifiedFailure Failed to obtain AF scene change detection status due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlAFSceneChangeResultMetadata(MLHandle result_handle, MLCameraMetadataControlAFSceneChange *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Lens focus distance.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Lens focus distance.

  \retval MLResult_InvalidParam Failed to obtain Lens focus distance range due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained Lens focus distance range.
  \retval MLResult_UnspecifiedFailure Failed to obtain Lens focus distance range due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetLensFocusDistanceResultMetadata(MLHandle result_handle, float *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get Lens state.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Lens state.

  \retval MLResult_InvalidParam Failed to obtain Lens state due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained Lens state.
  \retval MLResult_UnspecifiedFailure Failed to obtain Lens state due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetLensStateResultMetadata(MLHandle result_handle, MLCameraMetadataLensState *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Obtained mode.

  \retval MLResult_InvalidParam Failed to obtain mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlMode *out_data);
/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Scene mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Scene mode.

  \retval MLResult_InvalidParam Failed to obtain scene mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained scene mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain scene mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlSceneModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlSceneMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor exposure time.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Duration each pixel is exposed to light in nanoseconds.

  \retval MLResult_InvalidParam Failed to obtain sensor exposure time due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor exposure time.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor exposure time due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorExposureTimeResultMetadata(MLHandle result_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor sensitivity.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Sensor sensitivity.

  \retval MLResult_InvalidParam Failed to obtain sensor sensitivity due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor sensitivity.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor sensitivity due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorSensitivityResultMetadata(MLHandle result_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets post raw sensitivity boost.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Post raw sensitivity boost.

  \retval MLResult_InvalidParam Failed to obtain post raw sensitivity boost due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained post raw sensitivity boost.
  \retval MLResult_UnspecifiedFailure Failed to obtain post raw sensitivity boost due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetPostRawSensitivityBoostResultMetadata(MLHandle result_handle, int32_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets frame captured timestamp.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Timestamp in nanoseconds when captured.

  \retval MLResult_InvalidParam Failed to obtain frame captured timestamp due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained frame captured timestamp.
  \retval MLResult_UnspecifiedFailure Failed to obtain frame captured timestamp due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorTimestampResultMetadata(MLHandle result_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets sensor frame duration.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Sensor frame duration.

  \retval MLResult_InvalidParam Failed to obtain sensor frame duration due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained sensor frame duration.
  \retval MLResult_UnspecifiedFailure Failed to obtain sensor frame duration due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetSensorFrameDurationResultMetadata(MLHandle result_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets Effect mode.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Effect mode.

  \retval MLResult_InvalidParam Failed to obtain effect mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained effect mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain effect mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlEffectModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlEffectMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets exposure time upper limit.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Exposure time upper limit.

  \retval MLResult_InvalidParam Failed to obtain exposure time upper limit due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained exposure time upper limit.
  \retval MLResult_UnspecifiedFailure Failed to obtain exposure time upperlimit due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlExposureUpperTimeLimitResultMetadata(MLHandle result_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG GPS coordinates.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data JPEG GPS coordinates – latitude and longitude in degrees, altitude in meters.

  \retval MLResult_InvalidParam Failed to obtain JPEG GPS coordinates due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG GPS coordinates.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG GPS coordinates due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegGPSCoordinatesResultMetadata(MLHandle result_handle, double out_data[3]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG timestamp.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data JPEG timestamp in UNIX Epoch time (UTC in seconds since January 1, 1970).

  \retval MLResult_InvalidParam Failed to obtain JPEG timestamp due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG timestamp.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG timestamp due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegGPSTimestampResultMetadata(MLHandle result_handle, int64_t *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG thumbnail size.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Resolution of embedded JPEG thumbnail. When set to 0, thumbnail will not be included.

  \retval MLResult_InvalidParam Failed to obtain JPEG thumbnail size due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG thumbnail size.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG thumbnail size due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegThumbnailSizeResultMetadata(MLHandle result_handle, MLCameraMetadataJpegThumbnailSize *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets force apply mode.
         Main camera and CV Camera share the same camera hardware resources. When both the cameras are streaming, request metadata properties
         for both cameras are merged and then applied. While merging, the metadata properties from Main Camera take precedence over CV camera
         metadata properties. The force apply mode property can be used to override this. If CV Camera metadata has force apply mode on,
         the CV Camera metadata properties take precedence over Main Camera metadata properties.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Force apply mode.

  \retval MLResult_InvalidParam Failed to obtain force apply mode due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained force apply mode.
  \retval MLResult_UnspecifiedFailure Failed to obtain force apply mode due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetControlForceApplyModeResultMetadata(MLHandle result_handle, MLCameraMetadataControlForceApplyMode *out_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets JPEG quality.

  \apilevel 20

  \param[in] result_handle Camera capture result metadata handle returned in #MLCameraCaptureCallbacks.
  \param[out] out_data Compression quality of JPEG thumbnail, with 100 being the highest quality, and 1 the lowest.

  \retval MLResult_InvalidParam Failed to obtain JPEG quality due to an invalid input parameter.
  \retval MLResult_Ok Successfully obtained JPEG quality.
  \retval MLResult_UnspecifiedFailure Failed to obtain JPEG quality due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraMetadataGetJpegQualityResultMetadata(MLHandle result_handle, uint8_t *out_data);

/*! \} */

ML_EXTERN_C_END
