// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2021 Magic Leap, Inc. All Rights Reserved.
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
  \sharedobject media_format.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaFormat
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for creating and retrieving media format information.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

#define MAX_FORMAT_STRING_SIZE 512
#define MAX_KEY_STRING_SIZE    64

/*! Data type containing byte array buffer and the size. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaFormatByteArray {
  uint8_t *ptr;
  size_t length;
} MLMediaFormatByteArray;

typedef enum MLMediaFormatAudioEncoding {
  /*! Audio data format: PCM 16 bits per sample. */
  MLMediaFormatAudioEncoding_PCM16Bits = 2,
  /*! Audio data format: PCM 8 bits per sample. */
  MLMediaFormatAudioEncoding_PCM8Bits  = 3,
  /*! Audio data format: single-precision floating-point per sample. */
  MLMediaFormatAudioEncoding_PCMFloat = 4,
  /*! Audio data format: PCM 32 bits per sample. */
  MLMediaFormatAudioEncoding_PCM32Bits = 201,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaFormatAudioEncoding_Ensure32Bits = 0x7FFFFFFF
} MLMediaFormatAudioEncoding;

typedef const char *MLMediaFormatKey;

/*!
  \brief The format of media data (video/audio) is specified as key/value pairs.
  Below is a list of keys used to set/obtain format values.
*/

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the target reference level that was assumed at the encoder for
  calculation of attenuation gains for clipping prevention.

  <p>If it is known, this information can be provided as an integer value between
  0 and 127, which is calculated as -4 * Encoded Target Level in LKFS.
  If the Encoded Target Level is unknown, the value can be set to -1.
  <p>The default value is -1 (unknown).
  <p>The value is ignored when heavy compression is used (see
  {\link #MLMediaFormat_Key_AAC_DRC_Heavy_Compression}).

  <p>This key is only used during decoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_Encoded_Target_Level;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the boost factor allowing to adapt the dynamics of the output to the
  actual listening requirements. This relies on DRC gain sequences that can be transmitted in
  the encoded bitstream to be able to reduce the dynamics of the output signal upon request.
  This factor enables the user to select how much of the gains are applied.
  <p>Positive gains (boost) and negative gains (attenuation, see
  {\link #MLMediaFormat_Key_AAC_DRC_Attenuation_Factor}) can be controlled separately for a better match
  to different use-cases.
  <p>Typically, attenuation gains are sent for loud signal segments, and boost gains are sent
  for soft signal segments. If the output is listened to in a noisy environment, for example,
  the boost factor is used to enable the positive gains, i.e. to amplify soft signal segments
  beyond the noise floor. But for listening late at night, the attenuation
  factor is used to enable the negative gains, to prevent loud signal from surprising
  the listener. In applications which generally need a low dynamic range, both the boost factor
  and the attenuation factor are used to enable all DRC gains.
  <p>In order to prevent clipping, it is also recommended to apply the attenuation gains
  in case of a downmix and/or loudness normalization to high target reference levels.
  <p>Both the boost and the attenuation factor parameters are given as integer values
  between 0 and 127, representing the range of the factor of 0 (i.e. don't apply)
  to 1 (i.e. fully apply boost/attenuation gains respectively).
  <p>The default value is 127 (fully apply boost DRC gains).
  <p>This key is only used during decoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Boost_Factor;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the attenuation factor allowing to adapt the dynamics of the output to the
  actual listening requirements.

  See {\link #MLMediaFormat_Key_AAC_DRC_Boost_Factor} for a description of the role of this attenuation
  factor and the value range.
  <p>The default value is 127 (fully apply attenuation DRC gains).
  <p>This key is only used during decoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Attenuation_Factor;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the selection of the heavy compression profile for DRC.

  Two separate DRC gain sequences can be transmitted in one bitstream: MPEG-4 DRC light
  compression, and DVB-specific heavy compression. When selecting the application of the heavy
  compression, one of the sequences is selected:
  <ul>
  <li>0 enables light compression,</li>
  <li>1 enables heavy compression instead.
  </ul>
  Note that only light compression offers the features of scaling of DRC gains
  (see {\link #MLMediaFormat_Key_AAC_DRC_Boost_Factor} and {\link #MLMediaFormat_Key_AAC_DRC_Attenuation_Factor} for the
  boost and attenuation factors, and frequency-selective (multiband) DRC.
  Light compression usually contains clipping prevention for stereo downmixing while heavy
  compression, if additionally provided in the bitstream, is usually stronger, and contains
  clipping prevention for stereo and mono downmixing.
  <p>The default is 1 (heavy compression).
  <p>This key is only used during decoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Heavy_Compression;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing a gain to be applied so that the output loudness matches the
  Target Reference Level. This is typically used to normalize loudness across program items.

  The gain is derived as the difference between the Target Reference Level and the
  Program Reference Level. The latter can be given in the bitstream and indicates the actual
  loudness value of the program item.
  <p>The Target Reference Level controls loudness normalization for both MPEG-4 DRC and
  MPEG-D DRC.
  <p>The value is given as an integer value between
  40 and 127, and is calculated as -4 * Target Reference Level in LKFS.
  Therefore, it represents the range of -10 to -31.75 LKFS.
  <p>The default value on mobile devices is 64 (-16 LKFS).
  <p>This key is only used during decoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Target_Reference_Level;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the maximum number of channels that can be output by the AAC decoder.

  By default, the decoder will output the same number of channels as present in the encoded
  stream, if supported. Set this value to limit the number of output channels, and use
  the downmix information in the stream, if available.
  <p>Values larger than the number of channels in the content to decode are ignored.
  <p>This key is only used during decoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_Max_Output_Channel_Count;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the AAC profile to be used (AAC audio formats only).

  Constants are declared in \ref MLMediaCodecListGetSupportedProfileLevels.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_Profile;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the AAC SBR mode to be used (AAC audio formats only).

  The associated value is an integer and can be set to following values:
  <ul>
  <li>0 - no SBR should be applied.</li>
  <li>1 - single rate SBR.</li>
  <li>2 - double rate SBR.</li>
  </ul>
  Note: If this key is not defined the default SRB mode for the desired AAC profile will
  be used.
  <p>This key is only used during encoding.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_SBR_Mode;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the average bitrate in bits/sec.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Bit_Rate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired bitrate mode to be used by an encoder.

  Constants are declared in \ref MLMediaCodecBitrateMode.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Bit_Rate_Mode;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the capture rate of a video format in frames/sec.

  <p>
  When capture rate is different than the frame rate, it means that the
  video is acquired at a different rate than the playback, which produces
  slow motion or timelapse effect during playback. Application can use the
  value of this key to tell the relative speed ratio between capture and
  playback rates when the video was recorded.
  </p>
  <p>
  The associated value is an integer or a float.
  </p>
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Capture_Rate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the number of channels in an audio format.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Channel_Count;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the channel composition of audio content.

  This mask is composed of bits drawn from channel mask definitions in
  \ref android.media.AudioFormat.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Channel_Mask;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the color format of the content in a video format.

  Constants are declared in \ref MLMediaCodecBitrateMode.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Color_Format;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the duration (in microseconds) of the content.

  The associated value is a long.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Duration;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the FLAC compression level to be used (FLAC audio format only).

  The associated value is an integer ranging from 0 (fastest, least compression)
  to 8 (slowest, most compression).
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_FLAC_Compression_Level;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the frame rate of a video format in frames/sec.

  The associated value is normally an integer when the value is used by the platform,
  but video codecs also accept float configuration values.
  Specifically, \ref MLMediaExtractor#getTrackFormat provides an integer
  value corresponding to the frame rate information of the track if specified and non-zero.
  Otherwise, this key is not present. \ref MLMediaCodec#configure accepts both
  float and integer values. This represents the desired operating frame rate if the
  {\link #MLMediaFormat_Key_Operating_Rate} is not present and {\link #MLMediaFormat_Key_Priority} is <code>0</code>
  (realtime). For video encoders this value corresponds to the intended frame rate,
  although encoders are expected
  to support variable frame rate based on \ref MLMediaCodec.BufferInfo#presentationTimeUs
  buffer timestamp. This key is not used in the \ref MLMediaCodec#getInputFormat input/\ref MLMediaCodec#getOutputFormat output formats,
  nor by \ref MLMediaMuxer#addTrack.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Frame_Rate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the height of the content in a video format.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Height;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the frequency of key frames expressed in seconds between key frames.

  <p>
  This key is used by video encoders.
  A negative value means no key frames are requested after the first frame.
  A zero value means a stream containing all key frames is requested.
  <p class=note>
  Most video encoders will convert this value of the number of non-key-frames between
  key-frames, using the {\link #MLMediaFormat_Key_Frame_Rate frame rate} information; therefore,
  if the actual frame rate differs (e.g. input frames are dropped or the frame rate
  changes), the <strong>time interval</strong> between key frames will not be the
  configured value.
  <p>
  The associated value is an integer (or float since
  \ref android.os.Build.VERSION_CODES#N_MR1 ).
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_I_Frame_Interval;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the period of intra refresh in frames.

  This is an optional parameter that applies only to video encoders.
  If encoder supports it (\ref MLMediaCodecListIsIntraRefreshSupported), the whole frame is completely refreshed after the specified period.
  Also for each frame, a fix subset of macroblocks must be intra coded which leads to a more constant bitrate than inserting a key frame.
  This key is recommended for video streaming applications as it provides low-delay and good error-resilience.
  This key is ignored if the video encoder does not support the intra refresh feature.
  Use the output format to verify that this feature was enabled.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_Period;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key mapping to a value of 1 if the content is AAC audio and
  audio frames are prefixed with an ADTS header.

  The associated value is an integer (0 or 1).
  This key is only supported when _decoding_ content, it cannot
  be used to configure an encoder to emit ADTS output.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_ADTS;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key for boolean AUTOSELECT behavior for the track. Tracks with AUTOSELECT=true
  are considered when automatically selecting a track without specific user
  choice, based on the current locale.
  This is currently only used for subtitle tracks, when the user selected
  'Default' for the captioning locale.
  The associated value is an integer, where non-0 means TRUE.  This is an optional
  field; if not specified, AUTOSELECT defaults to TRUE.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Autoselect;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key for boolean DEFAULT behavior for the track. The track with DEFAULT=true is
  selected in the absence of a specific user choice.

  This is currently used in two scenarios:
  <ol>
  <li> For subtitle tracks, when the user selected 'Default' for the captioning locale.</li>
  <li> For a \ref MIMETYPE_IMAGE_ANDROID_HEIC track, indicating the image is the
  primary item in the file.</li>
  </ol>
  The associated value is an integer, where non-0 means TRUE.  This is an optional
  field; if not specified, DEFAULT is considered to be FALSE.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Default;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key for the FORCED field for subtitle tracks.

  True if it is a forced subtitle track. Forced subtitle tracks
  are essential for the content and are shown even when the user
  turns off Captions. They are used for example to translate
  foreign/alien dialogs or signs. The associated value is an integer,
  where non-0 means TRUE. This is an optional field; if not specified,
  FORCED defaults to FALSE.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Forced_Subtitle;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the language of the content, using either ISO 639-1
  or 639-2/T codes.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Language;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the maximum expected height of the content in a video
  decoder format, in case there are resolution changes in the video content.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Height;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Described by this MediaFormat.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Input_Size;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the maximum expected width of the content in a video
  decoder format, in case there are resolution changes in the video content.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Width;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the mime type of the MediaFormat.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Mime;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the raw audio sample encoding/format.

  <p>The associated value is an integer, using one of the
  \ref AudioFormat.ENCODING_PCM_ values.</p>

  <p>This is an optional key for audio decoders and encoders specifying the
  desired raw audio sample format during \ref MLMediaCodec#configure
  MediaCodec.configure(&hellip;) call. Use \ref MLMediaCodec#getInputFormat
  MediaCodec.getInput / \ref MLMediaCodec#getOutputFormatOutputFormat(&hellip;)
  to confirm the actual format. For the PCM decoder this key specifies both
  input and output sample encodings.</p>

  <p>This key is also used by \ref MLMediaExtractor to specify the sample
  format of audio data, if it is specified.</p>

  <p>If this key is missing, the raw audio sample format is signed 16-bit short.</p>

  The associated value is an integer with keys defined by \ref MLMediaFormatAudioEncoding.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_PCM_Encoding;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief If specified when configuring a video decoder rendering to a surface,
  causes the decoder to output "blank", i.e. black frames to the surface.

  when stopped to clear out any previously displayed contents.
  The associated value is an integer of value 1.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Push_Blank_Buffers_On_Stop;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Applies only when configuring a video encoder in "surface-input" mode.

  The associated value is a long and gives the time in microseconds
  after which the frame previously submitted to the encoder will be
  repeated (once) if no new frame became available since.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Repeat_Previous_Frame_After;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the sample rate of an audio format.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Sample_Rate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the stride of the video bytebuffer layout.

  Stride (or row increment) is the difference between the index of a pixel
  and that of the pixel directly underneath. For YUV 420 formats, the
  stride corresponds to the Y plane; the stride of the U and V planes can
  be calculated based on the color format, though it is generally undefined
  and depends on the device and release.
  The associated value is an integer, representing the number of bytes.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Stride;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the temporal layering schema.

  This is an optional parameter that applies only to video encoders.
  Use \ref MediaCodec#getOutputFormat after \ref MediaCodec#configure to
  query if the encoder supports the desired schema. Supported values are
  <code>webrtc.vp8.N-layer</code>, <code>android.generic.N</code>,
  <code>android.generic.N+M</code> and <code>none</code>, where
  <code>N</code> denotes the total number of non-bidirectional layers (which must be at least 1)
  and <code>M</code> denotes the total number of bidirectional layers (which must be non-negative).
  <p class=note><code>android.generic.*</code> schemas have been added in \ref
  android.os.Build.VERSION_CODES#N_MR1.
  <p>
  The encoder may support fewer temporal layers, in which case the output format
  will contain the configured schema. If the encoder does not support temporal
  layering, the output format will not have an entry with this key.
  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Temporal_Layering;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the width of the content in a video format.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Width;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief The left-coordinate (x) of the crop rectangle.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Left;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief The right-coordinate (x) MINUS 1 of the crop rectangle.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Right;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief The bottom-coordinate (y) MINUS 1 of the crop rectangle.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Bottom;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief The top-coordinate (y) of the crop rectangle.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crop_Top;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired operating frame rate for video or sample rate for audio
  that the codec will need to operate at.

  <p>
  The associated value is an integer or a float representing frames-per-second or
  samples-per-second.
  <p>
  This is used for cases like high-speed/slow-motion video capture, where the video encoder
  format contains the target playback rate (e.g. 30fps), but the component must be able to
  handle the high operating capture rate (e.g. 240fps).
  <p>
  This rate will be used by codec for resource planning and setting the operating points.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Operating_Rate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the desired encoder latency in frames.

  parameter that applies only to video encoders. If encoder supports it, it should ouput
  at least one output frame after being queued the specified number of frames. This key
  is ignored if the video encoder does not support the latency feature. Use the output
  format to verify that this feature was enabled and the actual value used by the encoder.
  <p>
  If the key is not specified, the default latency will be implementation specific.
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Latency;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired video bitrate.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Video_Bitrate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Request that the encoder produce a sync frame "soon".

  Provide an Integer with the value 0.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Request_Sync_Frame;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Temporarily suspend/resume encoding of input data.

  While suspended input data is effectively discarded instead of being fed into the encoder.
  This parameter really only makes sense to use with an encoder in "surface-input" mode,
  as the client code has no control over the input-side of the encoder in that case.

  The value is an Integer object containing the value 1 to suspend or the value 0 to resume.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Set_Suspend;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief When PARAMETER_KEY_SUSPEND is present, the client can also optionally use this key to
    specify the timestamp (in micro-second) at which the suspend/resume operation takes effect.

   Note that the specified timestamp must be greater than or equal to the timestamp of any previously queued suspend/resume operations.

   The value is a long int, indicating the timestamp to suspend/resume.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Set_Suspend_Time;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired before which frames are to be skipped.

  The associated value is a long int, indicating the timestamp (in microseconds) to be applied.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Drop_Before;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired after which frames are to be skipped.

  The associated value is a long int, indicating the timestamp (in microseconds) to be applied.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Drop_After;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Specify an offset (in micro-second) to be added on top of the timestamps onward.

  A typical use case is to apply adjustment to the timestamps after a period of pause by the user.
  This parameter can only be used on an encoder in "surface-input" mode.

  The value is a long int, indicating the timestamp offset to be applied.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Parameter_Offset_Time;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired codec priority.

  The associated value can be one of the \ref MLMediaCodecPriority enumeration.
  This is a hint used at codec configuration and resource planning - to understand the realtime requirements of the application;
  however, due to the nature of media components, performance is not guaranteed.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Priority;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the maximum number of B frames between I or P frames, to be used by a video encoder.

  The associated value is an integer. The default value is 0, which means that no B frames are allowed.
  Note that non-zero value does not guarantee B frames; it's up to the encoder to decide.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_B_Frames;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the mode of intra refresh in frames. The associated value is an integer.

  This is an optional parameter that applies only to video encoders.
  If encoder supports it (\ref MLMediaCodecListIsIntraRefreshSupported), the whole frame is completely refreshed after the specified period.
  Also for each frame, a fixed subset of macroblocks must be intra-coded which leads to a more constant bitrate than inserting a key frame.
  This key is recommended for video streaming applications as it provides low-delay and good error-resilience.
  This key is ignored if the video encoder does not support the intra refresh feature.
  Use the output format to verify that this feature was enabled.

  The possible values are defined in \ref MLMediaCodecIntraRefreshMode.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_Mode;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Number of consecutive macroblocks to be coded as intra when CIR is enabled.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_CIR_Num;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Number of intra macroblocks to refresh in a frame when AIR is enabled.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_AIR_Num;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Number of times a motion marked macroblock has to be intra coded.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Intra_Refresh_AIR_Ref;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired profile to be used by an encoder.

  The associated value is an integer.

  The supported profiles can be queries through \ref MLMediaCodecListGetSupportedProfileLevels.
  The values are defined in \ref MLMediaCodecProfileType enumeration.
  This key is used as a further hint when specifying a desired profile, and is only supported for codecs that specify a level.
  This key is ignored if the profile is not specified.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Profile;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired level to be used by an encoder.

  The associated value is an integer.

  The supported profiles can be queries through \ref MLMediaCodecListGetSupportedProfileLevels.
  The values are defined in \ref MLMediaCodecLevelType enumeration.
  This key is used as a further hint when specifying a desired profile, and is only supported for codecs that specify a level.
  This key is ignored if the level is not specified.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Level;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing whether encoders prepend headers to sync frames (e.g. SPS and PPS to IDR frames for H.264).

  This is an optional parameter that applies only to video encoders.
  A video encoder may not support this feature; the component will fail to configure in that case.
  For other components, this key is ignored.
  The value is an integer, with 1 indicating to prepend headers to every sync frame, or 0 otherwise.
  The default value is 0.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Prepend_Header_To_Sync_Frames;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the range of the component values of the video content.

  The associated value is an integer: 0 if unspecified, or one of the
  COLOR_RANGE_ values.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Color_Range;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the color primaries, white point and
  luminance factors for video content.

  The associated value is an integer: 0 if unspecified, or one of the
  COLOR_STANDARD_ values.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Color_Standard;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the opto-electronic transfer function used
  for the video content.

  The associated value is an integer: 0 if unspecified, or one of the
  COLOR_TRANSFER_ values.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Color_Transfer;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the static metadata of HDR (high-dynamic-range) video content.

  The associated value is a ByteBuffer. This buffer contains the raw contents of the
  Static Metadata Descriptor (including the descriptor ID) of an HDMI Dynamic Range and
  Mastering InfoFrame as defined by CTA-861.3. This key must be provided to video decoders
  for HDR video content unless this information is contained in the bitstream and the video
  decoder supports an HDR-capable profile. This key must be provided to video encoders for
  HDR video content.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_HDR_Static_Info;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the codec specific data.

  Codec-specific data in the format is automatically submitted to the codec upon start(); you MUST NOT submit this data explicitly.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_CSD;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the codec specific data buffer #0.

  Codec-specific data in the format is automatically submitted to the codec upon start(); you MUST NOT submit this data explicitly.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_CSD0;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the codec specific data buffer #1.

  Codec-specific data in the format is automatically submitted to the codec upon start(); you MUST NOT submit this data explicitly.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_CSD1;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the codec specific data buffer #2.

  Codec-specific data in the format is automatically submitted to the codec upon start(); you MUST NOT submit this data explicitly.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_CSD2;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the codec specific data buffer for AVC (h.264).

  Codec-specific data in the format is automatically submitted to the codec upon start(); you MUST NOT submit this data explicitly.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_CSD_Avc;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the codec specific data buffer for HEVC (h.265).

  Codec-specific data in the format is automatically submitted to the codec upon start(); you MUST NOT submit this data explicitly.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_CSD_Hevc;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata - album title of the media.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Album;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The artwork for the album of the media's original source as a Bitmap.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Albumart;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The artist for the album of the media's original source.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Albumartist;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The artist of the media.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Artist;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media presentation info.

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Audio_Presentation_Info;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media presentation Id.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Audio_Presentation_Presentation_Id;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media program Id.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Audio_Presentation_Program_Id;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the audio session ID of the AudioTrack associated
  to a tunneled video codec.

  The associated value is an integer.

  \see MLMediaCodecBitrateMode#FEATURE_TunneledPlayback
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Audio_Session_Id;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The author of the media.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Author;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Key representing media number of bits per sample.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Bits_Per_Sample;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The cd track number.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Cdtracknumber;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media compilation.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Compilation;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the encoding complexity.

  The associated value is an integer.  These values are device and codec specific,
  but lower values generally result in faster and/or less power-hungry encoding.

  \see MediaCodecInfo.EncoderCapabilities#getComplexityRange()
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Complexity;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata - composer of the media.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Composer;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief If specified when configuring a video encoder that's in "surface-input"
  mode, it will instruct the encoder to put the surface source in suspended
  state when it's connected.

  No video frames will be accepted until a resume
  operation (see \ref MediaCodec#PARAMETER_KEY_SUSPEND ), optionally with
  timestamp specified via \ref MediaCodec#PARAMETER_KEY_SUSPEND_TIME , is
  received.

  The value is an integer, with 1 indicating to create with the surface
  source suspended, or 0 otherwise. The default value is 0.

  If this key is not set or set to 0, the surface source will accept buffers
  as soon as it's connected to the encoder (although they may not be encoded
  immediately). This key can be used when the client wants to prepare the
  encoder session in advance, but do not want to accept buffers immediately.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Create_Input_Surface_Suspended;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Default_Iv_Size;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Encrypted_Byte_Block;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Encrypted_Sizes;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Iv;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Key;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Mode;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Plain_Sizes;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Crypto_Skip_Byte_Block;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_D263;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata - The date the media was created or published. The format is unspecified but RFC 3339 is recommended.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Date;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The disc number for the media's original source.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Discnumber;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing display crop rectangle.

  The associated value is a string of format "Rect %s(%d, %d, %d, %d)" where the value meaning is: "Rect name(left, top, right, bottom)".
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Display_Crop;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Display_Height;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Display_Width;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the number of frames to trim from the start of the decoded audio stream.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Encoder_Delay;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the number of frames to trim from the end of the decoded audio stream.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Encoder_Padding;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the electrostatic discharge and soldering (ESDS).

  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Esds;
/*!
  The associated value is a long integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Exif_Offset;
/*!
  The associated value is a long integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Exif_Size;
/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Frame_Count;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media genre.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Genre;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the number of grid columns in the content in a
  \ref MIMETYPE_IMAGE_ANDROID_HEIC track.

  The associated value is an integer.

  Refer to \ref MIMETYPE_IMAGE_ANDROID_HEIC on decoding instructions of such tracks.

  \see #MLMediaFormat_Key_Tile_Width
  \see #MLMediaFormat_Key_Tile_Height
  \see #MLMediaFormat_Key_Grid_Rows
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Grid_Columns;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the number of grid rows in the content in a
  \ref MIMETYPE_IMAGE_ANDROID_HEIC track.

  The associated value is an integer.

  Refer to \ref MIMETYPE_IMAGE_ANDROID_HEIC on decoding instructions of such tracks.

  \see #MLMediaFormat_Key_Tile_Width
  \see #MLMediaFormat_Key_Tile_Height
  \see #MLMediaFormat_Key_Grid_Columns
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Grid_Rows;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the number of haptic channels in an audio format.

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Haptic_Channel_Count;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the HDR10+ metadata of the video content.

  The associated value is a ByteBuffer containing HDR10+ metadata conforming to the
  user_data_registered_itu_t_t35() syntax of SEI message for ST 2094-40. This key will
  be present on:
  <p>
  - The formats of output buffers of a decoder configured for HDR10+ profiles (such as
    \ref MLMediaCodecListGetSupportedProfileLevels#VP9Profile2HDR10Plus,
    \ref MLMediaCodecListGetSupportedProfileLevels#VP9Profile3HDR10Plus or
    \ref MLMediaCodecListGetSupportedProfileLevels#HEVCProfileMain10HDR10Plus), or
  </p>
  - The formats of output buffers of an encoder configured for an HDR10+ profiles that
    uses out-of-band metadata (such as
    \ref MLMediaCodecListGetSupportedProfileLevels#VP9Profile2HDR10Plus or 
    \ref MLMediaCodecListGetSupportedProfileLevels#VP9Profile3HDR10Plus).

  \see MediaCodec#PARAMETER_KEY_HDR10_PLUS_INFO.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Hdr10_Plus_Info;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Icc_Profile;
/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Sync_Frame;
/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media location.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Location;
/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media loop.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Loop;
/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media lyricist.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Lyricist;
/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The media manufacturer.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Manufacturer;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the max bitrate in bits/sec.

  This is usually over a one-second sliding window (e.g. over any window of one second).
  The associated value is an integer.
  \hide
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Bit_Rate;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Instruct the video encoder in "surface-input" mode to drop excessive
  frames from the source, so that the input frame rate to the encoder
  does not exceed the specified fps.

  The associated value is a float, representing the max frame rate to
  feed the encoder at.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Fps_To_Encoder;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Instruct the video encoder in "surface-input" mode to limit the gap of
  timestamp between any two adjacent frames fed to the encoder to the
  specified amount (in micro-second).

  The associated value is a long int. When positive, it represents the max
  timestamp gap between two adjacent frames fed to the encoder. When negative,
  the absolute value represents a fixed timestamp gap between any two adjacent
  frames fed to the encoder. Note that this will also apply even when the
  original timestamp goes backward in time. Under normal conditions, such frames
  would be dropped and not sent to the encoder.

  The output timestamp will be restored to the original timestamp and will
  not be affected.

  This is used in some special scenarios where input frames arrive sparingly
  but it's undesirable to allocate more bits to any single frame, or when it's
  important to ensure all frames are captured (rather than captured in the
  correct order).
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Max_Pts_Gap_To_Encoder;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Mpeg_User_Data;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Mpeg2_Stream_Header;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_PCM_Big_Endian;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Pssh;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired clockwise rotation on an output surface.

  This key is only used when the codec is configured using an output surface.
  The associated value is an integer, representing degrees. Supported values
  are 0, 90, 180 or 270. This is an optional field; if not specified, rotation
  defaults to 0.

  \see MLMediaCodecBitrateMode#profileLevels
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Rotation;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Sar_Height;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Sar_Width;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Sei;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the plane height of a multi-planar (YUV) video bytebuffer layout.

  Slice height (or plane height/vertical stride) is the number of rows that must be skipped
  to get from the top of the Y plane to the top of the U plane in the bytebuffer. In essence
  the offset of the U plane is sliceHeight * stride. The height of the U/V planes
  can be calculated based on the color format, though it is generally undefined
  and depends on the device and release.
  The associated value is an integer, representing the number of rows.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Slice_Height;

/*!
  The associated value is a long integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Target_Time;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Temporal_Layer_Count;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Temporal_Layer_Id;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Text_Format_Data;

/*!
  The associated value is an \ref MLMediaFormatByteArray.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Thumbnail_CSD_Hevc;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Thumbnail_Height;

/*!
  The associated value is a long integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Thumbnail_Time;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Thumbnail_Width;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the height (in pixels) of each tile of the content in a
  \ref MIMETYPE_IMAGE_ANDROID_HEIC track. The associated value is an integer.

  Refer to \ref MIMETYPE_IMAGE_ANDROID_HEIC on decoding instructions of such tracks.

  \see #MLMediaFormat_Key_Tile_Width
  \see #MLMediaFormat_Key_Grid_Rows
  \see #MLMediaFormat_Key_Grid_Columns
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Tile_Height;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the width (in pixels) of each tile of the content in a
  \ref MIMETYPE_IMAGE_ANDROID_HEIC track. The associated value is an integer.

  Refer to \ref MIMETYPE_IMAGE_ANDROID_HEIC on decoding instructions of such tracks.

  \see #MLMediaFormat_Key_Tile_Height
  \see #MLMediaFormat_Key_Grid_Rows
  \see #MLMediaFormat_Key_Grid_Columns
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Tile_Width;

/*!
  The associated value is a long integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Time_Us;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The title of the media.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Title;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing a unique ID for the content of a media track.

  <p>This key is used by \ref MLMediaExtractor. Some extractors provide multiple encodings
  of the same track (e.g. float audio tracks for FLAC and WAV may be expressed as two
  tracks via MediaExtractor: a normal PCM track for backward compatibility, and a float PCM
  track for added fidelity. Similarly, Dolby Vision extractor may provide a baseline SDR
  version of a DV track.) This key can be used to identify which MediaExtractor tracks refer
  to the same underlying content.
  </p>

  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Track_Id;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Track_Index;

/*!
  The associated value is an integer.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Valid_Samples;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing metadata. The year the media was created or published as a long.

  The associated value is a string.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Year;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing for selecting the DRC effect type for MPEG-D DRC.

  The supported values are defined in ISO/IEC 23003-4:2015 and are described as follows:
  <table>
  <tr><th>Value</th><th>Effect</th></tr>
  <tr><th>-1</th><th>Off</th></tr>
  <tr><th>0</th><th>None</th></tr>
  <tr><th>1</th><th>Late night</th></tr>
  <tr><th>2</th><th>Noisy environment</th></tr>
  <tr><th>3</th><th>Limited playback range</th></tr>
  <tr><th>4</th><th>Low playback level</th></tr>
  <tr><th>5</th><th>Dialog enhancement</th></tr>
  <tr><th>6</th><th>General compression</th></tr>
  </table>
  <p>The value -1 (Off) disables DRC processing, while loudness normalization may still be
  active and dependent on KEY_AAC_DRC_TARGET_REFERENCE_LEVEL.<br>
  The value 0 (None) automatically enables DRC processing if necessary to prevent signal
  clipping<br>
  The value 6 (General compression) can be used for enabling MPEG-D DRC without particular
  DRC effect type request.<br>
  The default DRC effect type is 3 ("Limited playback range") on mobile devices.
  <p>This key is only used during decoding.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_AAC_DRC_Effect_Type;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the desired encoding quality.

  The associated value is an integer.  This key is only supported for encoders
  that are configured in constant-quality mode.  These values are device and
  codec specific, but lower values generally result in more efficient
  (smaller-sized) encoding.

  \see MediaCodecInfo.EncoderCapabilities#getQualityRange()
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Quality;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief An optional key describing the maximum number of non-display-order coded frames.

  This is an optional parameter that applies only to video encoders. Application should
  check the value for this key in the output format to see if codec will produce
  non-display-order coded frames. If encoder supports it, the output frames' order will be
  different from the display order and each frame's display order could be retrieved from
  \ref MLMediaCodec.BufferInfo#presentationTimeUs . Before API level 27, application may
  receive non-display-order coded frames even though the application did not request it.
  Note: Application should not rearrange the frames to display order before feeding them
  to \ref MLMediaMuxer#writeSampleData .
  <p>
  The default value is 0.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Output_Reorder_Depth;

/*!
  The associated value is an integer. The value should be 0 or 1.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Is_Timed_Text;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the system id of the conditional access system used to scramble
  a media track.

  <p>
  This key is set by \ref MLMediaExtractor if the track is scrambled with a conditional
  access system, regardless of the presence of a valid \ref MediaCas object.
  <p>
  The associated value is an integer.
  \hide
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Ca_System_Id;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the \ref MediaCas.Session object associated with a media track.

  <p>
  This key is set by \ref MLMediaExtractor if the track is scrambled with a conditional
  access system, after it receives a valid \ref MediaCas} object.
  <p>
  The associated value is a ByteBuffer.
  \hide
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Ca_Session_Id;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key describing the private data in the CA_descriptor associated with a media track.

  <p>
  This key is set by \ref MLMediaExtractor if the track is scrambled with a conditional
  access system, before it receives a valid \ref MediaCas object.
  <p>
  The associated value is a ByteBuffer.
  \hide
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Ca_Private_Data;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key prefix used together with a \ref MLMediaCodecBitrateMode
  feature name describing a required or optional feature for a codec capabilities
  query.

  The associated value is an integer, where non-0 value means the feature is
  requested to be present, while 0 value means the feature is requested to be not
  present.
  \see MLMediaCodecList#findDecoderForFormat
  \see MLMediaCodecList#findEncoderForFormat
  \see MLMediaCodecBitrateMode#isFormatSupported
  \hide
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaFormatKey MLMediaFormat_Key_Feature_;


/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a video format object.

  \param[in] mime_type Mime type of the content.
  \param[in] width Width of the content in pixels.
  \param[in] height Height of the content in pixels.
  \param[out] out_handle A handle to the created video format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatCreateVideo(const char *mime_type, int width, int height, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a audio format object.

  \param[in] mime_type Mime type of the content.
  \param[in] sample_rate Sample rate of the content.
  \param[in] channel_count Number of audio channels.
  \param[out] out_handle A handle to the created audio format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatCreateAudio(const char *mime_type, int sample_rate, int channel_count, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a subtitle format object.

  \param[in] mime_type Mime type of the content.
  \param[in] language Language of the content, using either ISO 639-1 or
             639-2/T codes. Specify null or "und" if language information
             is only included in the content (This will also work if there
             are multiple language tracks in the content).
  \param[out] out_handle A handle to the created subtitle format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatCreateSubtitle(const char *mime_type, const char *language, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create an empty format object.

  \apilevel 9

  \param[out] out_handle A handle to the created empty format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_InvalidParam If one of parameters is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatCreate(MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a copy of the format handle provided.

  This can be particularly useful to persist the media format handle/object that
  was received through the callbacks (as life cycle of those media format objects
  are with in the callback context only).

  The API call to make a copy ensures that the copied object exists until released with #MLMediaFormatDestroy call.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[out] out_handle A handle to the created copy of the format object.
              If there is an error during creation, it will
              return #ML_INVALID_HANDLE.


  \retval MLResult_AllocFailed If handle cannot be allocated.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_InvalidParam If one of parameters is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatCreateCopy(MLHandle handle, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Destroy a \ref MLMediaFormat object.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.

  \retval MLResult_InvalidParam If handle is invalid.
  \retval MLResult_Ok If \ref MLMediaCodec object was successfully destroyed.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
 */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatDestroy(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the human readable representation of the format.

  User shall allocate at least #MAX_FORMAT_STRING_SIZE bytes of memory for
  storing the output format string. The format string contains
  a list of key-value pairs, which can be extracted individually
  via the suitable "GetKeyValue" APIs.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[out] out_string Buffer to which stringify the media format. Shouldn't be NULL.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatObjectToString(MLHandle handle, char *out_string);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the value of an integer key.

  For example, use #MLMediaFormat_Key_Frame_Rate key to get
  the framerate of a video track.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatGetKeyValueInt32(MLHandle handle, MLMediaFormatKey name, int32_t *out_key);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the value of a long key.

  For example, use MLMediaFormat_Key_Duration key to get
  duration of a track.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatGetKeyValueInt64(MLHandle handle, MLMediaFormatKey name, int64_t *out_key);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the value of an float key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_key Value of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatGetKeyValueFloat(MLHandle handle, MLMediaFormatKey name, float *out_key);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the size of a key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_size Size of the key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatGetKeySize(MLHandle handle, MLMediaFormatKey name, size_t *out_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the value of a string key.

  User shall allocate at least #MAX_KEY_STRING_SIZE bytes of memory for
  storing the output key string.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_string Pointer to the C-string representation of the string key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatGetKeyString(MLHandle handle, MLMediaFormatKey name, char *out_string);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Obtain the value of a ByteBuffer key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[out] out_buffer Pointer to byte buffer that needs to be allocated and copied to.
              To free/release, call MLMediaFormatKeyByteBufferRelease().

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NameNotFound If name is not one of the media format key name.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatGetKeyByteBuffer(MLHandle handle, MLMediaFormatKey name, MLMediaFormatByteArray *out_buffer);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release the ByteBuffer acquired by MLMediaFormatGetKeyByteBuffer.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] buffer Byte buffer that needs to be released.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatKeyByteBufferRelease(MLHandle handle, MLMediaFormatByteArray *buffer);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the value of an integer key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatSetKeyInt32(MLHandle handle, MLMediaFormatKey name, int32_t key_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the value of a long key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatSetKeyInt64(MLHandle handle, MLMediaFormatKey name, int64_t key_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the value of a float key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value Key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatSetKeyFloat(MLHandle handle, MLMediaFormatKey name, float key_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the size of a key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_size Key size.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatSetKeySize(MLHandle handle, MLMediaFormatKey name, size_t key_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the value of a string key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] key_value C-string representation of key value.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
 */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatSetKeyString(MLHandle handle, MLMediaFormatKey name, const char *key_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the value of a ByteBuffer key.

  \param[in] handle #MLHandle to the \ref MLMediaFormat object.
  \param[in] name C-string representation of the key.
             Must be one of the #MLMediaFormatKey tags defined above.
  \param[in] buffer Pointer to the data buffer for the corresponding key.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaFormatSetKeyByteBuffer(MLHandle handle, MLMediaFormatKey name, const MLMediaFormatByteArray *buffer);

/*! \} */

ML_EXTERN_C_END
