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
#include <ml_api.h>

ML_EXTERN_C_BEGIN

/*!
  \addtogroup Input
  \sharedobject input.magicleap
  \brief APIs for the voice service system.

  \{
*/

enum {
  /*! Defines the prefix for MLVoiceResult codes. */
  MLResultAPIPrefix_Voice = MLRESULT_PREFIX(0xbe7a)
};

/*!
  \brief Return values for Voice API calls.

  \apilevel 20
*/
typedef enum MLVoiceResult {
  /*! Operation failed because a required voice intent feature is disabled in system settings. */
  MLVoiceResult_IntentDisabled = MLResultAPIPrefix_Voice,
  /*! Ensure enum is represented as 32 bits. */
  MLVoiceResult_Ensure32Bits = 0x7FFFFFFF
} MLVoiceResult;

/*!
  \brief Voice state in voice event.

  \apilevel 31
*/
typedef enum MLVoiceState {
  /*! Intent hotword detected, Automatic Speech Recognition (ASR) session is going to start. */
  MLVoiceState_IntentHotwordDetected = 0,
  /*! Voice UI is stopped, ASR session is going to stop. */
  MLVoiceState_IntentSessionEnded = 1,
  /*! ASR session is stopped due to abort. */
  MLVoiceState_IntentSessionEndedAborted = 2,
  /*! ASR session is stopped without detecting an intent. */
  MLVoiceState_IntentSessionEndedNoIntent = 3,
  /*! ASR session is stopped due to timeout. */
  MLVoiceState_IntentSessionEndedTimeout = 4,
  /*! ASR session is stopped due to error. */
  MLVoiceState_IntentSessionEndedError = 5,
  /*! Intent mode is started and ready. */
  MLVoiceState_IntentReady = 6,
  /*! Intent mode is stopped and not available. */
  MLVoiceState_IntentNotAvailable = 7,
  /*! Invalid app intent, double check content of JSON submitted with MLVoiceIntentConfigureSettings().
      Please refer to Voice Intent Development Toolkit from Magic Leap Hub to generate app intent content. */
  MLVoiceState_IntentInvalidAppIntent = 8,

  /*! Ensure enum is represented as 32 bits. */
  MLVoiceState_Ensure32Bits = 0x7FFFFFFF
} MLVoiceState;


/*!
  \brief No intent reason code in voice event.

  \apilevel 20
*/
typedef enum MLVoiceIntentNoIntentReason {
  /*! In case of success. */
  MLVoiceIntentNoIntentReason_NoReason = 0,
  /*! When the MLVoiceState in MLVoiceIntentEvent is either MLVoiceState_IntentSessionEndedTimeout or MLVoiceState_IntentSessionEndedError. */
  MLVoiceIntentNoIntentReason_Silence = 1,
  /*! When the MLVoiceState in MLVoiceIntentEvent is MLVoiceState_IntentSessionEndedNoIntent. */
  MLVoiceIntentNoIntentReason_NoMatch = 2,

  /*! Ensure enum is represented as 32 bits. */
  MLVoiceIntentNoIntentReason_Ensure32Bits = 0x7FFFFFFF
} MLVoiceIntentNoIntentReason;

/*!
  \brief A structure containing voice app-intent slot in voice event.

  \apilevel 24
*/
typedef struct MLInputVoiceAppIntentSlot {
  /*! The C string carrying slot name which is UTF-8 and null terminated.
      And the memory of this variable is managed by system. */
  const char* slot_name;
  /*! The C string carrying concept value which is UTF-8 and null terminated.
      And the memory of this variable is managed by system. */
  const char* slot_value;
} MLInputVoiceAppIntentSlot;

