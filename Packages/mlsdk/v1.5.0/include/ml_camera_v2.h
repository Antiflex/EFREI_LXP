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
#include "ml_types.h"

#include <string.h>

ML_EXTERN_C_BEGIN

/*!
  \defgroup Camera Camera
  \addtogroup Camera
  \sharedobject camera.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK CAMERA APIs:
            https://developer.android.com/training/camera2
            https://developer.android.com/ndk/reference/group/camera

  \brief APIs for accessing Camera Device and to do Camera Capture.

  # Supported Camera Modes, Resolutions, Capture Type, Formats and FrameRates
  <table>
  <tr><th>Camera                      <th>Mode        <th>Resolution <th> Capture Type <th>Formats   <th>FrameRate
  <tr><td rowspan="48">Main<td rowspan="12"><pre>Cam_Only    </pre><td rowspan="3">640x480<br>1280x720<br>1280x960<br>1440x1080<br>1920x1080<br>2048x1536
                                                                     <td rowspan="1">Preview<td rowspan="1">YUV<td rowspan="1">15/30/60
  <tr>                                                               <td rowspan="1">Image<td rowspan="1">YUV/JPEG<td rowspan="1">15/30/60
  <tr>                                                               <td rowspan="1">Video<td rowspan="1">YUV/RGB/Compressed<td rowspan="1">15/30/60
  <tr><td rowspan="3"><br>2880x2160<br>3840x2160<br>4096x3072<br><br><td rowspan="1">Preview<td rowspan="1">YUV<td rowspan="1">15/30
  <tr>                                                               <td rowspan="1">Image<td rowspan="1">YUV/JPEG<td rowspan="1">15/30
  <tr>                                                               <td rowspan="1">Video<td rowspan="1">YUV/RGB/Compressed<td rowspan="1">15/30
  </table>
  Note: 15Fps only supported in Auto Exposure Mode.
        <br>When multiple streams are configured frame rate is constrained by max resolution.
        <br>FrameRate_None can be used when only Image capture_type is used.

  <br>
  <br>
  <table>
  <tr><th>Camera                      <th>Mode        <th>Resolution <th> Capture Type <th>Formats   <th>FrameRate
  <tr><td rowspan="48"><pre>CV  </pre><td rowspan="24"><pre>Cam_Only    </pre><td rowspan="2">640x480<br>1280x720<br>1280x960<br>1440x1080<br>1920x1080<br>2048x1536
                                                                              <td rowspan="1">Image<td rowspan="1">YUV<td rowspan="1">15/30/60
  <tr>                                                                        <td rowspan="1">Video<td rowspan="1"><pre>YUV/RGB           </pre><td rowspan="1">15/30/60
  <tr>                                                                        <td rowspan="2"><br>2880x2160<br>3840x2160<br>4096x3072<br><br>
                                                                              <td rowspan="1">Image<td rowspan="1">YUV<td rowspan="1">15/30
  <tr>                                                                        <td rowspan="1">Video<td rowspan="1">YUV/RGB          <td rowspan="1">15/30
  </table>
  Note: 15Fps only supported in Auto Exposure Mode
        <br>FrameRate_None can be used when only Image capture_type is used.

  <br>
  <br>
  <table>
  <tr><th>Camera                      <th>Mode        <th>Resolution <th> Capture Type <th>Formats   <th>FrameRate
  <tr><td rowspan="48">Main<td rowspan="24">MR/Virtual_Only<td rowspan="2">648x720  <td rowspan="1">Image<td rowspan="1">RBG/JPEG<td rowspan="1">30/60
  <tr>                                                                              <td rowspan="1">Video<td rowspan="1"><pre>RGB/Compressed    </pre><td rowspan="1">30/60
  <tr>                                                     <td rowspan="2">960x720  <td rowspan="1">Image<td rowspan="1">RBG/JPEG<td rowspan="1">30/60
  <tr>                                                                              <td rowspan="1">Video<td rowspan="1">RGB/Compressed<td rowspan="1">30/60
  <tr>                                                     <td rowspan="2">972x1080 <td rowspan="1">Image<td rowspan="1">RBG/JPEG<td rowspan="1">30/60
  <tr>                                                                              <td rowspan="1">Video<td rowspan="1">RGB/Compressed<td rowspan="1">30/60
  <tr>                                                     <td rowspan="2">1440x1080<td rowspan="1">Image<td rowspan="1">RBG/JPEG<td rowspan="1">30/60
  <tr>                                                                              <td rowspan="1">Video<td rowspan="1">RGB/Compressed<td rowspan="1">30/60
  <tr>                                                     <td rowspan="2">1944x2160<td rowspan="1">Image<td rowspan="1">RBG/JPEG<td rowspan="1">30
  <tr>                                                                              <td rowspan="1">Video<td rowspan="1">RGB/Compressed<td rowspan="1">30
  <tr>                                                     <td rowspan="2">2880x2160<td rowspan="1">Image<td rowspan="1">RBG/JPEG<td rowspan="1">30
  <tr>                                                                              <td rowspan="1">Video<td rowspan="1">RGB/Compressed<td rowspan="1">30
  </table>
  Note: Quality and frame rate provided during connection should match the resolution and framerate in PrepareCapture.
  <br>
  <br>

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/
enum {
  /*! Max No of streams supported by logical camera. */
  MLCAMERA_MAXSTREAMS = 2,
};

