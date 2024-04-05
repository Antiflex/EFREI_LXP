using System;
using UnityEngine;

#if UNITY_ANDROID && !UNITY_EDITOR && !MAGICLEAP
using System.Collections;
using System.Collections.Generic;
using Astrolabe.Diagnostics;
using Synergiz.Harbor.Player.Tools;
#endif

namespace Synergiz.Harbor.Player
{
	public class AnchorManager : MonoBehaviour
	{
#if UNITY_ANDROID && !UNITY_EDITOR && !MAGICLEAP
	    private bool _anchorSaved=false;
#endif
		public Guid? AnchorUuid { get; private set; }
		private OVRSpatialAnchor _anchor;

		private void Awake()
		{
			_anchor = GetComponent<OVRSpatialAnchor>();
#if UNITY_ANDROID && !MAGICLEAP && !UNITY_EDITOR
			_anchor.enabled = true;
#else
			_anchor.enabled = false;
#endif
		}

#if UNITY_ANDROID && !UNITY_EDITOR && !MAGICLEAP
		private void Start()
		{
		    if (!_anchorSaved)
		    {
			    if (_anchor == null)
			    {
				    _anchor = GetComponent<OVRSpatialAnchor>();
			    }
			    _anchor.Save((anchor, success) =>
			    {
				    if (success)
				    {
					    AnchorUuid = anchor.Uuid;
						_anchorSaved = true;
						Log.WriteLine("Spatial Anchor saved locally.", LogMessageType.Information, LogTags.META_SCRIPTS);
					}
				    else
				    {
						Log.WriteLine("Failed Saving Spatial Anchor.", LogMessageType.Error, LogTags.META_SCRIPTS);
				    }
			    });
		    }
		}
#endif
	}
}