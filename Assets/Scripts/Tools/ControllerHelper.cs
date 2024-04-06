#if UNITY_ANDROID && !MAGICLEAP
using Microsoft.MixedReality.Toolkit.XRSDK.Oculus.Input;
#endif
using Microsoft.MixedReality.Toolkit;
using Microsoft.MixedReality.Toolkit.Input;
using Microsoft.MixedReality.Toolkit.Utilities;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.InputSystem;
using UnityEngine.InputSystem.Utilities;
using Vector3 = UnityEngine.Vector3;

namespace Assets.Scripts.Tools
{
	/// <summary>
	/// Helper class to manage controllers (Quest and/or MRTK)
	/// </summary>
	public class ControllerHelper : MonoBehaviour, IMixedRealitySourceStateHandler
	{
		#region EVENTS
		public UnityEvent<ControllerTypes, Handedness> controllerSourceDetected;
		public UnityEvent<ControllerTypes, Handedness> controllerMenuButtonClicked;
		#endregion

		#region PRIVATE
		private static IMixedRealityController _leftController;
		private static IMixedRealityController _rightController;
		#endregion

		public enum ControllerTypes
		{
			None,
			MagicLeap,
			QuestTouch,
		}

		private static ControllerHelper _instance;
		public static ControllerHelper Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = FindAnyObjectByType<ControllerHelper>();
					if (_instance == null)
					{
						_instance = GameObject.Find("ApplicationManager").AddComponent<ControllerHelper>();
					}
				}
				return _instance;
			}
		}

		#region Monobehavior

		private void OnEnable()
		{
			CoreServices.InputSystem?.RegisterHandler<IMixedRealitySourceStateHandler>(this);
		}

		private void OnDisable()
		{
			CoreServices.InputSystem?.UnregisterHandler<IMixedRealitySourceStateHandler>(this);
		}

		private void Update()
		{
#if UNITY_ANDROID
			if (OVRInput.GetUp(OVRInput.Button.Start))
			{
				//On regarde si le bouton start a été pressé, puis relâché dans la frame courante.
				//Le bouton start n'est présent que sur la manette gauche.
				controllerMenuButtonClicked?.Invoke(ControllerTypes.QuestTouch, Handedness.Left);
			}
#endif
		}
		#endregion

		#region Getters/Setters

		/// <summary>
		/// Gets MRTK controllers (even for Quest devices)
		/// </summary>
		/// <param name="controllerHandedness"></param>
		/// <param name="controller"></param>
		public static void GetController(Handedness controllerHandedness, out IMixedRealityController controller)
		{
			SetControllers();
			if (controllerHandedness == Handedness.Left)
			{
				controller = _leftController;
			}
			else if (controllerHandedness == Handedness.Right)
			{
				controller = _rightController;
			}
			else
			{
				controller = null;
			}
		}

		private static void SetControllers()
		{
			IMixedRealityInputSystem inputSystem = CoreServices.InputSystem;

			var controllers = inputSystem?.DetectedControllers;
			if (controllers != null)
			{
				foreach (IMixedRealityController detectedController in controllers)
				{
#if UNITY_ANDROID && !UNITY_EDITOR
					if (detectedController is OculusXRSDKTouchController && detectedController.ControllerHandedness.IsMatch(Handedness.Left))
					{
						_leftController = detectedController;
					}
					else if (detectedController is OculusXRSDKTouchController && detectedController.ControllerHandedness.IsMatch(Handedness.Right))
					{
						_rightController = detectedController;
					}
#else
					if (detectedController.ControllerHandedness.IsMatch(Handedness.Left))
					{
						_leftController = detectedController;
					}
					else if (detectedController.ControllerHandedness.IsMatch(Handedness.Right))
					{
						_rightController = detectedController;
					}
#endif
				}
			}
		}

		/// <summary>
		/// Gets hand or controller position for non-Quest devices
		/// </summary>
		/// <param name="handedness"></param>
		/// <param name="jointPos"></param>
		/// <returns></returns>
		public static bool GetJointPosition(Handedness handedness, out Vector3 jointPos)
		{
			SetControllers();
			var handJointService = CoreServices.GetInputSystemDataProvider<IMixedRealityHandJointService>();

			jointPos = Vector3.zero;

			if (handedness == Handedness.Left)
			{
				if (_leftController != null && _leftController.TrackingState == TrackingState.Tracked)
				{
					foreach (MixedRealityInteractionMapping interactionMapping in _leftController.Interactions)
					{
						// 6DOF controllers support the "SpatialPointer" type (pointing direction)
						// or "GripPointer" type (direction of the 6DOF controller)
						if (interactionMapping.InputType == DeviceInputType.SpatialPointer || interactionMapping.InputType == DeviceInputType.SpatialGrip)
						{
							jointPos = interactionMapping.PositionData;
							return true;
						}
					}
				}
				else
				{
					Transform jointTransform = handJointService.RequestJointTransform(TrackedHandJoint.IndexTip, Handedness.Left);
					if (jointTransform != null)
					{
						jointPos = jointTransform.position;
						return true;
					}
				}
			}
			else if (handedness == Handedness.Right)
			{
				if (_rightController != null && _rightController.TrackingState == TrackingState.Tracked)
				{
					foreach (MixedRealityInteractionMapping interactionMapping in _rightController.Interactions)
					{
						// 6DOF controllers support the "SpatialPointer" type (pointing direction)
						// or "GripPointer" type (direction of the 6DOF controller)
						if (interactionMapping.InputType == DeviceInputType.SpatialPointer || interactionMapping.InputType == DeviceInputType.SpatialGrip)
						{
							jointPos = interactionMapping.PositionData;
							return true;
						}
					}
				}
				else
				{
					Transform jointTransform = handJointService.RequestJointTransform(TrackedHandJoint.IndexTip, Handedness.Right);
					if (jointTransform != null)
					{
						jointPos = jointTransform.position;
						return true;
					}
				}
			}
			return false;
		}

		/// <summary>
		/// For devices that use only one controller, returns the hand in which it is currently held
		/// </summary>
		public Handedness GetSingleControllerHandedness()
		{
			if (IsControllerTracked(Handedness.Any))
			{
				if (!(_leftController is IMixedRealityHand))
				{
					return Handedness.Left;
				}
				if (!(_rightController is IMixedRealityHand))
				{
					return Handedness.Right;
				}
			}

			return Handedness.None;
		}
		#endregion

		#region Checkers

		/// <summary>
		/// Returns true if the left, right, both, or any controllers are currently tracked
		/// </summary>
		/// <param name="handedness"></param>
		/// <param name="setControllers"></param>
		/// <returns></returns>
		public bool IsControllerTracked(Handedness handedness, bool setControllers = true)
		{
			if (setControllers)
			{
				SetControllers();
			}

			if (handedness == Handedness.Left || handedness == Handedness.Any)
			{
				if (!(_leftController is IMixedRealityHand))
				{
					return true;
				}
			}
			if (handedness == Handedness.Right || handedness == Handedness.Any)
			{
				if (!(_rightController is IMixedRealityHand))
				{
					return true;
				}
			}

			if (handedness == Handedness.Both)
			{
				if (!(_leftController is IMixedRealityHand) && !(_rightController is IMixedRealityHand))
				{
					return true;
				}
			}

			return false;
		}

		/// <summary>
		/// Checks if the requested button is currently pressed on any supported controller.
		/// Currently supports Menu (start) button and Index Trigger
		/// </summary>
		/// <param name="button"></param>
		/// <param name="controllerType">Controller type if button is pressed. None if not pressed.</param>
		/// <param name="handedness"></param>
		/// <returns>True if pressed</returns>
		public bool IsButtonPressed(ControllerButtons button, Handedness handedness, out ControllerTypes controllerType)
		{
#if UNITY_ANDROID
			TwinkleControllerButtonToQuestButton(button, out OVRInput.Button questButton, out OVRInput.Axis1D questTrigger);

			OVRInput.Controller requestedController = handedness switch
			{
				Handedness.Right => OVRInput.Controller.RTouch,
				Handedness.Left => OVRInput.Controller.LTouch,
				Handedness.Both => OVRInput.Controller.All,
				_ => OVRInput.Controller.Active
			};

			if (questButton != OVRInput.Button.None)
			{
				if (OVRInput.Get(questButton, requestedController))
				{
					controllerType = ControllerTypes.QuestTouch;
					return true;
				}
			}
			else if (questTrigger != OVRInput.Axis1D.None)
			{
				if (OVRInput.Get(questTrigger, requestedController) > 0.9f)
				{
					controllerType = ControllerTypes.QuestTouch;
					return true;
				}
			}
#endif
			controllerType = ControllerTypes.None;
			return false;
		}

		/// <summary>
		/// Checks if the requested button was pressed on the current frame on any supported controller.
		/// </summary>
		/// <param name="button"></param>
		/// <param name="controllerType">Controller type if button is pressed. None if not pressed.</param>
		/// <param name="handedness">None if not pressed</param>
		/// <returns>True if pressed on this frame only</returns>
		public bool IsButtonPressedThisFrame(ControllerButtons button, Handedness handedness, out ControllerTypes controllerType)
		{
#if UNITY_ANDROID
			TwinkleControllerButtonToQuestButton(button, out OVRInput.Button questButton, out OVRInput.Axis1D questTrigger);

			OVRInput.Controller requestedController = handedness switch
			{
				Handedness.Right => OVRInput.Controller.RTouch,
				Handedness.Left => OVRInput.Controller.LTouch,
				Handedness.Both => OVRInput.Controller.All,
				_ => OVRInput.Controller.Active
			};

			if (questButton != OVRInput.Button.None)
			{
				if (OVRInput.GetDown(questButton, requestedController))
				{
					controllerType = ControllerTypes.QuestTouch;
					return true;
				}
			}
			else if (questTrigger != OVRInput.Axis1D.None)
			{
				if (OVRInput.Get(questTrigger, requestedController) > 0.9f)
				{
					controllerType = ControllerTypes.QuestTouch;
					return true;
				}
			}
#endif
			controllerType = ControllerTypes.None;
			return false;
		}

		#endregion

		#region Event Actions

		/// <summary>
		/// MagicLeap menu button is pressed
		/// </summary>
		private void MagicLeap_Menu_performed(InputAction.CallbackContext context)
		{
			var device = context.control.device;
			if (device.usages.Contains(CommonUsages.LeftHand))
			{
				controllerMenuButtonClicked?.Invoke(ControllerTypes.MagicLeap, Handedness.Left);
			}
			else
			{
				controllerMenuButtonClicked?.Invoke(ControllerTypes.MagicLeap, Handedness.Right);
			}
		}

		/// <summary>
		/// Raised when new controller source is detected. Does not support hands.
		/// </summary>
		/// <param name="eventData"></param>
		public void OnSourceDetected(SourceStateEventData eventData)
		{
			ControllerTypes type = ControllerTypes.None;

#if UNITY_ANDROID && !MAGICLEAP
			if (eventData.Controller is OculusXRSDKTouchController)
			{
				type = ControllerTypes.QuestTouch;
			}
#endif
			controllerSourceDetected?.Invoke(type, eventData.Controller?.ControllerHandedness ?? Handedness.None);
		}

		public void OnSourceLost(SourceStateEventData eventData)
		{
		}

		#endregion

		#region Utilitary