/*! Logical camera identifiers available for access. */
typedef enum MLCameraIdentifier {
  /*! x86 logical camera.*/
  MLCameraIdentifier_MAIN = 0,
  /*! CV logical camera. */
  MLCameraIdentifier_CV,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraIdentifier_Ensure32Bits = 0x7FFFFFFF
} MLCameraIdentifier;

/*!
  \brief Captures operation type.
*/
typedef enum MLCameraCaptureType {
  /*! To capture an image. */
  MLCameraCaptureType_Image = 0,
  /*! To capture a video. */
  MLCameraCaptureType_Video,
  /*! To capture a video and access the raw buffer of the frames. */
  MLCameraCaptureType_Preview,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraCaptureType_Ensure32Bits = 0x7FFFFFFF
} MLCameraCaptureType;

/*!
  \brief Captures frame rate.

   Call MLCameraPrepareCapture() to configure frame rate.
   Use MLCameraCaptureFrameRate_None when configuring only Image capture.
   Use MLCameraCaptureFrameRate_60fps only when resolution of captures <= 3MP(2048x1536).
   Use MLCameraCaptureFrameRate_15FPS only when MLCameraConnectFlag is MLCameraConnectFlag_CamOnly.
*/
typedef enum MLCameraCaptureFrameRate {
    /*! None, used for still capture. */
    MLCameraCaptureFrameRate_None = 0,
    /*! Specified 15FPS. */
    MLCameraCaptureFrameRate_15FPS,
    /*! Specified 30FPS. */
    MLCameraCaptureFrameRate_30FPS,
    /*! Specified 60FPS. */
    MLCameraCaptureFrameRate_60FPS,
    /*! Ensure enum is represented as 32 bits. */
    MLCameraCaptureFrameRate_Ensure32Bits = 0x7FFFFFFF
} MLCameraCaptureFrameRate;

/*!
  \brief Video Quality enumeration for mixed reality capture.

  Use #MLCameraGetStreamCaps to get the resolution.
*/
typedef enum MLCameraMRQuality {
  /*!
    \brief Specifies 648 x 720 resolution.
    Aspect ratio: 9x10.
  */
  MLCameraMRQuality_648x720 = 1,
  /*!
    \brief Specifies 972 x 1080 resolution.
    Aspect ratio: 9x10.
  */
  MLCameraMRQuality_972x1080 = 2,
  /*!
    \brief Specifies 1944 x 2160 resolution.
    Aspect ratio: 9x10.
    MLCameraCaptureFrameRate_60FPS is not supported for this quality mode.
  */
  MLCameraMRQuality_1944x2160 = 3,
  /*!
    \brief Specifies 960 x 720 resolution.
    Aspect ratio: 4x3.
  */
  MLCameraMRQuality_960x720 = 4,
  /*!
    \brief Specifies 1440 x 1080 resolution.
    Aspect ratio: 4x3.
  */
  MLCameraMRQuality_1440x1080 = 5,
  /*!
    \brief Specifies 2880 x 2160 resolution.
    Aspect ratio: 4x3.
    MLCameraCaptureFrameRate_60FPS is not supported for this quality mode.
  */
  MLCameraMRQuality_2880x2160 = 6,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMRQuality_Ensure32Bits = 0x7FFFFFFF
} MLCameraMRQuality;

/*! Flags to describe various modules in camera pipeline. */
typedef enum MLCameraConnectFlag {
  /*! Camera only frame capture. */
  MLCameraConnectFlag_CamOnly = 0x0,
  /*! Virtual only capture.  Only supported for MLCameraIdentifier_MAIN.*/
  MLCameraConnectFlag_VirtualOnly = 0x1,
  /*! Mixed Reality capture. Only supported for MLCameraIdentifier_MAIN. */
  MLCameraConnectFlag_MR = 0x2,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraConnectFlag_Ensure32Bits = 0x7FFFFFFF
} MLCameraConnectFlag;

/*! Virtual and real content blending modes. */
typedef enum MLCameraMRBlendType {
  /*! Additive blend type. It simply adds pixel values of real world and virtual
     layer.*/
  MLCameraMRBlendType_Additive = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraMRBlendType_Ensure32Bits = 0x7FFFFFFF
} MLCameraMRBlendType;

