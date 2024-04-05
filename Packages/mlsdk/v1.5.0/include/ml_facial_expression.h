// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2023 Magic Leap, Inc. All Rights Reserved.
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
  \addtogroup FacialExpression Facial Expression
  \sharedobject perception.magicleap

  \brief APIs for facial expression.

  Avatar animation is the primary purpose for the API.
  Currently the API will produce symmetrical eye expression data (e.g. blinks).
  In the subsequent OS releases asymmetrical eye expressions like winks will be supported.

  \{
*/

enum {
  /*! Defines the prefix for MLFacialExpressionResult codes. */
  MLResultAPIPrefix_FacialExpression = MLRESULT_PREFIX(0x18cd),
};
/*!
  \brief Facial expression specific return codes.

  \apilevel 29
*/
typedef enum MLFacialExpressionResult {
  /*! Unable to detect the eyes, check MLHeadsetFitStatus. */
  MLFacialExpressionResult_HeadsetFitIssue = MLResultAPIPrefix_FacialExpression,
  /*! Operation failed because enable_eye_expression in #MLFacialExpressionSettings is disabled. */
  MLFacialExpressionResult_EyeExpressionDisabled,
  /*! Ensure enum is represented as 32 bits. */
  MLFacialExpressionResult_Ensure32Bits = 0x7FFFFFFF
} MLFacialExpressionResult;

/*!
  \brief Available facial expressions.

  \apilevel 29
*/
typedef enum MLFacialExpressionEyeExpressionType {
  /*! Blinking the left eye. */
  MLFacialExpressionEyeExpressionType_Blink_Left = 0,
  /*! Blinking the right eye. */
  MLFacialExpressionEyeExpressionType_Blink_Right = 1,
  /*! Lower Lid upward movement of the left eye. */
  MLFacialExpressionEyeExpressionType_Lid_Tightener_Left = 2,
  /*! Lower Lid upward movement of the right eye. */
  MLFacialExpressionEyeExpressionType_Lid_Tightener_Right = 3,
  /*! Upper lid upward movement of the left eye. */
  MLFacialExpressionEyeExpressionType_Eye_Openness_Left = 4,
  /*! Upper lid upward movement of the right eye. */
  MLFacialExpressionEyeExpressionType_Eye_Openness_Right = 5,
  /*! Upward cheek movement, left. */
  MLFacialExpressionEyeExpressionType_Cheek_Raiser_Left = 6,
  /*! Upward cheek movement, right. */
  MLFacialExpressionEyeExpressionType_Cheek_Raiser_Right = 7,
  /*! Downward brow movement, left. */
  MLFacialExpressionEyeExpressionType_Brow_Lowerer_Left = 8,
  /*! Downward brow movement, right. */
  MLFacialExpressionEyeExpressionType_Brow_Lowerer_Right = 9,
  /*! Upward brow movement, left side. */
  MLFacialExpressionEyeExpressionType_Brow_Raiser_Left = 10,
  /*! Upward brow movement, right side. */
  MLFacialExpressionEyeExpressionType_Brow_Raiser_Right = 11,
  /*! Number of eye expression types. */
  MLFacialExpressionEyeExpressionType_Count = 12,
  /*! Ensure enum is represented as 32 bits. */
  MLFacialExpressionEyeExpressionType_Ensure32Bits = 0x7FFFFFFF
} MLFacialExpressionEyeExpressionType;

/*!
  \brief A structure containing information about facial expressions.
  This structure must be initialized by calling #MLFacialExpressionEyeDataInit before use.

  \apilevel 29
*/
typedef struct MLFacialExpressionEyeData {
  /*! Version of the structure. */
  uint32_t version;
  /*! The #MLTime timestamp when expression data was updated. */
  MLTime timestamp;
  /*!
    \brief Eye expression weights.
     The values are between 0 and 1 and ordered such that the array should
     be indexed using #MLFacialExpressionEyeExpressionType.
  */
  float eye_expression_weights[MLFacialExpressionEyeExpressionType_Count];
} MLFacialExpressionEyeData;

/*!
  \brief Initializes default values for #MLFacialExpressionEyeData.

  \apilevel 29

  \param[in,out] inout_eye_data The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLFacialExpressionEyeDataInit(MLFacialExpressionEyeData *inout_eye_data) {
  if (inout_eye_data) {
    memset(inout_eye_data, 0, sizeof(MLFacialExpressionEyeData));
    inout_eye_data->version = 1u;
  }
}

/*!
  \brief A structure containing settings for the facial expressions.
  This structure must be initialized by calling #MLFacialExpressionSettingsInit before use.

  \apilevel 29
*/
typedef struct MLFacialExpressionSettings {
  /*! Version of this settings. */
  uint32_t version;
  /*!
    \brief Enable #MLFacialExpressionEyeData.

    If true, facial expressions will detect #MLFacialExpressionEyeData and the
    same can queried using #MLFacialExpressionGetEyeData.

    This should be disabled when app does not need facial expression data. Internal
    state of the system will be maintained.
  */
  bool enable_eye_expression;
} MLFacialExpressionSettings;

/*!
  \brief Initializes default values for #MLFacialExpressionSettings.

  \apilevel 29

  \param[in,out] inout_settings The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLFacialExpressionSettingsInit(MLFacialExpressionSettings *inout_settings) {
  if (inout_settings) {
    memset(inout_settings, 0, sizeof(MLFacialExpressionSettings));
    inout_settings->version = 1u;
    inout_settings->enable_eye_expression = true;
  }
}

/*!
  \brief Returns an ASCII string for MLFacialExpressionResult and MLResult codes.

  \apilevel 29

  \param[in] result The input MLResult enum from MLFacialExpression functions.

  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_API const char *ML_CALL MLFacialExpressionGetResultString(MLResult result);

/*!
  \brief Creates a Facial expression client handle.

  Although multiple client handles can be created they all represent the same
  facial expressions backend system.

  \apilevel 29

  \param[in] settings Settings that configures the facial expressions system.
  \param[out] out_handle The handle to be created.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Facial expression client was created successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions com.magicleap.permission.FACIAL_EXPRESSION (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLFacialExpressionCreateClient(const MLFacialExpressionSettings *settings, MLHandle *out_handle);

/*!
  \brief Update the Facial expression system with new settings.

  \apilevel 29

  \param[in] handle Facial expression client handle created by #MLFacialExpressionCreateClient.
  \param[in] settings New Facial expression settings.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Facial expression settings was updated successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions None
*/
ML_API MLResult ML_CALL MLFacialExpressionUpdateSettings(MLHandle handle, const MLFacialExpressionSettings *settings);

/*!
  \brief Get facial expressions data.

  \apilevel 29

  \param[in] handle Facial expression client handle created by #MLFacialExpressionCreateClient.
  \param[out] out_eye_data Eye expressions data.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Facial expression data was retrieved successfully.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.
  \retval MLFacialExpressionResult_HeadsetFitIssue Operation failed because
          unable to detect the eyes, check #MLHeadsetFitStatus.

  \permissions None
*/
ML_API MLResult ML_CALL MLFacialExpressionGetEyeData(MLHandle handle, MLFacialExpressionEyeData *out_eye_data);

/*!
  \brief Destroy client handle and free client resources.

  \apilevel 29

  \param[in] handle Facial expression client handle created by #MLFacialExpressionCreateClient.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Client handle was successfully destroyed.
  \retval MLResult_PerceptionSystemNotStarted Perception System has not been started.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions None
*/
ML_API MLResult ML_CALL MLFacialExpressionDestroyClient(MLHandle handle);

/*! \} */
ML_EXTERN_C_END
