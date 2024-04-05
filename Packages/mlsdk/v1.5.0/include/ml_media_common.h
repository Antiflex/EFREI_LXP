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

ML_EXTERN_C_BEGIN

/*!
  \addtogroup MediaPlayer

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
            https://developer.android.com/reference/android/media/MediaPlayer#seekTo(long,%20int)
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \{
*/

/*! Mode indicating where exactly to seek to. */
typedef enum MLMediaSeekMode {
  /*! Seek to the previous key frame. */
  MLMediaSeekMode_Previous_Sync,
  /*! Seek to the next key frame. */
  MLMediaSeekMode_Next_Sync,
  /*! Seek to the closest key frame. */
  MLMediaSeekMode_Closest_Sync,
  /*! Seek to the closest frame, more accurate but slower. */
  MLMediaSeekMode_Closest,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaSeekMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaSeekMode;

/*! \} */

ML_EXTERN_C_END
