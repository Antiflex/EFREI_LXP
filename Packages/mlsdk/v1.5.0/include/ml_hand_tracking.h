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
  \addtogroup HandTracking Hand Tracking
  \sharedobject perception.magicleap
  \brief APIs for the Hand Tracking system.
  \{
*/

/*! Available hand types. */
typedef enum MLHandTrackingHandType {
  /*! Left hand. */
  MLHandTrackingHandType_Left = 0,
  /*! Right hand. */
  MLHandTrackingHandType_Right = 1,
  /*! Number of hands. */
  MLHandTrackingHandType_Count = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLHandTrackingHandType_Ensure32Bits = 0x7FFFFFFF
} MLHandTrackingHandType;

enum {
  /*! Maximum number of key points per hand. */
  MLHandTrackingStaticData_MaxKeyPoints = 28
};

/*!
  \brief Keypoint index ordering.

  The index ordering of 28 keypoints exposed in array
  keypoints_mask[MLHandTrackingStaticData_MaxKeyPoints] and
  left_frame/right_frame[MLHandTrackingStaticData_MaxKeyPoints].

  \apilevel 7
*/
typedef enum MLHandTrackingKeyPoint {
  MLHandTrackingKeyPoint_Thumb_Tip = 0,
  MLHandTrackingKeyPoint_Thumb_IP,
  MLHandTrackingKeyPoint_Thumb_MCP,
  MLHandTrackingKeyPoint_Thumb_CMC,
  MLHandTrackingKeyPoint_Index_Tip,
  MLHandTrackingKeyPoint_Index_DIP,
  MLHandTrackingKeyPoint_Index_PIP,
  MLHandTrackingKeyPoint_Index_MCP,
  MLHandTrackingKeyPoint_Middle_Tip,
  MLHandTrackingKeyPoint_Middle_DIP,
  MLHandTrackingKeyPoint_Middle_PIP,
  MLHandTrackingKeyPoint_Middle_MCP,
  MLHandTrackingKeyPoint_Ring_Tip,
  MLHandTrackingKeyPoint_Ring_DIP,
  MLHandTrackingKeyPoint_Ring_PIP,
  MLHandTrackingKeyPoint_Ring_MCP,
  MLHandTrackingKeyPoint_Pinky_Tip,
  MLHandTrackingKeyPoint_Pinky_DIP,
  MLHandTrackingKeyPoint_Pinky_PIP,
  MLHandTrackingKeyPoint_Pinky_MCP,
  MLHandTrackingKeyPoint_Wrist_Center,
  MLHandTrackingKeyPoint_Wrist_Ulnar,
  MLHandTrackingKeyPoint_Wrist_Radial,
  MLHandTrackingKeyPoint_Hand_Center,
  MLHandTrackingKeyPoint_Index_Meta,
  MLHandTrackingKeyPoint_Middle_Meta,
  MLHandTrackingKeyPoint_Ring_Meta,
  MLHandTrackingKeyPoint_Pinky_Meta,
  /*! Maximum number of key points per gesture. */
  MLHandTrackingKeyPoint_Count = MLHandTrackingStaticData_MaxKeyPoints,
  MLHandTrackingKeyPoint_Ensure32Bits = 0x7FFFFFFF
} MLHandTrackingKeyPoint;


/*!
  \brief MLCoordinateFrameUIDs for the keypoints.

  See #MLHandTrackingKeyPoint for more details.

  \apilevel 20
*/

typedef struct MLHandTrackingCFUIDs {
  MLCoordinateFrameUID keypoint_cfuids[MLHandTrackingStaticData_MaxKeyPoints];
} MLHandTrackingCFUIDs;

/*!
  \brief Static information about a hand tracker.

  This structure must be initialized by calling MLHandTrackingStaticDataInit() before use.

  \apilevel 28
*/
typedef struct MLHandTrackingStaticData {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief Smooth filtered coordinate frame identifiers of left and right hands.

    See #MLHandTrackingHandType for more details.
  */
  MLHandTrackingCFUIDs hand_cfuids[MLHandTrackingHandType_Count];
  /*! Unfiltered coordinate frame identifiers of left and right hands. */
  MLHandTrackingCFUIDs unfiltered_hand_cfuids[MLHandTrackingHandType_Count];
} MLHandTrackingStaticData;

/*!
  \brief Initializes default values for MLHandTrackingStaticData.

  \apilevel 28

  \param[in, out] inout_attr The object to initialize with default values.
*/
ML_STATIC_INLINE void MLHandTrackingStaticDataInit(MLHandTrackingStaticData *inout_attr) {
  if (NULL != inout_attr) {
    memset(inout_attr, 0, sizeof(MLHandTrackingStaticData));
    inout_attr->version = 3u;
  }
}

/*!
  \brief State of a single hand.

  Same for both filtered and unfiltered keypoints.

  \apilevel 20
*/
typedef struct MLHandTrackingHandState {
  /*!
    \brief Specifies if the hand is detected.
  */
  bool is_hand_detected;
  /*!
    \brief The confidence level of a hand is present in the scene.

    Value is between [0, 1], 0 is low, 1 is high degree of confidence.
  */
  float hand_confidence;
  /*!
   \brief Mask indicates if a keypoint is present or not.
  */
  bool keypoints_mask[MLHandTrackingStaticData_MaxKeyPoints];
} MLHandTrackingHandState;

/*!
  \brief Data which is received when querying hand tracker from MLHandTrackingGetData().

  This structure must be initialized by calling MLHandTrackingDataInit() before use.

  \apilevel 20
*/
typedef struct MLHandTrackingData {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief Hand tracker states of the hands.

    See #MLHandTrackingHandType for more details.
  */
  MLHandTrackingHandState hand_state[MLHandTrackingHandType_Count];

  /*! Timestamp of last measurement in nanoseconds. */
  MLTime timestamp_ns;

} MLHandTrackingData;

/*!
  \brief Initializes values for MLHandTrackingData.

  \apilevel 20

  \param[in,out] inout_attr The object to initialize.
*/
ML_STATIC_INLINE void MLHandTrackingDataInit(MLHandTrackingData *inout_attr) {
  if (NULL != inout_attr) {
    memset(inout_attr, 0, sizeof(MLHandTrackingData));
    inout_attr->version = 3u;
  }
}

/*!
  \brief Enumeration of flags to select settings related to hand tracking.

  Filtered keypoints are always available, no matter the settings.

  \apilevel 28
*/
typedef enum MLHandTrackingSettingsFlags {
  /*! No additional settings used. */
  MLHandTrackingSettingsFlags_None = 0,
  /*! Enable unfiltered keypoints. See #MLHandTrackingGetStaticData for more details. */
  MLHandTrackingSettingsFlags_UnfilteredKeypoints = 1 << 0,
  /*! Ensure enum is represented as 32 bits. */
  MLHandTrackingSettingsFlags_Ensure32Bits = 0x7FFFFFFF
} MLHandTrackingSettingsFlags;

/*!
  \brief Settings of the hand tracking system.

  This structure must be initialized by calling MLHandTrackingSettingsInit().

  \apilevel 28
*/
typedef struct MLHandTrackingSettings {
  /*! Version of this structure. */
  uint32_t version;
  /*! MLHandTrackingSettings Flags. */
  uint32_t flags;
} MLHandTrackingSettings;

/*!
  \brief Initializes default values for MLHandTrackingSettings.

  \apilevel 28

  \param[in, out] inout_settings The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLHandTrackingSettingsInit(MLHandTrackingSettings *inout_settings) {
  if (NULL != inout_settings) {
    memset(inout_settings, 0, sizeof(MLHandTrackingSettings));
    inout_settings->version = 1u;
    inout_settings->flags = MLHandTrackingSettingsFlags_None;
  }
}

/*!
  \deprecated Deprecated since 1.3.0. Scheduled for removal. Replaced by MLHandTrackingCreateEx.
  \brief Creates a hand tracker.

  \apilevel 20

  \param[out] out_handle A pointer to an #MLHandle which will contain the handle of the hand tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok The tracker was created successfully.
  \retval MLResult_PermissionDenied The application lacks the required permission.
  \retval MLResult_UnspecifiedFailure Failed to create the tracker.

  \permissions com.magicleap.permission.HAND_TRACKING (protection level: normal)
*/
ML_DEPRECATED_MSG("Replaced by MLHandTrackingCreateEx.")
ML_API MLResult ML_CALL MLHandTrackingCreate(MLHandle *out_handle);

/*!
  \brief Creates a hand tracker.

  \apilevel 28

  \param[in] settings A pointer to a previously initialized #MLHandTrackingSettings struct.
  \param[out] out_handle A pointer to an #MLHandle which will contain the handle of the hand tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok The tracker was created successfully.
  \retval MLResult_PermissionDenied The application lacks the required permission.
  \retval MLResult_UnspecifiedFailure Failed to create the tracker.

  \permissions com.magicleap.permission.HAND_TRACKING (protection level: normal)
*/
ML_API MLResult ML_CALL MLHandTrackingCreateEx(const MLHandTrackingSettings* settings, MLHandle *out_handle);

/*!
  \brief Updates settings.

  \apilevel 28

  \param[in] hand_tracker A handle to a Hand Tracker created by MLHandTrackingCreateEx().
  \param[in] settings A pointer to a previously initialized #MLHandTrackingSettings struct.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok The settings were updated successfully.
  \retval MLResult_UnspecifiedFailure Failed to update the settings.

  \permissions None
*/
ML_API MLResult ML_CALL MLHandTrackingUpdateSettings(MLHandle hand_tracker, const MLHandTrackingSettings* settings);

/*!
  \brief Destroys a hand tracker.

  \apilevel 20

  \param[in] hand_tracker A handle to a Hand Tracker created by MLHandTrackingCreateEx().

  \retval MLResult_Ok It successfully destroyed the tracker.
  \retval MLResult_UnspecifiedFailure Failed to destroy the tracker.

  \permissions None
*/
ML_API MLResult ML_CALL MLHandTrackingDestroy(MLHandle hand_tracker);

/*!
  \brief Queries the state of the hand tracker.

  The #MLHandTrackingData is the same for both filtered and unfiltered keypoints.

  \apilevel 20

  \param[in] hand_tracker A handle to a Hand Tracker created by MLHandTrackingCreateEx().
  \param[out] out_data Pointer to a variable that receives information about the tracked hands.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok The hand information was available and the information in out_data is valid.
  \retval MLResult_UnspecifiedFailure Failed to get the hand information.

  \permissions None
*/
ML_API MLResult ML_CALL MLHandTrackingGetData(MLHandle hand_tracker, MLHandTrackingData *out_data);

/*!
  \brief Gets static information about hand tracking system.

  See #MLHandTrackingStaticData for more details.

  \apilevel 20

  \param[in] hand_tracker A handle to a Hand Tracker created by MLHandTrackingCreateEx().
  \param[out] out_data Pointer to a variable that receives static data about the hand tracker.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok The hand information was available and the information in out_data is valid.
  \retval MLResult_UnspecifiedFailure Failed to get the hand information.

  \permissions None
*/
ML_API MLResult ML_CALL MLHandTrackingGetStaticData(MLHandle hand_tracker, MLHandTrackingStaticData *out_data);

/*! \} */

ML_EXTERN_C_END
