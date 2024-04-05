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
  \defgroup SpatialAnchor Spatial Anchor
  \ingroup MagicLeapSpaces
  \sharedobject perception.magicleap

  \brief APIs for managing Spatial Anchors.

  Spatial Anchor management is closely tied to the selected mapping mode on the device.
  The modes are mutually exclusive and affect the functionality of these APIs. The
  available mapping modes are:

  * On-Device Mode - A persistent mode in which anchors are persisted locally and will
    be available in multiple sessions when localized to the same space in which they
    were published.

  * AR Cloud Mode - A persistent mode in which anchors are persisted in the cloud
    environment and will be available in multiple sessions to devices that are localized
    to the same space in which they were published.

  \{
*/

enum {
  /*! Defines the prefix for MLSpatialAnchorResult codes. */
  MLResultAPIPrefix_SpatialAnchor = MLRESULT_PREFIX(0x439),

  /*! Maximum size for the name of the space in the #MLSpatialAnchorLocalizationInfo structure. */
  MLSpatialAnchor_MaxSpaceNameLength = 64,
};

/*!
  \brief SpatialAnchor-specific return codes.

  \apilevel 20
*/
typedef enum MLSpatialAnchorResult {
  /*! The maximum number of anchors for the current space has been reached. */
  MLSpatialAnchorResult_MaxAnchorLimitReached = MLResultAPIPrefix_SpatialAnchor,

  /*! The minimum distance between anchors was not met. */
  MLSpatialAnchorResult_MinDistanceThresholdExceeded,

  /*! The space has not been sufficiently mapped to allow this operation. */
  MLSpatialAnchorResult_InsufficientMapping,

  /*! The provided anchor Id was not valid. */
  MLSpatialAnchorResult_InvalidId,

  /*! The provided expiration suggestion was not valid. */
  MLSpatialAnchorResult_InvalidExpirationTimestamp,

  /*! The operation cannot be completed because the device has not yet localized. */
  MLSpatialAnchorResult_NotLocalized,

  /*! There was an error communicating with the server. */
  MLSpatialAnchorResult_ServerError,

  /*! The operation failed because the underlying service is not yet available, retry later. */
  MLSpatialAnchorResult_ServiceUnavailable,

  /*! Ensure enum is represented as 32 bits. */
  MLSpatialAnchorResult_Ensure32Bits = 0x7FFFFFFF
} MLSpatialAnchorResult;

/*!
  \deprecated Deprecated since 1.3.0. Scheduled for removal. Replaced by MLSpaceLocalizationStatus.
  \brief The current localization status.

  \apilevel 20
*/
typedef enum MLSpatialAnchorLocalizationStatus {
  /*! The device is not currently localized. */
  MLSpatialAnchorLocalizationStatus_NotLocalized,

  /*! The device has localized successfully. */
  MLSpatialAnchorLocalizationStatus_Localized,

  /*! A localization attempt is currently in progress. */
  MLSpatialAnchorLocalizationStatus_LocalizationPending,

  /*! Ensure enum is represented as 32 bits. */
  MLSpatialAnchorLocalizationStatus_Ensure32Bits = 0x7FFFFFFF
} MLSpatialAnchorLocalizationStatus;

/*!
  \deprecated Deprecated since 1.3.0. Scheduled for removal.
  \brief Mapping mode.

  \apilevel 20
*/
typedef enum MLSpatialAnchorMappingMode {
  /*! Using on-device mapping. */
  MLSpatialAnchorMappingMode_OnDevice,

  /*! Using cloud-based mapping.*/
  MLSpatialAnchorMappingMode_ARCloud,

  /*! Ensure enum is represented as 32 bits. */
  MLSpatialAnchorMappingMode_Ensure32Bits = 0x7FFFFFFF
} MLSpatialAnchorMappingMode;

/*!
  \brief The quality of the local space around the anchor.

  This can change over time as the user continues to scan the space.

  \apilevel 31
*/
typedef enum MLSpatialAnchorQuality {
  /*! Low quality, this anchor can be expected to move significantly. */
  MLSpatialAnchorQuality_Low,
  /*! Medium quality, this anchor may move slightly. */
  MLSpatialAnchorQuality_Medium,
  /*! High quality, this anchor is stable and suitable for digital content attachment. */
  MLSpatialAnchorQuality_High,
  /*! Ensure enum is represented as 32 bits. */
  MLSpatialAnchorQuality_Ensure32Bits = 0x7FFFFFFF
} MLSpatialAnchorQuality;

/*!
  \deprecated Deprecated since 1.3.0. Scheduled for removal. Replaced by MLSpaceLocalizationResult.
  \brief A structure containing information about the device's localization state.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Replaced by MLSpaceLocalizationResult.") struct MLSpatialAnchorLocalizationInfo {
  /*!
    \brief Version of the structure.
  */
  uint32_t version;

  /*!
    \brief The localization status at the time this structure was returned.
  */
  MLSpatialAnchorLocalizationStatus localization_status;

  /*!
    \brief The current mapping mode.
  */
  MLSpatialAnchorMappingMode mapping_mode;

  /*!
    \brief If localized, this will contain the name of the current space.
  */
  char space_name[MLSpatialAnchor_MaxSpaceNameLength];

  /*!
    \brief If localized, this will contain the unique ID of the current space.
  */
  MLUUID space_id;

  /*!
    \brief If localized, this will contain the identifier of the transform of
    the target space's origin relative to the world origin.
  */
  MLCoordinateFrameUID target_space_origin;
} MLSpatialAnchorLocalizationInfo;

