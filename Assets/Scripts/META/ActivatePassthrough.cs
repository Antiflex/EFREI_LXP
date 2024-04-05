using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Synergiz.Harbor.Player
{
	/// <summary>
	/// Non n�cessaire normalement, mais s�curit� : Permet d'activer (ou non) le passthrough si le script du MRTK l'a d�sactiv� nativement
	/// </summary>
    public class ActivatePassthrough : MonoBehaviour
    {
	    [SerializeField] private bool EnablePassthroughOnAwake = true;

	    private void Awake()
	    {
		    GameObject OVRCameraRig = GameObject.Find("MRTK-Quest_OVRCameraRig(Clone)");
		    if (OVRCameraRig != null)
		    {
			    OVRManager OVRManagerScript = OVRCameraRig.GetComponent<OVRManager>();
			    if (OVRManagerScript != null)
			    {
				    OVRManagerScript.isInsightPassthroughEnabled = EnablePassthroughOnAwake;
			    }
		    }
	    }
    }
}
