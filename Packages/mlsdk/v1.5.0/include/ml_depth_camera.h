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
  \addtogroup DCam Depth Camera
  \ingroup PixelSensors
  \brief APIs to access the depth camera data.

  \experimental This is an experimental API which may be modified or removed
                without any prior notice.

   Using the depth camera may result in the following APIs returning stale data:
     - Meshing (ml_meshing2.h).
     - Planes (ml_planes.h).

  \{
*/

enum {
  /*! Default distortion vector size. */
  MLDepthCameraIntrinsics_MaxDistortionCoefficients = 5
};

/*!
  \brief Enumeration of depth camera streams.

  \apilevel 29
*/
typedef enum MLDepthCameraStream {
  /*! None. */
  MLDepthCameraStream_None = 0,
  /*!
    \brief Long range stream.
    Under normal operations long range stream has a maximum frequency of 5fps
    and a range from 1m up to 5m, in some cases this can go as far 7.5m.
  */
  MLDepthCameraStream_LongRange = 1 << 0,
  /*!
    \brief Short range stream.
    Under normal operations short range stream has a maximum frequency of 60fps
    and a range from 0.2m up to 0.9m.
  */
  MLDepthCameraStream_ShortRange = 1 << 1,
  /*! Ensure enum is represented as 32 bits. */
  MLDepthCameraStream_Ensure32Bits = 0x7FFFFFFF
} MLDepthCameraStream;

/*!
  \brief Enumeration of camera stream used when capturing a frame.

  \apilevel 29
*/
typedef enum MLDepthCameraFrameType {
  /*!
    \brief Frame captured using #MLDepthCameraStream_LongRange stream.
  */
  MLDepthCameraFrameType_LongRange = 0,
  /*!
    \brief Frame captured using #MLDepthCameraStream_ShortRange stream.
  */
  MLDepthCameraFrameType_ShortRange = 1,
  MLDepthCameraFrameType_Count = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLDepthCameraFrameType_Ensure32Bits = 0x7FFFFFFF
} MLDepthCameraFrameType;

/*!
  \brief Enumeration of possible frame rates.

  \apilevel 29
*/
typedef enum MLDepthCameraFrameRate {
  MLDepthCameraFrameRate_1FPS = 0,
  MLDepthCameraFrameRate_5FPS = 1,
  MLDepthCameraFrameRate_25FPS = 2,
  MLDepthCameraFrameRate_30FPS = 3,
  MLDepthCameraFrameRate_50FPS = 4,
  MLDepthCameraFrameRate_60FPS = 5,
  /*! Ensure enum is represented as 32 bits. */
  MLDepthCameraFrameRate_Ensure32Bits = 0x7FFFFFFF
} MLDepthCameraFrameRate;

/*!
  \brief Enumeration of flags to select data requested from depth camera.
*/
typedef enum MLDepthCameraFlags {
  /*! None. */
  MLDepthCameraFlags_None = 0,
  /*! Enable MLDepthCameraDepthImage. See #MLDepthCameraDepthImage for more details. */
  MLDepthCameraFlags_DepthImage = 1 << 0,
  /*! Enable MLDepthCameraConfidenceBuffer. See #MLDepthCameraConfidenceBuffer for more details. */
  MLDepthCameraFlags_Confidence = 1 << 1,
  /*! Enable MLDepthCameraDepthFlagsBuffer. See #MLDepthCameraDepthFlagsBuffer for more details. */
  MLDepthCameraFlags_DepthFlags = 1 << 2,
  /*! Enable MLDepthCameraAmbientRawDepthImage. See #MLDepthCameraAmbientRawDepthImage for more details. */
  MLDepthCameraFlags_AmbientRawDepthImage = 1 << 3,
  /*! Enable MLDepthCameraRawDepthImage. See #MLDepthCameraRawDepthImage for more details. */
  MLDepthCameraFlags_RawDepthImage = 1 << 4,
  /*! Ensure enum is represented as 32 bits. */
  MLDepthCameraFlags_Ensure32Bits = 0x7FFFFFFF
} MLDepthCameraFlags;

/*!
  \brief Enumeration of flags to select data requested from depth camera.
*/
typedef enum MLDepthCameraDepthFlags {
  /*!
    \brief Valid pixel.
    Indicates that there is no additional flag data for this pixel.
  */
  MLDepthCameraDepthFlags_Valid = 0 << 0,
  /*!
    \brief Invalid.
     This bit is set to one to indicate that one or more flags from below have
     been set. Depending on the use case the application can correlate the
     flag data and corresponding pixel data to determine how to handle the pixel
     data.
  */
  MLDepthCameraDepthFlags_Invalid = 1 << 0,
  /*!
    \brief Pixel saturated.
    The pixel intensity is either below the min or the max threshold value.
  */
  MLDepthCameraDepthFlags_Saturated = 1 << 1,
  /*!
    \brief Inconsistent data.
    Inconsistent data received when capturing frames. This can happen due to
    fast motion.
  */
  MLDepthCameraDepthFlags_Inconsistent = 1 << 2,
  /*!
    \brief Low signal.
    Pixel has very low signal to noise ratio. One example of when this can
    happen is for pixels in far end of the range.
  */
  MLDepthCameraDepthFlags_LowSignal = 1 << 3,
  /*!
    \brief Flying pixel.
    This typically happens when there is step jump in the distance of adjoining
    pixels in the scene. Example: When you open a door looking into the room the
    edges along the door's edges can cause flying pixels.
  */
  MLDepthCameraDepthFlags_FlyingPixel = 1 << 4,
  /*!
    \brief Masked.
    If this bit is on it indicates that the corresponding pixel may not be within
    the illuminator's illumination cone.
  */
  MLDepthCameraDepthFlags_Masked = 1 << 5,
  /*!
    \brief SBI.
    This bit will be set when there is high noise.
  */
  MLDepthCameraDepthFlags_SBI = 1 << 8,
  /*!
    \brief Stray light.
    This could happen when there is another light source apart from the depth
    camera illuminator. This could also lead to MLDepthCameraDepthFlags_LowSignal.
  */
  MLDepthCameraDepthFlags_StrayLight = 1 << 9,
  /*!
    \brief Connected component.
    If a small group of MLDepthCameraDepthFlags_Valid is surrounded by a set of
    MLDepthCameraDepthFlags_Invalid then this bit will be set to 1.
  */
  MLDepthCameraDepthFlags_ConnectedComponent = 1 << 10,
  /*! Ensure enum is represented as 32 bits. */
  MLDepthCameraDepthFlags_Ensure32Bits = 0x7FFFFFFF
} MLDepthCameraDepthFlags;

/*!
  \brief Structure to encapsulate the camera config for a specific stream.

  \apilevel 29
*/
typedef struct MLDepthCameraStreamConfig {
  /*! Flags to configure the depth data. */
  uint32_t flags;
  /*! Exposure in microseconds. */
  uint32_t exposure;
  /*! Frame rate. */
  MLDepthCameraFrameRate frame_rate;
} MLDepthCameraStreamConfig;

/*!
  \brief Structure to encapsulate the camera settings.

  This structure must be initialized by calling #MLDepthCameraSettingsInit
  before use.

  These are supported configurations:
  <table>
  <caption id="configs_table"/>
  <tr><th>Streams     <th>Exposure limits [us]        <th>Frame rate [FPS]
  <tr><td>Long Range  <td>250 - 2000                  <td>1, 5
  <tr><td>Short Range <td>50 - 375                    <td>On 50Hz PLC: 5, 25, 50<br>On 60Hz PLC: 5, 30, 60
  </table>

  Use #MLDepthCameraGetCapabilities to get a list of available configurations.

  \note The system may not be able to service all the requested streams at any
        given time. This parameter is treated as a hint and data will be
        provided for the requested streams if available.

  \note The API only supports a single stream. In a future release support for
        multiple streams will be added.

  \apilevel 29
*/
typedef struct MLDepthCameraSettings {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Depth camera stream.

    See #MLDepthCameraStream for more details.

  */
  uint32_t streams;
  /*!
    \brief Controls for each of the depth camera streams.

    Only controls for streams enabled via #streams field will be read.
    Use #MLDepthCameraFrameType enumeration for indexing.
  */
  MLDepthCameraStreamConfig stream_configs[MLDepthCameraFrameType_Count];
} MLDepthCameraSettings;

/*!
  \brief Initialize the connect handle structure.
  Shall be called before calling #MLDepthCameraConnect().

  \apilevel 29

  \param[in,out] inout_handle MLDepthCameraSettings structure to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLDepthCameraSettingsInit(MLDepthCameraSettings *inout_handle) {
  if (inout_handle) {
    memset(inout_handle, 0, sizeof(MLDepthCameraSettings));
    inout_handle->version = 2;
    inout_handle->streams = MLDepthCameraStream_LongRange;

    MLDepthCameraStreamConfig *config = &inout_handle->stream_configs[MLDepthCameraFrameType_LongRange];
    config->flags = MLDepthCameraFlags_DepthImage;
    config->exposure = 1600;
    config->frame_rate = MLDepthCameraFrameRate_5FPS;

    config = &inout_handle->stream_configs[MLDepthCameraFrameType_ShortRange];
    config->flags = MLDepthCameraFlags_DepthImage;
    config->exposure = 375;
    config->frame_rate = MLDepthCameraFrameRate_5FPS;
  }
}

/*!
  \brief Depth camera intrinsic parameters.

  \apilevel 29
*/
typedef struct MLDepthCameraIntrinsics {
  /*! Camera width. */
  uint32_t width;
  /*! Camera height. */
  uint32_t height;
  /*! Camera focal length. */
  MLVec2f focal_length;
  /*! Camera principal point. */
  MLVec2f principal_point;
  /*! Field of view in degrees. */
  float fov;
  /*!
    \brief Distortion vector.
    The distortion co-efficients are in the following order: [k1, k2, p1, p2, k3].
   */
  double distortion[MLDepthCameraIntrinsics_MaxDistortionCoefficients];
} MLDepthCameraIntrinsics;

/*!
  \brief Structure to encapsulate per plane info for each camera frame.

  \apilevel 29
*/
typedef struct MLDepthCameraFrameBuffer {
  /*! Width of the buffer in pixels. */
  uint32_t width;
  /*! Height of the buffer in pixels. */
  uint32_t height;
  /*! Stride of the buffer in bytes. */
  uint32_t stride;
  /*! Number of bytes used to represent a single value. */
  uint32_t bytes_per_unit;
  /*! Number of bytes in the buffer. */
  uint32_t size;
  /*! Buffer data. */
  void *data;
} MLDepthCameraFrameBuffer;

/*!
  \brief Depth image.

  Depth image stores the depth data from the depth camera. Depth is represented in
  meters and gives the radial distance of the real world location from the
  depth camera coordinate frame. See MLDepthCameraIntrinsics and
  MLDepthCameraData.camera_pose for more details.

  Cast the MLDepthCameraFrameBuffer.data to float data type.

*/
typedef MLDepthCameraFrameBuffer MLDepthCameraDepthImage;

/*!
  \brief Confidence score.

  Confidence buffer stores the confidence values for each pixel in the
  MLDepthCameraDepthImage. The confidence score is derived from the sensor
  noise and it is not normalized. The higher the value the higher the
  confidence. Applications can determine what confidence threshold to use
  based on their use case.

  Cast the MLDepthCameraFrameBuffer.data to float data type.
*/
typedef MLDepthCameraFrameBuffer MLDepthCameraConfidenceBuffer;

/*!
  \brief Flags.

  Each pixel in the MLDepthCameraDepthImage will have an associated set of flags.

  Cast the MLDepthCameraFrameBuffer.data to uint32_t data type.
*/
typedef MLDepthCameraFrameBuffer MLDepthCameraDepthFlagsBuffer;

/*!
  \brief Ambient raw depth image.

  This is the raw depth camera sensor data captured without the depth camera
  illumination and corresponds to the amount of ambient light incident on the
  sensor.

  Cast the MLDepthCameraFrameBuffer.data to float data type.
*/
typedef MLDepthCameraFrameBuffer MLDepthCameraAmbientRawDepthImage;

/*!
  \brief Raw depth image.

  This is the raw depth camera sensor data captured with the depth camera
  illumination and corresponds to the amount of total light incident on the
  sensor.

  Cast the MLDepthCameraFrameBuffer.data to float data type.
*/
typedef MLDepthCameraFrameBuffer MLDepthCameraRawDepthImage;

/*!
  \brief Structure to encapsulate output data for each camera sensor.

  \apilevel 29
*/
typedef struct MLDepthCameraFrame {
  /*! A 64bit integer to index the frame number associated with this frame. */
  int64_t frame_number;
  /*! Frame timestamp specifies the time at which the frame was captured. */
  MLTime frame_timestamp;
  /*! Depth camera stream used for capturing this frame. */
  MLDepthCameraFrameType frame_type;
  /*! Depth camera pose in the world co-ordinate system. */
  MLTransform camera_pose;
  /*! Camera intrinsic parameters. */
  MLDepthCameraIntrinsics intrinsics;
  /*! Depth image. */
  MLDepthCameraDepthImage *depth_image;
  /*! Confidence score. */
  MLDepthCameraConfidenceBuffer *confidence;
  /*! Depth flags. */
  MLDepthCameraDepthFlagsBuffer *flags;
  /*!
    \brief Ambient raw depth image.
    The illuminator in the sensor is modulated with a system determined frequency.
    This is the raw sensor data captured when the illuminator is off.
  */
  MLDepthCameraAmbientRawDepthImage *ambient_raw_depth_image;
  /*!
    \brief Raw depth image.
    The illuminator in the sensor is modulated with a system determined frequency.
    This is the raw sensor data captured when the illuminator is on.
  */
  MLDepthCameraRawDepthImage *raw_depth_image;
} MLDepthCameraFrame;

/*!
  \brief Structure to encapsulate output data for each camera stream.

  This structure must be initialized by calling #MLDepthCameraDataInit
  before use.

  \apilevel 29
*/
typedef struct MLDepthCameraData {
  /*! Version of this structure. */
  uint32_t version;
  /*! Number of camera frames populated. */
  uint8_t frame_count;
  /*! Camera frame data. The number of frames is specified by frame_count. */
  MLDepthCameraFrame *frames;
} MLDepthCameraData;

/*!
  \brief Initialize MLDepthCameraData with version.

  \apilevel 29

  \param[in,out] inout_depth_camera_data Set up the version for inout_depth_camera_data.
*/
ML_STATIC_INLINE void MLDepthCameraDataInit(MLDepthCameraData *inout_depth_camera_data) {
  if (inout_depth_camera_data) {
    memset(inout_depth_camera_data, 0, sizeof(MLDepthCameraData));
    inout_depth_camera_data->version = 3;
  }
}

/*!
  \brief Structure to encapsulate a possible configuration for a single stream.
  Can be used to understand possible values for a specific #stream_configs element
  in #MLDepthCameraSettings.

  The capabilities supported by the depth camera can be queried
  with #MLDepthCameraGetCapabilities().

  \apilevel 29
*/
typedef struct MLDepthCameraStreamCapability {
  /*! Stream for which this capability can be applied. */
  MLDepthCameraStream stream;
  /*! Minimum sensor exposure in microseconds. */
  uint32_t min_exposure;
  /*! Maximum sensor exposure in microseconds. */
  uint32_t max_exposure;
  /*! Frame rate. */
  MLDepthCameraFrameRate frame_rate;
} MLDepthCameraStreamCapability;


/*!
  \brief Structure to encapsulate a possible set of streams configuration.
  Such set describes a possible way of setting #stream_configs in #MLDepthCameraSettings
  and may hold multiple #MLDepthCameraStreamCapability for different streams.

  Whole #stream_capabilities array describe a single configuration. Using only part
  of it is not recommended.

  The capabilities supported by the depth camera can be queried
  with #MLDepthCameraGetCapabilities().

  \apilevel 29
*/
typedef struct MLDepthCameraCapability {
  /*! Size of #stream_capabilities array. */
  uint8_t size;
  /*! Array of #MLDepthCameraStreamCapability elements. */
  MLDepthCameraStreamCapability *stream_capabilities;
} MLDepthCameraCapability;

/*!
  \brief Structure to encapsulate a list of possible stream configurations.

  User should be able to use any of the capabilities from the list.
  They are grouped in usable sets of configurations - one set may contain
  different #MLDepthCameraStreamCapability for different streams.
  For more information see #MLDepthCameraCapability.

  \apilevel 29
*/
typedef struct MLDepthCameraCapabilityList {
  /*! Size of #capabilities array. */
  uint8_t size;
  /*! Array of #MLDepthCameraCapability elements. */
  MLDepthCameraCapability *capabilities;
} MLDepthCameraCapabilityList;

/*!
  \brief Structure to encapsulate camera capabilities filtering.

  The capabilities supported by the depth camera can be queried
  with #MLDepthCameraGetCapabilities().

  \apilevel 29
*/
typedef struct MLDepthCameraCapabilityFilter {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Streams for which capabilities will be filtered.

    Can hold multiple #MLDepthCameraStream values.
  */
  uint32_t streams;
} MLDepthCameraCapabilityFilter;

/*!
  \brief Initialize the capabilities filtering structure.
  Shall be called before calling MLDepthCameraGetCapabilities().

  \apilevel 29

  \param[in,out] inout_handle MLDepthCameraCapabilityFilter structure to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLDepthCameraCapabilityFilterInit(MLDepthCameraCapabilityFilter *inout_handle) {
  if (inout_handle) {
    memset(inout_handle, 0, sizeof(MLDepthCameraCapabilityFilter));
    inout_handle->version = 1;
  }
}

/*!
  \brief Connect to depth camera.

  \apilevel 29

  \param[in] settings A pointer to MLDepthCameraSettings structure.
  \param[out] out_handle A pointer to camera handle to be used in later APIs.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Connected to camera device(s) successfully.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions com.magicleap.permission.DEPTH_CAMERA (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLDepthCameraConnect(const MLDepthCameraSettings *settings, MLHandle *out_handle);

/*!
  \brief Update the depth camera settings.

  \apilevel 29

  \param[in] handle Camera handle obtained from #MLDepthCameraConnect.
  \param[in] settings Pointer to #MLDepthCameraSettings.

  \retval MLResult_InvalidParam Invalid handle.
  \retval MLResult_Ok Settings updated successfully.
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLDepthCameraUpdateSettings(MLHandle handle, const MLDepthCameraSettings *settings);

/*!
  \brief Query the depth camera stream capabilities.

  Retrieves the capabilities supported by the depth camera based on the provided filter.
  Overview of the capabilities can be seen in the \ref configs_table "configuration table".

  After each call, a corresponding call to #MLDepthCameraReleaseCapabilities should be made
  to release allocated resources.

  \apilevel 29

  \param[in] handle Camera handle obtained from #MLDepthCameraConnect.
  \param[in] filter Pointer to initialized #MLDepthCameraCapabilityFilter structure. Used for filtering.
  \param[out] out_caps Pointer to initialized #MLDepthCameraCapabilityList structure.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok API call completed successfully.

   \permissions None
*/
ML_API MLResult ML_CALL MLDepthCameraGetCapabilities(MLHandle handle, const MLDepthCameraCapabilityFilter *filter, MLDepthCameraCapabilityList *out_caps);

/*!
  \brief Release resources allocated with #MLDepthCameraGetCapabilities.

  \apilevel 29

  \param[in] handle Camera handle obtained from #MLDepthCameraConnect.
  \param[out] out_caps Pointer to #MLDepthCameraCapabilityList filled by the call to #MLDepthCameraGetCapabilities.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok API call completed successfully.

   \permissions None
*/
ML_API MLResult ML_CALL MLDepthCameraReleaseCapabilities(MLHandle handle, MLDepthCameraCapabilityList *out_caps);

/*!
  \brief Poll for Frames.

  Returns #MLDepthCameraData with this latest data when available. The memory is
  owned by the system. Application should copy the data it needs to cache it
  and then release the memory by calling #MLDepthCameraReleaseCameraData.

  This is a blocking call. API is not thread safe.

  If there are no new depth data frames within the timeout_ms duration then the
  API will return MLResult_Timeout.

  \apilevel 29

  \param[in] handle Camera handle obtained from #MLDepthCameraConnect.
  \param[in] timeout_ms Timeout in milliseconds.
  \param[out] out_data Depth camera data. Should be an initialized #MLDepthCameraData object.

  \retval MLResult_InvalidParam Invalid handle.
  \retval MLResult_Ok Depth camera data fetched successfully.
  \retval MLResult_Timeout Returned because no new frame available at this time.
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLDepthCameraGetLatestDepthData(MLHandle handle, uint64_t timeout_ms, MLDepthCameraData *out_data);

/*!
  \brief Releases specified #MLDepthCameraData object.

  This function should be called exactly once for each successfull call to
  #MLDepthCameraGetLatestCameraData.

  \param[in] handle Camera handle obtained from #MLDepthCameraConnect.
  \param[in] depth_camera_data Pointer to a valid #MLDepthCameraData object.

  \retval MLResult_Ok Successfully released depth camera data.
  \retval MLResult_InvalidParam depth_camera_data parameter was not valid (NULL).
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLDepthCameraReleaseDepthData(MLHandle handle, MLDepthCameraData *depth_camera_data);

/*!
  \brief Disconnect from depth camera.

  This will disconnect from the depth camera.

  \apilevel 29

  \param[in] handle Camera handle obtained from #MLDepthCameraConnect.

  \retval MLResult_InvalidParam Invalid handle.
  \retval MLResult_Ok Disconnected camera successfully.
  \retval MLResult_UnspecifiedFailure Failed to disconnect camera.

  \permissions None
*/
ML_API MLResult ML_CALL MLDepthCameraDisconnect(MLHandle handle);

/*! \} */

ML_EXTERN_C_END

