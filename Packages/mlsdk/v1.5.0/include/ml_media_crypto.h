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

#include "ml_media_drm.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject media_crypto.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaCrypto
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for creaitng crypto session for setting up encrypted media playback.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a \ref MLMediaCrypto instance from a UUID.

  \param[in] uuid The universal unique ID of the crypto scheme. uuid must be 16 bytes.
  \param[in] data Opaque initialization data specific to the crypto scheme, This value must never be NULL.
  \param[out] out_handle Upon successful return will point to handle to the created \ref MLMediaCrypto.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaCrypto object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCryptoCreate(MLUUID uuid, const MLMediaDRMByteArray *data, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release the \ref MLMediaCrypto instance.

  \param[in] media_crypto #MLHandle to the \ref MLMediaCrypto.

  \retval MLResult_InvalidParam \ref MLMediaCrypto object is invalid.
  \retval MLResult_Ok \ref MLMediaCrypto object was successfully destroyed.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCryptoRelease(MLHandle media_crypto);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Query if the given scheme identified by its UUID is supported on this device.

  \param[in] uuid Identifies the universal unique ID of the crypto scheme. uuid must be 16 bytes.
  \param[out] out_supported On successful return contains \c true or \c false based on
              whether the given crypto scheme is supported or not.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok The query has run successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCryptoIsCryptoSchemeSupported(MLUUID uuid, bool *out_supported);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Query if the crypto scheme requires the use of a secure decoder to decode data of
  the given mime type.

  \param[in] mime_type The MIME type of the media container, e.g. "video/mp4".
  \param[out] out_required On successful return contains \c true or \c false based on
              whether the given mime type requires a secure decoder.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok The query has run successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCryptoRequiresSecureDecoderComponent(const char *mime_type, bool *out_required);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Associate a #MediaDRM session with this \ref MLMediaCrypto instance.

  \param[in] media_crypto #MLHandle to the \ref MLMediaCrypto.
  \param[in] session_id Session ID for the DRM session.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Media DRM session was set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCryptoSetMediaDRMSession(MLHandle media_crypto, const MLMediaDRMByteArray *session_id);

/*! \} */

ML_EXTERN_C_END