/*!
  \brief A structure containing voice intent event.

  \apilevel 24
*/
typedef struct MLVoiceIntentEvent {
  /*!
    \brief Voice event handling result in the voice intent event.

    In case of false, other member variables should be ignored (text will be NULL).
  */
  bool is_success;
  /*! Voice state when generating the voice intent event. */
  MLVoiceState state;
  /*! If intent is not detected, it contains the reason,
      otherwise the value is MLVoiceIntentNoIntentReason_NoReason. */
  MLVoiceIntentNoIntentReason no_intent_reason;
  /*! The C string carrying identifier data which is UTF-8 and null terminated.
      And the memory of this variable is managed by system. */
  const char* text;
  /*! User defined intent index which is detected. */
  uint32_t intent_id;
  /*! Array of app-intent slot, array count is set in app_intent_slot_count.
      And the memory of this variable is managed by system. */
  MLInputVoiceAppIntentSlot* app_intent_slots;
  /*! Count of an array app_intent_slots. */
  uint32_t app_intent_slot_count;
} MLVoiceIntentEvent;

/*!
  \brief A structure containing callbacks for voice intent events.

  The final parameter to all the callbacks is a void *, which will point to
  whatever payload data the user provides in MLVoiceIntentSetCallbacks.
  Individual callbacks which are not required by the client can be NULL.

  This structure must be initialized by calling MLVoiceIntentCallbacksInit()
  before use.

  \apilevel 24
*/
typedef struct MLVoiceIntentCallbacks {
  /*! Version of this callback. */
  uint32_t version;
  /*!
    \brief This callback will be invoked whenever a voice intent event is detected.

    \param[in] event Voice intent event.
    \param[in] data User data as passed to MLVoiceIntentSetCallbacks().
  */
  void (*on_voice_event)(const MLVoiceIntentEvent* event, void* data);
} MLVoiceIntentCallbacks;

/*!
  \brief Initializes default values for MLVoiceIntentCallbacks.

  \apilevel 24

  \param[in,out] inout_callbacks The object to initialize with default settings.

  \permissions None
*/
ML_STATIC_INLINE void MLVoiceIntentCallbacksInit(MLVoiceIntentCallbacks* inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 2u;
    inout_callbacks->on_voice_event = NULL;
  }
}

/*!
  \brief A structure containing settings for voice app intent.

  This structure must be initialized by calling MLVoiceIntentSettingsInit() before use.

  \apilevel 20
*/
typedef struct MLVoiceIntentSettings {
  /*! Version of this settings. */
  uint32_t version;
  /*!
    \brief The C string carrying app intent made by JSON format, which is UTF-8 and null terminated.

    The app intent should contain pre-defined fields, names, and values.
    Memory of this variable is managed by user.
   */
  const char* app_intent;
} MLVoiceIntentSettings;

/*!
  \brief Initializes default values for MLVoiceIntentSettings.

  \apilevel 20

  \param[in,out] inout_settings The object to initialize with default settings.

  \permissions None
*/
ML_STATIC_INLINE void MLVoiceIntentSettingsInit(MLVoiceIntentSettings* inout_settings) {
  if (inout_settings) {
    inout_settings->version = 1u;
    inout_settings->app_intent = NULL;
  }
}

/*!
  \brief Creates a voice intent client.

  \apilevel 20

  \param[out] out_handle A handle to the created voice intent client. Only valid if the return value is MLResult_Ok.

  \retval MLResult_InvalidParam Failed to create the voice intent client due to an invalid input parameter.
  \retval MLResult_Ok Successfully created the voice intent client.
  \retval MLResult_PermissionDenied Failed to create client due to missing permission.

  \permissions com.magicleap.permission.VOICE_INPUT (protection level: dangerous)
*/
ML_API MLResult ML_CALL MLVoiceIntentCreate(MLHandle *out_handle);

/*!
  \brief Destroys a voice intent client.

  \param[in] handle #MLHandle to the voice intent client to destroy.

  \retval MLResult_InvalidParam Failed to destroy the voice intent client due to an invalid input parameter.
  \retval MLResult_Ok Successfully destroyed the voice intent client.

  \permissions None
*/
ML_API MLResult ML_CALL MLVoiceIntentDestroy(MLHandle handle);

