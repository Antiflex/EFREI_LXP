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
  \defgroup MediaPlayer Media Player
  \addtogroup MediaPlayer
  \sharedobject native_surface.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/a-hardware-buffer
            https://developer.android.com/ndk/reference/group/media#aimagereader
            https://developer.android.com/reference/kotlin/android/hardware/HardwareBuffer

  \brief APIs for creaitng native surface (or surface texture) that works with graphics.

  To stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

/*!
  \brief Number of acquired buffers to be requested in functions #MLNativeSurfaceCreate and
  MLNativeSurfaceTextureCreate.
*/
typedef enum MLNativeSurfaceAcquiredBufferCount{
  /*! Min number of buffer count. */
  MLNativeSurfaceAcquiredBufferCount_Min = 1,
  /*! Max number of buffer count. */
  MLNativeSurfaceAcquiredBufferCount_Max = 16,
  /*! Ensure enum is represented as 32 bits. */
  MLNativeSurfaceAcquiredBufferCount_Ensure32Bits = 0x7FFFFFFF
}MLNativeSurfaceAcquiredBufferCount;

/*!
  \brief Pixel format to use when creating the native surface.
  Used in functions #MLNativeSurfaceCreate and MLNativeSurfaceTextureCreate.
*/
typedef enum MLNativeSurfacePixelFormat {
  /*! Custom format. */
  MLNativeSurfacePixelFormat_Custom        = -4,
  /*! Translucent format. */
  MLNativeSurfacePixelFormat_Translucent   = -3,
  /*! Transparent format. */
  MLNativeSurfacePixelFormat_Transparent   = -2,
  /*! Opaque format. */
  MLNativeSurfacePixelFormat_Opaque        = -1,
  /*! None. */
  MLNativeSurfacePixelFormat_None          = 0,
  /*! Below enums should match android_pixel_format_t in graphics-base-v1.0.h header. */
  /*! 4x8-bit RGBA format. */
  MLNativeSurfacePixelFormat_Rgba8888      = 1,
  /*! 4x8-bit RGBX format. */
  MLNativeSurfacePixelFormat_Rgbx8888      = 2,
  /*! 3x8-bit RGB format. */
  MLNativeSurfacePixelFormat_Rgb888        = 3,
  /*! 16-bit RGB format. */
  MLNativeSurfacePixelFormat_Rgb565        = 4,
  /*! 4x8-bit BGRA format. */
  MLNativeSurfacePixelFormat_Bgra8888      = 5,
  /*! 64-bit RGBA format. */
  MLNativeSurfacePixelFormat_RgbaFp16      = 22,
  /*! 32-bit RGBA format. */
  MLNativeSurfacePixelFormat_Rgba1010102   = 43,
  /*! Ensure enum is represented as 32 bits. */
  MLNativeSurfacePixelFormat_Ensure32Bits = 0x7FFFFFFF
} MLNativeSurfacePixelFormat;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief NativeSurface/NativeSurfaceTexture Output Frame Availability information.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLNativeSurfaceFrameAvailableInfo {
  /*! User data as passed in MLNativeSurfaceSetOnFrameAvailableCallback() or MLNativeSurfaceTextureSetOnFrameAvailableCallback(). */
  void *user_data;
} MLNativeSurfaceFrameAvailableInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Configuration values for creating the Native Surface.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLNativeSurfaceConfig {
  /*! Version of this structure. */
  uint32_t version;

  /*! Pixel format from #MLNativeSurfacePixelFormat to the NativeSurface to be created. */
  MLNativeSurfacePixelFormat pixel_format;

  /*! Number of buffers to be acquired. Refer to #MLNativeSurfaceAcquiredBufferCount for acceptable range of buffer count. */
  uint16_t buffer_count;

  /*! Default width of the buffer while dequeuing the buffer from consumer. This should be same as frame width.
      Invalid width (negative or 0) will result in failure to create the Surface with the error code MLResult_InvalidParam. */
  uint32_t width;

  /*! Default height of the buffer while dequeuing the buffer from consumer. This should be same as frame height.
      Invalid height (negative or 0) will result in failure to create the Surface with the error code MLResult_InvalidParam. */
  uint32_t height;

} MLNativeSurfaceConfig;

