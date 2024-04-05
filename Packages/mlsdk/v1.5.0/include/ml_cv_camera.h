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

ML_EXTERN_C_BEGIN

/*!
  \defgroup CVCamera CV Camera
  \addtogroup CVCamera
  \sharedobject perception.magicleap
  \brief APIs for camera pose.

  \{
*/

/*!
  \brief Camera id enum.

  \apilevel 5
*/
typedef enum MLCVCameraID {
  /*! Default camera id. */
  MLCVCameraID_ColorCamera = 0,
  /*! Camera id. */
  MLCVCameraID_Ensure32Bits = 0x7FFFFFFF
} MLCVCameraID;

/*!
  \brief Create CV Camera Tracker.

  \apilevel 5

  \param[out] out_handle Tracker handle.

  \retval MLResult_Ok On success.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied Necessary permission is missing.

  \permissions android.permission.CAMERA (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLCVCameraTrackingCreate(MLHandle *out_handle);

/*!
  \brief Get the camera pose in the world coordinate system.

  Use the timestamp provided from the #on_video_buffer_available callback from
  ml_camera_v2.h. The camera tracker only caches a limited set of poses. Retrieve
  the camera pose as soon as the timestamp is available else the API may return
  MLResult_PoseNotFound.

  \apilevel 5

  \param[in]  camera_handle MLHandle previously created with MLCVCameraTrackingCreate.
  \param[in]  head_handle MLHandle previously created with MLHeadTrackingCreate.
  \param[in]  id Camera id.
  \param[in]  camera_timestamp Time to request the pose.
  \param[out] out_transform Transform from camera to world origin.


  \retval MLResult_InvalidParam id parameter was not valid or out_transform parameter
                                was not valid (null).
  \retval MLResult_Ok Obtained transform successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PoseNotFound Pose is currently not available.
  \retval MLResult_UnspecifiedFailure Failed to obtain transform due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLCVCameraGetFramePose(MLHandle camera_handle, MLHandle head_handle, MLCVCameraID id, MLTime camera_timestamp, MLTransform *out_transform);

/*!
  \brief Destroy Tracker after usage.

  \apilevel 5

  \param[in] camera_handle MLHandle previously created with MLCVCameraTrackingCreate.

  \retval MLResult_Ok On success.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.

  \permissions None
*/
ML_API MLResult ML_CALL MLCVCameraTrackingDestroy(MLHandle camera_handle);

/*! \} */

ML_EXTERN_C_END
