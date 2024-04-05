// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Software License Agreement,
// located here: https://www.magicleap.com/software-license-agreement-ml2
// Terms and conditions applicable to third-party materials accompanying
// this distribution may also be found in the top-level NOTICE file
// appearing herein.
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

#pragma once

/*!
  \brief Definition of metadata tags for MagicLeap specific extensions to Camera Metadata.
         The metadata tags can be used with NDK apis to get and set camera metadata.
         The NDK apis lack the functionality to query metadata tag from name, which makes it difficult to work with vendor tags without having these definitions.

         Three Camera Devices are supported: Camera Id 0, Camera Id 1, Camera Id 3. Camera Id 0 and 1 support Camera_Only capture.
         Camera Id 3 supports Mixed_Reality capture, Virtual_Only capture, Camera_Only capture.
         Camera Id 0 and Camera Id 1 support a total of 3 streams. Streams are dynamically allocated between Camera Id 0 and Camera Id 1.
         Camera Id 0 and Camera Id 3 are conflicting devices, a higher priority application using Camera Id 3 will evict client using Camera Id 0.
         Camera Id 3(Mixed Reality Camera) only supports 1 stream.
         All the cameras are back cameras (LENS_FACING_BACK) and there are no front cameras.
         On ML2 Camera has landscape orientation and Display has portrait orientation, the applications should not try to match preview aspect
         ratio and display aspect ratio.
         When using Manual exposure mode, applications can expect a delay of 3-4 frames between application issuing a request and receiving the
         result with manual exposure parameters applied for the request because of latencies in configuring sensor on wearable.
         On ML2 a custom scene mode (Medical - 100) is implemented for the Operation theater environment (high intensity lights).
         The application can set the scene mode using standard tag (CONTROL_SCENE_MODE).
*/

/*! Tags for camera id 0 and camera id 1 */

/*!
  \brief ML_CONTROL_CAMERA_FORCEAPPLY_MODE can be used to force apply camera settings.
         Camera Id 0 and Camera Id 1 share the same camera hardware resources. It is recommended that applications try to use as much as possible
         the default template metadata otherwise metadata properties from one camera can affect the other.
         When both cameras are streaming, request metadata settings for both cameras are merged and then applied. While merging, the metadata
         settings from Camera Id 0 take precedence over Camera Id 1. The Force Apply mode setting can be used to override this.
         If Camera Id 1 Request metadata has force apply mode on, the Camera Id 1 metadata settings take precedence over Camera Id 0 properties.
         The tag is available in both Capture Request and Capture Result metadata.
         The tag has data type uint8 and can be set to 1 to force apply the camera settings.
         The name for this tag is "com.amd.control.forceapply" which can be used with android java camera API.
*/
#define ML_CONTROL_CAMERA_FORCEAPPLY_MODE 0x80000000

/*!
  \brief ML_CONTROL_CAMERA_EFFECT_MODE can be used to configure special effects.
         The tag is available in both Capture Request and Capture Result metadata.
         The tag has data type uint8 and can be set to the following values for configuring effect modes:
         0 - Off, 1 - Grayscale, 2 - Negative, 3 - Sepia, 4 - Color Selection, 5 - Sharpen, 6 - Emboss, 7 - Sketch.
         The name for this tag is "com.amd.control.effectmode" which can be used with android java camera API.
*/
#define ML_CONTROL_CAMERA_EFFECT_MODE 0x80000002

/*!
  \brief ML_CONTROL_CAMERA_APP_EXPOSURE_UPPER_TIME_LIMIT can be used to limit the max exposure time selected by auto exposure algorithm.
         The tag can be used to limit exposure time in a high motion environment to reduce motion blur.
         The auto exposure algorithm uses max time of 16ms/20ms in 60Hz/50Hz env, any value less than 16ms/20ms can be used.
         The tag is available in both Capture Request and Capture Result metadata.
         The tag has data type int64 and can be used to set max exposure time in nanoseconds.
         The name for this tag is "com.amd.control.app_exposure_time_upper_limit" which can be used with android java camera API.
*/
#define ML_CONTROL_CAMERA_APP_EXPOSURE_UPPER_TIME_LIMIT 0x80000004

/*!
  \brief ML_CONTROL_CAMERA_MLTIME_TIMESTAMPS can be used to query MLTime timestamps.
         The tag can be used to query MLTime timestamps and can be used for synchronizing with other data like head pose which has MLTime timestamps.
         The tag is available in Capture Result metadata.
         The tag has data type int64 and returns an array of 4 timestamps [StartOfFrameTransfer, CentreOfExposure, EndOfFrameTransfer, ExternalCameraSync].
         StartOfFrameTransfer, EndOfFrameTransfer, ExternalCameraSync are not useful for applications.
         The CentreOfExposure timestamp can be used for synchronizing with other data that has MLTime timestamps.
         MLTimeConvertMLTimeToSystemTime API can be used to convert MLTime to System Time.
         The name for this tag is "com.amd.control.cvip_timestamps" which can be used with android java camera API.
*/
#define ML_CONTROL_CAMERA_MLTIME_TIMESTAMPS 0x8000000B