/*! Camera disconnect reason. */
typedef enum MLCameraDisconnectReason {
  /*! Device lost. */
  MLCameraDisconnect_DeviceLost = 0,
  /*! Priority lost. */
  MLCameraDisconnect_PriorityLost,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraDisconnect_Ensure32Bits = 0x7FFFFFFF
} MLCameraDisconnectReason;

/*! Camera errors. */
typedef enum MLCameraError {
  MLCameraError_None = 0,
  /*! Invalid/Unknown Error. */
  MLCameraError_Invalid,
  /*! Camera disabled. */
  MLCameraError_Disabled,
  /*! Camera device failed. */
  MLCameraError_DeviceFailed,
  /*! Camera service failed. */
  MLCameraError_ServiceFailed,
  /*! Capture failed. */
  MLCameraError_CaptureFailed,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraError_Ensure32Bits = 0x7FFFFFFF
} MLCameraError;

/*!
  \brief Captured output format.
  These three parameters determine which formats are supported:
    - Camera type:  [Main, CV].
    - Mode:         [Real, MR, Virtual].
    - Capture type: [Preview, Video, Image].

    These are formats supported:
  <table>
  <tr><th>Format    <th>Camera Type             <th>Mode                            <th>Capture Type
  <tr><td >YUV      <td>Main <br>CV             <td>Real <br>Real                   <td>Preview, Video, Image <br>Video, Image
  <tr><td>RGBA      <td>Main <br>Main <br>CR    <td>Real <br>MR, Virtual <br>Real   <td>Video <br>Video, Image <br>Video
  <tr><td>JPEG      <td>Main                    <td>Real, MR, Virtual               <td>Image
  </table>

*/
typedef enum MLCameraOutputFormat {
  MLCameraOutputFormat_Unknown,
  /*! YUV planar format. */
  MLCameraOutputFormat_YUV_420_888,
  /*! Compressed output stream. */
  MLCameraOutputFormat_JPEG,
  /*! RGB32 format. */
  MLCameraOutputFormat_RGBA_8888,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraOutputFormat_Ensure32Bits = 0x7FFFFFFF
} MLCameraOutputFormat;

/*! Client can implement polling mechanism to retrieve device status and use
 *  these masks to view device status. */
typedef enum MLCameraDeviceStatusFlag {
  /*! Connected. */
  MLCameraDeviceStatusFlag_Connected     = 1 << 0,
  /*! Idle. */
  MLCameraDeviceStatusFlag_Idle          = 1 << 1,
  /*! Opened. */
  MLCameraDeviceStatusFlag_Streaming     = 1 << 2,
  /*! Disconnected. */
  MLCameraDeviceStatusFlag_Disconnected  = 1 << 3,
  /*! Error. Call #MLCameraGetErrorCode to obtain the error code. */
  MLCameraDeviceStatusFlag_Error         = 1 << 4,
  /*! Ensure enum is represented as 32 bits. */
  MLCameraDeviceStatusFlag_Ensure32Bits = 0x7FFFFFFF
} MLCameraDeviceStatusFlag;

/*! Camera context to be used while connecting to camera. */
typedef MLHandle MLCameraContext;

/*! A structure to encapsulate connection settings for MR capture. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraMRConnectInfo {
  /*! Video quality. */
  MLCameraMRQuality quality;
  /*! Blending type for mixed reality capture. */
  MLCameraMRBlendType blend_type;
  /*! Capture frame rate. */
  MLCameraCaptureFrameRate frame_rate;
} MLCameraMRConnectInfo;

/*! A structure to encapsulate context for a CameraConnect Request. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraConnectContext {
  /*! Version contains the version number for this structure. */
  uint32_t version;
  /*! Logical camera identifier. */
  MLCameraIdentifier cam_id;
  /*! Context in which the camera should operate in. */
  MLCameraConnectFlag flags;
  /*! Enable/disable video stabilization.*/
  bool enable_video_stab;
  /*!
   \brief MR capture connection settings.

   This field can be ignored if MLCameraConnectFlag_MR or MLCameraConnectFlag_VirtualOnly flag is not used.
  */
  MLCameraMRConnectInfo mr_info;
} MLCameraConnectContext;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A structure to encapsulate stream capabilities.

  The capabilities for each stream supported by logical camera device
  can be queried with MLCameraGetStreamCaps.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraCaptureStreamCaps {
  /*! Capture type: video, image, or preview. */
  MLCameraCaptureType capture_type;
  /*! Resolution width. */
  int32_t width;
  /*! Resolution height. */
  int32_t height;
} MLCameraCaptureStreamCaps;

