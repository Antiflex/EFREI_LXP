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

#include <string.h>

ML_EXTERN_C_BEGIN

/*!
  \defgroup HeadTracking Head Tracking
  \addtogroup HeadTracking
  \sharedobject perception.magicleap
  \brief APIs for the Head Tracking system.

  \{
*/

/*! Static information about a Head Tracker. Populate this structure with MLHeadTrackingGetStaticData(). */
typedef struct MLHeadTrackingStaticData {
  /*! Coordinate frame ID. */
  MLCoordinateFrameUID coord_frame_head;
} MLHeadTrackingStaticData;

/*!
  \deprecated Deprecated since 1.2.0. Scheduled for removal. Replaced by MLHeadTrackingErrorFlag.
  \brief A set of possible error conditions that can cause Head Tracking to be less than ideal.

  \apilevel 1
*/
typedef enum MLHeadTrackingError {
  /*! No error, tracking is nominal. */
  MLHeadTrackingError_None,
  /*! There are not enough features in the environment. */
  MLHeadTrackingError_NotEnoughFeatures,
  /*! Lighting in the environment is not sufficient to track accurately. */
  MLHeadTrackingError_LowLight,
  /*! Head tracking failed for an unknown reason. */
  MLHeadTrackingError_Unknown,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingError_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingError;

/*!
  \brief A set of possible error conditions that can cause Head Tracking to be less than ideal.

  \apilevel 26
*/
typedef enum MLHeadTrackingErrorFlag {
  /*! No error, tracking is nominal. */
  MLHeadTrackingErrorFlag_None = 0,
  /*! Head tracking failed for an unknown reason. */
  MLHeadTrackingErrorFlag_Unknown = 1 << 0,
  /*! There are not enough features in the environment. */
  MLHeadTrackingErrorFlag_NotEnoughFeatures = 1 << 1,
  /*! Lighting in the environment is not sufficient to track accurately. */
  MLHeadTrackingErrorFlag_LowLight = 1 << 2,
  /*! Head tracking failed due to excessive motion. */
  MLHeadTrackingErrorFlag_ExcessiveMotion = 1 << 3,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingErrorFlag_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingErrorFlag;

/*!
  \deprecated Deprecated since 1.2.0. Scheduled for removal. Replaced by MLHeadTrackingStatus.
  \brief A set of possible tracking modes the Head Tracking system can be in.

  \apilevel 1
*/
typedef enum MLHeadTrackingMode {
  /*! Full 6 degrees of freedom tracking (position and orientation). */
  MLHeadTrackingMode_6DOF = 0,
  /*! Head tracking is unavailable. */
  MLHeadTrackingMode_Unavailable = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingMode_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingMode;

/*!
  \brief A set of possible tracking status for the Head Tracking system.

  \apilevel 26
*/
typedef enum MLHeadTrackingStatus {
  /*! Head tracking is unavailable. */
  MLHeadTrackingStatus_Invalid = 0,
  /*! Head tracking is initializing. */
  MLHeadTrackingStatus_Initializing = 1,
  /*! Head tracking is relocalizing. */
  MLHeadTrackingStatus_Relocalizing = 2,
  /*! Valid head tracking data is available. */
  MLHeadTrackingStatus_Valid = 100,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingStatus_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingStatus;


/*!
  \deprecated Deprecated since 1.2.0. Scheduled for removal. Replaced by MLHeadTrackingStateEx.
  \brief A structure containing information on the current state of the Head Tracking system.

  \apilevel 1
*/
typedef struct MLHeadTrackingState {
  /*! What tracking mode the Head Tracking system is currently in. */
  MLHeadTrackingMode mode;
  /*! A confidence value (from [0, 1]) representing the confidence in the current pose estimation. */
  float confidence;
  /*! Represents what tracking error (if any) is present. */
  MLHeadTrackingError error;
} MLHeadTrackingState;

/*!
  \brief Structure containing information on the current state of the Head Tracking system.
  This structure must be initialized by calling #MLHeadTrackingStateExInit before use.

  \apilevel 26
*/
typedef struct MLHeadTrackingStateEx {
  /*! Version of this structure. */
  uint32_t version;
  /*! Current status of the Head Tracking system. */
  MLHeadTrackingStatus status;
  /*! Confidence value (from [0, 1]) representing the confidence in the current pose. */
  float confidence;
  /*! Represents a bitmask of #MLHeadTrackingErrorFlag. */
  uint32_t error;
} MLHeadTrackingStateEx;

/*!
  \brief Initialize default values for a #MLHeadTrackingStateEx structure.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLHeadTrackingStateExInit(MLHeadTrackingStateEx *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLHeadTrackingStateEx));
    inout_info->version = 1;
  }
}

/*!
  \brief Different types of map events that can occur that a developer may have to handle.

  \apilevel 2
*/
typedef enum MLHeadTrackingMapEvent {
  /*! Map was lost. It could possibly recover. */
  MLHeadTrackingMapEvent_Lost = (1 << 0),
  /*! Previous map was recovered. */
  MLHeadTrackingMapEvent_Recovered = (1 << 1),
  /*! Failed to recover previous map. */
  MLHeadTrackingMapEvent_RecoveryFailed = (1 << 2),
  /*! New map session created. */
  MLHeadTrackingMapEvent_NewSession = (1 << 3),
  /*! Ensure enum is represented as 32 bits. */
  MLHeadTrackingMapEvent_Ensure32Bits = 0x7FFFFFFF
} MLHeadTrackingMapEvent;

/*!
  \brief Creates a Head Tracker.

  \param[out] out_handle A pointer to an MLHandle which will contain the handle of the head tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_Ok Successfully created head tracker.
  \retval MLResult_UnspecifiedFailure Failed to create head tracker due to an unknown error.
  \retval MLResult_PermissionDenied The application lacks permission.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadTrackingCreate(MLHandle *out_handle);

/*!
  \brief Destroys a Head Tracker.

  \param[in] head_tracker A handle to a Head Tracker created by MLHeadTrackingCreate().

  \retval MLResult_Ok Successfully destroyed head tracker.
  \retval MLResult_UnspecifiedFailure Failed to destroy head tracker due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadTrackingDestroy(MLHandle head_tracker);

/*!
  \brief Returns static information about the Head Tracker.

  \param[in] head_tracker A handle to the tracker.
  \param[out] out_data Target to populate the data about that Head Tracker.

  \retval MLResult_InvalidParam Failed to receive static data due to an invalid input parameter.
  \retval MLResult_Ok Successfully received static data.
  \retval MLResult_UnspecifiedFailure Failed to receive static data due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadTrackingGetStaticData(MLHandle head_tracker, MLHeadTrackingStaticData *out_data);

/*!
  \deprecated Deprecated since 1.2.0. Scheduled for removal. Replaced by MLHeadTrackingGetStateEx.
  \brief Returns the most recent head tracking state.

  \param[in] head_tracker A handle to the tracker.
  \param[out] out_state Pointer to valid #MLHeadTrackingState object to be filled with current state information.

  \retval MLResult_InvalidParam Failed to return the most recent head tracking state due to an invalid input parameter.
  \retval MLResult_Ok Successfully returned the most recent head tracking state.
  \retval MLResult_UnspecifiedFailure Failed to return the most recent head tracking state due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Replaced by MLHeadTrackingGetStateEx.")
ML_API MLResult ML_CALL MLHeadTrackingGetState(MLHandle head_tracker, MLHeadTrackingState *out_state);

/*!
  \brief Returns the most recent head tracking state.

  \apilevel 26

  \param[in] head_tracker A handle to the tracker.
  \param[out] out_state Pointer to valid #MLHeadTrackingStateEx object to be filled with current state information.

  \retval MLResult_InvalidParam Failed to return the most recent head tracking state due to an invalid input parameter.
  \retval MLResult_Ok Successfully returned the most recent head tracking state.
  \retval MLResult_UnspecifiedFailure Failed to return the most recent head tracking state due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadTrackingGetStateEx(MLHandle head_tracker, MLHeadTrackingStateEx *out_state);


/*!
  \brief Gets map events.

  A developer must be aware of certain events that can occur under degenerative conditions
  in order to cleanly handle it. The most important event to be aware of is when a map changes.

  In the case that a new map session begins, or recovery fails, all formerly cached transform
  and world reconstruction data (planes, mesh) is invalidated and must be updated.

  \apilevel 2

  \param[in] head_tracker A handle to the tracker.
  \param[out] out_map_events Pointer to a uint64_t representing a bitmask of
              MLHeadTrackingMapEvent, allocated by the caller.

  \retval MLResult_InvalidParam Failed to get map events due to an invalid input parameter.
  \retval MLResult_Ok Successfully got map events.
  \retval MLResult_UnspecifiedFailure Failed to get map events due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadTrackingGetMapEvents(MLHandle head_tracker, uint64_t *out_map_events);

/*! \} */

ML_EXTERN_C_END