/*!
  \brief Sets the settings for voice intent events.

  App needs to call MLVoiceIntentConfigureSettings at least once before it calls MLVoiceIntentStartProcessing.
  App can call MLVoiceIntentConfigureSettings anytime it needs to update the voice intents.
  But such call will trigger updating intent grammar inside speech engine, which may result in a short delay (could be a few seconds depending on the device's workload).
  So it is not recommended to call the function frequently.

  \apilevel 20

  \param[in] handle Handle to the voice intent client.
  \param[in] voice_settings Pointer to #MLVoiceIntentSettings structure.

  \retval MLResult_InvalidParam Failed to set settings for voice intent events due to an invalid param.
  \retval MLResult_Ok Successfully set settings for voice intent events.
  \retval MLVoiceResult_IntentDisabled Failed to set the settings because required voice intent feature is disabled.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLVoiceIntentConfigureSettings(MLHandle handle, const MLVoiceIntentSettings* voice_settings);

/*!
  \brief Sets the callbacks for voice intent events.

  \apilevel 20

  \param[in] handle Handle to the voice intent client.
  \param[in] voice_callbacks Pointer to #MLVoiceIntentCallbacks structure. Set this to NULL to unregister callbacks.
  \param[in] user_data Pointer to user payload data (can be NULL).

  \retval MLResult_InvalidParam Failed to set callbacks for voice intent events due to an invalid param.
  \retval MLResult_Ok Successfully set callbacks for voice intent events.
  \retval MLVoiceResult_IntentDisabled Failed to set the callbacks because required voice intent feature is disabled in system settings.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLVoiceIntentSetCallbacks(MLHandle handle, const MLVoiceIntentCallbacks* voice_callbacks, void* user_data);

/*!
  \brief Starts voice intent processing.

  This API call affects the system voice service.

  NOTE: If your application is processing voice intents make sure to call
        #MLVoiceIntentStopProcessing when application loses focus and
        #MLVoiceIntentStartProcessing when application gains focus to allow
        for uninterrupted processing of the voice intents.

  \apilevel 20

  \param[in] handle Handle to the voice intent client.

  \retval MLResult_InvalidParam Failed to start processing due to an invalid parameter.
  \retval MLResult_Ok Successfully start intent processing.
  \retval MLVoiceResult_IntentDisabled Failed to start intent processing because required voice intent feature is disabled in system settings.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLVoiceIntentStartProcessing(MLHandle handle);

/*!
  \brief Stops voice intent processing.

  This API call affects the system voice service.

  NOTE: If your application is processing voice intents make sure to call
        #MLVoiceIntentStopProcessing when application loses focus and
        #MLVoiceIntentStartProcessing when application gains focus to allow
        for uninterrupted processing of the voice intents.

  \apilevel 20

  \param[in] handle Handle to the voice intent client.

  \retval MLResult_InvalidParam Failed to stop processing due to an invalid parameter.
  \retval MLResult_Ok Successfully stop intent processing.
  \retval MLVoiceResult_IntentDisabled Failed to stop intent processing because required voice intent feature is disabled in system settings.
  \retval MLResult_UnspecifiedFailure The operation failed with an unspecified error.

  \permissions None
*/
ML_API MLResult ML_CALL MLVoiceIntentStopProcessing(MLHandle handle);

/*!
  \brief Checks voice intent feature is enabled in the system.

  \apilevel 20

  \param[in] handle Handle to the voice intent client.
  \param[out] out_is_enabled Returns status whether voice intent feature is enabled in system settings.

  \retval MLResult_InvalidParam Failed to check due to an invalid parameter.
  \retval MLResult_Ok The API call completed successfuly.

  \permissions None
*/
ML_API MLResult ML_CALL MLVoiceIntentIsEnabled(MLHandle handle, bool* out_is_enabled);

/*!
  \brief Returns an ASCII string for MLVoiceResult and MLResult codes.

  \apilevel 31

  \param[in] result The input MLResult enum from MLVoice functions.
  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_API const char *ML_CALL MLVoiceGetResultString(MLResult result);
/*! \} */
ML_EXTERN_C_END
