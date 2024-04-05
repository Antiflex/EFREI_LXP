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

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
            https://developer.android.com/reference/android/media/MediaFormat#MIMETYPE_TEXT_VTT
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief Data Structure for WebVTT Timed Text.

  \{
*/

/*!
  \brief Cue orientation setting.

  \apilevel 4

*/
typedef enum MLWebVTTOrientation {
  MLWebVTTOrientation_Horizontal   = 0,
  MLWebVTTOrientation_Vertical     = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLWebVTTOrientation_Ensure32Bits = 0x7FFFFFFF
} MLWebVTTOrientation;

/*!
  \brief Cue direction setting.

  \apilevel 4

*/
typedef enum MLWebVTTDirection {
  MLWebVTTDirection_Default      = 0,
  MLWebVTTDirection_LeftToRight  = 1,
  MLWebVTTDirection_RightToLeft  = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLWebVTTDirection_Ensure32Bits = 0x7FFFFFFF
} MLWebVTTDirection;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Cue aligment setting.

  \apilevel 4

*/
typedef enum MLWebVTTAlign {
  MLWebVTTAlign_Start        = 0,
  MLWebVTTAlign_Middle       = 1,
  MLWebVTTAlign_End          = 2,
  MLWebVTTAlign_Left         = 3,
  MLWebVTTAlign_Right        = 4,
  /*! Ensure enum is represented as 32 bits. */
  MLWebVTTAlign_Ensure32Bits = 0x7FFFFFFF
} MLWebVTTAlign;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief WebVTT data structure.

  \apilevel 4

*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLWebVTTData {
  /*! Track cue start time in milliseconds. */
  int64_t             start_time_ms;
  /*! Track cue end time in milliseconds. */
  int64_t             end_time_ms;
  /*!  WebVTT file body encoded as UTF-8. */
  char                *body;
  /*! A sequence of characters unique amongst all the WebVTT cue identifiers. */
  char                *id;
  /*! A boolean indicating whether the line is an integer number of lines. */
  bool                snap_to_lines;
  /*! Orientation of the cue. */
  MLWebVTTOrientation orientation;
  /*! The writing direction. */
  MLWebVTTDirection   direction;
  /*! Relative cue line position. */
  float               relative_line_position;
  /*! WebVTT cue line number. */
  int32_t             line_number;
  /*! The indent of the cue box in the direction defined by the writing direction. */
  float               text_position;
  /*! WebVTT cue size. */
  float               size;
  /*! WebVTT cue text alignment. */
  MLWebVTTAlign       align;
} MLWebVTTData;

ML_EXTERN_C_END
