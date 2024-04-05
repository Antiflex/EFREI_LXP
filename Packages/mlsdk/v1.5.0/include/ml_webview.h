// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
// Copyright (c) 2022 Magic Leap, Inc. All Rights Reserved.
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
  \defgroup WebView
  \addtogroup WebView

  \sharedobject webview.magicleap
  \brief APIs for the WebView component.

  This interface allows an application to instantiate a WebView and interact
  with it (via "mouse" and "keyboard" events).

  \note MLWebView methods use re-entrant JNI monitors to provide a thread-safe API.
        See: https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/functions.html#wp5256 for details.
  \{
*/

/*!
  \brief The type of text entry selected when on_show_keyboard is called.

  \apilevel 20
*/
typedef enum MLWebViewTextInputType {
  MLWebViewTextInputType_None = 0,
  MLWebViewTextInputType_Text,
  MLWebViewTextInputType_Password,
  MLWebViewTextInputType_Search,
  MLWebViewTextInputType_Email,
  MLWebViewTextInputType_Number,
  MLWebViewTextInputType_Telephone,
  MLWebViewTextInputType_URL,
  MLWebViewTextInputType_Date,
  MLWebViewTextInputType_DateTime,
  MLWebViewTextInputType_DateTimeLocal,
  MLWebViewTextInputType_Month,
  MLWebViewTextInputType_Time,
  MLWebViewTextInputType_Week,
  MLWebViewTextInputType_TextArea,
  MLWebViewTextInputType_ContentEditable,
  MLWebViewTextInputType_DateTimeField,
  MLWebViewTextInputType_Ensure32Bits = 0x7FFFFFFF
} MLWebViewTextInputType;

/*!
  \brief Flags related to a text entry field passed when on_show_keyboard is called.

  \apilevel 20
*/
typedef enum MLWebViewTextInputFlags {
  MLWebViewTextInputFlags_None = 0,
  MLWebViewTextInputFlags_AutocompleteOn = 1 << 0,
  MLWebViewTextInputFlags_AutocompleteOff = 1 << 1,
  MLWebViewTextInputFlags_AutocorrectOn = 1 << 2,
  MLWebViewTextInputFlags_AutocorrectOff = 1 << 3,
  MLWebViewTextInputFlags_SpellcheckOn = 1 << 4,
  MLWebViewTextInputFlags_SpellcheckOff = 1 << 5,
  MLWebViewTextInputFlags_AutocapitalizeNone = 1 << 6,
  MLWebViewTextInputFlags_AutocapitalizeCharacters = 1 << 7,
  MLWebViewTextInputFlags_AutocapitalizeWords = 1 << 8,
  MLWebViewTextInputFlags_AutocapitalizeSentences = 1 << 9,
  MLWebViewTextInputFlags_HaveNextFocusableElement = 1 << 10,
  MLWebViewTextInputFlags_HavePreviousFocusableElement = 1 << 11,
  MLWebViewTextInputFlags_HasBeenPasswordField = 1 << 12,
  MLWebViewTextInputFlags_Ensure32Bits = 0x7FFFFFFF
} MLWebViewTextInputFlags;

/*!
  \brief Flags to set special key states during input.

  \apilevel 20
*/
typedef enum MLWebViewEventFlags {
  MLWebViewEventFlags_None = 0,
  MLWebViewEventFlags_CapsLockOn = 1 << 0,
  MLWebViewEventFlags_ShiftDown = 1 << 1,
  MLWebViewEventFlags_ControlDown = 1 << 2,
  MLWebViewEventFlags_AltDown = 1 << 3,
  MLWebViewEventFlags_LeftMouseButton = 1 << 4,
  MLWebViewEventFlags_MiddleMouseButton = 1 << 5,
  MLWebViewEventFlags_RightMouseButton = 1 << 6,
  MLWebViewEventFlags_CommandDown = 1 << 7,
  MLWebViewEventFlags_NumLockOn = 1 << 8,
  MLWebViewEventFlags_IsKeyPad = 1 << 9,
  MLWebViewEventFlags_IsLeft = 1 << 10,
  MLWebViewEventFlags_IsRight = 1 << 11,
  MLWebViewEventFlags_AltGRDown = 1 << 12,
  MLWebViewEventFlags_Ensure32Bits = 0x7FFFFFFF
} MLWebViewEventFlags;

enum {
  /*! Defines the prefix for #MLWebViewResult codes. */
  MLResultAPIPrefix_WebView = MLRESULT_PREFIX(0xebf7)
};

/*!
  \brief Return values for the WebView API calls.

  \apilevel 20
*/
typedef enum MLWebViewResult {
  MLWebViewResult_ZoomLimitReached = MLResultAPIPrefix_WebView,
  /*! Ensure enum is represented as 32 bits. */
  MLWebViewResult_Ensure32Bits = 0x7FFFFFFF
} MLWebViewResult;

/*!
  \brief Flags set for the process using webview.

  \apilevel 22
*/
typedef enum MLWebViewProcessSettingFlags {
  MLWebViewProcessSettingFlags_None = 0,
  /*! The bit to enable (1) or disable (0) web inspector. */
  MLWebViewProcessSettingFlags_WebInspectorOn = 1 << 0,
  /*! Ensure enum is represented as 32 bits. */
  MLWebViewProcessSettingFlags_Ensure32Bits = 0x7FFFFFFF
} MLWebViewProcessSettingFlags;

/*!
  \brief Struct to define the cursor's state.

  This structure must be initialized by calling #MLWebViewCursorStateInit before use.

  \apilevel 20
*/
typedef struct MLWebViewCursorState {
  uint32_t version;
  /*! Horizontal position of the cursor. */
  uint32_t x_position;
  /*! Vertical position of the cursor. */
  uint32_t y_position;
  /*! Should be one or combination of #MLWebViewEventFlags. */
  MLWebViewEventFlags modifiers;
} MLWebViewCursorState;

/*!
  \brief Initializes a #MLWebViewCursorState with the default parameters.

  \apilevel 20

  \param[in,out] inout_cursor_state The object to initialize with default values.

  \permissions None
*/
ML_STATIC_INLINE void MLWebViewCursorStateInit(MLWebViewCursorState* inout_cursor_state) {
  if (inout_cursor_state) {
    inout_cursor_state->version = 1;
    inout_cursor_state->x_position = 0;
    inout_cursor_state->y_position = 0;
    inout_cursor_state->modifiers = MLWebViewEventFlags_None;
  }
}

/*!
  \brief Event handler for MLWebView callbacks.

  This structure must be initialized by calling #MLWebViewEventCallbacksInit before use.

  \apilevel 24
*/
typedef struct MLWebViewEventCallbacks {

  /*! Version of this structure. */
  uint32_t version;

  /*! User data passed to every callback. */
  void* user_data;

  /*!
    \brief Called to notify when a resource will loadeded.

    \param[in] resource_url the url of the resource about to be loaded.
  */
  void (*on_before_resource_load)(const char* resource_url, void* user_data);
  /*!
    \brief Called to notify load completion.

    \param[in] is_main_frame Whether this event was for the main frame.
    \param[in] http_status_code The standard http status code.
  */
  void (*on_load_end)(bool is_main_frame, int32_t http_status_code, void* user_data);
  /*!
    \brief Called if there was any error during loading.
    These errors could be due to connectivity, certificate errors etc.

    \param[in] is_main_frame If this event was for the main frame.
    \param[in] http_status_code Http status code for the URL load failure.
    \param[in] error_str The stringified version of the error code.
    \param[in] failed_url The url that caused the load error.
  */
  void (*on_load_error)(bool is_main_frame, int32_t http_status_code, const char* error_str, const char* failed_url, void* user_data);
  /*!
    \brief Called when there is any certificate error.

    \param[in] error_code Error code for ssl error.
    \param[in] url The url associated to the certificate error.
    \param[in] error_message Certificate error short description.
    \param[in] details Certificate error details.
    \retval Returns true if should continue loading and false if should stop loading.
  */
  bool (*on_certificate_error)(int32_t error_code, const char* url, const char* error_message, const char* details, void* user_data);
  /*!
    \brief Called when user selects an input field.

    \param[in] x Horizontal position of the input field.
    \param[in] y Vertical position of the input field.
    \param[in] width Width of the input field.
    \param[in] height Height of the input field.
    \param[in] text_input_flags One or combination of #MLWebViewTextInputFlags.
    \param[in] text_input_type One of #MLWebViewTextInputType.
  */
  void (*on_show_keyboard)(int32_t x,
                           int32_t y,
                           int32_t width,
                           int32_t height,
                           int32_t text_input_flags,
                           MLWebViewTextInputType text_input_type,
                           void* user_data);
  /*!
    \brief Called when user deselects an input field and the keyboard should be dismissed.
  */
  void (*on_keyboard_dismiss)(void* user_data);
  /*!
    \brief Called when webview is destroyed.
  */
  void (*on_destroy)(void* user_data);
  /*!
    \brief This callback is used to pass notify user of service connection.

    \param[in] user_data The user data passed in during initialization.
  */
  void (*on_service_connected)(void* user_data);
  /*!
    \brief This callback is used to notify user that service is disconnect.
    \note Handle can no longer be used.
  */
  void (*on_service_disconnected)(void* user_data);
  /*!
    \brief This callback is used to notify user that service has failed.
    \note Callback on_service_failed is for version >= 2.

    \param[in] result The reason for the failure.
    \param[in] user_data The user data passed back to the user.
  */
  void (*on_service_failed)(MLResult result, void* user_data);

  /*!
    \brief This callback is used to ask the application if is OK to load a URL.
    \note Callback on_before_popup is for version >= 3.

    \param[in] result The application should return true if it accepts the popup and false otherwise.
    \param[in] user_data The user data passed back to the user.
  */
  bool (*on_before_popup)(const char* url, void* user_data);

  /*!
    \brief This callback is used to notify application that popup is opened.
    \note Callback on_popup_opened is for version >= 3.

    \param[in] user_data The user data passed back to the user.
  */
  void (*on_popup_opened)(uint64_t popup_id, const char* url, void* user_data);

  /*!
   \brief This callback is used to notify the application of a closing popup.

   This callback is used to notify the application of a popup that is being closed.
   For example, this can happen if window.close() is used. This is not always called.
   If the application closes the popup itself, then this function is not called.
   An application should call MLWebViewDestroy as soon as possible on the popup's
   handle after receiving this callback.

    \param[in] handle the webview handle of the popup being closed
    \param[in] user_data The user data passed back to the user.
  */
  void (*on_popup_closed)(MLHandle handle, void* user_data);
} MLWebViewEventCallbacks;

/*!
  \brief Initializes a #MLWebViewEventCallbacks with the default parameters.

  \apilevel 24

  \param[in,out] inout_callback The object to initialize with default settings.

  \permissions None
*/
ML_STATIC_INLINE void MLWebViewEventCallbacksInit(MLWebViewEventCallbacks* inout_callback) {
  if (inout_callback) {
    inout_callback->version = 3u;
    inout_callback->user_data = NULL;
    inout_callback->on_before_resource_load = NULL;
    inout_callback->on_load_end = NULL;
    inout_callback->on_load_error = NULL;
    inout_callback->on_certificate_error = NULL;
    inout_callback->on_show_keyboard = NULL;
    inout_callback->on_keyboard_dismiss = NULL;
    inout_callback->on_destroy = NULL;
    inout_callback->on_service_connected = NULL;
    inout_callback->on_service_disconnected = NULL;
    inout_callback->on_service_failed = NULL;
    inout_callback->on_before_popup = NULL;
    inout_callback->on_popup_opened = NULL;
    inout_callback->on_popup_closed = NULL;
  }
}

/*!
  \brief Struct to define webview initialization.

  This structure must be initialized by calling #MLWebViewSettingsInit before use.

  \apilevel 24
*/
typedef struct MLWebViewSettings {
  uint32_t version;
  /*! Horizontal size of webview in pixels. */
  uint32_t width;
  /*! Vertical size of webview in pixels. */
  uint32_t height;
  /*! JavaVM pointer to use for Android up-calls. */
  void* application_vm;
  /*! Android jobject to android.content.Context instance for Android up-calls. */
  void* context;
  /*! Event callbacks for interacting with webview. */
  MLWebViewEventCallbacks callbacks;
  /*! Is this a popup? */
  bool is_popup;
  /*! Popup identifier used to create a webview. */
  uint64_t popup_id;
} MLWebViewSettings;

/*!
  \brief Initializes a #MLWebViewSettings with the default parameters.

  \apilevel 20

  \param[in,out] inout_settings The object to initialize with default settings.

  \permissions None
*/
ML_STATIC_INLINE void MLWebViewSettingsInit(MLWebViewSettings* inout_settings) {
  if (inout_settings) {
    inout_settings->version = 3u;
    inout_settings->width = 1200;
    inout_settings->height = 750;
    inout_settings->application_vm = NULL;
    inout_settings->context = NULL;
    inout_settings->is_popup = false;
    inout_settings->popup_id = 0;
    MLWebViewEventCallbacksInit(&inout_settings->callbacks);
  }
}

/*!
  \brief Struct to define webview process initialization.

  This structure must be initialized by calling #MLWebViewProcessSettingsInit before use.

  \apilevel 22
*/
typedef struct MLWebViewProcessSettings {
  uint32_t version;
  /*! Flags to be set for the process using the webview. */
  uint32_t flags;
} MLWebViewProcessSettings;

/*!
  \brief Initializes a #MLWebViewProcessSettings with the default parameters.

  \apilevel 22

  \param[in,out] inout_settings The object to initialize with default settings.

  \permissions None
*/
ML_STATIC_INLINE void MLWebViewProcessSettingsInit(MLWebViewProcessSettings* inout_settings) {
  if (inout_settings) {
    inout_settings->version = 1;
    inout_settings->flags = MLWebViewProcessSettingFlags_None;
  }
}

/*!
  \brief Specify the process settings to be used for webviews.

  \note Current implementation only supports enabling and disabling web inspector before first call to MLWebViewCreate. If all webviews have been destroyed, it is possible to call this with effect again. Default is to disable.


  \apilevel 22

  \param[in] settings The settings to be used for webviews.

  \permissions None

  \retval MLResult_InvalidParam If settings is null.
  \retval MLResult_NotImplemented If called after MLWebViewCreate.
  \retval MLResult_Ok If settings is not null.
*/
ML_API MLResult ML_CALL MLWebViewSetProcessSettings(const MLWebViewProcessSettings* settings);

/*!
  \brief Create a MLWebView.

  The MLWebView will be ready to use once this function returns with MLResult_OK.

  \note In version >= 2 for MLWebViewCallbacks struct, MLWebViewCreate launches a separate thread to create a webview. If creation fails and the on_service_failed callback is not null the MLResult code will be passed into the on_service_failed callback. The on_service_connected callback will be called if it is not null and creation was successful.  For version < 2 of MLWebViewCallbacks struct, MLWebViewCallbacks will create in synchronous mode.

  \apilevel 24

  \param[out] out_handle Handle that is ready to use with all other MLWebView API calls.
  \param[in] in_settings The initialization paramaters for the webview.

  \retval MLResult_InvalidParam out_handle, in_settings, or application_vm pointer was null.
  \retval MLResult_Ok If version >= 2, returns MLResult_Ok for successful start of asynchronous operation, but any eventual failure will be reported through on_service_failed.  If version < 2, this indicates that synchronous creation was successful.
  \retval MLResult_PermissionDenied Missing required permission(s).
  \retval MLResult_UnspecifiedFailure Unable to create the MLWebView, MLWebViewCallbacks struct version < 2.

  \permissions com.magicleap.permission.WEBVIEW (protection level: normal)
*/
ML_API MLResult ML_CALL MLWebViewCreate(MLHandle *out_handle,
                                        const MLWebViewSettings *in_settings);

/*!
  \brief Destroy a MLWebView.

  The MLWebView will be terminated by this function call and the handle shall no longer be valid.

  \apilevel 21

  \param[in] handle The handle to invalidate.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The MLWebView was destroyed successfully.
  \retval MLResult_UnspecifiedFailure An error occurred destroying the MLWebView.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewDestroy(MLHandle handle);

/*!
  \brief Specify the callbacks for a MLWebView.

  \apilevel 24

  \param[in] web_view The MLWebView to link the event handler.
  \param[in] callbacks The event handler to link to the MLWebView.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok MLWebView event handler was set.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewSetEventCallbacks(MLHandle web_view,
                                                   const MLWebViewEventCallbacks* callbacks);

struct AHardwareBuffer;

/*!
  \brief Acquires next available frame buffer for rendering.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_native_buffer Pointer to an AHardwareBuffer.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The frame is ready.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \note To use with OpenGL, EGL, and Vulkan please see: https://developer.android.com/ndk/reference/group/a-hardware-buffer for details.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewAcquireNextAvailableFrame(MLHandle web_view,
                                                           struct AHardwareBuffer** out_native_buffer);

/*!
  \brief Release a frame acquired by #MLWebViewAcquireNextAvailableFrame.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[in] native_buffer The frame being released.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok Frame successfully released.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure An error occurred releasing the frame.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewReleaseFrame(MLHandle web_view, struct AHardwareBuffer* native_buffer);

/*!
  \brief Go to a URL with the specified MLWebView.

  Note that success with this call only indicates that a load will be attempted. Caller can be
  notified about issues loading the URL via the event handler on_load_error.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[in] url The URL that will be loaded.

  \retval MLResult_IllegalState WebView was paused. #MLWebViewResume should be called before this function.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The WebView is attempting to load the specified URL.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewGoTo(MLHandle web_view, const char* url);

/*!
  \brief Trigger a "Back" action in the MLWebView.

  Query #MLWebViewCanGoBack before calling this method. If there is no valid
  page to go back to, this method will be no-op.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_Ok The WebView Back action was initiated or cannot go back any further.
  \retval MLResult_IllegalState WebView was paused. #MLWebViewResume should be called before this function.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewGoBack(MLHandle web_view);

/*!
  \brief Trigger a "Forward" action in the MLWebView.

  Query #MLWebViewCanGoForward before calling this method. If there is no valid
  page to go forward to, this method will be no-op.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. #MLWebViewResume should be called before this function.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The WebView Forward action was initiated or cannot go forward any further.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewGoForward(MLHandle web_view);

/*!
  \brief Trigger a "Reload" action in the MLWebView.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. #MLWebViewResume should be called before this function.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The WebView Reload action was initiated.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewReload(MLHandle web_view);

/*!
  \brief Get the current URL. Set out_url to NULL to get the length of the current URL.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[in,out] inout_size The size that has been allocated in out_url to hold the URL. This will be
                set to the actual length of URL if inout_size and size needed for the URL are different.
  \param[in,out] inout_url The URL up to inout_size of characters.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The WebView URL was acquired.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewGetUrl(MLHandle web_view, uint32_t* inout_size, char* inout_url);

/*!
  \brief Checks if the "Back" action is currently valid.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_can_go_back True if "Back" has a valid page to go to.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The status of going "Back" was acquired.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewCanGoBack(MLHandle web_view, bool* out_can_go_back);

/*!
  \brief Checks if the "Forward" action is currently valid.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_can_go_forward True if "Forward" has a valid page to go to.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The status of going "Forward" was acquired.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewCanGoForward(MLHandle web_view, bool* out_can_go_forward);

/*!
  \brief Moves the WebView mouse.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[in] cursor_state Information about the mouse movement.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The internal mouse was moved.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \note Please see MLWebViewInjectMouseButtonDown for behavior.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewInjectMouseMove(MLHandle web_view, const MLWebViewCursorState* cursor_state);

/*!
  \brief Sends a mouse button down/pressed event on a specific location on screen.

  \param[in] web_view The webview being accessed.
  \param[in] cursor_state Information about the mouse button event.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok If successful.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \note Behavior:
   (1) Click behavior: On mouse down, (x, y) is saved and mouse down sent.
   When mouse up received within 200ms, mouse up sent to previous mouse
   down (x, y) position so Chromium interprets as click.
   (2) Drag behavior: On mouse down (x, y) is saved and mouse down sent.
   When mouse moves within timeout period of 200ms, webview will continue
   to wait.  Otherwise, mouse move sent to current (x, y) location to let
   Chromium interpret as drag.
   (3) These click and drag behaviors make it possible to just send mouse
   events as they are received and the underlying Chromium implementation
   will work as expected.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewInjectMouseButtonDown(MLHandle web_view,
                                                       const MLWebViewCursorState* cursor_state);

/*!
  \brief Sends a mouse button up/released event on a specific location on screen.

  \param[in] web_view The webview being accessed.
  \param[in] cursor_state Information about the mouse button event.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok If successful.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \note Please see MLWebViewInjectMouseButtonDown for behavior.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewInjectMouseButtonUp(MLHandle web_view,
                                                     const MLWebViewCursorState* cursor_state);

/*!
  \brief Sends a printable char keyboard event to MLWebView.

  \apilevel 21

  \param[in] web_view Target webview.
  \param[in] char_utf32 Printable char utf code.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The key event was injected.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewInjectChar(MLHandle web_view, uint32_t char_utf32);

/*!
  \brief Sends a key down/pressed event to MLWebView.

  \apilevel 21

  \param[in] web_view Target webview.
  \param[in] key_code Key code.
  \param[in] modifier_mask Should be one or combination of #MLWebViewEventFlags.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The key event was injected.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewInjectKeyDown(MLHandle web_view, int32_t key_code, uint32_t modifier_mask);

/*!
  \brief Sends a key up/release event to MLWebView.

  \apilevel 21

  \param[in] web_view Target webview.
  \param[in] key_code Key code.
  \param[in] modifier_mask Should be one or combination of #MLWebViewEventFlags.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The key event was injected.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewInjectKeyUp(MLHandle web_view, int32_t key_code, uint32_t modifier_mask);

/*!
  \deprecated Deprecated since 1.2.0. Scheduled for removal.

  \brief This API is stubbed out and translates to a no-op.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_width The number representing the entire width of the webview, in pixels.
  \param[out] out_height The number representing the entire height of the webview, in pixels.

  \retval MLResult_NotImplemented This API is stubbed out and translates to a no-op.

  \permissions None
*/
ML_DEPRECATED_MSG("Unimplemented and scheduled for removal.")
ML_API MLResult ML_CALL MLWebViewGetScrollSize(MLHandle web_view, int32_t* out_width, int32_t* out_height);

/*!
  \deprecated Deprecated since 1.2.0. Scheduled for removal.

  \brief This API is stubbed out and translates to a no-op.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_x The number representing the horizontal offset of the webview, in pixels.
  \param[out] out_y The number representing the vertical offset of the webview, in pixels.

  \retval MLResult_NotImplemented This API is stubbed out and translates to a no-op.

  \permissions None
*/
ML_DEPRECATED_MSG("Unimplemented and scheduled for removal.")
ML_API MLResult ML_CALL MLWebViewGetScrollOffset(MLHandle web_view, int32_t* out_x, int32_t* out_y);

/*!
  \brief Triggers a mouse "Scroll" event.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[in] x_pixels The number of pixels to scroll on the x axis.
  \param[in] y_pixels The number of pixels to scroll on the y axis.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The MLWebView was scrolled.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewScrollBy(MLHandle web_view, const int32_t x_pixels, const int32_t y_pixels);

/*!
  \brief Get the current zoom factor. The default zoom factor is 1.0.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_zoom_factor Current numeric value for zoom factor.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The out_zoom_factor parameter was updated with the current zoom value.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure Failed to get the zoom factor due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewGetZoomFactor(MLHandle web_view, double* out_zoom_factor);

/*!
  \brief Zoom in one level.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The MLWebView zoomed in.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure Failed to zoom in due to an internal error.
  \retval MLWebViewResult_ZoomLimitReached if cannot zoom in any further.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewZoomIn(MLHandle web_view);

/*!
  \brief Zoom out one level.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The MLWebView zoomed out.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure Failed to zoom out due to an internal error.
  \retval MLWebViewResult_ZoomLimitReached if cannot zoom out any further.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewZoomOut(MLHandle web_view);

/*!
  \brief Reset zoom level to 1.0.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok The MLWebView zoom was reset.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure Failed to reset zoom due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewResetZoom(MLHandle web_view);

/*!
  \brief Retrieves the 4x4 texture coordinate transform matrix used by all MLWebView frames.

  This transform matrix maps 2D homogeneous texture coordinates of the form
  (s, t, 0, 1) with s and t in the inclusive range [0, 1] to the texture
  coordinate that should be used to sample that location from the texture.
  Sampling the texture outside of the range of this transform is undefined.

  The matrix is stored in column-major order so that it may be passed
  directly to OpenGL ES via the glLoadMatrixf or glUniformMatrix4fv
  functions.

  \apilevel 21

  \param[in] web_view The webview being accessed.
  \param[out] out_matrix The retrieved matrix.

  \retval MLResult_Ok The constant matrix was retrieved.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewGetFrameTransformMatrix(MLHandle web_view, MLMat4f* out_matrix);

/*!
  \brief Remove all webview cookies.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok If all cookies removed successfully.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure Removing all cookies failed due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewRemoveAllCookies(MLHandle web_view);

/*!
  \brief Clear the webview cache.

  \apilevel 21

  \param[in] web_view The webview being accessed.

  \retval MLResult_IllegalState WebView was paused. See #MLWebViewPause.
  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok If cache cleared successfully.
  \retval MLResult_Pending If the MLWebView handle is not ready to use if asynchronous creation was used, MLWebViewCallbacks struct version >= 2.
  \retval MLResult_UnspecifiedFailure Clearing cache failed due to an internal error.

  \permissions None
*/
ML_API MLResult ML_CALL MLWebViewClearCache(MLHandle web_view);

/*!
  \brief The type of the webview pause.

  \apilevel 22
*/
typedef enum MLWebViewPauseType {
  /*! Pause all multimedia activities of the webview. */
  MLWebViewPauseType_Multimedia = 0,
  /*! Pause javascript timers of the webview. */
  MLWebViewPauseType_Timers,
  /*! Pause and discard the webview rendering process. But keep alive the MLWebView handle. */
  MLWebViewPauseType_Discard,
  /*! Ensure enum is represented as 32 bits. */
  MLWebViewPauseType_Ensure32Bits = 0x7FFFFFFF
} MLWebViewPauseType;

/*!
  \brief Pause the webview. Call #MLWebViewResume to resume.

  This method provides a multiple pause types to the webview.

  \apilevel 22

  \param[in] web_view The webview being accessed.
  \param[in] pause_type The webview pause type #MLWebViewPauseType.
             #MLWebViewPauseType_Multimedia Is a simple pause for all multimedia of the webview.
             #MLWebViewPauseType_Timers Intended to stop animation of the webview content.
             #MLWebViewPauseType_Discard Uses to free the webview rendering process but keep alive the MLWebView handle.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle or invalid MLWebViewPauseType value.
  \retval MLResult_Ok If paused successfully.
  \retval MLResult_Pending MLWebView handle is not ready to use. See an asynchronous mode of the #MLWebViewCreate.
  \retval MLResult_UnspecifiedFailure Pause failed due to an internal error.
*/
ML_API MLResult ML_CALL MLWebViewPause(MLHandle web_view, MLWebViewPauseType pause_type);

/*!
  \brief Resumes a webview after a previous call of the #MLWebViewPause.

  Resume webview to the normal operation for all webview pause types.

  \apilevel 22

  \param[in] web_view The webview being accessed.

  \retval MLResult_InvalidParam Unable to find the specified MLWebView handle.
  \retval MLResult_Ok If resumed successfully.
  \retval MLResult_Pending MLWebView handle is not ready to use. See an asynchronous mode of the #MLWebViewCreate.
  \retval MLResult_UnspecifiedFailure Resume failed due to an internal error.
*/
ML_API MLResult ML_CALL MLWebViewResume(MLHandle web_view);

/*! \} */

ML_EXTERN_C_END