/*!
  \deprecated Deprecated since 1.3.0. Scheduled for removal. Replaced by MLSpaceLocalizationResultInit.
  \brief Initialize default values for #MLSpatialAnchorLocalizationInfo.

  \apilevel 20

  \param[in,out] inout_info The localization info to initialize.

  \permissions None
*/
ML_DEPRECATED_MSG("Replaced by MLSpaceLocalizationResultInit.")
ML_STATIC_INLINE void MLSpatialAnchorLocalizationInfoInit(MLSpatialAnchorLocalizationInfo *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLSpatialAnchorLocalizationInfo));
    inout_info->version = 2;
  }
}

/*!
  \brief A structure representing a user-defined Spatial Anchor.

  \apilevel 31
*/
typedef struct MLSpatialAnchor {
  /*!
    \brief Version of the structure.
  */
  uint32_t version;

  /*!
    \brief The anchor's unique ID.

    This is a unique identifier for a single Spatial Anchor that is generated and managed by the
    Spatial Anchor system. The ID is created when MLSpatialAnchorCreate is called.
  */
  MLUUID id;

  /*!
    \brief The coordinate frame identifier of the Spatial Anchor.

    This should be passed to MLSnapshotGetTransform to get the anchor's transform.

    The anchor's transform is set when the anchor is created but may be updated later by the Spatial Anchor
    system based on factors such as quality of the mapped space and subsequent localizations.
  */
  MLCoordinateFrameUID cfuid;

  /*!
    \brief The suggested expiration timestamp for this anchor represented in seconds since the Unix epoch.

    This is implemented as an expiration timestamp in the future after which the associated anchor should
    be considered no longer valid and may be removed by the Spatial Anchor system.
  */
  uint64_t expiration_timestamp_s;

  /*!
    \brief Indicates whether or not the anchor has been persisted via a call to #MLSpatialAnchorPublish.
  */
  bool is_persisted;

  /*!
    \brief The ID of the space that this anchor belongs to. This is only relevant if is_persisted is true.
  */
  MLUUID space_id;

  /*!
    \brief The quality of the local space that this anchor occupies. This value may change over time.
  */
  MLSpatialAnchorQuality quality;
} MLSpatialAnchor;

