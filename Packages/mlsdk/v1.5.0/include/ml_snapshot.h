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
#include "ml_coordinate_frame_uid.h"
#include "ml_types.h"

#include <string.h>

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Perception
  \sharedobject perception.magicleap
  \{
*/

enum {
  /*! Defines the prefix for MLSnapshotResult codes. */
  MLResultAPIPrefix_Snapshot = MLRESULT_PREFIX(0x87b8)
};

/*! Return values for Snapshot API calls. */
typedef enum MLSnapshotResult {
  /*! Derivatives not calculated for requested coordinate frame. */
  MLSnapshotResult_DerivativesNotCalculated = MLResultAPIPrefix_Snapshot,
  /*! Ensure enum is represented as 32 bits. */
  MLSnapshotResult_Ensure32Bits = 0x7FFFFFFF
} MLSnapshotResult;

/*!
  \brief Velocity and acceleration derivatives for a related transform.

  \apilevel 8

 */
typedef struct MLTransformDerivatives {
  /*! Version of this structure. */
  uint32_t version;
  /*! Linear velocity in meters per second, expressed in destination frame
      coordinates. */
  MLVec3f linear_velocity_m_s;
  /*! Linear acceleration in meters per second squared, expressed in destination
      frame coordinates. */
  MLVec3f linear_acceleration_m_s2;
  /*! Angular velocity in radians per second, expressed in destination frame
      coordinates. */
  MLVec3f angular_velocity_r_s;
  /*! Angular acceleration in radians per second squared, expressed in
      destination frame coordinates. */
  MLVec3f angular_acceleration_r_s2;
} MLTransformDerivatives;

/*!
  \brief Intializes the default values for #MLTransformDerivatives.

  \apilevel 8

  \param[in,out] inout_data The object that will be initialized with default values.
*/
ML_STATIC_INLINE void MLTransformDerivativesInit(MLTransformDerivatives *inout_data) {
  if (inout_data) {
    inout_data->version = 1u;
    inout_data->linear_velocity_m_s.x = 0.f;
    inout_data->linear_velocity_m_s.y = 0.f;
    inout_data->linear_velocity_m_s.z = 0.f;
    inout_data->linear_acceleration_m_s2.x = 0.f;
    inout_data->linear_acceleration_m_s2.y = 0.f;
    inout_data->linear_acceleration_m_s2.z = 0.f;
    inout_data->angular_velocity_r_s.x = 0.f;
    inout_data->angular_velocity_r_s.y = 0.f;
    inout_data->angular_velocity_r_s.z = 0.f;
    inout_data->angular_acceleration_r_s2.x = 0.f;
    inout_data->angular_acceleration_r_s2.y = 0.f;
    inout_data->angular_acceleration_r_s2.z = 0.f;
  }
}

/*!
  \brief Static information about the snapshot system.

  Initalize this structure with MLSnapshotStaticDataInit and populate with MLSnapshotGetStaticData().

  \apilevel 30
*/
typedef struct MLSnapshotStaticData {
  /*! Version of this structure. */
  uint32_t version;
  /*! Coordinate frame ID. */
  MLCoordinateFrameUID coord_world_origin;
} MLSnapshotStaticData;

/*!
  \brief Intializes the default values for #MLSnapshotStaticData.

  \apilevel 30

  \param[in,out] inout_data The object that will be initialized with default values.
*/
ML_STATIC_INLINE void MLSnapshotStaticDataInit(MLSnapshotStaticData *inout_data) {
  if (inout_data) {
    memset(inout_data, 0, sizeof(MLSnapshotStaticData));
    inout_data->version = 1u;
  }
}

/*!
  \brief Get the static data pertaining to the snapshot system.

  \apilevel 30

  \param[out] out_static_data Target to populate the data about snapshot system.

  \retval MLResult_InvalidParam Failed to obtain static data due to invalid parameter.
  \retval MLResult_Ok Obtained static data successfully.
  \retval MLResult_UnspecifiedFailure Failed to obtain static data due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLSnapshotGetStaticData(MLSnapshotStaticData *out_static_data);

/*! Opaque snapshot of system state. */
typedef struct MLSnapshot MLSnapshot;

/*!
  \brief Get transform between world origin and the coordinate frame `id'.

  \param[in] snapshot A snapshot of tracker state. Can be obtained with MLPerceptionGetSnapshot().
  \param[in] id Look up the transform between the current origin and this coordinate frame id.
  \param[out] out_transform Valid pointer to a #MLTransform. To be filled out with requested transform data.

  \retval MLResult_InvalidParam Failed to obtain transform due to invalid parameter.
  \retval MLResult_Ok Obtained transform successfully.
  \retval MLResult_PoseNotFound Coordinate Frame is valid, but not found in the current pose snapshot.
  \retval MLResult_UnspecifiedFailure Failed to obtain transform due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLSnapshotGetTransform(const MLSnapshot *snapshot, const MLCoordinateFrameUID *id, MLTransform *out_transform);

/*!
  \brief Get transform between world origin and the coordinate frame `id' as well as any derivatives
         that have been calculated.

  \apilevel 8

  \param[in] snapshot A snapshot of tracker state. Can be obtained with MLPerceptionGetSnapshot().
  \param[in] id Look up the transform between the current origin and this coordinate frame id.
  \param[out] out_transform Valid pointer to a #MLTransform. To be filled out with requested transform data.
  \param[out] out_derivatives Valid pointer to a #MLTransformDerivatives. To be filled out with the derivatives
              of the transform if available.

  \retval MLResult_InvalidParam Failed to obtain transform due to invalid parameter.
  \retval MLResult_Ok Obtained transform successfully.
  \retval MLResult_PoseNotFound Coordinate Frame is valid, but not found in the current pose snapshot.
  \retval MLResult_UnspecifiedFailure Failed to obtain transform due to internal error.
  \retval MLSnapshotResult_DerivativesNotCalculated Derivatives are not available for the requested coordinate Frame.

  \permissions None
*/
ML_API MLResult ML_CALL MLSnapshotGetTransformWithDerivatives(const MLSnapshot *snapshot, const MLCoordinateFrameUID *id,
                                                              MLTransform *out_transform, MLTransformDerivatives *out_derivatives);

/*!
  \brief Get transform between coordinate frame 'base_id' and the coordinate frame `id' as well as any derivatives
         that have been calculated.

  \code

   // Get the CFUID for World Origin
   MLSnapshotStaticData snapshot_static_data = {};
   MLSnapshotStaticDataInit(&snapshot_static_data);
   MLSnapshotGetStaticData(&snapshot_static_data);

   // Get the CFUID for Headset Origin
   MLHeadTrackingStaticData head_static_data_ = {};
   MLHeadTrackingGetStaticData(head_tracker_, &head_static_data_);

   // Get the CFUID for left eye
   MLEyeTrackingStaticData eye_static_data_ = {};
   MLEyeTrackingGetStaticData(eye_tracker_, &eye_static_data_);

   MLPose left_eye_center = {};
   MLSnapshot *snapshot = nullptr;
   bool gaze_in_device_coordinate_frame = true;
   MLPerceptionGetSnapshot(&snapshot);
   if(gaze_in_device_coordinate_frame) {  // Left eye gaze in device coordinate frame.
     MLSnapshotGetPoseInBase(snapshot, &head_static_data_.coord_frame_head, &eye_static_data_.left_center, &left_eye_center);
   }
   else {  // Left eye gaze in world origin coordinate frame.
     MLSnapshotGetPoseInBase(snapshot, &snapshot_static_data.coord_world_origin, &eye_static_data_.left_center, &left_eye_center);
   }
   MLPerceptionReleaseSnapshot(snapshot);

  \endcode

  \apilevel 30

  \param[in] snapshot A snapshot of tracker state. Can be obtained with MLPerceptionGetSnapshot().
  \param[in] base_id The coordinate frame in which to locate 'id'.
  \param[in] id The coordinate frame which needs to be located in the base_id coordinate frame.
  \param[out] out_pose Valid pointer to a #MLPose. To be filled out with requested pose data.

  \retval MLResult_InvalidParam Failed to obtain transform due to invalid parameter.
  \retval MLResult_Ok Obtained transform successfully.
  \retval MLResult_PoseNotFound Coordinate Frame is valid, but not found in the current pose snapshot.
  \retval MLResult_UnspecifiedFailure Failed to obtain transform due to internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLSnapshotGetPoseInBase(const MLSnapshot *snapshot, const MLCoordinateFrameUID *base_id, const MLCoordinateFrameUID *id, MLPose *out_pose);

/*!
  \brief Returns an ASCII string representation for each result code.

  This call returns strings for all of the global MLResult and
  MLSnapshotResult codes.

  \param[in] result_code MLResult type to be converted to string.

  \return ASCII string containing readable version of the result code.

  \permissions None
*/
ML_API const char* ML_CALL MLSnapshotGetResultString(MLResult result_code);

/*! \} */

ML_EXTERN_C_END
