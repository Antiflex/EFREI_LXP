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
  \defgroup MediaRecorder Media Recorder
  \addtogroup MediaRecorder
  \sharedobject media_recorder.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
            https://developer.android.com/reference/android/media/MediaRecorder

  \brief APIs for video and auido recording.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*! Media recorder video source. */
typedef enum MLMediaRecorderVideoSource {
  /*! Camera video source. */
  MLMediaRecorderVideoSource_Camera       = 1,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderVideoSource_Ensure32Bits = 0x7FFFFFFF
} MLMediaRecorderVideoSource;

/*! Media recorder audio source. */
typedef enum MLMediaRecorderAudioSource {
  /*! Recording voice. */
  MLMediaRecorderAudioSource_Voice        = 0,
  /*! Recording ambient sounds. */
  MLMediaRecorderAudioSource_World        = 1,
  /*! Recording digital sounds. */
  MLMediaRecorderAudioSource_Virtual      = 2,
  /*! Mixed reality mode: digital + ambient. */
  MLMediaRecorderAudioSource_Mixed        = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderAudioSource_Ensure32Bits = 0x7FFFFFFF
} MLMediaRecorderAudioSource;

/*! Media recorder events. */
typedef enum MLMediaRecorderEvent {
  /*! Media recorder error. */
  MLMediaRecorderEvent_Error             = 1,
  /*! Media recorder info. */
  MLMediaRecorderEvent_Info              = 2,
  /*! Media recorder track error. */
  MLMediaRecorderTrackEvent_Error        = 100,
  /*! Media recorder track info. */
  MLMediaRecorderTrackEvent_Info         = 101,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderTrackEvent_Ensure32Bits = 0x7FFFFFFF
} MLMediaRecorderEvent;

typedef enum MLMediaRecorderInfo {
  MLMediaRecorderInfo_Unknown                 = 1,
  /*! Max duration of the clip is reached. */
  MLMediaRecorderInfo_MaxDurationReached      = 800,
  /*! Max file size is reached. */
  MLMediaRecorderInfo_MaxFileSizeReached      = 801,
  /*! Max file size is approaching. */
  MLMediaRecorderInfo_MaxFileSizeApproaching  = 802,
  /*! Next output file has started. */

  /*! The info about completion status. */
  MLMediaRecorderTrackInfo_CompletionStatus   = 1000,
  /*! The info about progress in time. */
  MLMediaRecorderTrackInfo_ProgressInTime     = 1001,
  /*! Track info. */
  MLMediaRecorderTrackInfo_Type               = 1002,
  /*! The info about track duration. */
  MLMediaRecorderTrackInfo_DurationMs         = 1003,
  /*! The time to measure the max chunk duration. */
  MLMediaRecorderTrackInfo_MaxChunkDurationMs = 1004,
  /*! The info about encoded frames. */
  MLMediaRecorderTrackInfo_EncodedFrames      = 1005,
  /*! The time to measure how well the audio and video track data interleaved. */
  MLMediaRecorderTrackInfo_InterChunkTimeUs   = 1006,
  /*! The time to measure system response. */
  MLMediaRecorderTrackInfo_InitialDelayMs     = 1007,
  /*!  The time used to compensate for initial A/V sync. */
  MLMediaRecorderTrackInfo_StartOffsetMs      = 1008,
  /*! Total number of bytes of the media data. */
  MLMediaRecorderTrackInfo_DataKBytes         = 1009,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderTrackInfo_Ensure32Bits       = 0x7FFFFFFF
} MLMediaRecorderInfo;

typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaRecorderOnInfo {
  /*! Holds valid track id only for track specific info (returned via on_track_info callback.).
      Holds 0 for the generic info (returned via on_info callback).
      Refer to MLMediaRecorderInfo for the info. */
  uint32_t track_id;
  /*! The info of MLMediaRecorderInfo. */
  MLMediaRecorderInfo info;
  /*! The extra info. */
  int extra;
  /*! User data as passed to MLMediaRecorderSetEventCallbacks. */
  void *data;
} MLMediaRecorderOnInfo;

