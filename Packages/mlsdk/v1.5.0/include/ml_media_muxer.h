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
#include "ml_types.h"

ML_EXTERN_C_BEGIN

/*!
  \defgroup MediaRecorder Media Recorder
  \addtogroup MediaRecorder
  \sharedobject media_muxer.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaMuxer

  \brief APIs for MediaMuxer to facilitate muxing of elementary streams.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*!
  \brief Output formats for MediaMuxer.

  This enumarates list of all the possibly supported output formats for the muxer
  across all the releases/Platform.

  Use #MLMediaMuxerGetSupportedOutputFormats to query for all supported Output formats on the Platform.

  \apilevel 20
*/
typedef enum MLMediaMuxerOutputFormat {
  /*! MP4 format. */
  MLMediaMuxerOutputFormat_MPEG4 = 0,
  /*! VP8/VORBIS data in a WEBM container. */
  MLMediaMuxerOutputFormat_WEBM  = 1,
  /*! 3gpp format. */
  MLMediaMuxerOutputFormat_3GPP  = 2,
  /*! HEIC data in a HEIF container. */
  MLMediaMuxerOutputFormat_HEIF  = 3,
  /*! Opus data in a OGG container. */
  MLMediaMuxerOutputFormat_OGG   = 4,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaMuxerOutputFormat_Ensure32Bits = 0x7FFFFFFF
} MLMediaMuxerOutputFormat;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Data type that encapsulates sample data to be written in to MLMediaMuxer.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaMuxerSampleData {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief The track index number, to which to write the sample data into.
    This should be one of the number returned by #MLMediaMuxerAddTrack.
  */
  size_t track_index;
  /*! Pointer to the sample buffer/data. */
  const uint8_t *buffer;
  /*! Size of the sample buuffer/data. */
  size_t size;
  /*! The buffer's time stamp in microseconds. */
  int64_t time_us;
  /*!
    \brief The flag about the data. The following flags are supported:
          #MLMediaCodecBufferFlag_KeyFrame: if its a sync/key frame.
          #MLMediaCodecBufferFlag_EOS: To notify end of stream.
          #MLMediaCodecBufferFlag_MuxerData: if it is muxer data (only Exif data block is supported).
  */
  uint32_t flags;
} MLMediaMuxerSampleData;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initializes MLMediaMuxerSampleData with default values.

  \param[in,out] inout_sampledata SampleData defined by #MLMediaMuxerSampleData that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaMuxerSampleDataInit(MLMediaMuxerSampleData *inout_sampledata) {
  if (inout_sampledata) {
    inout_sampledata->version = 1;
    inout_sampledata->track_index = 0;
    inout_sampledata->buffer = NULL;
    inout_sampledata->size = 0;
    inout_sampledata->time_us = 0;
    inout_sampledata->flags = 0;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a \ref MLMediaMuxer instance.

  \apilevel 20

  \param[out] out_handle Upon successful return will point to handle to the created \ref MLMediaMuxer.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed \ref MLMediaMuxer object creation failed with resource allocation failure.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaMuxer object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerCreate(MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release the \ref MLMediaMuxer instance.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaMuxer object was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerRelease(MLHandle media_muxer);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get a list of all the supported Media Muxer Output Formats on the Platform.

  User doesn't own the memory/buffer returned from this API and MUST NOT be freeing or releasing
  the out_format_list.

  \apilevel 20

  \param[in]  media_muxer Handle to the MLMediaMuxer instance.
  \param[out] out_format_list Pointer to MLMediaMuxerOutputFormat. This should not be NULL.
  \param[out] out_format_list_size The size of the returned out_format_list. This should not be NULL.

  \retval MLResult_InvalidParam If one of the parameters are invalid.
  \retval MLResult_Ok Successfully retrieved all the supported Output Formats.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerGetSupportedOutputFormats(MLHandle media_muxer, const MLMediaMuxerOutputFormat *out_format_list[], size_t *out_format_list_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Get a list of all the supported mime-types for a given Media Muxer Output Format on the Platform.

  User doesn't own the memory/buffer returned from this API and MUST NOT be freeing or releasing
  the out_mime_list.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.
  \param[in] format The Output format, to which we would like to know all the supported mime-types.
             The format should be one returned from #MLMediaMuxerGetSupportedOutputFormats.
  \param[out] out_mime_list Pointer to array of mime-type (char array). This should not be NULL.
  \param[out] out_mime_list_size The size of the returned out_mime_list. This should not be NULL.

  \retval MLResult_InvalidParam If one of the parameters is invalid.
  \retval MLResult_Ok Successfully retrieved all the supported Output Formats.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerGetSupportedMimes(MLHandle media_muxer, MLMediaMuxerOutputFormat format, const char *const *out_mime_list[], size_t *out_mime_list_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Configure the \ref MLMediaMuxer for a given Output format with output path.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.
  \param[in] format The format of the muxed output media file.
  The format should be one returned from #MLMediaMuxerGetSupportedOutputFormats.
  \param[in] path The linux-style path for the output media file. This value cannot be empty or NULL.

  \retval MLResult_AllocFailed Failed to configure the \ref MLMediaMuxer object with resource allocation failure.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaMuxer object was configured successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaResult_Unsupported If the format is not supported.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerConfigure(MLHandle media_muxer, MLMediaMuxerOutputFormat format, const char *path);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Add a track with given format information.

  This should be called before #MLMediaMuxerStart() and after #MLMediaMuxerConfigure.

  The following media format keys are supported for Audio/Video and Metadata tracks.

  ================================================================================================
  | Audio Track                     | Video Track                       | Metadata Track         |
  ================================================================================================
  | MLMediaFormat_Key_Mime          | MLMediaFormat_Key_Mime            | MLMediaFormat_Key_Mime |
  | MLMediaFormat_Key_Sample_Rate   | MLMediaFormat_Key_Width           |                        |
  | MLMediaFormat_Key_Channel_Count | MLMediaFormat_Key_Height          |                        |
  | MLMediaFormat_Key_CSD0          | MLMediaFormat_Key_Bt_Rate         |                        |
  | MLMediaFormat_Key_CSD1          | MLMediaFormat_Key_Frame_Rate      |                        |
  |                                 | MLMediaFormat_Key_Color_Range     |                        |
  |                                 | MLMediaFormat_Key_Color_Standard  |                        |
  |                                 | MLMediaFormat_Key_Color_Transfer  |                        |
  |                                 | MLMediaFormat_Key_HDR_Static_Info |                        |
  |                                 | MLMediaFormat_Key_CSD0            |                        |
  |                                 | MLMediaFormat_Key_CSD1            |                        |
  ================================================================================================

  #MLMediaMuxerGetSupportedMimes can be used to query for all the supported MLMediaFormat_Key_Mime
  for a given Output Format.

  While MLMediaFormat_Key_Mime is must for all tracks, some of the keys aren't mandatory.
  For Audio track, MLMediaFormat_Key_SAMPLE_RATE and MLMediaFormat_Key_CHANNEL_COUNT is must.
  For Video track, MLMediaFormat_Key_WIDTH anb MLMediaFormat_Key_HEIGHT are must.

  Requierment of providing csd (Codec Specific Data) through MediaFormat is optional for
  some audio/video mimes where as it is mandatory for some other ones (for example vorbis).

  With mp4 container following audio/video and metadata mime types can be supported.

  ===============================================================
  | Audio Mimes      | Video Mimes     | Metadata Mimes         |
  ===============================================================
  | audio/3gpp       | video/3gpp      | application/           |
  | audio/mp4a-latm  | video/mp4v-es   | image/vnd.android.heic |
  | audio/amr-wb     | video/avc       |                        |
  |                  | video/hevc      |                        |
  ===============================================================

  With Webm container following audio/video mime types can be supported.

  ============================================
  | Audio Mimes      | Video Mimes           |
  ============================================
  | audio/vorbis     | video/x-vnd.on2.vp8   |
  | audio/opus       | video/x-vnd.on2.vp9   |
  ============================================

  With Ogg container, only supported mime is "audio/opus".

  If a mime passed through the MLMediaFormat is not supported, it will return MLMediaResult_Unsupported.

  \apilevel 20

  \param[in]  media_muxer Handle to the MLMediaMuxer instance.
  \param[in]  media_format #MLHandle to the \ref MLMediaFormat that contains the track's format.
  \param[out] out_track_index Upon successful return, this will conatin the index of the track added.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If the operation completes successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation The operation is invalid.
  \retval MLMediaResult_Unsupported If one of the keys in the format is not supported.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerAddTrack(MLHandle media_muxer, MLHandle media_format, size_t *out_track_index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set the orientation hint for output video playback.

  This should be called before #MLMediaMuxerStart() and after #MLMediaMuxerConfigure.

  Calling this method will not rotate the video frame when muxer is generating the file,
  but add a composition matrix containing the rotation angle in the output video
  if the output format is MLMediaMuxerOutputFormat_MPEG4 so that a video player can choose
  the proper orientation for playback.

  Note that some video players may choose to ignore the composition matrix
  in a video during playback. By default, the rotation degree is 0.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.
  \param[in] degrees The rotation degrees. It has to be either 0, 90, 180 or 270.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If the operation completes successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation The operation is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerSetOrientationHint(MLHandle media_muxer, int32_t degrees);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set and store the geodata (latitude and longitude) in the output file.

  This should be called before #MLMediaMuxerStart() and after #MLMediaMuxerConfigure.

  The geodata is stored in udta box if the output format is MLMediaMuxerOutputFormat_MPEG4,
  and is ignored for other output formats.
  The geodata is stored according to ISO-6709 standard.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.
  \param[in] latitude The latitude in degree. Its value must be in the range [-90, 90].
  \param[in] longitude The longitude in degree. Its value must be in the range [-180, 180].

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If the operation completes successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation The operation is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerSetLocation(MLHandle media_muxer, float latitude, float longitude);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Start muxing.

  Make sure all the tracks have been added (#MLMediaMuxerAddTrack) before calling this.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If the operation completes successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation The operation is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerStart(MLHandle media_muxer);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Writes an encoded sample into the muxer.

  The application needs to make sure that the samples are written into the right tracks.
  Also, it needs to make sure the samples for each track are written in chronological order
  (e.g. in the order they are provided by the encoder).

  For MPEG4 media format, the duration of the last sample in a track can be set by passing
  an additional empty buffer) with #MLMediaCodecBufferFlag_EOS flag and a suitable
  presentation timestamp set in time_us (of MLMediaMuxerSampleData structure)
  as the last sample of that track.
  This last sample's presentation timestamp shall be a sum of the presentation timestamp
  and the duration preferred for the original last sample.
  If no explicit END_OF_STREAM sample was passed, then the duration of the last sample
  would be the same as that of the sample before that.

  The buffer can be reused once this method returns.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.
  \param[in] data The sample data to be written encapsulated in #MLMediaMuxerSampleData.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If the operation completes successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation The operation is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerWriteSampleData(MLHandle media_muxer, const MLMediaMuxerSampleData *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Stop muxing.

  Once the muxer stops, it can not be restarted.

  \apilevel 20

  \param[in] media_muxer Handle to the MLMediaMuxer instance.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok If the operation completes successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation The operation is invalid.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaMuxerStop(MLHandle media_muxer);

/*! \} */

ML_EXTERN_C_END