/*! A structure to encapsulate stream configurations. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraCaptureStreamConfig {
  /*! Capture type. */
  MLCameraCaptureType capture_type;
  /*! Specifies resolution width. */
  int32_t width;
  /*! Specifies resolution height. */
  int32_t height;
  /*! Specifies output format. */
  MLCameraOutputFormat output_format;
  /*!
   \brief Native surface.

   Used for compressed video recording.
   Handle returned by MLMediaRecorderGetInputSurface should be provided.
   Maximum video recording resolution supported is 4K(3840x2160).
   Only valid for capture type #MLCameraCaptureType_Video.
   Set to ML_INVALID_HANDLE for yuv/rgba video capture.
  */
  MLHandle native_surface_handle;
} MLCameraCaptureStreamConfig;

/*! A structure to encapsulate capture configuration. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraCaptureConfig {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Capture frame rate:
    <br>If only IMAGE stream configuration set to MLCameraCaptureFrameRate_None.
    <br>If setting to 60fps capture resolution should not be more than 1920x1080
    for any of the streams.
    <br>For MR/virtual only capture, the frame rate should match the value
    selected in #MLCameraMRConnectInfo.
  */
  MLCameraCaptureFrameRate capture_frame_rate;
  /*! Number of captured streams. */
  uint32_t num_streams;
  /*! Stream configurations. */
  MLCameraCaptureStreamConfig stream_config[MLCAMERA_MAXSTREAMS];
} MLCameraCaptureConfig;

/*! Per plane info for captured output. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraPlaneInfo {
  /*! Version of this structure. */
  uint32_t version;
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
  /*! Image data. */
  uint8_t  *data;
  /*! Number of bytes in the image output data. */
  uint32_t size;
} MLCameraPlaneInfo;

enum {
  /*! Number of planes representing the image color space. */
  MLCamera_MaxImagePlanes = 3
};

/*! A structure to encapsulate captured output. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraOutput {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Number of output image planes:
    <br>1 for compressed output such as JPEG stream,
    <br>3 for separate color component output such as YUV/RGB.
  */
  uint8_t plane_count;
  /*! Output image plane info. The number of output planes is specified by plane_count. */
  MLCameraPlaneInfo planes[MLCamera_MaxImagePlanes];
  /*! Supported output format specified by MLCameraOutputFormat. */
  MLCameraOutputFormat format;
} MLCameraOutput;

/*!
  \brief Camera distortion vector size.

  \apilevel 20
*/
enum {
  /*! Default distortion vector size. */
  MLCameraIntrinsics_MaxDistortionCoefficients = 5
};

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Camera intrinsic parameter.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraIntrinsicCalibrationParameters {
  /*! Version of this structure. */
  uint32_t version;
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
  /*! \brief Distortion vector.
      The distortion co-efficients are in the following order:
      <br>[k1, k2, p1, p2, k3].
   */
  double distortion[MLCameraIntrinsics_MaxDistortionCoefficients];
} MLCameraIntrinsicCalibrationParameters;

/*! A structure to encapsulate various indices for a capture result. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraResultExtras {
  /*! Version of this structure. */
  uint32_t version;
  /*! A 64bit integer to index the frame number associated with this result. */
  int64_t frame_number;
  /*! Frame timestamp. */
  MLTime vcam_timestamp;
  /*! Camera intrinsic parameter. */
  /*! Only valid within callback scope. */
  /*! The Library allocates and maintains the lifetime of intrinsics. */
  /*! Only valid for on_image_buffer_available, on_video_buffer_available, on_preview_buffer_available callbacks. */
  /*! NULL for on_capture_completed, on_capture_failed callbacks. */
  MLCameraIntrinsicCalibrationParameters *intrinsics;
} MLCameraResultExtras;

/*! A structure to represent info on camera availability. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraDeviceAvailabilityInfo {
  /*! Identifier for the camera that the callback applies. */
  MLCameraIdentifier cam_id;
  /*! The context pointer supplied to MLCameraInit() call. */
  void *user_data;
} MLCameraDeviceAvailabilityInfo;

/*! Device availability status callbacks to be implemented by client to receive device availability status. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraDeviceAvailabilityStatusCallbacks {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Callback is invoked when the camera becomes available.

    \param[in] info Information about the camera availability.
  */
  void (*on_device_available)(const MLCameraDeviceAvailabilityInfo *info);
  /*!
    \brief Callback is invoked when the camera becomes unavailable.

    \param[in] info Information about the camera availability
    */
  void (*on_device_unavailable)(const MLCameraDeviceAvailabilityInfo *info);
} MLCameraDeviceAvailabilityStatusCallbacks;

