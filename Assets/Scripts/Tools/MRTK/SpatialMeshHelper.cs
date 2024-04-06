using Microsoft.MixedReality.Toolkit;
using Microsoft.MixedReality.Toolkit.SpatialAwareness;
using System;
using UnityEngine;

namespace Assets.Scripts.Tools.MRTK
{
	public static class SpatialMeshHelper
	{
		private static bool GetSpatialMeshObserver(out IMixedRealitySpatialAwarenessMeshObserver meshObs)
		{
			try
			{
				var observer = CoreServices
					.GetSpatialAwarenessSystemDataProvider<IMixedRealitySpatialAwarenessMeshObserver>();

				if (observer != null)
				{
					meshObs = observer;
				}
				else
				{
					throw new System.Exception("No Providers found");
				}

				return true;
			}
			catch (Exception e)
			{
				if (Debug.isDebugBuild)
				{
					Debug.LogError("Exception on SpatialMeshHelper.GetSpatialMeshObserver : " + e.Message);
				}

				meshObs = null;
				return false;
			}
		}

		public static bool SetSpatialMeshRenderer(SpatialAwarenessMeshDisplayOptions option)
		{
			if (GetSpatialMeshObserver(out IMixedRealitySpatialAwarenessMeshObserver obs))
			{
				obs.DisplayOption = option;
				return true;
			}

			return false;
		}
	}
}