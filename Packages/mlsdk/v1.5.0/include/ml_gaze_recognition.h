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

ML_EXTERN_C_BEGIN

/*!
  \defgroup GazeRecognition Gaze Recognition
  \addtogroup GazeRecognition
  \sharedobject perception.magicleap
  \brief APIs for the Gaze Recognition system.
  \{
*/

/*!
  \brief A set of possible error codes that the Gaze Recognition system can report.

  \apilevel 20
*/
typedef enum MLGazeRecognitionError {
  /*! No error, tracking is nominal. */
  MLGazeRecognitionError_None,
  /*! Gaze Recognition system failed. */
  MLGazeRecognitionError_Generic,
  /*! Ensure enum is represented as 32 bits. */
  MLGazeRecognitionError_Ensure32Bits = 0x7FFFFFFF
} MLGazeRecognitionError;

/*!
  \brief A set of mutually-exclusive behaviors that the Gaze Recognition system can report.

  \apilevel 24
*/
typedef enum MLGazeRecognitionBehavior {
  /*! Unknown. */
  MLGazeRecognition_Unknown = 0,
  /*! Both eyes closed. */
  MLGazeRecognition_EyesClosed = 1,
  /*! Blink detected. Both eyes open, close, and open. */
  MLGazeRecognition_Blink = 2,
  /*! User is fixating, eye position is stable. */
  MLGazeRecognition_Fixation = 3,
  /*! User is pursuing, eye velocity is low but nonzero. */
  MLGazeRecognition_Pursuit = 4,
  /*! User is making a saccade, eye velocity is high. */
  MLGazeRecognition_Saccade = 5,
  /*! Left eye blink, right eye open. */
  MLGazeRecognition_BlinkLeft = 6,
  /*! Right eye blink, left eye open. */
  MLGazeRecognition_BlinkRight = 7,
  MLGazeRecognition_Ensure32Bits = 0x7FFFFFFF
} MLGazeRecognitionBehavior;

/*!
  \brief Static information about the Gaze Recognition system. Populate with MLGazeRecognitionGetStaticData().

  \apilevel 27
*/
typedef struct MLGazeRecognitionStaticData {
  /*! Version of this structure. */
  uint32_t version;
  /*! The maximum value for the height of the eye_left and eye_right vector. */
  float eye_height_max;
    /*! The maximum value for the width of the eye_left and eye_right vector. */
  float eye_width_max;
  /*! Location of the 3D vergence point, intersection of 3D gaze vectors. */
  MLCoordinateFrameUID vergence;
} MLGazeRecognitionStaticData;

/*!
  \brief Initialize MLGazeRecognitionStaticData with version.

  \apilevel 27

  \param[in,out] inout_state Sets up the version for inout_state and nulls pointer for the MLCoordinateFrameUID.

  \permissions None
*/
ML_STATIC_INLINE void MLGazeRecognitionStaticDataInit(MLGazeRecognitionStaticData *inout_state) {
  if (inout_state) {
    inout_state->version = 2u;
  }
}

/*!
  \brief Information about the state of the Gaze Recognition system. This structure must be initialized by calling MLGazeRecognitionStateInit() before use.

  \apilevel 20
*/
typedef struct MLGazeRecognitionState {
  /*! Version of this structure. */
  uint32_t version;
  /*! The timestamp accociated with all data fields in this struct. */
  MLTime timestamp;
  /*! Represents what gaze Recognition error (if any) is present. */
  MLGazeRecognitionError error;
  /*! Represents what known gaze Recognition behavior is present. */
  MLGazeRecognitionBehavior behavior;
  /*! A vector for eye-in-skull position of left eye, even if right eye is closed.*/
  MLVec2f eye_left;
  /*! A vector for eye-in-skull position of right eye, even if left eye is closed. */
  MLVec2f eye_right;
  /*! Metadata field for onset of the current behavior, in seconds. Onset applies to all behaviors and marks the time when the current behavior began.*/
  float onset_s;
  /*! Metadata field for duration of the current behavior, in seconds. Duration applies to all gaze types.*/
  float duration_s;
  /*! Metadata field for velocity of the current movement, in degrees per second. Velocity field applies to saccades and pursuit, otherwise NaN.*/
  float velocity_degps;
  /*! Metadata field for amplitude of the current movement, which is eye-position displacement in degrees of visual angle. Amplitude applies to saccades and pursuit, otherwise NaN.*/
  float amplitude_deg;
  /*! Metadata field for direction of the current movement, in radial degrees (0-360). Direction field applies to saccades and pursuit, otherwise NaN.*/
  float direction_radial;
} MLGazeRecognitionState;

