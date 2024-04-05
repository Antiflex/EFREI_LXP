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
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
            https://developer.android.com/reference/android/media/TimedText
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief Data Structure for TTML Timed Text.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.

  \{
*/

/*!
  \brief An unset position, width or size which is negative of maximum finite value of float (-FLT_MAX).

  \apilevel 20

*/
static const float MLTTMLDimen_Unset = -3.402823466e+38F;

/*!
  \brief Cue text alignment within the cue box.

  \apilevel 20

*/
typedef enum MLTTMLLayoutAlignment {
  /*! An unspecified alignment value. */
  MLTTMLLayoutAlignment_Unspecified  = 0x7FFFFFFF,
  /*! Normal alignment relative to text direction. */
  MLTTMLLayoutAlignment_Normal       = 0,
  /*! Centered alignment. */
  MLTTMLLayoutAlignment_Center       = 1,
  /*! Opposite alignment relative to text direction. */
  MLTTMLLayoutAlignment_Opposite     = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLTTMLLayoutAlignment_Ensure32Bits = 0x7FFFFFFF
} MLTTMLLayoutAlignment;

/*!
  \brief Cue line type.

  \apilevel 20

*/
typedef enum MLTTMLLineType {
  /*! An unset line type value. */
  MLTTMLLineType_Unset        = 0x7FFFFFFF,
  /*! Line position is fractional position within the viewport. */
  MLTTMLLineType_Fraction     = 0,
  /*! Line position is number of lines, interpretation also depends on the line anchor type. */
  MLTTMLLineType_Number       = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLTTMLLineType_Ensure32Bits = 0x7FFFFFFF
} MLTTMLLineType;

/*!
  \brief Cue anchor type.

  \apilevel 20

*/
typedef enum MLTTMLAnchorType {
  /*! An unset anchor type value. */
  MLTTMLAnchorType_Unset        = 0x7FFFFFFF,
  /*! Anchors the left (for horizontal positions) or top (for vertical positions) edge of the cue box. */
  MLTTMLAnchorType_Start        = 0,
  /*! Anchors the middle of the cue box. */
  MLTTMLAnchorType_Middle       = 1,
  /*! Anchors the right (for horizontal positions) or bottom (for vertical positions) edge of the cue box. */
  MLTTMLAnchorType_End          = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLTTMLAnchorType_Ensure32Bits = 0x7FFFFFFF
} MLTTMLAnchorType;

/*!
  \brief Cue text size type.

  \apilevel 20

*/
typedef enum MLTTMLTextSizeType {
  /*! An unset text size type value. */
  MLTTMLTextSizeType_Unset                     = 0x7FFFFFFF,
  /*! Text size is measured as a fraction of the viewport size minus the view padding. */
  MLTTMLTextSizeType_Fractional                = 0,
  /*! Text size is measured as a fraction of the viewport size, ignoring the view padding. */
  MLTTMLTextSizeType_Fractional_Ignore_Padding = 1,
  /*! Text size is measured in number of pixels. */
  MLTTMLTextSizeType_Absolute                  = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLTTMLTextSizeType_Ensure32Bits              = 0x7FFFFFFF
} MLTTMLTextSizeType;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Byte data for TTML image cues.

  \apilevel 20

*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLTTMLImage {
  /*! Image size in bytes. */
  size_t size;
  /*! Byte data of the image. */
  uint8_t *data;
} MLTTMLImage;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief TTML data structure.

  \apilevel 20

*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLTTMLData {
  /*! Track cue start time in milliseconds. */
  int64_t start_time_ms;
  /*! Track cue end time in milliseconds. */
  int64_t end_time_ms;
  /*! The cue text encoded as UTF-8. Or null if this is an image cue. */
  char *text;
  /*! The alignment of the cue text within the cue box. */
  MLTTMLLayoutAlignment text_alignment;
  /*! The cue image if this is an image cue, an empty image otherwise. */
  MLTTMLImage bitmap;
  /*! \brief The position of the #line_anchor of the cue box within the viewport in the direction
      orthogonal to the writing direction, or MLTTMLDimen_Unset.

      When set, the interpretation of the value depends on the value of #line_type.
      For horizontal text and #line_type equal to #MLTTMLLineType_Fraction, this is the
      fractional vertical position relative to the top of the viewport.
   */
  float line;
  /*! \brief The cue line type.

      #MLTTMLLineType_Fraction indicates that #line is a fractional position within the viewport.

      #MLTTMLLineType_Number indicates that #line is a line number, where the size of
      each line is taken to be the size of the first line of the cue. When #line is greater
      than or equal to 0 lines count from the start of the viewport, with 0 indicating zero offset
      from the start edge. When #line is negative lines count from the end of the viewport,
      with -1 indicating zero offset from the end edge. For horizontal text the line spacing is the
      height of the first line of the cue, and the start and end of the viewport are the top and
      bottom respectively.

      Note that it's particularly important to consider the effect of #line_anchor when
      using #MLTTMLLineType_Number.

      \code{.cpp} (line == 0 && line_anchor == MLTTMLAnchorType_Start) \endcode
      Positions a (potentially multi-line) cue at the very top of the viewport.

      \code{.cpp} (line == -1 && line_anchor == MLTTMLAnchorType_EndD) \endcode
      Positions a (potentially multi-line) cue at the very bottom of the viewport.

      \code{.cpp} (line == 0 && line_anchor == MLTTMLAnchorType_End) \endcode and
      \code{.cpp} (line == -1 && line_anchor == MLTTMLAnchorType_Start) \endcode
      Position cues entirely outside of the viewport.

      \code{.cpp} (line == 1 && line_anchor == MLTTMLAnchorType_End) \endcode
      Positions a cue so that only the last line is visible at the top of the viewport.

      \code{.cpp} (line == -2 && line_anchor == MLTTMLAnchorType_Start) \endcode
      Position a cue so that only its first line is visible at the bottom of the viewport.
   */
  MLTTMLLineType line_type;
  /*! The cue box anchor in the direction of line. */
  MLTTMLAnchorType line_anchor;
  /*! \brief The fractional position of the #position_anchor of the cue box within the viewport in
      the direction orthogonal to #line, or MLTTMLDimen_Unset.

      For horizontal text, this is the horizontal position relative to the left of the viewport.
      Note that positioning is relative to the left of the viewport even in the case of right-to-left text.
   */
  float position;
  /*! The cue box anchor in the direction of position. */
  MLTTMLAnchorType position_anchor;
  /*! The cue box size in the writing direction, as a fraction of the viewport size or MLTTMLDimen_Unset. */
  float size;
  /*! The cue bitmap height as a fraction of the viewport size or MLTTMLDimen_Unset if the bitmap should be
      displayed at its natural height given the bitmap dimensions and the specified #size. */
  float bitmap_height;
  /*! Specifies whether or not the #window_color property is set. */
  bool window_color_set;
  /*! The cue window fill color in ARGB format. */
  uint32_t window_color;
  /*! The cue default text size type, or #MLTTMLTextSizeType_Unset if this cue has no default text size. */
  MLTTMLTextSizeType text_size_type;
  /*! The cue default text size, or MLTTMLDimen_Unset if this cue has no default. */
  float text_size;
} MLTTMLData;

ML_EXTERN_C_END
