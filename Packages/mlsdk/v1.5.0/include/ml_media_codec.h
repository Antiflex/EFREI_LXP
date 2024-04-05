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
  \sharedobject media_codec.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
              https://developer.android.com/ndk/reference/group/media
              https://developer.android.com/reference/android/media/MediaCodec
              Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for encoding and decoding audio and video buffers.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*! Media codec buffer info. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecBufferInfo {
  /*! Offset. */
  size_t offset;
  /*! Size. */
  size_t size;
  /*! Flags. */
  size_t flags;
  /*! Presentation timestamp in microseconds for this buffer. */
  int64_t presentation_time_us;
} MLMediaCodecBufferInfo;

/*! Media codec creation method. */
typedef enum MLMediaCodecCreation {
  /*! Create by name. */
  MLMediaCodecCreation_ByName,
  /*! Create by type. */
  MLMediaCodecCreation_ByType,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecCreation_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecCreation;

/*! Media codec type. */
typedef enum MLMediaCodecType {
  /*! Encoder. */
  MLMediaCodecType_Encoder,
  /*! Decoder. */
  MLMediaCodecType_Decoder,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecType_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecType;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Indicate the type of data when queuing the input buffer via
  MLMediaCodecQueueInputBuffer() or MLMediaCodecQueueSecureInputBuffer().
*/
typedef enum MLMediaCodecBufferFlag {
  /*! The (encoded) buffer contains the data for a key frame. */
  MLMediaCodecBufferFlag_KeyFrame     = 1,
  /*! Buffer contains codec initialization OR codec specific data instead of media data. */
  MLMediaCodecBufferFlag_CodecConfig  = 2,
  /*! Signals the end of stream, i.e. no buffers will be available after this. */
  MLMediaCodecBufferFlag_EOS          = 4,
  /*!
   \brief Buffer only contains part of a frame, and the decoder should batch the data
   until a buffer without this flag appears before decoding the frame.
  */
  MLMediaCodecBufferFlag_PartialFrame = 8,
  /*! Buffer contains muxer data - Supported only for Exif data block. */
  MLMediaCodecBufferFlag_MuxerData = 16,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecBufferFlag_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecBufferFlag;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Other than the normal buffer index, the output of MLMediaCodecDequeueOutputBuffer()
  can take on one of these statuses.
*/
typedef enum MLMediaCodecOutputBufferStatus {
  /*! Output buffer changed. */
  MLMediaCodec_OutputBuffersChanged           = -1014,
  /*! Format changed. */
  MLMediaCodec_FormatChanged                  = -1012,
  /*! Try again later. */
  MLMediaCodec_TryAgainLater                  = -11,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecOutputBufferStatus_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecOutputBufferStatus;

#define MAX_CODEC_NAME_SIZE 64

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief MediaCodec Input buffer information.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecInputBufferInfo {
  /*! The index of the available input buffer. */
  int64_t input_buffer_index;
  /*! User data as passed to MLMediaCodecSetCallbacksEx(). */
  void *data;
} MLMediaCodecInputBufferInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief MediaCodec Output buffer information.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecOutputBufferInfo {
  /*! The index of the available output buffer. */
  int64_t output_buffer_index;
  /*! The buffer info about the available output buffer. */
  MLMediaCodecBufferInfo *buffer_info;
  /*! User data as passed to MLMediaCodecSetCallbacksEx(). */
  void *data;
} MLMediaCodecOutputBufferInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief MediaCodec Output Format information.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecOutputFormatInfo {
  /*! Handle to the new output format. */
  MLHandle new_output_format;
  /*! User data as passed to MLMediaCodecSetCallbacksEx(). */
  void *data;
} MLMediaCodecOutputFormatInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief MediaCodec Output Format information.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecErrorInfo {
  /*! Error code. */
  int error_code;
  /*! User data as passed to MLMediaCodecSetCallbacksEx(). */
  void *data;
} MLMediaCodecErrorInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Callbacks for notifying asynchronously of various codec events to the user/client.
  If user intends to use codec in asynchronous mode, then the user/client is expected to
  implement these callbacks and take proper actions where appropriate.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecCallbacksEx {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief This callback function is invoked when an input buffer becomes available.

    This should not be set to NULL as codec will not function properly if client has
    no means to specify incoming input buffers.

    \note Client should *not* call MLMediaCodec APIs from within this callback but
    rather set internal flags or use synchronization mechanisms to wake up another
    thread that will queue encoded data into decoder.

    \param[in] media_codec MLMediaCodec instance for which callback was called.
    \param[in] info Input buffer info as MLMediaCodecInputBufferInfo().
  */
  void (*on_input_buffer_available)(MLHandle media_codec, const MLMediaCodecInputBufferInfo *info);

  /*!
    \brief This callback function is invoked when an output buffer.

    This should not be set to NULL as codec will not function properly.
    Typical implementation on on_output_buffer_available is simply to
    1) render the buffer to audio subsystem [if codec is audio]
    2) release-and-render-to-surface with MLMediaCodecReleaseOutputBuffer(.., true) [if codec is video].

    \note Client should *not* call MLMediaCodec APIs from within this callback but
    rather set internal flags or use synchronization mechanisms to wake up another
    thread that will dequeue and release the buffer.

    \param[in] media_codec MLMediaCodec instance for which callback was called.
    \param[in] info Output buffer info as MLMediaCodecOutputBufferInfo.
  */
  void (*on_output_buffer_available)(MLHandle media_codec, const MLMediaCodecOutputBufferInfo *info);

  /*!
    \brief This callback function is invoked when the output format has changed.

    This can be set to NULL if client is not interested in receiving this callback.

    \note Client should *not* call MLMediaCodec APIs from within this callback but
    rather set internal flags or use synchronization mechanisms to wake up another
    thread that will handle the change.

    \param[in] media_codec MLMediaCodec instance for which callback was called.
    \param[in] info Output format info as MLMediaCodecOutputFormatInfo.
  */
  void (*on_output_format_changed)(MLHandle media_codec, const MLMediaCodecOutputFormatInfo *info);

  /*!
    \brief This callback function is invoked when \ref MLMediaCodec encountered an error.

    This can be set to NULL if client is not interested in receiving this callback.

    \note Client should *not* call MLMediaCodec APIs from within this callback.

    \param[in] media_codec MLMediaCodec instance for which callback was called.
    \param[in] info Codec error info as MLMediaCodecErrorInfo.
  */
  void (*on_error)(MLHandle media_codec, const MLMediaCodecErrorInfo *info);
} MLMediaCodecCallbacksEx;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Initializes MLMediaCodecCallbacksEx with default values.

  \param[in,out] inout_callbacks MediaCodec Callback structure defined by #MLMediaCodecCallbacksEx that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaCodecCallbacksExInit(MLMediaCodecCallbacksEx *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 1;
    inout_callbacks->on_input_buffer_available = NULL;
    inout_callbacks->on_output_buffer_available = NULL;
    inout_callbacks->on_output_format_changed = NULL;
    inout_callbacks->on_error = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief MediaCodec Output Frame Rendered information.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecFrameRenderedInfo {
  /*! The presentation time (media time) in microseconds of the frame rendered. */
  int64_t presentation_time_us;
  /*! System time when the frame was rendered. */
  int64_t system_time_nano;
  /*! User data as passed to MLMediaCodecSetOutputFrameListener(). */
  void *data;
} MLMediaCodecFrameRenderedInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Callbacks for notifying when an output frame is available for consumption
   or has been rendered on the output surface.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecOutputFrameListener {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief This callback is invoked when an output frame has rendered on the output surface.

    The presentation time (media time) of the frame rendered is is usually the same as specified in
    MLMediaCodecQueueInputBuffer(); however, some codecs may alter the media time by applying some
    time-based transformation, such as frame rate conversion.
    In that case, presentation time corresponds to the actual output frame rendered.

    This callback is for informational purposes only: to get precise
    render timing samples, and can be significantly delayed and batched.
    Some frames may have been rendered even if there was no callback
    generated. This can be set to NULL if client is not interested in receiving
    this callback.

    \note Client should *not* call MLMediaCodec APIs from within this callback.

    \param[in] media_codec MLMediaCodec instance for which callback was called.
    \param[in] presentation_time_us The presentation time (media time) in microseconds of the frame rendered.
    \param[in] system_time_nano System time when the frame was rendered.
    \param[in] info Output Frame rendered info as MLMediaCodecFrameRenderedInfo.
  */
  void (*on_frame_rendered)(MLHandle media_codec, const MLMediaCodecFrameRenderedInfo *info);
} MLMediaCodecOutputFrameListener;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Initializes MLMediaCodecOutputFrameListener with default values.

  \param[in,out] inout_callbacks MediaCodec Callback structure defined by #MLMediaCodecOutputFrameListener that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaCodecOutputFrameListenerInit(MLMediaCodecOutputFrameListener *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 1;
    inout_callbacks->on_frame_rendered = NULL;
  }
}

/*! Crypto mode using which media samples are encrypted. */
typedef enum MLMediaCodecCryptoMode {
  /*! Clear samples. */
  MLMediaCodecCryptoMode_Clear,
  /*! Sample encrypted with AES CTR mode. */
  MLMediaCodecCryptoMode_CTR,
  /*! Sample encrypted with AES CBC mode. */
  MLMediaCodecCryptoMode_CBC,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaCodecCryptoMode_Ensure32Bits = 0x7FFFFFFF
} MLMediaCodecCryptoMode;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Metadata describing an encryption pattern for the protected bytes in a subsample.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecCryptoPattern {
  /*! Number of blocks to be encrypted in the pattern. If zero, pattern encryption is in-operative. */
  size_t encrypt_blocks;
  /*! Number of blocks to be skipped (left clear) in the pattern. If zero, pattern encryption is in-operative. */
  size_t skip_blocks;
} MLMediaCodecCryptoPattern;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Metadata describing the structure of a (at least partially) encrypted input sample.
  A buffer's data is considered to be partitioned into "subSamples", each subSample starts with
  a (potentially empty) run of plain, unencrypted bytes followed by a (also potentially empty)
  run of encrypted bytes.
  If pattern encryption applies, each of the encrypted runs is encrypted only partly,
  according to a repeating pattern of "encrypt" and "skip" blocks.
  This information encapsulates per-sample metadata as outlined in
  ISO/IEC FDIS 23001-7:2011 "Common encryption in ISO base media file format files".

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaCodecCryptoInfo {
  /*! Version of this structure. */
  uint32_t version;

  /*! The number of subsamples that make up the buffer's contents. */
  size_t                    number_of_subsamples;
  /*! Cipher Mode associated with the encrypted blocks. */
  MLMediaCodecCryptoMode    crypto_mode;
  /*!  Encryption pattern used by the subsample. */
  MLMediaCodecCryptoPattern crypto_pattern;
  /*! 16 bytes of Key used for the encrypted blocks. */
  const uint8_t*            key;
  /*! 16 bytes of Initialization vector used for the encrypted blocks. */
  const uint8_t*            iv;
  /*! An array of size "number_of_subsamples", that contains the number of leading
      (potentially none, which is 0) unencrypted bytes in each subsample. */
  const size_t*             bytes_of_clear_data;
  /*! An array of size "number_of_subsamples", that contains the number of trailing
      (potentially none, which is 0) encrypted bytes in each subsample. */
  const size_t*             bytes_of_encrypted_data;
} MLMediaCodecCryptoInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Initializes MLMediaCodecCryptoInfo with default values.

  \param[in,out] inout_crypto_info CryptoInfo structure defined by #MLMediaCodecCryptoInfo that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaCodecCryptoInfoInit(MLMediaCodecCryptoInfo *inout_crypto_info) {
  if (inout_crypto_info) {
    inout_crypto_info->version = 1;
    inout_crypto_info->number_of_subsamples = 0;
    inout_crypto_info->crypto_mode = MLMediaCodecCryptoMode_Clear;
    inout_crypto_info->crypto_pattern.encrypt_blocks = 0;
    inout_crypto_info->crypto_pattern.skip_blocks = 0;
    inout_crypto_info->key = NULL;
    inout_crypto_info->iv = NULL;
    inout_crypto_info->bytes_of_clear_data = NULL;
    inout_crypto_info->bytes_of_encrypted_data = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Create a Crypto Info object.

  The CryptoInfo object should be released by calling #MLMediaCodecReleaseCryptoInfo.

  \apilevel 20

  \param[in] crypto_info Input Structure that encapsulates sample crypto info.
  \param[out] out_crypto_info_handle Upon successful return will point to handle to the created Crypto info.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecCreateCryptoInfo(const MLMediaCodecCryptoInfo *crypto_info, MLHandle *out_crypto_info_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Release the Crypto Info created by #MLMediaCodecCreateCryptoInfo.

  \apilevel 20

  \param[in] crypto_info_handle Handle to Crypto info that needs to be released.

  \retval MLResult_InvalidParam If one of parameters is invalid.
  \retval MLResult_Ok If operation succeeded.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecReleaseCryptoInfo(MLHandle crypto_info_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Create a new \ref MLMediaCodec.

  \param[in] method One of the creation methods defined by #MLMediaCodecCreation.
  \param[in] type One of the codec types defined by #MLMediaCodecType.
  \param[in] name_str If creating a codec by name, this is the name of the codec.
             If creating a codec by type, this is the mime type of the codec.
             Refer to APIs in \ref MLMediaCodecList for retrieving the list of names
             and mime types of supported codecs.
  \param[out] out_handle Upon successful return will point to handle to the created \ref MLMediaCodec.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaCodec object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecCreateCodec(MLMediaCodecCreation method, MLMediaCodecType type, const char *name_str, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Destroy a \ref MLMediaCodec.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok \ref MLMediaCodec object was successfully destroyed.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecDestroy(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Set callbacks to notify client codec events. Client needs to implement the callback functions.

   If the client intends to use the codec component in asynchronous mode, a valid callback should be
   provided before MLMediaCodecConfigure is called.
   When asynchronous callback is enabled, the client should not call:
     - MLMediaCodecDequeueInputBuffer
     - MLMediaCodecDequeueOutputBuffer
   Calling those functions will return MLMediaGenericResult_InvalidOperation.

   Also, MLMediaCodecFlush() behaves differently in asynchronous mode.
   After calling MLMediaCodecFlush, you must call MLMediaCodecStart() to "resume" receiving
   input buffers, even if an input surface was created.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] callbacks Set of codec callbacks. Can be set to NULL to unset all the callback altogether.
  \param[in] user_data Pointer to user payload data.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok callback was set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecSetCallbacksEx(MLHandle handle, MLMediaCodecCallbacksEx *callbacks, void *user_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Registers a callback to be invoked when an output frame is available or rendered on the output surface.

   This method can be called in any codec state, but will only have an effect in the
   "Executing" state for codecs that render buffers to the output surface.

   Note:
   - This callback is for informational purposes only: to get precise render timing samples,
     and can be significantly delayed and batched.
     Some frames may have been rendered even if there was no callback generated.
   - This callback doesn't set the codec to operate in asynchrous mode.
   - Since audio codec doesn't use Surface, this callback as no effect when audio codec is
     instantiated.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] callbacks Set of codec callbacks. Can be set to NULL to unset all the callback altogether.
  \param[in] user_data Pointer to user payload data.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok callback was set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecSetOutputFrameListener(MLHandle handle, MLMediaCodecOutputFrameListener *callbacks, void *user_data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Obtain the name of the created codec.

  User shall allocate at least #MAX_CODEC_NAME_SIZE bytes of memory for
  storing the output name string.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[out] out_name Pointer to the user-maintained buffer for storing
              the output C-style name string.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaCodec name was retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecGetName(MLHandle handle, char *out_name);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Configure the \ref MLMediaCodec.

  Encoder configuration: surface_handle and crypto_handle should be 0.
  Decoder Configuration:
    The surface_handle should be provided if using output surface.
    The crypto_handle should be provided for encrypted content.

  The output surface can be:
    - Native surface created by MLNativeSurfaceCreate().
    - Native surface texture created by MLNativeSurfaceTextureCreate().
    - The surface object created on an encoder using MLMediaCodecCreateInputSurface().
    - Pass 0 or ML_INVALID_HANDLE if the codec does not generate raw video output (e.g. not a video decoder)
      and/or if you want to configure the codec with CPU bound output buffers.
  NOTE that:
    1. For the first 3 cases (above), the decoded output of the decoder will be consumed direclty by the surface.
       This allows implementation of fast, zero-copy raw video consumption operation.
       Also, calling #MLMediaCodecGetOutputBufferPointer will return MLMediaGenericResult_InvalidOperation
    2. For the last case, user will have to explictly consume the output of the decoder by calling
       #MLMediaCodecGetOutputBufferPointer.

  \apilevel 6

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] format_handle #MLHandle to the #MediaFormat object.
  \param[in] surface_handle #MLHandle to the Surface object.
  \param[in] crypto_handle #MLHandle to the #MediaCrypto object.
             Pass 0 for clear content.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok \ref MLMediaCodec was configured successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecConfigure(MLHandle handle, MLHandle format_handle, MLHandle surface_handle, MLHandle crypto_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Start the codec.

  Shall be called upon successful configuration.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok \ref MLMediaCodec was started successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecStart(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Stop the codec.

  Codec is stopped and not destroyed, therefore can be started again.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok \ref MLMediaCodec was stopped successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecStop(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Reset the codec.

  This will reset the codec to initial (Uninitialized) state.
  Call this when:
      - Input or output queuing operation fails.
      - An error is notified through the asynchronous event MLMediaCodecCallbacks.on_error.

  Resetting a codec can fail when an unrecoverable error occurs (which is Hardare codec implementation specific),
  in which case codec will be in unusable state and should be destroyed using #MLMediaCodecDestroy.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok \ref MLMediaCodec was stopped successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecReset(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Flush the both the input and output ports of the codec.

  Upon return, all indices previously returned in calls to
  MLMediaCodecDequeueInputBuffer() and MLMediaCodecDequeueOutputBuffer()
  become invalid, and all buffers are owned by the codec.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.

  \retval MLResult_InvalidParam \ref MLMediaCodec object is invalid.
  \retval MLResult_Ok \ref MLMediaCodec was flushed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecFlush(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Communicate additional parameter changes to a codec.

  Dynamically modify or add configuration parameters to a configured or started codec.

  Create an empty \ref MLMediaFormat object using #MLMediaFormatCreate() and set the appropriate parameters. For
  more details, refer to ml_media_format.h.

  \note Some of these parameter changes may silently fail to apply. Unless specified below,
        an error will be returned on unsuccesful application.

  Parameters and associated values that may be applied are:
    - MLMediaFormat_Key_Parameter_Video_Bitrate:
      * Dynamically change the video encoder's target bitrate.
      * Associated value is an int32_t representing the new encode bitrate in bits-per-second.
      * Applicable to any video encoder.
    - MLMediaFormat_Key_Parameter_Request_Sync_Frame:
      * Communicate to the encoder to produce a sync frame soon.
      * Associated value is an int32_t with the value 0.
      * Applicable to any video encoder.
    - MLMediaFormat_Key_Parameter_Drop_After:
      * Set the time after which samples should be dropped and not submitted to the encoder.
      * Associated value is an int64_t value representing the system time in micro-seconds.
      * Applicable to an encoder receiving input from a surface.
    - MLMediaFormat_Key_Parameter_Drop_Before:
      * Set the time before which samples should be dropped and not submitted to the encoder.
      * Associated value is an int64_t value representing the system time in micro-seconds.
      * Applicable to an encoder receiving input from a surface.
    - MLMediaFormat_Key_Parameter_Set_Suspend:
      * Temporarily suspend or resume video encoding of input data. When suspended, all incoming buffers are discarded until suspension is lifted.
      * Used in conjunction with MLMediaFormat_Key_Parameter_Set_Suspend_Time to speficy the time of suspension or resumption.
      * Associated value is an int32_t value with the value 1 or 0 to suspend or resume, respectively.
      * Applicable to an encoder receiving input from a surface.
    - MLMediaFormat_Key_Parameter_Set_Suspend_Time:
      * Specifies the time when the action associated with the value of MLMediaFormat_Key_Parameter_Set_Suspend should take effect.
      * Associated value is an int64_t value representing the system time, in micro-seconds, indicating when suspendion or resumption takes effect.
      * Applicable to an encoder receiving input from a surface.
    -  MLMediaFormat_Key_Parameter_Time_Offset:
      * Describes an offset to adjust timestamps going forward on a video endcoder.
      * Associated value is an int64_t value representing the offset timestamp, in micro-seconds.
      * Applicable to an encoder receiving input from a surface.
    - MLMediaFormat_Key_Operating_Rate:
      * Describes the rate at which a codec is expected to operate. For video, this is the operating frame rate; for audio, this is the sample rate.
      * Associated value is a float value representing either the frames-per-second or the samples-per-second for video or audio, respectively.
      * Applicable to any codec.
      * Note: This key is ignored if it fails to apply.
      * Note: This key can also be set as part of the MLMediaFormat provided at configure-time.
    - MLMediaFormat_Key_Intra_Refresh_Period:
      * Describes the period of intra refresh in frames.
      * Associated value is a int32_t value representing the period in frames after which the whole frame is completely refreshed.
      * Applicable to any video encoder.
      * Note: This key is ignored if not supported by the codec or it fails to apply.
      * Note: This key can also be set as part of the MLMediaFormat provided at configure-time.
    - MLMediaFormat_Key_Latency:
      * Describes the latency, in frames, a video encoder should have queued up before outputting at least one output frame.
      * Associated value is an int32_t value representing the latency, in number of frames.
      * Applicable to any video encoder.
      * Note: This key is ignored if not supported by the codec or it fails to apply.
      * Note: This key can also be set as part of the MLMediaFormat provided at configure-time.

  \apilevel 9

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] format_handle #MLHandle to the \ref MLMediaFormat containing the parameters to set.

  \retval MLResult_InvalidParam At least one of the input parameters or one of the format parameter values is invalid.
  \retval MLResult_Ok The operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation At least one format parameter is not applicable.
  \retval MLMediaGenericResult_NoInit MLMediaCodec was not initialized.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecSetParameters(MLHandle handle, MLHandle format_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Obtain a writable buffer pointer for a dequeued
  input buffer index to contain the input data.

  After calling this method any buffer pointer previously
  returned for the same input index MUST no longer be used.

  Note: For VIDEO encoder, this API will fail if an input surface was created by #MLMediaCodecCreateInputSurface
  (see return value documentation below).

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] buffer_index The index of a client-owned input buffer
             previously returned from a call to
             MLMediaCodecDequeueInputBuffer().
  \param[out] out_buffer_ptr Pointer to returned input buffer.
  \param[out] out_buffer_size Size of returned input buffer.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Input buffer pointer is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Buffer pointer could not be retrieved. Note that this API
          returns MLMediaGenericResult_InvalidOperation especially if video encoder has hardware input surface
          (see #MLMediaCodecCreateInputSurface), and thus, out_buffer_ptr will be set to NULL and
          out_buffer_size set to 0.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecGetInputBufferPointer(MLHandle handle, int64_t buffer_index, uint8_t **out_buffer_ptr, size_t *out_buffer_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Obtain a read-only buffer pointer for a dequeued output
  buffer index.

  The position and limit of the returned buffer are set to the valid output data.
  After calling this method any buffer pointer previously returned for the same output
  index MUST no longer be used.

  Note: For VIDEO decoder, this API will fail if codec was configured with a hardware surface
  (see return value documentation below).

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] buffer_index The index of a client-owned output buffer
             previously returned from a call to
             MLMediaCodecDequeueOutputBuffer().
  \param[out] out_buffer_ptr Pointer to returned output buffer.
  \param[out] out_buffer_size Size of returned output buffer.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Output buffer pointer is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation Buffer pointer could not be retrieved. Note that this API
          returns MLMediaGenericResult_InvalidOperation especially if codec was VIDEO and configured
          with a hardware surface using #MLMediaCodecConfigure(), and thus, out_buffer_ptr
          will be set to NULL and out_buffer_size set to 0 since decoded buffer lives in GPU memory and is
          not accessible via a pointer.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecGetOutputBufferPointer(MLHandle handle, int64_t buffer_index, const uint8_t **out_buffer_ptr, size_t *out_buffer_size);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief After filling a range of the input buffer at the specified index
  submit it to the component.

  Once an input buffer is queued to the codec, it MUST NOT be used until it is later retrieved by
  MLMediaCodecGetInputBufferPointer() in response to a MLMediaCodecDequeueInputBuffer() return value.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] buffer_index Index of a client-owned input buffer previously returned
             in a call to MLMediaCodecDequeueInputBuffer().
  \param[in] offset Byte offset into the input buffer at which the data starts.
  \param[in] size Number of bytes of valid input data.
  \param[in] time_us Presentation timestamp in microseconds for this buffer.
             This is normally the media time at which this buffer should
             be presented (rendered).
  \param[in] flags A bitmask of flags defined by #MLMediaCodecBufferFlag.
             While not prohibited, most codecs do not use the
             #MLMediaCodecBufferFlag_KeyFrame flag for input buffers.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Intput buffer is queued successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecQueueInputBuffer(MLHandle handle, int64_t buffer_index, int64_t offset, size_t size, uint64_t time_us, int flags);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Similar to queueInputBuffer but submits a buffer that is potentially encrypted.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] buffer_index Index of a client-owned input buffer previously returned
             in a call to MLMediaCodecDequeueInputBuffer().
  \param[in] offset Byte offset into the input buffer at which the data starts.
  \param[in] crypto_info_handle Metadata required to facilitate decryption,
             the object can be reused immediately after this call returns.
  \param[in] time_us Presentation timestamp in microseconds for this
             buffer. This is normally the media time at which this
             buffer should be presented (rendered).
  \param[in] flags A bitmask of flags defined by #MLMediaCodecBufferFlag.
             While not prohibited, most codecs do not use the
             #MLMediaCodecBufferFlag_KeyFrame flag for input buffers.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Secure Intput buffer is queued successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecQueueSecureInputBuffer(MLHandle handle, int64_t buffer_index, int64_t offset, MLHandle crypto_info_handle, uint64_t time_us, int flags);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Dequeue an input buffer from buffer queue.

  This method will return immediately if timeoutUs == 0, wait indefinitely
  for the availability of an input buffer if timeoutUs < 0 or wait up
  to "timeoutUs" microseconds if timeoutUs > 0.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] timeout_us Timeout in microseconds.
             Negative timeout indicates "infinite".
  \param[out] out_buffer_index Index of an Input buffer from buffer queue,
              or #MLMediaCodec_TryAgainLater status.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Intput buffer is dequeued successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation if the codec is configured to operate in async mode.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecDequeueInputBuffer(MLHandle handle, int64_t timeout_us, int64_t *out_buffer_index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Dequeue an output buffer from buffer queue.

  This method will return immediately if timeoutUs == 0, wait indefinitely
  for the availability of an input buffer if timeoutUs < 0 or wait up
  to "timeoutUs" microseconds if timeoutUs > 0.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[out] out_buffer_info Will be filled with buffer meta data.
  \param[in] timeout_us Timeout in microseconds.
             Negative timeout indicates "infinite".
  \param[out] out_buffer_index Index of an output buffer from buffer queue,
              or one of the statuses defined by #MLMediaCodecOutputBufferStatus.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Output buffer is dequeued successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation if the codec is configured to operate in async mode.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecDequeueOutputBuffer(MLHandle handle, MLMediaCodecBufferInfo *out_buffer_info, int64_t timeout_us, int64_t *out_buffer_index);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Obtain input format supported by the codec.

  Call this function, after successful codec configuration, to determine
  what optional configuration parameters were supported by the codec.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[out] out_format_handle Input format supported by the codec.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Input Media format is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecGetInputFormat(MLHandle handle, MLHandle *out_format_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Return output format supported by the codec, or the format to which the configuration has changed.

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[out] out_format_handle Output format supported by the codec,
              or the format to which the configuration has changed.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Output Media format is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecGetOutputFormat(MLHandle handle, MLHandle *out_format_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Create an input surface for a hardware encoder.

  Requests an input surface to use as the input to an encoder, in place of input buffers.

  This API must only be called after MLMediaCodecConfigure() and before MLMediaCodecStart()
  otherwise the operation will fail and an input surface cannot be created.

  An input surface allows video consumers, such as a video encoder, to process raw input video
  buffers natively. The input surface is intended to act as a destination surface for your input data.

  When using an input surface, there are no accessible input buffers, as buffers are automatically
  passed from the input surface to the codec. In synchronous mode, calling MLMediaCodecDequeueInputBuffer()
  will return MLMediaGenericResult_InvalidOperation. In asynchronous mode, the client will not be
  notified when an input buffer is available (i.e. the on_input_buffer_available callback will not fire).

  The returned input surface can be passed as a destination surface to a decoder when calling
  MLMediaCodecConfigure(). Decoded output of the decoder can be consumed direclty as input
  to an encoder without copying. This allows implementation of fast, zero-copy transcoding.

  The returned input surface can also be passed as a destination surface to:
    - A video capture session when using #MLCameraConnectFlag_CamOnly.
    - A virtual capture session when using #MLCameraConnectFlag_VirtualOnly .
    - A mixed reality capture session when using #MLCameraConnectFlag_MR.
  Captured raw video frames will be consumed directly as input to an encoder without copying.

  The user of this API is responsible for calling #MLMediaCodecReleaseSurface() on the Surface when done.

  \apilevel 9

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[out] out_input_surface_handle #MLHandle to created input native surface. Valid only if result is MLResult_Ok.

  \retval MLResult_AllocFailed The operation failed to allocate the surface.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Input input surface was created successfully.
  \retval MLMediaGenericResult_AlreadyExists An input surface has already been created for the given handle.
  \retval MLMediaGenericResult_InvalidOperation MLMediaCodec is not an encoder.
  \retval MLMediaGenericResult_NoInit MLMediaCodec was not initialized.
  \retval MLMediaGenericResult_UnspecifiedFailure Input surface could not be created.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecCreateInputSurface(MLHandle handle, MLHandle *out_input_surface_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Release the Surface that was created by #MLMediaCodecCreateInputSurface.

  \apilevel 9

  \param[in] handle #MLHandle to the \ref MLMediaCodec.
  \param[in] input_surface_handle #MLHandle to the internal Surface object.

  \retval MLResult_InvalidParam #MLHandle is invalid.
  \retval MLResult_Ok Surface object was successfully released.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_InvalidOperation MLMediaCodec is not an encoder.
  \retval MLMediaGenericResult_NoInit MLMediaCodec was not initialized.

  \permissions None

*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecDestroyInputSurface(MLHandle handle, MLHandle input_surface_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Signal end-of-stream on input to a surface.

  This may only be used with encoders receiving input from a surface created by #MLMediaCodecCreateInputSurface().

  Equivalent to submitting an empty buffer with MLMediaCodecBufferFlag_EOS set when queueing an input buffer.

  \apilevel 9

  \param[in] handle #MLHandle to the \ref MLMediaCodec.

  \retval MLResult_InvalidOperation MLMediaCodec is not an encoder or MLMediaCodec is not receving input from a surface.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok The operation was successful.
  \retval MLMediaGenericResult_NoInit MLMediaCodec was not initialized.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecSignalEndOfInputStream(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Release buffer to codec or to render it on output surface.

  If codec is configured with an output surface, setting render
  to \c true will send the buffer to that output surface. The surface
  will release the buffer back to the codec once it is no longer
  used/displayed.

  Once an output buffer is released to codec, it MUST NOT
  be used until it is later retrieved by MLMediaCodecGetOutputBufferPointer()
  in response to a MLMediaCodecDequeueOutputBuffer() return value.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec object.
  \param[in] buffer_index Index of a client-owned output buffer previously returned
             from a call to MLMediaCodecDequeueOutputBuffer().
  \param[in] render If a valid surface was specified when configuring the
             codec, passing \c true renders this output buffer to the surface.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Output buffer was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecReleaseOutputBuffer(MLHandle handle, int64_t buffer_index, bool render);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.

  \brief Update surface timestamp and returns it to the codec to render
  it on the output surface. If codec is not configured with output
  surface, this call simply returns the buffer to codec.

  The timestamp may have special meaning depending on the destination
  surface.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLMediaCodec object.
  \param[in] buffer_index Index of a client-owned output buffer previously returned
             from a call to MLMediaCodecDequeueOutputBuffer().
  \param[in] timestamp_ns The timestamp in nanoseconds to associate with this buffer when
             it is sent to the Surface.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Output buffer was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaCodecReleaseOutputBufferAtTime(MLHandle handle, int64_t buffer_index, int64_t timestamp_ns);

/*! \} */

ML_EXTERN_C_END