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

ML_EXTERN_C_BEGIN

/*!
  \defgroup MediaError Media Error
  \addtogroup MediaError
  \sharedobject media_error.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaPlayer.OnErrorListener
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \{
*/

enum {
  /*! Defines the prefix for MLMediaGenericResult codes. */
  MLResultAPIPrefix_MediaGeneric = MLRESULT_PREFIX(0xbf3b)
};

/*! Generic return values for Multimedia API calls. */
typedef enum MLMediaGenericResult {
  MLMediaGenericResult_InvalidOperation = MLResultAPIPrefix_MediaGeneric,
  MLMediaGenericResult_BadType,
  MLMediaGenericResult_NameNotFound,
  MLMediaGenericResult_HandleNotFound,
  MLMediaGenericResult_NoInit,
  MLMediaGenericResult_AlreadyExists,
  MLMediaGenericResult_DeadObject,
  MLMediaGenericResult_FailedTransaction,
  MLMediaGenericResult_BadIndex,
  MLMediaGenericResult_NotEnoughData,
  MLMediaGenericResult_WouldBlock,
  MLMediaGenericResult_UnknownTransaction,
  MLMediaGenericResult_FDSNotAllowed,
  MLMediaGenericResult_UnexpectedNull,
  MLMediaGenericResult_NotAvailable,

  /*! Ensure enum is represented as 32 bits. */
  MLMediaGenericResult_Ensure32Bits = 0x7FFFFFFF
} MLMediaGenericResult;

enum {
  /*! Defines the prefix for MLMediaResult codes. */
  MLResultAPIPrefix_Media = MLRESULT_PREFIX(0x4184)
};

/*! Detailed return values for Multimedia API calls. */
typedef enum MLMediaResult {
  MLMediaResult_AlreadyConnected = MLResultAPIPrefix_Media,
  MLMediaResult_NotConnected,
  MLMediaResult_UnknownHost,
  MLMediaResult_CannotConnect,
  MLMediaResult_IO,
  MLMediaResult_ConnectionLost,
  MLMediaResult_Legacy1,
  MLMediaResult_Malformed,
  MLMediaResult_OutOfRange,
  MLMediaResult_BufferTooSmall,
  MLMediaResult_Unsupported,
  MLMediaResult_EndOfStream,
  MLMediaResult_FormatChanged,
  MLMediaResult_Discontinuity,
  MLMediaResult_OutputBuffersChanged,
  MLMediaResult_PermissionRevoked,
  MLMediaResult_UnsupportedAudioFormat,
  MLMediaResult_HeartbeatTerminateRequested,
  /*! Unknown Media Codec Resource Request Error. */
  MLMediaResult_UnknownResource,
  /*! Invalid Request on Media Codec Resources. */
  MLMediaResult_InvalidResourceRequest,
  /*!
    \brief Only Hardware Media Codec Resources are available.
    This error code is a result of requesting for Software Media Codec Resource that is not available.
  */
  MLMediaResult_OnlyHWResourceAvailable,
  /*!
    \brief Only Software Media Codec Resources are available.
    This error code is a result of requesting for Hardware Media Codec Resource that is not available.
  */
  MLMediaResult_OnlySWResourceAvailable,
  /*! No more (Hardware or Software) Media Codec Resources available. */
  MLMediaResult_NoMoreResources,
  /*! No more Hardware Media Codec Resources available. */
  MLMediaResult_NoMoreHWResources,
  /*! No more Software Media Codec Resources available. */
  MLMediaResult_NoMoreSWResources,
  /*!
    \brief Media Codec Resource request made with Invalid Codec parameters.
    This error code could be a result of one of these cases (not limited to):
     - Requested video frame width or height is beyond the maximum resolution (width or height) supported.
     - Requested Framerate/Sample rate/Bitratre/Channel count is not supported.
  */
  MLMediaResult_InvalidCodecParam,

  /*! Ensure enum is represented as 32 bits. */
  MLMediaResult_Ensure32Bits = 0x7FFFFFFF
} MLMediaResult;