#if UNITY_ANDROID
		/// <summary>
		/// Translates astrolabe controller button into the quest input (for mapping)
		/// On Quest, triggers are of a different type than buttons
		/// </summary>
		/// <param name="twinkleButton"></param>
		/// <param name="buttonOnDevice">Button of device type. None if request is a trigger.</param>
		/// <param name="triggerOnDevice">Trigger of device type. None if requets is a button.</param>
		private void TwinkleControllerButtonToQuestButton(ControllerButtons twinkleButton, out OVRInput.Button buttonOnDevice, out OVRInput.Axis1D triggerOnDevice)
		{
			buttonOnDevice = twinkleButton switch
			{
				ControllerButtons.Menu => OVRInput.Button.Start,
				ControllerButtons.A => OVRInput.Button.One,
				ControllerButtons.B => OVRInput.Button.Two,
				ControllerButtons.X => OVRInput.Button.Three,
				ControllerButtons.Y => OVRInput.Button.Four,
				ControllerButtons.Joystick => OVRInput.Button.PrimaryThumbstick,
				_ => OVRInput.Button.None
			};
			if (buttonOnDevice == OVRInput.Button.None)
			{
				triggerOnDevice = twinkleButton switch
				{
					ControllerButtons.Trigger => OVRInput.Axis1D.PrimaryIndexTrigger,
					ControllerButtons.Bumper => OVRInput.Axis1D.PrimaryHandTrigger,
					_ => OVRInput.Axis1D.None
				};
			}
			else
			{
				triggerOnDevice = OVRInput.Axis1D.None;
			}
		}
#endif
		public enum ControllerButtons
		{
			None,
			Menu,
			Trigger,
			Bumper,
			Touchpad,
			A,
			B,
			X,
			Y,
			Joystick,
			Any,
		}
		#endregion
	}
}