/*!
  \brief Video recorder error types.
*/
typedef enum MLMediaRecorderError {
  MLMediaRecorderError_Unknown           = 1,
  MLMediaRecorderError_ServerDied        = 2,

  MLMediaRecorderTrackError_General      = 100,
  MLMediaRecorderError_VideoNoSyncFrame  = 200,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderTrackError_Ensure32Bits = 0x7FFFFFFF
} MLMediaRecorderError;

typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaRecorderOnError {
  /*! Holds valid track id only for track specific errors (returned via on_track_error callback).
      Holds 0 for the generic errors (returned via on_error callback).
      Refer to MLMediaRecorderError for the errors. */
  uint32_t track_id;
  /*! The error of MLMediaRecorderError. */
  MLMediaRecorderError error;
  /*! The extra info. */
  int extra;
  /*! User data as passed to MLMediaRecorderSetEventCallbacks. */
  void *data;
} MLMediaRecorderOnError;

typedef enum MLMediaRecorderOutputFormat {
  MLMediaRecorderOutputFormat_DEFAULT            = 0,
  /*! 3gpp format. */
  MLMediaRecorderOutputFormat_THREE_GPP          = 1,
  /*! MP4 format. */
  MLMediaRecorderOutputFormat_MPEG_4             = 2,
  /*! AMR NB. */
  MLMediaRecorderOutputFormat_AMR_NB             = 3,
  /*! AMR WB. */
  MLMediaRecorderOutputFormat_AMR_WB             = 4,
  /*! AAC_ADIF. */
  MLMediaRecorderOutputFormat_AAC_ADIF           = 5,
  /*! AAC_ADTS. */
  MLMediaRecorderOutputFormat_AAC_ADTS           = 6,
  /*! Stream over a socket, limited to a single stream. */
  MLMediaRecorderOutputFormat_RTP_AVP            = 7,
  /*! H.264/AAC data encapsulated in MPEG2/TS. */
  MLMediaRecorderOutputFormat_MPEG2TS            = 8,
  /*! VP8/VORBIS data in a WEBM container. */
  MLMediaRecorderOutputFormat_WEBM               = 9,
  /*! HEIC data in a HEIF container. */
  MLMediaRecorderOutputFormat_HEIF               = 10,
  /*! Opus data in a OGG container. */
  MLMediaRecorderOutputFormat_OGG                = 11,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderOutputFormat_Ensure32Bits        = 0x7FFFFFFF
} MLMediaRecorderOutputFormat;

typedef enum MLMediaRecorderVideoEncoder {
  MLMediaRecorderVideoEncoder_Default      = 0,
  /*! H263. This format has support for software encoder. */
  MLMediaRecorderVideoEncoder_H263         = 1,
  /*! H264. This format has support for hardware encoder. */
  MLMediaRecorderVideoEncoder_H264         = 2,
  /*! MPEG4 SP. This format has support for software encoder. */
  MLMediaRecorderVideoEncoder_MPEG_4_SP    = 3,
  /*! VP8. This format has support for software encoder. */
  MLMediaRecorderVideoEncoder_VP8          = 4,
  /*! HEVC. This format has support for hardware encoder. */
  MLMediaRecorderVideoEncoder_HEVC         = 5,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderVideoEncoder_Ensure32Bits = 0x7FFFFFFF
} MLMediaRecorderVideoEncoder;

