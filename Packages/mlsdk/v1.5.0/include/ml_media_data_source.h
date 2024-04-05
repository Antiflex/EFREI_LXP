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

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
              https://developer.android.com/reference/android/media/MediaDataSource
              Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for defining an user implemented DataSource that acts as media track source.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*!
  \brief Called to request data from the given position.

  Implementations should should write up to \p size bytes into
  \p buffer, and return the number of bytes written.

  Return 0 to indicate that end of stream is reached.
  Return -1 on error.

  \param[in] media_data_source #MLHandle as returned by MLMediaDataSourceCreate().
  \param[in] position The position in the data source to read from.
  \param[in] size The number of bytes to read.
  \param[out] buffer The buffer to read the data into.
  \param[in,out] context User data as passed to MLMediaDataSourceCreate().

  \return The number of bytes read, or -1 if there was an error.
*/
typedef int64_t (*MLMediaDataSourceReadAt) (MLHandle media_data_source, size_t position, size_t size, uint8_t *buffer, void *context);

/*!
  \brief Called to get the size of the data source.

  \param[in] media_data_source #MLHandle as returned by MLMediaDataSourceCreate().
  \param[in,out] context User data as passed to MLMediaDataSourceCreate().

  \return the size of data source in bytes, or -1 if the size is unknown.
*/
typedef int64_t (*MLMediaDataSourceGetSize) (MLHandle media_data_source, void *context);

/*!
  \brief Called before deleting |this|. The other methods may return errors
  if they're called after calling close().

  \param[in] media_data_source #MLHandle as returned by MLMediaDataSourceCreate().
  \param[in,out] context User data as passed to MLMediaDataSourceCreate().
*/
typedef void (*MLMediaDataSourceClose) (MLHandle media_data_source, void *context);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new MediaDataSource object.

  \param[in] read_at MLMediaDataSourceReadAt callback.
  \param[in] get_size MLMediaDataSourceGetSize callback.
  \param[in] close MLMediaDataSourceClose callback.
  \param[in] context User data to be passed to callbacks.
  \param[out] out_handle The #MLHandle to the new source object created. Only valid if result is MLResult_Ok.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok if operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaDataSourceCreate(MLMediaDataSourceReadAt read_at, MLMediaDataSourceGetSize get_size, MLMediaDataSourceClose close, void *context, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Destroy a #MediaDataSource object.

  \param[in] media_data_source #MLHandle to the #MediaDataSource object to destroy.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok if operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaDataSourceDestroy(MLHandle media_data_source);

/*! \} */

ML_EXTERN_C_END