/*!
  \brief Initializes MLNativeSurfaceConfig with default values.

  \param[in,out] inout_config_values MLNativeSurfaceConfig structure defined by #MLNativeSurfaceConfig that needs to be initialized.
*/
ML_STATIC_INLINE void MLNativeSurfaceConfigInit(MLNativeSurfaceConfig *inout_config_values)
{
  if (inout_config_values) {
    inout_config_values->version = 1;
    inout_config_values->width = 0;
    inout_config_values->height = 0;
    inout_config_values->buffer_count = 1;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Callbacks for notifying when an output frame is available for consumption.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLNativeSurfaceOnFrameAvailableCallback {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief This callback is invoked when the raw video frame is available for consumption
    on client side.

    Client should implement this callback when they want to use raw video frame as a texture mapped
    to 3D geometry, for example.

    This callback is typically fired when the when a raw frame is available for consumption,
    such as when the decoded output buffer has been released by the decoder OR camera produces a frame.

    \param[in] handle MLNativeSurface or MLNativeSurfaceTexture handle for which callback was called.
    \param[in] info Output Frame availability info as MLNativeSurfaceFrameAvailableInfo.
  */
  void (*on_frame_available)(MLHandle handle, const MLNativeSurfaceFrameAvailableInfo *info);
} MLNativeSurfaceOnFrameAvailableCallback;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initializes MLNativeSurfaceOnFrameAvailableCallback with default values.

  \param[in,out] inout_callbacks MLNativeSurfaceOnFrameAvailableCallback Callback structure defined by #MLNativeSurfaceOnFrameAvailableCallback that needs to be initialized.
*/
ML_STATIC_INLINE void MLNativeSurfaceOnFrameAvailableCallbackInit(MLNativeSurfaceOnFrameAvailableCallback *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 1;
    inout_callbacks->on_frame_available = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new NativeSurface.

  The NativeSurface created through this API should be released using MLNativeSurfaceRelease
  once done using it.

  \apilevel 20

  \param[in]  config_values Configuration values for creating the native surface, refer #MLNativeSurfaceConfig for more details.
  \param[out] out_handle Upon successful return will point to handle to the created NativeSurface.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed Failed to allocate memory for surface.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok NativeSurface object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceCreate(const MLNativeSurfaceConfig *config_values, MLHandle* out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release a NativeSurface.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurface.

  \retval MLResult_InvalidParam NativeSurface object is invalid.
  \retval MLResult_Ok NativeSurface object was successfully released.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceRelease(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Gets an implementation of NativeWindow that feeds graphic buffers into MLNativeSurface.

  This function returns the platform-dependent native window typically used by Graphics API or HW decoders to render frames.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
             This handle can be:
             - Surface created on an Encoder using #MLMediaCodecCreateInputSurface.
             - The output surface created using #MLNativeSurfaceCreate.
             - The output surface created using #MLNativeSurfaceTextureCreate.
  \param[out] out_native_window Native window as MLHandle on success.
  \param[out] out_format Native window format on success and for valid pointer, which will be used as EGL_NATIVE_VISUAL_ID.

  \retval MLResult_InvalidParam NativeSurface object is invalid or out_native_window is NULL.
  \retval MLResult_Ok Native window is successfully retrieved.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceGetNativeWindow(MLHandle handle, MLHandle *out_native_window, int32_t *out_format);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Releases NativeWindow previously acquired by #MLNativeSurfaceGetNativeWindow.

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[in] native_window Native window handle acquired through #MLNativeSurfaceGetNativeWindow.

  \retval MLResult_InvalidParam NativeSurface or NativeWindow object is invalid.
  \retval MLResult_Ok Native window is successfully released.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceReleaseNativeWindow(MLHandle handle, MLHandle native_window);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Consume next available buffer.

  Note: This function is non-blocking and should only be called from the rendering
  thread *after* #on_frame_available callback has been fired.

  Note: The returned buffer's color format is multi-planar YUV420. Since our
  underlying hardware interops do not support multiplanar formats, advanced
  texture features like mipmaping, anisotropic filtering and MSAA will *not*
  work on those returned buffers. If such advanced texturing features are
  required, one has to acquire the YUV buffers as usual and *render* to an
  RGB texture and only then, will one be able to enable hardware optimization
  for such advanced texture features.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[out] out_native_buffer A pointer to the acquired native buffer of the frame.
              When buffer is not required anymore, caller must call
              MLNativeSurfaceReleaseFrame() with this nativeBuffer handle to free up
              queuing space for incoming buffers.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Next available frame is acquired successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \retval MLMediaGenericResult_NotEnoughData Native buffer is not available yet to acquire.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceAcquireNextAvailableFrame(MLHandle handle, MLHandle *out_native_buffer);

struct AHardwareBuffer;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Acquire an AHardwareBuffer* from a native buffer handle.

  \apilevel 20

  The AHardwareBuffer* can be used with the Vulkan extension VK_ANDROID_external_memory_android_hardware_buffer
  to get the hardware buffer format properties, which can then be used to bind this hardware buffer to a VkImage.
  Caller is responsible for releasing the AHardwareBuffer by calling AHardwareBuffer_release() after its usage.

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance. Pass #ML_INVALID_HANDLE when using with native
              buffers acquired without a \ref MLNativeSurface, like in the case of ml_webview api.
  \param[in] native_buffer The native buffer handle acquired from a \ref MLNativeSurfaceAcquireNextAvailableFrame call.
  \param[out] out_hardware_buffer The AHardwareBuffer pointer to the imported surface.
  \param[out] out_width Width of the imported surface.
  \param[out] out_height Height of the imported surface.

  \retval MLResult_InvalidParam Import was not performed due to an invalid parameter.
  \retval MLResult_Ok Surface was acquired successfully.
  \retval MLResult_UnspecifiedFailure Import was not performed due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceAcquireHardwareBufferFromNativeBuffer(MLHandle handle, MLHandle native_buffer, struct AHardwareBuffer **out_hardware_buffer, uint32_t *out_width, uint32_t *out_height);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release a native buffer previously acquired.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[in] native_buffer The native buffer for the frame to release.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Frame was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceReleaseFrame(MLHandle handle, MLHandle native_buffer);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieves the 4x4 texture coordinate transform matrix associated with
  the last acquired Frame.

  This transform matrix maps 2D homogeneous texture coordinates of the form
  (s, t, 0, 1) with s and t in the inclusive range [0, 1] to the texture
  coordinate that should be used to sample that location from the texture.
  Sampling the texture outside of the range of this transform is undefined.

  This transform is necessary to compensate for transforms that the stream
  content producer may implicitly apply to the content. By forcing users of
  a GLConsumer to apply this transform we avoid performing an extra
  copy of the data that would be needed to hide the transform from the
  user.

  The matrix is stored in column-major order.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[out] out_mtx A pointer to an array of 16 floats that will receive retrieved
              transformation matrix.

  \return MLResult_InvalidParam One of the parameters is invalid.
  \return MLResult_Ok Transformation matrix was returned.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceGetFrameTransformationMatrix(MLHandle handle, float out_mtx[16]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieves the timestamp associated with the last acquired frame.
  The timestamp is in nanoseconds, and is monotonically increasing from
  beginning of the playback. Its other semantics (zero point, etc) are
  codec-dependent and should be documented by the codec vendor.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[out] out_timestamp_ns A pointer to user variable for storing retrieved timestamp.

  \return MLResult_InvalidParam One of the parameters is invalid.
  \return MLResult_Ok Timestamp was returned.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceGetFrameTimestamp(MLHandle handle, int64_t *out_timestamp_ns);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieves the QueueBuffer timestamp associated with the last acquired Frame
  This timestamp is for profiling purposes only and corresponds to the time when this
  frame was queued by internal Codec's producer code. The timestamp is in nanoseconds,
  and is monotonically increasing from beginning of playback. Its other semantics
  (zero point, etc) are codec-dependent and should by documented by the codec vendor.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[out] out_timestamp_ns A pointer to user variable for storing retrieved timestamp.

  \return MLResult_InvalidParam One of the parameters is invalid.
  \return MLResult_Ok Timestamp was returned.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceGetFrameQueueBufferTimestamp(MLHandle handle, int64_t *out_timestamp_ns);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieves the last acquired frame number.
  The frame number is an incrementing counter set to 0 at Codec configuration time.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[out] out_number A pointer to user variable for storing retrieved frame number.

  \return MLResult_InvalidParam One of the parameters is invalid.
  \return MLResult_Ok Frame number was returned.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceGetFrameNumber(MLHandle handle, uint64_t *out_number);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieves the cropping rectangle of the current frame/buffer.

  The Frame crop is returned as {left, bottom, width, height}.

  \apilevel 20

  \param[in] handle #MLHandle to the \ref MLNativeSurface instance.
  \param[out] out_crop_rect A pointer to user variable for storing retrieved Crop.

  \return MLResult_InvalidParam One of the parameters is invalid.
  \return MLResult_Ok Frame Crop was returned.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceGetFrameCropRect(MLHandle handle, MLRecti *out_crop_rect);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set callback to notify client when a frame is available.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurface.
  \param[in] callback A MLNativeSurfaceOnFrameAvailableCallback function.
  \param[in] user_data Pointer to user payload data.

  \retval MLResult_InvalidParam \ref MLNativeSurface object is invalid.
  \retval MLResult_Ok Callback was set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.
  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceSetOnFrameAvailableCallback(MLHandle handle, const MLNativeSurfaceOnFrameAvailableCallback *callback, void *user_data);

/*! Graphic backend to use.

  \apilevel 20
*/
typedef enum MLNativeSurfaceTextureBackend {
  /*! OpenGL texture. */
  MLNativeSurfaceTextureBackend_OpenGL = 0,
  /*! Ensure enum is represented as 32 bits. */
  MLNativeSurfaceTextureBackend_Ensure32Bits = 0x7FFFFFFF
} MLNativeSurfaceTextureBackend;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a new NativeSurfaceTexture.

  \apilevel 20

  \param[in]  config_values Configuration values for creating the native surface, refer #MLNativeSurfaceConfig for more details.
  \param[in]  backend The graphic backend to use.
  \param[out] out_handle Upon successful return will point to handle to the created NativeSurfaceTexture.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed Failed to allocate memory for surface.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok NativeSurfaceTexture object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureCreate(const MLNativeSurfaceConfig *config_values, MLNativeSurfaceTextureBackend backend,
    MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release a NativeSurfaceTexture.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok NativeSurfaceTexture object was successfully released.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureRelease(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Update the texture image to the most recent frame from the image stream.

  May only be called on the thread with the graphic context that contains the texture object.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok the texture was updated successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureUpdateTexImage(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Attach the NativeSurfaceTexture to the graphic context that is current on the calling thread.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.
  \param[in] texture_id The graphic texture object id.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok the texture was detached successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureAttachToGLContext(MLHandle handle, uint32_t texture_id);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Detach the NativeSurfaceTexture from the graphic context that owns the graphic texture object.

  If called on the thread with graphic context that contains the attached texture object, said
  texture will be deleted.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok the texture was detached successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureDetachFromGLContext(MLHandle handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieve the 4x4 texture coordinate transform matrix associated with the texture image set by the most recent
         call to MLNativeSurfaceTextureUpdateTexImage.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.
  \param[out] out_matrix A 4x4 matrix stored in column-major order as 16 consecutive values.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok Operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureGetTransformationMatrix(MLHandle handle, float out_matrix[16]);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Retrieve the timestamp associated with the texture image set by the most recent call to
         MLNativeSurfaceTextureUpdateTexImage.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.
  \param[out] out_timestamp_ns The timestamp in nanoseconds.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok Operation was successful.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureGetTimestamp(MLHandle handle, int64_t *out_timestamp_ns);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set callback to notify client when a frame is available.

  \apilevel 20

  \param[in] handle #MLHandle to the NativeSurfaceTexture.
  \param[in] callback A MLNativeSurfaceTextureOnFrameAvailableCallback function.
  \param[in] user_data Pointer to user payload data.

  \retval MLResult_InvalidParam NativeSurfaceTexture object is invalid.
  \retval MLResult_Ok Callback was set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLNativeSurfaceTextureSetOnFrameAvailableCallback(MLHandle handle,
    const MLNativeSurfaceOnFrameAvailableCallback *callback, void *user_data);

/*! \} */

ML_EXTERN_C_END
