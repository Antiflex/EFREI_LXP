// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2021 Magic Leap, Inc. All Rights Reserved.
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
#include "ml_coordinate_frame_uid.h"

#include <string.h>

ML_EXTERN_C_BEGIN

/*!
  \defgroup MarkerTracking Fiducial Marker Tracking
  \addtogroup MarkerTracking
  \sharedobject perception.magicleap
  \brief APIs for the Marker Tracking system.

  This API can be used to track fiducial markers like QR
  codes, April tags and Aruco markers. For fiducial markers,
  this API provides 6DOF poses, and the encoded information.

  The scanner supports up to 16 markers.
  Identical QR codes will be treated as separate targets and
  reported individually, identical Aruco markers or April tags
  will lead to a collision and won't be reported separately.

  List of supported, trackable markers (with pose info):
  - Aruco markers.
  - AprilTag v2.
  - QR codes (model 1 & 2).

  List of supported, detectable markers (no pose info):
  - EAN-13 (experimental).
  - UPC-A (experimental).
  - Code 128 (experimental).

  Starting at API level 28 all ArUco marker, QR code and
  April tag poses reported from this API are consistently
  following the convention below.

  Marker axes convention:
   The marker has its own coordinate system (which in the case
   of a marker coplanar with the image plane and facing the camera
   means a 180° rotation around the vertical axis).

   In RUB coordinates, this means that we will have:
  \code
          y ^
          __|___
         |  |  |
    x <--|--+  |
         |_____|
  \endcode
   Z-axis pointing backwards away from the camera.

  \{
*/

