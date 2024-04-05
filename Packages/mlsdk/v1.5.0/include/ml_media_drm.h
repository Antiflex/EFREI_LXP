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
  \sharedobject media_drm.magicleap

  \warning THIS API IS DEPRECATED IN FAVOR OF STANDARD ANDROID SDK AND NDK MEDIA APIs:
            https://developer.android.com/ndk/reference/group/media
            https://developer.android.com/reference/android/media/MediaPlayer.DrmInfo
            Developers are encouraged to use ExoPlayer for all media playback needs.

  \brief APIs for MediaDRM to obtain the content keys for decrypting protected media streams,
         in conjunction with ml_mediacrypto.

  Stringify the error codes returned by these APIs, call MLMediaResultGetString.
  \{
*/

typedef const char *MLMediaDRMProperty;

/*! String property name: identifies the maker of the DRM engine plugin. */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaDRMProperty MLMediaDRMProperty_Vendor;

/*! String property name: identifies the version of the DRM engine plugin. */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaDRMProperty MLMediaDRMProperty_Version;

/*! String property name: describes the DRM engine plugin. */
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaDRMProperty MLMediaDRMProperty_Description;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief String property name: a comma-separated list of cipher and mac algorithms
  supported by #CryptoSession. The list may be empty if the DRM engine
  plugin does not support #CryptoSession operations.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaDRMProperty MLMediaDRMProperty_Algorithms;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Byte array property name: the device unique identifier is established during
  device provisioning and provides a means of uniquely identifying each device.
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API extern MLMediaDRMProperty MLMediaDRMProperty_DeviceUniqueID;

/*! Data type containing byte array buffer and the size. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMByteArray {
  /*! Byte array buffer. */
  uint8_t *ptr;
  /*! Size of #ptr. */
  size_t length;
} MLMediaDRMByteArray;

/*! Data type containing list of byte array buffers and the size. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMByteArrayList {
  /*! Byte array buffer. */
  MLMediaDRMByteArray *ptr;
  /*! Length of #ptr. */
  size_t length;
} MLMediaDRMByteArrayList;

/*! Data type containing key/value pair. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMKeyValue {
  /*! Key. */
  const char *key;
  /*! Value. */
  const char *value;
} MLMediaDRMKeyValue;

/*! Data type containing array of key/value pair. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMKeyValueArray {
  /*! Array of key/value pair. */
  MLMediaDRMKeyValue *ptr;
  /*! Length of #ptr. */
  size_t length;
  /*! Index. */
  size_t index;
} MLMediaDRMKeyValueArray;

/*! Request types. */
typedef enum MLMediaDRMKeyType {
  /*!
    \brief This key request type specifies that the keys will be for online use, they will
    not be saved to the device for subsequent use when the device is not connected to a network.
  */
  MLMediaDRMKeyType_Streaming    = 1,
  /*!
    \brief This key request type specifies that the keys will be for offline use, they
    will be saved to the device for use when the device is not connected to a network.
  */
  MLMediaDRMKeyType_Offline      = 2,
  /*! This key request type specifies that previously saved offline keys should be released. */
  MLMediaDRMKeyType_Release      = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMKeyType_Ensure32Bits = 0x7FFFFFFF
} MLMediaDRMKeyType;

