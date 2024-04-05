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
  \addtogroup Input
  \sharedobject input.magicleap
  \brief APIs for the Input system.

  Magic Leap 2 is built on top of AOSP, Android 10 (Q) API level 29.
  Mouse and Keyboard APIs, which have been supported in legacy versions of
  Magic Leap 1, have now been removed from the Magic Leap C-API. For mouse and keyboard events,
  please refer to the <a href="https://developer.android.com/ndk/reference/group/input" target="_blank">Android Input NDK API documentation</a>.
  \{
*/

enum {
  /*! Defines the prefix for MLInputResult codes. */
  MLResultAPIPrefix_Input = MLRESULT_PREFIX(0x21DC)
};

/*!
  \brief Return values for Input API calls.
*/
typedef enum MLInputResult {
  MLInputResult_ServiceNotAvailable = MLResultAPIPrefix_Input,
  /*! \brief Operation failed because a required permission has not been granted.
   Example: This can happen when the app is not in the foreground.
  */
  MLInputResult_PermissionDenied,
  /*! Operation failed because a required device was not found. */
  MLInputResult_DeviceNotFound,
  /*! Operation failed because the service was in an illegal state.
   Example: This can occur when the service is still initializing.
  */
  MLInputResult_IllegalState,
  /*! Operation failed because of an internal error. */
  MLInputResult_InternalError,
  /*! Operation failed because a required speech feature is disabled in system settings. */
  MLInputResult_SpeechDisabled,
  /*! Ensure enum is represented as 32 bits. */
  MLInputResult_Ensure32Bits = 0x7FFFFFFF
} MLInputResult;

enum {
  /*! Maximum recognized number of input controllers. */
  MLInput_MaxControllers = 1,
  /*! Maximum recognized number of controller touchpad touches. */
  MLInput_MaxControllerTouchpadTouches = 2
};

/*! Touchpad gesture state. */
typedef enum MLInputControllerTouchpadGestureState {
  /*! End(Default). */
  MLInputControllerTouchpadGestureState_End,
  /*! Continue. */
  MLInputControllerTouchpadGestureState_Continue,
  /*! Start. */
  MLInputControllerTouchpadGestureState_Start,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerTouchpadGestureState_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTouchpadGestureState;

/*! Recognized touchpad gesture types. */
typedef enum MLInputControllerTouchpadGestureType {
  /*! None. */
  MLInputControllerTouchpadGestureType_None,
  /*! Tap. This is a discrete gesture. */
  MLInputControllerTouchpadGestureType_Tap,
  /*! Force tap down. This is a discrete gesture. */
  MLInputControllerTouchpadGestureType_ForceTapDown,
  /*! Force tap up. This is a discrete gesture. */
  MLInputControllerTouchpadGestureType_ForceTapUp,
  /*! Force dwell. This is a discrete gesture. */
  MLInputControllerTouchpadGestureType_ForceDwell,
  /*! Second force down. This is a discrete gesture. */
  MLInputControllerTouchpadGestureType_SecondForceDown,
  /*! Radial scroll. This is a continuous gesture. */
  MLInputControllerTouchpadGestureType_RadialScroll,
  /*! Swipe. This is a continuous gesture. */
  MLInputControllerTouchpadGestureType_Swipe,
  /*! Number of gesture types. */
  MLInputControllerTouchpadGestureType_Count,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerTouchpadGestureType_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTouchpadGestureType;

/*! Direction of touchpad gesture. */
typedef enum MLInputControllerTouchpadGestureDirection {
  /*! None. */
  MLInputControllerTouchpadGestureDirection_None,
  /*! Up. */
  MLInputControllerTouchpadGestureDirection_Up,
  /*! Down. */
  MLInputControllerTouchpadGestureDirection_Down,
  /*! Left. */
  MLInputControllerTouchpadGestureDirection_Left,
  /*! Right. */
  MLInputControllerTouchpadGestureDirection_Right,
  /*! Clockwise. */
  MLInputControllerTouchpadGestureDirection_Clockwise,
  /*! Counter clockwise. */
  MLInputControllerTouchpadGestureDirection_CounterClockwise,
  /*! Number of directions. */
  MLInputControllerTouchpadGestureDirection_Count,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerTouchpadGestureDirection_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTouchpadGestureDirection;

/*! A structure containing information about recognized touchpad gesture. */
typedef struct MLInputControllerTouchpadGesture {
  /*!
    \brief Gesture position (x,y) and force (z).
    Position is in the [-1.0,1.0] range and force is in the [0.0,1.0] range.
  */
  MLVec3f pos_and_force;
  /*! Type of gesture. Supported gesture types are listed below:
    \li Tap gesture.
    \li Force tap down gesture.
    \li Second force down gesture.
    \li Force tap up gesture.
    \li Force dwell gesture.
    \li Radial scroll gesture.
    \li Swipe gesture.
  */
  MLInputControllerTouchpadGestureType type;
  /*! Direction of gesture. */
  MLInputControllerTouchpadGestureDirection direction;
  /*!
    \brief Speed of gesture. Note that the value has different meanings depending
    on the gesture type being performed.
    For radial scroll the distance is the difference in angles between the start and the end of the gesture.
  */
  float speed;
  /*!
    \brief For radial gestures, this is the absolute value of the angle.
  */
  float distance;
  /*!
    \brief For radial gestures, this is the radius of the gesture.
  */
  float radius;
  /*! Angle between the positive x axis and the ray to the finger point in radians. */
  float angle;
} MLInputControllerTouchpadGesture;

/*! Types of input controllers recognized by Magic Leap platform. */
typedef enum MLInputControllerType {
  /*! None. */
  MLInputControllerType_None,
  /*! Device. */
  MLInputControllerType_Device,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerType_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerType;

/*! Buttons on input controllers. */
typedef enum MLInputControllerButton {
  MLInputControllerButton_None,
  /*! Bumper. */
  MLInputControllerButton_Bumper,
  /*! Menu.
  */
  MLInputControllerButton_Menu,
  /*! Number of buttons. */
  MLInputControllerButton_Count,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerButton_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerButton;

/*! Trigger events types. */
typedef enum MLInputControllerTriggerEvent {
  /*! This is used when trigger is pulled down, and the normalized value is > 0. */
  MLInputControllerTriggerEvent_Pull,
  /*! This is used when trigger is fully released, and the normalized value is 0. */
  MLInputControllerTriggerEvent_Release,
  /*! This is used when trigger is pulled and released within a short duration. */
  MLInputControllerTriggerEvent_Click,
  /*! This is used when trigger is pulled and held for a longer duration. */
  MLInputControllerTriggerEvent_Hold,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerTriggerEvent_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerTriggerEvent;

/*! Custom haptics pattern types. */
typedef enum MLInputPreDefinedPatternType {
  /*! Pre-defined pattern used for VKB hover. */
  MLInputPreDefinedPatternType_A = 0,
  /*! Pre-Defined pattern used for VKB select. */
  MLInputPreDefinedPatternType_B = 1,
  /*! Pre-Defined pattern used for homemenu hover. */
  MLInputPreDefinedPatternType_C = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLInputPreDefinedPatternType_Ensure32Bits = 0x7FFFFFFF
} MLInputPreDefinedPatternType;

/*! Custom haptics pattern types. */
typedef enum MLInputCustomHapticsType {
  /*! None. */
  MLInputCustomHapticsType_None = 0,
  /*! Pattern is a buzz command. */
  MLInputCustomHapticsType_Buzz = 1,
  /*! Pattern is a pre-defined pattern. */
  MLInputCustomHapticsType_Predefined = 2,
  /*! Ensure enum is represented as 32 bits. */
  MLInputCustomHapticsType_Ensure32Bits = 0x7FFFFFFF
} MLInputCustomHapticsType;

/*!
  \brief Hand in which the controller is held.

  \apilevel 21
*/
typedef enum MLInputControllerHand {
  /*! None. */
  MLInputControllerHand_None = 0,
  /*! Left hand. */
  MLInputControllerHand_Left = 1,
  /*! Right hand. */
  MLInputControllerHand_Right = 2,
  /*! Both hand. */
  MLInputControllerHand_Both = 3,
  /*! Ensure enum is represented as 32 bits. */
  MLInputControllerHand_Ensure32Bits = 0x7FFFFFFF
} MLInputControllerHand;

/*!
  \brief A structure containing callbacks for input controller events.

  The final parameter to all the callbacks is a void *, which will point to
  whatever payload data the user provides in MLInputSetControllerCallbacksEx.
  Individual callbacks which are not required by the client can be NULL.

  This structure must be initialized by calling MLInputControllerCallbacksExInit()
  before use.

  \apilevel 20
*/
typedef struct MLInputControllerCallbacksEx {
  /*! Version of this structure. */
  uint32_t version;
  /*!
    \brief This callback will be invoked whenever a touch gesture is detected.
    This callback will be called for both discrete and continuous gestures.
    \param[in] controller_id Id of the controller.
    \param[in] touchpad_gesture Pointer to the struct containing state of the controller.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_touchpad_gesture)(uint8_t controller_id, const MLInputControllerTouchpadGesture *touchpad_gesture, void *data);
  /*!
    \brief This callback will be invoked whenever a continuation of a touch gesture
    is detected. This callback will be called only for continuous gestures.
    \param[in] controller_id Id of the controller.
    \param[in] touchpad_gesture Pointer to the struct containing state of the controller.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_touchpad_gesture_continue)(uint8_t controller_id, const MLInputControllerTouchpadGesture *touchpad_gesture, void *data);
  /*!
    \brief This callback will be invoked whenever a continuous touch gesture ends.
    This callback will be called only for continuous gestures.
    \param[in] controller_id Id of the controller.
    \param[in] touchpad_gesture Pointer to the struct containing state of the controller.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_touchpad_gesture_end)(uint8_t controller_id, const MLInputControllerTouchpadGesture *touchpad_gesture, void *data);
  /*!
    \brief This callback will be invoked whenever a controller button is pressed. This callback will be called only for discrete gestures.
    \param[in] controller_id Id of the controller.
    \param[in] button Value of the controller button.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_button_down)(uint8_t controller_id, MLInputControllerButton button, void *data);
  /*!
    \brief This callback will be invoked whenever a controller button is released.
    \param[in] controller_id Id of the controller.
    \param[in] button Value of the controller button.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_button_up)(uint8_t controller_id, MLInputControllerButton button, void *data);
  /*!
    \brief This callback will be invoked whenever a controller button is pressed and released within a short duration.
    \param[in] controller_id Id of the controller.
    \param[in] button Value of the controller button.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_button_click)(uint8_t controller_id, MLInputControllerButton button, void *data);
  /*!
    \brief This callback will be invoked whenever a controller trigger state is changed.
    \param[in] controller_id Id of the controller.
    \param[in] event Value of the trigger event.
    \param[in] depth Normalized value of trigger pressing (0.0 ~ 1.0)
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_trigger)(uint8_t controller_id, MLInputControllerTriggerEvent event, float depth, void *data);
  /*!
    \brief This callback will be invoked whenever a controller is connected.
    \param[in] controller_id Id of the controller.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_connect)(uint8_t controller_id, void *data);
  /*!
    \brief This callback will be invoked whenever a controller is disconnected.
    \param[in] controller_id Id of the controller.
    \param[in] data User data as passed to MLInputSetControllerCallbacksEx().
  */
  void (*on_disconnect)(uint8_t controller_id, void *data);
} MLInputControllerCallbacksEx;

/*!
  \brief Initializes default values for MLInputControllerCallbacksEx.

  \apilevel 20

  \param[in,out] inout_callbacks The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLInputControllerCallbacksExInit(MLInputControllerCallbacksEx *inout_callbacks) {
  if (inout_callbacks) {
    inout_callbacks->version = 3u;
    inout_callbacks->on_touchpad_gesture = NULL;
    inout_callbacks->on_touchpad_gesture_continue = NULL;
    inout_callbacks->on_touchpad_gesture_end = NULL;
    inout_callbacks->on_button_down = NULL;
    inout_callbacks->on_button_up = NULL;
    inout_callbacks->on_button_click = NULL;
    inout_callbacks->on_trigger = NULL;
    inout_callbacks->on_connect = NULL;
    inout_callbacks->on_disconnect = NULL;
  }
}

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.
  \brief A structure containing information about the current state of an input controller.
*/
typedef ML_DEPRECATED_MSG("Replaced by MLInputControllerStateEx.") struct MLInputControllerState {
  /*!
    \brief Current touch position (x,y) and force (z).
    Position is in the [-1.0,1.0] range and force is in the [0.0,1.0] range.
  */
  MLVec3f touch_pos_and_force[MLInput_MaxControllerTouchpadTouches];
  /*! Normalized trigger value [0.0,1.0]. */
  float trigger_normalized;
  /*! Button states. */
  bool button_state[MLInputControllerButton_Count];
  /*! If this controller's touch is active. */
  bool is_touch_active[MLInput_MaxControllerTouchpadTouches];
  /*! If this controller is connected. */
  bool is_connected;
  /*! Current touchpad gesture. */
  MLInputControllerTouchpadGesture touchpad_gesture;
  /*! Current touchpad gesture state. */
  MLInputControllerTouchpadGestureState touchpad_gesture_state;
  /*! Type of this controller. */
  MLInputControllerType type;
  /*!
    \brief Hardware index of this controller. For ML2 physical controller this
    value will always be 0.
  */
  uint8_t hardware_index;
} MLInputControllerState;

/*!
  \brief A structure containing information about the current state of an input controller.

  \apilevel 21
*/
typedef struct MLInputControllerStateEx {
  /*! Version of this structure. */
  uint32_t version;
  /*! Type of this controller. */
  MLInputControllerType type;
  /*! Controller holding hand. */
  MLInputControllerHand hand;
  /*!
    \brief Current touch position (x,y) and force (z).
    Position is in the [-1.0,1.0] range and force is in the [0.0,1.0] range.
  */
  MLVec3f touch_pos_and_force[MLInput_MaxControllerTouchpadTouches];
  /*! Normalized trigger value [0.0,1.0]. */
  float trigger_normalized;
  /*! Button states. */
  bool button_state[MLInputControllerButton_Count];
  /*! If this controller's touch is active. */
  bool is_touch_active[MLInput_MaxControllerTouchpadTouches];
  /*! If this controller is connected. */
  bool is_connected;
  /*! Current touchpad gesture. */
  MLInputControllerTouchpadGesture touchpad_gesture;
  /*! Current touchpad gesture state. */
  MLInputControllerTouchpadGestureState touchpad_gesture_state;
  /*!
    \brief Hardware index of this controller. For ML2 physical controller this
    value will always be 0.
  */
  uint8_t hardware_index;
} MLInputControllerStateEx;

/*!
  \brief Initializes values for MLInputControllerStateEx.

  \apilevel 21

  \param[in,out] inout_attr The object to initialize.
*/
ML_STATIC_INLINE void MLInputControllerStateExInit(MLInputControllerStateEx inout_attr[MLInput_MaxControllers]) {
  if (NULL != inout_attr) {
    for (int i = 0; i < MLInput_MaxControllers; ++i) {
      inout_attr[i].version = 1u;
    }
  }
}

/*!
  \brief A structure containing information about the connected devices.

  \apilevel 20
*/
typedef struct MLInputConnectedDevicesList {
  /*! Version of this structure. */
  uint32_t version;
  /*! Number of connected controllers. */
  uint32_t connected_controller_count;
  /*! Pointer to the array of connected controller IDs. */
  const uint8_t *connected_controller_ids;
} MLInputConnectedDevicesList;

/*!
  \brief Initializes default values for #MLInputConnectedDevicesList.

  \apilevel 20

  \param[in,out] inout_devices_list The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLInputConnectedDevicesListInit(MLInputConnectedDevicesList *inout_devices_list) {
  if (inout_devices_list) {
    inout_devices_list->version = 2u;
    inout_devices_list->connected_controller_count = 0u;
    inout_devices_list->connected_controller_ids = NULL;
  }
}

/*!
  \brief A structure containing information about the Pre-Defined pattern to be played.

  \apilevel 20

  When playing haptic pre-defined pattern, needed information is stored in this structure.
*/
typedef struct MLInputPreDefinedPattern {
  /*! Version of this structure. */
  uint32_t version;
  /*! Pre-defined pattern to be played. */
  uint32_t pattern;
} MLInputPreDefinedPattern;

/*!
  \brief Initializes default values for MLInputPreDefinedPattern.

  \param[in,out] inout_pattern The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLInputPreDefinedPatternInit(MLInputPreDefinedPattern *inout_pattern) {
  if (inout_pattern) {
    inout_pattern->version = 1u;
    inout_pattern->pattern = (uint32_t)MLInputPreDefinedPatternType_C;
  }
}

/*!
  \brief A structure containing information about the Buzz command to be played.

  \apilevel 20

  When playing haptic buzz command, needed information is stored in this structure.
*/
typedef struct MLInputBuzzCommand {
  /*! Version of this structure. */
  uint32_t version;
  /*! Start frequency of the buzz command (1 - 1250). */
  uint16_t start_hz;
  /*! End frequency of the buzz command (1 - 1250). */
  uint16_t end_hz;
  /*! Duration of the buzz command in milliseconds (ms). */
  uint32_t duration_ms;
  /*! Amplitude of the buzz command, as a percentage (1 - 100). */
  uint8_t amp;
} MLInputBuzzCommand;

/*!
  \brief Initializes default values for MLInputBuzzCommand.

  \param[in,out] inout_command The object to initialize with default settings.
*/
ML_STATIC_INLINE void MLInputBuzzCommandInit(MLInputBuzzCommand *inout_command) {
  if (inout_command) {
    inout_command->version = 1u;
    inout_command->start_hz = 200;
    inout_command->end_hz = 800;
    inout_command->duration_ms = 1000;
    inout_command->amp = 20;
  }
}

/*!
  \brief A structure containing information about the Buzz command and/or pre-defined pattern to be played.

  A custom haptics pattern can be played by combining Buzz haptic command and/or a pre-defined pattern,
  this structure will hold info of a pattern to be added to the custom haptics array.
  A #MLInputCustomHapticsType should be set while initializing the struct to indicate whether the to-be set
  pattern is a buzz command or a pre-defined pattern.

  The #duration will set the time for which a pattern is played:
  - If the inherited duration of a pre-defined pattern is greater, then it will be cut short
    and the next pattern will start playing.
  - If the inherited duration of a pre-defined pattern is smaller, then it will not repeat itself
    and will wait for the #duration to complete before starting to play the next pattern.
  - Buzz command's duration will supersede the #duration. Above caveat is true in case buzz command's
    duration is smaller.
  - The last pattern of the array will continue playing even if the inherited duration is longer
    than #duration unless the pattern is interrupted by another pattern in the pipeline.
*/
typedef struct MLInputCustomHaptics {
  /*! Type of the pattern to be set. */
  MLInputCustomHapticsType type;
  /*! Either buzz command or pre-defined pattern. */
  union {
    MLInputBuzzCommand buzz;
    MLInputPreDefinedPattern pre_defined;
  } MLInputCustomHapticsPattern;
  /*! Duration of the pattern in millisecond (ms). */
  uint32_t duration_ms;
} MLInputCustomHaptics;

/*!
  \brief A structure containing a list of Buzz command and/or pre-defined patterns to be played.

  \apilevel 20

  A custom haptics pattern can be played by combining Buzz haptic command and/or a pre-defined pattern,
  this structure holds a list of such a combination.
*/
typedef struct MLInputCustomHapticsInfo {
  /*! Version of the structure. */
  uint32_t version;
  /*! An array containing the list of buzz command and/or pre-defined patterns.

      Memory of this variable is managed by user.
  */
  MLInputCustomHaptics *custom;
  /*! Size of the array. */
  uint32_t size;
} MLInputCustomHapticsInfo;

/*!
  \brief Initializes an array of #MLInputCustomHaptics with default values.

  \param[in,out] inout_info The object to #MLInputCustomHapticsInfo struct to initialize the array elements
  with default settings.
*/
ML_STATIC_INLINE void MLInputCustomHapticsInfoInit(MLInputCustomHapticsInfo *inout_info) {
  if (inout_info && inout_info->custom) {
    for (uint32_t it = 0; it < inout_info->size; it++) {
      inout_info->version = 1u;
      inout_info->custom[it].type = MLInputCustomHapticsType_None;
      inout_info->custom[it].MLInputCustomHapticsPattern.pre_defined.pattern = 0;
      inout_info->custom[it].duration_ms = 0;
    }
  }
}

/*!
  \brief Returns an ASCII string for MLInputsResult and MLResult codes.

  \apilevel 8

  \param[in] result The input MLResult enum from MLInput functions.
  \return ASCII string containing readable version of result code.

  \permissions None
*/
ML_API const char *ML_CALL MLInputGetResultString(MLResult result);

/*!
  \brief Creates an input tracker.

  \apilevel 20

  \param[out] out_handle A handle to the created input tracker. Only valid if the return value is MLResult_Ok.
  \retval MLResult_InvalidParam Failed to create the input tracker to an invalid input parameter.
  \retval MLResult_Ok Successfully created the input tracker.
  \retval MLResult_UnspecifiedFailure Failed to create the input tracker due to an unknown error.
  \retval MLInputResult_IllegalState Failed to create the input tracker due to an unexpected state.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputCreate(MLHandle *out_handle);

/*!
  \brief Sets the callbacks for controller input events.

  \apilevel 8

  \param[in] handle Handle to the input tracker.
  \param[in] controller_callbacks Pointer to #MLInputControllerCallbacksEx structure (can be NULL).
  \param[in] user_data Pointer to user payload data; this will be the first argument
             passed to all the callback functions (can be NULL).
  \retval MLResult_InvalidParam Failed to set the callback for controller input events due to an invalid input parameter.
  \retval MLResult_Ok Successfully set the callback for controller input events.
  \retval MLResult_UnspecifiedFailure Failed to set the callback for the controller input events due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputSetControllerCallbacksEx(MLHandle handle, const MLInputControllerCallbacksEx *controller_callbacks, void *user_data);

/*!
  \deprecated Deprecated since 1.1.0. Scheduled for removal.
  \brief Returns current state of all possible input controllers.

  \param[in] handle Handle to the input tracker.
  \param[out] out_state Array of #MLInputControllerState structures that will be populated. The size of this array is at least the size #MLInput_MaxControllers.
  \retval MLResult_InvalidParam Failed to fetch the controller state due to an invalid input parameter.
  \retval MLResult_Ok Successfully fetched the controller state.
  \retval MLResult_UnspecifiedFailure Failed to fetch the controller state due to an unknown error.

  \permissions None
*/
ML_DEPRECATED_MSG("Replaced by MLInputGetControllerStateEx.")
ML_API MLResult ML_CALL MLInputGetControllerState(MLHandle handle, struct MLInputControllerState out_state[MLInput_MaxControllers]);

/*!
  \brief Returns current state of all possible input controllers.

  \apilevel 21

  \param[in] handle Handle to the input tracker.
  \param[out] out_state Array of #MLInputControllerStateEx structures that will be populated. The size of this array is at least the size #MLInput_MaxControllers.
  \retval MLResult_InvalidParam Failed to fetch the controller state due to an invalid input parameter.
  \retval MLResult_Ok Successfully fetched the controller state.
  \retval MLResult_UnspecifiedFailure Failed to fetch the controller state due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputGetControllerStateEx(MLHandle handle, MLInputControllerStateEx out_state[MLInput_MaxControllers]);

/*!
  \brief    Gets the device IDs of all connected devices.

  \apilevel 5

  \param[in]      handle Handle to the input tracker.
  \param[in,out]  inout_devices Pointer to #MLInputConnectedDevicesList structure that will be populated.
                  The app should call #MLInputReleaseConnectedDevicesList to release the contents after use.
  \retval         MLResult_InvalidParam Failed to get the IDs of all connected devices due to an invalid input parameter.
  \retval         MLResult_Ok Successfully fetched the IDs of the connected devices.
  \retval         MLResult_UnspecifiedFailure Failed to get the IDs of all connected devices due to an unknown error.

  \permissions   None
*/
ML_API MLResult ML_CALL MLInputGetConnectedDevices(MLHandle handle, MLInputConnectedDevicesList *inout_devices);

/*!
  \brief Releases the contents of #MLInputConnectedDevicesList populated by #MLInputGetConnectedDevices.

  \apilevel 5

  \param[in]      handle Handle to the input tracker.
  \param[in]      devices Pointer to #MLInputConnectedDevicesList struct. Its contents will be released.
  \retval         MLResult_Ok Successfully released the contents of the device list.
  \retval         MLResult_InvalidParam Failed to release the contents of the device list due to an invalid input parameter.
  \retval         MLResult_UnspecifiedFailure Failed to release the contents of the device list due to an unknown error.

  \permissions   None
*/
ML_API MLResult ML_CALL MLInputReleaseConnectedDevicesList(MLHandle handle, MLInputConnectedDevicesList *devices);

/*!
  \brief Plays the pre-defined pattern.

  \apilevel 20

  \param[in] handle Handle to the input tracker.
  \param[in] controller_id Id of the input controller 0 ~ #MLInput_MaxControllers.
  \param[in] pattern A pointer to #MLInputPredefinedPattern structure (can be NULL).

  \retval MLInputResult_IllegalState The service is either not initialized or terminated or the app is not in focus.
  \retval MLResult_DeviceNotFound The haptic device could not be found.
  \retval MLResult_InvalidParam Failed to start a pre-defined pattern due to an invalid input parameter.
  \retval MLResult_Ok Successfully started a pre-defined pattern on the specified controller.
  \retval MLResult_UnspecifiedFailure Failed to start a pre-defined pattern due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputStartControllerFeedbackPreDefinedPattern(MLHandle handle, uint8_t controller_id, MLInputPreDefinedPattern* pattern);

/*!
  \brief Plays controller haptic buzz command.

  \apilevel 20

  \param[in] handle Handle to the input tracker.
  \param[in] controller_id Id of the input controller 0 ~ #MLInput_MaxControllers.
  \param[in] command A pointer to #MLInputBuzzCommand structure (can be NULL).

  \retval MLInputResult_IllegalState The service is either not initialized or terminated or the app is not in focus.
  \retval MLResult_DeviceNotFound The haptic device could not be found.
  \retval MLResult_InvalidParam Failed to start the buzz command due to an invalid input parameter.
  \retval MLResult_Ok Successfully started the buzz command on the specified controller.
  \retval MLResult_UnspecifiedFailure Failed to start the buzz command due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputStartControllerFeedbackBuzzCommand(MLHandle handle, uint8_t controller_id, const MLInputBuzzCommand* command);

/*!
  \brief Creates a custom haptic pattern.

  \apilevel 20

  A custom haptics pattern is defined as a set of either buzz command and/or pre-defined patterns. Each pattern
  is played for a duration defined as the #duration_ms member of each element of the #MLInputCustomHaptics array.

  \param[in] handle Handle to the input tracker.
  \param[in] info Pointer to #MLInputCustomHapticsInfo struct.
  \param[in,out] inout_pattern_id A pattern Id created by the API, to be used by #MLInputStartControllerFeedbackCustomHapticsPattern.

  \retval MLInputResult_IllegalState The service is either not initialized or terminated.
  \retval MLResult_InvalidParam Failed to create a custom haptic pattern due to an invalid input parameter.
  \retval MLResult_Ok Successfully created a custom haptic pattern.
  \retval MLResult_UnspecifiedFailure Failed to create a custom haptic pattern due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputCreateCustomHapticsPattern(MLHandle handle, MLInputCustomHapticsInfo *info, uint32_t *inout_pattern_id);

/*!
  \brief Plays the custom haptic pattern created by #MLInputCreateCustomHapticsPattern.

  \apilevel 20

  \param[in] handle Handle to the input tracker.
  \param[in] controller_id Id of the input controller 0 ~ #MLInput_MaxControllers.
  \param[in] pattern_id Custom pattern id created by #MLInputCreateCustomHapticsPattern.

  \retval MLInputResult_IllegalState The service is either not initialized or terminated or the app is not in focus.
  \retval MLResult_DeviceNotFound The haptic device could not be found.
  \retval MLResult_InvalidParam Failed to start the custom haptic pattern due to an invalid input parameter.
  \retval MLResult_Ok Successfully started the custom haptic pattern on the specified controller.
  \retval MLResult_UnspecifiedFailure Failed to start the custom haptic pattern due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputStartControllerFeedbackCustomHapticsPattern(MLHandle handle, uint8_t controller_id, uint32_t pattern_id);

/*!
  \brief Deletes the custom haptic pattern created by #MLInputCreateCustomHapticsPattern.

  \apilevel 20

  \param[in] handle Handle to the input tracker.
  \param[in] pattern_id Custom pattern Id created by #MLInputCreateCustomHapticsPattern.

  \retval MLInputResult_IllegalState The service is either not initialized or terminated.
  \retval MLResult_InvalidParam Failed to destroy the custom haptic pattern due to an invalid input parameter.
  \retval MLResult_Ok Successfully destroyed the custom haptic pattern on the specified controller.
  \retval MLResult_UnspecifiedFailure Failed to destroy the custom haptic pattern due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputDeleteCustomHapticsPattern(MLHandle handle, uint32_t pattern_id);

/*!
  \brief Stops the currently playing haptic pattern.

  \apilevel 20

  \param[in] handle Handle to the input tracker.
  \param[in] controller_id Id of the input controller 0 ~ #MLInput_MaxControllers.

  \retval MLInputResult_IllegalState The service is either not initialized or terminated or the app is not in focus.
  \retval MLResult_DeviceNotFound The haptic device could not be found.
  \retval MLResult_InvalidParam Failed to stop the pattern due to an invalid input parameter.
  \retval MLResult_Ok Successfully stopped the pattern on the specified controller.
  \retval MLResult_UnspecifiedFailure Failed to stop the pattern due to an unknown error.

  \permissions None
*/
ML_API MLResult ML_CALL MLInputStopControllerFeedback(MLHandle handle, uint8_t controller_id);

/*!
  \brief Destroys an input tracker.

  \param[in] handle #MLHandle to the input tracker to destroy.
  \retval MLResult_InvalidParam Failed to destroy the input tracker due to an invalid input parameter.
  \retval MLResult_Ok Successfully destroyed the input tracker.
  \retval MLResult_UnspecifiedFailure Failed to destroy the input handler due to an unknown error.
  \retval MLInputResult_IllegalState Failed to destroy the input handler due to an unexpected state.

  \permissions   None
*/
ML_API MLResult ML_CALL MLInputDestroy(MLHandle handle);
/*! \} */
ML_EXTERN_C_END
