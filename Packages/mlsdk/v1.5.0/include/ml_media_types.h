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

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/struct/pssh-entry
            https://developer.android.com/reference/android/media/MediaExtractor#getPsshInfo()
            Developers are encouraged to consider using ExoPlayer for all media playback needs.

  \{
*/

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief PSSH entry.
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLPSSHEntry {
  /*! 16 bytes UUID specifying crypto scheme. */
  MLUUID uuid;
  /*! Size of the data payload. */
  size_t size;
  /*! Data specific to that scheme. */
  uint8_t *data;
} MLPSSHEntry;

/*! \} */

ML_EXTERN_C_END
