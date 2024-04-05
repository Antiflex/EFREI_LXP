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
  \defgroup GestureClassification Gesture Classification System
  \addtogroup GestureClassification
  \sharedobject perception.magicleap
  \brief APIs for the Gesture Classification system.

  The gesture classification system identifies specific hand configurations and
  exposes them via the APIs here. These hand configurations can be broadly
  divided into two groups:

  1. Postures (#MLGestureClassificationPostureType).
  2. Key Poses (#MLGestureClassificationKeyPoseType).


  \section Postures

  Postures is a collection of hand configuration that allows for meaningful
  variations of the same configuration. For example a hand configuration is
  classified as pinch posture when the index and thumb tip is touching while
  the other three fingers are fully extended. At the same time a hand configuration
  where the index and thumb tips are touching but the other three fingers are
  partially curled will still be treated as a pinch posture.

  Postures will be more accommodative to variations seen between users and the
  same user doing the gesture in slightly different ways.

  Postures will work well for use cases where the user is interacting with the
  UI over time. Examples: grab and move, point and click.


  \section KeyPoses

  KeyPoses on the other hand is a discrete collection of static hand configurations.
  It looks for specific geometric relationship between the hand key points.

  KeyPoses will work well for use cases where the user need a on-off switch, a button.
  Examples: start capture, save session.


  \section Interaction Point

  The interaction point is a transform which dynamically adapts, in both
  translation and rotation, based on the current classified posture (#MLGestureClassificationPostureType).
  It provides a single optimal point of reference to simplify common direct and
  indirect hand interactions.

  \{
*/

/*! Available hand types. */
typedef enum MLGestureClassificationHandType {
  /*! Left hand. */
  MLGestureClassificationHandType_Left = 0,
  /*! Right hand. */
  MLGestureClassificationHandType_Right = 1,
  /*! Number of hands. */
  MLGestureClassificationHandType_Count = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLGestureClassificationHandType_Ensure32Bits = 0x7FFFFFFF
} MLGestureClassificationHandType;


/*!
  \brief Static information about the gesture classification.

  Populate with MLGestureClassificationGetStaticData().
  This structure must be initialized by calling MLGestureClassificationStaticDataInit() before use.

  \apilevel 20
*/
typedef struct MLGestureClassificationStaticData {
  /*! Version of this structure. */
  uint32_t version;
  /*! CFUID for hands' interaction point transform based on the current posture type. */
  MLCoordinateFrameUID hand_interaction[MLGestureClassificationHandType_Count];
  /*! CFUID for hands' center point transform. */
  MLCoordinateFrameUID hand_transform[MLGestureClassificationHandType_Count];
} MLGestureClassificationStaticData;

/*!
  \brief Initializes default values for MLGestureClassificationStaticData.

  \apilevel 20

  \param[in, out] inout_data The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLGestureClassificationStaticDataInit(MLGestureClassificationStaticData* inout_data) {
  if (NULL != inout_data) {
    memset(inout_data, 0, sizeof(MLGestureClassificationStaticData));
    inout_data->version = 1u;
  }
}

/*!
  \brief System gesture classification posture type.

  \apilevel 20
 */
typedef enum MLGestureClassificationPostureType {
  /*! None. */
  MLGestureClassificationPostureType_None = 0,
  /*! Pinch posture. */
  MLGestureClassificationPostureType_Pinch = 1,
  /*! Point posture. */
  MLGestureClassificationPostureType_Point = 2,
  /*! Grasp posture. */
  MLGestureClassificationPostureType_Grasp = 3,
  /*! Open hand. */
  MLGestureClassificationPostureType_Open = 4,
  /*! Ensure enum is represented as 32 bits. */
  MLGestureClassificationPostureType_Ensure32Bits = 0x7FFFFFFF
} MLGestureClassificationPostureType;

/*!
  \brief System gesture classification key pose type.

  \apilevel 20
 */
typedef enum MLGestureClassificationKeyPoseType {
  /*! None. */
  MLGestureClassificationKeyPoseType_None = 0,
  /*! OK pose. */
  MLGestureClassificationKeyPoseType_OK = 1,
  /*! C pose. */
  MLGestureClassificationKeyPoseType_C = 2,
  /*! Pinch pose. */
  MLGestureClassificationKeyPoseType_Pinch = 3,
  /*! Finger pose. */
  MLGestureClassificationKeyPoseType_Finger = 4,
  /*! L pose. */
  MLGestureClassificationKeyPoseType_L = 5,
  /*! Thumb up pose. */
  MLGestureClassificationKeyPoseType_Thumb = 6,
  /*! Fist pose. */
  MLGestureClassificationKeyPoseType_Fist = 7,
  /*! Open pose. */
  MLGestureClassificationKeyPoseType_Open = 8,
  /*! Ensure enum is represented as 32 bits. */
  MLGestureClassificationKeyPoseType_Ensure32Bits = 0x7FFFFFFF
} MLGestureClassificationKeyPoseType;

/*!
  \brief Gesture classification posture related finger data.

  Pinch values are measured between the finger and thumb.
  In case thumb is the finger, values are same with index's values.

  \apilevel 20
 */
typedef struct MLGestureClassificationPostureFingerData {
  /*! Normalized pinch angle (range 0.0 ~ 1.0). -1.0 if the value is not valid. */
  float pinch_normalized_angle;
  /*! Absolute pinch angle (angular) in degrees. -1.0 if the value is not valid. */
  float pinch_angle_of_separation_deg;
  /*! Normalized pinch distance (range 0.0 ~ 1.0). -1.0 if the value is not valid. */
  float pinch_normalized_distance;
  /*! Absolute pinch distance (euclidean) in meters. -1.0 if the value is not valid. */
  float pinch_distance_m;
} MLGestureClassificationPostureFingerData;

/*!
  \brief Gesture classification state of a single finger.

  \apilevel 20
 */
typedef struct MLGestureClassificationFingerState {
  /*! State of finger. */
  bool is_extended;
  /*! Finger length in meters. */
  float length_m;
  /*! State of finger extension range 0.0 to 1.0. (0.0 folded, 1.0 fully extended). */
  float normalized_extension;
  /*! Absolute angle to palm (angular). -1.0 if the value is not valid. */
  float angle_to_palm;
  /*! Gesture classification posture related finger data. */
  MLGestureClassificationPostureFingerData posture_data;
} MLGestureClassificationFingerState;

/*!
  \brief Gesture classification state of a single hand.

  \apilevel 20
*/
typedef struct MLGestureClassificationState {
  /*! Gesture classification hand posture type. */
  MLGestureClassificationPostureType posture_type;
  /*! Gesture classification hand key pose type. */
  MLGestureClassificationKeyPoseType keypose_type;
  /*! Thumb finger state data. */
  MLGestureClassificationFingerState thumb;
  /*! Index finger state data. */
  MLGestureClassificationFingerState index;
  /*! Middle finger state data. */
  MLGestureClassificationFingerState middle;
  /*! Ring finger state data. */
  MLGestureClassificationFingerState ring;
  /*! Pinky finger state data. */
  MLGestureClassificationFingerState pinky;
  /*! Angle between thumb and index (angular) in degrees. */
  float angle_thumb_index_deg;
  /*! Angle between index and middle (angular) in degrees. */
  float angle_index_middle_deg;
  /*! Angle between middle and ring (angular) in degrees. */
  float angle_middle_ring_deg;
  /*! Angle between ring and pinky (angular) in degrees. */
  float angle_ring_pinky_deg;
} MLGestureClassificationState;

/*!
  \brief Data which is received when querying tracker from MLGestureClassificationGetData().

  This structure must be initialized by calling MLGestureClassificationDataInit() before use.

  \apilevel 20
*/
typedef struct MLGestureClassificationData {
  /*! Version of this structure. */
  uint32_t version;
  /*! Gesture classification state of the left and right hand. */
  MLGestureClassificationState hand_state[MLGestureClassificationHandType_Count];
} MLGestureClassificationData;

/*!
  \brief Initializes default values for MLGestureClassificationData.

  \apilevel 20

  \param[in, out] inout_data The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLGestureClassificationDataInit(MLGestureClassificationData* inout_data) {
  if (NULL != inout_data) {
    memset(inout_data, 0, sizeof(MLGestureClassificationData));
    inout_data->version = 1u;
  }
}

/*!
  \brief Creates a gesture classification tracker.

  \apilevel 20

  \param[out] out_handle A handle to the created gesture classification tracker. Only valid if the return value is MLResult_Ok.

  \retval MLResult_InvalidParam Failed to create a tracker due to an invalid parameter.
  \retval MLResult_Ok The tracker was created successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PrivilegeDenied The application lacks privilege.
  \retval MLResult_UnspecifiedFailure  The operation failed with an unspecified error.

  \permissions com.magicleap.permission.HAND_TRACKING (protection level: normal)
*/
ML_API MLResult ML_CALL MLGestureClassificationCreate(MLHandle* out_handle);

/*!
  \brief Destroys a gesture classification tracker.

  \apilevel 20

  \param[in] handle A handle to a gesture classification tracker created by MLGestureClassificationCreate().

  \retval MLResult_InvalidParam Failed to destroy a tracker due to an invalid parameter.
  \retval MLResult_Ok It successfully destroyed the tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure  The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLGestureClassificationDestroy(MLHandle handle);

/*!
  \brief Gets static information about the gesture classification.

  \apilevel 20

  \param[in] handle A handle to a gesture classification tracker created by MLGestureClassificationCreate().
  \param[out] out_data Target to populate the data about the gesture classification.

  \retval MLResult_InvalidParam Failed to get static data due to an invalid parameter.
  \retval MLResult_Ok Gesture classification static data was successfully received.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure  The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLGestureClassificationGetStaticData(MLHandle handle, MLGestureClassificationStaticData *out_data);

/*!
  \brief Queries the state of the gesture classification.

  \apilevel 20

  \param[in] handle A handle to a gesture classification tracker created by MLGestureClassificationCreate().
  \param[out] out_data Pointer to #MLGestureClassificationData structure.

  \retval MLResult_InvalidParam Failed to retrieve data due to an invalid parameter.
  \retval MLResult_Ok The state information was available and the information in out_data is valid.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLGestureClassificationGetData(MLHandle handle, MLGestureClassificationData *out_data);

/*! \} */

ML_EXTERN_C_END
