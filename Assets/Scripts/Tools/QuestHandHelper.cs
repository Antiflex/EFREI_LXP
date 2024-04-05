using Microsoft.MixedReality.Toolkit;
using Microsoft.MixedReality.Toolkit.Input;
using Microsoft.MixedReality.Toolkit.Utilities;
using UnityEngine;

namespace Assets.Scripts.Tools
{
	public static class QuestHandHelper
	{
		private static GameObject _leftHandGo;
		private static GameObject _rightHandGo;

		private static OVRHand _leftOvrHand;
		private static OVRSkeleton _leftOvrSkeleton;
		private static OVRHand _rightOvrHand;
		private static OVRSkeleton _rightOvrSkeleton;

		private static IMixedRealityController _leftController;
		private static IMixedRealityController _rightController;

		/// <summary>
		/// Gets the OVRHand object (Quest)
		/// </summary>
		/// <param name="handedness"></param>
		/// <param name="hand"></param>
		/// <param name="skeleton"></param>
		public static void GetOvrHand(OVRInput.Handedness handedness, out OVRHand hand, out OVRSkeleton skeleton)
		{
			SetHands();
			if (handedness == OVRInput.Handedness.RightHanded)
			{
				hand = _rightOvrHand;
				skeleton = _rightOvrSkeleton;
			}
			else if (handedness == OVRInput.Handedness.LeftHanded)
			{
				hand = _leftOvrHand;
				skeleton = _leftOvrSkeleton;
			}
			else
			{
				hand = null;
				skeleton = null;
			}
		}

		/// <summary>
		/// Gets hands or controller Pose for Quest devices (OVR)
		/// </summary>
		/// <param name="joint"></param>
		/// <param name="handedness"></param>
		/// <param name="bonePose"></param>
		public static void GetOvrBonePose(TrackedHandJoint joint, OVRInput.Handedness handedness, out Pose bonePose)
		{
			SetHands();
			SetControllers();
			GetOvrBoneIDFromJoint(joint, out OVRSkeleton.BoneId boneId);

			OVRBone bone;
			bonePose = Pose.identity;

			if (handedness == OVRInput.Handedness.LeftHanded)
			{
				if (_leftOvrSkeleton != null && _leftOvrSkeleton.Bones.Count > 0)
				{
					bone = _leftOvrSkeleton.Bones[(int)boneId];
					bonePose = new Pose(bone.Transform.position, bone.Transform.rotation);
				}
				else if (_leftController != null && _leftController.TrackingState == TrackingState.Tracked)
				{
					Transform controllerTransformLeft = GameObject.FindGameObjectWithTag("QuestControllerLeftLaser")?.transform;

					if (controllerTransformLeft != null)
					{
						bonePose = new Pose(controllerTransformLeft.position, controllerTransformLeft.rotation);
					}
				}
			}
			else if (handedness == OVRInput.Handedness.RightHanded)
			{
				if (_rightOvrSkeleton != null && _rightOvrSkeleton.Bones.Count > 0)
				{
					bone = _rightOvrSkeleton.Bones[(int)boneId];
					bonePose = new Pose(bone.Transform.position, bone.Transform.rotation);
				}
				else if (_rightController != null && _rightController.TrackingState == TrackingState.Tracked)
				{

					Transform controllerTransformRight = GameObject.FindGameObjectWithTag("QuestControllerRightLaser")?.transform;

					if (controllerTransformRight != null)
					{
						bonePose = new Pose(controllerTransformRight.position, controllerTransformRight.rotation);
					}
				}
			}
		}

		private static void SetHands()
		{
			if (_leftHandGo == null)
			{
				_leftHandGo = GameObject.Find("OVRHandPrefab_Left");
			}
			if (_leftHandGo != null)
			{
				_leftHandGo.TryGetComponent(out _leftOvrHand);
				_leftHandGo.TryGetComponent(out _leftOvrSkeleton);
			}

			if (_rightHandGo == null)
			{
				_rightHandGo = GameObject.Find("OVRHandPrefab_Right");
			}
			if (_rightHandGo != null)
			{
				_rightHandGo.TryGetComponent(out _rightOvrHand);
				_rightHandGo.TryGetComponent(out _rightOvrSkeleton);
			}
		}

		private static void SetControllers()
		{
			ControllerHelper.GetController(Handedness.Left, out _leftController);
			ControllerHelper.GetController(Handedness.Right, out _rightController);
		}

		/// <summary>
		/// Translates MRTK joints to OVR joints
		/// </summary>
		/// <param name="joint"></param>
		/// <param name="boneId"></param>
		public static void GetOvrBoneIDFromJoint(TrackedHandJoint joint, out OVRSkeleton.BoneId boneId)
		{
			boneId = joint switch
			{
				TrackedHandJoint.Wrist => OVRSkeleton.BoneId.Hand_WristRoot,
				TrackedHandJoint.Palm => OVRSkeleton.BoneId.Hand_WristRoot,

				TrackedHandJoint.IndexKnuckle => OVRSkeleton.BoneId.Hand_Index1,
				TrackedHandJoint.IndexMiddleJoint => OVRSkeleton.BoneId.Hand_Index2,
				TrackedHandJoint.IndexDistalJoint => OVRSkeleton.BoneId.Hand_Index3,
				TrackedHandJoint.IndexTip => OVRSkeleton.BoneId.Hand_IndexTip,

				TrackedHandJoint.MiddleKnuckle => OVRSkeleton.BoneId.Hand_Middle1,
				TrackedHandJoint.MiddleMiddleJoint => OVRSkeleton.BoneId.Hand_Middle2,
				TrackedHandJoint.MiddleDistalJoint => OVRSkeleton.BoneId.Hand_Middle3,
				TrackedHandJoint.MiddleTip => OVRSkeleton.BoneId.Hand_MiddleTip,

				TrackedHandJoint.RingKnuckle => OVRSkeleton.BoneId.Hand_Ring1,
				TrackedHandJoint.RingMiddleJoint => OVRSkeleton.BoneId.Hand_Ring2,
				TrackedHandJoint.RingDistalJoint => OVRSkeleton.BoneId.Hand_Ring3,
				TrackedHandJoint.RingTip => OVRSkeleton.BoneId.Hand_RingTip,

				TrackedHandJoint.PinkyMetacarpal => OVRSkeleton.BoneId.Hand_Pinky0,
				TrackedHandJoint.PinkyKnuckle => OVRSkeleton.BoneId.Hand_Pinky1,
				TrackedHandJoint.PinkyMiddleJoint => OVRSkeleton.BoneId.Hand_Pinky2,
				TrackedHandJoint.PinkyDistalJoint => OVRSkeleton.BoneId.Hand_Pinky3,
				TrackedHandJoint.PinkyTip => OVRSkeleton.BoneId.Hand_PinkyTip,

				TrackedHandJoint.ThumbMetacarpalJoint => OVRSkeleton.BoneId.Hand_Thumb0,
				TrackedHandJoint.ThumbProximalJoint => OVRSkeleton.BoneId.Hand_Thumb1,
				TrackedHandJoint.ThumbDistalJoint => OVRSkeleton.BoneId.Hand_Thumb3,
				TrackedHandJoint.ThumbTip => OVRSkeleton.BoneId.Hand_ThumbTip,
				_ => OVRSkeleton.BoneId.Invalid
			};
		}
	}
}
