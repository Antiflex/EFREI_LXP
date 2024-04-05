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
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject media_player.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaDataSource
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for accessing streaming media from memory.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*!
  \brief Called when buffers becomes available.

  Signal that at least one buffer is now available. Application should then
  call getBuffer() as much as possible until it returns false, or until no
  more data is currently available in the application.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
  \param[in,out] context User data as passed to MLMediaStreamSourceCreate().
*/
typedef void (*MLMediaStreamSourceOnBufferAvailable) (MLHandle media_stream_source, void *context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new MediaStreamSource object.

  \param[in] on_buffer_available #MLMediaStreamSourceOnBufferAvailable callback.
  \param[in] context User data to be passed to callbacks.
  \param[out] out_handle The #MLHandle to the new source object created. Only valid if result is #MLResult_Ok.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaStreamSourceCreate(MLMediaStreamSourceOnBufferAvailable on_buffer_available, void *context, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Destroy a MediaStreamSource object.

  \param[in] media_stream_source #MLHandle to the MediaStreamSource object to destroy.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaStreamSourceDestroy(MLHandle media_stream_source);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get a buffer where data can be written.

  If a buffer is available, true is returned and \c out_id, \c out_ptr and \c out_size
  are set. Application can then write up to \c out_size bytes into \c out_ptr and
  push that data using MLMediaStreamSourcePushBuffer().

  If no buffer is available, false is returned and application should wait
  for MLMediaStreamSourceOnBufferAvailable() to be called before retrying.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
  \param[out] out_id An opaque ID that should be passed to MLMediaStreamSourcePushBuffer().
  \param[out] out_ptr The location where to write data.
  \param[out] out_size Maximum bytes that can be written in \c out_ptr.

  \retval MLResult_Ok If operation was successful.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaStreamSourceGetBuffer(MLHandle media_stream_source, size_t *out_id, uint8_t **out_ptr, size_t *out_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Push a buffer.

  Queue a buffer acquired from MLMediaStreamSourceGetBuffer() once data has been written.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().
  \param[in] id The ID of the buffer as given by MLMediaStreamSourceGetBuffer().
  \param[in] size The number of bytes actually written in the buffer.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaStreamSourcePushBuffer(MLHandle media_stream_source, size_t id, size_t size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Push End-Of-Stream event.

  Signal that the end of stream is reached and no more data will be pushed.

  \param[in] media_stream_source #MLHandle as returned by MLMediaStreamSourceCreate().

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaStreamSourcePushEOS(MLHandle media_stream_source);

/*! \} */

ML_EXTERN_C_END
