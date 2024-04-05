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
#include "ml_media_common.h"
#include "ml_media_data_source.h"
#include "ml_media_error.h"
#include "ml_media_types.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject media_extractor.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaExtractor
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for to extracting elementary track from media container.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*! Sample flag output from #MLMediaExtractorGetSampleFlags. */
typedef enum MLMediaExtractorSampleFlag {
  MLMediaExtractorSampleFlag_Sync         = 1,
  MLMediaExtractorSampleFlag_Encrypted    = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaExtractorSampleFlag_Ensure32Bits = 0x7FFFFFFF
} MLMediaExtractorSampleFlag;

/*! Seek mode used by #MLMediaExtractorSeekTo. */
typedef enum MLMediaExtractorSeekPosition {
  MLMediaExtractorSeekPosition_Previous_Sync,
  MLMediaExtractorSeekPosition_Next_Sync,
  MLMediaExtractorSeekPosition_Closest_Sync,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaExtractorSeekPosition_Ensure32Bits = 0x7FFFFFFF
} MLMediaExtractorSeekPosition;

typedef MLPSSHEntry MLMediaExtractorPSSHEntry;

/*! DRM Scheme initialization data. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaExtractorDRMSchemeInitData {
  /*! Mimetype of the DRM Scheme initialization data. */
  char *mime_type;
  /*! Size of the DRM Scheme initialization data. */
  size_t size;
  /*! DRM Scheme initialization data. */
  uint8_t *data;
} MLMediaExtractorDRMSchemeInitData;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new \ref MLMediaExtractor.

  \param[out] out_handle A handle to the created \ref MLMediaExtractor.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If MediaExtractor handle cannot be allocated.
  \retval MLResult_InvalidParam If out_handle is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorCreate(MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Destroy a \ref MLMediaExtractor.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor object.

  \retval MLResult_InvalidParam If handle is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorDestroy(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set a local file path as the data source.

  The path should be an absolute path and should
  reference a world-readable file.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] path Content path of the file.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSetDataSourceForPath(MLHandle handle, const char *path);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set a URI string as the data source.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] uri C-style string representing the URI complete string.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions android.permission.INTERNET (protection level: normal)
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSetDataSourceForURI(MLHandle handle, const char *uri);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set a URI string as the data source.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] uri C-style string representing the complete URL.
  \param[in] headers Array of char * headers to be sent.
  \param[in] len Number of headers passed-in.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions android.permission.INTERNET (protection level: normal)
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSetDataSourceForURIWithHeaders(MLHandle handle, const char *uri, const char **headers, size_t len);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the data source as the file-descriptor to use.

  It is the caller's responsibility to close the file descriptor.
  It is safe to do so as soon as this call returns.

  \param[in] handle MLHandle to the MediaExtractor.
  \param[in] fd File-descriptor for the file to extract from.
  \param[in] offset Offset in bytes into the file where the data
             to be extracted starts.
  \param[in] length Length in bytes of the data to be extracted.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSetDataSourceForFD(MLHandle handle, int fd, int64_t offset, int64_t length);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the data source as user defined media data source.

  \param[in] handle MLHandle to the MediaExtractor.
  \param[in] media_data_source MLHandle returned by MLMediaDataSourceCreate().

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If media_data_source cannot be found.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSetMediaDataSource(MLHandle handle, MLHandle media_data_source);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Extract DRM initialization data for a given DRM Scheme if it exists.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] drm_uuid UUID of the DRM scheme.
  \param[out] out_drm_init_data DRM initialization data pointer.
              To release the DRM initialization data upon successful return, call
              MLMediaExtractorReleaseDRMInitData().

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetDRMInitData(MLHandle handle, MLUUID drm_uuid, MLMediaExtractorDRMSchemeInitData *out_drm_init_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release DRM initialization data which was previously retrieved.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] drm_init_data DRM initialization data that needs to be released.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorReleaseDRMInitData(MLHandle handle, MLMediaExtractorDRMSchemeInitData *drm_init_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Count the number of tracks found in the data source.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[out] out_track_count Number of tracks found in data source.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetTrackCount(MLHandle handle, uint64_t *out_track_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get the track format at the specified index.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] index Index of the track.
  \param[out] out_track_handle \ref MLMediaFormat handle that represents track format.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetTrackFormat(MLHandle handle, size_t index, MLHandle *out_track_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Select a track for the subsequent operations.

  Subsequent calls to MLMediaExtractorReadSampleData(), MLMediaExtractorGetSampleTrackIndex() and
  getSampleTime() only retrieve information for the subset of
  tracks selected. Selecting the same track multiple times has
  no effect, the track is only selected once.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] index Index of the track.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSelectTrack(MLHandle handle, size_t index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Unselect a track for the subsequent operations.

  Subsequent calls to MLMediaExtractorReadSampleData(), MLMediaExtractorGetSampleTrackIndex() and
  getSampleTime() only retrieve information for the subset of
  tracks selected.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] index Index of the track.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorUnselectTrack(MLHandle handle, size_t index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief All selected tracks seek near the requested time according to the specified mode.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] time_us Seek time.
  \param[in] mode Seek mode defined by MLMediaSeekMode.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorSeekTo(MLHandle handle, int64_t time_us, MLMediaSeekMode mode);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Advance to the next sample.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.

  \retval MLResult_InvalidParam If handle is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_FailedTransaction If Advance operation failed, no more sample data is available (end of stream).

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorAdvance(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieve the current encoded sample and store it in the byte buffer starting at the given offset.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[in] byte_buf Destination byte buffer.
  \param[in] buf_size Size of the destination buffer.
  \param[in] offset Offset within the buffer.
  \param[out] out_data_size Sample size or -1 if no more samples are available.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorReadSampleData(MLHandle handle, uint8_t *byte_buf, size_t buf_size, size_t offset, int64_t *out_data_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return the track index the current sample originates from.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor.
  \param[out] out_track_index Track index or -1 if no more samples are available.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetSampleTrackIndex(MLHandle handle, int64_t *out_track_index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return the current sample's presentation time in microseconds.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[out] out_sample_time Sample time or -1 if no more samples are available.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetSampleTime(MLHandle handle, int64_t *out_sample_time);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return the current sample's flags.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[out] out_sample_flags Sample flag defined by #MLMediaExtractorSampleFlag, or -1 if on failure.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetSampleFlags(MLHandle handle, int *out_sample_flags);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return the current sample's Crypto info if has encrypted sample.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[out] out_info_handle On success it returns handle to Crypto info of the sample.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetSampleCryptoInfo(MLHandle handle, MLHandle *out_info_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release the Crypto Info.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[in, out] inout_info_handle handle to Crypto info that needs to be released.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorReleaseCryptoInfo(MLHandle handle, MLHandle *inout_info_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return an estimate of how much data is presently cached in memoryexpressed in microseconds.

  \param[in] #handle MLHandle to the \ref MLMediaExtractor.
  \param[out] out_cached_duration Cached amount or -1 if that
              information is unavailable or not applicable (no cache).

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetCachedDuration(MLHandle handle, int64_t *out_cached_duration);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Return \c true if we are caching data and the cache has
  reached the end of the data stream (for now, a future
  seek may of course restart the fetching of data).

  This API only returns a meaningful result if getCachedDuration()
  indicates the presence of a cache, i.e. does NOT return -1.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorHasCacheReachedEOS(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get the Number of PSSH info if present.

  The PSSH(Protection System Specific Header)
  contains a UUID representing a DRM scheme along with opaque data blob
  used for creating crypto session, which in turn used to configure codec.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[out] out_index On successful return contains number of PSSH entries.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetPSSHInfoCount(MLHandle handle, size_t *out_index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get the PSSH info if present. The PSSH(Protection System Specific Header)
  contains a UUID representing a DRM scheme along with opaque data blob
  used for creating crypto session, which in turn used to configure codec.

  Upon successful return, if a #MLMediaExtractorPSSHEntry is returned,
  same should be released by calling MLMediaExtractorReleasePSSHInfo().

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[in] index Index of the PSSH info data element being retrieved.
  \param[out] out_pssh_entry Pointer to the PSSH info data element being retrieved.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorGetPSSHInfo(MLHandle handle, size_t index, MLMediaExtractorPSSHEntry *out_pssh_entry);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Clear the PSSH info data.

  Clears the entire cached PSSH info data in the library.

  \param[in] handle #MLHandle to the \ref MLMediaExtractor instance.
  \param[in] pssh_entry Pointer to the PSSH info data element that needs to be released.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaExtractorReleasePSSHInfo(MLHandle handle, MLMediaExtractorPSSHEntry *pssh_entry);

/*! \} */

ML_EXTERN_C_END