typedef enum MLMediaRecorderAudioEncoder {
  MLMediaRecorderAudioEncoder_Default      = 0,
  /*! AMR NB. */
  MLMediaRecorderAudioEncoder_AMR_NB       = 1,
  /*! AMR WB. */
  MLMediaRecorderAudioEncoder_AMR_WB       = 2,
  /*! AAC. */
  MLMediaRecorderAudioEncoder_AAC          = 3,
  /*! HE AAC. */
  MLMediaRecorderAudioEncoder_HE_AAC       = 4,
  /*! AAC ELD. */
  MLMediaRecorderAudioEncoder_AAC_ELD      = 5,
  /*! Vorbis. */
  MLMediaRecorderAudioEncoder_VORBIS       = 6,
  /*! Opus. */
  MLMediaRecorderAudioEncoder_OPUS         = 7,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaRecorderAudioEncoder_Ensure32Bits = 0x7FFFFFFF
} MLMediaRecorderAudioEncoder;

typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaRecorderEventCallbacks {
  uint32_t version;
  /*!
    \brief MediaRecorder received a general info/warning message.

    \param[in] media_recorder Handle is a MediaRecorder instance on which callback was set.
    \param[out] pointer to MLMediaRecorderOnInfo.
  */
  void (*on_info)(MLHandle media_recorder, const MLMediaRecorderOnInfo *info);

  /*!
    \brief MediaRecorder received a track-related info/warning message.

    \param[in] media_recorder Handle is a MediaRecorder instance on which callback was set.
    \param[out] track_info pointer to MLMediaRecorderOnInfo.
  */
  void (*on_track_info)(MLHandle media_recorder, const MLMediaRecorderOnInfo *track_info);
  /*!
    \brief MediaRecorder received a general error message.

    \param[in] media_recorder Handle is a MediaRecorder instance on which callback was set.
    \param[out] pointer to MLMediaRecorderOnError.
  */
  void (*on_error)(MLHandle media_recorder, const MLMediaRecorderOnError *error);
  /*!
    \brief MediaRecorder received a track-related error message.

    \param[in] media_recorder Handle is a MediaRecorder instance on which callback was set.
    \param[out] pointer to MLMediaRecorderError.
  */
  void (*on_track_error)(MLHandle media_recorder, const MLMediaRecorderOnError *track_error);
} MLMediaRecorderEventCallbacks;