/*!
  \brief Initialize MLGazeRecognitionState with version.

  \apilevel 20

  \param[in,out] inout_state Sets up the version for inout_state and zeros all the fields.

  \permissions None
*/
ML_STATIC_INLINE void MLGazeRecognitionStateInit(MLGazeRecognitionState *inout_state) {
  if (inout_state) {
    inout_state->version = 1u;
    inout_state->timestamp = 0;
    inout_state->error = MLGazeRecognitionError_None;
    inout_state->behavior = MLGazeRecognition_Unknown;
    inout_state->eye_left.x = 0.0f;
    inout_state->eye_left.y = 0.0f;
    inout_state->eye_right.x = 0.0f;
    inout_state->eye_right.y = 0.0f;
    inout_state->onset_s = 0.0f;
    inout_state->duration_s = 0.0f;
    inout_state->velocity_degps = 0.0f;
    inout_state->amplitude_deg = 0.0f;
    inout_state->direction_radial = 0.0f;
  }
}

/*!
  \brief Create Gaze Recognition.

  \apilevel 20

  \param[out] out_handle A pointer to an #MLHandle which will contain a handle to Gaze Recognition.
  If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam The out_handle parameter was not valid (null).
  \retval MLResult_Ok Gaze Recognition was successfully created.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied The application lacks permission.
  \retval MLResult_UnspecifiedFaiure Gaze Recognition was not created successfully.

  \permissions com.magicleap.permission.EYE_TRACKING (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLGazeRecognitionCreate(MLHandle *out_handle);

/*!
  \brief Destroy Gaze Recognition.

  \apilevel 20

  \param[in] handle A handle to Gaze Recognition created by MLGazeRecognitionCreate().

  \retval MLResult_InvalidParam The Gaze Recognition handle was not valid.
  \retval MLResult_Ok The Gaze Recognition was successfully destroyed.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure The Gaze Recognition was not successfully destroyed.

  \permissions None
*/
ML_API MLResult ML_CALL MLGazeRecognitionDestroy(MLHandle handle);

/*!
  \brief Get static information about Gaze Recognition.

  \apilevel 20

  \param[in] handle A handle to Gaze Recognition created by MLGazeRecognitionCreate().
  \param[out] out_data Target to populate the data about Gaze Recognition.

  \retval MLResult_InvalidParam The out_data parameter was not valid (null).
  \retval MLResult_Ok Gaze Recognition static data was successfully received.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to receive Gaze Recognition static data.

  \permissions None
*/
ML_API MLResult ML_CALL MLGazeRecognitionGetStaticData(MLHandle handle,
                                                   MLGazeRecognitionStaticData *out_data);

/*!
  \brief Get information about the user's gaze.

  \apilevel 20

  \param[in] handle A handle to Gaze Recognition created by MLGazeRecognitionCreate().
  \param[out] out_state Information about the gaze.

  \retval MLResult_InvalidParam The out_state parameter was not valid (null).
  \retval MLResult_Ok gaze Recognition state was successfully received.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to receive gaze Recognition state data.

  \permissions None
*/
ML_API MLResult ML_CALL MLGazeRecognitionGetState(MLHandle handle,
                                              MLGazeRecognitionState *out_state);

ML_EXTERN_C_END
