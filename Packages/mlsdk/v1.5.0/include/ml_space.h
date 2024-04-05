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
  \defgroup MagicLeapSpaces Magic Leap Spaces
  \defgroup Space Space
  \ingroup MagicLeapSpaces
  \sharedobject space.magicleap

  \brief APIs for Magic Leap Space.

  Magic Leap Space is a container that holds metadata about your scanned
  environment. It is a digital copy of a physical place and could include spatial
  anchors, environment meshes, environment objects, etc. Spaces can be created
  on device or in the Magic Leap AR Cloud. Spaces created in the AR Cloud can be
  easily shared between other devices.

  ==> APIs for localization requests:

  Magic Leap Space API allows an application to query the list of Spaces available
  to the application and determine the Space that the device should localize into.
  Applications needs to create a Space Manager to list the spaces and trigger
  localization. Application can create only one manager instance and the API
  is not thread safe.

  ==> APIs for importing and exporting Spaces:

  Magic Leap Space API supports exporting and importing on device Spaces.
  Applications cannot export AR Cloud spaces. There is no need to create a
  Magic Leap Space manager to import/export spaces but the application will need
  additional permissions to import/export spaces. See the API for more details.

  The format of the exported Space data can change with OS version updates.
  Backwards compatibility: Space exported using OS version n should work on
  OS versions up to and including OS version n-4.
  Forwards compatibility: Space exported using OS version n is not guaranteed
  to work on OS versions > n.

  Developers are strongly encouraged to encrypt the exported Magic Leap Spaces.

  \{
*/

enum {
  /*! Defines the prefix for MLSpaceResult codes. */
  MLResultAPIPrefix_Space = MLRESULT_PREFIX(0x10cc),
  /*! Maximum size for the name of a Magic Leap Space. */
  MLSpace_MaxSpaceNameLength = 64,
};

/*!
  \brief Magic Leap Space specific return codes.

  \apilevel 26
*/
typedef enum MLSpaceResult {
  /*! There was an error communicating with the server. */
  MLSpaceResult_ServerError = MLResultAPIPrefix_Space,
  /*! The operation failed because the underlying service is not yet available, retry later.*/
  MLSpaceResult_ServiceUnavailable,
  /*!
    \brief Space is not available.
    This can happen when the selected space is in AR Cloud but the device is
    configured for On Device spaces or vice-versa.
  */
  MLSpaceResult_UnavailableSpace,
  /*!
    \brief Space is not compatible with the current OS version.
    This can happen when a space exported from an older version of the OS is
    imported to a device running a newer version of the OS. Refer to the
    documentation at the top of this header for more notes on Space compatibility.
  */
  MLSpaceResult_IncompatibleSpace,
  /*! The operation failed because the Space being imported already exists in the device.*/
  MLSpaceResult_SpaceAlreadyExists,
  /*! Ensure enum is represented as 32 bits. */
  MLSpaceResult_Ensure32Bits = 0x7FFFFFFF
} MLSpaceResult;

/*!
  \brief Space type.
  Indicates the type of the Space.

  \apilevel 26
*/
typedef enum MLSpaceType {
  /*! On device space. */
  MLSpaceType_OnDevice = 0,
  /*! AR Cloud based space.*/
  MLSpaceType_ARCloud = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLSpaceType_Ensure32Bits = 0x7FFFFFFF
} MLSpaceType;

/*!
  \brief The current localization status.

  \apilevel 26
*/
typedef enum MLSpaceLocalizationStatus {
  /*! The device is currently not localized. */
  MLSpaceLocalizationStatus_NotLocalized = 0,
  /*! The device has localized successfully. */
  MLSpaceLocalizationStatus_Localized = 1,
  /*! Localization attempt is currently in progress. */
  MLSpaceLocalizationStatus_LocalizationPending = 2,
  /*! The device will attempt to localize after sleep duration is complete. */
  MLSpaceLocalizationStatus_SleepingBeforeRetry = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLSpaceLocalizationStatus_Ensure32Bits = 0x7FFFFFFF
} MLSpaceLocalizationStatus;

/*!
  \brief The confidence of the current localization.

  \apilevel 31
*/
typedef enum MLSpaceLocalizationConfidence {
  /*! Localization confidence is very poor and should be reattempted. */
  MLSpaceLocalizationConfidence_Poor = 0,
  /*! The confidence is low, current environmental conditions may adversely affect localization. */
  MLSpaceLocalizationConfidence_Fair = 1,
  /*! The confidence is high, persistent content should be stable. */
  MLSpaceLocalizationConfidence_Good = 2,
  /*! This is a very high-confidence localization, persistent content will be very stable. */
  MLSpaceLocalizationConfidence_Excellent = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLSpaceLocalizationConfidence_Ensure32Bits = 0x7FFFFFFF
} MLSpaceLocalizationConfidence;

/*!
  \brief A set of possible reasons that a localization attempt may be unsuccessful.

  \apilevel 31
*/
typedef enum MLSpaceLocalizationErrorFlag {
  /*! No error, localization was successful. */
  MLSpaceLocalizationErrorFlag_None = 0,
  /*! Localization failed for an unknown reason. */
  MLSpaceLocalizationErrorFlag_Unknown = 1 << 0,
  /*! Localization failed becuase the user is outside of the mapped area. */
  MLSpaceLocalizationErrorFlag_OutOfMappedArea = 1 << 1,
  /*! There are not enough features in the environment to successfully localize. */
  MLSpaceLocalizationErrorFlag_LowFeatureCount = 1 << 2,
  /*! Localization failed due to excessive motion. */
  MLSpaceLocalizationErrorFlag_ExcessiveMotion = 1 << 3,
  /*! Localization failed because the lighting levels are too low in the environment. */
  MLSpaceLocalizationErrorFlag_LowLight = 1 << 4,
  /*! A headpose failure caused localization to be unsuccessful. */
  MLSpaceLocalizationErrorFlag_HeadposeFailure = 1 << 5,
  /*! There was an internal algorithm failure that prevented localization. */
  MLSpaceLocalizationErrorFlag_AlgorithmFailure = 1 << 6,
  /*! Ensure enum is represented as 32 bits. */
  MLSpaceLocalizationErrorFlag_Ensure32Bits = 0x7FFFFFFF
} MLSpaceLocalizationErrorFlag;

/*!
  \brief A structure containing settings for the space manager.
  This structure must be initialized by calling #MLSpaceManagerSettingsInit before use.

  \apilevel 26
*/
typedef struct MLSpaceManagerSettings {
  /*! Version of this settings. */
  uint32_t version;
} MLSpaceManagerSettings;

/*!
  \brief Initializes default values for MLSpaceManagerSettings.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceManagerSettingsInit(MLSpaceManagerSettings *inout_info) {
  if (inout_info) {
    memset(inout_info, 0, sizeof(MLSpaceManagerSettings));
    inout_info->version = 1u;
  }
}

/*!
  \brief A structure containing information about a Magic Leap Space.
  This structure must be initialized by calling #MLSpaceInit before use.

  \apilevel 26
*/
typedef struct MLSpace {
  /*! Version of the structure. */
  uint32_t version;
  /*! Name of the Space. */
  char space_name[MLSpace_MaxSpaceNameLength];
  /*! Unique ID of the Space. */
  MLUUID space_id;
  /*! Type of the Space. */
  MLSpaceType space_type;
} MLSpace;

/*!
  \brief Initializes default values for MLSpace.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceInit(MLSpace *inout_info) {
  if (inout_info) {
    memset(inout_info, 0, sizeof(MLSpace));
    inout_info->version = 1u;
  }
}


/*!
  \brief A structure containing list of #MLSpace.
  This structure must be initialized by calling #MLSpaceListInit before use.

  \apilevel 26
*/
typedef struct MLSpaceList {
  /*! Version of the structure. */
  uint32_t version;
  /*! Number of Magic Leap Spaces. */
  uint32_t space_count;
  /*! List of Magic Leap Spaces. */
  MLSpace *spaces;
} MLSpaceList;

/*!
  \brief Initializes default values for MLSpaceList.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceListInit(MLSpaceList *inout_info) {
  if (inout_info) {
    memset(inout_info, 0, sizeof(MLSpaceList));
    inout_info->version = 1u;
  }
}

/*!
  \brief A collection of filters for Magic Leap Spaces.
  This structure must be initialized by calling #MLSpaceQueryFilterInit before use.
  There is no support for filters at this time.

  \apilevel 26
*/
typedef struct MLSpaceQueryFilter {
  /*! Version of the structure. */
  uint32_t version;
} MLSpaceQueryFilter;

/*!
  \brief Initializes the default values for a query filter.

  \apilevel 26

  \param[in,out] inout_query_filter The filter to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceQueryFilterInit(MLSpaceQueryFilter *inout_query_filter) {
  if (inout_query_filter != NULL) {
    memset(inout_query_filter, 0, sizeof(MLSpaceQueryFilter));
    inout_query_filter->version = 1;
  }
}

/*!
  \brief A collection of parameters to be used for localization request.
  This structure must be initialized by calling #MLSpaceLocalizationInfoInit before use.

  \apilevel 26
*/
typedef struct MLSpaceLocalizationInfo {
  /*! Version of the structure. */
  uint32_t version;
  /*! #MLUUID of the Space into which the device attempts to localize into. */
  MLUUID space_id;
} MLSpaceLocalizationInfo ;

/*!
  \brief Initializes the default values for localization info.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceLocalizationInfoInit(MLSpaceLocalizationInfo *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLSpaceLocalizationInfo));
    inout_info->version = 1;
  }
}

/*!
  \brief A structure containing information about the device's localization state.
  This structure must be initialized by calling #MLSpaceLocalizationResultInit before use.

  \apilevel 31
*/
typedef struct MLSpaceLocalizationResult {
  /*! Version of the structure. */
  uint32_t version;
  /*! The localization status at the time this structure was returned. */
  MLSpaceLocalizationStatus localization_status;
  /*!
    \brief Space information.
    If localized (#MLSpaceLocalizationStatus_Localized) this will contain valid Space information.
    If not localized this field should be ignored.
  */
  MLSpace space;
  /*!
    \brief Target space's origin relative to world origin.
    If localized this will contain the identifier of the transform of
    the target space's origin relative to the world origin.
    If not localized this will be null.
  */
  MLCoordinateFrameUID target_space_origin;
  /*! The confidence level of this localization result. */
  MLSpaceLocalizationConfidence localization_confidence;
  /*! Represents a bitmask of #MLSpaceLocalizationErrorFlag. */
  uint32_t error;
} MLSpaceLocalizationResult;

/*!
  \brief Initialize default values for #MLSpaceLocalizationResult.

  \apilevel 31

  \param[in,out] inout_info The localization result to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceLocalizationResultInit(MLSpaceLocalizationResult *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLSpaceLocalizationResult));
    inout_info->version = 3;
  }
}

/*!
  \brief A structure containing callbacks for events related to the Space.

  This structure must be initialized by calling #MLSpaceCallbacksInit before use.
  Application can unregister (stop receiving callbacks) at any time by setting
  the corresponding callback to NULL.

  \apilevel 26
*/
typedef struct MLSpaceCallbacks {
  /*! Version of the structure. */
  uint32_t version;
  /*!
    \brief This callback will be invoked whenever there is an update to the localization status.

    Localization events can occur when the application requests for localization
    via #MLSpaceRequestLocalization or due to other events outside the control of
    the app such as head tracking failure, localization loss.

    \param[in] localization_result Information about the localization status.
    \param[in] user_data Pointer to user context data as set by #MLSpaceSetCallbacks (can be NULL).
  */
  void (*on_localization_changed)(const MLSpaceLocalizationResult *localization_result, void *user_data);
 } MLSpaceCallbacks;

/*!
  \brief Initialize defaults for #MLSpaceCallbacks.

  \apilevel 26

  \param[in,out] inout_callbacks The callback structure to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceCallbacksInit(MLSpaceCallbacks *inout_callbacks) {
  if (inout_callbacks != NULL) {
    inout_callbacks->version = 1;
    inout_callbacks->on_localization_changed = NULL;
  }
}

/*!
  \brief A structure containing information needed to import Magic Leap Space.
  This structure must be initialized by calling #MLSpaceImportInfoInit before use.

  \apilevel 26
*/
typedef struct MLSpaceImportInfo {
  /*! Version of the structure. */
  uint32_t version;
  /*! Binary data size in bytes. */
  uint64_t size;
  /*! Binary data obtained from #MLSpaceExportSpace. */
  const char* data;
} MLSpaceImportInfo;

/*!
  \brief Initialize default values for #MLSpaceImportInfo.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceImportInfoInit(MLSpaceImportInfo *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLSpaceImportInfo));
    inout_info->version = 1;
  }
}

/*!
  \brief A structure containing information about the imported Space.

  \apilevel 26
*/
typedef struct MLSpaceImportOutData {
  /*! Unique ID of the imported Space. */
  MLUUID space_id;
} MLSpaceImportOutData;



/*!
  \brief A structure containing information about the Space export settings.
  This structure must be initialized by calling #MLSpaceExportInfoInit before use.

  \apilevel 26
*/
typedef struct MLSpaceExportInfo {
  /*! Version of the structure. */
  uint32_t version;
  /*! #MLUUID of the Space that needs to be exported. */
  MLUUID space_id;
} MLSpaceExportInfo;

/*!
  \brief Initialize default values for #MLSpaceExportInfo.

  \apilevel 26

  \param[in,out] inout_info The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLSpaceExportInfoInit(MLSpaceExportInfo *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLSpaceExportInfo));
    inout_info->version = 1;
  }
}

/*!
  \brief A structure containing information about the exported Space.

  \apilevel 26
*/
typedef struct MLSpaceExportOutData {
  /*! Binary data size in bytes. */
  uint64_t size;
  /*!
    \brief Space data.
    This is binary data and typically does not include a terminating null
    character.
   */
  const char* data;
} MLSpaceExportOutData;


/*!
  \brief Returns an ASCII string for MLSpaceResult and MLResult codes.

  \apilevel 26

  \param[in] result The input MLResult enum from MLSpace functions.
  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_API const char *ML_CALL MLSpaceGetResultString(MLResult result);



/*!
  \brief Creates a Magic Leap Space manager handle.

  Application can create only one Magic Leap Space manager handle. Multiple
  calls to create a manager handle will result in a failure. The handle is
  valid for the lifecycle of the application.

  \apilevel 26

  \param[in] settings Settings that configures the space manager.
  \param[out] out_handle The handle to be created.

  \retval MLResult_ClientLimitExceeded Failed due to an existing manager.
  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Space manager handle was successfully created.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions com.magicleap.permission.SPACE_MANAGER (protection level: normal)
*/
ML_API MLResult ML_CALL MLSpaceManagerCreate(const MLSpaceManagerSettings* settings, MLHandle* out_handle);

/*!
  \brief Set the callbacks for events related to the Magic Leap Space.

  \apilevel 26

  \param[in] handle Space manager handle created by #MLSpaceManagerCreate.
  \param[in] callbacks Pointer to the #MLSpaceCallbacks structure containing the callbacks.
  \param[in] user_data Pointer that will be returned in the callback.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok The callbacks were registered successfully.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.
*/
ML_API MLResult ML_CALL MLSpaceSetCallbacks(MLHandle handle, const MLSpaceCallbacks *callbacks, void* user_data);

/*!
  \brief Get the list of available spaces.

  The list of spaces returned will depend on the current device mapping mode.
  Only the Spaces associated with the current mapping mode will be returned by
  this call. Device mapping mode can be changed via the system application(s).

  The list memory is owned by the library, call #MLSpaceReleaseSpaceList to
  release the memory. Each get #MLSpaceGetSpaceList should have a corresponding
  #MLSpaceReleaseSpaceList.

  \apilevel 26

  \param[in] handle Space manager handle created by #MLSpaceManagerCreate.
  \param[in] query_filter The filter structure for the query.
  \param[out] out_space_list List of Spaces currently available to the device.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok List of spaces retrieved successfully.
  \retval MLResult_Unauthenticated Invalid authentication credentials for this operation.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.
  \retval MLSpaceResult_ServerError Operation failed due to server side error.
  \retval MLSpaceResult_ServiceUnavailable Operation failed because service is not ready.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpaceGetSpaceList(MLHandle handle, const MLSpaceQueryFilter* query_filter, MLSpaceList* out_space_list);

/*!
  \brief Release the list of available spaces.

  \apilevel 26

  \param[in] handle Space manager handle created by #MLSpaceManagerCreate.
  \param[in] space_list List Magic Leap Spaces that needs to be released.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok List resources was successfully released.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpaceReleaseSpaceList(MLHandle handle, MLSpaceList* space_list);

/*!
  \brief Send a request to localize to a given Magic Leap Space.

  This is an asynchronous request. Use #MLSpaceGetLocalizationResult to get
  the results of the localization or use #MLSpaceCallbacks to listen to
  on_localization_changed events.


  A new request for localization will override all the past requests for
  localization that are yet to be completed.

  \apilevel 26

  \param[in] handle Space manager handle created by #MLSpaceManagerCreate.
  \param[in] localization_info  Magic Leap Space to localize into.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Localization request was submitted successfully.
  \retval MLResult_Unauthenticated Invalid authentication credentials for this operation.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.
  \retval MLSpaceResult_UnavailableSpace Operation failed due an unavailable Space.
  \retval MLSpaceResult_ServerError Operation failed due to server side error.
  \retval MLSpaceResult_ServiceUnavailable Operation failed because service is not ready.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpaceRequestLocalization(MLHandle handle, const MLSpaceLocalizationInfo* localization_info);

/*!
  \brief Get the localization results.

  Returns the results of the most recent localization request.

  \apilevel 26

  \param[in] handle Space manager handle created by #MLSpaceManagerCreate.
  \param[out] out_localization_result Contains the result of the localization request.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Localization result was retrieved successfully.
  \retval MLResult_Unauthenticated Invalid authentication credentials for this operation.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpaceGetLocalizationResult(MLHandle handle, MLSpaceLocalizationResult* out_localization_result);

/*!
  \brief Destroys a Space manager handle.

  \apilevel 26

  \param[in] handle The handle to be destroyed.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok Space manager handle was successfully destroyed.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpaceManagerDestroy(MLHandle handle);

/*!
  \brief Import a Magic Leap Space.

  The #MLSpaceImportInfo memory is owned by the app and the app should make sure
  to release the memory once the API call has returned.

  \apilevel 26

  \param[in] import_info Information need to import the space.
  \param[out] out_data Information about the imported space.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.
  \retval MLSpaceResult_IncompatibleSpace Operation failed due an incompatible Space.
  \retval MLSpaceResult_SpaceAlreadyExists Operation failed because Space being imported already exists.

  \permissions com.magicleap.permission.SPACE_IMPORT_EXPORT (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLSpaceImportSpace(const MLSpaceImportInfo* import_info, MLSpaceImportOutData* out_data);


/*!
  \brief Export an on device Magic Leap Space.

  The #MLSpaceExportOutData is owned by the library, call #MLSpaceReleaseExportData
  to release the memory. Each #MLSpaceExportSpace call should have a corresponding
  #MLSpaceReleaseExportData.

  \apilevel 26

  \param[in] export_info Information needed to export the space.
  \param[out] out_data Exported space data.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.
  \retval MLSpaceResult_UnavailableSpace Operation failed due an unavailable Space.

  \permissions com.magicleap.permission.SPACE_IMPORT_EXPORT (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLSpaceExportSpace(const MLSpaceExportInfo* export_info, MLSpaceExportOutData* out_data);

/*!
  \brief Release resources acquired in #MLSpaceExportSpace.

  \apilevel 26

  \param[in] space_data MLSpaceExportOutData that needs to be released.

  \retval MLResult_InvalidParam One or more input parameters are not valid.
  \retval MLResult_Ok List resources was successfully released.
  \retval MLResult_UnspecifiedFailure Operation failed for unknown reason.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpaceReleaseExportData(MLSpaceExportOutData* space_data);

/*! \} */
ML_EXTERN_C_END