/*!
  \brief Initializes MediaRecorderEventCallbacks with default values.

  \param[in,out] inout_callbacks Media Recorder Callback structure defined by MLMediaRecorderEventCallbacks that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaRecorderEventCallbacksInit(MLMediaRecorderEventCallbacks *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 1;
    inout_callbacks->on_info = NULL;
    inout_callbacks->on_error = NULL;
    inout_callbacks->on_track_error = NULL;
    inout_callbacks->on_track_info = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new MediaRecorder object.

  \apilevel 20

  \param[out] out_handle Handle to the new MediaRecorder object created. Only valid if result is MLResult_Ok.

  \retval MLResult_AllocFailed Could not allocate internal MediaRecorder.
  \retval MLResult_InvalidParam Passed out_handle was NULL.
  \retval MLResult_Ok MediaRecorder was created successfully.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderCreate(MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Destroy a MediaRecorder object.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder object to destroy.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok MediaRecorder was destroyed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderDestroy(MLHandle media_recorder);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Pass in the file descriptor of the file to be written.

  Call this after MLMediaRecorderSetOutputFormat() but before MLMediaRecorderprepare().

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder instance.
  \param[in] fd The file descriptor for the file you want to write into.

  \retval MLResult_InvalidParam Passed fd does no refer to a valid,open file descriptor or 'media_recorder' was NULL.
  \retval MLResult_Ok Data source was correctly set to passed file descriptor.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetOutputFileForFD(MLHandle media_recorder, int32_t fd);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the path of the output file to be produced.

  Call this after MLMediaRecorderSetOutputFormat() but before MLMediaRecorderprepare().

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder instance.
  \param[in] path The linux-style path of the file. Must be a valid and existing path.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Data source was correctly set to passed file path.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetOutputFileForPath(MLHandle media_recorder, const char *path);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the MediaRecorderListener object that will receive MediaRecorder notifications.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] callbacks Set of event callbacks. Can be set to NULL to unset
             the callbacks altogether.
  \param[in] data Custom data to be returned when any callback is fired.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok The specified callbacks were successfully set/unset.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetEventCallbacks(MLHandle media_recorder, const MLMediaRecorderEventCallbacks *callbacks, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets MediaRecorder default video source.

  Cannot be called twice (without calling MLMediaRecorderReset() in between) because it triggers internal initialization.

  Current implementation supports only camera as video source from MediaRecorderVideoSource.

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_video_source Type of the MediaRecorderVideoSource.

  \retval MLResult_InvalidParam Media recorder handle was not found or in_video_source is not MLMediaRecorderVideoSource_Camera.
  \retval MLResult_Ok Set default video source successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetVideoSource(MLHandle media_recorder, MLMediaRecorderVideoSource in_video_source);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set MediaRecorder audio source.

  Cannot be called twice (without calling MLMediaRecorderReset() in between) because it triggers internal initialization.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_audio_source Type of the MediaRecorderAudioSource.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Set audio source successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions android.permission.RECORD_AUDIO (protection level: dangerous)
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetAudioSource(MLHandle media_recorder, MLMediaRecorderAudioSource in_audio_source);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the format of the output file produced during recording.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_format Type of the MLMediaRecorderOutputFormat.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Set output format successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetOutputFormat(MLHandle media_recorder, MLMediaRecorderOutputFormat in_format);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the video encoder to be used for recording.

  If this method is not called, the output file will not contain an video track.
  Call this after MLMediaRecorderSetOutputFormat() and before MLMediaRecorderPrepare().

  The video source is always set to camera by default.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_video_encoder Type of the VideoEncoder to use.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Set video encoder successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaResult_InvalidCodecParam requested width height is not supported.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetVideoEncoder(MLHandle media_recorder, MLMediaRecorderVideoEncoder in_video_encoder);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the audio encoder to be used for recording.

  If this method is not called, the output file will not contain an audio track.
  Call this after MLMediaRecorderSetOutputFormat() and before MLMediaRecorderPrepare().

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_audio_encoder Type of the MLMediaRecorderAudioEncoder to use.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Set audio encoder successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetAudioEncoder(MLHandle media_recorder, MLMediaRecorderAudioEncoder in_audio_encoder);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the maximum duration (in ms) of the recording session.

  Call this after MLMediaRecorderSetOutputFormat() and before MLMediaRecorderPrepare().
  After recording reaches the specified duration, a notification
  will be sent via the callback with a MLMediaRecorderInfo code of
  MLMediaRecorderInfo_MaxDurationReached and recording will be stopped.
  Stopping happens asynchronously, there is no guarantee that the recorder
  will have stopped by the time the listener is notified.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_max_duration_msec The maximum duration in ms (if zero or negative, disables the duration limit).

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Max duration was successfully set.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetMaxDuration(MLHandle media_recorder, int32_t in_max_duration_msec);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the maximum filesize (in bytes) of the recording session.

  \apilevel 20

  Call this after MLMediaRecorderSetOutputFormat() and before MLMediaRecorderPrepare().
  After recording reaches the specified filesize, a notification
  will be sent via the callback with a MLMediaRecorderInfo code of
  MLMediaRecorderInfo_MaxFileSizeReached and recording will be stopped.
  Stopping happens asynchronously, there is no guarantee that the recorder
  will have stopped by the time the listener is notified.

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_max_file_size MaxFilesizeBytes The maximum filesize in bytes (if zero or negative, disables the limit).

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Max file size was successfully set.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetMaxFileSize(MLHandle media_recorder, int64_t in_max_file_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the GEO location for recording.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] in_latitude10000 The 10000 multiplies latitude of location.
  \param[in] in_longitude10000 The 10000 multiplies longitude of location.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok GEO location was successfully set.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderSetGeoLocation(MLHandle media_recorder, int64_t in_latitude10000, int64_t in_longitude10000);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Prepares the recorder to begin capturing and encoding data for input mediaformat.

  This method must be called after setting up the desired audio and video sources, encoders, but before start.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.
  \param[in] format #MLHandle to the MediaFormat.
              MediaFormat object can be created with:
                - #MLMediaFormatCreateVideo if we want to record video only.
                - #MLMediaFormatCreateAudio if we want to record audio only.
                - #MLMediaFormatCreate if we want to record both video and audio.

              Following parameters can be added to MediaFormat handle.
              Audio Specific parametes:
                - #MLMediaFormat_Key_Bit_Rate for audio "bitrate".
                - #MLMediaFormat_Key_Channel_Count for audio "channel-count".
                - #MLMediaFormat_Key_Sample_Rate for audio "sample-rate".

              Video Specific parametes:
                - #MLMediaFormat_Key_Width for video frame "width".
                - #MLMediaFormat_Key_Height for video frame "height".
                - #MLMediaFormat_Key_Frame_Rate for video "frame-rate".
                - #MLMediaFormat_Key_Parameter_Video_Bitrate for "video-bitrate".
                - #MLMediaFormat_Key_I_Frame_Interval for "i-frame-interval".

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Recorder was prepared successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderPrepare(MLHandle media_recorder, MLHandle format);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Begins capturing and encoding data to the specified file.

  Call this after MLMediaRecorderPrepare(). The apps should not start another recording session during recording.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Recorder was started successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderStart(MLHandle media_recorder);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets the input surface to record from when using SURFACE video source.

  May only be called after MLMediaRecorderPrepare. Frames rendered to the producer
  before MLMediaRecorderStart() is called will be discarded.

  When using an input surface, there are no accessible input buffers, as buffers are automatically
  passed from the other modules to this surface.

  The returned input surface can also be passed as a destination surface to
    - a video/mixed reality video capture session when calling MLCameraPrepareCapture().

  Captured raw video frames will be consumed directly as input to an encoder without copying.
  Caller of this API should release the surface using MLMediaRecorderReleaseInputSurface()
  on the Surface handle after usage.

  \apilevel 20

  \param[in] media_recorder Handle to the Media Recorder instance.
  \param[out] out_input_surface_handle Handle to the created input native surface.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_OK input surface was correctly returned.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderGetInputSurface(MLHandle media_recorder, MLHandle *out_input_surface_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns the maximum absolute amplitude that was sampled since the last call to this method.

  Call this only after the MLMediaRecorderSetAudioSource().

  \apilevel 20

  \param[in] media_recorder Handle to the MediaRecorder.
  \param[in,out] inout_max_amp The maximum absolute amplitude measured since the last call, or 0 when called for the first time.

  \retval MLResult_InvalidParam Mmedia recorder handle was not found.
  \retval MLResult_Ok Maximum amplitude was returned successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderGetMaxAmplitude(MLHandle media_recorder, int32_t *inout_max_amp);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Stops recording.

  Call this after MLMediaRecorderStart(). Once recording is stopped,
  you will have to configure it again as if it has just been constructed.

  \apilevel 20

  \param[in] media_recorder Handle to the MediaRecorder.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Recorder was stopped successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderStop(MLHandle media_recorder);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release the surface that was returned by MLMediaRecorderGetInputSurface.

  \apilevel 20

  \param[in] media_recorder Handle to the MediaRecorder.
  \param[in] input_surface_handle Handle to the internal surface object.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Surface object was successfully released.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NoInit MLMediaCodec was not initialized.

  \permissions None

*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderReleaseInputSurface(MLHandle media_recorder, MLHandle input_surface_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Restarts the MediaRecorder to its idle state.

  After calling this method, you will have to configure it again as if it had just been
  constructed.

  \apilevel 20

  \param[in] media_recorder Handle to the media recorder.

  \retval MLResult_InvalidParam Media recorder handle was not found.
  \retval MLResult_Ok Recorder was resetted successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaRecorderReset(MLHandle media_recorder);

ML_EXTERN_C_END
