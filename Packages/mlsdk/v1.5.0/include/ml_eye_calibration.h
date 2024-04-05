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
  \defgroup EyeCalibration Eye Calibration
  \addtogroup EyeCalibration
  \sharedobject perception.magicleap
  \brief APIs for querying the eye calibration state.

  \{
*/

/*!
  \brief A set of possible eye calibration codes that the eye calibration system can report.

  Has a calibration occurred. If so, what was the granularity.

  \apilevel 20
*/
typedef enum MLEyeCalibrationStatus {
  /*! No valid calibration was found for eyes. */
  MLEyeCalibrationStatus_None = 0,
  /*! Calibration is of lower accuracy. */
  MLEyeCalibrationStatus_Coarse = 1,
  /*! Calibration is of higher accuracy. */
  MLEyeCalibrationStatus_Fine = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLEyeCalibrationStatus_Ensure32Bits = 0x7FFFFFFF
} MLEyeCalibrationStatus;


/*!
  \brief A struct representing the eye calibration state.

  \apilevel 20
*/
typedef struct MLEyeCalibrationState {
  /*! Version of this structure. */
  uint32_t version;
  /*! MLEyeCalibrationStatus enum defined above. */
  MLEyeCalibrationStatus eye_calibration;
  /*! Epoch timestamp of last calibration in microseconds. */
  int64_t epoch_timestamp_us;
} MLEyeCalibrationState;

/*!
  \brief Initialize MLEyeCalibrationState with version.

  \apilevel 20

  \param[in,out] inout_state Set up the version for inout_state and zero all other fields.
*/
ML_STATIC_INLINE void MLEyeCalibrationStateInit(MLEyeCalibrationState *inout_state) {
  if (inout_state) {
    memset(inout_state, 0, sizeof(MLEyeCalibrationState));
    inout_state->version = 1;
  }
}

/*!
  \brief Creates an eye calibration client.

  \apilevel 20

  \param[out] out_handle A pointer to an MLHandle to the newly created eye calibration client.

  \retval MLResult_InvalidParam Failed to create eye calibration client due to an invalid input parameter.
  \retval MLResult_Ok Successfully created eye calibration client.
  \retval MLResult_UnspecifiedFaiure Failed to create eye calibration client due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCalibrationCreateClient(MLHandle *out_handle);

/*!
  \brief Destroys an eye calibration client.

  \apilevel 20

  \param[in] handle MLHandle to the eye calibration cleint created by #MLEyeCalibrationCreateClient.

  \retval MLResult_InvalidParam MLHandle is invalid.
  \retval MLResult_Ok Successfully destroyed eye calibration client.
  \retval MLResult_UnspecifiedFaiure Failed to destroy eye calibration client due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCalibrationDestroyClient(MLHandle handle);

/*!
  \brief Gets information about the user's current eye calibration.

  \apilevel 20

  \param[in] handle A handle to an Eye calibration client created by #MLEyeCalibrationCreateClient.
  \param[out] out_state A pointer to MLEyeCalibrationState where information about the eye calibration state is to be stored.

  \retval MLResult_InvalidParam Failed to receive eye calibration state due to an invalid input parameter.
  \retval MLResult_Ok Successfully received eye calibration state.
  \retval MLResult_UnspecifiedFailure Failed to receive eye calibration state due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLEyeCalibrationGetState(MLHandle handle, MLEyeCalibrationState *out_state);

ML_EXTERN_C_END
