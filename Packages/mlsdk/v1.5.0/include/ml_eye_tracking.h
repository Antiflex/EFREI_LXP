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
  \defgroup EyeTracking Eye Tracking
  \addtogroup EyeTracking
  \sharedobject perception.magicleap
  \brief APIs for the Eye Tracking system.
  \{
*/

/*! A set of possible error codes that the Eye Tracking system can report. */
typedef enum MLEyeTrackingError {
  /*! No error, tracking is nominal. */
  MLEyeTrackingError_None,
  /*! Eye Tracker failed. */
  MLEyeTrackingError_Generic,
  /*! Ensure enum is represented as 32 bits. */
  MLEyeTrackingError_Ensure32Bits = 0x7FFFFFFF
} MLEyeTrackingError;

/*!
  \brief Static information about the eye tracking.

  Populate with MLEyeTrackingGetStaticData().

  \apilevel 20
*/
typedef struct MLEyeTrackingStaticData {
  /*! Location of the 3D vergence point, intersection of 3D gaze vectors. */
  MLCoordinateFrameUID vergence;

  /*!
    Left center.
    The rotation component is the left gaze w.r.t. -Z (RUB)
    Note: Prior to API Level 7 rotation will only return identity.
  */
  MLCoordinateFrameUID left_center;

  /*!
    Right center.
    The rotation component is the right gaze w.r.t. -Z (RUB)
    Note: Prior to API Level 7 rotation will only return identity.
  */
  MLCoordinateFrameUID right_center;
} MLEyeTrackingStaticData;

/*!
  \brief Information about the state of the eye tracking system.

  This structure must be initialized by calling MLEyeTrackingStateInit() before use.

  \apilevel 26
*/
typedef struct MLEyeTrackingStateEx {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief A quality metric confidence value 0.0 - 1.0 to indicate accuracy of vergence.

    Output may be arbitrary if confidence == 0.
  */
  float vergence_confidence;
  /*!
    \brief A quality metric confidence value 0.0 - 1.0 to indicate accuracy of left eye center.

    Output may be arbitrary if confidence == 0.
  */
  float  left_center_confidence;
  /*!
    \brief A quality metric confidence value 0.0 - 1.0 to indicate accuracy of right eye center.

    Output may be arbitrary if confidence == 0.
  */
  float right_center_confidence;
  /*! Returns true if eyes are inside a blink. When not wearing the device, values can be arbitrary. */
  bool left_blink;
  bool right_blink;
  /*! Represents what eye tracking error (if any) is present. */
  MLEyeTrackingError error;
  /*!
    \brief The timestamp for all the data fields in this struct.
  */
  MLTime timestamp;
  /*!
    \brief Openness of the left eye.

    Output is 0.0 - 1.0, with 0.0 being fully closed and 1.0 fully open.
  */
  float left_eye_openness;
  /*!
    \brief Openness of the right eye.

    Output is 0.0 - 1.0, with 0.0 being fully closed and 1.0 fully open.
  */
  float right_eye_openness;
} MLEyeTrackingStateEx;

/*!
  \brief Initialize MLEyeTrackingStateEx with version.

  \apilevel 26

  \param[in,out] inout_state Set up the version for inout_state and zero all other fields.
*/
ML_STATIC_INLINE void MLEyeTrackingStateInit(MLEyeTrackingStateEx *inout_state) {
  if (inout_state) {
    memset(inout_state, 0, sizeof(MLEyeTrackingStateEx));
    inout_state->version = 2;
    inout_state->error = MLEyeTrackingError_None;
  }
}

/*!
  \brief Creates an eye tracker.

  \param[out] out_handle A pointer to an #MLHandle which will contain the handle of the eye tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to create eye tracker due to an invalid input parameter.
  \retval MLResult_Ok Successfully created eye tracker.
  \retval MLResult_UnspecifiedFaiure Failed to create eye tracker due to an unknown failure.
  \retval MLResult_PermissionDenied The application lacks permission.

  \permissions com.magicleap.permission.EYE_TRACKING (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLEyeTrackingCreate(MLHandle *out_handle);

/*!
  \brief Destroys an eye tracker.

  \param[in] eye_tracker A handle to an Eye Tracker created by MLEyeTrackingCreate().

  \retval MLResult_Ok Successfully destroyed eye tracker.
  \retval MLResult_UnspecifiedFaiure Failed to destroy eye tracker due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeTrackingDestroy(MLHandle eye_tracker);

/*!
  \brief Gets static information about the eye tracker.

  \apilevel 20

  \param[in] eye_tracker A handle to an Eye Tracker created by MLEyeTrackingCreate().
  \param[out] out_data Target to populate the data about the eye tracker.

  \retval MLResult_InvalidParam The out_data parameter was not valid (null).
  \retval MLResult_Ok Eye tracking static data was successfully received.
  \retval MLResult_UnspecifiedFailure Failed to receive eye tracking static data.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeTrackingGetStaticData(MLHandle eye_tracker, MLEyeTrackingStaticData *out_data);

/*!
  \brief Gets information about the user's eyes.

  NOTE: To ensure a clean trace of any eye state, it is important to monitor
  the confidence value of that eye to reject frames where confidence is 0 (or
  employ another fallback strategy like propagating the last high confidence value).

  \apilevel 9

  \param[in] eye_tracker A handle to an Eye Tracker created by MLEyeTrackingCreate().
  \param[out] out_state Information about the eyes.

  \retval MLResult_InvalidParam Failed to receive eye tracking state due to an invalid input parameter.
  \retval MLResult_Ok Successfully received eye tracking state.
  \retval MLResult_UnspecifiedFailure Failed to receive eye tracking state due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeTrackingGetStateEx(MLHandle eye_tracker, MLEyeTrackingStateEx *out_state);

/*! \} */

ML_EXTERN_C_END