/*!
  \brief Request event types.

  \apilevel 7
*/
typedef enum MLMediaDRMEventType {
  /*!
    \brief This event type indicates that the app needs to request
    a certificate from the provisioning server.
    The request message data is obtained using MLMediaDRMGetProvisionRequest().
  */
  MLMediaDRMEventType_ProvisionRequired = 1,
  /*!
    \brief This event type indicates that the app needs to request keys from a license server.
    The request message data is obtained using MLMediaDRMGetKeyRequest().
  */
  MLMediaDRMEventType_KeyRequired       = 2,
  /*!
    \brief This event type indicates that the licensed usage duration for keys in a session has expired.
    The keys are no longer valid.
  */
  MLMediaDRMEventType_KeyExpired        = 3,
  /*!
    \brief This event may indicate some specific vendor-defined condition,
    see your DRM provider documentation for details.
  */
  MLMediaDRMEventType_VendorDefined     = 4,
  /*!
    \brief This event indicates that a session opened by the app has been
     reclaimed by the resource manager.
  */
  MLMediaDRMEventType_SessionReclaimed = 5,
  /*!
    \brief This event is issued when a session expiration update occurs,
     to inform the app about the change in expiration time.

     If MLMediaDRMEventCallbacks is setup with a valid on_expiration_update callback,
     then this event is not notified.
  */
  MLMediaDRMEventType_ExpirationUpdate = 6,
  /*!
    \brief This event is issued when the keys in a session change status,
     such as when the license is renewed or expires.

     If MLMediaDRMEventCallbacks is setup with a valid on_key_status_change callback,
     then this event is not notified.
  */
  MLMediaDRMEventType_KeysChange = 7,
  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMEventType_Ensure32Bits      = 0x7FFFFFFF
} MLMediaDRMEventType;

/*! Data type that encapsulates Key Request input arguments. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMKeyRequestInputParam {
  /*!
    \brief The container-specific data, its meaning is interpreted based on the
    mime-type provided in the mime_type parameter.
    It could contain, for example, the content ID, key ID or other data obtained
    from the content metadata that is required in generating the key request.
  */
  MLMediaDRMByteArray *init_data;
  /*! The mime type of the content. */
  char *mime_type;
  /*!
    \brief The type of the request.
    The request may be to acquire keys for streaming or offline content,
    or to release previously acquired keys, which are identified by a key_set_id.
  */
  MLMediaDRMKeyType key_type;
  /*!
    \brief Optional parameters included in the key request message to allow a client
    application to provide additional message parameters to the server.
  */
  MLMediaDRMKeyValueArray *optional_params;
} MLMediaDRMKeyRequestInputParam;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Data type that encapsulates either of the following along with an URL:

  For Key Request Message: an opaque key request byte array
  that should be delivered to the license server.

  For Provision Request Message: an opaque provision request byte array
  that should be delivered to the provisioning server.
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMRequestMessage {
  /*! The opaque request byte array. */
  MLMediaDRMByteArray request;
  /*! The recommended URL to deliver the request to. */
  char *default_URL;
} MLMediaDRMRequestMessage;

/*! Data type that encapsulates algorithm, key_set_id and IV for Encryption/Decryption. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMCryptoInputParam {
  /*!
    \brief The cipher mode used for the crypto operation.
    The only supported algorithm now is "AES/CBC/NoPadding".
  */
  char *algorithm;
  /*! The identifier for the key to be used. */
  MLMediaDRMByteArray *key_set_id;
  /*! The initial vector used for the crypto operation. */
  MLMediaDRMByteArray *iv;
} MLMediaDRMCryptoInputParam;

/*! Data type that encapsulates algorithm, key_set_id for HMAC based Sign/Verify. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMHMACInputParam {
  /*!
    \brief The MAC algorithm used for the MAC-HASH operation.
    The only supported algorithm now is "HmacSHA256".
  */
  char *algorithm;
  /*! The identifier for the key to be used. */
  MLMediaDRMByteArray *key_set_id;
} MLMediaDRMHMACInputParam;

