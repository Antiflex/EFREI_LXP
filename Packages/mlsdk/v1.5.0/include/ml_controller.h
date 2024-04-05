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

#include <string.h>

#include "ml_api.h"
#include "ml_coordinate_frame_uid.h"

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Controller
  \sharedobject perception.magicleap
  \brief APIs for the direct access to the Controller system.
  \{
*/

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.

  \brief A set of possible tracking modes for the Controller system.
*/
typedef enum MLControllerMode {
  Deprecated_Mode_0 = 0,
  Deprecated_Mode_1 = 1,
  /*! High quality 6 degrees of freedom tracking (position and orientation). */
  MLControllerMode_Fused6Dof = 2,
  /*! Count of number of modes. */
  MLControllerMode_Count,
  /*! Ensure enum is represented as 32 bits. */
  MLControllerMode_Ensure32Bits = 0x7FFFFFFF
} MLControllerMode;

/*! A structure to configure controller's tracking-modes. */
typedef struct MLControllerConfiguration {
  bool deprecated_mode_0;
  bool deprecated_mode_1;
  /*! High quality 6 degrees of freedom tracking (position and orientation). */
  bool enable_fused6dof;
} MLControllerConfiguration;

enum {
  /*! Maximum number of active Controllers. */
  MLController_MaxActive = 1
};

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.

  \brief Calibration Accuracy levels for controller.
*/
typedef enum MLControllerCalibAccuracy {
  /*! CalAccuracy is Bad. */
  MLControllerCalibAccuracy_Bad = 0,
  /*! CalAccuracy is Low. */
  MLControllerCalibAccuracy_Low = 1,
  /*! CalAccuracy is Medium. */
  MLControllerCalibAccuracy_Medium = 2,
  /*! CalAccuracy is High. */
  MLControllerCalibAccuracy_High = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLControllerCalibAccuracy_Ensure32Bits = 0x7FFFFFFF
} MLControllerCalibAccuracy;

/*!
  \brief Stream mode for controller stream.

  \apilevel 21
*/
typedef enum MLControllerStatus {
  /*! Controller stream is not active. */
  MLControllerStatus_NotActive = 0,
  /*! Controller stream is active (rotation only). */
  MLControllerStatus_Active_Rotation_Only = 1,
  /*! Controller stream is active (both position and rotation). */
  MLControllerStatus_Active = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLControllerStatus_Ensure32Bits = 0x7FFFFFFF
} MLControllerStatus;

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.

  \brief A structure containing information about the tracking-stream of this controller.
*/
typedef ML_DEPRECATED_MSG("Replaced by MLControllerStateEx.") struct MLControllerStream {
  /*! Smooth filtered coordinate frame identifier for this Controller. */
  MLCoordinateFrameUID coord_frame_controller;
  /*! Flag to indicate if tracking-stream is active. */
  bool is_active;
  /*! \brief Mode of the given controller stream.

      Note that the controller mode can switch depending
      on current environmental conditions. In 6dof mode
      both rotation and translation are available. In 3dof
      mode only rotation is available.
  */
  MLControllerMode mode;
} MLControllerStream;

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.

  \brief A structure containing information about the current state of this controller.
*/
typedef ML_DEPRECATED_MSG("Replaced by MLControllerStateEx.") struct MLControllerState {
  /*! ID of this controller. */
  uint8_t controller_id;
  /*! Current controller's tracking streams. */
  struct MLControllerStream stream[MLControllerMode_Count];
  /*! Calibration accuracy for the current controller. */
  MLControllerCalibAccuracy accuracy;
} MLControllerState;

/*!
  \brief A structure containing information about the current state of this controller.

  \apilevel 21
*/
typedef struct MLControllerStateEx {
  /*! ID of this controller. */
  uint8_t controller_id;
  /*! Smooth filtered coordinate frame identifier for this Controller. */
  MLCoordinateFrameUID coord_frame_controller;
  /*! Raw coordinate frame identifier for this Controller. */
  MLCoordinateFrameUID raw_coord_frame_controller;
  /*! Current controller stream status. */
  MLControllerStatus status;
} MLControllerStateEx;

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.

  \brief A structure containing information about the current state of the controller system.
*/
typedef ML_DEPRECATED_MSG("Replaced by MLControllerSystemStateEx.") struct MLControllerSystemState {
  /*! State objects for each connected and active controller. */
  struct MLControllerState controller_state[MLController_MaxActive];
  /*! Calibration accuracy for the lightwear. */
  MLControllerCalibAccuracy lightwear_accuracy;
} MLControllerSystemState;

/*!
  \brief A structure containing information about the current state of the controller system.

  \apilevel 21
*/
typedef struct MLControllerSystemStateEx {
  /*! Version of this structure. */
  uint32_t version;
  /*! State objects for each connected and active controller. */
  MLControllerStateEx controller_state[MLController_MaxActive];
} MLControllerSystemStateEx;

/*!
  \brief Initializes values for MLControllerSystemStateEx.

  \apilevel 21

  \param[in,out] inout_attr The object to initialize.
*/
ML_STATIC_INLINE void MLControllerSystemStateExInit(MLControllerSystemStateEx *inout_attr) {
  if (NULL != inout_attr) {
    memset(inout_attr, 0, sizeof(MLControllerSystemStateEx));
    inout_attr->version = 1u;
  }
}

/*!
  \brief Creates a controller tracker.

  \apilevel 4

  \param[in]  mode A pointer to #MLControllerConfiguration struct which contains the tracking modes to use for this session.
  \param[out] out_handle A pointer to an #MLHandle which will the handle to the controller tracker.
              If this operation fails, out_handle will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam Failed to create a controller tracker due to an invalid input parameter.
  \retval MLResult_Ok Controller Succesfully created a controller tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied Failed to create a controller tracker due to lack of permission.

  \permissions None
*/
ML_API MLResult ML_CALL MLControllerCreateEx(const MLControllerConfiguration *mode, MLHandle *out_handle);

/*!
  \brief Destroys a controller tracker.

  \param[in] tracker MLHandle to the tracker created by MLControllerCreateEx().

  \retval MLResult_Ok Successfully destroyed the controller tracker.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Failed to destroy the controller tracker due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLControllerDestroy(MLHandle tracker);

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.

  \brief Return the most recent controller state.

  \param[in]  handle Handle to the tracker created by MLControllerCreateEx().
  \param[out] out_state Pointer to valid MLControllerSystemState object to be filled with
              current state information.

  \retval MLResult_InvalidParam Failed to get the controller state due to an invalid input parameter.
  \retval MLResult_Ok Successfully filled out_state with current state.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_DEPRECATED_MSG("Replaced by MLControllerGetStateEx.")
ML_API MLResult ML_CALL MLControllerGetState(MLHandle handle, struct MLControllerSystemState *out_state);

/*!
  \brief Return the most recent controller state.

  \apilevel 21

  \param[in]  handle Handle to the tracker created by MLControllerCreateEx().
  \param[out] out_state Pointer to valid MLControllerSystemStateEx object to be filled with
              current state information.

  \retval MLResult_InvalidParam Failed to get the controller state due to an invalid input parameter.
  \retval MLResult_Ok Successfully filled out_state with current state.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLControllerGetStateEx(MLHandle handle, MLControllerSystemStateEx *out_state);

/*! \} */

ML_EXTERN_C_END
