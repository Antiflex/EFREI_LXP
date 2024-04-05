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
  \defgroup HeadsetFit Headset Fit
  \addtogroup HeadsetFit
  \sharedobject perception.magicleap
  \brief API to query the status of the Headset fit.

  This API can be used to determine the fit of the headset on the user. The API
  will only look to see if the pupil location corresponding to the neutral
  gaze is centered on the image. What this means is that we can only look for a
  certain type of bad fits. However this covers majority of the bad fit cases.
  \{
*/

/*!
  \brief Represents the different fit status that the system can report.

  If status is neither NotWorn nor Unknown, then headset is being worn.

  \apilevel 20
*/
typedef enum MLHeadsetFitStatus {
  /*! Headset fit status not available for unknown reason. */
  MLHeadsetFitStatus_Unknown = 0,
  /*! Headset not worn. */
  MLHeadsetFitStatus_NotWorn,
  /*! Good fit. */
  MLHeadsetFitStatus_GoodFit,
  /*! Bad fit. */
  MLHeadsetFitStatus_BadFit,
  /*! Ensure enum is represented as 32 bits. */
  MLHeadsetFitStatus_Ensure32Bits = 0x7FFFFFFF
} MLHeadsetFitStatus;

/*!
  \brief Headset fit state.

  \apilevel 20
*/
typedef struct MLHeadsetFitState {
  /*! Version of this structure. */
  uint32_t version;
  /*!  Headset fit status as defined in #MLHeadsetFitStatus. */
  MLHeadsetFitStatus fit_status;
  /*!  The epoch time of the last update in microseconds. */
  int64_t epoch_timestamp_us;
} MLHeadsetFitState;

/*!
  \brief Initialize MLHeadsetFitState.

  \apilevel 20

  \param[in,out] inout_state Set up the version for inout_state and zero all other fields.
*/
ML_STATIC_INLINE void MLHeadsetFitStateInit(MLHeadsetFitState *inout_state) {
  if(inout_state) {
    memset(inout_state, 0, sizeof(MLHeadsetFitState));
    inout_state->version = 1;
  }
}

/*!
  \brief Creates a headset fit client.

  \apilevel 20

  \param[out] out_handle A pointer to an MLHandle to the newly created headset fit client.

  \retval MLResult_InvalidParam Failed to create headset fit client due to an invalid input parameter.
  \retval MLResult_Ok Successfully created headset fit client.
  \retval MLResult_UnspecifiedFailure Failed to create headset fit client due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadsetFitCreateClient(MLHandle *out_handle);

/*!
  \brief Destroys headset fit client.

  \apilevel 20

  \param[in] handle MLHandle to the headset fit client created by #MLHeadsetFitCreateClient.

  \retval MLResult_Ok Successfully destroyed headset fit client.
  \retval MLResult_InvalidParam MLHandle is invalid.
  \retval MLResult_UnspecifiedFailure Failed to destroy headset fit client due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadsetFitDestroyClient(MLHandle handle);

/*!
  \brief Gets information about the user's current headset fit.

  \apilevel 20

  \param[in] handle Handle to the headset fit information created by #MLHeadsetFitCreateClient.
  \param[out] out_state Information about headset fit state.

  \retval MLResult_InvalidParam Failed to receive headset fit state due to an invalid input parameter.
  \retval MLResult_Ok Successfully returned headset fit state.
  \retval MLResult_UnspecifiedFailure Failed to receive headset fit state due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLHeadsetFitGetState(MLHandle handle, MLHeadsetFitState *out_state);

/*! \} */
ML_EXTERN_C_END