/*! Device status callbacks to be implemented by client to receive device status if callback mechanism is used. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraDeviceStatusCallbacks {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Callback is invoked when the camera is streaming.

    \param[in] data Custom data to be returned when callback is triggered. This data
               passed in #MLCameraSetDeviceStatusCallbacks.
  */
  void (*on_device_streaming)(void *data);
  /*!
    \brief Callback is invoked when the camera stops streaming.

    \param[in] data Custom data to be returned when callback is triggered. This data
               passed in #MLCameraSetDeviceStatusCallbacks.
  */
  void (*on_device_idle)(void *data);
  /*!
    \brief Callback is invoked when the camera is disconnected.

    \param[in] reason Represents the reason for disconnection.
    \param[in] data Custom data to be returned when callback is triggered. This data
               passed in #MLCameraSetDeviceStatusCallbacks.
  */
  void (*on_device_disconnected)(MLCameraDisconnectReason reason, void *data);
  /*!
    \brief Callback is invoked when the camera encountered errors.

    <br><br>Invalid: The camera device is not available.

    <br>Disabled: The camera device can't be opened due to a device policy.

    <br>Device error: The camera device encountered a fatal error such as the
    Headset device has lost connection or the hardware comm bus is busy and
    not be able to response and caused a timeout.

    <br>Service error: The camera service has encountered a fatal error and
    could not provide service.

    <br>Capture failed: The capture request has failed. on_capture_failed or
    on_capture_buffer_lost callbacks will be invoked when this error happens.

    \param[in] error Represents the error type when happened.
    \param[in] data Custom data to be returned when callback is triggered. This data
                    passed in #MLCameraSetDeviceStatusCallbacks.
  */
  void (*on_device_error)(MLCameraError error, void *data);
} MLCameraDeviceStatusCallbacks;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Capture callbacks to be implemented by client to receive capture status if callback mechanism is used.

  This structure must be initialized by calling MLCameraCaptureCallbacksInit() before use.

