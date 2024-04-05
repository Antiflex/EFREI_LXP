// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
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
#include "ml_types.h"

#include <string.h>

ML_EXTERN_C_BEGIN

/*!
  \addtogroup PixelSensors Pixel Sensors
  \sharedobject perception.magicleap
  \brief APIs to access pixel sensors data.
*/

/*!
  \addtogroup ECam Eye Camera
  \ingroup PixelSensors
  \brief APIs to access the eye camera data.

  \experimental This is an experimental API which may be modified or removed without
                any prior notice.

  \{
*/

/*!
  \brief Camera Identifier.

  Enumeration of all the available eye camera sensors.
*/
typedef enum MLEyeCameraIdentifier{
  /*! None. */
  MLEyeCameraIdentifier_None = 0,
  /*! Left temple eye camera. */
  MLEyeCameraIdentifier_LeftTemple = 1 << 0,
  /*! Left nasal eye camera. */
  MLEyeCameraIdentifier_LeftNasal = 1 << 1,
  /*! Right nasal eye camera. */
  MLEyeCameraIdentifier_RightNasal = 1 << 2,
  /*! Right temple eye camera. */
  MLEyeCameraIdentifier_RightTemple = 1 << 3,
  /*! All Eye cameras. */
  MLEyeCameraIdentifier_All = MLEyeCameraIdentifier_LeftTemple |
                              MLEyeCameraIdentifier_LeftNasal  |
                              MLEyeCameraIdentifier_RightNasal |
                              MLEyeCameraIdentifier_RightTemple,
  /*! Ensure enum is represented as 32 bits. */
  MLEyeCameraIdentifier_Ensure32Bits = 0x7FFFFFFF
} MLEyeCameraIdentifier;

/*!
  \brief A structure to encapsulate the camera settings.

  This structure must be initialized by calling #MLEyeCameraSettingsInit before use.

  \apilevel 26
*/
typedef struct MLEyeCameraSettings {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Eye cameras that need to be enabled.

     See #MLEyeCameraIdentifier for more details. If you want to request
     frames from different eye camera then "OR" the cameras of interest to
     the app.
  */
  uint32_t cameras;
} MLEyeCameraSettings;

/*!
  \brief Initialize the camera settings structure.
  Shall be called before calling MLEyeCameraConnect().

  \apilevel 26

  \param[in,out] inout_settings MLEyeCameraSettings structure to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLEyeCameraSettingsInit(MLEyeCameraSettings *inout_settings) {
  if (inout_settings) {
    memset(inout_settings, 0, sizeof(MLEyeCameraSettings));
    inout_settings->version = 1;
    inout_settings->cameras = MLEyeCameraIdentifier_All;
  }
}

/*!
  \brief A structure to encapsulate per plane info for each camera frame.

  \apilevel 26
*/
typedef struct MLEyeCameraFrameBuffer {
  /*! Width of the output image in pixels. */
  uint32_t width;
  /*! Height of the output image in pixels. */
  uint32_t height;
  /*! Stride of the output image in bytes. */
  uint32_t stride;
  /*! Number of bytes used to represent a pixel. */
  uint32_t bytes_per_pixel;
  /*! Distance between 2 consecutive pixels in bytes. */
  uint32_t pixel_stride;
  /*! Number of bytes in the image output data. */
  uint32_t size;
  /*! Image data. */
  uint8_t *data;
} MLEyeCameraFrameBuffer;

/*!
  \brief A structure to encapsulate output data for each camera sensor.

  \apilevel 26
*/
typedef struct MLEyeCameraFrame {
  /*! Camera Identifier specifies which camera is associated with this frame. */
  MLEyeCameraIdentifier camera_id;
  /*! Frame number associated with this frame. */
  int64_t frame_number;
  /*! Frame timestamp specifies the time at which the frame was captured. */
  MLTime timestamp;
  /*! Frame buffer data. */
  MLEyeCameraFrameBuffer frame_buffer;
} MLEyeCameraFrame;

/*!
  \brief A structure to encapsulate all the eye camera data.

  This structure must be initialized by calling #MLEyeCameraDataInit before use.

  \apilevel 26
*/
typedef struct MLEyeCameraData {
  /*! Version of this structure. */
  uint32_t version;
  /*! Number of camera frames. */
  uint8_t frame_count;
  /*! Camera frame data. The number of frames is specified by frame_count. */
  MLEyeCameraFrame *frames;
} MLEyeCameraData;

/*!
  \brief Initialize MLEyeCameraData with version.

  \apilevel 26

  \param[in,out] inout_eye_camera_data Set up the version for inout_eye_camera_data.
*/
ML_STATIC_INLINE void MLEyeCameraDataInit(MLEyeCameraData *inout_eye_camera_data) {
  if (inout_eye_camera_data) {
    memset(inout_eye_camera_data, 0, sizeof(MLEyeCameraData));
    inout_eye_camera_data->version = 1;
  }
}

/*!
  \brief Connect to eye cameras.

  \apilevel 26

  \param[in] settings A pointer to MLEyeCameraSettings structure.
  \param[out] out_handle A pointer to camera handle to be used in later APIs.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Connected to camera device(s) successfully.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions com.magicleap.permission.EYE_CAMERA (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLEyeCameraConnect(const MLEyeCameraSettings *settings, MLHandle *out_handle);


/*!
  \brief Update the eye camera settings.

  \apilevel 26

  \param[in] handle Camera handle obtained from #MLEyeCameraConnect.
  \param[in] settings Pointer to #MLEyeCameraSettings.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Settings updated successfully.
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCameraUpdateSettings(MLHandle handle, const MLEyeCameraSettings *settings);

/*!
  \brief Poll for Frames.

  Returns #MLEyeCameraData with this latest data when available. The memory is
  owned by the system. Application should copy the data it needs to cache and
  release the memory by calling #MLEyeCameraReleaseCameraData.

  This is a blocking call. API is not thread safe.

  If there are no new camera frames within the timeout_ms duration then the
  API will return MLResult_Timeout.

  \apilevel 26

  \param[in] handle Camera handle obtained from #MLEyeCameraConnect.
  \param[in] timeout_ms Timeout in milliseconds.
  \param[out] out_data Eye camera data. Will be set to NULL if no valid data is
              available at this time.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Camera frames fetched successfully.
  \retval MLResult_Timeout Returned because no new frame available at this time.
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCameraGetLatestCameraData(MLHandle handle, uint64_t timeout_ms, MLEyeCameraData *out_data);

/*!
  \brief Releases specified #MLEyeCameraData object.

  This function should be called exactly once for each call to #MLEyeCameraGetLatestCameraData.

  \apilevel 26

  \param[in] handle Camera handle obtained from #MLEyeCameraConnect.
  \param[in] eye_camera_data Pointer to a valid #MLEyeCameraData object.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Successfully released eye camera data.
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCameraReleaseCameraData(MLHandle handle, MLEyeCameraData *eye_camera_data);

/*!
  \brief Disconnect from eye camera(s).

  This will disconnect from all the eye camera(s) currently connected.

  \apilevel 26

  \param[in] handle Camera handle obtained from #MLEyeCameraConnect.

  \retval MLResult_InvalidParam Invalid handle.
  \retval MLResult_Ok Disconnected camera(s) successfully.
  \retval MLResult_UnspecifiedFailure Failed to disconnect camera(s).

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCameraDisconnect(MLHandle handle);

/*! \} */

ML_EXTERN_C_END