/*!
  \brief Initialize default values for a #MLSpatialAnchor structure.

  \apilevel 31

  \param[in,out] inout_anchor The anchor to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLSpatialAnchorInit(MLSpatialAnchor *inout_anchor) {
  if (inout_anchor != NULL) {
    memset(inout_anchor, 0, sizeof(MLSpatialAnchor));
    inout_anchor->version = 2;
  }
}

/*!
  \brief A structure used to populate anchor creation info when creating a new Spatial Anchor.

  \apilevel 20
*/
typedef struct MLSpatialAnchorCreateInfo {
  /*!
    \brief Version of the structure.
  */
  uint32_t version;

  /*!
    \brief The desired transform of the new Spatial Anchor.

    The anchor's transform is set when the anchor is created but may be updated later by the Spatial Anchor
    system based on factors such as quality of the mapped space and subsequent localizations.
  */
  MLTransform transform;

  /*!
    \brief The suggested expiration timestamp for this anchor represented in seconds since the Unix epoch.

    This is implemented as an expiration timestamp in the future after which the associated anchor should
    be considered no longer valid and may be removed by the Spatial Anchor system. If the timestamp is set
    to zero in this struct, the anchor will never expire.
  */
  uint64_t expiration_timestamp_s;
} MLSpatialAnchorCreateInfo;

/*!
  \brief Initialize default values for a #MLSpatialAnchorCreateInfo structure.

  \apilevel 20

  \param[in,out] inout_info The info struct to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLSpatialAnchorCreateInfoInit(MLSpatialAnchorCreateInfo *inout_info) {
  if (inout_info != NULL) {
    memset(inout_info, 0, sizeof(MLSpatialAnchorCreateInfo));
    inout_info->version = 1;
  }
}

/*!
  \brief A collection of filters for Spatial Anchor queries.

  Filters that have been set will be combined via logical conjunction. E.g. results must match the ids filter
  AND fall within the radius constraint when both have been set.

  This struct must be initialized by calling #MLSpatialAnchorQueryFilterInit before use.

  \apilevel 20
*/
typedef struct MLSpatialAnchorQueryFilter {
  /*!
    \brief Version of the structure.
  */
  uint32_t version;

  /*!
    \brief The center point of where a spatial query will originate.
  */
  MLVec3f center;

  /*!
    \brief The radius in meters used for a spatial query, relative to the specified center.

    Only anchors inside this radius will be returned. Set to 0 for unbounded results.
  */
  float radius_m;

  /*!
    \brief A list of Spatial Anchor IDs to query for.
  */
  const MLUUID *ids;

  /*!
    \brief The number of IDs provided.
  */
  uint32_t ids_count;

  /*!
    \brief The upper bound of expected results.

    Set to 0 for unbounded results.
  */
  uint32_t max_results;

  /*!
    \brief Indicate whether the results will be returned sorted by distance from center.

    Sorting results by distance will incur a performance penalty.
  */
  bool sorted;
} MLSpatialAnchorQueryFilter;

/*!
  \brief Initializes the default values for a query filter.

  \apilevel 20

  \param[in,out] inout_query_filter The filter to initialize.

  \permissions None
*/
ML_STATIC_INLINE void MLSpatialAnchorQueryFilterInit(MLSpatialAnchorQueryFilter *inout_query_filter) {
  if (inout_query_filter != NULL) {
    memset(inout_query_filter, 0, sizeof(MLSpatialAnchorQueryFilter));
    inout_query_filter->version = 1;
    inout_query_filter->sorted = true;
    inout_query_filter->max_results = 1;
  }
}