/*!
  \brief Represents the different detector types supported by the API.

  \apilevel 20
*/
typedef enum MLMarkerTrackerDetectorType {
  /*! Represents no marker type. */
  MLMarkerTrackerDetectorType_None = 0,
  /*! QR code. */
  MLMarkerTrackerDetectorType_QR = 1 << 0,
  /*! Aruco and AprilTag. */
  MLMarkerTrackerDetectorType_Aruco = 1 << 1,
  /*! EAN-13 (experimental). */
  MLMarkerTrackerDetectorType_EAN_13 = 1 << 2,
  /*! UPC-A (experimental). */
  MLMarkerTrackerDetectorType_UPC_A = 1 << 3,
  /*! Code 128 decoded data (experimental). */
  MLMarkerTrackerDetectorType_Code_128 = 1 << 4,
  /*! All supported marker types. */
  MLMarkerTrackerDetectorType_All = 0x3FFFFFFF,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackerDetectorType_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackerDetectorType;

/*!
  \brief Represents the different tracker profiles.

  \apilevel 21
*/
typedef enum MLMarkerTrackerProfile {
  /*!
    \brief Generic tracker profile.
    Tracker profile that covers standard use cases. If this does not suite the
    needs of the application try the other profiles listed below.
  */
  MLMarkerTrackerProfile_Default = 0,
  /*!
    \brief Customer Tracker Profile.

    Application can define a custom traker profiler. See #MLMarkerTrackerCustomProfile
    for more details.
  */
  MLMarkerTrackerProfile_Custom = 1,
  /*!
    \brief Optimized for speed.
    Use this profile to reduce the compute load and increase detection/tracker
    speed. This can result poor poses.
  */
  MLMarkerTrackerProfile_Speed = 2,
  /*!
    \brief Optimized for accuracy.
    Use this profile to optimize for accurate marker poses. This can cause
    increased load on the compute.
  */
  MLMarkerTrackerProfile_Accuracy = 3,
  /*!
    \brief Optimized for small targets.
    Use this profile to optimize for markers that are small or for larger
    markers that need to detected from far.
  */
  MLMarkerTrackerProfile_SmallTargets = 4,
  /*!
    \brief Optimized for FoV.
    Use this profile to be able to detect markers across a larger FoV.
    Marker Tracker system will attempt to use multiple cameras to detect the
    markers.
  */
  MLMarkerTrackerProfile_Large_FoV = 6,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackerProfile_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackerProfile;

/*!
  \brief Marker tracker FPS hint.

  The MLMarkerTrackingFpsHint enum values are used
  to hint to the back-end the max frames per second
  that should be analyzed. This is set in the
  MLMarkerTrackerCustomProfile structure and this setting
  applies to all enabled trackers.

  CPU load is a combination of enabled detector types,
  FpsHint and ResolutionHint. More detectors and a higher
  fps and resolution hints will result in a higher CPU load.
  High CPU load can affect the performance of your system.

  \apilevel 20
*/
typedef enum MLMarkerTrackingFpsHint {
  /*! Low FPS. */
  MLMarkerTrackingFpsHint_Low = 0,
  /*! Medium FPS. */
  MLMarkerTrackingFpsHint_Medium = 1,
  /*! High FPS. */
  MLMarkerTrackingFpsHint_High = 2,
  /*! Max possible FPS. */
  MLMarkerTrackingFpsHint_Max = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackingFpsHint_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackingFpsHint;

/*!
  \brief Marker tracker resolution hint.

  The MLMarkerTrackingResolutionHint enum values are
  used to hint to the back-end the resolution
  that should be used. This is set in the
  MLMarkerTrackerCustomProfile structure and this setting
  currently only applies to the QR, UPC and EAN detectors.

  CPU load is a combination of enabled detector types,
  FpsHint and ResolutionHint. More detectors and a higher
  fps and resolution hints will result in a higher CPU load.
  High CPU load can affect the performance of your system.

  \apilevel 20
*/
typedef enum MLMarkerTrackingResolutionHint {
  /*! Low Resolution. */
  MLMarkerTrackingResolutionHint_Low = 0,
  /*! Medium Resolution. */
  MLMarkerTrackingResolutionHint_Medium = 1,
  /*! High Resolution. */
  MLMarkerTrackingResolutionHint_High = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackingResolutionHint_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackingResolutionHint;

/*!
  \brief Marker tracker camera hint.

  The MLMarkerTrackerCameraHint enum values are used to hint to the camera
  that should be used. This is set in the MLMarkerTrackerCustomProfile structure
  and this setting currently only applies to the aruco detectors.

  RGB camera has higher resolution than world cameras and are better suited
  for use cases where the target to be tracked is small or needs to be detected
  from far.

  World cameras make use of multiple world cameras to improve accuracy and
  increase the FoV for detection.

  \apilevel 21
*/
typedef enum MLMarkerTrackerCameraHint {
  /*! Single RGB camera. */
  MLMarkerTrackerCameraHint_RGB_Camera = 0,
  /*! One or more world cameras. */
  MLMarkerTrackerCameraHint_World_Cameras = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackerCameraHint_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackerCameraHint;


/*!
  \brief Corner Refinement Method.

  The Aruco/April tag detector comes with several corner refinement methods.
  Choosing the right corner refinement method has an impact on the accuracy and
  speed trade-off that comes with each detection pipeline.

  \note Corner refinement only applies to Aruco and April tags, not QR codes.

  \apilevel 20
*/
typedef enum MLMarkerTrackerCornerRefineMethod {
  /*! No refinement. Inaccurate corners. */
  MLMarkerTrackerCornerRefineMethod_None = 0,
  /*! Subpixel refinement. Corners have subpixel coordinates. High detection
     rate, very fast, reasonable accuracy. */
  MLMarkerTrackerCornerRefineMethod_Subpix = 1,
  /*! Contour refinement. High detection rate, fast, reasonable accuracy. */
  MLMarkerTrackerCornerRefineMethod_Contour = 2,
  /*! AprilTag refinement. Reasonable detection rate, slowest, but very
     accurate. */
  MLMarkerTrackerCornerRefineMethod_AprilTag = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackerCornerRefineMethod_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackerCornerRefineMethod;

/*!
  \brief Full Frame Analysis Time Interval.

  In order to improve performance, the detectors don't always run on the full
  frame. Full frame analysis is however necessary to detect new markers that
  weren't detected before. Use this option to control how often the detector may
  detect new markers and its impact on tracking performance.

  \apilevel 20
*/
typedef enum MLMarkerTrackerFullAnalysisIntervalHint {
  /*! Detector analyzes every frame fully. */
  MLMarkerTrackerFullAnalysisIntervalHint_Max = 0,
  /*! Detector analyzes frame fully very often. */
  MLMarkerTrackerFullAnalysisIntervalHint_Fast = 1,
  /*! Detector analyzes frame fully a few times per second. */
  MLMarkerTrackerFullAnalysisIntervalHint_Medium = 2,
  /*! Detector analyzes frame fully about every second. */
  MLMarkerTrackerFullAnalysisIntervalHint_Slow = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackerFullAnalysisIntervalHint_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackerFullAnalysisIntervalHint;

/*!
  \brief Supported pre-defined Aruco dictionary and AprilTags.

  Marker Tracker supports pre-defined Aruco dictionary and AprilTags.
  Aruco dictionaries can be looked up and markers can be generated for them here:
  \link http://chev.me/arucogen/ \endlink

  \note: Due to the 4X4 and the 'Aruco Original' dictionaries suffering from frequent false detections, we discourage their use.

  \apilevel 20
*/
typedef enum MLMarkerTrackerArucoDictionaryName {
  /*! Default value. Nothing will be detected. */
  MLMarkerTrackerArucoDictionaryName_NotInitialized = -1,
  /*! 4 by 4 pixel Aruco marker dictionary with 50 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_4X4_50 = 0,
  /*! 4 by 4 pixel Aruco marker dictionary with 100 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_4X4_100,
  /*! 4 by 4 pixel Aruco marker dictionary with 250 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_4X4_250,
  /*! 4 by 4 pixel Aruco marker dictionary with 1000 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_4X4_1000,
  /*! 5 by 5 pixel Aruco marker dictionary with 50 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_5X5_50,
  /*! 5 by 5 pixel Aruco marker dictionary with 100 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_5X5_100,
  /*! 5 by 5 pixel Aruco marker dictionary with 250 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_5X5_250,
  /*! 5 by 5 pixel Aruco marker dictionary with 1000 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_5X5_1000,
  /*! 6 by 6 pixel Aruco marker dictionary with 50 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_6X6_50,
  /*! 6 by 6 pixel Aruco marker dictionary with 100 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_6X6_100,
  /*! 6 by 6 pixel Aruco marker dictionary with 250 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_6X6_250,
  /*! 6 by 6 pixel Aruco marker dictionary with 1000 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_6X6_1000,
  /*! 7 by 7 pixel Aruco marker dictionary with 50 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_7X7_50,
  /*! 7 by 7 pixel Aruco marker dictionary with 100 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_7X7_100,
  /*! 7 by 7 pixel Aruco marker dictionary with 250 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_7X7_250,
  /*! 7 by 7 pixel Aruco marker dictionary with 1000 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_7X7_1000,
  /*! 5 by 5 pixel Aruco marker dictionary with 1024 IDs. */
  MLMarkerTrackerArucoDictionaryName_DICT_ARUCO_ORIGINAL,
  /*! 4 by 4 bits, minimum hamming distance between any two codes = 5, 30 codes. */
  MLMarkerTrackerArucoDictionaryName_DICT_APRILTAG_16h5,
  /*! 5 by 5 bits, minimum hamming distance between any two codes = 9, 35 codes. */
  MLMarkerTrackerArucoDictionaryName_DICT_APRILTAG_25h9,
  /*! 6 by 6 bits, minimum hamming distance between any two codes = 10, 2320 codes. */
  MLMarkerTrackerArucoDictionaryName_DICT_APRILTAG_36h10,
  /*! 6 by 6 bits, minimum hamming distance between any two codes = 11, 587 codes. */
  MLMarkerTrackerArucoDictionaryName_DICT_APRILTAG_36h11,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackerArucoDictionaryName_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackerArucoDictionaryName;

/*!
  \brief Decoded Data Type enumeration.

  Each decoder may output different types of decoded
  data structures. The type field of #MLMarkerTrackingDecodedTypedData
  holds this enum and can be used to cast #MLMarkerTrackingDecodedTypedData
  to the correct sub type.

  \apilevel 20
*/
typedef enum MLMarkerTrackingDecodedDataType {
  /*! Represents no decoded data. */
  MLMarkerTrackingDecodedDataType_None = 0,
  /*! Aruco and AprilTag decoded data. */
  MLMarkerTrackingDecodedDataType_Aruco = 1,
  /*! QR decoded data. */
  MLMarkerTrackingDecodedDataType_QR = 2,
  /*! EAN-13 decoded data. */
  MLMarkerTrackingDecodedDataType_EAN_13 = 3,
  /*! UPC-A decoded data. */
  MLMarkerTrackingDecodedDataType_UPC_A = 4,
  /*! Code 128 decoded data. */
  MLMarkerTrackingDecodedDataType_Code_128 = 5,
  /*! Ensure enum is represented as 32 bits. */
  MLMarkerTrackingDecodedDataType_Ensure32Bits = 0x7FFFFFFF
} MLMarkerTrackingDecodedDataType;

/*!
  \brief Structure type selector.

  Different Marker Decoders will produce different data. Use this
  structure to find what the data structure is.
  \code
  switch ( data->type ) {
    case MLMarkerTrackingDecodedDataType_Aruco:
      MLMarkerTrackerDecodedArucoData * aruco = reinterpret_cast<MLMarkerTrackerDecodedArucoData*>(data);
      MLog(Verbose, "Received Aruco Code %u", aruco->id);
      break;
    default:
      MLog(Verbose, "Unhandled type received");
  }
  \endcode

  \apilevel 20
*/
typedef struct MLMarkerTrackerDecodedTypedData {
  /*! Type selector for the structure. */
  MLMarkerTrackingDecodedDataType type;
} MLMarkerTrackerDecodedTypedData;

/*!
  \brief Aruco decoded data.

  \apilevel 20
*/
typedef struct MLMarkerTrackerDecodedArucoData {
  /*! Type selector for the structure. */
  MLMarkerTrackingDecodedDataType type;
  /*! Dictionary used by the Aruco Marker. */
  MLMarkerTrackerArucoDictionaryName dictionary;
  /*! Aruco marker Id. */
  uint32_t id;
} MLMarkerTrackerDecodedArucoData;


/*!
  \brief Binary decoded data.

  \apilevel 20
*/
typedef struct MLMarkerTrackerDecodedBinaryData {
  /*! Type selector for the structure. */
  MLMarkerTrackingDecodedDataType type;
  /*! Binary data size. */
  uint32_t data_size;
  /*!
    \brief Binary data.

    This is the binary data directly from the
    scanned code. This typically does not include
    a terminating null character. When using this
    as a string, either always specify the length
    or manually add a null terminator after copying.
   */
  const char data[];
} MLMarkerTrackerDecodedBinaryData;

/*!
  \brief QR Code data.

  \apilevel 20
*/
typedef MLMarkerTrackerDecodedBinaryData MLMarkerTrackerDecodedQRData;

/*!
  \brief EAN-13 data.

  \apilevel 20
*/
typedef MLMarkerTrackerDecodedBinaryData MLMarkerTrackerDecodedEAN13Data;

/*!
  \brief UPC-A data.

  \apilevel 20
*/
typedef MLMarkerTrackerDecodedBinaryData MLMarkerTrackerDecodedUPCAData;

/*!
  \brief Code 128 data.

  \apilevel 25
*/
typedef MLMarkerTrackerDecodedBinaryData MLMarkerTrackerDecodedCode128Data;

/*!
  \brief Represents the decoded data.

  The different detectors will have different decoded outputs.
  See #MLMarkerTrackerDecodedTypedData for details on the output
  formats supported.

  \apilevel 20
*/
typedef struct MLMarkerTrackerDecodedData {
  /*!
    \brief Data decoded from a detected marker.

    Where data field contents depends on the detected marker,
    and data->type indicates which structure this actually contains.
  */
  const MLMarkerTrackerDecodedTypedData *data;

  /*!
    \brief Length of the decoded data.
  */
  uint32_t size;
} MLMarkerTrackerDecodedData;

/*!
  \brief Represents the result for a single marker.

  A list of these detections will be returned by the Marker Tracker, after processing a camera
  frame succesfully.

  \apilevel 20
*/
typedef struct MLMarkerTrackerResult {
  /*!
    \brief The data which was encoded in the marker.
  */
  MLMarkerTrackerDecodedData decoded_data;

  /*!
    \brief The detector type that created this result.
  */
  MLMarkerTrackerDetectorType detector_type;

  /*!
    \brief This indicates if coord_frame_marker holds a valid pose.

    If false do not use coord_frame_marker.
  */
  bool valid_pose;

  /*!
    \brief MLCoordinateFrameUID of the marker.

    When valid_pose is true, this can be passed to the
    MLSnapshotGetTransform() function to get the 6 DOF
    pose of the marker.
  */
  MLCoordinateFrameUID coord_frame_marker;

  /*!
    \brief The reprojection error of this marker detection in meters.

    A high reprojection error means that the estimated pose of the marker doesn't match well with
    the 2D detection on the processed video frame and thus the pose might be inaccurate. The error
    is given in meters, representing the displacement between real marker and its estimated pose.
    This means this is a normalized number, independent of marker distance or length.
  */
  float reprojection_err;

} MLMarkerTrackerResult;

/*!
  \brief An array of all the marker results from the Marker Tracker.

  Free this array with #MLMarkerTrackerReleaseResult.

  \apilevel 20
*/
typedef struct MLMarkerTrackerResultArray {
  /*! Version of this structure. */
  uint32_t version;

  /*! Pointer to an array of pointers for MLMarkerTrackerResult. */
  MLMarkerTrackerResult** detections;

  /*! Number of markers being tracked. */
  size_t count;
} MLMarkerTrackerResultArray;


/*!
  \brief Initializes default values for MLMarkerTrackerResultArray.

  \apilevel 20

  \param[in,out] inout_result_array The object to initialize to an empty result array.

  \retval MLResult_InvalidParam Failed to init result array due to pointer being NULL.
  \retval MLResult_Ok Successfully initialized the marker tracking result array.
*/
ML_STATIC_INLINE MLResult MLMarkerTrackerResultArrayInit(MLMarkerTrackerResultArray *inout_result_array) {
  if (inout_result_array == NULL) {
    return MLResult_InvalidParam;
  }
  inout_result_array->version = 1u;
  inout_result_array->detections = NULL;
  inout_result_array->count = 0;
  return MLResult_Ok;
}

/*!
  \brief Marker Tracker Custom Profile.

  Marker Tracker system provides a set of standard tracking profiles (see
  #MLMarkerTrackerProfile) to configure the tracker settings. If this does not
  meet the application's needs then the application can choose to define a custom
  tracker profile using MLMarkerTrackerCustomProfile.
*/
typedef struct MLMarkerTrackerCustomProfile {
  /*!
    \brief Framerate hint used for all detectors.
    See #MLMarkerTrackingFpsHint for details.
  */
  MLMarkerTrackingFpsHint fps_hint;

  /*!
    \brief The resolution hint.
    See #MLMarkerTrackingResolutionHint for details.
  */
  MLMarkerTrackingResolutionHint resolution_hint;

  /*!
    \brief Camera hint used for all detectors.
    See #MLMarkerTrackerCameraHint for details.
  */
  MLMarkerTrackerCameraHint camera_hint;

  /*! \brief Corner refinement method for Aruco/April tag detector.

    This option provides control over corner refinement methods and a way to
    balance detection rate, speed and pose accuracy. Always available and
    applicable for Aruco and April tags.

    See #MLMarkerTrackerCornerRefineMethod for details.
  */
  MLMarkerTrackerCornerRefineMethod corner_refine_method;

  /*! \brief Activate Edge Refinement.
    Run refinement step that uses marker edges to generate even more accurate
    corners, but slow down tracking rate overall by consuming more compute.
    Aruco/April tags only.

    \note Recommended in combination with Contour Corner Refine method for best
    balance between performance and accuracy.
  */
  bool use_edge_refinement;

  /*!
    \brief Time interval between fully analyzed frames.

    For faster tracking not every single frame is fully analyzed. Increasing
    this time will improve tracking speed but negatively impact detection
    latency of new markers.
  */
  MLMarkerTrackerFullAnalysisIntervalHint full_analysis_interval_hint;

} MLMarkerTrackerCustomProfile;



/*!
  \brief Marker Tracker Settings.

  When creating a Marker Tracker, this list of settings needs to be passed to configure the tracker
  properly. The tracker will only output detections of markers that belong to the defined dictionary
  and the estimated poses will only be correct if the marker length has been set correctly.

  \apilevel 21
*/
typedef struct MLMarkerTrackerSettings {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief If \c true, Marker Tracker will detect and track the enabled marker types.

    Marker Tracker should be disabled when app is paused and enabled when app resumes.
    When enabled, Marker Tracker will gain access to the camera and start analysing camera frames.
    When disabled Marker Tracker will release the camera and stop tracking markers.
    Internal state of the tracker will be maintained.
  */
  bool enable_marker_tracking;

  /*!
    \brief The detector types that are enabled.

    Enable detector types by combining any number of #MLMarkerTrackerDetectorType flags using '|' (bitwise 'or').
  */
  uint32_t enabled_detector_types;

  /*! \brief Aruco Dictionary or April Tag name from which markers shall be tracked.

    Unused if Aruco detector is not enabled.
  */
  MLMarkerTrackerArucoDictionaryName dictionary;

  /*!
    \brief The length of the Aruco markers that shall be tracked.

    The marker length is important to know, because once a marker is detected we
    can only determine its 3D position if we know how large it is in real life.
    The length of a marker is given in meters and represents the length of a
    single side of the marker square.

    Unused if Aruco detector is not enabled.
  */
  float aruco_marker_length;

  /*!
    \brief The length of the QR code that shall be tracked.

    The marker length is important to know, because once a QR code is detected
    we can only determine its 3D position if we know how large it is in real
    life.  The length of a QR code is given in meters and represents the length
    of a single side of the QR code square.

    Unused if QR detector is not enabled.
  */
  float qr_code_length;

  /*!
    \brief Tracker profile to be used.

    See #MLMarkerTrackerProfile for details.
  */
  MLMarkerTrackerProfile tracker_profile;

  /*!
    \brief Custom tracker profile to be used.

    See #MLMarkerTrackerCustomProfile for details. This custom profile will only
    be used when MLMarkerTrackerProfile is set to MLMarkerTrackerProfile_Custom
    and ignored for all other cases.
  */
  MLMarkerTrackerCustomProfile custom_tracker_profile;
} MLMarkerTrackerSettings;

/*!
  \brief Initializes default values for MLMarkerTrackerSettings.

  This call initializes a setting struct with default values. Default values will not start any tracking as the
  API user needs to add which detector types should be enabled and in case of Aruco/April tag tracking also the
  corresponding dictionary.

  Default marker size is 10cm, but smaller or larger sizes are supported as long as they are detectable with the
  camera.

  Default corner refinement method is 'Contour'. Edge refinement is deactivated.

  Max time between fully analyzed frames is 1s.

  \apilevel 28

  \param[in,out] inout_settings The object to initialize with default settings.

  \retval MLResult_InvalidParam Failed to init settings array due to pointer being NULL.
  \retval MLResult_Ok Successfully initialized the marker tracking settings array.
*/
ML_STATIC_INLINE MLResult MLMarkerTrackerSettingsInit(MLMarkerTrackerSettings *inout_settings) {
  if (inout_settings == NULL) {
    return MLResult_InvalidParam;
  }
  memset(inout_settings, 0, sizeof(MLMarkerTrackerSettings));
  inout_settings->version = 6u;
  inout_settings->dictionary = MLMarkerTrackerArucoDictionaryName_NotInitialized;
  inout_settings->aruco_marker_length = 0.1f;
  inout_settings->qr_code_length = 0.1f;
  inout_settings->enable_marker_tracking = true;
  inout_settings->tracker_profile = MLMarkerTrackerProfile_Default;
  return MLResult_Ok;
}

/*!
  \brief Create a Marker Tracker.

  \note Only one marker tracker is allowed per app/session. This call will fail when called multiple times.
  Use MLMarkerTrackerUpdateSettings and update values if you want to change the detector.

  \apilevel 21

  \param[in] settings List of settings of type MLMarkerTrackerSettings that configure the tracker.
  \param[out] out_handle A pointer to an MLHandle to the newly created Marker Tracker.
              If this operation fails, out_handle will be ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to create Marker Tracker due to invalid out_handle.
  \retval MLResult_Ok Successfully created Marker Tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied Failed to create tracker due to lack of permission(s).
  \retval MLResult_UnspecifiedFailure Failed to create the Marker Tracker due to an internal error.

  \permissions com.magicleap.permission.MARKER_TRACKING (protection level: normal)
*/
ML_API MLResult ML_CALL MLMarkerTrackerCreate(const MLMarkerTrackerSettings *settings, MLHandle *out_handle);

/*!
  \brief Update the Marker Tracker with new settings.

  \apilevel 21

  \param[in] tracker_handle MLHandle to the Marker Tracker created by MLMarkerTrackerCreate().
  \param[in] tracker_settings List of new Marker Tracker settings.

  \retval MLResult_InvalidParam Failed to update the settings due to invalid tracker_settings.
  \retval MLResult_Ok Successfully updated the Marker Tracker settings.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to update the settings due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLMarkerTrackerUpdateSettings(MLHandle tracker_handle,
                                                     const MLMarkerTrackerSettings *tracker_settings);

/*!
  \brief Destroy an Marker Tracker.

  \apilevel 20

  \param[in] tracker_handle MLHandle to the Marker Tracker created by MLMarkerTrackerCreate().

  \retval MLResult_Ok Successfully destroyed the Marker Tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to destroy the tracker due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLMarkerTrackerDestroy(MLHandle tracker_handle);

/*!
  \brief Get the results for Marker Tracking.

  \apilevel 20

  \param[in] tracker_handle #MLHandle to the Marker Tracker created by MLMarkerTrackerCreate().
  \param[out] out_data Pointer to an array of pointers to MLMarkerTrackerResult.
              The content will be freed by the MLMarkerTrackerReleaseResult.

  \retval MLResult_InvalidParam Failed to return detection data due to invalid out_data.
  \retval MLResult_Ok Successfully fetched and returned all detections.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to return detections due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLMarkerTrackerGetResult(MLHandle tracker_handle,
                                                MLMarkerTrackerResultArray *out_data);

/*!
  \brief Release the resources for the results array.

  \apilevel 20

  \param[in] data The list of detections to be freed.

  \retval MLResult_InvaldParam Failed to free structure due to invalid data.
  \retval MLResult_Ok Successfully freed data structure.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to free data due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLMarkerTrackerReleaseResult(MLMarkerTrackerResultArray *data);

/*! \} */

ML_EXTERN_C_END