enum {
  /*! Defines the prefix for MLMediaDRMResult codes. */
  MLResultAPIPrefix_MediaDRM = MLRESULT_PREFIX(0x62ce)
};

/*! DRM related return values for Multimedia API calls. */
typedef enum MLMediaDRMResult {
  /*! Error code for undefined type. */
  MLMediaDRMResult_Unknown = MLResultAPIPrefix_MediaDRM,
  /*! Error code for no DRM license. */
  MLMediaDRMResult_NoLicense,
  /*! Error code for DRM license expired. */
  MLMediaDRMResult_LicenseExpired,
  /*! Error code for DRM session not expired. */
  MLMediaDRMResult_SessionNotOpened,
  /*! Error code for DRM when decrypt unit is not initialized. */
  MLMediaDRMResult_DecryptUnitNotInitialized,
  /*! Error code for DRM when failed to decrypt data. */
  MLMediaDRMResult_Decrypt,
  /*! Error code for DRM can not handle the operation. */
  MLMediaDRMResult_CannotHandle,
  /*! Error code for DRM when data is tampered. */
  MLMediaDRMResult_TamperDetect,
  /*!
    \brief Error Code when an operation on a \ref MLMediaDRM handle is attempted
    and the device does not have a certificate.
    The app should obtain and install a certificate using the \ref MLMediaDRM
    provisioning methods then retry the operation.
  */
  MLMediaDRMResult_NotProvisioned,
  /*! Error code for Device License Revoked. */
  MLMediaDRMResult_DeviceRevoked,
  /*! Error code if the MLMediaDRM operation fails when the required resources are in use. */
  MLMediaDRMResult_ResourceBusy,
  /*! Error code for insufficient output protection. */
  MLMediaDRMResult_InsufficientOutputProtection,
  MLMediaDRMResult_LastUsedErrorCode = MLMediaDRMResult_InsufficientOutputProtection,

  /*! Range for vendor specific DRM errors. */
  MLMediaDRMResult_VendorMin = MLResultAPIPrefix_MediaDRM + 500,
  MLMediaDRMResult_VendorMax = MLResultAPIPrefix_MediaDRM + 999,

  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMResult_Ensure32Bits = 0x7FFFFFFF
} MLMediaDRMResult;

enum {
  /*! Defines the prefix for OMX specific error codes. */
  MLResultAPIPrefix_MediaOMX = MLRESULT_PREFIX(0x5f76),
  /*! Defines the prefix for OMX extensions specific error codes. */
  MLResultAPIPrefix_MediaOMXExtensions = MLRESULT_PREFIX(0x11d9),
  /*! Defines the prefix for OMX vendor specific error codes. */
  MLResultAPIPrefix_MediaOMXVendors = MLRESULT_PREFIX(0xe4d0),
};

enum {
  /*! Defines the prefix for MLMediaPlayerResult codes. */
  MLResultAPIPrefix_MediaPlayer = MLRESULT_PREFIX(0xc435),
};

/*! Media player related return values for Multimedia API calls. */
typedef enum MLMediaPlayerResult {
  /*! Media errors (eg. Codec not supported). */
  MLMediaPlayerResult_ServerDied = MLResultAPIPrefix_MediaPlayer,
  /*! Runtime errors. */
  MLMediaPlayerResult_NotValidForProgressivePlayback,

  /*! Ensure enum is represented as 32 bits. */
  MLMediaPlayerResult_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerResult;

/*!
    \brief Translate a media error code into a human-readable string.

    \param[in] code Error code to translate to a string.

    \return C-style ASCII string containing readable version of result code.
            Note that user should not keep a reference to the returned char pointer for future
            use as subsequent calls to MLMediaResultGetString will overwrite its content.
            Consequently, user *must not* explicitly free the returned pointer.

    \permissions None
 */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API const char * ML_CALL MLMediaResultGetString(MLResult code);

/*! \} */

ML_EXTERN_C_END
