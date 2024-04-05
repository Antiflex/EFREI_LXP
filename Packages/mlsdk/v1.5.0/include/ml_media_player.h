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
#include "ml_media_common.h"
#include "ml_media_data_source.h"
#include "ml_media_error.h"
#include "ml_media_stream_source.h"
#include "ml_types.h"
#include "ml_media_types.h"
#include "ml_media_drm.h"
#include "ml_media_webvtt.h"
#include "ml_media_ttml.h"
#include <stddef.h>

ML_EXTERN_C_BEGIN

/*!
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject media_player.magicleap
 
  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK MEDIA APIs:
            https://developer.android.com/reference/android/media/MediaPlayer
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for high level management of media playback.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.

  \{
*/

/*! Codes for setting video scaling mode. */
typedef enum MLMediaPlayerVideoScalingMode {
  MLMediaPlayerVideoScalingMode_ScaleToFit = 1,
  MLMediaPlayerVideoScalingMode_ScaleToFitWithCropping = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaPlayerVideoScalingMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerVideoScalingMode;

/*! The state to be polled. */
typedef enum MLMediaPlayerPollingStateFlags {
  /*! Playing. */
  MLMediaPlayerPollingStateFlag_IsPlaying            = 1 << 0,
  /*! Looping. */
  MLMediaPlayerPollingStateFlag_IsLooping            = 1 << 1,
  /*! Prepared. */
  MLMediaPlayerPollingStateFlag_HasBeenPrepared      = 1 << 2,
  /*! Playback completed. */
  MLMediaPlayerPollingStateFlag_HasPlaybackCompleted = 1 << 3,
  /*! Seek completed. */
  MLMediaPlayerPollingStateFlag_HasSeekCompleted     = 1 << 4,
  /*! Size changed. */
  MLMediaPlayerPollingStateFlag_HasSizeChanged       = 1 << 5,
  /*! Buffering updated. */
  MLMediaPlayerPollingStateFlag_HasBufferingUpdated  = 1 << 6,
  /*! Received info. */
  MLMediaPlayerPollingStateFlag_HasReceivedInfo      = 1 << 7,
  /*! Received error. */
  MLMediaPlayerPollingStateFlag_HasReceivedError     = 1 << 8,
  /*! Timed text updated. */
  MLMediaPlayerPollingStateFlag_HasTimedTextUpdated  = 1 << 9,
  /*! Subtitle updated. */
  MLMediaPlayerPollingStateFlag_HasSubtitleUpdated   = 1 << 10,
  /*! Metadata updated. */
  MLMediaPlayerPollingStateFlag_HasMetadataUpdated   = 1 << 11,
  /*! DRM info updated. */
  MLMediaPlayerPollingStateFlag_HasDrmInfoUpdated    = 1 << 12,
  /*! Async Reset completed. */
  MLMediaPlayerPollingStateFlag_HasResetCompleted    = 1 << 13,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaPlayerPollingStateFlag_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerPollingStateFlags;

/*!
  \brief Info and warning codes for the media player framework.

  These are non fatal, the playback is going on but there might be some user visible issues.

  Info and warning messages are communicated back to the client using the on_info callback.
  In this situation, this method is invoked with the following:

  Description of 'what' should be a value from the MLMediaPlayerInfo.
  Description of 'extra' contains an implementation dependent info code to provide more details.
  Should default to 0 when not used.
*/
typedef enum MLMediaPlayerInfo {
  /*! Unknown. */
  MLMediaPlayerInfo_Unknown           = 1,
  /*! The player was started because it was used as the next player. */
  MLMediaPlayerInfo_StartedAsNext     = 2,
  /*! The player just pushed the very first video frame for rendering. */
  MLMediaPlayerInfo_RenderingStart    = 3,
  /*! The player just reached EOS and started from beginning (loop). */
  MLMediaPlayerInfo_Looping           = 4,
  /*! The player acknowledgement that it has started playing. */
  MLMediaPlayerInfo_Started           = 5,
  /*! The player acknowledgement that it has paused. */
  MLMediaPlayerInfo_Paused            = 6,
  /*! The player acknowledgement that it has stopped playing. */
  MLMediaPlayerInfo_Stopped           = 7,
  /*! The player acknowledgement that it has started playing as result of shared player's request. */
  MLMediaPlayerInfo_StartedBySharedPlayer = 8,
  /*! The player acknowledgement that it has paused playing as result of shared player's request. */
  MLMediaPlayerInfo_PausedBySharedPlayer  = 9,
  /*! The player acknowledgement that it is seeking as result of shared player's request. */
  MLMediaPlayerInfo_SeekBySharedPlayer    = 10,
  /*! The player acknowledgement that it has stopped playing as result of shared player's request. */
  MLMediaPlayerInfo_StoppedBySharedPlayer = 11,
  /*! The player has started sync'ing with other shared players. */
  MLMediaPlayerInfo_SyncStart = 12,
  /*! The player has completed sync'ing with other shared players. */
  MLMediaPlayerInfo_SyncComplete = 13,
  /*! The video is too complex for the decoder, it can't decode frames fast enough. */
  MLMediaPlayerInfo_VideoTrackLagging = 700,
  /*! Media player is temporarily pausing playback. */
  MLMediaPlayerInfo_BufferingStart    = 701,
  /*! Media player is resuming playback after filling buffers. */
  MLMediaPlayerInfo_BufferingEnd      = 702,
  /*! Network bandwidth info. */
  MLMediaPlayerInfo_NetworkBandwidth  = 703,
  /*! Dash Live stream is Behind Live Window. */
  MLMediaPlayerInfo_BehindLiveWindow  = 704,
  /*! Playback Paused because of Power State Transition. */
  MLMediaPlayerInfo_PowerStatePause   = 705,
  /*! Playback Resumed because of Power State Transition. */
  MLMediaPlayerInfo_PowerStateResume  = 706,
  /*! Duration in milliseconds of buffered content. */
  MLMediaPlayerInfo_BufferedDuration  = 707,
  /*! Bad interleaving means that a media has been improperly interleaved. */
  MLMediaPlayerInfo_BadInterleaving   = 800,
  /*! The media is not seekable (e.g live stream). */
  MLMediaPlayerInfo_NotSeekable       = 801,
  /*! New media metadata is available. */
  MLMediaPlayerInfo_MetadataUpdate    = 802,
  /*! Audio can not be played. */
  MLMediaPlayerInfo_PlayAudioError    = 804,
  /*! Video can not be played. */
  MLMediaPlayerInfo_PlayVideoError    = 805,
  /*! Media timed text error. */
  MLMediaPlayerInfo_TimedTextError    = 900,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaPlayerInfo_Ensure32Bits      = 0x7FFFFFFF
} MLMediaPlayerInfo;

/*! MediaTrack types returned by MLMediaPlayerGetTrackType(). */
typedef enum MLMediaPlayerTrackType {
  /*! Unknown. */
  MLMediaPlayerTrackType_Unknown      = 0,
  /*! Video. */
  MLMediaPlayerTrackType_Video        = 1,
  /*! Audio. */
  MLMediaPlayerTrackType_Audio        = 2,
  /*! Timed text. */
  MLMediaPlayerTrackType_TimedText    = 3,
  /*! Subtitle. */
  MLMediaPlayerTrackType_Subtitle     = 4,
  /*! Metadata. */
  MLMediaPlayerTrackType_Metadata     = 5,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaPlayerTrackType_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerTrackType;

typedef MLPSSHEntry MLMediaPlayerPSSHEntry;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer DRM Info for a Media Track .

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerTrackDRMInfo {
  /*! Number of PSSH entries. */
  size_t pssh_info_count;
  /*! Pointer to array of #MLMediaPlayerPSSHEntry of size pssh_info_count. */
  MLMediaPlayerPSSHEntry *pssh_info;
  /*! Number of supported DRM UUID entries. */
  size_t uuid_count;
  /*! Pointer to array of #MLUUID of size uuid_count. */
  MLUUID *UUIDs;
  /*! Media track type, can be either audio or video. */
  MLMediaPlayerTrackType track_type;
} MLMediaPlayerTrackDRMInfo;

/*! MediaPlayer subtitle data. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerSubtitleData {
  uint32_t track_index;
  uint64_t start_time_us;
  uint64_t duration_us;
  uint32_t data_size;
  uint8_t *data;
} MLMediaPlayerSubtitleData;

/*! Indicate the mode of buffering settings. */
typedef enum MLMediaPlayerBufferingMode {
  /*! Do not support buffering. */
  MLMediaPlayerBufferingMode_None         = 0,
  /*! Support only time based buffering. */
  MLMediaPlayerBufferingMode_TimeOnly     = 1,
  /*! Support only size based buffering. */
  MLMediaPlayerBufferingMode_SizeOnly     = 2,
  /*!
    \brief Support both time and size based buffering, time based calculation precedes
    size based. Size based calculation will be used only when time information is not
    available for the stream.
  */
  MLMediaPlayerBufferingMode_TimeThenSize = 3,
  /*! Number of modes. */
  MLMediaPlayerBufferingMode_Count        = 4,
  /*! Ensure enum size is 32 bits. */
  MLMediaPlayerBufferingMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaPlayerBufferingMode;

/*! Indicate the buffering settings. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerBufferingSettings {
    /*! For prepare. */
    MLMediaPlayerBufferingMode initial_buffering_mode;
    /*! For playback. */
    MLMediaPlayerBufferingMode rebuffering_mode;
    /*! Time based. */
    int32_t initial_watermark_ms;
    /*! Size based. */
    int32_t initial_watermark_kb;
    /*!
      \brief When cached data is below this mark, playback will be paused for buffering
      until data reaches |mRebufferingWatermarkHighMs| or end of stream.
    */
    int32_t rebuffering_watermark_low_ms;
    /*! When cached data is above this mark, buffering will be paused. */
    int32_t rebuffering_watermark_high_ms;
    /*!
      \brief When cached data is below this mark, playback will be paused for buffering
      until data reaches |mRebufferingWatermarkHighKB| or end of stream. */
    int32_t rebuffering_watermark_low_kb;
    /*! When cached data is above this mark, buffering will be paused. */
    int32_t rebuffering_watermark_high_kb;
} MLMediaPlayerBufferingSettings;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Buffering update callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnBufferingUpdateInfo {
  /*! The new percentage of buffered content. */
  int percent;
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnBufferingUpdateInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Playback completion callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnCompletionInfo {
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnCompletionInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Error callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnErrorInfo {
  /*! Error/result code indicating failure reason. */
  MLResult result;
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnErrorInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Information callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnInfoInfo {
  /*! Type of informational event. */
  MLMediaPlayerInfo info;
  /*!
    \brief MLMediaPlayerInfo type specific extra information.

    When info is MLMediaPlayerInfo_NetworkBandwidth, this holds bandwidth in kbps. It is 0 for others.
  */
  int extra;
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnInfoInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Playback prepared callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnPreparedInfo {
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnPreparedInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Playback seek completion callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnSeekCompleteInfo {
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnSeekCompleteInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Video Size Changed callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnVideoSizeChangedInfo {
  /*! The new surface width. */
  int width;
  /*! The new surface height. */
  int height;
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnVideoSizeChangedInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Track DRM Info callback Info.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnTrackDRMInfo {
  /*! Pointer to MLMediaPlayerTrackDRMInfo. */
  MLMediaPlayerTrackDRMInfo *track_info;
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void* data;
} MLMediaPlayerOnTrackDRMInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer reset completion callback Info.

  \apilevel 8
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnResetCompleteInfo {
  /*!
    \brief User data as passed to MLMediaPlayerSetEventCallbacksEx().

    \apilevel 8
  */
  void *data;
} MLMediaPlayerOnResetCompleteInfo;

/*!
  \brief Frame Packing Arrangement for stereoscopic videos.

  \apilevel 8
*/
typedef enum {
  /*! Not a stereoscopic video. */
  MLMediaFramePackingMode_None = 0,
  /*! Checkboard. */
  MLMediaFramePackingMode_Checkboard,
  /*! Column interleaved. */
  MLMediaFramePackingMode_ColumnInterleaved,
  /*! Row interleaved. */
  MLMediaFramePackingMode_RowInterleaved,
  /*! Side by side quincunx. */
  MLMediaFramePackingMode_SideBySideQuincunx,
  /*! Side by side. */
  MLMediaFramePackingMode_SideBySide,
  /*! Top bottom. */
  MLMediaFramePackingMode_TopBottom,
  /*! Multiview frame by frame. */
  MLMediaFramePackingMode_MultiviewFrameByFrame,
  /*! Frame by frame. */
  MLMediaFramePackingMode_FrameByFrame,
  /*! Anaglyph. */
  MLMediaFramePackingMode_Anaglyph,
} MLMediaFramePackingMode;

/*!
  \brief Frame Packing Arrangement flags for stereoscopic videos.

  \apilevel 8
*/
typedef enum {
  /*! No flags. */
  MLMediaFramePackingFlags_None = 0,
  /*! Right view first. */
  MLMediaFramePackingFlags_RightViewFirst = 1 << 0,
  /*! Left view flipped. */
  MLMediaFramePackingFlags_LeftFlipped = 1 << 1,
  /*! Right view flipped. */
  MLMediaFramePackingFlags_RightFlipped = 1 << 2,
  /*! Anaglyph red/cyan. */
  MLMediaFramePackingFlags_Anaglyph_RedCyan = 1 << 3,
  /*! Anaglyph green/magenta. */
  MLMediaFramePackingFlags_Anaglyph_GreenMagenta = 1 << 4,
} MLMediaFramePackingFlags;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer frame packing callback Info.

  \apilevel 8
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerOnFramePackingInfo {
  /*! Frame packing more. */
  MLMediaFramePackingMode mode;
  /*! Frame packing flag. */
  MLMediaFramePackingFlags flags;
  /*! User data as passed to MLMediaPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaPlayerOnFramePackingInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Callbacks for notifying client about \ref MediaPlayer error events.

  Those are async mechanisms that should not be used in parallel with their
  sync counterpart, i.e. poll-based queries for the same events using
  MLMediaPlayerPollStatespoll().

  \apilevel 8
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerEventCallbacksEx {
  uint32_t version;
  /*!
    \brief This callback function is invoked when buffered contents percentage changed.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] update_info Pointer to MLMediaPlayerOnBufferingUpdateInfo.
  */
  void (*on_buffering_update)(MLHandle media_player, const MLMediaPlayerOnBufferingUpdateInfo *update_info);
  /*!
    \brief This callback is invoked when media player played back until end of media and has now come to a stop.

    Note that this callback does not fire when 'looping = true',
    because \ref MediaPlayer does not "stop" in that case, but rather
    loops to beginning of media.

    To get notified when EOS is reached (when looping = true),
    set a proper callback function for the below on_info and look for the
    #MEDIA_PLAYER_INFO_LOOPING info code.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] completion_info Pointer to  MLMediaPlayerOnCompletionInfo.
  */
  void (*on_completion)(MLHandle media_player, const MLMediaPlayerOnCompletionInfo *completion_info);
  /*!
    \brief This callback function is invoked when media player encounters an error.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] erro_info Pointer to MLMediaPlayerOnErrorInfo.
  */
  void (*on_error)(MLHandle media_player, const MLMediaPlayerOnErrorInfo *error_info);
  /*!
    \brief This callback function is invoked when \ref MediaPlayer generates informational events.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] info Pointer to MLMediaPlayerOnInfoInfo.
  */
  void (*on_info)(MLHandle media_player, const MLMediaPlayerOnInfoInfo *info);
  /*!
    \brief This callback is invoked when the player has finished preparing media and is ready to playback.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] prepared_info Pointer to MLMediaPlayerOnPreparedInfo.
  */
  void (*on_prepared)(MLHandle media_player, const MLMediaPlayerOnPreparedInfo *prepared_info);
  /*!
    \brief This callback function is invoked when a seek operation has completed.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] seek_complete_info Pointer to MLMediaPlayerOnSeekCompleteInfo.
  */
  void (*on_seek_complete)(MLHandle media_player, const MLMediaPlayerOnSeekCompleteInfo *seek_complete_info);
  /*!
    \brief This callback function is invoked when the internal surface has changed size.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] video_size_info Pointer to MLMediaPlayerOnVideoSizeChangedInfo.
  */
  void (*on_video_size_changed)(MLHandle media_player, const MLMediaPlayerOnVideoSizeChangedInfo *video_size_info);
  /*!
    \brief This callback function is invoked when source has DRM protected media track(s).

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] track_drm_info Pointer to MLMediaPlayerOnTrackDRMInfo.
  */
  void (*on_track_drm_info)(MLHandle media_player, const MLMediaPlayerOnTrackDRMInfo *track_drm_info);
  /*!
    \brief This callback function is invoked when an async reset operation has completed.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] reset_complete_info pointer to MLMediaPlayerOnResetCompleteInfo.
  */
  void (*on_reset_complete)(MLHandle media_player, const MLMediaPlayerOnResetCompleteInfo *reset_complete_info);
  /*!
    \brief This callback function is invoked when a stereoscopic video frame packing change.

    \param[in] media_player #MLHandle is a \ref MediaPlayer instance on which callback was set.
    \param[in] mode A MLMediaFramePackingMode.
    \param[in] flags A MLMediaFramePackingFlags.
  */
  void (*on_frame_packing)(MLHandle media_player, const MLMediaPlayerOnFramePackingInfo *frame_packing_info);
} MLMediaPlayerEventCallbacksEx;

/*!
  \brief Initializes MediaPlayerEventCallbacks with default values.

  \param[in,out] inout_callbacks Media Player Callback structure defined by #MLMediaPlayerEventCallbacksEx that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaPlayerEventCallbacksExInit(MLMediaPlayerEventCallbacksEx *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 2;
    inout_callbacks->on_buffering_update = NULL;
    inout_callbacks->on_completion = NULL;
    inout_callbacks->on_error = NULL;
    inout_callbacks->on_info = NULL;
    inout_callbacks->on_prepared = NULL;
    inout_callbacks->on_seek_complete = NULL;
    inout_callbacks->on_video_size_changed = NULL;
    inout_callbacks->on_track_drm_info = NULL;
    inout_callbacks->on_reset_complete = NULL;
    inout_callbacks->on_frame_packing = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer Track Information.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerTrackInfo {
  uint32_t version;
  /*! Media track type, can be either audio or video. */
  MLMediaPlayerTrackType track_type;
} MLMediaPlayerTrackInfo;

/*!
  \brief Initializes Media Track Information with default values.

  \param[in,out] inout_track_info Media track information defined by #MLMediaPlayerTrackInfo that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaPlayerTrackInfoInit(MLMediaPlayerTrackInfo *inout_track_info) {
  if (inout_track_info) {
    inout_track_info->version = 1;
    inout_track_info->track_type = MLMediaPlayerTrackType_Unknown;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief DRM Session information for a MediaPlayer Track.

  \apilevel 2
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerTrackDRMSessionInfo {
  uint32_t version;
  /*! Media track type, can be either audio or video. */
  MLMediaPlayerTrackType track_type;
  /*! UUID of the DRM Scheme of type #MLUUID. */
  const MLUUID *uuid;
  /*! DRM Session ID of type #MLMediaDRMByteArray. */
  const MLMediaDRMByteArray *session_id;
} MLMediaPlayerTrackDRMSessionInfo;

/*!
  \brief Initializes Media Track DRM Session Information with defult values.

  \param[in,out] inout_drm_session_info Media track DRM Session information defined by #MLMediaPlayerTrackDRMSessionInfo that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaPlayerTrackDRMSessionInfoInit(MLMediaPlayerTrackDRMSessionInfo *inout_drm_session_info) {
  if (inout_drm_session_info) {
    inout_drm_session_info->version = 1;
    inout_drm_session_info->track_type = MLMediaPlayerTrackType_Unknown;
    inout_drm_session_info->uuid = NULL;
    inout_drm_session_info->session_id = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new \ref MediaPlayer object.

  \note This is a blocking sync method. As creating a MediaPlayer object might take some time,
        make sure to *not* call this API from your main UI thread.

  \param[out] out_handle The #MLHandle to the new \ref MediaPlayer object created. Only valid if result is MLResult_Ok.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully created MediaPlayer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerCreate(MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Destroys a MediaPlayer object.

  \note This is a blocking sync method. As destroying a MediaPlayer object might take some time,
        make sure to *not* call this API from your main UI thread.

  \param[in] media_player #MLHandle to the \ref MediaPlayer object to destroy.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully destroyed MediaPlayer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerDestroy(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets a file descriptor as the data source.

  The file descriptor must be seekable. It is the caller's responsibility to
  close the file descriptor. It is safe to do so as soon as this call returns.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] fd The file descriptor for the file you want to play.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set file descriptor.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetDataSourceForFD(MLHandle media_player, int32_t fd);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets a file descriptor as the data source with offset.

  The file descriptor must be seekable. It is the caller's responsibility to
  close the file descriptor. It is safe to do so as soon as this call returns.
  This API is useful for specifying playable media located in resource files.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] fd The file descriptor for the file you want to play.
  \param[in] offset The offset (in bytes) of the source's start.
  \param[in] length The number of bytes of media to load after offset.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set file descriptor.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetOffsetDataSourceForFD(MLHandle media_player, int32_t fd, int64_t offset, int64_t length);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets a local file path as the data source.

  The path should be an absolute path and should reference a world-readable
  file.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] path The linux-style path of the file.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set local file path.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetDataSourceForPath(MLHandle media_player, const char *path);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets a URI string as the data source.

  Supported URI schemes are `file`, `http`, `https`, and `rtsp`. If looking to
  provide headers, use MLMediaPlayerSetRemoteDataSourceForURI().

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] uri The C-style string representing the URI complete string.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set URI string.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions android.permission.INTERNET (protection level: normal)
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetDataSourceForURI(MLHandle media_player, const char *uri);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets a URI string as the remote data source.

  Supported URI schemes are `file`, `http`, `https`, and `rtsp`.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] uri The C-style string representing the complete URL.
  \param[in] headers Array of char * headers to be sent.
  \param[in] len Number of headers passed.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set URI string.
  \retval MLResult_PermissionDenied Failed due to lack of permission.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions android.permission.INTERNET (protection level: normal)
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetRemoteDataSourceForURI(MLHandle media_player, const char *uri, char **headers, size_t len);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the data source to use.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] media_data_source #MLHandle returned by MLMediaDataSourceCreate().

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the data source to use.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NameNotFound Failed because no valid source could be found.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetMediaDataSource(MLHandle media_player, MLHandle media_data_source);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the data source to use.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] media_stream_source #MLHandle returned by MLMediaStreamSourceCreate().

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the data source to use.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NameNotFound Failed because no valid source could be found.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetMediaStreamSource(MLHandle media_player, MLHandle media_stream_source);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Adds a TimedText source from a URI.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] uri The C-style string representing the complete URI.
  \param[in] mime_type The MIME type of the file.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully added TimedText source from URI.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown failure.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerAddTimedTextSourceForURI(MLHandle media_player, const char *uri, const char *mime_type);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Adds a TimedText source from a file descriptor.

  The file descriptor must be seekable. It is the caller's responsibility to
  close the file descriptor. It is safe to do so as soon as this call returns.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] fd The file descriptor for the timed text source.
  \param[in] offset The offset (in bytes) of the source's start. Must be >= 0.
  \param[in] length The number of bytes of media to load after offset. Must be >= 0.
  \param[in] mime_type The MIME type of the file.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully added TimedText source from file descriptor.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown failure.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerAddTimedTextSourceForFD(MLHandle media_player, int32_t fd, int64_t offset, int64_t length, const char *mime_type);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the 'next' \ref MediaPlayer to automatically 'start' when current \ref MediaPlayer playback completes.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] next_media_player #MLHandle of an already created \ref MediaPlayer instance.
          To 'remove' the next player, set next_media_player = 0.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully registered next \ref MediaPlayer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NameNotFound Failed source because no valid source could be found.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetNextPlayer(MLHandle media_player, MLHandle next_media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Counts the number of tracks found in the data source.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_track_count The number of tracks found in the player source.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the number of tracks.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTrackCount(MLHandle media_player, uint32_t *out_track_count);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets the type of a track.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] track The track number for which type is to be returned. Has to be < TrackCount.
  \param[out] out_track_type The returned type for specified track number.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned type for passed track.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NameNotFound Found track's type was unknown.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTrackType(MLHandle media_player, uint32_t track, MLMediaPlayerTrackType *out_track_type);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets the language of a track.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] track The track number for which language is to be returned. Has to be < TrackCount.
  \param[out] out_track_language The returned language of the track. Caller has ownership of that param
              and has to free it when no longer needed.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned language for passed track.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTrackLanguage(MLHandle media_player, uint32_t track, char **out_track_language);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets the Media Format of a track.

  \apilevel 2

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] track The track number for which Media Format is to be returned. Has to be < TrackCount.
  \param[out] out_media_format #MLHandle to \ref MediaFormat of the track.
              Caller has ownership of this handle and should call #MLMediaFormatDestroy to free it when no longer needed.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully retreived the media format of passed track.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTrackMediaFormat(MLHandle media_player, uint32_t track, MLHandle *out_media_format);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Selects a track.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] track Number of the track to select. Has to be < TrackCount.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully selected track.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSelectTrack(MLHandle media_player, uint32_t track);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Unselects a track.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] track Number of the track to unselect. Has to be < TrackCount.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully unselected track.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerUnselectTrack(MLHandle media_player, uint32_t track);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Prepares the player for playback, synchronously.

  After setting the data source and the #GraphicBufferProducer, you need to
  either call prepare() or prepareAsync(). For files, it is OK to call
  prepare(), which blocks until \ref MediaPlayer is ready for playback.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully prepared the player.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          Can only be called after one of the setDataSource methods or in the 'stopped' state.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.
  \retval MLMediaResult_CannotConnect Failed becaue MediaPlayer could not connect with the given URL.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerPrepare(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Prepares the player for playback, asynchronously.

  After setting the data's source and the #GraphicBufferProducer, you need to
  either call prepare() or prepareAsync(). For streams, you should call
  prepareAsync(), which returns immediately, rather than blocking until
  enough data has been buffered. Prepared state will then be obtained via the
  'on_prepared' callback if already registered (see MLMediaPlayerSetEventCallbacksEx),
  or polled for via the MLMediaPlayerPollStates() call with the
  MLMediaPlayerPollingStateFlag_HasBeenPrepared flag set.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully prepared the player asynchronously.
          For result, poll for MLMediaPlayerPollingStateFlag_HasBeenPrepared state
          or wait for 'on_prepared' callback if already set.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          Can only be called after one of the setDataSource methods or in the 'stopped' state.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerPrepareAsync(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Starts or resumes playback.

  If playback had previously been paused, playback will continue from where
  it was paused. If playback had been stopped, or never started before,
  playback will start at the beginning.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully started/resumed playback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          Can only be called in one of the following states: 'prepared', 'playback complete', 'paused', 'stopped'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerStart(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Stops playback after playback has been started or paused.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully stopped playback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          Can only be called in one of the following states: 'playing', 'paused', 'stopped', 'prepared', 'playback complete'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerStop(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Pauses playback.

  Calling pause() is a NOOP if \ref MediaPlayer is in state #MEDIA_PLAYER_PAUSED
  or #MEDIA_PLAYER_PLAYBACK_COMPLETE.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully paused playback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          Can only be called in one of the following states: 'playing', 'paused', 'playback complete'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerPause(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Resets the \ref MediaPlayer to its uninitialized state.

  After calling this method, you will have to initialize it again by setting the
  data source and calling prepare().

  \note This is a blocking sync method, make sure to *not* call this API
        from your main UI thread.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully reset MediaPlayer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          This method can be called anytime except when in 'preparing async'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerReset(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Seeks to specified time position.

  Note that SeekTo is an async. function and returns immediately.
  Successful seek result has to be obtained either via the 'on_seek_complete' if
  already registered (see MLMediaPlayerSetEventCallbacksEx) or by polling for the flag
  'MLMediaPlayerPollingStateFlag_HasSeekCompleted' when calling MLMediaPlayerPollStates().

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] msec The offset in milliseconds from the start, to seek to.
  \param[in] mode Seek mode defined by MLMediaSeekMode.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully launched seek operation asynchronously.
          For result, poll for MLMediaPlayerPollingStateFlag_HasSeekCompleted state or
          wait for the 'on_seek_complete' callback if already set.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          This method can only be called from the following states: 'started', 'prepared', 'paused' and 'playback complete'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSeekTo(MLHandle media_player, int msec, MLMediaSeekMode mode);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets callbacks to notify clients about player events.

  This structure must be initialized by calling MLMediaPlayerEventCallbacksExInit() before use.

  Client needs to implement the callback functions declared in
  #MLMediaPlayerEventCallbacksEx, but can set to NULL the ones he does not care about.

  \apilevel 2

  \param[in] media_player #MLHandle to the \ref MediaCodec.
  \param[in] callbacks Set of event callbacks. Can be set to NULL to unset
             the callbacks altogether.
  \param[in] data Custom data to be returned when any callback is fired.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set/unset the specified callbacks.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetEventCallbacksEx(MLHandle media_player, const MLMediaPlayerEventCallbacksEx *callbacks, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns the size of the video frame.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_width The returned video width.
  \param[out] out_height The returned video height.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned video size.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetVideoSize(MLHandle media_player, int32_t *out_width, int32_t *out_height);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns current position of playback.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_msec The returned position in milliseconds.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned current position.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetCurrentPosition(MLHandle media_player, int32_t *out_msec);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns media duration.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_msec The returned duration in milliseconds.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the media duration.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          This method can only be called from the following states: 'prepared', 'started', 'paused', 'stopped' and 'playback complete'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetDuration(MLHandle media_player, int32_t *out_msec);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns current buffering percentage.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_percentage The returned buffering percentage in the range [0, 100].

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned current buffering percentage.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetBufferingUpdate(MLHandle media_player, int32_t *out_percentage);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns last info received by internal \ref MediaPlayer.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_code The main info code.
  \param[out] out_extra The secondary code/data.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the last MediaPlayer.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetInfo(MLHandle media_player, int32_t *out_code, int32_t *out_extra);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns last error received by internal \ref MediaPlayer.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_result The result code.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the last MediaPlayer error.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetError(MLHandle media_player, MLResult *out_result);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns last timed text event information.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_text The text of the timed text event.
  \param[out] out_start The start time.
  \param[out] out_end The end time.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the last timedtext entry.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTimedText(MLHandle media_player, const char **out_text, int32_t *out_start, int32_t *out_end);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns last subtitle event information.

  \apilevel 2

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_subtitle_data The returned MLMediaPlayerGetSubtitleExArgs pointer.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the last subtitle entry.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetSubtitleEx(MLHandle media_player, MLMediaPlayerSubtitleData **out_subtitle_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Releases last subtitle event information.

  \apilevel 2

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully released the last subtitle entry.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerReleaseSubtitleEx(MLHandle media_player);

/*!
  \brief Callbacks signature called when subtitle update is available.

  \param[in] data Custom data to be returned when callback is fired.
  \param[in] media_player #MLHandle is a \ref MediaPlayer instance for which callback was called.
  \param[in] subtitle_data #MLMediaPlayerSubtitleData is the raw subtitle data.
*/
typedef void(*MLMediaPlayerOnMediaSubtitleUpdateCallback)(MLHandle media_player, MLMediaPlayerSubtitleData subtitle_data, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets callback to get notified when a subtitle update is available along with its data.

  \apilevel 4

  Setting this callback disables use of the poll-based API to query for the
  #MLMediaPlayerPollingStateFlag_HasSubtitleUpdated flag.
  MLMediaPlayerPollStates() will ignore checks for this bit.

  This also makes MLMediaPlayerGetSubtitleEx() redundant as the subtitle data is provided with the callback.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] on_media_subtitle_callback Function pointer to be called.
            This can be 'NULL' to unset the callback.
            See MLMediaPlayerOnMediaSubtitleUpdateCallback() callback typedef declaration and comments
            for explanation on expected callback parameters.
  \param[in] data Custom data to be returned when callback is fired.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set callback.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetOnMediaSubtitleUpdateCallback(MLHandle media_player, MLMediaPlayerOnMediaSubtitleUpdateCallback on_media_subtitle_callback, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Returns last metadata event information.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_time The returned event time.
  \param[out] out_size The returned event buffer size.
  \param[out] out_buffer The returned event buffer.
              This buffer is only valid until the next metadata event arrives,
              so make a copy if you need to use the buffer later.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned last metadata entry.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetMetadata(MLHandle media_player, int64_t *out_time, int32_t *out_size, uint8_t **out_buffer);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets video scaling mode.

  \param[in] media_player MLHandle to the MediaPlayer instance.
  \param[in] mode The video scaling mode to set.
             For a list of valid values, see #media_video_scaling_mode_type declaration.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned current video scaling mode.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          SetDataSource must be called immediately after creation, or after a media player reset.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetVideoScalingMode(MLHandle media_player, MLMediaPlayerVideoScalingMode mode);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the looping mode of the player.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] loop The looping mode.
             Set to true if player should loop to beginning of MediaPlayer when EOS reached.
             Set to false if MediaPlayer should simply stop playback at end of media.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned current looping mode.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetLooping(MLHandle media_player, bool loop);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the volume on this player.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] volume The new volume in the [0.0, 1.0] range.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set the volume.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetVolume(MLHandle media_player, float volume);

/*!
  \deprecated Unsupported since 1.2.0. Scheduled for removal.
  \brief Gets the handle of the audio stream.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_handle The #MLHandle to the returned Audio handle. Only valid if result is MLResult_Ok.

  \retval MLResult_NotImplemented If used in versions starting 1.2.0 or later.

  \permissions None
*/
ML_DEPRECATED_MSG("This feature is not supported starting 1.2.0.")
ML_API MLResult ML_CALL MLMediaPlayerGetAudioHandle(MLHandle media_player, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Polls the desired states from internal \ref MediaPlayer.

  Desired states have to be selected by passing a bitwise OR'ed mask of
  #MLMediaPlayerPollingStateFlags flags.

  The "is_XXX"  states can be polled multiples times and the return value will
  be the same if internal state hasn't changed since last call.

  When polling the "has_XXX" states however, internal state is set to false,
  since they mean : has `<state>` happened/changed since I last polled `<state>`.

  Two-step state polling : The following states, when returning '1', indicate
                           there is some data ready to be retrieved, by calling
                           a getter function, as explained below.


  For '#MLMediaPlayerPollingState_HasSizeChanged', call MLMediaPlayerGetVideoSize() to get the new size.

  For '#MLMediaPlayerPollingState_HasBufferingUpdated', call MLMediaPlayerGetBufferingUpdate() to get buffering progress value.

  For '#MLMediaPlayerPollingState_HasReceivedInfo, call MLMediaPlayerGetError() to get last info code and data.

  For '#MLMediaPlayerPollingState_HasReceivedError, call MLMediaPlayerGetError() to get last error code and data.

  Note: This API can still be used even if an #OnBufferAvailable callback has been set using MLMediaPlayerSetOnBufferAvailableCallback() method.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] mask Selection mask for picking which states to retrieve.
  \param[out] out_polled_states Bitwise OR'ed integer of all the chosen states from bitwise 'mask' and in the range [0 = false : 1 = true].

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully polled and returned the selected states.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerPollStates(MLHandle media_player, uint16_t mask, uint16_t *out_polled_states);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets the DRM info of the selected media (either audio or video) track.

  This function has to be called only after DataSource has been set and the MediaPlayer is completely prepared.

  \apilevel 2

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] track_info Media track information defined by #MLMediaPlayerTrackInfo.
  \param[out] out_drm_info Pointer to the pointer to #MLMediaPlayerTrackDRMInfo struct.
              The caller should not free the pointer returned.
              The memory will be released in the call to MLMediaPlayerReleaseDRM().

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned the current DRM Info.
  \retval MLResult_Pending Media Source is not prepared yet. Wait for on_prepared callback and call again.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.
  \retval MLMediaGenericResult_NotAvailable DRM Information not available for the given track.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTrackDRMInfo(MLHandle media_player, const MLMediaPlayerTrackInfo *track_info, MLMediaPlayerTrackDRMInfo **out_drm_info);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Prepares DRM for the selected media (either audio or video) track.

  \apilevel 2

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] drm_session_info DRM Session info for the Media track, as defined by #MLMediaPlayerTrackDRMSessionInfo.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully prepared DRM.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerPrepareTrackDRM(MLHandle media_player, const MLMediaPlayerTrackDRMSessionInfo *drm_session_info);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Releases DRM.

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully released DRM.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerReleaseDRM(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets default Buffering settings.

  \Attention The API is only implemented in ML1.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_buf_settings A pointer to #MLMediaPlayerBufferingSettings.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned default Buffering settings.
  \retval MLResult_NotImplemented Feature not implemented in the given model.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetDefaultBufferingSettings(MLHandle media_player, MLMediaPlayerBufferingSettings *out_buf_settings);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets current Buffering settings.

  \Attention The API is only implemented in ML1.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_buf_settings A pointer to #MLMediaPlayerBufferingSettings.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned current Buffering settings.
  \retval MLResult_NotImplemented Feature not implemented in the given model.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetBufferingSettings(MLHandle media_player, MLMediaPlayerBufferingSettings *out_buf_settings);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets buffering settings.

  \Attention The API is only implemented in ML1.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] buf_settings An #MLMediaPlayerBufferingSettings struct.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully set buffering settings.
  \retval MLResult_NotImplemented Feature not implemented in the given model.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetBufferingSettings(MLHandle media_player, MLMediaPlayerBufferingSettings buf_settings);

/*!
  \brief Callbacks signature called when Timed Text update is available.

  \apilevel 4

  \param[in] media_player #MLHandle is a \ref MediaPlayer instance for which callback was called.
  \param[in] timed_text #MLHandle is the handle for timed_text data.
  \param[in] data Custom data to be delivered when callback is invoked.

  \permissions None
*/
typedef void(*MLMediaPlayerOnMediaTimedTextUpdateCallback)(MLHandle media_player, MLHandle timed_text, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set callback to get invoked when a Timed Text update is available along with its data.

  \apilevel 4

  Setting this callback disables use of the poll-based API to query for the
  #MLMediaPlayerPollingStateFlag_HasTimedTextUpdated flag.
  MLMediaPlayerPollStates() will ignore checks for this bit.

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] on_media_timed_text_callback Function pointer to be called.
            This can be 'NULL' to unset the callback.
  \param[in] data Custom data to be returned when callback is fired.

  \retval MLResult_Ok Successfully set callback.
  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetOnMediaTimedTextUpdateCallback(MLHandle media_player, MLMediaPlayerOnMediaTimedTextUpdateCallback on_media_timed_text_callback, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets WebVTT data represented by a timed text handle.

  The returned MLWebVTTData structure is valid only in the callback's context.

  \apilevel 4

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] timed_text The Timed Text handle.
  \param[out] out_webvtt_data The WebVTT data structure to be returned.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned WebVTT data.
  \retval MLMediaGenericResult_BadType Failed because the timed_text handle was not in the WebVTT format.
          The timed text track's mime type must be "text/vtt".
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetWebVTTData(MLHandle media_player, MLHandle timed_text, MLWebVTTData **out_webvtt_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets TTML data represented by a timed text handle.

  The returned MLTTMLData structure is valid only in the callback's context.

  \apilevel 20

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] timed_text The Timed Text handle.
  \param[out] out_ttml_data The TTML data structure to be returned.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully returned TTML data.
  \retval MLMediaGenericResult_BadType Failed because the timed_text handle was not in the TTML format.
          The timed text track's mime type must be "application/ttml+xml".
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetTTMLData(MLHandle media_player, MLHandle timed_text, MLTTMLData **out_ttml_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Resets the \ref MediaPlayer to its uninitialized state asynchronously.

  This method is asynchronous and will return immediately. After invocation,
  you will have to initialize it again by setting the data source and calling prepare()
  or prepareAsync().

  A successful reset result can be obtained either by registering the 'on_reset_complete'
  callback (see MLMediaPlayerSetEventCallbacksEx) or by polling for the
  'MLMediaPlayerPollingStateFlag_HasResetCompleted' flag when calling MLMediaPlayerPollStates().

  \apilevel 8

  \param[in] media_player Handle to the MediaPlayer instance.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully launched MediaPlayer reset operation asynchronously.
          For result, poll for MLMediaPlayerPollingStateFlag_HasResetCompleted or
          use the 'on_reset_complete' callback if already set.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
          This method can be called anytime except when in 'preparing async'.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerResetAsync(MLHandle media_player);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaPlayer metrics data.

  \apilevel 8
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK APIs.") struct MLMediaPlayerMetrics {
  /*! The average framerate (fps) of video playback. */
  float average_framerate;
  /*! The average bitrate (bps) of video playback. */
  int average_video_bitrate;
  /*! The average bitrate (bps) of audio playback. */
  int average_audio_bitrate;
} MLMediaPlayerMetrics;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieves metrics recorded on the MediaPlayer.

  \apilevel 8

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[out] out_metrics See \ref MLMediaPlayerMetrics.

  \retval MLResult_InvalidParam Failed due to an invalid parameter.
  \retval MLResult_Ok Successfully received metrics.
  \retval MLResult_UnspecifiedFailure Failed due to an unknown error.
  \retval MLMediaGenericResult_InvalidOperation Failed because method was called in the wrong state.
  \retval MLMediaGenericResult_NoInit Failed because MediaPlayer was not properly initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerGetMetrics(MLHandle media_player, MLMediaPlayerMetrics *out_metrics);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Sets the Native surface to be used as the sink for displaying the video portion of the media.

  The surface should be created by MLNativeSurfaceCreate().
  When called, this method should be called after one of the MLMediaPlayerSetDataSource() API and
  before MLMediaPlayerPrepare() or MLMediaPlayerPrepareAsync()
  Not calling this method or calling this with surface as ML_INVALID_HANDLE will result in
  only the audio track being played.

  \apilevel 20

  \param[in] media_player Handle to the MediaPlayer instance.
  \param[in] surface Handle to the MLNativeSurface object.

  \retval MLResult_InvalidParam Passed media_player or the surface handle was not found.
  \retval MLResult_Ok Successfully set output surface.
  \retval MLResult_UnspecifiedFailure Internal error.
  \retval MLMediaGenericResult_InvalidOperation Method was called from the wrong state.
  \retval MLMediaGenericResult_NoInit MediaPlayer was not properly built or initialized.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK APIs.")
ML_API MLResult ML_CALL MLMediaPlayerSetSurface(MLHandle media_player, MLHandle surface);
/*! \} */

ML_EXTERN_C_END