/*!
  \brief Create a Spatial Anchor tracker.

  \apilevel 20

  \param[out] out_handle A pointer to an #MLHandle which will contain a handle for a Spatial Anchor tracker
  if successful, otherwise it will be #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam The out_handle parameter was not valid.
  \retval MLResult_Ok Successfully created the tracker.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure The tracker was not created.

  \permissions com.magicleap.permission.SPATIAL_ANCHOR (protection level: normal)
*/
ML_API MLResult ML_CALL MLSpatialAnchorTrackerCreate(MLHandle *out_handle);

/*!
  \brief Destroy a previously created Spatial Anchor tracker.

  \apilevel 20

  \param[in] handle A handle to a Spatial Anchor tracker created by MLSpatialAnchorCreate().

  \retval MLResult_InvalidParam The handle parameter was not valid.
  \retval MLResult_Ok Successfully destroyed the tracker.
  \retval MLResult_UnspecifiedFailure The tracker was not destroyed.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorTrackerDestroy(MLHandle handle);

/*!
  \brief Create a new local Spatial Anchor at the desired location.

  On success, out_anchor will be returned with a newly generated ID.

  Any unpublished anchor will be lost if the Headpose session is lost. See #MLHeadTrackingGetMapEvents for more details.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] create_info A struct containing the creation info for the new anchor.
  \param[out] out_anchor The created anchor.

  \retval MLResult_InvalidParam One of the parameters was null.
  \retval MLResult_Ok The anchor was successfully created.
  \retval MLSpatialAnchorResult_InsufficientMapping Insufficient mapping.
  \retval MLSpatialAnchorResult_InvalidExpirationTimestamp Invalid expiration timestamp.
  \retval MLSpatialAnchorResult_MaxAnchorLimitReached Maximum anchor limit reached.
  \retval MLSpatialAnchorResult_MinDistanceThresholdExceeded Minimum distance threshold exceeded.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorCreate(MLHandle handle, const MLSpatialAnchorCreateInfo *create_info, MLSpatialAnchor *out_anchor);

/*!
  \brief Publish an existing local Spatial Anchor to the persistent backend.

  Depending on the currently selected mapping mode, this can store the anchor locally or in the cloud.
  This call will fail if the device is not localized to a space.

  Any unpublished anchor will be lost if the Headpose session is lost. See #MLHeadTrackingGetMapEvents for more details.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] anchor_id The Id of the local anchor to publish.

  \retval MLResult_InvalidParam One of the parameters was null.
  \retval MLResult_Ok The anchor was successfully published and persisted.
  \retval MLResult_Unauthenticated Invalid authentication credentials for this operation.
  \retval MLSpatialAnchorResult_NotLocalized Not localized.
  \retval MLSpatialAnchorResult_InvalidId Invalid Id provided.
  \retval MLSpatialAnchorResult_MaxAnchorLimitReached Maximum anchor limit reached.
  \retval MLSpatialAnchorResult_MinDistanceThresholdExceeded Minimum distance threshold exceeded.
  \retval MLSpatialAnchorResult_ServerError Server error occurred.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorPublish(MLHandle handle, MLUUID anchor_id);

/*!
  \brief Delete an existing Spatial Anchor.

  If successful, this will delete the anchor from persistent storage based on the currently selected mapping mode.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] anchor_id The Id of the anchor to delete.

  \retval MLResult_InvalidParam One of the parameters was null.
  \retval MLResult_Ok The anchor was successfully deleted.
  \retval MLResult_Unauthenticated Invalid authentication credentials for this operation.
  \retval MLSpatialAnchorResult_InvalidId Invalid Id provided.
  \retval MLSpatialAnchorResult_ServerError Server error occurred.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorDelete(MLHandle handle, MLUUID anchor_id);

/*!
  \brief Update a Spatial Anchor's properties.

  The only property that can currently be updated is the expiration timestamp.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] anchor The anchor containing the desired updated properties.

  \retval MLResult_InvalidParam One of the parameters was null.
  \retval MLResult_Ok The anchor was successfully updated.
  \retval MLResult_Unauthenticated Invalid authentication credentials for this operation.
  \retval MLSpatialAnchorResult_InvalidId Invalid Id provided.
  \retval MLSpatialAnchorResult_InvalidExpirationTimestamp Invalid expiration timestamp.
  \retval MLSpatialAnchorResult_ServerError Server error occurred.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorUpdate(MLHandle handle, const MLSpatialAnchor *anchor);

/*!
  \brief Create a new query for Spatial Anchors in the current space.

  It is the responsibility of the caller to call #MLSpatialAnchorQueryDestroy with the query handle
  returned from this function after the results are no longer needed.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] query_filter The filter structure for the query.
  \param[out] out_query_handle The handle for this query to be used with MLSpatialAnchorQueryGetResult.
  \param[out] out_results_count The total number of entries found by the query. This can be any number
              between 0 and max_results.

  \retval MLResult_InvalidParam One of the parameters was null.
  \retval MLResult_Ok The query executed successfully.
  \retval MLResult_UnspecifiedFailure Unspecified error occurred.
  \retval MLSpatialAnchorResult_NotLocalized Not localized to a space.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorQueryCreate(MLHandle handle,
                                                   const MLSpatialAnchorQueryFilter *query_filter,
                                                   MLHandle *out_query_handle,
                                                   uint32_t *out_results_count);

/*!
  \brief Destroy a previously created query handle and release its associated resources.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] query_handle Handle to a Spatial Anchor query.

  \retval MLResult_InvalidParam One of the parameters was null.
  \retval MLResult_Ok The handle was successfully destroyed.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorQueryDestroy(MLHandle handle, MLHandle query_handle);

/*!
  \brief Get the result of a previous Spatial Anchor query.

  Putting index bounds on the results allows the caller to only receive a subset of the total number
  of results generated by the query. This is useful as a form of pagination in the case of a large
  number of anchors in the current space. Indexing is zero-based so if there are N results in the query,
  then it is required that 0 <= first_index <= last_index < N.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[in] query_handle Handle to a query obtained from MLSpatialAnchorQuery.
  \param[in] first_index The first index.
  \param[in] last_index The last index.
  \param[out] out_results An array of (last_index - first_index + 1) size to hold the query results.

  \retval MLResult_Ok The query executed successfully.
  \retval MLResult_InvalidParam One of the parameters was incorrect.
  \retval MLResult_UnspecifiedFailure Unspecified failure occurred.
  \retval MLSpatialAnchorResult_NotLocalized Not localized to a space.

  \permissions None
*/
ML_API MLResult ML_CALL MLSpatialAnchorQueryGetResult(MLHandle handle,
                                                      MLHandle query_handle,
                                                      uint32_t first_index,
                                                      uint32_t last_index,
                                                      MLSpatialAnchor* out_results);

/*!
  \brief Returns an ASCII string for MLSpatialAnchorResult and MLResult codes.

  \apilevel 31

  \param[in] result The input MLResult enum from MLSpatialAnchor functions.
  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_API const char *ML_CALL MLSpatialAnchorGetResultString(MLResult result);

/*!
  \deprecated Deprecated since 1.3.0. Scheduled for removal. Replaced by MLSpaceGetLocalizationResult.
  \brief Get the current localization status of the device.

  \apilevel 20

  \param[in] handle Handle to a Spatial Anchor tracker.
  \param[out] out_localization_info The localization info structure to be populated.

  \retval MLResult_Ok The query executed successfully.
  \retval MLResult_InvalidParam One of the parameters was incorrect.
  \retval MLResult_UnspecifiedFailure Unspecified failure occurred.

  \permissions None
*/
ML_DEPRECATED_MSG("Replaced by MLSpaceGetLocalizationResult.")
ML_API MLResult ML_CALL MLSpatialAnchorGetLocalizationInfo(MLHandle handle, MLSpatialAnchorLocalizationInfo* out_localization_info);

/*! \} */
ML_EXTERN_C_END
