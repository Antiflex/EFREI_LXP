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
#include "ml_snapshot.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Perception
  \sharedobject perception.magicleap
  \brief APIs for the Perception system.

  \{
*/

/*! Settings for initializing the perception system. */
typedef struct MLPerceptionSettings {
  uint16_t override_port;
} MLPerceptionSettings;

/*!
  \brief Initializes the perception system with the passed in settings.

  \param[out] out_settings Initializes the perception system with these settings.

  \retval MLResult_InvalidParam Failed to initialize the perception settings due to an invalid input parameter.
  \retval MLResult_Ok Successfully initialized the perception settings.
  \retval MLResult_UnspecifiedFailure Failed to initialize the perception settings due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLPerceptionInitSettings(MLPerceptionSettings *out_settings);

/*!
  \brief Starts the perception system.

  This function should be called before any perception functions are called.

  \param[in] settings The perception system starts with these settings.

  \retval MLResult_Ok Successfully started perception system.
  \retval MLResult_UnspecifiedFailure Failed to start perception system due to an unknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLPerceptionStartup(MLPerceptionSettings *settings);

/*!
  \brief Shuts down the perception system and cleans up all resources used by it.

  This function should be called prior to exiting the program
  if a call to `MLPerceptionStartup()` was called.

  \retval MLResult_Ok Successfully shut down the perception system.
  \retval MLResult_UnspecifiedFailure Failed to shut down the perception system because of an uknown failure.

  \permissions None
*/
ML_API MLResult ML_CALL MLPerceptionShutdown();

/*!
  \brief Pulls in the latest state of all persistent transforms and all
  enabled trackers extrapolated to the next frame time.

  Returns a #MLSnapshot with this latest state. This snap should be
  used for the duration of the frame being constructed and then
  released with a call to `MLPerceptionReleaseSnapshot()`.

  \param[out] out_snapshot Pointer to a pointer containing an #MLSnapshot on success.

  \retval MLResult_Ok Successfully created snapshot.
  \retval MLResult_InvalidParam out_snapshot parameter was not valid (null).
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLPerceptionGetSnapshot(MLSnapshot **out_snapshot);

/*!
  \brief Pulls in the state of all persistent transforms and all
  enabled trackers extrapolated to the provided timestamp.

  This timestamp typically comes from out_frame_info.predicted_display_time out parameter from
  the MLGraphicsBeginFrameEx function.

  Returns a #MLSnapshot with this latest state. This snap should be
  used for the duration of the frame being constructed and then
  released with a call to `MLPerceptionReleaseSnapshot()`.

  \apilevel 27

  \param[in] timestamp Timestamp representing the time for which to predict poses.
  \param[out] out_snapshot Pointer to a pointer containing an #MLSnapshot on success.

  \retval MLResult_Ok Successfully created snapshot.
  \retval MLResult_InvalidTimestamp Timestamp is either more than 100ms in the future or too old for cached state.
  \retval MLResult_InvalidParam Output parameter was not valid (null).
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLPerceptionGetPredictedSnapshot(MLTime timestamp, MLSnapshot **out_snapshot);

/*!
  \brief Releases specified `#MLSnapshot` object.

  This function should be called exactly once for each call to `MLPerceptionGetSnapshot()`.

  \param[in] snap Pointer to a valid snap object.

  \retval MLResult_Ok Successfully released snapshot.
  \retval MLResult_InvalidParam snapshot parameter was not valid (null).
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLPerceptionReleaseSnapshot(MLSnapshot *snap);

/*! \} */

ML_EXTERN_C_END
