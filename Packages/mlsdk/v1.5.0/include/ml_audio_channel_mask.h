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
  \brief Defines Audio Channel Mask to describe the input/output posistion.
         Position implies, the location of a speaker or a microphone for recording or playback.
  \{
*/

/*!
  \brief Audio channel output mask.

   For a channel position mask, each allowed channel position corresponds to a
   bit in the channel mask. If that channel position is present in the audio
   frame, that bit is set, otherwise it is zero. The order of the bits (from
   lsb to msb) corresponds to the order of that position's sample in the audio
   frame. The canonical channel position masks by channel count are as follows:

   =====================================================================
   channel count	channel position mask
   =====================================================================
       1		MLAudioChannelOutMono
       2		MLAudioChannelOutStereo
       3		MLAudioChannelOutStereo | MLAudioChannelOutMask_FrontCenter
       4		MLAudioChannelOutQuad
       5		MLAudioChannelOutQuad | MLAudioChannelOutMask_FrontCenter
       6		MLAudioChannelOut5Point1
       7		MLAudioChannelOut5Point1 | MLAudioChannelOutMask_BackCenter
       8		MLAudioChannelOut7Point1Surround
   =====================================================================

   These masks are an ORed composite of individual channel masks. For example
   MLAudioChannelOutMask_Stereo is composed of MLAudioChannelOutMask_FrontLeft
   and MLAudioChannelOutMask_FrontRight.

   Reference:
   - https://android.googlesource.com/platform/frameworks/base/+/b267554/media/java/android/media/AudioFormat.java
   - https://trac.ffmpeg.org/wiki/AudioChannelManipulation#Listchannelnamesandstandardchannellayouts
*/
typedef enum MLAudioChannelOutMask {
  MLAudioChannelOutMask_FrontLeft          = 0x1,
  MLAudioChannelOutMask_FrontRight         = 0x2,
  MLAudioChannelOutMask_FrontCenter        = 0x4,
  MLAudioChannelOutMask_LowFrequency       = 0x8,
  MLAudioChannelOutMask_BackLeft           = 0x10,
  MLAudioChannelOutMask_BackRight          = 0x20,
  MLAudioChannelOutMask_FrontLeftOfCenter  = 0x40,
  MLAudioChannelOutMask_FrontRightOfCenter = 0x80,
  MLAudioChannelOutMask_BackCenter         = 0x100,
  MLAudioChannelOutMask_SideLeft           = 0x200,
  MLAudioChannelOutMask_SideRight          = 0x400,
  MLAudioChannelOutMask_TopCenter          = 0x800,
  MLAudioChannelOutMask_TopFrontLeft       = 0x1000,
  MLAudioChannelOutMask_TopFrontCenter     = 0x2000,
  MLAudioChannelOutMask_TopFrontRight      = 0x4000,
  MLAudioChannelOutMask_TopBackLeft        = 0x8000,
  MLAudioChannelOutMask_TopBackCenter      = 0x10000,
  MLAudioChannelOutMask_TopBackRight       = 0x20000,
  /*! Ensure enum is represented as 32 bits. */
  MLAudioChannelOutMask_Ensure32Bits       = 0x7FFFFFFF
} MLAudioChannelOutMask;

/*!
  Definition of some of the known Channel Layouts.
*/
/*! Channel Layout for Mono. */
const int32_t MLAudioChannelOutMono = MLAudioChannelOutMask_FrontLeft;

/*! Channel Layout for Stereo. */
const int32_t MLAudioChannelOutStereo = (MLAudioChannelOutMask_FrontLeft | MLAudioChannelOutMask_FrontRight);

/*! Channel Layout for Quad. */
const int32_t MLAudioChannelOutQuad = (MLAudioChannelOutMask_FrontLeft | MLAudioChannelOutMask_FrontRight |
                                 MLAudioChannelOutMask_BackLeft | MLAudioChannelOutMask_BackRight);

/*! Channel Layout for Surround. */
const int32_t MLAudioChannelOutSurround = (MLAudioChannelOutMask_FrontLeft | MLAudioChannelOutMask_FrontRight |
                                     MLAudioChannelOutMask_FrontCenter | MLAudioChannelOutMask_BackCenter);

/*! Channel Layout for 5.1. */
const int32_t MLAudioChannelOut5Point1 = (MLAudioChannelOutMask_FrontLeft | MLAudioChannelOutMask_FrontRight |
                                    MLAudioChannelOutMask_FrontCenter | MLAudioChannelOutMask_LowFrequency |
                                    MLAudioChannelOutMask_BackLeft | MLAudioChannelOutMask_BackRight);

/*! Channel Layout for 7.1. */
const int32_t MLAudioChannelOut7Point1 = (MLAudioChannelOutMask_FrontLeft | MLAudioChannelOutMask_FrontRight |
                                    MLAudioChannelOutMask_FrontCenter | MLAudioChannelOutMask_LowFrequency |
                                    MLAudioChannelOutMask_BackLeft | MLAudioChannelOutMask_BackRight |
                                    MLAudioChannelOutMask_FrontLeftOfCenter |
                                    MLAudioChannelOutMask_FrontRightOfCenter);

/*! Channel Layout for 7.1 Surround. */
const int32_t MLAudioChannelOut7Point1Surround = (MLAudioChannelOutMask_FrontLeft | MLAudioChannelOutMask_FrontCenter |
                                            MLAudioChannelOutMask_FrontRight |
                                            MLAudioChannelOutMask_SideLeft | MLAudioChannelOutMask_SideRight |
                                            MLAudioChannelOutMask_BackLeft | MLAudioChannelOutMask_BackRight |
                                            MLAudioChannelOutMask_LowFrequency);

/*! \} */

ML_EXTERN_C_END