/*! Data type that encapsulates algorithm, wrapped_key for RSA operation. */
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMRSAInputParam {
  /*!
    \brief The MAC algorithm used for padding/signing.
    The only supported algorithm now is "HmacSHA256".
  */
  char *algorithm;
  /*! The wrapped RSA key to be used. */
  MLMediaDRMByteArray *wrapped_rsa_key;
} MLMediaDRMRSAInputParam;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaDRM event info associated with a session.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMEventInfo {
  /*! DRM session id associated with the event. */
  MLMediaDRMByteArray *session_id;
  /*! Type of Media DRM event. */
  MLMediaDRMEventType event_type;
  /*! Extra Secondary error code. */
  int extra;
  /*! Optional data that may be associated with the event. */
  MLMediaDRMByteArray *event_data;
  /*! User data as passed to MLMediaDRMPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaDRMEventInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaDRM expiration update info associated with a session.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMExpirationUpdateInfo {
  /*! DRM session id associated with the event. */
  MLMediaDRMByteArray *session_id;
  /*!
    \brief The new expiration time for the keys in the session. The time is in milliseconds,
     relative to the Unix epoch. A time of 0 indicates that the keys never expire.
  */
  uint64_t expiration_time_ms;
  /*! User data as passed to MLMediaDRMPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaDRMExpirationUpdateInfo;

/*!
  \brief Status code associated with a DRM session key.

  \apilevel 20
*/
typedef enum MLMediaDRMKeyStatusCode {
   /*! The key is currently usable to decrypt media data. */
  MLMediaDRMKeyStatusCode_KeyStatusUsable = 0,

  /*! The key is no longer usable to decrypt media data because its expiration time has passed. */
  MLMediaDRMKeyStatusCode_KeyStatusExpired = 1,

  /*!
    \brief The key is not currently usable to decrypt media data because its output requirements
     cannot currently be met.
  */
  MLMediaDRMKeyStatusCode_KeyStatusOutputNotAllowed = 2,

  /*!
     \brief The status of the key is not yet known and is being determined.
      The status will be updated with the actual status when it has been determined.
  */
  MLMediaDRMKeyStatusCode_KeyStatusPending = 3,

  /*!
    \brief The key is not currently usable to decrypt media data because of an internal error in
     processing unrelated to input parameters. This error is not actionable by an app.
  */
  MLMediaDRMKeyStatusCode_KeyStatusInternalError = 4,

  /*! Ensure enum is represented as 32 bits. */
  MLMediaDRMKeyStatusCode_Ensure32Bits = 0x7FFFFFFF
} MLMediaDRMKeyStatusCode;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaDRM key status.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMKeyStatus {
  /*! KeyID that belongs to one of th DRM session key. */
  MLMediaDRMByteArray key_id;
  /*! Status code of the corresponding key. */
  MLMediaDRMKeyStatusCode status_code;
} MLMediaDRMKeyStatus;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief MediaDRM session keys status change info.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMKeyStatusInfo {
  /*! DRM session id associated with the event. */
  MLMediaDRMByteArray *session_id;
  /*! Number of KeyStatus entries. */
  size_t key_status_count;
  /*! Pointer to array of #MLMediaDRMKeyStatus of size key_status_count. */
  MLMediaDRMKeyStatus *key_status;
  /*!
    \brief Indicates if a key has been added that is usable, which may trigger an attempt to
     resume playback on the media stream if it is currently blocked waiting for a key.
  */
  bool has_new_usable_key;
  /*! User data as passed to MLMediaDRMPlayerSetEventCallbacksEx(). */
  void *data;
} MLMediaDRMKeyStatusInfo;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Callbacks for notifying client about MLMediaDRM events.

  User of MLMediaDRM should implement this.

  \apilevel 20
*/
typedef ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.") struct MLMediaDRMEventCallbacks {
  /*! Version of this structure. */
  uint32_t version;

  /*!
    \brief This callback function is invoked when specific MLMediaDrm events happen.

    \param[in] media_drm MediaDRM instance on which callback was set.
    \param[in] event_info MediaDRM info as MLMediaDRMEventInfo.
  */
  void (*on_event)(MLHandle media_drm, const MLMediaDRMEventInfo *event_info);

  /*!
    \brief This callback function is invoked when a drm session expiration update occurs.

     If this callback is not defined, then MLMediaDRMEventType_ExpirationUpdate event is notified
     through on_event callback, without the expiration time.

    \param[in] media_drm MediaDRM instance on which callback was set.
    \param[in] update_info Updated session info as MLMediaDRMEventInfo.
  */
  void (*on_expiration_update)(MLHandle media_drm, const MLMediaDRMExpirationUpdateInfo *update_info);

  /*!
    \brief This callback function is invoked when the keys in a drm session change states.

     If this callback is not defined, then MLMediaDRMEventType_KeysChange event is notified
     through on_event callback, without the key(s) status information.

    \param[in] media_drm MediaDRM instance on which callback was set.
    \param[in] key_status_info Changed key status as MLMediaDRMKeyStatusInfo.
  */
  void (*on_key_status_change)(MLHandle media_drm, const MLMediaDRMKeyStatusInfo *key_status_info);
} MLMediaDRMEventCallbacks;

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Initializes MLMediaDRMEventCallbacks with default values.

  \param[in,out] inout_callbacks MediaDRM Callback structure defined by #MLMediaDRMEventCallbacks that needs to be initialized.