/*!
  \brief ML_CONTROL_CAMERA_NUM_INTRINSICS can be used to query no. of camera intrinsics in Capture Result Metadata.
         The tag can be used to query no. of intrinsics which is the no. of streams configured for camera.
         The tag is available in Capture Result metadata.
         The tag has data type int32.
         The name for this tag is "com.amd.control.num_intrinsics" which can be used with android java camera API.
*/
#define ML_CONTROL_CAMERA_NUM_INTRINSICS 0x8000001B

/*!
  \brief ML_CONTROL_CAMERA_INTRINSICS can be used to query the camera intrinsics in Capture Result Metadata.
         The tag can be used to query intrinsics for camera.
         The tag is available in Capture Result metadata.
         The tag has data type float and returns an array of floats which can be interpreted as:
         num_intrinsics * {width, height, focal_length_x, focal_length_y, principal_point_x, principal_point_y, field_of_view, k1, k2, p1, p2, k3}.
         The name for this tag is "com.amd.control.intrinsics" which can be used with android java camera API.
*/
#define ML_CONTROL_CAMERA_INTRINSICS 0x8000001C


/*! Tags for camera id 3 (Mixed Reality Capture)*/
/*!
  \brief ML_CONTROL_MRCAMERA_TINT can be used to control tint for virtual and camera frames composition.
         The tag is available in Capture Request and Capture Result metadata.
         The tag has data type float and can be set between 0.0 to 1.0 to control the tint of mixed reality content.
         The name for this tag is "com.ml.control.tint" which can be used with android java camera API.
*/
#define ML_CONTROL_MRCAMERA_TINT 0x80000103

/*!
  \brief ML_CONTROL_MRCAMERA_ALPHA_BIAS can be used to control alpha for virtual and camera frames composition.
         The tag is available in Capture Request and Capture Result metadata.
         The tag has data type float and can be set between -1.0 to 1.0 to control the opacity/transparency of virtual content.
         The name for this tag is "com.ml.control.alpha_bias" which can be used with android java camera API.
*/
#define ML_CONTROL_MRCAMERA_ALPHA_BIAS 0x80000104

/*!
  \brief ML_CONTROL_MRCAMERA_CAPTURE_MODE can be used to set the capture mode for mixed reality capture.
         The tag is available in Capture Request and Capture Result metadata.
         The tag has data type uint8_t and can be set to 0 for Mixed_Reality capture, 1 for Virtual_Only capture, 2 for Camera_Only capture.
         The name for this tag is "com.ml.control.capture_mode" which can be used with android java camera API.
*/
#define ML_CONTROL_MRCAMERA_CAPTURE_MODE 0x80000105

/*!
  \brief ML_CONTROL_MRCAMERA_MLTIME_TIMESTAMPS can be used to query MLTime timestamps.
         The tag can be used to query MLTime timestamps and can be used for synchronizing with other data like head pose which has MLTime timestamps.
         The tag is available in Capture Result metadata.
         The tag has data type int64 and returns an array of 4 timestamps [StartOfFrameTransfer, CentreOfExposure, EndOfFrameTransfer, ExternalCameraSync].
         StartOfFrameTransfer, EndOfFrameTransfer, ExternalCameraSync are not useful for applications.
         The CentreOfExposure timestamp can be used for synchronizing with other data that has MLTime timestamps.
         MLTimeConvertMLTimeToSystemTime API can be used to convert MLTime to System Time.
         The name for this tag is "com.ml.control.cvip_timestamps" which can be used with android java camera API.
*/
#define ML_CONTROL_MRCAMERA_MLTIME_TIMESTAMPS 0x80000106

/*!
  \brief ML_CONTROL_MRCAMERA_NUM_INTRINSICS can be used to query no. of camera intrinsics in Capture Result Metadata.
         The tag can be used to query no. of intrinsics which is the no. of streams configured for camera.
         The tag is available in Capture Result metadata.
         The tag has data type int32.
         The name for this tag is "com.ml.control.num_intrinsics" which can be used with android java camera API.
*/
#define ML_CONTROL_MRCAMERA_NUM_INTRINSICS 0x80000112

/*!
  \brief ML_CONTROL_MRCAMERA_INTRINSICS can be used to query the camera intrinsics in Capture Result Metadata.
         The tag can be used to query intrinsics for camera.
         The tag is available in Capture Result metadata.
         The tag has data type float and returns an array of floats which can be interpreted as:
         num_intrinsics * {width, height, focal_length_x, focal_length_y, principal_point_x, principal_point_y, field_of_view, k1, k2, p1, p2, k3}.
         The name for this tag is "com.ml.control.intrinsics" which can be used with android java camera API.
*/
#define ML_CONTROL_MRCAMERA_INTRINSICS 0x80000113