*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLCameraCaptureCallbacks {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Callback is invoked when a capture has failed when the camera device
           failed to produce a capture result for the request.

    \param[in] extra Carries capture result information of current captured frame.
    \param[in] data Custom data to be returned when callback is triggered. This data
               passed in #MLCameraSetCaptureCallbacks.
  */
  void (*on_capture_failed)(const MLCameraResultExtras *extra, void *data);
  /*!
    \brief Callback is invoked when an ongoing video or preview capture or both are aborted
           due to an error. This is not valid for MR Capture.

    \param[in] data Custom data to be returned when callback is triggered. This data
               passed in #MLCameraSetCaptureCallbacks.
  */
  void (*on_capture_aborted)(void *data);
  /*!
    \brief Callback is invoked when capturing single frame is completed and result is available.
    For MRCapture null metadata handle.

    \param[in] result_metadata_handle Represents camera result metadata which could be used as
                input handle for camera result metadata related functions.
    \param[in] extra Carries capture result information of current captured frame.
    \param[in] data Custom data to be returned when callback is triggered. This data
                passed in #MLCameraSetCaptureCallbacks.
  */
  void (*on_capture_completed)(MLHandle result_metadata_handle, const MLCameraResultExtras *extra, void *data);
  /*!
    \brief Callback is invoked when a captured image buffer is available with #MLCameraCaptureType_Image.

    \param[in] output Provides image properties and buffer pointer to image data.
    \param[in] result_metadata_handle Handle to metadata of captured frame.
    \param[in] extra Carries capture result information of current captured frame.
    \param[in] data Custom data to be returned when callback is triggered. This data
                passed in #MLCameraSetCaptureCallbacks.
  */
  void (*on_image_buffer_available)(const MLCameraOutput *output, const MLHandle result_metadata_handle, const MLCameraResultExtras *extra, void *data);
  /*!
    \brief Callback is invoked when a captured video frame buffer is available with #MLCameraCaptureType_Video.

    \param[in] output Provides video frame properties and buffer pointer to video frame data.
    \param[in] result_metadata_handle Handle to metadata of captured frame.
    \param[in] extra Carries capture result information of current captured frame.
    \param[in] data Custom data to be returned when callback is triggered. This data
                passed in #MLCameraSetCaptureCallbacks.
  */
  void (*on_video_buffer_available)(const MLCameraOutput *output, const MLHandle result_metadata_handle, const MLCameraResultExtras *extra, void *data);
  /*!
    \brief Callback is invoked when a preview video frame buffer is available with #MLCameraCaptureType_Preview.

     This callback is not valid for MR Capture since it does not have preview support.

    \param[in] buffer_handle Handle of preview buffer allocated for preview.
    \param[in] result_metadata_handle Handle to metadata of captured frame.
    \param[in] extra Carries capture result information of current captured frame.
    \param[in] data Custom data to be returned when callback is triggered. This data
               passed in #MLCameraSetCaptureCallbacks.
  */
  void (*on_preview_buffer_available)(const MLHandle buffer_handle, const MLHandle result_metadata_handle, const MLCameraResultExtras *extra, void *data);
} MLCameraCaptureCallbacks;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initialize the connect context structure.

  Shall be called before calling MLCameraConnect().

  \apilevel 20

  \param[in,out] inout_context MLCameraConnectContext structure to initialize.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_STATIC_INLINE void MLCameraConnectContextInit(MLCameraConnectContext *inout_context) {

  if (inout_context) {
    memset(inout_context, 0, sizeof(MLCameraConnectContext));
    inout_context->version = 1;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initialize the capture config structure.

  Shall be called before calling MLCameraPrepareCapture().

  \apilevel 20

  \param[in,out] inout_config MLCameraCaptureConfig structure to initialize.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_STATIC_INLINE void MLCameraCaptureConfigInit(MLCameraCaptureConfig *inout_config) {

  if (inout_config) {
    memset(inout_config, 0, sizeof(MLCameraCaptureConfig));
    inout_config->version = 1;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initialize the callback structure.

  Shall be called before calling MLCameraSetDeviceAvailabilityStatusCallbacks().

  \apilevel 20

  \param[in,out] inout_device_availability_status_callbacks Device availability
  status callbacks structure to initialize.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_STATIC_INLINE void MLCameraDeviceAvailabilityStatusCallbacksInit(
    MLCameraDeviceAvailabilityStatusCallbacks
        *inout_device_availability_status_callbacks) {
  if (inout_device_availability_status_callbacks) {
    inout_device_availability_status_callbacks->version = 1;
    inout_device_availability_status_callbacks->on_device_available = NULL;
    inout_device_availability_status_callbacks->on_device_unavailable = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initialize the callback structure.

  Shall be called before calling MLCameraSetDeviceStatusCallbacks().

  \apilevel 20

  \param[in,out] inout_device_status_callbacks Device status callbacks structure
  to initialize.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_STATIC_INLINE void MLCameraDeviceStatusCallbacksInit(
    MLCameraDeviceStatusCallbacks *inout_device_status_callbacks) {
  if (inout_device_status_callbacks) {
    inout_device_status_callbacks->version = 1;
    inout_device_status_callbacks->on_device_streaming = NULL;
    inout_device_status_callbacks->on_device_idle = NULL;
    inout_device_status_callbacks->on_device_error = NULL;
    inout_device_status_callbacks->on_device_disconnected = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initialize the callback structure.

  Shall be called before calling MLCameraSetCaptureCallbacks().

  \apilevel 20

  \param[in,out] inout_capture_callbacks Capture status callbacks structure to initialize.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_STATIC_INLINE void MLCameraCaptureCallbacksInit(MLCameraCaptureCallbacks *inout_capture_callbacks) {
  if (inout_capture_callbacks) {
    inout_capture_callbacks->version = 1;
    inout_capture_callbacks->on_capture_failed = NULL;
    inout_capture_callbacks->on_capture_aborted = NULL;
    inout_capture_callbacks->on_capture_completed = NULL;
    inout_capture_callbacks->on_image_buffer_available = NULL;
    inout_capture_callbacks->on_video_buffer_available = NULL;
    inout_capture_callbacks->on_preview_buffer_available = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initialize ML Camera API, Register callback for device availability.
         If the user does not want to register device availability listener,
         MLCameraConnect can be called directly without MLCameraInit().
         MLCameraDeInit should be used for unregistering callbacks and
         releasing resources acquired in MLCameraInit().

  \apilevel 20

  \param[in] device_availability_status_callbacks Callback to notify camera availability status.
  \param[in] user_data Pointer to user context data (can be NULL).

  \retval MLResult_Ok Camera is initialized and callbacks registered successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLResult_PermissionDenied Necessary permission is missing.

  \permissions android.permission.CAMERA (protection level: dangerous)
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraInit(const MLCameraDeviceAvailabilityStatusCallbacks *device_availability_status_callbacks, void *user_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Connect to camera device.

  \apilevel 20

  \param[in] input_context MLCameraConnectContext structure.
  \param[out] out_context Camera context to be used in later APIs.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLResult_Ok Connected to camera device successfully.
  \retval MLMediaGenericResult_InvalidOperation camera device already connected.
  \retval MLResult_PermissionDenied Necessary permission is missing.

  \permissions android.permission.CAMERA (protection level: dangerous)
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraConnect(const MLCameraConnectContext *input_context, MLCameraContext *out_context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Query the no of streams supported by camera device.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[out] out_num_supported_streams Number of streams supported by device.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok API call completed successfully.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraGetNumSupportedStreams(MLCameraContext context, uint32_t *out_num_supported_streams);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Query the stream capabilities.

  Retrieves either the number of capabilities supported by the given stream or
  an array of capabilities for the given stream.
  To get the number of capabilities supported by the given stream, this API should be
  called with num_stream_caps being valid pointer and out_stream_caps being NULL.
  To retrieve the array of capabilities for the given stream, this API should be called
  with a valid num_stream_caps (that contains the size of the out_stream_caps) and
  out_stream_caps being a preallocated array of MLCameraCaptureStreamCaps of size
  specified by num_stream_caps.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[in] stream_index Index of the stream for which to query capabilities. The index should
              be in the range [0 , num_supported_streams) where the num_supported_streams is from MLCameraGetNumSupportedStreams().
  \param[in,out] inout_num_stream_caps When the parameter inout_stream_caps is null, this is an output
                  parameter which will hold the number of capabilities supported by the stream on function return.
                  Otherwise this is an input parameter specifying the number of capabilities to retrieve, namely 
                  the size of the array pointed to by inout_stream_caps on return. The value should be in the range of [0, number-of-caps-retrieved].
  \param[in,out] inout_stream_caps This is either null or pointing to an array of MLCameraCaptureStreamCaps() on return. 
                  Note that caller is responsible for allocating and releasing the array.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok API call completed successfully.

   \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraGetStreamCaps(MLCameraContext context, const uint32_t stream_index,
    uint32_t* inout_num_stream_caps, MLCameraCaptureStreamCaps *inout_stream_caps);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Disconnect from camera device.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_Ok Disconnected Camera device successfully.
  \retval MLMediaGenericResult_InvalidOperation Camera device already disconnected or camera device is streaming.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraDisconnect(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Uninitialize ML Camera API, unregister callback for device availability.
         Should be called after all camera devices are disconnected.
         After MLCameraDeInit, MLCameraInit can be called or MLCameraConnect can be called.

  \apilevel 20

  \retval MLResult_Ok Deinitialization completed successfully.
  \retval MLMediaGenericResult_InvalidOperation DeInit called when camera device is connected.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraDeInit();

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Trigger AEAWB Convergence.

  This API triggers AEAWB sequence and returns when AEAWB convergence has been
  achieved. The Users can either trigger and converge AEAWB metadata settings
  or use this API.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_InvalidParam Invalid camera context.
  \retval MLResult_Ok AEAWB convergence done.
  \retval MLResult_UnspecifiedFailure Unspecified failure.
  \retval MLResult_Timeout Timed out waiting for AEAWB convergence.
  \retval MLMediaGenericResult_InvalidOperation Camera device not configured using MLCameraPrepareCapture() or camera device is streaming.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraPreCaptureAEAWB(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Prepare for capture.

  This API prepares for capture per specified #MLCameraCaptureType by creating
  a capture request, and a handle to which is returned to the user, who can
  choose to manipulate the request data (metadata) via APIs defined in
  ml_camera_metadata_v2.h before performing the capture.

  Shall be called after MLCameraConnect().

  Note: When preparing capture the width and height parameters should match
        one of the values returned from #MLCameraGetStreamCaps.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[in] config Capture configuration.
  \param[out] out_request_handle Handle to the capture request metadata. Only valid if result is MLResult_Ok.

  \retval MLResult_InvalidParam Failed to prepare for capture due to invalid input parameter.
  \retval MLResult_Ok Prepared for capture successfully.
  \retval MLResult_UnspecifiedFailure Failed to prepare for capture due to internal error.
  \retval MLMediaGenericResult_InvalidOperation Camera device in streaming state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraPrepareCapture(MLCameraContext context, const MLCameraCaptureConfig *config, MLHandle *out_request_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Update capture setting.

  This API updates the capture settings for an active preview/video stream.
  The API can be used to update capture settings like exposure compensation
  manual exposure settings like exposure time, iso setting.The capture settings
  can be changed in metadata handle returned by MLCameraPrepareCapture() and then this API
  can be called to apply the capture settings.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_InvalidParam Invalid context.
  \retval MLMediaGenericResult_InvalidOperation Camera not streaming video or not in preview.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraUpdateCaptureSettings(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the client-implemented callbacks to convey camera device status.

  Client needs to implement the callbacks defined by #MLCameraDeviceStatusCallbacks.
  The library passes the camera device status to the client via those callbacks.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[in] device_status_callbacks Camera device status callbacks.
  \param[in] data User metadata.

  \retval MLResult_InvalidParam Invalid context.
  \retval MLResult_Ok Set device status callbacks successfully.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraSetDeviceStatusCallbacks(MLCameraContext context, const MLCameraDeviceStatusCallbacks *device_status_callbacks, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the client-implemented callbacks to convey capture status.

  Client needs to implement the callbacks defined by #MLCameraCaptureCallbacks.
  The library passes the capture status to the client via those callbacks.

  Shall be called before capture operation for preview/image/video.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[in] capture_callbacks Capture status callbacks.
  \param[in] data User metadata.

  \retval MLResult_InvalidParam Invalid context.
  \retval MLResult_Ok Set Capture callbacks successfully.
  \retval MLResult_UnspecifiedFailure Internal error occurred.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraSetCaptureCallbacks(MLCameraContext context, const MLCameraCaptureCallbacks *capture_callbacks, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Capture still image.

  The output image will be returned in capture callback on_image_buffer_available.

  This is a blocking call, it will return after the end of on_image_buffer_available callback execution.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[in] num_images Number of images to capture valid range is 1-10.

  \retval MLResult_InvalidParam Invalid context or invalid num_images.
  \retval MLResult_Ok Triggered image capture successfully.
  \retval MLMediaGenericResult_InvalidOperation MLMediaGenericResult_InvalidOperation Capture device in invalid state or image stream not configured by MLCameraPrepareCapture().
  \retval MLResult_UnspecifiedFailure Internal error occurred.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraCaptureImage(MLCameraContext context, uint32_t num_images);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Start video capture. Capture either encoded video or YUV/RGBA frames.

  YUV/RGBA frames are provides through callback.For encoded video capture
  valid encoder input surface should be configured.The captured video YUV/RGBA
  frames will be returned to the application via on_video_buffer_available.

  #MLCameraCaptureVideoStop needs to be called to stop the capture.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_InvalidParam Invalid context input parameter.
  \retval MLResult_Ok Started video capture successfully.
  \retval MLMediaGenericResult_InvalidOperation Capture device in invalid state or video stream not configured by MLCameraPrepareCapture().
  \retval MLResult_UnspecifiedFailure Failed to start video recording due to internal error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraCaptureVideoStart(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Start preview provide raw frames through callback.

  The captured preview YUV frames will be returned to the application via on_preview_buffer_available.

  #MLCameraCapturePreviewStop needs to be called to stop the capture.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_InvalidParam Invalid context.
  \retval MLResult_Ok Started preview successfully.
  \retval MLResult_UnspecifiedFailure Failed to start preview due to internal error.
  \retval MLMediaGenericResult_InvalidOperation Capture device in invalid state or preview stream not configured by MLCameraPrepareCapture().

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraCapturePreviewStart(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Stop video capture.

  User should allow some time, i.e., >500ms, after MLCameraCaptureVideoStart
  and before calling this API, as captured frames are being encoded. Otherwise,
  MLResult_UnspecifiedFailure will be returned.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_InvalidParam Invalid context.
  \retval MLResult_Ok Stopped video capture successfully.
  \retval MLResult_UnspecifiedFailure Failed to stop video recording due to internal error.
  \retval MLMediaGenericResult_InvalidOperation Capture device in invalid state or video stream not streaming.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraCaptureVideoStop(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Stop preview.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().

  \retval MLResult_InvalidParam Invalid context.
  \retval MLResult_Ok Stopped video capture successfully.
  \retval MLResult_UnspecifiedFailure Failed to stop preview due to internal error.
  \retval MLMediaGenericResult_InvalidOperation Capture device in invalid state or preview stream not streaming.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraCapturePreviewStop(MLCameraContext context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Poll camera device status.

  Use #MLCameraDeviceStatusFlag to view specific status bit.
  Call MLCameraGetErrorCode() to obtain the error code if #MLCameraDeviceStatusFlag_Error bit is set.

  Note: This API can still be used even if MLCameraSetDeviceStatusCallbacks() has been called.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[out] out_device_status Device status.

  \retval MLResult_InvalidParam Failed to obtain device status due to invalid input parameter.
  \retval MLResult_Ok Obtained device status successfully.

  \permissions None
 */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraGetDeviceStatus(MLCameraContext context, uint32_t *out_device_status);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Poll camera device availability status.

  Use #MLCameraGetDeviceAvailabilityStatus to view specific status.

  Note: This API can still be used even if availability status callback is not registered through #MLCameraInit call.

  \apilevel 20

  \param[in] cam_id Camera Id for which the availability status is to be queried.
  \param[out] out_device_availability_status Device availability status.

  \retval MLResult_InvalidParam Failed to obtain device status due to invalid input parameter.
  \retval MLResult_Ok Obtained device status successfully.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraGetDeviceAvailabilityStatus(MLCameraIdentifier cam_id, bool *out_device_availability_status);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain camera device error code.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[out] out_error_code Camera device error code.

  \retval MLResult_InvalidParam Failed to obtain device error code due to invalid input parameter.
  \retval MLResult_Ok Obtained camera device error code successfully.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraGetErrorCode(MLCameraContext context, MLCameraError *out_error_code);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtains handle for retrieving camera characteristics.

  This API provides the handle for retrieving camera characteristics via APIs defined in ml_camera_metadata_v2.h.

  \apilevel 20

  \param[in] context Camera context obtained from MLCameraConnect().
  \param[out] out_characteristics_handle Handle to access camera characteristic metadata. Only valid if result is MLResult_Ok.

  \retval MLResult_InvalidParam Failed to obtain camera characteristic handle due to invalid input parameter.
  \retval MLResult_Ok Obtained camera characteristic handle successfully.
  \retval MLResult_UnspecifiedFailure Failed due to internal error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLCameraGetCameraCharacteristics(MLCameraContext context, MLHandle *out_characteristics_handle);

/*! \} */

 ML_EXTERN_C_END