*/
ML_STATIC_INLINE void MLMediaDRMEventCallbacksInit(MLMediaDRMEventCallbacks *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 1;
    inout_callbacks->on_event = NULL;
    inout_callbacks->on_expiration_update = NULL;
    inout_callbacks->on_key_status_change = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Allocate byte array buffer.

  \param[in] size Maximum size of the desirable byte array to be allocated.
  \param[out] out_array Pointer to byte array buffer that needs to be allocated.
              To free/release, call MLMediaDRMByteArrayRelease().

  \retval MLResult_AllocFailed Failed because of allocation failure.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Byte Array is allocated successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMByteArrayAllocate(size_t size, MLMediaDRMByteArray *out_array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Allocate and Copy to byte array buffer.

  \param[in] copy_from Buffer from which copy into byte array.
  \param[in] size Number of bytes to be copied.
  \param[out] out_array Pointer to byte array buffer that needs to be allocated and copied to.
              To free/release, call MLMediaDRMByteArrayRelease().

  \retval MLResult_AllocFailed Failed because of allocation failure.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Byte Array is allocated and copied successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMByteArrayAllocAndCopy(const uint8_t *copy_from, size_t size, MLMediaDRMByteArray *out_array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Allocate array of key/value pairs.

  \param[in] size Maximum size of the desirable array of key/value pair to be allocated.
  \param[out] out_array Pointer to array of key/value pair that needs to be allocated.
              To free/release, call MLMediaDRMKeyValueArrayRelease().

  \retval MLResult_AllocFailed Failed because of allocation failure.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Key/value pair array is allocated successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMKeyValueArrayAllocate(size_t size, MLMediaDRMKeyValueArray *out_array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Create a MLMediaDRM instance from a UUID.

  \param[in] uuid The universal unique ID of the crypto scheme. uuid must be 16 bytes.
  \param[out] out_handle Upon successful return will point to handle to the created MLMediaDRM.
              Or else, it will point to #ML_INVALID_HANDLE.

  \retval MLResult_AllocFailed MLMediaDRM object creation failed with resource allocation failure.
  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok MLMediaDRM object was created successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMCreate(MLUUID uuid, MLHandle *out_handle);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release the MLMediaDRM instance.

  \param[in] media_drm Handle to the MLMediaDRM.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok MLMediaDRM object was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMRelease(MLHandle media_drm);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release byte array buffer.

  \param[in] array Byte array buffer that needs to be released.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Byte Array was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMByteArrayRelease(MLMediaDRMByteArray *array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release list of byte array buffer.

  \param[in] array List of byte array buffer that needs to be released.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Byte Array List was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMByteArrayListRelease(MLMediaDRMByteArrayList *array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release key/value pair array.

  \param[in] array Key/value pair array that needs to be released.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok Key/value pair array was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMKeyValueArrayRelease(MLMediaDRMKeyValueArray *array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Release Request Message.

  \param[in] request Pointer to Request Message that needs to be released.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok DRM Request Message was released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMRequestMessageRelease(MLMediaDRMRequestMessage *request);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Add a key/value pair to the array of key/value pairs.

  \param[in] pair The source key/value pair that needs to be added.
  \param[out] out_array Pointer to array of key/value pair to which the pair needs to be added to.

  \retval MLResult_InvalidParam One of the parameters is invalid.
  \retval MLResult_Ok key/value pair is added successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMKeyValueArrayAdd(const MLMediaDRMKeyValue *pair, MLMediaDRMKeyValueArray *out_array);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Query if the given scheme identified by its UUID is supported on this device.
  And whether the drm plugin is able to handle the media container format.

  \param[in] uuid Identifies the universal unique ID of the crypto scheme. UUID must be 16 bytes.
  \param[in] mime_type The MIME type of the media container, e.g. "video/mp4".
             If mime_type is not known or required, it can be provided as NULL.
  \param[out] out_supported On successful return contains \c true or \c false based on
              whether the given crypto scheme is supported or not.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok The query has run successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMIsCryptoSchemeSupported(MLUUID uuid, const char *mime_type, bool *out_supported);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Register a callback to be invoked when DRM events or updates or status change occurs.

  \apilevel 20

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] callbacks Set of event callbacks. Can be set to NULL to unset the callbacks altogether.
  \param[in] data Custom data to be returned when any callback is fired.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok Event listener was set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMSetOnEventListenerEx(MLHandle media_drm, MLMediaDRMEventCallbacks *callbacks, void *data);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Opens a new session. A session ID is returned.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[out] out_session_id ID of the session created/opened.
              This byte array will be released when MLMediaDRMCloseSession() is called.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM session was opened successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMOpenSession(MLHandle media_drm, MLMediaDRMByteArray *out_session_id);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Closes a session on the MLMediaDRM object that was previously opened with openSession().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session, which will be released on return.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM session was closed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMCloseSession(MLHandle media_drm, MLMediaDRMByteArray *session_id);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key request/response exchange occurs between the app and a license server
  to obtain or release keys used to decrypt encrypted content.

  MLMediaDRMGetKeyRequest() is used to obtain an opaque key request byte array
  that is delivered to the license server.
  The opaque key request byte array is returned in out_key_request.request
  The recommended URL to deliver the key request to is returned in out_key_request.default_URL.

  After the app has received the key request response from the server,
  it should deliver to the response to the DRM engine plugin using the method
  MLMediaDRMProvideKeyResponse().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] key_request_param Placeholder for needed arguments for generating a key request message.
  \param[out] out_key_request Upon successful return, contains key request message.
              To free/release this, call MLMediaDRMRequestMessageRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Key Request message is constructed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMGetKeyRequest(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMKeyRequestInputParam *key_request_param, MLMediaDRMRequestMessage *out_key_request);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A key response is received from the license server by the app, then it is
  provided to the DRM engine plugin using MLMediaDRMProvideKeyResponse().

  When the response is for an offline key request, a key_set_id is returned that can be
  used to later restore the keys to a new session with restoreKeys().
  When the response is for a streaming or release request, a null key_set_id is returned.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] response The opaque response from the server.
  \param[out] out_key_set_id Upon successful return, contains the key identifier.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Key Response message was consumed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMProvideKeyResponse(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMByteArray *response, MLMediaDRMByteArray *out_key_set_id);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Restore persisted offline keys into a new session. key_set_id identifies the
  keys to load, obtained from a prior call to MLMediaDRMProvideKeyResponse().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] key_set_id The saved key set to restore.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Keys are restored successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMRestoreKeys(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMByteArray *key_set_id);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Remove the current keys from a session.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] key_set_id The keys to remove, which will be released on success.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Keys are removed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMRemoveKeys(MLHandle media_drm, MLMediaDRMByteArray *key_set_id);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Request an informative description of the key status for the session.

  The status is in the form of key/value pairs. Since DRM license policies vary by vendor,
  the specific status field names are determined by each DRM vendor. Refer to your
  DRM provider documentation for definitions of the field names for a particular DRM engine plugin.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[out] out_info_map The Key-Value pair place-holder for the key status.
              To release/free this call MLMediaDRMKeyValueArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok Query for MLMediaDRM Key status completed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMQueryKeyStatus(MLHandle media_drm, const MLMediaDRMByteArray *session_id, MLMediaDRMKeyValueArray *out_info_map);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief A provision request/response exchange occurs between the app and a provisioning
  server to retrieve a device certificate.

  If provisioning is required, the #EVENT_PROVISION_REQUIRED event will be sent to the event handler.
  MLMediaDRMGetProvisionRequest() is used to obtain the opaque provision request byte array that
  should be delivered to the provisioning server.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] cert_type The device certificate type, which can be "none" or "X.509".
  \param[out] out_provision_request Upon successful return, contains provision request message.
              To free/release this, call MLMediaDRMRequestMessageRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok Device Provision Request message is constructed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMGetProvisionRequest(MLHandle media_drm, const char *cert_type, MLMediaDRMRequestMessage *out_provision_request);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief After a provision response is received by the app, it is provided to the DRM
  engine plugin using this method.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] response The opaque provisioning response byte array to provide to the DRM engine plugin.
  \param[out] out_certificate The device certificate upon sucessful return.
              To release/free this call MLMediaDRMByteArrayRelease().
  \param[out] out_wrapped_key The wrapped device key upon sucessful return.
              To release/free this call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok Device Provision Response message is consumed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMProvideProvisionResponse(MLHandle media_drm, const MLMediaDRMByteArray *response, MLMediaDRMByteArray *out_certificate, MLMediaDRMByteArray *out_wrapped_key);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Access all secure stops.

  Secure Stop:

  A means of enforcing limits on the number of concurrent streams per subscriber
  across devices is provided via #SecureStop. This is achieved by securely
  monitoring the lifetime of sessions.

  Information from the server related to the current playback session is written
  to persistent storage on the device when each #MediaCrypto object is created.

  In the normal case, playback will be completed, the session destroyed and the
  Secure Stops will be queried. The app queries secure stops and forwards the
  secure stop message to the server which verifies the signature and notifies the
  server side database that the session destruction has been confirmed.

  The persisted record on the client is only removed after positive confirmation that the server
  received the message using releaseSecureStops().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[out] out_secure_stops List of all the secure stops upon successful return.
              To free/release call MLMediaDRMByteArrayListRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Secure stops are retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMGetSecureStops(MLHandle media_drm, MLMediaDRMByteArrayList *out_secure_stops);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Access secure stop by secure stop ID. \see MLMediaDRMGetSecureStops().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] ss_id The ID for the DRM securestop session.
  \param[out] out_secure_stop The secure stop upon successful return.
              To free/release call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Secure stop is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMGetSecureStop(MLHandle media_drm, const MLMediaDRMByteArray *ss_id, MLMediaDRMByteArray *out_secure_stop);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Process the SecureStop server response message. After authenticating the message, remove the SecureStops 
  identified in the response. See MLMediaDRMGetSecureStops() for details.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] secure_stop The server response indicating which secure stops to release.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM Secure stops are released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMReleaseSecureStops(MLHandle media_drm, const MLMediaDRMByteArray *secure_stop);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Remove all the SecureStops. \see MLMediaDRMGetSecureStops().

  \param[in] media_drm Handle to the MLMediaDRM.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok All secure stops for the MLMediaDRM are released successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMReleaseAllSecureStops(MLHandle media_drm);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Read a DRM engine plugin String property value, given the property name.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_Vendor.
             - MLMediaDRMProperty_Version.
             - MLMediaDRMProperty_Description.
             - MLMediaDRMProperty_Algorithms.
  \param[out] out_property_value The property value upon successful return. Ownership is passed, call free(*out_property_value) to free it.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM property is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMGetPropertyString(MLHandle media_drm, MLMediaDRMProperty property_name, char **out_property_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Read a DRM engine plugin byte array property value, given the property name.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_DeviceUniqueID.
  \param[out] out_property_value The property value upon successful return.
              To release/free call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM property is retrieved successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMGetPropertyByteArray(MLHandle media_drm, MLMediaDRMProperty property_name, MLMediaDRMByteArray *out_property_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set a DRM engine plugin String property value.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_Vendor.
             - MLMediaDRMProperty_Version.
             - MLMediaDRMProperty_Description.
             - MLMediaDRMProperty_Algorithms.
  \param[in] property_value The value of the corresponding property.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM property is set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMSetPropertyString(MLHandle media_drm, MLMediaDRMProperty property_name, const char *property_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Set a DRM engine plugin byte array property value.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] property_name The property to query. Standard property names are:
             - MLMediaDRMProperty_DeviceUniqueID.
  \param[in] property_value The value of the corresponding property.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM property is set successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMSetPropertyByteArray(MLHandle media_drm, MLMediaDRMProperty property_name, const MLMediaDRMByteArray *property_value);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Encrypt the data referenced by input using algorithm if specified,
  and write the encrypted result into output.

  The key to use is identified by the 16 byte keyId. The key must have been loaded into
  the session using MLMediaDRMProvideKeyResponse().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] crypto_key_param Pointer to the structure that contains
             needed crypto arguments for encryption operation.
  \param[in] input The data that needs to be encrypted.
  \param[out] out_output The encrypted input upon successful return.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM encryption operation has been completed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMEncrypt(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMCryptoInputParam *crypto_key_param, const MLMediaDRMByteArray *input, MLMediaDRMByteArray *out_output);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Decrypt the data referenced by input using algorithm if specified,
  and write the encrypted result into output.

  The key to use is identified by the 16 byte keyId. The key must have been loaded into
  the session using MLMediaDRMProvideKeyResponse().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] crypto_key_param Pointer to the structure that contains
             needed crypto arguments for decryption operation.
  \param[in] input The data that needs to be decrypted.
  \param[out] out_output The decrypted input upon successful return.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM decryption operation has been completed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMDecrypt(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMCryptoInputParam *crypto_key_param, const MLMediaDRMByteArray *input, MLMediaDRMByteArray *out_output);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Generate a signature using the specified algorithm (if provided) over the message data
  and store the signature.

  The key to use is identified by the 16 byte keyId.
  The key must have been loaded into the session using MLMediaDRMProvideKeyResponse().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] hmac_key_param Pointer to the structure that contains
             needed crypto arguments for HMAC operation.
  \param[in] message The data that needs to be signed.
  \param[out] out_signature The signature of the input message upon success.
              To free/release this buffer, call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM HMAC Sign operation has been completed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMSign(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMHMACInputParam *hmac_key_param, const MLMediaDRMByteArray *message, MLMediaDRMByteArray *out_signature);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Perform a signature verification using the specified algorithm (if specified)
  over the message data referenced by the message parameter.

  The key must have been loaded into the session using MLMediaDRMProvideKeyResponse().

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] hmac_key_param Pointer to the structure that contains
             needed crypto arguments for HMAC operation.
  \param[in] message The data for which signature needs to be verified.
  \param[in] signature The signature of the input message.
  \param[out] out_match Pointer to bool, which would return "true" if the signature matches,
              "false" otherwise.

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM HMAC Verify operation has been completed successfully.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMVerify(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMHMACInputParam *hmac_key_param, const MLMediaDRMByteArray *message, const MLMediaDRMByteArray *signature, bool *out_match);

/*!
  \deprecated Deprecated since 1.4.0. Scheduled for removal.
  \brief Generate a signature using the specified RSA Key and algorithm.

  \param[in] media_drm Handle to the MLMediaDRM.
  \param[in] session_id The session ID for the DRM session.
  \param[in] rsa_key_param Pointer to the structure that contains needed key arguments for this RSA operation.
  \param[in] message The data that needs to be signed.
  \param[out] out_signature The signature of the input message upon success. To free/release this buffer, call MLMediaDRMByteArrayRelease().

  \retval MLResult_InvalidParam Parameter is invalid.
  \retval MLResult_Ok MLMediaDRM RSA Sign operation has been completed successfully.
  \retval MLResult_PermissionDenied Necessary permission is missing.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_DEPRECATED_MSG("Use standard Android SDK and NDK APIs.")
ML_API MLResult ML_CALL MLMediaDRMSignRSA(MLHandle media_drm, const MLMediaDRMByteArray *session_id, const MLMediaDRMRSAInputParam *rsa_key_param, const MLMediaDRMByteArray *message, MLMediaDRMByteArray *out_signature);

/*! \} */

ML_EXTERN_C_END
